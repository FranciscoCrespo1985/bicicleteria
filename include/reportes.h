#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED

void ponerIntCero(int *,int);
void matrizEnCero(int ** ,int , int  );
void deleteMatrix(int **,int);
void orderaMatrix(int **, int);
void ponerFloatCero(float[],int);
// cliente con mas ventas

void reporte3(){
      char mmes[12][15];
      strcpy(mmes[0],"Enero");
      strcpy(mmes[1],"Febrero");
      strcpy(mmes[2],"Marzo");
      strcpy(mmes[3],"Abril");
      strcpy(mmes[4],"Mayo");
      strcpy(mmes[5],"Junio");
      strcpy(mmes[6],"Julio");
      strcpy(mmes[7],"Agosto");
      strcpy(mmes[8],"Septiembre");
      strcpy(mmes[9],"OCtubre");
      strcpy(mmes[10],"Noviembre");
      strcpy(mmes[11],"Diciembre");


    int pos =0;
    long valAnual;
    float vecC[12];
    float vecV[12];

    ponerFloatCero(vecC,12);
    ponerFloatCero(vecV,12);

    C_Ventas vv;
    C_Compras cc;
    Cliente c;
    while(vv.LeerDisco(pos++)==1){
               vecV[vv.GetFVenta().mes-1]+=getPrecioTotal(vv);
    }
    pos=0;
    while(cc.LeerDisco(pos++)==1){
            vecC[cc.getFPedido().mes-1]+=getPrecioTotal(cc);
    }
    cout<<endl;
    cout<<setw(15)<<left<<"MES"<<setw(20)<<right<<"INGRESOS"<<setw(20)<<right<<"EGRESOS"<<setw(20)<<right<<"VALANCE"<<endl;
    for(int i=0;i<12;i++){
        cout<<setw(15)<<left<<mmes[i]<<setw(20)<<right<<vecV[i]<<setw(20)<<right<<vecC[i]<<setw(20)<<right<<vecV[i]-vecC[i]<<endl;
        valAnual+= vecV[i]-vecC[i];
    }
    cout<<endl<<endl;
    cout<<right<<setw(60)<<"VALANCE ANUAL"<< setw(15)<<right<<valAnual<<endl;
}

void reporte2(){
    Ventas vv;
    C_Ventas cv;
    int cant =cantCVentas();
    int pos=0;
    Producto p;
    int puntero=0;
    int cantP = cantProductos();
    int **vecP = new int *[cantP];

    for(int i=0; i<cantP; i++){
        vecP[i] = new int[2];
    }
    matrizEnCero(vecP,cantP,2);

    for(int i =0; i< cant; i++){
        cv.LeerDisco(i);

        if(cv.GetEstado()==1)
        {
            for(int j=0; j< cantVentas();j++)
            {
                vv.LeerDisco(j);
                if(strcmp(cv.GetIDFactura(),vv.GetIdFactura())==0)
                {
                    puntero = buscarPos(vv.GetIDProd(),p);
                    if(puntero!=-1){
                        vecP[puntero][1]+=vv.GetCant();
                    }
                    if(puntero ==-1){
                        puntero=buscarEliminado(vv.GetIDProd(),p);
                        vecP[puntero][1]+=vv.GetCant();
                    }
                }
            }
        }
    }
    orderaMatrix(vecP,cantP);

    for(int i=0; i<cantP; i++){
        p.LeerDisco(vecP[i][0]);
        cout <<left<<setw(20)<<p.GetID();
        cout<<left<<setw(20)<<p.GetNombre()<<setw(20)<<vecP[i][1]<<endl;
    }
    deleteMatrix(vecP,cantP);
}

void reporte1(){
    int cant;
    int eli=0;
    int **vecP = new int * [cantClientes()];

    for(int i=0; i<cantClientes(); i++)
    {
        vecP[i] = new int[2];
    }
    matrizEnCero(vecP,cantClientes(),2);

    cant  = cantCVentas();
    Cliente c;



    C_Ventas *cv;
    cv = new C_Ventas[cant];

    for(int i=0; i<cant; i++)
    {
        cv[i].LeerDisco(i);
    }

    for(int i=0; i<cant; i++)
    {
        if(buscarPos(cv[i].GetDNICliente(),c)==-1){
            vecP[buscarEliminado(cv[i].GetDNICliente(),c)][1]+=getPrecioTotal(cv[i]);
        }else{
            vecP [buscarPos(cv[i].GetDNICliente(), c)][1]+= getPrecioTotal(cv[i]);
        }
    }
    orderaMatrix(vecP,cantClientes());
    cout << fixed;
    cout<<left<<setw(20)<<"DNI"<<setw(20)<<"NOMBRE"<<setw(20)<<"MONTO"<<endl;
    for(int i=0; i<cantClientes(); i++)
    {
        c.LeerDisco(vecP[i][0]);

        cout <<left<<setw(20)<<c.GetDni();
        cout<<left<<setw(20)<<c.GetNombre()<<setw(20)<<vecP[i][1]<<endl;
    }

    delete(cv);
    deleteMatrix(vecP,cantClientes());
}
/////////////////////////////////////// cliente mas comprador ///////////////////////////

void orderaMatrix(int **vec, int rows )
{
    int aux[2];

    for (int i=0; i<rows-1; i++)
    {
        for(int j=0; j<rows-i-1; j++)
        {
            if(vec[j][1]<vec[j+1][1])
            {
                aux[0]=vec[j][0];
                aux[1]=vec[j][1];
                vec[j][0]=vec[j+1][0];
                vec[j][1]=vec[j+1][1];
                vec[j+1][0]=aux[0];
                vec[j+1][1]=aux[1];
            }
        }
    }
}

void deleteMatrix(int **matrix,int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}


void ponerFloatCero(float vec[],int sice){
    for(int i=0;i<sice;i++){
        vec[i]=0;
    }

}

void matrizEnCero(int **m ,int fila, int col )
{
    for(int i=0; i<fila; i++)
    {
        for(int j=0; j<col; j++)
        {
            m[i][j]=0;
        }
    }
    for(int i=0; i<fila; i++)
    {
        m[i][0]=i;
    }
}

void ponerIntCero(int *vec, int sice )
{
    for(int i=0; i<sice; i++)
    {
        vec[i]=0;
    }
}







#endif // REPORTES_H_INCLUDED
