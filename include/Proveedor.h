#ifndef PROVEEDOR_H
#define PROVEEDOR_H

const char ARCH_PROVEEDOR[]="datos/proveedor.fjc";

class Proveedor:public Persona{
    private:
            char dir[40];
            float desc;
            int entrega;
            bool tarjeta;
            int estado;
    public:
            char* GetDir(){return dir;};
            float GetDesc(){return desc;};
            int GetEntrega(){return entrega;};
            bool GETtarjeta(){return tarjeta;};
            int Getestado(){return estado;};

            void SetDir(char *d){strcpy(dir,d);};
            void SetDesc(float d){desc=d;};
            void SetEntrega(int d){entrega=d;};
            void SetTarjeta(bool d){tarjeta=d;};
            void SetEstado(int d){estado=d;};

            void Cargar();
            void Mostrar(int);
            bool LeerDisco(int);
            void Guardar(int);
};

void Proveedor::Cargar(){
    Validar v;
    v.header("Alta Proveedor");
    v.validarString("Nombre de la empresa",nombre,20);
    v.validarString("Nombre del contacto",apellido,20);
    v.validarString("Telefono",telefono,15);
    v.validarString("Email",email,40);
    v.validarString("Direccion",this->dir,40);
    cout<<"Ingrese el descuento ofrecido por el proveedor: ";

    desc = v.validarFloat(0,40);
    cout<<"Ingrese demora del proveedor\nValor maximo 365: ";
    entrega = v.validarFloat(0,365);

    tarjeta = 1;
    estado = 1;
}
void Proveedor::Mostrar(int opc){
  if(opc==0){
        cout<<"CUIT: "<<dni<<endl;
        cout<<"Empresa: "<<nombre<<endl;
        cout<<"Contacto: "<<apellido<<endl;
        cout<<"Telefono: "<<telefono<<endl;
        cout<<"Direccion: "<<dir<<endl;
        cout<<"Descuento: "<<desc<<endl;
        cout<<"Tarjeta: "<<tarjeta<<endl;
        cout<<"Demora: "<<entrega<<endl;
        cout<<"EMAIL: "<<email<<endl;
        cout<<endl;
    } else{

        cout<<"CUIT: "<<dni<< "    "<<  "Empresa: "<<nombre<<endl;

    }
}
bool Proveedor::LeerDisco(int pos){
    bool leyo;
    FILE *p;
    p=fopen(ARCH_PROVEEDOR,"rb");

    if(p==NULL) exit(1);
    fseek(p,sizeof*this*pos,0);
    leyo=fread(this,sizeof*this,1,p);
    fclose(p);
    return leyo;
}
void Proveedor::Guardar(int pos){
         FILE *p;

    if(pos >=0){
        p = fopen(ARCH_PROVEEDOR,"rb+");
        if(p == NULL){
            exit(1);
        }
        fseek(p,pos*sizeof(Proveedor),0);
    } else {
        p = fopen(ARCH_PROVEEDOR,"ab");
        if(p==NULL){
            exit(1);
        }
    }
    fwrite(this,sizeof *this ,1,p);
    fclose(p);
}


/////////////////////////////////////////////////////////
///////          Funciones helper                                 ////////////
///////////////////////////////////////////////////////

/// Funciones para  Alta
void altaProveedor();
int buscarPos(char[15],Proveedor&);
int buscarEliminado(char[15],Proveedor&);
int cantProveedores();

/// Listado de proveedores
void listarProveedores(int);
void mostrarProveedorPorDNI();

/// Modificar campo
void modificarProveedor();
void modCampo(int ,Proveedor &,int ,Validar &);
int mostrarOpcionProveedor();
/// Eliminar proveedor
void eliminarProveedor();
/// LISTADOS Y CONSULTAS
     void ordenadoPorNombre(Proveedor *,int);
    void ordenadoPorDesc(Proveedor *,int);
    void ordenadoPorFPago(Proveedor *,int);
    void ordenadoPorCUIT(Proveedor*,int);
    void buscarStringProveedor(int);
void modificarProveedor(){
    Proveedor pro;
    Validar v;
    int pos;
    int opc;

    listarProveedores(1);
    char cuit[15];
    v.validarString("CUIT ",cuit,15);
    pos=buscarPos(cuit,pro);

    if(pos!=-1){
        pro.LeerDisco(pos);
        v.header("Mod Producto");
        pro.Mostrar(0);
        while(opc=mostrarOpcionProveedor()){
            modCampo(opc,pro,pos,v);
        }
    }
}

