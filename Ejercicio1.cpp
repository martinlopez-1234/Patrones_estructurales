/*
Supongamos que nos encargan construir una aplicación para poder buscar de hoteles, 
debemos brindar  un presupuesto según las características que se seleccionen. 
Además de los hoteles, se desea que en el futuro se oferten diferentes tipos de alojamientos
(contemplar la extensibilidad), como apartamentos u Hostels.
Construir una aplicación en C++ que permita la extensibilidad de Tipos de Hoteles
sin afectar el código, implementar un patrón Decorator para tal fin.
*/
#include <iostream>

using namespace std; 

// Clase componente, interfaz
class Soldado 
{
public:
    // Declaro métodos virtuales puros 
    virtual int ataqueEspada() = 0;
    virtual int defensaEscudo() = 0;
    virtual string llamarCompañeros() = 0;
};

// Componente concreto a ser decorado
class SoldadoClase1 : public Soldado 
{
public:
    //Implemento los métodos virtuales puros de la clase base
    int ataqueEspada() override
    {   // Devuelve el valor de ataque con espada
        return 4; 
    }

    int defensaEscudo() override 
    {   //Devuelve el valor que resta
        return -2; 
    }
    //Función que muestra la acción del soldado clase 1 cuando es atacado
    string llamarCompañeros() override {
        return "¡Nos atacan, que envien refuerzos!";
    }
};

// Decorador abstracto
class agregarObjetoSoldado : public Soldado 
{
protected:
    Soldado* soldado; // Puntero que apunta a clase soldado, agregación

public:
    agregarObjetoSoldado(Soldado* s) : soldado(s) {} // Constructor que inicializa el puntero

    // Implementa los métodos virtuales puros de la clase base delegando en el objeto soldado
    virtual int ataqueEspada() override {
        return soldado->ataqueEspada();
    }

    virtual int defensaEscudo() override {
        return soldado->defensaEscudo();
    }

    virtual string llamarCompañeros() override {
        return soldado->llamarCompañeros();
    }
};

// Decorador concreto
class agregarEspadaAcero : public agregarObjetoSoldado 
{
public:
     //Constructor que inicializa el puntero
    agregarEspadaAcero(Soldado* s) : agregarObjetoSoldado(s) {}

    int ataqueEspada() override
    {
        //Aumenta el ataque en 2 puntos
        return agregarObjetoSoldado::ataqueEspada() + 2;
    }
};

int main() 
{   //Creo un soldado
    Soldado* soldado = new SoldadoClase1(); 
    //Imprime el ataque por pantalla
    cout << "Ataque original: " << soldado->ataqueEspada() << endl; 

    // Decoro el soldado con una espada de acero
    Soldado* soldadoConEspadaAcero = new agregarEspadaAcero(soldado);
    // Muestra el nuevo ataque
    cout << "Ataque con espada de acero: " << soldadoConEspadaAcero->ataqueEspada() << endl; 
    //Libero la memoria del soldado original
    delete soldado; 
    //Libero la memoria del soldado decorado
    delete soldadoConEspadaAcero; 

    return 0;
}
