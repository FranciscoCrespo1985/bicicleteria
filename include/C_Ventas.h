#ifndef C_VENTAS_H
#define C_VENTAS_H

struct fVenta{ int dia, mes, anio;};

char * ARCH_C_VENTA="datos/c_venta.fjc";

class C_Ventas
{

    private:
          char IDFactura[7];
          char dniCliente[15];
          fVenta f;
          int tipo_de_factura;
          int estado =1;
   public:

         char * GetIDFactura(){return IDFactura;};
         char * GetDNICliente(){return dniCliente;};
         fVenta GetFVenta(){return f;};
         int getTipoFactura(){return tipo_de_factura;};
         int GetEstado(){return estado;};

         void SetIDFactura(char * idf){strcpy(IDFactura,idf);};
         void SetDNICliente(char* dni){strcpy(dniCliente,dni);};
         void SetfVenta(fVenta ff){f=ff;};
         void SetTipoFactura(int tdf){tipo_de_factura=tdf;};
         void setEstado(int e){estado=e;};

        void Cargar(int,Cliente&);
        void Mostrar(Cliente&,float);
        bool LeerDisco(int);
        void Guardar(int);
};




void C_Ventas::Cargar(int nVenta,Cliente& c){

    Validar v;
    Fecha f;

    int correcto= 0;
    char dni[15];
    char id[7];
    int opc[]={1,2,3};
    int selTipo=0;
    this->f.anio=f.getAnio();
    this->f.dia=f.getDia();
    this->f.mes=f.getMes();


    snprintf(IDFactura, 7, "%d", ++nVenta);



    /// necesita una instancia de cliente para chequear que exista y que este en estado 1

   while(!correcto){
        v.header("Alta Venta");
        listarClientes(1);
        cout<<"Seleccione un cliente: \n";
        cin >> dni;
        if(buscarPos(dni,c)!=-1){
            SetDNICliente (dni);
            cout<< "El cliente SELECCIONADO FUE:\n"<<c.GetApellido()<<" "<< c.GetNombre()<<endl;
            cout<< "CONFIRMAR: 1: Correcto 0: Incorrecto: ";
            cin>>correcto;
        }
    }

    cout<< "Seleciconar tipo de factura: \n1=A, 2=B, 3=C\n";
    while((selTipo=v.validarOpcion(opc,3))==-1)cout<< "Valor incorrecto\n Ingrese 1=A 2=C 3=C\n";
    SetTipoFactura(selTipo);

}

void C_Ventas::Mostrar(Cliente &c,float total){
        char tipo;
        if(buscarPos(GetDNICliente(),c)==-1){
            buscarEliminado(GetDNICliente(),c);
        }
        if(tipo_de_factura==1){
            tipo ='A';
        }else if(tipo_de_factura==2){
            tipo ='B';
        }else{
            tipo ='C';
        }
        cout << fixed;
        cout << setprecision(2);

        cout << left << setw(10) << "N Factura";
        cout << left << setw(20) << "Nombre";
        cout << left << setw(10) << "DNI";
        cout << left << setw(10) << "F. de Venta";
        cout << left << setw(7) << " T. Factura";
        cout << right << setw(10) << "Importe\n";

        cout << left << setw(10) << GetIDFactura();
        cout << left << setw(20) << c.GetNombre();
        cout << left << setw(10) <<  GetDNICliente();
        cout << left << f.dia<<"/"<<f.mes<<"/"<<f.anio<<"  ";
        cout << right << setw(10) <<  tipo;
        cout << right << setw(10) << total<<endl;
}



void C_Ventas::Guardar(int pos){
     FILE *p;

    if(pos >=0){
        p = fopen(ARCH_C_VENTA,"rb+");
        if(p == NULL){
            exit(1);
        }
        fseek(p,pos*sizeof(C_Ventas),0);
    } else {
        p = fopen(ARCH_C_VENTA,"ab");
        if(p==NULL){
            exit(1);
        }
    }
    fwrite(this,sizeof*this ,1,p);
    fclose(p);

}