void modCampo(int opc,Proveedor &pro,int pos ,Validar &v){
    int opcion[]={1,2};
    int tipo=-1;
    switch(opc){
        case 1:/// id
               char cuit[15];
                v.validarString("CUIT",cuit,15);
                if(buscarPos(cuit,pro)==-1){
                    pro.LeerDisco(pos);

                    strcpy(pro.GetDni(),cuit);
                    pro.Guardar(pos);
                }else{
                    cout<<"Ya existe ese cuit";
                }
            break;
        case 2:///nombreEmpresa
            v.validarString("Nombre de la Empresa",pro.GetNombre(),25);
            pro.Guardar(pos);
            break;
        case 3:///nombreContacto
            v.validarString("Descripcion",pro.GetApellido(),25);
            pro.Guardar(pos);
            break;
        case 4:///telefono
                v.validarString("Telefono",pro.GetTelefono(),15);
                pro.Guardar(pos);
                break;
        case 5:///Direccion
                v.validarString("Direccion",pro.GetDir(),40);
                pro.Guardar(pos);
                break;
        case 6:///Descuento
            cout<<"Ingrese el descuento ofrecido por el proveedor: ";
            pro.SetDesc(v.validarFloat(0,40));
            pro.Guardar(pos);
            break;
        case 7: ///tarjeta
            cout<<"Acepta tarjeta \n 1 - Si 2 - No\n";
            tipo=v.validarInt(0,3);
            if(tipo==1){
                pro.SetTarjeta(true);
            }else if(tipo==2)
            {
                pro.SetTarjeta(false);
            }
             pro.Guardar(pos);
            break;

        case 8:
            cout<<" Ingrese la nueva demora: ";
            tipo=v.validarInt(0,365);
            pro.SetEntrega(tipo);
            break;
        case 9:
            cout<<"Ingrese el nuevo email:  ";
            v.validarString("EMail",pro.GetEmail(),40);
            pro.Guardar(pos);
    }

}

int mostrarOpcionProveedor(){

    int opc;
    cout <<"\nElija una opcion\n";
    cout<<"1- CUIT\n";
    cout<<"2- Nombre Proveedor\n";
    cout<<"3- Nombre Contacto\n";
    cout<<"4- Telefono\n";
    cout<<"5- Direccion\n";
    cout<<"6- Descuento\n";
    cout<<"7- Tarjeta\n";
    cout<<"8- Demora\n";
    cout<<"9- EMAIL\n";

    cout<<"0- SALIR\n";
    cout<<"\n";
    cin >> opc;
    return opc;
}

void mostrarProveedorPorDNI(){
    Validar v;
    Proveedor pro;
    char cuit[15];

    listarProveedores(1);
    v.validarString("CUIT:",cuit,15);
    if(buscarPos(cuit,pro)!=-1){
        pro.Mostrar(0);
    }
}

void listarProveedores(int opc){
    Proveedor pro;
    int cant = cantProveedores();
    for(int i = 0; i<cant;i++){
        pro.LeerDisco(i);
        if(pro.GetEstado()){
            pro.Mostrar(opc);
        }
    }
}



void altaProveedor(){
    Proveedor pro;
    Validar v;
    v.header("Nuevo proveedor");
    char cuit[15];

    v.validarString("CUIT",cuit,15);

    if(buscarPos(cuit,pro)==-1&&buscarEliminado(cuit,pro)==-1){
            strcpy(pro.GetDni(),cuit);
            pro.Cargar();

            pro.Guardar(-1);
            cout << "DATOS GUARDADOS\n"<< endl;
            pro.Mostrar(0);
    }

}


int buscarEliminado(char cuit[15],Proveedor &pro){
     for(int i = 0; i<cantProveedores();i++){
            pro.LeerDisco(i);
            if(strcmp(pro.GetDni(),cuit)==0&& !pro.GetEstado()){
                return i;
            }
    }
    return -1;
}

int buscarPos(char cuit[15],Proveedor &pro){
    for(int i = 0; i< cantProveedores();i++){
        pro.LeerDisco(i);
        if(strcmp(pro.GetDni(),cuit)==0&&pro.GetEstado()){
            return i;
        }
    }
    return -1;
}

