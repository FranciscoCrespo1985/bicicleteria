#include <iostream>
#include<iostream>
#include<windows.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iomanip>

#include<Validar.h>
#include <Fecha.h>

#include <Persona.h>
#include <Producto.h>
#include <Proveedor.h>
#include <Cliente.h>

#include<Compras.h>>
#include<C_Compras.h>
#include<Ventas.h>
#include<C_Ventas.h>
#include<reportes.h>
#include<configuracion.h>




using namespace std;

// repo test

void menuManager();
void menuClientes(Validar&);
void menuProductos(Validar&);
void menuProveedor(Validar&);
void menuVentas(Validar&);
void menuCompras(Validar&);
void menuConfiguracion(Validar&);
void menuReportes(Validar &);
void setTeclado();






int main()
{
    /*
    char a[]="There are two needles in this haystack with needles.";
    char b[]="ere";

    string sa=a;


    if(sa.find(b)!=std::string::npos)
        cout<<"found"<<"in the pos "<< sa.find(b) <<endl;
    system("pause");

*/
    system("MODE CON COLS=100 LINES=40");
    validarIngreso();
    menuManager();

    return 0;
}




void menuManager(){

    int opcion;

    Validar v;
    while(1){
    v.header("Bicicleteria");


    cout<<" 1) Clientes"<<endl;
    cout<<" 2) Productos"<<endl;
    cout<<" 3) Proveedores"<<endl;
    cout<<" 4) Ventas"<<endl;
    cout<<" 5) Compras"<<endl;
    cout<<" 6) Reportes"<<endl;
    cout<<" 7) Configuracion"<<endl;
    cout<<" 0) Salir"<<endl<<endl;

    cout<<" INGRESE LA OPCION: ";
    cin>>opcion;
    cout<<" --------------------------------"<<endl;


    switch(opcion){
        case 1:
             menuClientes(v);
        break;
        case 2:
             menuProductos(v);
        break;
        case 3:
             menuProveedor(v);
        break;
        case 4:
             menuVentas(v);
        break;
        case 5:
             menuCompras(v);
             break;
        case 6:
             menuReportes(v);
        break;
        case 7:
            menuConfiguracion(v);
        break;
        case 0:
            return;
        break;
        }
    }
}


void menuConfiguracion(Validar &v){

    int opcion;

    while(1){
        v.header("Configuracion");


        cout<<" 1) Realizar BackUp"<<endl;
        cout<<" 2) Roll Back"<<endl;

        cout<<endl<<"Ingrese una opcion: \n";

        cin>>opcion;


        switch(opcion){
            case 1:
                backup();
            break;
            case 2:
                rollback();
            break;
            case 0:
            return;
            break;
        }

    }
}
void menuClientes(Validar &v){
    int opcion;
    while(true){
    v.header("Cliente");

    cout<<" 1) NUEVO CLIENTE"<<endl;
    cout<<" 2) MODIFICAR CLIENTE"<<endl;
    cout<<" 3) LISTAR CLIENTE POR CODIGO"<<endl;
    cout<<" 4) LISTAR TODOS LOS CLIENTES"<<endl;
    cout<<" 5) OTROS LISTADOS"<<endl;
    cout<<" 6) CONSULTAS" <<endl;
    cout<<" 7) ELIMINAR CLIENTE"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER AL MENU PRINCIPAL"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
              altaCliente();
              //cargarCliente();

          break;
          case 2:
                modCliente();
          break;
          case 3:
                 mostrarClientePorDNI();
          break;
          case 4:
                 listarClientes(0);
          break;
          case 5:
                clienteOtrosListados(v);
          break;
          case 6:
                clienteOtrasConsulta();
          break;
          case 7:
                 eliminarCliente();
          break;
          case 0:
              system("cls");
              return;
          break;
          }
          system("pause");
    }
}