bool C_Ventas::LeerDisco(int pos){
    bool leyo;
    FILE *p;
    p=fopen(ARCH_C_VENTA,"rb");
    if(p==NULL) exit(1);


    fseek(p,sizeof*this*pos,0);
    leyo = fread(this,sizeof*this,1,p);
    fclose(p);
    return leyo;
}


int cantCVentas();
void NuevaVenta();
void listarVentas(int);
float getPrecioTotal(C_Ventas &);
int buscarPos(char[7],C_Ventas&);

void ventasOtrosListados();
void ventasOtrasConsultas();
void ordenadoPorFecha(C_Ventas*,int);
void ordenadoPorDNI(C_Ventas*,int);
void ordenadoPorMonto(C_Ventas*,int);
void buscarImporte();
void buscarFecha();
void buscarTipoDeFactura();


void ventasOtrosListados(){
    Validar v;
    int cant = cantCVentas();
    C_Ventas *cv;
    cv = new C_Ventas[cant];
    for(int i=0;i<cant;i++){
            cv[i].LeerDisco(i);
    }

    int opcion;
    while(true){

    v.header("Ventas Listados");

    cout<<" 1) ORDENADOS POR FECHA"<<endl;
    cout<<" 2) ORDENADOS POR DNI"<<endl;
    cout<<" 3) ORDENADOS POR MONTO"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A PROVEEDORES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
                ordenadoPorFecha(cv,cant);
          break;
          case 2:
                ordenadoPorDNI(cv,cant);
          break;
          case 3:
                 ordenadoPorMonto(cv,cant);
          break;
          case 0:
              system("cls");
              delete[] cv;
              return;

          break;
        }
    }
}

void ordenadoPorFecha(C_Ventas * cv, int cant){

    Validar v;
    C_Ventas aux;
    Cliente c;
    Fecha f,ff;

    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){

            f.setAnio(cv[j].GetFVenta().anio);
            f.setMes(cv[j].GetFVenta().mes);
            f.setDia(cv[j].GetFVenta().dia);

            ff.setAnio(cv[j+1].GetFVenta().anio);
            ff.setMes(cv[j+1].GetFVenta().mes);
            ff.setDia(cv[j+1].GetFVenta().dia);

            if(f<ff){
                aux = cv[j];
                cv[j] = cv[j+1];
                cv[j+1] =aux;
            }

        }
    }


    v.header("VENTAS POR FECHA");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(12)<<"N FACTURA"<<setw(20)<<"NOMBRE"<<setw(15)<<"DNI"<<setw(15)<<"F. DE VENTA"<<right<<setw(12)<<"IMPORTE"<<endl;

    for (int i=0; i<cant;i++){
        if(cv[i].GetEstado()==1){
            buscarPos(cv[i].GetDNICliente(),c);
            cout << fixed;
            cout << setprecision(2);
            cout <<left<<setw(12)<<cv[i].GetIDFactura()<<setw(20)<<c.GetNombre()<<setw(15)<<c.GetDni()<<cv[i].GetFVenta().dia<<"/"<<cv[i].GetFVenta().mes<<"/"<<cv[i].GetFVenta().anio<<setw(3)<<" "<<right<<setw(15)<<getPrecioTotal(cv[i])<<endl;

        }
    }
    cout << endl;
    system("pause");


}

