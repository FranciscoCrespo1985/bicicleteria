#ifndef FECHA_H
#define FECHA_H


#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;
///////////////CLASE FECHA
//Puede utilizarse para fechas desde el 01/01/1900

class Fecha
{
  private:
    int dia;
    int mes;
    int anio;
    bool esbisiesto(int);
    void NumeroSerieaFecha(int);
  public:
    void validarFecha();
    Fecha(int d=0,int m=0,int a=0);
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}
    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;};
    void setAnio(int a){anio=a;};


    void CargarFecha();
    void MostrarFecha();
    void MostrarFechaTexto();
    int NumeroSerie();
    bool operator >(Fecha &);
    bool operator <(Fecha &);
    bool operator<=(Fecha &);
    bool operator ==(Fecha &);
    Fecha operator+(int);
    int operator /(int a){return 2;};
    int operator -(Fecha &);
    void operator +=(int);
    friend istream & operator>>(istream &, Fecha &);
    friend ostream & operator<<(ostream &, Fecha &);
};


void Fecha::CargarFecha(){

    cout << "Dia: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    validarFecha();
}



Fecha::Fecha(int d,int m,int a)
{//El constructor asigna los valores recibidos, si le son pasados como par�metros


  if(d!=0)
  {
  dia=d;mes=m;anio=a;
  validarFecha();//�Qu� modificaci�n habr�a que hacerle al constructor para
  }                   // garantizar que no se asignen valores absurdos? Ej.:65/65/-12
  else  //si no recibe valores asigna por defecto la fecha actual
  {
    time_t tiempo;
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    anio=tmPtr->tm_year+1900;
    mes=tmPtr->tm_mon+1;
    dia=tmPtr->tm_mday;
  }
}




void Fecha::validarFecha(){
    int diasXMes[]={31,28,31,30,31,30,31,31,30,31,30,31};

    bool biciesto=false;
        while(anio<1900){
            cout << "Los anios deben ser superiores a 1900"<<endl;
            cout << "Anio: ";
            fflush(stdin);
            cin >> anio;
            cout<<endl;
        }
        // me fijo si el a�o es biciesto
        if(anio % 4 == 0 && anio % 100 != 0 || anio % 400 ==0) biciesto=true;

        //cheque que los meses sean del  al 12
        while(mes>12 || mes<1){
            cout << "Los meses solo tienen 12 meses y son mayores que 0:"<<endl;
            cout << "Mes: ";
            fflush(stdin);
            cin >> mes;
            cout<<endl;

        }
        //chequeo que el dia sea menor que el dia maximo del mes con anio biciesto
         while(mes==2 && (biciesto) && (dia >29||dia<1)){
            cout<<"biciesto";
            cout << "El dia debe ser menor que 29 :"<< dia <<"y mayor que 0"<<endl;
            cout << "Dia: "<< dia;
            fflush(stdin);
            cin >> dia;
            cout<<endl;
        }

        //chequeo que el dia sea menor que el dia maximo del mes
        while((dia <1 ||dia > diasXMes[mes-1])&&(!biciesto)){
            if(mes >0){
                cout << "El dia debe ser menos que "<<diasXMes[mes-1]<< " y mayor que 0 :"<<endl;
            }else{
                cout << "El me es incorrecto "<<diasXMes[mes-1]<< " y mayor que 0 :"<<endl;
            }
            cout << "Dia: ";
            fflush(stdin);
            cin >> dia;
            cout<<endl;
        }

}
//Devuelve true si el a�o recibido es bisiesto.
bool Fecha::esbisiesto(int a)
{
  bool bisiesto=false;
  if(a%4==0)
     bisiesto=true;
  if((a%100==0) && (a%400!=0))
           bisiesto=false;
  return bisiesto;
}

//Muestra la fecha en formato n�mero. Ej.:  15/10/2008
void Fecha::MostrarFecha()
{
  cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
}//�Qu� modificaci�n habr�a que hacer para que siempre muestre DD/MM/AAAA?


