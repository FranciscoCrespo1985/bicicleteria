#ifndef C_COMPRAS_H
#define C_COMPRAS_H
char * ARCH_C_COMPRAS="datos/c_compras.fjc";
struct fCompra{ int dia, mes, anio;};
class C_Compras
{
  private:
      char idRemito [7];
      char CUITProveedor [15];
      fCompra fPedido;
      fCompra fEntrega;
      int tipo_de_factura;
      int estado;
  public:
      char* GetRemito(){return idRemito;};
      char* GetCUITProveedor(){return CUITProveedor;};
      fCompra getFPedido(){return fPedido;};
      fCompra getFEntrega(){return fEntrega;};
      int GetTipoDeFactura(){return tipo_de_factura;};
      int GetEstado(){return estado;};

      void SetRemito(char idr[7]){strcpy(idRemito,idr);};
      void SetCUITProveedor(char cuit[15]){strcpy(CUITProveedor,cuit);};
      void SetFPedido(fCompra f){fPedido=f;};
      void SetFEntrega(fCompra f){fEntrega=f;};
      void SetTipoFactura(int t){tipo_de_factura=t;};
      void SetEstado(int e){estado=e;};

      void Cargar(int,Proveedor&);
      void Mostrar(Proveedor&,float);
      bool LeerDisco(int);
      void Guardar(int);
};

bool C_Compras::LeerDisco(int pos){
    bool leyo;
    FILE *p;
    p=fopen(ARCH_C_COMPRAS,"rb");
    if(p==NULL) exit(1);


    fseek(p,sizeof*this*pos,0);
    leyo = fread(this,sizeof*this,1,p);
    fclose(p);
    return leyo;
}

void C_Compras::Guardar(int pos){
    FILE *p;

    if(pos >=0){
        p = fopen(ARCH_C_COMPRAS,"rb+");
        if(p == NULL){
            exit(1);
        }
        fseek(p,pos*sizeof(C_Compras),0);
    } else {
        p = fopen(ARCH_C_COMPRAS,"ab");
        if(p==NULL){
            exit(1);
        }
    }
    fwrite(this,sizeof*this ,1,p);
    fclose(p);
}

void C_Compras::Mostrar(Proveedor &pro, float total){

    buscarPos(GetCUITProveedor(),pro);

        cout << fixed;
        cout << setprecision(2);

        cout << left << setw(10) << "N Remito";
        cout << left << setw(15) << "R. Social";
        cout << left << setw(15) << "CUIT";
        cout << left << setw(12) << "F. de Venta";
        cout << left << setw(12) << "F. de Entrega ";
        cout << left << setw(6) << "T. Fac ";
        cout << right << setw(10) << "Importe\n";

        cout << left << setw(10) << GetRemito();
        cout << left << setw(15) << pro.GetNombre();
        cout << left << setw(15) <<  pro.GetDni();
        cout << right <<setw(2)<<std::setfill('0') << fPedido.dia<<setw(1) <<"/"<<setw(2) <<fPedido.mes<<setw(1) <<"/"<<left<<setw(6)<<std::setfill(' ') <<fPedido.anio;
        cout << right <<setw(2) << fEntrega.dia<<setw(1) <<"/"<<setw(2) <<fEntrega.mes<<setw(1) <<"/"<<left<<setw(6) <<fEntrega.anio;
        cout << right << setw(8) <<std::setfill(' ')  <<GetTipoDeFactura();
        cout << right << setw(10) << total<<endl;




}

void C_Compras::Cargar(int nCompra,Proveedor & pro){

    Validar v;
    Fecha f;

    int correcto=0;
    char cuit[15];
    char id[7];
    int opc[]={1,2,3};
    int selTipo=0;
    this->fPedido.dia =  f.getDia();
    this->fPedido.mes = f.getMes();
    this->fPedido.anio = f.getAnio();


    snprintf(idRemito, 7, "%d", ++nCompra);

     while(!correcto){
        v.header("Alta Venta");
        listarProveedores(1);
        cout<<"Seleccione un Proveedor: \n";
        cin >> cuit;
        if(buscarPos(cuit,pro)!=-1){
            SetCUITProveedor(cuit);
            cout<< "El proveedor SELECCIONADO FUE:\n"<<pro.GetApellido()<<" Contacto:"<< pro.GetNombre()<<endl;
            cout<< "CONFIRMAR: 1: Correcto 0: Incorrecto: ";
            cin>>correcto;
        }
    }
    /// una ves que tengo el proveedor indicado se carga la entrega
     f+=pro.GetEntrega();
    this->fEntrega.dia=f.getDia();
    this->fEntrega.mes=f.getMes();
    this->fEntrega.anio=f.getAnio();

    cout<< "Seleciconar tipo de factura: \n1=A, 2=B, 3=C\n";
    while((selTipo=v.validarOpcion(opc,3))==-1)cout<< "Valor incorrecto\n Ingrese 1=A 2=C 3=C\n";
    SetTipoFactura(selTipo);
}


