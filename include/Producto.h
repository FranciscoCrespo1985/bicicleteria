#ifndef PRODUCTO_H
#define PRODUCTO_H
const char ARCH_PRODUCTO[]="datos/producto.fjc";

class Producto
{
    private:
        char id[7];
        char nombre[25];
        char descripcion[250];
        float precioU=0;
        int stock ,tipo, estado=1;
    public:
        char* GetID(){return id;};
        char* GetNombre(){return nombre;};
        char* GetDescripcion(){return descripcion;};
        float GetPrecioU(){return precioU;};
        int GetStock(){return stock;};
        int GetTipo(){return tipo;};
        int GetEstado(){return estado;};

        void SetID(char *id){strcpy(this->id,id);};
        void SetNombre(char *nombre){strcpy(this->nombre,nombre);};
        void SetDescripcion(char *descripcion){strcpy(this->descripcion,descripcion);};
        void SetPrecioU(float precioU){this->precioU=precioU;};
        void SetStock(int stock){this->stock=stock;};
        void SetTipo(int tipo){this->tipo=tipo;};
        void SetEstado(int estado){this->estado=estado;};

        void Cargar();
        void Mostrar(int);
        bool LeerDisco(int);
        void Guardar(int);
};


void Producto::Cargar(){
    Validar v;
    int opcion[]={1,2};
    v.header("Alta Producto");



    v.validarString("Nombre ",nombre,25);
    v.validarString("Descripcion",descripcion,250);

    cout<<"Ingrese el precio: ";
    precioU = v.validarFloat(0,150000);
    cout<<"Ingrese el Stock: ";
    stock = v.validarInt(0,10000);
    cout<<"Ingrese el tipo de produccto\n 1 - Repuesto 2 - Item\n";
    while((tipo = v.validarOpcion(opcion,2))==-1)cout << "Valor incorreto: ";
    cout<< "Valor aceptado\n";
    SetEstado(1);
    cout << GetEstado()<<"\n";

}
void Producto::Mostrar(int opc){
  if(opc==0){
        cout<<"ID: "<<id<<endl;
        cout<<"Nombre: "<<nombre<<endl;
        cout<<"Descripcion: "<<descripcion<<endl;
        cout<<"Precio Unitario: "<<precioU<<endl;
        cout<<"Stock: "<<stock<<endl;
        if(tipo==2){
            cout<<"Tipo: ITEM\n";
        }else{
            cout<<"Tipo: REPUESTO \n";
        }
        cout<<endl;
    } else{

        cout<<"ID: "<<id<< "    "<<  "Nombre: "<<nombre<<" Precio Unitario: "<<precioU<<" Stock: "<<stock<<endl;

    }
}

