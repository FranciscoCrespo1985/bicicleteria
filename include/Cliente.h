#ifndef CLIENTE_H
#define CLIENTE_H





const char ARCH_CLIENTE[]="datos/cliente.fjc";





struct antiguedad{ int dia, mes, anio;};

class Cliente :public Persona
{
    private:
        antiguedad anti;

    public:

        void SetAntiguedad(antiguedad a){anti=a;};
        antiguedad GetAntiguedad(){return anti;};



        void Cargar();
        void Mostrar(int);
        bool LeerDisco(int);
        void Guardar(int);


};


void Cliente::Mostrar(int opc){

    if(opc==0){

        cout<<"DNI: "<<dni<<endl;
        cout<<"Nombre: "<<nombre<<endl;
        cout<<"Apellido: "<<apellido<<endl;
        cout<<"Telefono: "<<telefono<<endl;
        cout<<"EMAIL: "<<email<<endl;
        cout<<"Fecha incripta: \n"<<anti.dia<<"/"<<anti.mes<<"/"<<anti.anio<<endl;

        cout<<endl;
    } else{

        cout<<right<<setw(15)<<dni<< setw(20)<<nombre<<setw(20)<<apellido<<endl;

    }
}

void Cliente::Cargar(){
    Validar v;
    Fecha f;
    anti.anio=f.getAnio();
    anti.dia=f.getDia();
    anti.mes=f.getMes();
    v.header("Alta Cliente");

    v.validarString("Nombre ",nombre,20);
    v.validarString("Apellido",apellido,20);
    v.validarString("Telefono",telefono,15);
    v.validarString("Email",email,40);



}

void Cliente::Guardar(int pos){
     FILE *p;

    if(pos >=0){
        p = fopen("datos/cliente.fjc","rb+");
        if(p == NULL){
            exit(1);
        }
        fseek(p,pos*sizeof(Cliente),0);
    } else {
        p = fopen("datos/cliente.fjc","ab");
        if(p==NULL){
            exit(1);
        }
    }
    fwrite(this,sizeof *this ,1,p);
    fclose(p);

}

bool Cliente::LeerDisco(int pos){
    bool leyo;
    FILE *p;
    p=fopen(ARCH_CLIENTE,"rb");
    if(p==NULL) exit(1);


    fseek(p,sizeof*this*pos,0);
    leyo = fread(this,sizeof*this,1,p);
    fclose(p);
    return leyo;
}


/////////////////////////////////////////////////////////
///////          Funciones helper                                 ////////////
///////////////////////////////////////////////////////
void altaCliente();
int buscarPos(char[15],Cliente&);
int buscarEliminado(char[15],Cliente&);
int cantClientes();

void listarClientes(int opc);

void mostrarClientePorDNI();



void modCliente();
int mostrarOpcionCliente();
void modCampo(int,Cliente &,int,Validar &,Fecha &);
void eliminarCliente();
void clienteOtrosListados();
void ordenadoPorApellido(Cliente *,int);
void ordenadoPorAntiguedad(Cliente *,int);
void ordenadoPorEmail(Cliente *,int);
void eliminarCliente(){
    Validar v;
    Cliente c;
    char dni[15];
    int pos;
    v.header("Eliminar Cliente");
    listarClientes(1);


    v.validarString("DNI",dni,15);
    pos = buscarPos(dni,c);
    if(pos!=-1){
        c.SetEstado(0);
        c.Guardar(pos);
        v.header("Cliente Eliminado");
        c.Mostrar(1);

    }
}


void modCliente(){

    Cliente c;
    Validar v;
    Fecha f;
    int pos;
    int opc;
    listarClientes(1);
    char dni[15];
    v.validarString("DNI ",dni,15);
    pos=buscarPos(dni,c);

    if(pos!=-1){
        c.LeerDisco(pos);
        v.header("Mod Cliente");
        c.Mostrar(0);
        while(opc=mostrarOpcionCliente()){
            v.header("Mod Cliente");
            modCampo(opc,c,pos,v,f);
            c.Mostrar(0);
        }
    }

}