void ordenadoPorDNI(C_Ventas *cv ,int cant){

    Validar v;
    C_Ventas aux;
    Cliente c;



    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){


            if( atol(cv[j].GetDNICliente())>atol(cv[j+1].GetDNICliente()) ){
                aux = cv[j];
                cv[j] = cv[j+1];
                cv[j+1] =aux;
            }
        }
    }


    v.header("VENTAS POR DNI");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(12)<<"N FACTURA"<<setw(20)<<"NOMBRE"<<setw(15)<<"DNI"<<setw(15)<<"F. DE VENTA"<<right<<setw(12)<<"IMPORTE"<<endl;

    for (int i=0; i<cant;i++){
        if(cv[i].GetEstado()==1){
            buscarPos(cv[i].GetDNICliente(),c);
            cout << fixed;
            cout << setprecision(2);
            cout <<left<<setw(12)<<cv[i].GetIDFactura()<<setw(20)<<c.GetNombre()<<setw(15)<<c.GetDni()<<cv[i].GetFVenta().dia<<"/"<<cv[i].GetFVenta().mes<<"/"<<cv[i].GetFVenta().anio<<setw(3)<<" "<<right<<setw(15)<<getPrecioTotal(cv[i])<<endl;

        }
    }
    cout << endl;
    system("pause");


}
void ordenadoPorMonto(C_Ventas * cv , int cant){

    Validar v;
    C_Ventas aux;
    Cliente c;



    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){
            if(getPrecioTotal(cv[i])>getPrecioTotal(cv[i+1])){
                aux = cv[j];
                cv[j] = cv[j+1];
                cv[j+1] =aux;
            }
        }
    }


    v.header("VENTAS POR MONTO");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(12)<<"N FACTURA"<<setw(20)<<"NOMBRE"<<setw(15)<<"DNI"<<setw(15)<<"F. DE VENTA"<<right<<setw(12)<<"IMPORTE"<<endl;

    for (int i=0; i<cant;i++){
        if(cv[i].GetEstado()==1){
            buscarPos(cv[i].GetDNICliente(),c);
            cout << fixed;
            cout << setprecision(2);
            cout <<left<<setw(12)<<cv[i].GetIDFactura()<<setw(20)<<c.GetNombre()<<setw(15)<<c.GetDni()<<cv[i].GetFVenta().dia<<"/"<<cv[i].GetFVenta().mes<<"/"<<cv[i].GetFVenta().anio<<setw(3)<<" "<<right<<setw(15)<<getPrecioTotal(cv[i])<<endl;

        }
    }
    cout << endl;
    system("pause");
}





void ventasOtrasConsultas(){
    int opcion;
    Validar v;

    while(true){
    v.header("Ventas Consultas");

    cout<<" 1) CONSULTAR POR FECHA"<<endl;
    cout<<" 2) CONSULTAR POR IMPORTE"<<endl;
    cout<<" 3) CONSULTAR POR TIPO DE FACTURA"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A CLIENTES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
    cin>>opcion;
        switch (opcion){
          case 1:
                buscarFecha();

          break;
          case 2:
                buscarImporte();

          break;
          case 3:
                buscarTipoDeFactura();
          break;
          case 0:
            system("cls");
          return;

          break;
        }
    }


}


void buscarTipoDeFactura(){
        Validar v;
        Cliente c;
        C_Ventas cv;
        bool found = false;
        int opc[]={1,2,3};
        int selTipo;
        int pos=0;

        cout<< "Seleciconar tipo de factura: \n1=A, 2=B, 3=C\n";
        while((selTipo=v.validarOpcion(opc,3))==-1)cout<< "Valor incorrecto\n Ingrese 1=A 2=C 3=C\n";

        while(cv.LeerDisco(pos++)){
            if(cv.getTipoFactura()==selTipo){
                cv.Mostrar(c,getPrecioTotal(cv));
                found=true;
            }
        }
        if(!found){
            cout<< "No se encontraron ventas con ese tipo de factura\n";
        }
         system("pause");

}

void buscarImporte(){
        cout<<endl<<"Favor de Importe: ";
        Validar v;
        bool found=false;
        float importe,importeA=999999,dif;;
        importe = v.validarFloat(0,999999);
        C_Ventas cv;
        Cliente c;
        int pos=0,pos2;
        float masCercano;




        while(cv.LeerDisco(pos)){
            dif=v.matDist(getPrecioTotal(cv),importe);
            if(dif!=0){
                    if(dif<importeA){
                        importeA=dif;
                        pos2=pos;
                     }
            }else{
                cv.Mostrar(c,getPrecioTotal(cv));
                found=true;
                break;
            }
            pos++;
        }
        if(!found){
            cout <<"El importe mas cercano al ingresado esta en la factura: "<<endl;
            cv.LeerDisco(pos2);
            cv.Mostrar(c,getPrecioTotal(cv));
        }
        system("pause");

}