int cantProveedores(){
    int cant=0,bytes=0;
    FILE *p;
    p = fopen(ARCH_PROVEEDOR,"rb");
    if(p==NULL){
        fclose(p);
        return 0; ///esta bien
    }
    fseek(p,0,SEEK_END);
    bytes = ftell(p);
    cant= bytes /sizeof(Proveedor);
    fclose(p);
    return cant;
}

void eliminarProveedor(){
    Validar v;
    Proveedor pro;
    char cuit[15];
    int pos;
    v.header("Eliminar Proveedor");
    listarProductos(1);

    v.validarString("CUIT",cuit,15);
    pos = buscarPos(cuit,pro);
    if(pos!=-1){
        pro.SetEstado(0);
        pro.Guardar(pos);
    }

}


void proveedorOtrosListados(){
    Validar v;
    int cant = cantProveedores();
    Proveedor *pro;
    pro = new Proveedor[cant];
                for(int i=0;i<cant;i++){
                        pro[i].LeerDisco(i);
                }


    int opcion;
    while(true){

    v.header("Proveedor Listados");

    cout<<" 1) ORDENADOS POR NOMBRE"<<endl;
    cout<<" 2) ORDENADOS POR DESCUENTO"<<endl;
    cout<<" 3) ORDENADOS POR FORMA DE PAGO"<<endl;
    cout<<" 4) ORDENADOS POR CUIT"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A PROVEEDORES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:

                ordenadoPorNombre(pro,cant);
          break;
          case 2:
                ordenadoPorDesc(pro,cant);
          break;
          case 3:
                 ordenadoPorFPago(pro,cant);
          break;
          case 4:
                  ordenadoPorCUIT(pro,cant);
          break;
          case 0:
              system("cls");
              delete[] pro;
              return;

          break;
        }




    }
}

void proveedorOtrasConsultas(){
    int opcion;
    Validar v;

    while(true){
    v.header("Proveedor Consultas");

    cout<<" 1) CONSULTAR POR NOMBRE"<<endl;
    cout<<" 2) CONSULTAR POR EMAIL"<<endl;
    cout<<" 3) CONSULTAR POR DIRECCION"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A PROVEEDOR"<<endl<<endl;

    cout<<" INGRESE LA OPCION: ";
    cin>>opcion;
        switch (opcion){
          case 1:
                buscarStringProveedor(opcion);
          break;
          case 2:
                buscarStringProveedor(opcion);
          break;
          case 3:
                buscarStringProveedor(opcion);
          break;
          case 0:
            system("cls");
          return;
          break;
        }
    }
}

void buscarStringProveedor(int opcion){
                int pos=0;
                bool found;
                char ingreso [40];
                Validar v;
                Proveedor pro;
                FILE *p;
                p = fopen(ARCH_PROVEEDOR,"rb");
                if(p==NULL)exit(1);

                switch(opcion){
                    case 1:
                        pos=0;
                        v.validarString("Nombre",ingreso,20);
                        found=false;
                        while(pro.LeerDisco(pos++)==1){
                            if(strcmp(ingreso,pro.GetNombre())==0){
                                if(pro.GetEstado()==1){
                                    pro.Mostrar(0);
                                    found=true;
                                }
                            }
                        }
                        break;
                    case 2:
                        v.validarString("EMAIL",ingreso,40);
                        found=false;
                        while(pro.LeerDisco(pos++)==1){
                            if(strcmp(ingreso,pro.GetEmail())==0){
                                if(pro.GetEstado()==1){
                                    pro.Mostrar(0);
                                    found=true;
                                }
                            }
                        }
                        break;
                    case 3:
                        v.validarString("Direccion",ingreso,40);
                        found=false;
                        while(pro.LeerDisco(pos++)==1){
                            if(strcmp(ingreso,pro.GetDir())==0){
                                if(pro.GetEstado()==1){
                                    pro.Mostrar(0);
                                    found=true;
                                }
                            }
                        }
                        break;
                }
                if(!found){
                    cout<<ingreso<<": "<<"Proveedor inexistente"<<endl;
                }
                fclose(p);
                system("pause");



}


