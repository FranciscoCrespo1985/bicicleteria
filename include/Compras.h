#ifndef COMPRAS_H
#define COMPRAS_H

char * ARCH_COMPRAS="datos/compras.fjc";

class Compras
{
    private:
       char idRemito[7];
       char idProd[7];
       float pUnitario;
       int cant;
       float desc;

    public:
        char * GetIdRemito(){return idRemito;};
        char * GetIdProd(){return idProd;};
        float GetPUnitario(){return pUnitario;};
        int GetCant(){return cant;};
        float GetDesc(){return desc;};

        void SetIdRemito(char i[7]){strcpy(idRemito,i);};
        void SetIdProd(char i[7]){strcpy(idProd,i);};
        void SetPUnitario(float pu){pUnitario=pu;};
        int SetCant(int c){cant=c;};
        float SetDesc(float descc){desc=descc;};

        void Cargar(char*,float);
        int Mostrar();
        int LeerDisco(int);
        void Guardar(int);
};


void Compras::Guardar(int pos){
    FILE *p;

    if(pos >=0){
        p = fopen(ARCH_COMPRAS,"rb+");
        if(p == NULL){
            exit(1);
        }
        fseek(p,pos*sizeof(Compras),0);
    } else {
        p = fopen(ARCH_COMPRAS,"ab");
        if(p==NULL){
            exit(1);
        }
    }
    fwrite(this,sizeof*this ,1,p);
    fclose(p);
}

int Compras::Mostrar(){
        Producto p;
        float descTotal=0;
        p.LeerDisco(buscarPos(GetIdProd(),p));

        descTotal=((GetPUnitario()*GetDesc())/100)*GetCant();


        cout << fixed;
        cout << setprecision(2);

        cout << left << setw(10) << GetIdRemito();
        cout << left << setw(10) << GetIdProd();
        cout << left << setw(20) << p.GetNombre();
        cout << left<< setw(10) << GetCant();
        cout << right << setw(10) << GetPUnitario();
        cout << right << setw(10) << GetDesc();
        cout << right << setw(10) << descTotal;
        cout << right << setw(10) << GetPUnitario()*GetCant() - descTotal;
        cout<<endl;

}


int Compras::LeerDisco(int pos){

    bool leyo;
    FILE *p;
    p=fopen(ARCH_COMPRAS,"rb");
    if(p==NULL){ return 0;};
    fseek(p,sizeof*this*pos,0);
    leyo = fread(this,sizeof*this,1,p);
    fclose(p);
    return leyo;



}

void Compras::Cargar(char * nRemito , float desc){
    Validar v;

    Producto p;
    char id[7];
    v.header("Compra");
    listarProductos(1);

    cout<<"Seleccionar producto: ";
    v.validarString("ID",id,7);

    while(buscarPos(id,p)==-1){
        cout<<"Producto inexistente vuelva a ingresar el id;"<<endl;
        v.validarString("ID",id,7);
    }

    p.Mostrar(1);
    SetIdProd(p.GetID());
    SetIdRemito(nRemito);
    SetDesc(desc);
    SetPUnitario(p.GetPrecioU());

    cout<<"Ingrese la cantidad que desea comprar: ";
    SetCant(v.validarInt(1,1000));


}



////////////////////////////
///////////////////////////
/////////////////////////
float altaCompra(char[7],Proveedor &pro);
void mostrarTituloVenta();
float altaCompra(char idRemito[7],Proveedor &pro){
    Producto p;
    int pos;
    Compras nc;
    float pTotal;
    int cant;
    int confirmar=0;
    float desc=pro.GetDesc();

    nc.Cargar(idRemito,desc);

    mostrarTituloVenta();

    nc.Mostrar();




    cout<<"Confirmar compra 1-SI 0-NO asdfasdf\n";


    cin>>confirmar;
    system("pause");
    if(confirmar==1){
        nc.Guardar(-1);
        if(pro.GetEntrega()==0)     {
        pos = buscarPos(nc.GetIdProd(),p);
        cant = p.GetStock() + nc.GetCant();
        p.SetStock(cant);
        p.Guardar(pos);
    }
        return pTotal;
    }
    return 0;
}

void mostrarTituloVenta(){
        cout << fixed;
        cout << setprecision(2);

        cout << left << setw(10) << "N Remito";
        cout << left << setw(10) << "P Id";
        cout << left << setw(20) << "P Nombre";
        cout << left << setw(10) << "P Cant";
        cout << right << setw(10) << "Precio U";
        cout << right << setw(10) << "Desc U";
        cout << right << setw(10) << "D Total";
        cout << right << setw(10) << "Total";
        cout<<endl;
}

void listarCompraPorRemito(char idRemito[7]){
    Compras nc;


    int pos=0;

     while(nc.LeerDisco(pos++)){
        if(strcmp(idRemito,nc.GetIdRemito())==0){
            nc.Mostrar();

        }
    }
}

#endif // COMPRAS_H