void buscarFecha(){
        cout<<endl<<"Favor de ingresar fecha";
        bool found=false;
        C_Ventas cv;
        Cliente c;
        int pos=0;

        Fecha fl,fi;
        Validar v;

        fi.CargarFecha();
        while(cv.LeerDisco(pos++)==1){
            fl.setAnio(cv.GetFVenta().anio);
            fl.setMes(cv.GetFVenta().mes);
            fl.setDia(cv.GetFVenta().dia);
            if(fl==fi){
                if(cv.GetEstado()==1){
                    cv.Mostrar(c,getPrecioTotal(cv));
                    found=true;
                }
            }
        }

        if(!found){
            cout<<"NO EXISTEN VENTAS EN LA FECHA INGRESADA"<<endl;
        fi.MostrarFecha();
        }
        system("pause");


}

void eliminarVenta(){

    listarVentas(0);
}

int buscarPos(char idFactura[7],C_Ventas &cv){

    for(int i = 0; i<cantCVentas();i++){
            cv.LeerDisco(i);
            if(strcmp(cv.GetIDFactura(),idFactura)==0){
                return i;
            }
    }
    return -1;
}

void listarVentas(int opc){
    char selVenta[7];
    Validar v;int pos=-1;
    C_Ventas cv;
    Cliente c;
    Ventas vv;
    int cant = cantCVentas();

    for(int i =0; i< cant;i++){
        cv.LeerDisco(i);
        if(cv.GetEstado()==1){
            cv.Mostrar(c,getPrecioTotal(cv));
        }
    }

    cout<< "Elegir la factura: ";
    v.validarString("N Venta",selVenta,7);
    v.header("FACTURA");
    pos=buscarPos(selVenta,cv);
    cv.LeerDisco(pos);
    if(pos!=-1&&cv.GetEstado()){
        if(opc==1){
            cv.Mostrar(c,getPrecioTotal(cv));
            cout<<endl;
            listarVentasPorFactura(selVenta);
        }else if(opc==0){
            cv.setEstado(0);
            cv.Guardar(pos);
        }
    }
}


void nuevaVenta(){
    Validar v;
    C_Ventas cv;
    Ventas vv;
    int pos=0;
    int comprar = 1;


    Cliente c;
    cv.Cargar(cantCVentas(),c);

    cv.Mostrar(c,getPrecioTotal(cv));
    while(comprar){
        altaVenta(cv.GetIDFactura(),c);

        cout<<"Desea agregar otro item: 1-Si 0-No\n";
        cin >> comprar;
    }

    cv.Guardar(-1);
    v.header("Factura");
    cv.Mostrar(c, getPrecioTotal(cv));
    cout<<endl;

    while(vv.LeerDisco(pos++)){
        if(strcmp(cv.GetIDFactura(),vv.GetIdFactura())==0){
            vv.Mostrar();
        }
    }

}

float getPrecioTotal(C_Ventas &cv){
    Ventas vv;
    int pos=0;
    float descTotal;
    float total=0;

    while(vv.LeerDisco(pos++)==1){
        if(strcmp(cv.GetIDFactura(),vv.GetIdFactura())==0){

               descTotal=((vv.GetPrecioU()*vv.Getdesc())/100)*vv.GetCant();
               total+=  vv.GetPrecioU()*vv.GetCant() - descTotal;

        }
    }
    return total;
}

int cantCVentas(){
    int cant=0, bytes=0;
    FILE *p;
    p = fopen(ARCH_C_VENTA,"rb");
    if(p==NULL) {
         fclose(p);
         return 0;

    }
    fseek(p,0,SEEK_END);
    bytes  =ftell(p);
    cant = bytes/sizeof (C_Ventas);
    fclose(p);
    return cant;
}


#endif // C_VENTAS_H
