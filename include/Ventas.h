#ifndef VENTAS_H
#define VENTAS_H
char * ARCH_VENTA="datos/venta.fjc";

class Ventas
{
    private:
        char idFactura[7];
        char idProd[7];
        float precioU;
        int cant;
        float desc;

    public:
        char* GetIdFactura(){return idFactura;};
        char* GetIDProd(){return idProd;};
        float GetPrecioU(){return precioU;};
        int GetCant(){return cant;};
        float Getdesc(){return desc;};

        void SetIDFactura(char *idf){strcpy(idFactura,idf);};
        void SetIDProd(char *idp){strcpy(idProd,idp);};
        void SetPrecioU(float pu){precioU = pu;};
        void SetCant(int cant){this->cant=cant;};
        void SetDesc(float desc){this->desc=desc;};

        void Cargar(char*,float);
        int Mostrar();
        int LeerDisco(int);
        void Guardar(int);
};

void Ventas::Guardar(int pos){
    FILE *p;

    if(pos >=0){
        p = fopen(ARCH_VENTA,"rb+");
        if(p == NULL){
            exit(1);
        }
        fseek(p,pos*sizeof(Ventas),0);
    } else {
        p = fopen(ARCH_VENTA,"ab");
        if(p==NULL){
            exit(1);
        }
    }
    fwrite(this,sizeof*this ,1,p);
    fclose(p);
}
int Ventas::LeerDisco(int pos){
    bool leyo;
    FILE *p;
    p=fopen(ARCH_VENTA,"rb");
    if(p==NULL){ return 0;};
    fseek(p,sizeof*this*pos,0);
    leyo = fread(this,sizeof*this,1,p);
    fclose(p);
    return leyo;
}
int Ventas::Mostrar(){

        Producto p;
        float descTotal=0;
        p.LeerDisco(buscarPos(GetIDProd(),p));

        descTotal=((GetPrecioU()*Getdesc())/100)*GetCant();


        cout << fixed;
        cout << setprecision(2);

        cout << left << setw(10) << GetIdFactura();
        cout << left << setw(10) << GetIDProd();
        cout << left << setw(20) << p.GetNombre();
        cout << right << setw(10) << GetCant();
        cout << right << setw(10) << GetPrecioU();
        cout << right << setw(10) << Getdesc();
        cout << right << setw(10) << descTotal;
        cout << right << setw(10) << (GetPrecioU()*GetCant()) - descTotal;
        cout<<endl;
}


void Ventas::Cargar(char * nFactura,float desc){
    Validar v;

    Producto p;
    char id[7];
    v.header("VENTA");
    listarProductos(1);

    cout<<"Seleccionar producto: ";
    v.validarString("ID",id,7);

    while(buscarPos(id,p)==-1){
        cout<<"Producto inexistente vuelva a ingresar el id;"<<endl;
        v.validarString("ID",id,7);
    }

    p.Mostrar(1);
    SetIDProd(p.GetID());
    SetIDFactura(nFactura);
    SetDesc(desc);
    SetPrecioU(p.GetPrecioU());

    cout<<"Ingrese la cantidad que desea vender: ";
    SetCant(v.validarInt(1,p.GetStock()));


}

float altaVenta(char[7] ,Cliente&);
float calcDesc(Cliente&);
void mostrarTituloCompra();
void listarVentasPorFactura(char [7]);







void listarVentasPorFactura(char idFactura[7]){
    Ventas vv;


    int pos=0;

     while(vv.LeerDisco(pos++)){
        if(strcmp(idFactura,vv.GetIdFactura())==0){
            vv.Mostrar();
        }
    }
}

float altaVenta(char nFactura[7] ,Cliente& c){
    Producto p;
    int pos;
    Ventas v;
    float pTotal;
    int cant;
    int confirmar=0;
    float desc=0;
    desc=calcDesc(c);

    v.Cargar(nFactura,desc);

    mostrarTituloVenta();

    v.Mostrar();

    pos = buscarPos(v.GetIDProd(),p); ///pista para compras, p se envia como referencia por lo que se carga en este momento
    cant = p.GetStock() - v.GetCant();
    p.SetStock(cant);
    cout<<"Confirmar compra 1-SI 0-NO \n";
    cin>>confirmar;
    if(confirmar==1){
        v.Guardar(-1);
        p.Guardar(pos);

        return pTotal;
    }
    return 0;

}

void mostrarTituloCompra(){
        cout << fixed;
        cout << setprecision(2);

        cout << left << setw(10) << "N Factura";
        cout << left << setw(10) << "P Id";
        cout << left << setw(10) << "P Nombre";
        cout << left << setw(10) << "P Cant";
        cout << right << setw(10) << "Precio U";
        cout << right << setw(10) << "Desc U";
        cout << right << setw(10) << "D Total";
        cout << right << setw(10) << "Total";
        cout<<endl;
}
float calcDesc(Cliente &c ){
    Fecha factual;
    Fecha fingreso;
    antiguedad a;
    float descuento=0;
    a=c.GetAntiguedad();


    fingreso.setDia(a.dia);
    fingreso.setMes(a.mes);
    fingreso.setAnio(a.anio);

    descuento =(float) ((factual-fingreso)/365)*1.5;
    if(descuento>20) return 20;
    if(descuento<=0) return 0;
    return descuento;
}
int cantVentas(){
    int cant=0, bytes=0;
    FILE *p;
    p = fopen(ARCH_VENTA,"rb");
    if(p==NULL) {
         fclose(p);
         return 0;

    }
    fseek(p,0,SEEK_END);
    bytes  =ftell(p);
    cant = bytes/sizeof (Ventas);
    fclose(p);
    return cant;
}



#endif // VENTAS_H