//Muestra la fecha indicando en texto el d�a y el mes.Ej.: Lunes 1 de enero de 1900
void Fecha::MostrarFechaTexto()
{
char mmes[12][10];
  strcpy(mmes[0],"Enero");
  strcpy(mmes[1],"Febrero");
  strcpy(mmes[2],"Marzo");
  strcpy(mmes[3],"Abril");
  strcpy(mmes[4],"Mayo");
  strcpy(mmes[5],"Junio");
  strcpy(mmes[6],"Julio");
  strcpy(mmes[7],"Agosto");
  strcpy(mmes[8],"Septiembre");
  strcpy(mmes[9],"OCtubre");
  strcpy(mmes[10],"Noviembre");
  strcpy(mmes[11],"Diciembre");


  int cantdias=NumeroSerie()-1;//cantidad de d�as transcurridos desde 01/01/1900
  //El 01/01/1900 fue Lunes
  int numerodia=cantdias%7;

  char mdia[7][10];
  strcpy(mdia[0],"Lunes");
  strcpy(mdia[1],"Martes");
  strcpy(mdia[2],"Miercoles");
  strcpy(mdia[3],"Jueves");
  strcpy(mdia[4],"Viernes");
  strcpy(mdia[5],"S�bado");
  strcpy(mdia[6],"Domingo");

  cout<<endl<<mdia[numerodia]<<" "<<dia<<" de "<<mmes[mes-1]<<" de "<<anio<<endl;
  }

  //Devuelve la cantidad de d�as transcurridos desde el 01/01/1900
  int Fecha::NumeroSerie()
  {
    int cont=0,i;
    for(i=1900;i<anio;i++)
      if(esbisiesto(i)) cont++;
    int vmes[]={31,28,31,30,31,30,31,31,30,31,31,31},suma=0;
    if(esbisiesto(anio)) vmes[1]=29;
    for(int i=0;i<mes-1;i++)  suma+=vmes[i];
    int cantdias=(anio-1900)*365+cont+suma+dia;
    return cantdias;
  }

bool Fecha::operator>(Fecha &obj)
{
  if(NumeroSerie()>obj.NumeroSerie())
    return true;
  return false;
}

bool Fecha::operator<(Fecha &obj)
{
  if(NumeroSerie()<obj.NumeroSerie())
    return true;
  return false;
}

bool Fecha::operator<=(Fecha &obj)
{
  if(NumeroSerie()<=obj.NumeroSerie())
    return true;
  return false;
}



bool Fecha::operator==(Fecha &obj)
{
  if(NumeroSerie()==obj.NumeroSerie())
    return true;
  return false;
}

void Fecha::NumeroSerieaFecha(int ns)
{
  int suma=0, dia_adicional, suma_ant;
  int anio_real=1900;
  while(ns>suma)
    {
    dia_adicional=(esbisiesto(anio_real)?1:0);
    suma_ant=suma;
    suma+=365+dia_adicional;
    anio_real++;
    }
   anio=anio_real-1;
   //Cantidad de d�as pasados desde anio
  int dias_anio_actual=ns-suma_ant,i=0;
  int vmes[]={31,28,31,30,31,30,31,31,30,31,31,31};
  if(esbisiesto(anio)) vmes[1]=29;
  suma=0;
  while(dias_anio_actual>suma) suma+=vmes[i++];
  mes=i;
  dia=dias_anio_actual-(suma-vmes[i-1]);
 }

void Fecha::operator +=(int masdias)
{
 int  ns=NumeroSerie()+masdias;
 NumeroSerieaFecha(ns);
 }

istream & operator>>(istream &entra, Fecha &f)
{
  cout<<"Ingrese el dia: ";
  entra>>f.dia;
  cout<<"Ingrese el mes: ";
  entra>>f.mes;
  cout<<"Ingrese el a�o: ";
  entra>>f.anio;
  return entra;
}

ostream & operator<<(ostream &sale, Fecha &f)
{
  cout<<"Dia: ";
  sale<<f.dia<<endl;
  cout<<"Mes: ";
  sale<<f.mes<<endl;
  cout<<"A�o: ";
  sale<<f.anio<<endl;
  return sale;
}

Fecha Fecha::operator+(int masdias)
{
 Fecha aux;
 int  ns=NumeroSerie()+masdias;
 aux.NumeroSerieaFecha(ns);
 return aux;
}

int Fecha::operator -(Fecha &obj)
{
  return NumeroSerie()-obj.NumeroSerie();
  }





#endif // FECHA_H
