#ifndef PERSONA_H
#define PERSONA_H

using namespace std;
class Persona
{
    protected:
        char  dni[15];
        char nombre[20];
        char apellido[20];
        char telefono[15];
        char email[40];
        int estado = 1;


    public:
        char* GetDni(){return dni;};
        char* GetNombre(){return nombre;};
        char* GetApellido(){return apellido;};
        char* GetTelefono(){return telefono;};
        char* GetEmail(){return email;};
        int GetEstado(){return estado;}

        void SetDni(char *dni){strcpy(this->dni,dni);};
        void SetNombre(char *nombre){strcpy(this->nombre,nombre);};
        void SetApellido(char *apellido){strcpy(this->apellido,apellido);};
        void SetTelefono(char * telefono){strcpy(this->telefono,telefono);};
        void SetEmail(char * email){strcpy(this->email,email);};
        void SetEstado(int estado){this->estado=estado;};

        };

#endif // PERSONA_H