void nuevaCompra();
int cantCCompras();
float getPrecioTotal(C_Compras &);

void ordenadoPorFecha(C_Compras*,int,int);
void ordenadoPorDNI(C_Compras*,int);
void ordenadoPorMonto(C_Compras*,int);
void buscarFechaDeCompra();
void buscarImporteDeCompra();
void buscarTipoDeFacturaCompra();



void nuevaCompra(){
    Validar v;
    C_Compras cc;
    Compras nc;
    int pos=0;
    int comprar = 1;

    Proveedor pro;
    cc.Cargar(cantCCompras(),pro);
    cc.Mostrar(pro,getPrecioTotal(cc));
    /// creo los items de la factura
    while(comprar){
        altaCompra(cc.GetRemito(),pro);

        cout<<"Desea agregar otro item: 1-Si 0-No\n";
        cin >> comprar;
    }
    /// guardo la factura, los items ya fueron guardados
    if(pro.GetEntrega()==0){
         cc.SetEstado(1);
    }else{
         cc.SetEstado(3);
    }




    cc.Guardar(-1);

    /// Muestro la factura
    v.header("Remito");

    cc.Mostrar(pro, getPrecioTotal(cc));
    cout<<"\n\n";
    mostrarTituloVenta();
    while(nc.LeerDisco(pos++)){
        if(strcmp(cc.GetRemito(),nc.GetIdRemito())==0){
            nc.Mostrar();
        }
    }
}

float getPrecioTotal(C_Compras &cc){
    Compras nc;
    int pos=0;
    float descTotal;
    float total=0;

    while(nc.LeerDisco(pos++)==1){
        if(strcmp(cc.GetRemito(),nc.GetIdRemito())==0){
               descTotal=((nc.GetPUnitario()*nc.GetDesc())/100)*nc.GetCant();
               total+=  nc.GetPUnitario()*nc.GetCant() - descTotal;
        }
    }
    return total;
}

int cantCCompras(){
    int cant=0, bytes=0;
    FILE *p;
    p = fopen(ARCH_C_COMPRAS,"rb");
    if(p==NULL) {
         fclose(p);
         return 0;
    }

    fseek(p,0,SEEK_END);
    bytes  =ftell(p);
    cant = bytes/sizeof (C_Compras);
    fclose(p);
    return cant;
}


int buscarPos(char idRemito[7],C_Compras &cc){

    for(int i = 0; i<cantCCompras();i++){
            cc.LeerDisco(i);
            if(strcmp(cc.GetRemito(),idRemito)==0){
                return i;
            }
    }
    return -1;
}



void listarCompras(int opc){
    char selCompra[7];
    Validar v;int pos=-1;
    C_Compras cc;
    Proveedor pro;
    Compras nc;
    int cant = cantCCompras();

    for(int i =0; i< cant;i++){
        cc.LeerDisco(i);
        if(cc.GetEstado()>=1){
            cc.Mostrar(pro,getPrecioTotal(cc));
        }
    }

    cout<< "Elegir el Remito: ";
    v.validarString("N Remito",selCompra,7);
    v.header("REMITO");
    pos=buscarPos(selCompra,cc);
    cc.LeerDisco(pos);
    if(pos!=-1&&cc.GetEstado()){
        if(opc==1){
            cc.Mostrar(pro,getPrecioTotal(cc));
            cout<<endl;
            listarCompraPorRemito(selCompra);
        }else if(opc==0){
            cc.SetEstado(0);
            cc.Guardar(pos);
        }
    }


}

void eliminarCompras(){
    listarCompras(0);
}


