#ifndef VALIDAR_H
#define VALIDAR_H

using namespace std;
class Validar
{
    public:

        void header(char *);
        float validarFloat(float,float);
        int validarInt(int,int);
        char validarSexo();
        int validarOpcion(int *,int );
        void validarString(char*,char* ,int);
        float matDist(float n1,float n2);
};




void Validar::header(char * t){
   system("cls");

    for(int i =0;i < (int)strlen(t)+8;i++){
        cout<<"-";
    }
    cout <<endl<<"--- "<<t<<" ---"<<endl;

    for(int i =0;i < strlen(t)+8;i++){
        cout<<"-";
    }
    cout<<"\n\n";

}
float Validar::matDist(float n1,float n2){
    if(n1==n2)return 0;
    if(n1<n2){
        return n2-n1;
    }else{
        return n1-n2;
    }
}

float Validar::validarFloat(float minimo,float maximo){

    float n2 = 0;
    cin>>n2;
    while(n2>maximo || n2<minimo){
        cout << "El numero debe ser menor que "<<maximo<< " y mayor que "<<minimo<<"\n";
        cout << "Vuelva a ingresar el numero: ";
        cin>>n2;

    }
    return n2;
}

int Validar::validarInt(int minimo,int maximo){
    int n2;
    cin>>n2;
    while(n2>maximo || n2<minimo){
        cout << "El numero debe ser menor que "<<maximo<< "y mayor que "<<minimo<<"\n";
        cout << "vuelva a ingresar el numero: ";
        cin>>n2;

    }
    return n2;

}

char Validar::validarSexo(){
            char s;
            cout<<"Ingrese su Sexo: "<<endl;
            cout<<"Opciones F=femenino M=Masculino X=Otro: " ;
            fflush (stdin);
            s=getchar();

            while(s!='x' && s!='f'  && s!='m'  ){
                cout<<"El campo Sexo no puede quedar vacio y debe ser F,M o X: ";
                fflush (stdin);
                s=getchar();
                fflush(stdout);
                cout<<endl;
                }
            return s;


}
int Validar::validarOpcion(int * opc,int sice){
    int ingreso;
    cin >>ingreso;
    for(int i = 0; i<sice;i++){
        if(ingreso == opc[i])
            return ingreso;
    }
    return -1;
}
void Validar::validarString(char* nString,char* vChar,int lon ){

            cout<<"Ingrese su "<<nString<< ": ";
            fflush (stdin);

            gets(vChar);


            while(strlen(vChar)<1||strlen(vChar)>=lon){
                cout<<"El campo "<<nString<<" no puede quedar vacio \n y debe ser de menos de: "<<lon <<" caracteres: ";

				gets(vChar);


                }
}

#endif // VALIDAR_H
