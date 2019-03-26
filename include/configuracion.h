
#ifndef ABML_H_INCLUDED
#define ABML_H_INCLUDED

#include <iomanip>
using namespace std;


void backup(){


    system("copy datos\\cliente.fjc             datos\\bck\\cliente.bck" );
    system("copy datos\\producto.fjc         datos\\bck\\producto.bck" );
    system("copy datos\\c_venta.fjc          datos\\bck\\c_venta.bck" );
    system("copy datos\\venta.fjc              datos\\bck\\venta.bck" );
    system("copy datos\\compras.fjc        datos\\bck\\compras.bck" );
    system("copy datos\\c_compras.fjc    datos\\bck\\c_compras.bck" );
    system("copy datos\\proveedor.fjc     datos\\bck\\proveedor.bck" );
    system("pause");
}

void rollback(){
    cout<<"ALERTA!!!! ESTA A PUNTO DE SOBREESCRIBIR ARCHIVOS \n";
    cout<<"ESTA SEGURO DE QUE DESEA SOBREESCRIBIR LAS BASE DE DATOS: \nCLIENTE \nCHOFER \nVIAJE\n";
    system("pause");
    cout<<"ESCRIBA YES, NO :";
    char * respuesta;

    cin>> respuesta;
    if(strcmp(respuesta,"YES")==0){
        system("copy datos\\bck\\cliente.bck  datos\\cliente.fjc" );
        system("copy datos\\bck\\producto.bck  datos\\producto.fjc" );
        system("copy datos\\bck\\venta.bck  datos\\venta.fjc" );
        system("copy datos\\bck\\c_venta.bck  datos\\c_venta.fjc" );
        system("copy datos\\bck\\compras.bck  datos\\compras.fjc" );
        system("copy datos\\bck\\c_compras.bck  datos\\c_compras.fjc" );
        system("copy datos\\bck\\proveedor.bck datos\\proveedor.fjc" );
    } else{
        cout << "NO SE HAN SOBREESCRITO LOS ARCHIVOS\n\n";
    }
    system("pause");

}

#endif