void modCampo(int opc,Cliente &c,int pos,Validar &v,Fecha &f){

    switch(opc){
        case 1:/// dni

               char dni[15];
                v.validarString("DNI ",dni,15);
                if(buscarPos(dni,c)==-1){
                    c.LeerDisco(pos);

                    strcpy(c.GetDni(),dni);
                    c.Guardar(pos);
                }else{
                    cout<<"Ya existe ese dni";
                }


            break;
        case 2:///nombre
            v.validarString("Nombre",c.GetNombre(),20);
            c.Guardar(pos);
            break;
        case 3:///apellido
            v.validarString("Apellido",c.GetApellido(),20);
            c.Guardar(pos);
            break;
        case 4:///telefono
                v.validarString("Telefono",c.GetTelefono(),15);
                c.Guardar(pos);
            break;
        case 5:///email
            v.validarString("Email",c.GetEmail(),40);
            c.Guardar(pos);
            break;
        case 6:///antiguedad

            antiguedad anti;
            f.CargarFecha();

            anti.anio = f.getAnio();
            anti.mes=f.getMes();
            anti.dia=f.getDia();

            c.SetAntiguedad(anti);
            c.Guardar(pos);
            break;
        case 0:
            break;
    }
}


int mostrarOpcionCliente(){

    int opc;
    cout <<"\nElija una opcion\n";
    cout<<"1- DNI\n";
    cout<<"2- Nombre\n";
    cout<<"3- Apellido\n";
    cout<<"4- Telefono\n";
    cout<<"5- Email\n";
    cout<<"6- Antiguedad\n";

    cout<<"0- SALIR\n";
    cout<<"\n";
    cin >> opc;
    return opc;


}





void altaCliente(){

    Cliente c;
    Validar v;
    v.header("Nuevo Cliente");
    char dni[15];
    v.validarString("DNI ",dni,15);


    if(buscarPos(dni,c)==-1 && buscarEliminado(dni,c)==-1){
        strcpy(c.GetDni(),dni);
        c.Cargar();
        c.Guardar(-1);
    }
}
void mostrarClientePorDNI(){

    Validar v;
    Cliente c;
    char dni[15];

    listarClientes(1);
    cout<<endl;
    v.validarString("DNI: ",dni,15);
    cout<<endl;
    if(buscarPos(dni,c)!=-1){
        c.Mostrar(0);
    }

}

int buscarEliminado(char dni[15],Cliente &c){
    for(int i = 0; i<cantClientes();i++){
            c.LeerDisco(i);
            if(strcmp(c.GetDni(),dni)==0&& !c.GetEstado()){
                return i;
            }
    }
    return -1;

}
int buscarPos(char dni[15],Cliente &c){

    for(int i = 0; i<cantClientes();i++){
            c.LeerDisco(i);
            if(strcmp(c.GetDni(),dni)==0&&c.GetEstado()){
                return i;
            }
    }
    return -1;
}

int buscarPos(char dni[15]){
    Cliente c;
    for(int i = 0; i<cantClientes();i++){
            c.LeerDisco(i);
            if(strcmp(c.GetDni(),dni)==0&&c.GetEstado()){
                return i;
            }
    }
    return -1;
}
void listarClientes(int opc){

    Validar v;
    v.header("Lista Clientes");
    cout<<right<<setw(15)<<"DNI:"<<setw(20)<<"NOMBRE:"<<setw(20)<<"APELLIDO:"<<endl;
    Cliente c;
    int cant = cantClientes();
    for(int i =0; i< cant;i++){

        c.LeerDisco(i);
        if(c.GetEstado()){
            c.Mostrar(opc);
        }
    }
}