void validarIngreso(){
    Fecha hoy;
    Fecha fentrega;
    int pos=0;
    int posProd;
    C_Compras cc;
    Compras nc;
    Proveedor pro;
    Producto p;
    int cant=0;
    cant= cantCCompras();
      for(int i =0; i< cant;i++){
        cc.LeerDisco(i);


        fentrega.setDia(cc.getFEntrega().dia);
        fentrega.setMes(cc.getFEntrega().mes);
        fentrega.setAnio(cc.getFEntrega().anio);

        if(cc.GetEstado()==3 && fentrega<=hoy){

            cc.Mostrar(pro,getPrecioTotal(cc));

            while(nc.LeerDisco(pos++))
                if(strcmp(cc.GetRemito(),nc.GetIdRemito())==0){
                    if(posProd=buscarPos(nc.GetIdProd(),p)!=-1){

                        p.Mostrar(1);
                        p.SetStock(p.GetStock()+nc.GetCant());
                        p.Mostrar(1);
                        p.Guardar(posProd);
                    }
                }
            cc.SetEstado(1);
            cc.Guardar(i);
            /// sumar cada venta de la factura a los productos
            cout<<"\nRemito Procesado";
        }
    }
    system("pause");
}

 void comprasOtrasConsultas(){
    int opcion;
    Validar v;

    while(true){
    v.header("Compras Consultas");

    cout<<" 1) CONSULTAR POR FECHA"<<endl;
    cout<<" 2) CONSULTAR POR IMPORTE"<<endl;
    cout<<" 3) CONSULTAR POR TIPO DE FACTURA"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A CLIENTES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
    cin>>opcion;
        switch (opcion){
          case 1:
                buscarFechaDeCompra();

          break;
          case 2:
                buscarImporteDeCompra();

          break;
          case 3:
                buscarTipoDeFacturaCompra();
          break;
          case 0:
            system("cls");
          return;
          break;
        }
    }


 }

 void buscarTipoDeFacturaCompra(){
    Validar v;
        Proveedor pro;
        C_Compras cc;
        bool found = false;
        int opc[]={1,2,3};
        int selTipo;
        int pos=0;

        cout<< "Seleciconar tipo de factura: \n1=A, 2=B, 3=C\n";
        while((selTipo=v.validarOpcion(opc,3))==-1)cout<< "Valor incorrecto\n Ingrese 1=A 2=C 3=C\n";

        while(cc.LeerDisco(pos++)){
            if(cc.GetTipoDeFactura()==selTipo){
                cc.Mostrar(pro,getPrecioTotal(cc));
                found=true;
            }
        }
        if(!found){
            cout<< "No se encontraron ventas con ese tipo de factura\n";
        }
         system("pause");
 }



 void buscarImporteDeCompra(){
        cout<<endl<<"Favor de Importe: ";
        Validar v;
        bool found=false;
        float importe,importeA=999999,dif;;
        importe = v.validarFloat(0,999999);
        C_Compras cc;
        Proveedor pro;
        int pos=0,pos2;
        float masCercano;




        while(cc.LeerDisco(pos)){
            dif=v.matDist(getPrecioTotal(cc),importe);
            if(dif!=0){
                    if(dif<importeA){
                        importeA=dif;
                        pos2=pos;
                     }
            }else{
                cc.Mostrar(pro,getPrecioTotal(cc));
                found=true;
                break;
            }
            pos++;
        }
        if(!found){
            cout <<"El importe mas cercano al ingresado esta en la factura: "<<endl;
            cc.LeerDisco(pos2);
            cc.Mostrar(pro,getPrecioTotal(cc));
        }
        system("pause");

 }



void buscarFechaDeCompra(){
    cout<<endl<<"Favor de ingresar fecha";
        bool found=false;
        C_Compras cc;
        Proveedor pro;
        int pos=0;


        Fecha fl,fi;
        Validar v;

        fi.CargarFecha();
        while(cc.LeerDisco(pos++)==1){
            fl.setAnio(cc.getFEntrega().anio);
            fl.setMes(cc.getFEntrega().mes);
            fl.setDia(cc.getFEntrega().dia);
            if(fl==fi){
                if(cc.GetEstado()>=1){
                    cc.Mostrar(pro,getPrecioTotal(cc));
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

void comprasOtrosListados(){
    Validar v;
    int cant = cantCCompras();
    cout<< cant;
    system("pause");
    C_Compras *cc;
    cc = new C_Compras[cant];
    for(int i=0;i<cant;i++){
            cc[i].LeerDisco(i);
    }

    int opcion;
    while(true){

    v.header("Compras Listados");

    cout<<" 1) ORDENADOS POR FECHA"<<endl;
    cout<<" 2) ORDENADOS POR FECHA DE ENTREGA"<<endl;
    cout<<" 3) ORDENADOS POR DNI"<<endl;
    cout<<" 4) ORDENADOS POR MONTO"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A PROVEEDORES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
                ordenadoPorFecha(cc,cant,1);
          break;
          case 2:
                ordenadoPorFecha(cc,cant,3);
          break;
          case 3:
                 ordenadoPorDNI(cc,cant);


          break;
          case 4:
                ordenadoPorMonto(cc,cant);
                break;
          case 0:
              system("cls");
              delete[] cc;
              return;

          break;
        }
    }
}

void ordenadoPorMonto(C_Compras *cc,int cant){
    Validar v;
    C_Compras aux;
    Proveedor pro;
    Fecha f,ff;


    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){
            if( getPrecioTotal(cc[j])<getPrecioTotal(cc[j+1])) {
                aux = cc[j];
                cc[j] = cc[j+1];
                cc[j+1] =aux;
            }
        }
    }
    v.header("COMPRAS POR MONTO");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(12)<<"N REMITO"<<setw(20)<<"NOMBRE"<<setw(15)<<"DNI"<<setw(15)<<"F.Pedido"<<setw(12)<<right<<"IMPORTE"<<endl;

    for (int i=0; i<cant;i++){
        if(cc[i].GetEstado()>=1){
            buscarPos(cc[i].GetCUITProveedor(),pro);
            cout << fixed;
            cout << setprecision(2);
            cout <<left<<setw(12)<<cc[i].GetRemito()<<setw(20)<<pro.GetNombre()<<setw(15)<<pro.GetDni()<<cc[i].getFPedido().dia<<"/"<<cc[i].getFPedido().mes<<"/"<<cc[i].getFPedido().anio<<setw(3)<<" "<<right<<setw(15)<<getPrecioTotal(cc[i])<<endl;
        }
    }
    cout << endl;
    system("pause");


}


void ordenadoPorDNI(C_Compras *cc,int cant){
    Validar v;
    C_Compras aux;
    Proveedor pro;
    Fecha f,ff;
    char fechade[15];

    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){


            if( atol(cc[j].GetCUITProveedor())>atol(cc[j+1].GetCUITProveedor()) ){
                aux = cc[j];
                cc[j] = cc[j+1];
                cc[j+1] =aux;
            }
        }
    }
    v.header("COMPRAS POR CUIT");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(12)<<"N REMITO"<<setw(20)<<"NOMBRE"<<setw(15)<<"DNI"<<setw(15)<<"F.Pedido"<<right<<setw(12)<<"IMPORTE"<<endl;

    for (int i=0; i<cant;i++){
        if(cc[i].GetEstado()==1){
            buscarPos(cc[i].GetCUITProveedor(),pro);
            cout << fixed;
            cout << setprecision(2);
            cout <<left<<setw(12)<<cc[i].GetRemito()<<setw(20)<<pro.GetNombre()<<setw(15)<<pro.GetDni()<<cc[i].getFPedido().dia<<"/"<<cc[i].getFPedido().mes<<"/"<<cc[i].getFPedido().anio<<setw(3)<<" "<<right<<setw(15)<<getPrecioTotal(cc[i])<<endl;
        }
    }
    cout << endl;
    system("pause");


}