bool Producto::LeerDisco(int pos){
    bool leyo;
    FILE *p;
    p=fopen(ARCH_PRODUCTO,"rb");
    if(p==NULL) exit(1);

    fseek(p,sizeof*this*pos,0);
    leyo = fread(this,sizeof*this,1,p);
    fclose(p);
    return leyo;

}
void Producto::Guardar(int pos){
    FILE *p;

    if(pos >=0){
        p = fopen(ARCH_PRODUCTO,"rb+");
        if(p == NULL){
            exit(1);
        }
        fseek(p,pos*sizeof(Producto),0);
    } else {
        p = fopen(ARCH_PRODUCTO,"ab");
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


void altaProducto();
int buscarPos(char[7] ,Producto &);
int buscarEliminado(char* ,Producto &);
int cantProductos();

void listarProductos(int opc);
void listarProdPorID();

void modProducto();
int mostrarOpcionProducto();
void modCampo(int ,Producto &,int ,Validar &);
void eliminarProducto();

void productoOtrosListados(Validar &);
void productoOtrasConsultas(Validar &);
void ordenadoPorNombre(Producto *,int);
void ordenadoPorStock(Producto*,int);
void ordenadoPorPrecio(Producto*,int);
void ordenadoPorTipoNombre(Producto*,int);

void productoOtrosListados(Validar &v){

    int cant = cantProductos();
    Producto *p;
    p = new Producto[cant];
    for(int i=0;i<cant;i++){
            p[i].LeerDisco(i);
    }


    int opcion;
    while(true){
    v.header("Producto Listados");

    cout<<" 1) ORDENADOS POR NOMBRE"<<endl;
    cout<<" 2) ORDENADOS POR STOCK"<<endl;
    cout<<" 3) ORDENADOS POR PRECIO"<<endl;
    cout<<" 4) ORDENADOS POR TIPO Y NOMBRE"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A CLIENTES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:

                ordenadoPorNombre(p,cant);

          break;
          case 2:

                ordenadoPorStock(p,cant);

          break;
          case 3:

                ordenadoPorPrecio(p,cant);

          break;
          case 4:

                 ordenadoPorTipoNombre(p,cant);

                break;
          case 0:
              system("cls");
              delete [] p;
              return;

          break;
        }
    }
}

void ordenadoPorTipoNombre(Producto *p,int cant){
    Validar v;
    Producto aux;
    for (int i=0; i<cant-1; i++){
        for(int j=1; j<cant-i-1; j++){

            if(p[j].GetTipo()>p[j+1].GetTipo()){
                aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
            }else if(p[j].GetTipo()==p[j+1].GetTipo()&& strcmp(p[j].GetNombre(),p[j+1].GetNombre() )>0 ){
                aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
            }
        }
    }
    v.header("PRODUCTO POR TIPO Y NOMBRE");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(20)<<"Nombre"<<setw(10)<<"ID"<<setw(15)<<"Precio"<<setw(7)<<"Stock"<<setw(7)<<"Tipo"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(p[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<p[i].GetNombre()<<setw(10)<<p[i].GetID()<<setw(15)<<p[i].GetPrecioU()<<setw(7)<<p[i].GetStock();
            if(p[i].GetTipo()==1){
                    cout << setw(7)<<"REP";
            }else{
                    cout << setw(7)<<"ITEM";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");

}
void ordenadoPorPrecio(Producto *p,int cant){
    Validar v;
    Producto aux;
    for (int i=0; i<cant-1; i++){
        for(int j=1; j<cant-i-1; j++){
            if(p[j].GetPrecioU()>p[j+1].GetPrecioU()){
                aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
            }
        }
    }
    v.header("PRODUCTO POR PRECIO");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(20)<<"Nombre"<<setw(10)<<"ID"<<setw(15)<<"Precio"<<setw(7)<<"Stock"<<setw(7)<<"Tipo"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(p[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<p[i].GetNombre()<<setw(10)<<p[i].GetID()<<setw(15)<<p[i].GetPrecioU()<<setw(7)<<p[i].GetStock();
            if(p[i].GetTipo()==1){
                    cout << setw(7)<<"REP";
            }else{
                    cout << setw(7)<<"ITEM";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");

}

void ordenadoPorStock(Producto *p, int cant){
    Validar v;
    Producto aux;
    for (int i=0; i<cant-1; i++){
        for(int j=1; j<cant-i-1; j++){
            if(p[j].GetStock()>p[j+1].GetStock()){
                aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
            }
        }
    }
    v.header("PRODUCTO POR STOCK");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(20)<<"Nombre"<<setw(10)<<"ID"<<setw(15)<<"Precio"<<setw(7)<<"Stock"<<setw(7)<<"Tipo"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(p[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<p[i].GetNombre()<<setw(10)<<p[i].GetID()<<setw(15)<<p[i].GetPrecioU()<<setw(7)<<p[i].GetStock();
            if(p[i].GetTipo()==1){
                    cout << setw(7)<<"REP";
            }else{
                    cout << setw(7)<<"ITEM";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");

}

void ordenadoPorNombre(Producto *p,int cant){
    Validar v;
    Producto aux;

  for (int i=0; i<cant-1; i++){
    for(int j=1; j<cant-i-1; j++){
        if(strcmp(p[j].GetNombre(),p[j+1].GetNombre())>0){
                aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
        }
    }
}
v.header("PRODUCTO POR NOMBRE");
cout<<endl<<endl;
cout << fixed;
cout << setprecision(2);
cout <<left<< setw(20)<<"Nombre"<<setw(10)<<"ID"<<setw(15)<<"Precio"<<setw(7)<<"Stock"<<setw(7)<<"Tipo"<<endl<<endl;

    for (int i=0; i<cant;i++){
        if(p[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<p[i].GetNombre()<<setw(10)<<p[i].GetID()<<setw(15)<<p[i].GetPrecioU()<<setw(7)<<p[i].GetStock();
            if(p[i].GetTipo()==1){
                    cout << setw(7)<<"REP";
            }else{
                    cout << setw(7)<<"ITEM";
            }
            cout<<endl;
        }
    }
    cout << endl;
    system("pause");
}

void modCampo(int opc,Producto &p,int pos,Validar &v){
    int opcion[]={1,2};
    int tipo=-1;
    switch(opc){
        case 1:/// id

               char id[7];
                v.validarString("ID",id,7);
                if(buscarPos(id,p)==-1){
                    p.LeerDisco(pos);

                    strcpy(p.GetID(),id);
                    p.Guardar(pos);
                }else{
                    cout<<"Ya existe ese id";
                }
            break;
        case 2:///nombre
            v.validarString("Nombre",p.GetNombre(),25);
            p.Guardar(pos);
            break;
        case 3:///DESC
            v.validarString("Descripcion",p.GetDescripcion(),250);
            p.Guardar(pos);
            break;
        case 4:///PrecioUnitario
                cout<<"Ingrese el nuevo precio: ";
                p.SetPrecioU(v.validarFloat(0,150000));
                p.Guardar(pos);
            break;
        case 5:///Stock
                cout<<"Ingrese el nuevo Stock: ";
                p.SetStock(v.validarFloat(0,10000));
                p.Guardar(pos);
            break;
        case 6:///antiguedad
            cout<<"Ingrese nuevo tipo de produccto\n 1 - Repuesto 2 - Item\n";
            while((tipo=v.validarOpcion(opcion,2))==-1)cout << "Valor incorreto: ";
            p.SetTipo(tipo);
            p.Guardar(pos);
            break;
        case 0:
            break;
    }
}

void modProducto(){

    Producto p;
    Validar v;
    int pos;
    int opc;

    listarProductos(1);
    char id[7];
    v.validarString("ID ",id,7);
    pos=buscarPos(id,p);

    if(pos!=-1){
        p.LeerDisco(pos);
        v.header("Mod Producto");
        p.Mostrar(0);
        while(opc=mostrarOpcionProducto()){
            modCampo(opc,p,pos,v);
        }
    }
}

int mostrarOpcionProducto(){

    int opc;
    cout <<"\nElija una opcion\n";
    cout<<"1- ID\n";
    cout<<"2- Nombre\n";
    cout<<"3- Descripcion\n";
    cout<<"4- Precio Unitario\n";
    cout<<"5- Stock\n";
    cout<<"6- Tipo\n";

    cout<<"0- SALIR\n";
    cout<<"\n";
    cin >> opc;
    return opc;
}

void listarProductos(int opc){
    Producto p;
    int cant = cantProductos();

    for(int i=0; i < cant;i++){
            p.LeerDisco(i);
            if(p.GetEstado()==1){
                p.Mostrar(opc);
            }
    }
}

void listarProdPorID(){
    Validar v;
    Producto p;
    char id[7];

    listarProductos(1);
    v.validarString("ID",id,7);
    if(buscarPos(id,p)!=-1){
        p.Mostrar(0);
    }
}







void altaProducto(){
    Producto p;
    Validar v;
    v.header("Nuevo Producto");
    char id[7];
    v.validarString("ID ",id,7);


    if(buscarPos(id,p)==-1 && buscarEliminado(id,p)==-1){
        strcpy(p.GetID(),id);
        p.Cargar();
        p.Mostrar(0);

        p.Guardar(-1);
    }
}






int buscarPos(char id[7],Producto &p){

    for(int i = 0; i<cantProductos();i++){
            p.LeerDisco(i);
            if(strcmp(p.GetID(),id)==0&&p.GetEstado()){
                return i;
            }
    }
    return -1;
}

int buscarEliminado(char id[7],Producto &p){
    for(int i = 0; i<cantProductos();i++){
            p.LeerDisco(i);
            if(strcmp(p.GetID(),id)==0&& p.GetEstado()==0){
                return i;
            }
    }
    return -1;
}

int cantProductos(){
    int cant=0, bytes=0;
    FILE *p;
    p = fopen(ARCH_PRODUCTO,"rb");
    if(p==NULL) {
         fclose(p);
         return 0;

    }
    fseek(p,0,SEEK_END);
    bytes  =ftell(p);
    cant = bytes/sizeof (Producto);
    fclose(p);
    return cant;
}

void eliminarProducto(){
    Validar v;
    Producto p;
    char id[7];
    int pos;
    v.header("Eliminar Producto");
    listarProductos(1);

    v.validarString("ID",id,7);
    pos = buscarPos(id,p);
    if(pos!=-1){
        p.SetEstado(0);
        p.Guardar(pos);
    }
}




#endif // PRODUCTO_H