void menuProveedor(Validar &v){
    int opcion;
    while(true){
    v.header("Proveedor");

    cout<<" 1) NUEVO PROVEEDOR"<<endl;
    cout<<" 2) MODIFICAR PROVEEDOR"<<endl;
    cout<<" 3) LISTAR PROVEEDOR POR CODIGO"<<endl;
    cout<<" 4) LISTAR TODOS LOS PROVEEDORES"<<endl;
    cout<<" 5) OTROS LISTADOS" <<endl;
    cout<<" 6) CONSULTAS"<<endl;
    cout<<" 7) ELIMINAR PROVEEDOR"<<endl;

    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER AL MENU PRINCIPAL"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
             altaProveedor();
          break;
          case 2:
             modificarProveedor();
          break;
          case 3:
             mostrarProveedorPorDNI();
          break;
          case 4:
             listarProveedores(0);
          break;
          case 5:
              proveedorOtrosListados();
          break;
          case 6:
              proveedorOtrasConsultas();
          break;
          case 7:
             eliminarProveedor();
          break;
          case 0:
              system("cls");
              return;
          break;
          }
          system("pause");
    }
}




void menuProductos(Validar &v){

    int opcion;
    while(true){
    v.header("PRODUCTO");

    cout<<" 1) NUEVO PRODUCTO"<<endl;
    cout<<" 2) MODIFICAR PRODUCTO"<<endl;
    cout<<" 3) LISTAR PRODUCTO POR CODIGO"<<endl;
    cout<<" 4) LISTAR TODOS LOS PRODUCTOS"<<endl;
    cout<<" 5) OTROS LISTADOS"<<endl;
    cout<<" 6) ELIMINAR PRODUCTO"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER AL MENU PRINCIPAL"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
              altaProducto();


          break;
          case 2:
                modProducto();
          break;
          case 3:
                listarProdPorID();
          break;
          case 4:
                listarProductos(0);
          break;
          case 5:
                 productoOtrosListados(v);
          break;

          case 6:
                 eliminarProducto();
          break;
          case 0:
              system("cls");
              return;
              break;
          }
          system("pause");
    }
}

void menuVentas(Validar &v){

    int opcion;
    while(true){
    v.header("VENTAS");

    cout<<" 1) NUEVA VENTA"<<endl;
    cout<<" 2) LISTAR VENTAS"<<endl;
    cout<<" 3) ELIMINAR VENTA"<<endl;
    cout<<" 4) OTROS LISTADOS"<<endl;
    cout<<" 5) OTRAS CONSULTAS"<<endl;

    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER AL MENU PRINCIPAL"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
              nuevaVenta();
          break;
          case 2:
              listarVentas(1);
          break;
          case 3:
                eliminarVenta();
          break;
          case 4:
              ventasOtrosListados();

          break;
          case 5:
              ventasOtrasConsultas();
          break;

          case 0:
              system("cls");
              return;
              break;
          }
          system("pause");
    }
}

void menuCompras(Validar &v){

    int opcion;
    while(true){
    v.header("COMPRAS");

    cout<<" 1) NUEVA COMPRA"<<endl;
    cout<<" 2) LISTAR COMPRAS"<<endl;
    cout<<" 3) ELIMINAR COMPRAS"<<endl;
    cout<<" 4) OTROS LISTADOS"<<endl;
    cout<<" 5) CONSULTAS"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER AL MENU PRINCIPAL"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
              nuevaCompra();
          break;
          case 2:
              listarCompras(1);
          break;
          case 3:
               eliminarCompras();
          break;
          case 4:
              comprasOtrosListados();

          break;
          case 5:
               comprasOtrasConsultas();
          break;
          case 0:
              system("cls");
              return;
              break;
          }
          system("pause");
    }
}

void menuReportes(Validar &v){

    int opcion;
    while(true){
    v.header("REPORTES");

    cout<<" 1) CLIENTE CON MAS COMPRAS "<<endl;
    cout<<" 2) PRODUCTOS MAS VENDIDOS"<<endl;
    cout<<" 3) INGRESOS POR MES"<<endl;
    cout<<" --------------------------------"<<endl;
    cout<<" 0) VOLVER AL MENU PRINCIPAL"<<endl<<endl;


    cout<<" INGRESE LA OPCION: ";
        cin>>opcion;
        switch (opcion){
          case 1:
                reporte1();


          break;
          case 2:
                reporte2();
          break;
          case 3:
                reporte3();
          break;
          case 4:

          break;
          case 5:

          break;
          case 0:
              system("cls");
              return;
              break;
          }
          system("pause");
    }
}