void ordenadoPorFecha(C_Compras *cc,int cant,int opc){
    Validar v;
    C_Compras aux;
    Proveedor pro;
    Fecha f,ff;
    char fechade[15];


    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){
            if(opc==1){
            strcpy(fechade,"F. DE VENTA");
            f.setAnio(cc[j].getFEntrega().anio);
            f.setMes(cc[j].getFEntrega().mes);
            f.setDia(cc[j].getFEntrega().dia);

            ff.setAnio(cc[j+1].getFEntrega().anio);
            ff.setMes(cc[j+1].getFEntrega().mes);
            ff.setDia(cc[j+1].getFEntrega().dia);
            } else if(opc==3){
                strcpy(fechade,"F. DE ENTREGA");
                f.setAnio(cc[j].getFPedido().anio);
                f.setMes(cc[j].getFPedido().mes);
                f.setDia(cc[j].getFPedido().dia);

                ff.setAnio(cc[j+1].getFPedido().anio);
                ff.setMes(cc[j+1].getFPedido().mes);
                ff.setDia(cc[j+1].getFPedido().dia);

            }

            if(f<ff){
                aux = cc[j];
                cc[j] = cc[j+1];
                cc[j+1] =aux;
            }

        }
    }


    v.header("COMPRAS POR FECHA");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(12)<<"N REMITO"<<setw(20)<<"NOMBRE"<<setw(15)<<"DNI"<<setw(15)<<fechade<<right<<setw(12)<<"IMPORTE"<<endl;

    for (int i=0; i<cant;i++){
        if(cc[i].GetEstado()>=opc){
            buscarPos(cc[i].GetCUITProveedor(),pro);
            cout << fixed;
            cout << setprecision(2);
            if(opc==1)cout <<left<<setw(12)<<cc[i].GetRemito()<<setw(20)<<pro.GetNombre()<<setw(15)<<pro.GetDni()<<cc[i].getFPedido().dia<<"/"<<cc[i].getFPedido().mes<<"/"<<cc[i].getFPedido().anio<<setw(3)<<" "<<right<<setw(15)<<getPrecioTotal(cc[i])<<endl;
            if(opc==3)cout <<left<<setw(12)<<cc[i].GetRemito()<<setw(20)<<pro.GetNombre()<<setw(15)<<pro.GetDni()<<cc[i].getFEntrega().dia<<"/"<<cc[i].getFEntrega().mes<<"/"<<cc[i].getFEntrega().anio<<setw(3)<<" "<<right<<setw(15)<<getPrecioTotal(cc[i])<<endl;
        }
    }
    cout << endl;
    system("pause");



}







#endif // C_COMPRAS_H