int cantClientes(){
    int cant=0, bytes=0;
    FILE *p;
    p = fopen(ARCH_CLIENTE,"rb");
    if(p==NULL) {
         fclose(p);
         return 0;

    }
    fseek(p,0,SEEK_END);
    bytes  =ftell(p);
    cant = bytes/sizeof (Cliente);
    fclose(p);
    return cant;

}

void buscarString(int opcion){
                int pos=0;
                string s;

                bool found;
                char ingreso [40];
                Validar v;
                Cliente c;
                FILE *p;
                p = fopen(ARCH_CLIENTE,"rb");
                if(p==NULL)exit(1);

                switch(opcion){
                    case 1:
                        v.validarString("Apellido",ingreso,20);
                         found=false;
                        while(c.LeerDisco(pos++)==1){
                            if(strcmp(ingreso,c.GetApellido())==0){
                                if(c.GetEstado()==1){
                                    c.Mostrar(0);
                                    found=true;
                                }
                            }
                        }
                        if(!found){
                            pos=0;
                             while(c.LeerDisco(pos++)==1){
                                s=c.GetApellido();
                                if(s.find(ingreso)!=std::string::npos){
                                    if(c.GetEstado()==1){
                                        c.Mostrar(0);
                                    }
                                }
                            }
                        }
                        break;
                    case 2:
                        v.validarString("Nombre",ingreso,20);
                        found=false;
                        while(c.LeerDisco(pos++)==1){
                            if(strcmp(ingreso,c.GetNombre())==0){
                                if(c.GetEstado()==1){
                                    c.Mostrar(0);
                                    found=true;
                                }
                            }
                        }

                        if(!found){
                            pos=0;
                             while(c.LeerDisco(pos++)==1){
                                s=c.GetNombre();
                                if(s.find(ingreso)!=std::string::npos){
                                    if(c.GetEstado()==1){
                                        c.Mostrar(0);
                                    }
                                }
                            }
                        }


                        break;
                    case 3:
                        v.validarString("EMAIL",ingreso,20);
                        found=false;
                        while(c.LeerDisco(pos++)==1){
                            if(strcmp(ingreso,c.GetEmail())==0){
                                if(c.GetEstado()==1){
                                    c.Mostrar(0);
                                    found=true;
                                }
                            }
                        }

                         if(!found){
                            pos=0;
                             while(c.LeerDisco(pos++)==1){
                                s=c.GetEmail();
                                if(s.find(ingreso)!=std::string::npos){
                                    if(c.GetEstado()==1){
                                        c.Mostrar(0);
                                    }
                                }
                            }
                        }


                        break;
                }



                if(!found){
                    cout<<ingreso<<": "<<"Cliente inexistente"<<endl;
                }
                fclose(p);
                system("pause");
}


void clienteOtrasConsulta(){
    int opcion;
    Validar v;

    while(true){
    v.header("Cliente Consultas");

    cout<<" 1) CONSULTAR POR APELLIDO"<<endl;
    cout<<" 2) CONSULTAR POR NOMBRE"<<endl;
    cout<<" 3) CONSULTAR POR EMAIL"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A CLIENTES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
    cin>>opcion;
        switch (opcion){
          case 1:
                buscarString(opcion);

          break;
          case 2:
                buscarString(opcion);

          break;
          case 3:
                buscarString(opcion);
          break;
          case 0:
            system("cls");


          return;

          break;
        }
    }
}
void clienteOtrosListados(Validar &v){
    int cant = cantClientes();
    Cliente *c;
    c = new Cliente[cant ];
    for(int i=0;i<cant;i++){
            c[i].LeerDisco(i);
    }


    int opcion;
    while(true){
    v.header("Cliente Listados");

    cout<<" 1) ORDENADOS POR APELLIDO"<<endl;
    cout<<" 2) ORDENADOS POR ANTIGUEDAD"<<endl;
    cout<<" 3) ORDENADOS POR EMAIL"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER A CLIENTES"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:

                ordenadoPorApellido(c,cant);

          break;
          case 2:

                ordenadoPorAntiguedad(c,cant);

          break;
          case 3:

                ordenadoPorEmail(c,cant);
          break;
          case 0:
              system("cls");
              delete [] c;
              return;

          break;
        }




    }
}