void ordenadoPorCUIT(Proveedor * pro , int cant){
     Validar v;
    Proveedor aux;

  for (int i=0; i<cant-1; i++)
    {
        for(int j=0; j<cant-i-1; j++)
        {
            if(strcmp(pro[j].GetDni(),pro[j+1].GetDni())>0)
            {
                    aux = pro[j];
                    pro[j] = pro[j+1];
                    pro[j+1] = aux;
            }
        }
    }
v.header("PROVEEDOR POR CUIT");
cout<<endl<<endl;
cout << fixed;
cout << setprecision(2);
cout <<left<< setw(20)<<"Nombre"<<setw(15)<<"CUIT"<<setw(20)<<"Contacto"<<setw(15)<<"Desc"<<setw(15)<<"Telefono"<<setw(7)<<"F.Pago"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(pro[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<pro[i].GetNombre()<<setw(15)<<pro[i].GetDni()<<setw(20)<<pro[i].GetApellido()<<setw(15)<<pro[i].GetDesc()<<setw(15)<<pro[i].GetTelefono();
            if(pro[i].GETtarjeta()==1){
                    cout << setw(7)<<"VISA";
            }else{
                    cout << setw(7)<<"EFECT";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");




}


void ordenadoPorFPago(Proveedor * pro,int cant){
     Validar v;
    Proveedor aux;

  for (int i=0; i<cant-1; i++)
    {
        for(int j=0; j<cant-i-1; j++)
        {
            if(pro[j].GETtarjeta()<pro[j+1].GETtarjeta())
            {
                    aux = pro[j];
                    pro[j] = pro[j+1];
                    pro[j+1] = aux;
            }
        }
    }
v.header("PROVEEDOR POR FORMA DE PAGO");
cout<<endl<<endl;
cout << fixed;
cout << setprecision(2);
cout <<left<< setw(20)<<"Nombre"<<setw(15)<<"CUIT"<<setw(20)<<"Contacto"<<setw(15)<<"Desc"<<setw(15)<<"Telefono"<<setw(7)<<"F.Pago"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(pro[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<pro[i].GetNombre()<<setw(15)<<pro[i].GetDni()<<setw(20)<<pro[i].GetApellido()<<setw(15)<<pro[i].GetDesc()<<setw(15)<<pro[i].GetTelefono();
            if(pro[i].GETtarjeta()==1){
                    cout << setw(7)<<"VISA";
            }else{
                    cout << setw(7)<<"EFECT";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");




}
void ordenadoPorNombre(Proveedor *pro,int cant){
    Validar v;
    Proveedor aux;

  for (int i=0; i<cant-1; i++)
    {
        for(int j=0; j<cant-i-1; j++)
        {
            if(strcmp(pro[j].GetNombre(),pro[j+1].GetNombre())>0)
            {
                    aux = pro[j];
                    pro[j] = pro[j+1];
                    pro[j+1] = aux;
            }
        }
    }
v.header("PROVEEDOR POR RAZON SOCIAL");
cout<<endl<<endl;
cout << fixed;
cout << setprecision(2);
cout <<left<< setw(20)<<"Nombre"<<setw(15)<<"CUIT"<<setw(20)<<"Contacto"<<setw(15)<<"Desc"<<setw(15)<<"Telefono"<<setw(7)<<"F.Pago"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(pro[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<pro[i].GetNombre()<<setw(15)<<pro[i].GetDni()<<setw(20)<<pro[i].GetApellido()<<setw(15)<<pro[i].GetDesc()<<setw(15)<<pro[i].GetTelefono();
            if(pro[i].GETtarjeta()==1){
                    cout << setw(7)<<"VISA";
            }else{
                    cout << setw(7)<<"EFECT";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");



}

void ordenadoPorDesc(Proveedor *pro,int cant){
    Validar v;
    Proveedor aux;

  for (int i=0; i<cant-1; i++)
    {
        for(int j=0; j<cant-i-1; j++)
        {
            if(pro[j].GetDesc()<pro[j+1].GetDesc())
            {
                    aux = pro[j];
                    pro[j] = pro[j+1];
                    pro[j+1] = aux;
            }
        }
    }
v.header("PROVEEDOR POR DESCUENTO");
cout<<endl<<endl;
cout << fixed;
cout << setprecision(2);
cout <<left<< setw(20)<<"Nombre"<<setw(15)<<"CUIT"<<setw(20)<<"Contacto"<<setw(15)<<"Desc"<<setw(15)<<"Telefono"<<setw(7)<<"F.Pago"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(pro[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<pro[i].GetNombre()<<setw(15)<<pro[i].GetDni()<<setw(20)<<pro[i].GetApellido()<<setw(15)<<pro[i].GetDesc()<<setw(15)<<pro[i].GetTelefono();
            if(pro[i].GETtarjeta()==1){
                    cout << setw(7)<<"VISA";
            }else{
                    cout << setw(7)<<"EFECT";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");
}
#endif // PROVEEDOR_H