void ordenadoPorEmail(Cliente *c,int cant){
    Validar v;
    Cliente aux;


    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){
            if(strcmp(c[j].GetEmail(),c[j+1].GetEmail())>0){
                aux = c[j];
                c[j] = c[j+1];
                c[j+1] =aux;
            }
        }
    }
    v.header("CLIENTE POR EMAIL");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(20)<<"Apellido"<<setw(15)<<"DNI"<<setw(40)<<"EMAIL"<<endl;

    for (int i=0; i<cant;i++){
        if(c[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<c[i].GetApellido()<<setw(15)<<c[i].GetDni()<<setw(40)<<c[i].GetEmail()<<endl;
        }
    }
    cout << endl;
    system("pause");


}
void ordenadoPorAntiguedad(Cliente *c,int cant){
    Validar v;
    Cliente aux;
    Fecha f,ff;

    for (int i=0; i<cant-1; i++){
        for(int j=0; j<cant-i-1; j++){

            f.setAnio(c[j].GetAntiguedad().anio);
            f.setMes(c[j].GetAntiguedad().mes);
            f.setDia(c[j].GetAntiguedad().dia);

            ff.setAnio(c[j+1].GetAntiguedad().anio);
            ff.setMes(c[j+1].GetAntiguedad().mes);
            ff.setDia(c[j+1].GetAntiguedad().dia);

            if(f<ff){
                aux = c[j];
                c[j] = c[j+1];
                c[j+1] =aux;
            }

        }
    }


    v.header("CLIENTE POR ANTIGUEDAD");
    cout<<endl<<endl;
    cout << fixed;
    cout << setprecision(2);
    cout <<left<< setw(12)<<"Fecha"<<setw(20)<<"Apellido"<<setw(20)<<"Nombre"<<setw(15)<<"DNI"<<setw(15)<<"Telefono"<<endl;

    for (int i=0; i<cant;i++){
        if(c[i].GetEstado()==1){

            cout << fixed;
            cout << setprecision(2);
            cout <<left<<c[i].GetAntiguedad().dia<<"/"<<c[i].GetAntiguedad().mes<<"/"<<c[i].GetAntiguedad().anio<<setw(3)<<" "<< setw(20)<<c[i].GetApellido()<<setw(20)<<c[i].GetNombre()<<setw(15)<<c[i].GetDni()<<setw(15)<<c[i].GetTelefono()<<endl;

        }
    }
    cout << endl;
    system("pause");




}
void ordenadoPorApellido(Cliente *c,int cant){
    Validar v;
    Cliente aux;



  for (int i=0; i<cant-1; i++){
    for(int j=0; j<cant-i-1; j++){
        if(strcmp(c[j].GetApellido(),c[j+1].GetApellido())>0){
                aux = c[j];
                c[j] = c[j+1];
                c[j+1] = aux;
        }
    }
}
v.header("CLIENTE POR APELLIDO");
cout<<endl<<endl;
cout << fixed;
cout << setprecision(2);
cout <<left<< setw(20)<<"Apellido"<<setw(20)<<"Nombre"<<setw(15)<<"DNI"<<setw(15)<<"Telefono"<<endl;

    for (int i=0; i<cant;i++){
        if(c[i].GetEstado()==1){
            cout << fixed;
            cout << setprecision(2);
            cout <<left<< setw(20)<<c[i].GetApellido()<<setw(20)<<c[i].GetNombre()<<setw(15)<<c[i].GetDni()<<setw(15)<<c[i].GetTelefono()<<endl;
        }
    }
    cout << endl;
    system("pause");

}




#endif // CLIENTE_H
