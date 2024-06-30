#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <ctime>



using namespace std;




//Estructuras necesarias

struct Ambiente {
    string Nombre;
};


struct Especies{
    string nombre;
    int Energia;
    int Salud;
    Ambiente ambiente;
};

struct Accesorios {
    string Nombre;
    string Tipo;
    int Valor;
    string Tipo2;
    int Energia;
    int Contenedor;
};

struct Mochila {
    Accesorios Accesorio1;
    Accesorios Accesorio2;
    Accesorios Accesorio3;
    Accesorios Accesorio4;
    Accesorios Accesorio5;
};

struct Jugador {
    string Nombre;
    Especies Raza;
    vector<Accesorios> Mochila;
    string Fidelidad;
};

struct JugadorBatalla {
    string Nombre;
    vector<Accesorios> Mochila;
    int Energia;
    int Salud;
    Ambiente ambiente;
    int Contenedor;
    bool haPeleado;
};


struct NodoEspecie {
    Especies dato;
    NodoEspecie *siguientePtr;
};

struct NodoAccesorios {
    Accesorios dato;
    NodoAccesorios *siguientePtr;
};

struct NodoAmbiente {
    Ambiente dato;
    NodoAmbiente *siguientePtr;
};



NodoEspecie *especie = NULL;
NodoAccesorios *accesorio = NULL;
NodoAmbiente *lugar = NULL;


//Funcion para eliminar especie y lista vacia especie, ajuro en esta posicion

bool listaVaciaEspecie(NodoEspecie *inicio){
    return inicio==NULL;
}




void EliminarEspecie(NodoEspecie **inicio, int posicion){
    NodoEspecie *mover = NULL;
    NodoEspecie *anterior = NULL;

    if(listaVaciaEspecie(*inicio))
        cout << "No hay elementos a eliminar";
    else {
        mover = *inicio;
        int contador = 1;
        while((mover != NULL) && (contador != posicion)) {
            anterior = mover;
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición excede el numero de especies" << endl;
        else {
            if(mover == *inicio)
                *inicio=(*inicio)->siguientePtr;
            else
                anterior->siguientePtr = mover->siguientePtr;
            delete mover;
        }
    }
}






//Empiezan Funciones de Ambientes

Ambiente PedirAmbiente(){
    Ambiente nuevo_ambiente;
    string nuevo_nombre_ambiente = "";
    cout << "Ingresa el nombre del Ambiente: ";
    while (!(cin >> nuevo_nombre_ambiente)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo_ambiente.Nombre = nuevo_nombre_ambiente; 
    return nuevo_ambiente;
}

NodoAmbiente* CrearNodoAmbiente(Ambiente caracteristicas) {
    NodoAmbiente *nuevo = new NodoAmbiente;
    nuevo->dato = caracteristicas;
    nuevo->siguientePtr = NULL;
    return nuevo;
}


bool listaVaciaAmbiente(NodoAmbiente *inicio){
    return inicio==NULL;
}

void MostrarListaAmbientes(NodoAmbiente *inicio){
    NodoAmbiente *mover;
    int contador = 1;
    if(!listaVaciaAmbiente(inicio)){
        mover = inicio;
        while(mover != NULL) {
            cout << contador << ") " << mover->dato.Nombre << endl;
            mover = mover->siguientePtr;
            contador+=1; 
        }
    }
    else{
        cout << "No hay ningun ambiente, añada ambientes para jugar" << endl;
        }
}

void InsertarAmbiente(NodoAmbiente **inicio, Ambiente caracteristicas){
    NodoAmbiente *nuevo = CrearNodoAmbiente(caracteristicas);

    if(listaVaciaAmbiente(*inicio)){
        *inicio = nuevo;
    }
    else {
        NodoAmbiente *auxiliar = *inicio;
        while(auxiliar->siguientePtr != NULL) {
            auxiliar = auxiliar->siguientePtr;
        }
        auxiliar->siguientePtr = nuevo;
    }
}


void EliminarEspeciesAsociadas(NodoEspecie **inicio, string nombreAmbiente) {
    NodoEspecie *mover = NULL;
    NodoEspecie *anterior = NULL;

    if(listaVaciaEspecie(*inicio))
        cout << "No hay elementos a eliminar";
    else {
        mover = *inicio;
        int contador = 1;
        while(mover != NULL) {
            if (mover->dato.ambiente.Nombre == nombreAmbiente) {
                if(mover == *inicio)
                    *inicio=(*inicio)->siguientePtr;
                else
                    anterior->siguientePtr = mover->siguientePtr;
                delete mover;
                mover = anterior;
            } else {
                anterior = mover;
                mover = mover->siguientePtr;
            }
            contador++;
        }
    }
}

void EliminarAmbiente(NodoAmbiente **inicio, int posicion){
    NodoAmbiente *mover = NULL;
    NodoAmbiente *anterior = NULL;

    if(listaVaciaAmbiente(*inicio))
        cout << "No hay elementos a eliminar";
    else {
        mover = *inicio;
        int contador = 1;
        while((mover != NULL) && (contador != posicion)) {
            anterior = mover;
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición excede el numero de Ambientes" << endl;
        else {
            NodoEspecie *especieMover = especie;
            EliminarEspeciesAsociadas(&especie, mover->dato.Nombre);
            if(mover == *inicio)
                *inicio=(*inicio)->siguientePtr;
            else
                anterior->siguientePtr = mover->siguientePtr;
            delete mover;
        }
    }
}

void ModificarAmbiente(NodoAmbiente **inicio, int posicion, Ambiente nuevasCaracteristicas){
    NodoAmbiente *mover = NULL;
    int contador = 1;

    if(listaVaciaAmbiente(*inicio))
        cout << "No hay elementos a modificar" << endl;
    else {
        mover = *inicio;
        while((mover != NULL) && (contador != posicion)) {
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición ingresada no existe" << endl;
        else {
            mover->dato = nuevasCaracteristicas; 
            cout << "Ambiente modificado exitosamente" << endl;
        }
    }
}

Ambiente BuscarAmbientePorPosicion(NodoAmbiente *cabeza, int posicion){
    NodoAmbiente *actual = cabeza;
    int contador = 1;
    NodoAmbiente *prev;

    while(actual != NULL) {
        if (contador == posicion) {
            return actual->dato;
        }
        prev = actual; 
        actual = actual->siguientePtr;
        contador += 1;
    }

    cout << "No hay ambiente en la posicion seleccionada, se dara la que esta en la ultima posicion" << endl;
    return prev->dato;
}

int LongitudListaAmbientes(NodoAmbiente* lugar) {
    int longitud = 0;
    NodoAmbiente* temp = lugar;
    while (temp!= NULL) {
        longitud += 1;
        temp = temp->siguientePtr;
    }
    return longitud;
}


//Terminan Funciones de Ambientes





//Empiezan Funciones de Especies

Especies PedirEspecie(){
    int crearAmbiente = 0;
    Especies nueva_especie;
    string nuevo_nombre_raza = "";
    int nueva_energia_raza = 0;
    int nueva_salud_raza = 0;
    Ambiente nuevo_ambiente_raza = {};
    cout << "Ingresa el nombre de la raza: ";
    while (!(cin >> nuevo_nombre_raza)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nueva_especie.nombre = nuevo_nombre_raza; 
    cout << endl << "Ingresa la energía de la raza: ";
    while (!(cin >> nueva_energia_raza)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nueva_especie.Energia = nueva_energia_raza;
    cout << endl << "Ingresa la salud de la raza: ";
    while (!(cin >> nueva_salud_raza)) { 
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nueva_especie.Salud = nueva_salud_raza;
    cout << endl << "Ingresa el ambiente de la raza: " << endl;
    cout << endl << "Lista de ambientes: " << endl;
    MostrarListaAmbientes(lugar);
    cout << endl << endl << "Seleccione un ambiente o coloque 0 para crear un ambiente: ";
    while (!(cin >> crearAmbiente)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if(crearAmbiente == 0) {
        Ambiente ambiente_creado = PedirAmbiente();
        InsertarAmbiente(&lugar,ambiente_creado);
        nuevo_ambiente_raza = ambiente_creado;
    }
    else {
        nuevo_ambiente_raza = BuscarAmbientePorPosicion(lugar, crearAmbiente);
    }
    nueva_especie.ambiente = nuevo_ambiente_raza;
    return nueva_especie;
}

NodoEspecie* CrearNodoEspecies(Especies caracteristicas) {
    NodoEspecie *nuevo = new NodoEspecie;
    nuevo->dato = caracteristicas;
    nuevo->siguientePtr = NULL;
    return nuevo;
}

void MostrarListaEspecies(NodoEspecie *inicio){
    NodoEspecie *mover;
    int contador = 1;
    if(!listaVaciaEspecie(inicio)){
        mover = inicio;
        while(mover != NULL) {
            cout << contador << ") " << mover->dato.nombre << ", " << mover->dato.Energia << ", " << mover->dato.Salud;
            cout << ", " << mover->dato.ambiente.Nombre << endl;
            mover = mover->siguientePtr;
            contador+=1; 
        }
    }
    else
        cout << "No hay ninguna especie, añada especies para jugar." << endl;
}

void InsertarEspecie(NodoEspecie **inicio, Especies caracteristicas){
    NodoEspecie *nuevo = CrearNodoEspecies(caracteristicas);

    if(listaVaciaEspecie(*inicio)){
        *inicio = nuevo;
    }
    else {
        NodoEspecie *auxiliar = *inicio;
        while(auxiliar->siguientePtr != NULL) {
            auxiliar = auxiliar->siguientePtr;
        }
        auxiliar->siguientePtr = nuevo;
    }
}

void ModificarEspecie(NodoEspecie **inicio, int posicion, Especies nuevasCaracteristicas){
    NodoEspecie *mover = NULL;
    int contador = 1;

    if(listaVaciaEspecie(*inicio))
        cout << "No hay elementos a modificar" << endl;
    else {
        mover = *inicio;
        while((mover != NULL) && (contador != posicion)) {
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición ingresada no existe" << endl;
        else {
            mover->dato = nuevasCaracteristicas; 
            cout << "Especie modificada exitosamente" << endl;
        }
    }
}

Especies BuscarEspeciePorPosicion(NodoEspecie *cabeza, int posicion){
    NodoEspecie *actual = cabeza;
    int contador = 1;
    NodoEspecie *prev;

    while(actual != NULL) {
        if (contador == posicion) {
            return actual->dato;
        }
        prev = actual;
        actual = actual->siguientePtr;
        contador += 1;
    }

    cout << "No hay raza en la posicion seleccionada, le daremos la especie que este en la ultima posicion" << endl;
    return prev->dato;
}

//Terminan Funciones de Especies







//Empiezan Funciones de Accesorios

Accesorios PedirAccesorio(){
    Accesorios nuevo_accesorio;
    int seleccion_tipo_2 = 0;
    string nuevo_nombre_accesorio = "";
    int nuevo_tipo_accesorio = 0;
    int nuevo_valor_accesorio = 0;
    int nueva_energia_accesorio = 0;
    int nuevo_contenedor_accesorio = 0;
    cout << "Ingresa el nombre del accesorio: ";
    while (!(cin >> nuevo_nombre_accesorio)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo_accesorio.Nombre = nuevo_nombre_accesorio; 
    cout << endl << "Estos son los tipos del accesorio: ";
    cout << endl << endl << "1) Ataque" << endl << "2) Defensa" << endl << "3) Supervivencia" << endl << "4) Acondicionamiento" << endl;
    cout << endl << "Ingrese el tipo del accesorio: ";
    while (!(cin >> nuevo_tipo_accesorio) or nuevo_tipo_accesorio < 1 or nuevo_tipo_accesorio > 4) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if(nuevo_tipo_accesorio == 1) {
        nuevo_accesorio.Tipo = "Ataque";
    } else if(nuevo_tipo_accesorio == 2) {
        nuevo_accesorio.Tipo = "Defensa";
    } else if(nuevo_tipo_accesorio == 3) {
        nuevo_accesorio.Tipo = "Supervivencia";
    } else if(nuevo_tipo_accesorio == 4) {
        nuevo_accesorio.Tipo = "Acondicionamiento";
    }
    cout << endl << "Ingresa el valor del accesorio: ";
    while (!(cin >> nuevo_valor_accesorio)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo_accesorio.Valor = nuevo_valor_accesorio;
    cout << endl << "Ingresa la energia de su accesorio: ";
    while (!(cin >> nueva_energia_accesorio)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo_accesorio.Energia = nueva_energia_accesorio;
    cout << endl << "Ingresa el contenedor de su accesorio: ";
    while (!(cin >> nuevo_contenedor_accesorio)) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nuevo_accesorio.Contenedor = nuevo_contenedor_accesorio;
    if (nuevo_accesorio.Tipo == "Supervivencia") {
        cout << endl << "¿Su accesorio cura vida o energia?";
        cout << endl << "1) Vida" << endl << "2) Energia" << endl;
        while (!(cin >> seleccion_tipo_2) or seleccion_tipo_2 < 1 or seleccion_tipo_2 > 2) {
            cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if(seleccion_tipo_2 == 1) {
        nuevo_accesorio.Tipo2 = "Vida";
        } else {
            nuevo_accesorio.Tipo2 = "Energia";
        }
    } else if (nuevo_accesorio.Tipo == "Acondicionamiento") {
        cout << endl << "Ingresa el ambiente que protege el objeto: " << endl;
        cout << endl << "Lista de ambientes: " << endl;
        MostrarListaAmbientes(lugar);
        cout << endl << endl << "Seleccione un ambiente: ";
        while (!(cin >> seleccion_tipo_2)) {
            cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        nuevo_accesorio.Tipo2 = BuscarAmbientePorPosicion(lugar, seleccion_tipo_2).Nombre;
    } else {
        nuevo_accesorio.Tipo2 = "";
    }
    return nuevo_accesorio;
}

NodoAccesorios* CrearNodoAccesorio(Accesorios caracteristicas) {
    NodoAccesorios *nuevo = new NodoAccesorios;
    nuevo->dato = caracteristicas;
    nuevo->siguientePtr = NULL;
    return nuevo;
}

bool listaVaciaAccesorio(NodoAccesorios *inicio){
    return inicio==NULL;
}

void MostrarListaAccesorio(NodoAccesorios *inicio){
    NodoAccesorios *mover;
    int contador = 1;
    if(!listaVaciaAccesorio(inicio)){
        mover = inicio;
        while(mover != NULL) {
            cout << contador << ") " << mover->dato.Nombre << ", " << mover->dato.Tipo << ", " << mover->dato.Valor;
            cout << ", " << mover->dato.Tipo2 << ", " << mover->dato.Energia << "," << mover->dato.Contenedor << endl;
            mover = mover->siguientePtr;
            contador+=1; 
        }
    }
    else
        cout << "No hay ningun elemento a mostrar, añada elementos para jugar" << endl;
}

void InsertarAccesorio(NodoAccesorios **inicio, Accesorios caracteristicas){
    NodoAccesorios *nuevo = CrearNodoAccesorio(caracteristicas);

    if(listaVaciaAccesorio(*inicio)){
        *inicio = nuevo;
    }
    else {
        NodoAccesorios *auxiliar = *inicio;
        while(auxiliar->siguientePtr != NULL) {
            auxiliar = auxiliar->siguientePtr;
        }
        auxiliar->siguientePtr = nuevo;
    }
}

void EliminarAccesorio(NodoAccesorios **inicio, int posicion){
    NodoAccesorios *mover = NULL;
    NodoAccesorios *anterior = NULL;

    if(listaVaciaAccesorio(*inicio))
        cout << "No hay elementos a eliminar"<<endl<<endl;
    else {
        mover = *inicio;
        int contador = 1;
        while((mover != NULL) && (contador != posicion)) {
            anterior = mover;
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición excede el numero de especies" << endl;
        else {
            if(mover == *inicio)
                *inicio=(*inicio)->siguientePtr;
            else
                anterior->siguientePtr = mover->siguientePtr;
            delete mover;
        }
    }
}

void ModificarAccesorio(NodoAccesorios **inicio, int posicion, Accesorios nuevasCaracteristicas){
    NodoAccesorios *mover = NULL;
    int contador = 1;

    if(listaVaciaAccesorio(*inicio))
        cout << "No hay elementos a modificar" << endl;
    else {
        mover = *inicio;
        while((mover != NULL) && (contador != posicion)) {
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición ingresada no existe" << endl;
        else {
            mover->dato = nuevasCaracteristicas; 
            cout << "Especie modificada exitosamente" << endl;
        }
    }
}

Accesorios BuscarAccesorioPorPosicion(NodoAccesorios *cabeza, int posicion){
    NodoAccesorios *actual = cabeza;
    int contador = 1;
    NodoAccesorios *prev_ac;

    while(actual != NULL) {
        if (contador == posicion) {
            return actual->dato;
        }
        prev_ac = actual;
        actual = actual->siguientePtr;
        contador += 1;
    }

    cout << "No hay accesorio en la posicion seleccionada" << endl;
    return prev_ac->dato;
}

//Terminan Funciones de Accesorios


//Funcion de objetos ambientes

bool BuscarObjetoAmbiente(vector<Accesorios> listaMochila, Ambiente ambienteABuscar) {
    for (int i = 0; i < listaMochila.size(); i++) {
        if (listaMochila[i].Tipo2 == ambienteABuscar.Nombre) {
            return true;
        }
    }
    return false;
}

int BuscarNombreEnVector(const vector<JugadorBatalla>& vec, const string& str) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].Nombre == str) {
            return i; 
        }
    }

    return -1;
}

bool BuscarNombre(vector<Jugador> personajes, string nombre) {
    for (int i = 0; i < personajes.size(); i++) {
        if (personajes[i].Nombre == nombre) {
            return true;
        }
    }
    return false;
}



//Funcion de la partida


int seleccion;
int turno = 0;
int energia_eliminar_p1 = 0;
int energia_eliminar_p2 = 0;
int vida_a_proteger_p1 = 0;
int vida_a_proteger_p2 = 0;

vector<JugadorBatalla> ply1;
vector<JugadorBatalla> ply2;
JugadorBatalla personaje_actual_J1;
JugadorBatalla personaje_actual_J2;
JugadorBatalla prev_p;


void seleccionarPersonaje(vector<JugadorBatalla>& personajes, int jugador) {
    int seleccion_personaje;
    cout << endl << "Jugador " << jugador << ", seleccione a su personaje" << endl << endl;
    if(jugador == 1) {
        for (int i = 0; i < size(ply1); i++) {
            cout << i << ") " << personajes[i].Nombre << endl;
        }
    } else {
        for (int i = 0; i < size(ply2); i++) {
            cout << i << ") " << personajes[i].Nombre << endl;
        }
    }
    while (!(cin >> seleccion_personaje) or seleccion_personaje < 0 or seleccion_personaje > 2) {
        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for(int i = 0; i<3; i++) {
        if(ply1[i].haPeleado == true && ply1[i].Nombre != prev_p.Nombre) {
            ply1[i].Energia += ply1[i].Energia * 0.25;
            ply1[i].Salud += ply1[i].Salud * 0.10;
        }
        if(ply2[i].haPeleado == true && ply2[i].Nombre != prev_p.Nombre) {
            ply2[i].Energia += ply2[i].Energia * 0.25;
            ply2[i].Salud += ply2[i].Salud * 0.10;
        }
    }
    JugadorBatalla personaje_actual;
    personaje_actual.Nombre = personajes[seleccion_personaje].Nombre;
    personaje_actual.Salud = personajes[seleccion_personaje].Salud;
    personaje_actual.Energia = personajes[seleccion_personaje].Energia;
    personaje_actual.ambiente = personajes[seleccion_personaje].ambiente;
    personaje_actual.Mochila = personajes[seleccion_personaje].Mochila;
    personaje_actual.Contenedor = personajes[seleccion_personaje].Contenedor;
    personaje_actual.haPeleado = personajes[seleccion_personaje].haPeleado;

    // Mostrar mochila del personaje
    cout << endl << "Mochila del personaje " << personaje_actual.Nombre << ":" << endl;
    for (int i = 0; i < personajes[seleccion_personaje].Mochila.size(); i++) {
        cout << i << ") " << personajes[seleccion_personaje].Mochila[i].Nombre << endl;
    }

    // Seleccionar 3 objetos para la mochila
    vector<Accesorios> mochila_seleccionada;
    cout << endl << "Seleccione 3 objetos para la mochila:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << endl << "Ingrese la posición del objeto a agregar: ";
        int seleccion_accesorio;
        while (!(cin >> seleccion_accesorio) || seleccion_accesorio < 0 || seleccion_accesorio >= personaje_actual.Mochila.size()) {
            cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl << endl;
        mochila_seleccionada.push_back(personaje_actual.Mochila[seleccion_accesorio]);
        cout << "Ha seleccionado: " << personaje_actual.Mochila[seleccion_accesorio].Nombre << endl;
    }
    personaje_actual.Mochila = mochila_seleccionada;

    if (jugador == 1) {
        personaje_actual_J1.Nombre = personaje_actual.Nombre;
        personaje_actual_J1.Salud = personaje_actual.Salud;
        personaje_actual_J1.Energia = personaje_actual.Energia;
        personaje_actual_J1.ambiente = personaje_actual.ambiente;
        personaje_actual_J1.Mochila = personaje_actual.Mochila;
        personaje_actual_J1.Contenedor = personaje_actual.Contenedor;
        personaje_actual_J1.haPeleado = personaje_actual.haPeleado;
    } else {
        personaje_actual_J2.Nombre = personaje_actual.Nombre;
        personaje_actual_J2.Salud = personaje_actual.Salud;
        personaje_actual_J2.Energia = personaje_actual.Energia;
        personaje_actual_J2.ambiente = personaje_actual.ambiente;
        personaje_actual_J2.Mochila = personaje_actual.Mochila;
        personaje_actual_J2.Contenedor = personaje_actual.Contenedor;
        personaje_actual_J2.haPeleado = personaje_actual.haPeleado;
    }
}

bool nombre_existe = false;
bool turno_jugador1 = true;
bool turno_jugador2 = false;
int contador = 0;
int aleatorio1;
int aleatorio2;

void EmpezarJuego(Ambiente ambienteJuego, JugadorBatalla p1, JugadorBatalla p2) {
    int seleccion_informacion;
    int seleccion_objeto;
    int seleccion_nuevo_personaje;

    if (turno_jugador1) {
        if(p1.ambiente.Nombre != ambienteJuego.Nombre && BuscarObjetoAmbiente(p1.Mochila, ambienteJuego) == false) {
                p1.Salud = p1.Salud - p1.Salud/3;
                p1.Energia = p1.Energia - p1.Energia/3;
                cout << endl << "Como el ambiente de su jugador no es igual al del campo y no tiene ningun objeto para contrarrestar," << endl;
                cout << "Se le quitara vida y energia a su personje";
                }
        while(contador < 2) {
                        cout<< endl <<"-------------------------------------";
            cout << endl << ">==========TURNO JUGADOR 1==========<" << endl;
                    cout<< "-------------------------------------" << endl;
            cout << endl << p1.Nombre << endl << "Vida: " << p1.Salud << endl << "Midiclorias: " << p1.Energia;
            cout << endl;
            cout << "Mochila: " << endl << endl;
            for (int i = 0; i < p1.Mochila.size(); i++) {
                cout << i << ") " << p1.Mochila[i].Nombre << endl;
            }
            cout << "3) Saltar Turno" << endl;
            cout << "4) Ver informacion de un objeto" << endl;
            cout << endl << "Seleccione el objeto que va a usar: " << endl;
            while (!(cin >> seleccion_objeto) or seleccion_objeto < 0 or (seleccion_objeto > p1.Mochila.size() && seleccion_objeto != 3 && seleccion_objeto != 4)) {
                cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (seleccion_objeto == 3) {
                cout << endl << "El jugador ha saltado su turno." << endl;
            }
            else if (seleccion_objeto == 4) {
                cout << endl << "Seleccione el objeto que qiuiere ver." << endl;
                while (!(cin >> seleccion_informacion) or seleccion_informacion < 0 or seleccion_informacion > p1.Mochila.size()) {
                    cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << p1.Mochila[seleccion_informacion].Nombre << endl;
                cout << "Tipo: " << p1.Mochila[seleccion_informacion].Tipo << endl;
                cout << "Valor: " << p1.Mochila[seleccion_informacion].Valor << endl;
                cout << "Energia: " << p1.Mochila[seleccion_informacion].Energia << endl;
                if(p1.Mochila[seleccion_informacion].Contenedor != 0) {
                    cout << "Contenedor: " << p1.Mochila[seleccion_informacion].Contenedor << endl;
                }
                if(p1.Mochila[seleccion_informacion].Tipo2 != "") {
                    cout << "Recuperacion: " << p1.Mochila[seleccion_informacion].Tipo2 << endl << endl;
                }
                contador -=1;
            }
            else if (p1.Mochila[seleccion_objeto].Tipo == "Ataque") {
                if(p2.Contenedor > 0) {
                    p2.Energia -= energia_eliminar_p2;
                    p2.Contenedor -= p1.Mochila[seleccion_objeto].Valor - ((p1.Mochila[seleccion_objeto].Valor * vida_a_proteger_p2)/100);
                    if (p2.Contenedor <= 0) {
                        vida_a_proteger_p2 = 0;
                        p2.Salud += p2.Contenedor;
                        p2.Contenedor = 0;
                        energia_eliminar_p2 = 0;
                    }
                    if (p2.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 2 ha muerto." << endl;
                }
                } else {
                    p2.Salud -= p1.Mochila[seleccion_objeto].Valor;
                }
                if (p2.Salud < 0) {
                    p2.Salud = 0;
                }
                p1.Energia -= p1.Mochila[seleccion_objeto].Energia;
                if (p1.Energia < 0) {
                    p1.Energia = 0;
                }
                cout << endl << "Ataque realizado exitosamente." << endl;
                cout << endl << "Ahora el personaje del jugador 2 tiene: " << p2.Salud << " puntos de vida";
                if (p2.Salud == 0) {
                    cout << endl << endl << "El personaje del jugador 2 ha muerto." << endl;
                }
                if (p1.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 1 ha muerto." << endl;
                }
            } else if (p1.Mochila[seleccion_objeto].Tipo == "Defensa") {
                energia_eliminar_p1 = p1.Mochila[seleccion_objeto].Energia;
                if (p1.Energia < 0) {
                    p1.Energia = 0;
                }
                vida_a_proteger_p1 = p1.Mochila[seleccion_objeto].Valor;
                p1.Contenedor = p1.Mochila[seleccion_objeto].Contenedor;
                cout << endl << "Defensa realizada exitosamente." << endl;
                if (p1.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 1 ha muerto." << endl;
                }
                p1.Mochila.erase(p1.Mochila.begin() + seleccion_objeto);
            } else if (p1.Mochila[seleccion_objeto].Tipo == "Supervivencia") {
                p1.Salud += p1.Mochila[seleccion_objeto].Valor;
                p1.Energia -= p1.Mochila[seleccion_objeto].Energia;
                if (p1.Energia < 0) {
                    p1.Energia = 0;
                }
                cout << endl << "Objeto utilizado exitosamente" << endl;
                cout << endl << "Su personaje se ha curado: " << p1.Mochila[seleccion_objeto].Valor << " puntos de vida";
                if (p1.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 1 ha muerto." << endl;
                }
                p1.Mochila.erase(p1.Mochila.begin() + seleccion_objeto);
            } else {
                cout << endl << "Este objeto no tiene uso, se repetira el turno." << endl;
                contador -=1;
            }
            if (p2.Salud <=0 or p2.Energia <= 0 or p1.Salud <= 0 or p1.Energia <= 0) {
                contador = 2;
            }
            contador += 1;
        }
        turno_jugador1 = false;
        turno_jugador2 = true;
        contador = 0;
    } else {         // Turno jugador 2
        if(p2.ambiente.Nombre != ambienteJuego.Nombre && BuscarObjetoAmbiente(p2.Mochila, ambienteJuego) == false) {
                p2.Salud = p2.Salud - p2.Salud/3;
                p2.Energia = p2.Energia - p2.Energia/3;
                cout << endl << "Como el ambiente de su jugador no es igual al del campo y no tiene ningun objeto para contrarrestar," << endl;
                cout << "Se le quitara vida y energia a su personje" << endl;
            }
        while(contador < 2) {
                        cout<< endl <<"-------------------------------------";
            cout << endl << ">==========TURNO JUGADOR 2==========<" << endl;
                        cout<<"-------------------------------------"<<endl;
            cout << endl << p2.Nombre << endl << "Vida: " << p2.Salud << endl << "Midiclorias: " << p2.Energia;
            cout << endl;
            cout << "Mochila: " << endl << endl;
            for (int i = 0; i < p2.Mochila.size(); i++) {
                cout << i << ") " << p2.Mochila[i].Nombre << endl;
            }
            cout << "3) Saltar Turno" << endl;
            cout << "4) Ver informacion de un objeto" << endl;
            cout << endl << "Seleccione el objeto que va a usar " << endl;
            while (!(cin >> seleccion_objeto) or seleccion_objeto < 0 or (seleccion_objeto > p2.Mochila.size() && seleccion_objeto != 3 && seleccion_objeto != 4)) {
                cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (seleccion_objeto == 3) {
                cout << endl << "El jugador ha saltado su turno" << endl;
            }
            else if (seleccion_objeto == 4) {
                cout << endl << "Seleccione el objeto que qiuiere ver." << endl;
                while (!(cin >> seleccion_informacion) or seleccion_informacion < 0 or seleccion_informacion > p2.Mochila.size()) {
                    cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << p2.Mochila[seleccion_informacion].Nombre << endl;
                cout << "Tipo: " << p2.Mochila[seleccion_informacion].Tipo << endl;
                cout << "Valor: " << p2.Mochila[seleccion_informacion].Valor << endl;
                cout << "Energia: " << p2.Mochila[seleccion_informacion].Energia << endl;
                if(p2.Mochila[seleccion_informacion].Contenedor != 0) {
                    cout << "Contenedor: " << p2.Mochila[seleccion_informacion].Contenedor << endl;
                }
                if(p2.Mochila[seleccion_informacion].Tipo2 != "") {
                    cout << "Recuperacion: " << p2.Mochila[seleccion_informacion].Tipo2 << endl << endl;
                }
                contador -=1;
            }
            else if (p2.Mochila[seleccion_objeto].Tipo == "Ataque") {
                if(p1.Contenedor > 0) {
                    p1.Energia -= energia_eliminar_p1;
                    p1.Contenedor -= p2.Mochila[seleccion_objeto].Valor - ((p2.Mochila[seleccion_objeto].Valor * vida_a_proteger_p1)/100);
                    if (p1.Contenedor <= 0) {
                        vida_a_proteger_p1 = 0;
                        p1.Salud += p1.Contenedor;
                        p1.Contenedor = 0;
                        energia_eliminar_p1 = 0;
                    }
                    if (p1.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 1 ha muerto." << endl;
                }
                } else {
                    p1.Salud -= p2.Mochila[seleccion_objeto].Valor;
                }
                if (p1.Salud < 0) {
                    p1.Salud = 0;
                }
                p2.Energia -= p2.Mochila[seleccion_objeto].Energia;
                if (p2.Energia < 0) {
                    p2.Energia = 0;
                }
                cout << endl << "Ataque realizado exitosamente" << endl;
                cout << endl << "Ahora el personaje del jugador 1 tiene: " << p1.Salud << " puntos de vida";
                if (p1.Salud == 0) {
                    cout << endl << endl << "El personaje del jugador 1 ha muerto." << endl;
                }
                if (p2.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 2 ha muerto." << endl;
                }
            } else if (p2.Mochila[seleccion_objeto].Tipo == "Defensa") {
                energia_eliminar_p2 = p2.Mochila[seleccion_objeto].Energia;
                if (p2.Energia < 0) {
                    p2.Energia = 0;
                }
                vida_a_proteger_p2 = p2.Mochila[seleccion_objeto].Valor;
                p2.Contenedor = p2.Mochila[seleccion_objeto].Contenedor;
                cout << endl << "Defensa realizada exitosamente" << endl;
                if (p2.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 2 ha muerto." << endl;
                }
                p2.Mochila.erase(p2.Mochila.begin() + seleccion_objeto);
            } else if (p2.Mochila[seleccion_objeto].Tipo == "Supervivencia") {
                p2.Salud += p2.Mochila[seleccion_objeto].Valor;
                p2.Energia -= p2.Mochila[seleccion_objeto].Energia;
                if (p2.Energia < 0) {
                    p2.Energia = 0;
                }
                cout << endl << "Objeto utilizado exitosamente" << endl;
                cout << endl << "Su personaje se ha curado: " << p2.Mochila[seleccion_objeto].Valor << " puntos de vida";
                if (p2.Energia == 0) {
                    cout << endl << endl << "El personaje del jugador 2 ha muerto." << endl;
                }
                p2.Mochila.erase(p2.Mochila.begin() + seleccion_objeto);
            } else {
                cout << endl << "Este objeto no tiene uso, se repetira el turno" << endl;
                contador -=1;
            }
            if (p2.Salud <=0 or p2.Energia <= 0 or p1.Salud <= 0 or p1.Energia <= 0) {
                contador = 2;
            }
            contador += 1;
        } 
        turno_jugador2 = false;
        turno_jugador1 = true;
        contador = 0;
        
        }


    

    // Verificar si alguno de los personajes ha muerto

    if ((p1.Salud <= 0 or p1.Energia <=0) && (p2.Salud <= 0 or p2.Energia <=0)) {
        ply1.erase(ply1.begin() + BuscarNombreEnVector(ply1, p1.Nombre));
        ply2.erase(ply2.begin() + BuscarNombreEnVector(ply2, p2.Nombre));
        if(ply1.size() == 0 && ply2.size() == 0) {
            cout << endl << endl << "▓█████  ███▄ ▄███▓ ██▓███   ▄▄▄     ▄▄▄█████▓▓█████ " << endl;
                            cout << "▓█   ▀ ▓██▒▀█▀ ██▒▓██░  ██▒▒████▄   ▓  ██▒ ▓▒▓█   ▀ " << endl;
                            cout << "▒███   ▓██    ▓██░▓██░ ██▓▒▒██  ▀█▄ ▒ ▓██░ ▒░▒███   " << endl;
                            cout << "▒▓█  ▄ ▒██    ▒██ ▒██▄█▓▒ ▒░██▄▄▄▄██░ ▓██▓ ░ ▒▓█  ▄ " << endl;
                            cout << "░▒████▒▒██▒   ░██▒▒██▒ ░  ░ ▓█   ▓██▒ ▒██▒ ░ ░▒████▒" << endl;
                            cout << "░░ ▒░ ░░ ▒░   ░  ░▒▓▒░ ░  ░ ▒▒   ▓▒█░ ▒ ░░   ░░ ▒░ ░" << endl;
                            cout << " ░ ░  ░░  ░      ░░▒ ░       ▒   ▒▒ ░   ░     ░ ░  ░" << endl;
                            cout << "   ░   ░      ░   ░░         ░   ▒    ░         ░   " << endl;
                            cout << "   ░  ░       ░                  ░  ░           ░  ░" << endl<<endl;

                            
            return;
        }
        else if(ply1.size() == 0) {
            cout << endl << endl << "db    db d888888b  .o88b. d888888b  .d88b.  d8888b. d888888b  .d8b.          d88b db    db  d888b   .d8b.  d8888b.  .d88b.  d8888b.      .d888b. " << endl;
                            cout << "88    88   `88'   d8P  Y8 `~~88~~' .8P  Y8. 88  `8D   `88'   d8' `8b         `8P' 88    88 88' Y8b d8' `8b 88  `8D .8P  Y8. 88  `8D      VP  `8D " << endl;
                            cout << "Y8    8P    88    8P         88    88    88 88oobY'    88    88ooo88          88  88    88 88      88ooo88 88   88 88    88 88oobY'         odD' " << endl;
                            cout << "`8b  d8'    88    8b         88    88    88 88`8b      88    88~~~88          88  88    88 88  ooo 88~~~88 88   88 88    88 88`8b         .88'   " << endl;
                            cout << " `8bd8'    .88.   Y8b  d8    88    `8b  d8' 88 `88.   .88.   88   88      db. 88  88b  d88 88. ~8~ 88   88 88  .8D `8b  d8' 88 `88.      j88.    " << endl;
                            cout << "   YP    Y888888P  `Y88P'    YP     `Y88P'  88   YD Y888888P YP   YP      Y8888P  ~Y8888P'  Y888P  YP   YP Y8888D'  `Y88P'  88   YD      888888D " << endl<<endl;
            return;
        }
        else if(ply2.size() == 0) {
         
            cout << endl << endl << "db    db d888888b  .o88b. d888888b  .d88b.  d8888b. d888888b  .d8b.          d88b db    db  d888b   .d8b.  d8888b.  .d88b.  d8888b.       db " << endl;
                            cout << "88    88   `88'   d8P  Y8 `~~88~~' .8P  Y8. 88  `8D   `88'   d8' `8b         `8P' 88    88 88' Y8b d8' `8b 88  `8D .8P  Y8. 88  `8D      o88 " << endl;
                            cout << "Y8    8P    88    8P         88    88    88 88oobY'    88    88ooo88          88  88    88 88      88ooo88 88   88 88    88 88oobY'       88 " << endl;
                            cout << "`8b  d8'    88    8b         88    88    88 88`8b      88    88~~~88          88  88    88 88  ooo 88~~~88 88   88 88    88 88`8b         88 " << endl;
                            cout << " `8bd8'    .88.   Y8b  d8    88    `8b  d8' 88 `88.   .88.   88   88      db. 88  88b  d88 88. ~8~ 88   88 88  .8D `8b  d8' 88 `88.       88 " << endl;
                            cout << "   YP    Y888888P  `Y88P'    YP     `Y88P'  88   YD Y888888P YP   YP      Y8888P  ~Y8888P'  Y888P  YP   YP Y8888D'  `Y88P'  88   YD       VP " << endl<< endl;
            return;
        }
        seleccionarPersonaje(ply1, 1);
        p1 = personaje_actual_J1;
        seleccionarPersonaje(ply2, 2);
        p2 = personaje_actual_J2;
        aleatorio2 = rand() % 2;
        if(p1.ambiente.Nombre != ambienteJuego.Nombre && p2.ambiente.Nombre == ambienteJuego.Nombre) {
            turno_jugador1 = true;
            turno_jugador2 = false;
        } else if (p1.ambiente.Nombre == ambienteJuego.Nombre && p2.ambiente.Nombre != ambienteJuego.Nombre) {
            turno_jugador1 = false;
            turno_jugador2 = true;
        } else {
            aleatorio2 = rand() % 2;
            if(aleatorio2 == 0) {
                turno_jugador1 = true;
                turno_jugador2 = false;
            } else {
                turno_jugador1 = false;
                turno_jugador2 = true;
            }
        }
    } 
    
    else if (p1.Salud <= 0 or p1.Energia <= 0 && ply1.size() != 0) {
        p2.Energia += p1.Energia;
        ply1.erase(ply1.begin() + BuscarNombreEnVector(ply1, p1.Nombre));
        if(ply1.size() == 0) {
            cout << endl << endl << "db    db d888888b  .o88b. d888888b  .d88b.  d8888b. d888888b  .d8b.          d88b db    db  d888b   .d8b.  d8888b.  .d88b.  d8888b.      .d888b. " << endl;
                            cout << "88    88   `88'   d8P  Y8 `~~88~~' .8P  Y8. 88  `8D   `88'   d8' `8b         `8P' 88    88 88' Y8b d8' `8b 88  `8D .8P  Y8. 88  `8D      VP  `8D " << endl;
                            cout << "Y8    8P    88    8P         88    88    88 88oobY'    88    88ooo88          88  88    88 88      88ooo88 88   88 88    88 88oobY'         odD' " << endl;
                            cout << "`8b  d8'    88    8b         88    88    88 88`8b      88    88~~~88          88  88    88 88  ooo 88~~~88 88   88 88    88 88`8b         .88'   " << endl;
                            cout << " `8bd8'    .88.   Y8b  d8    88    `8b  d8' 88 `88.   .88.   88   88      db. 88  88b  d88 88. ~8~ 88   88 88  .8D `8b  d8' 88 `88.      j88.    " << endl;
                            cout << "   YP    Y888888P  `Y88P'    YP     `Y88P'  88   YD Y888888P YP   YP      Y8888P  ~Y8888P'  Y888P  YP   YP Y8888D'  `Y88P'  88   YD      888888D " << endl<<endl;
            return;
        }
        p2.Mochila = ply2[BuscarNombreEnVector(ply2, p2.Nombre)].Mochila;
        ply2.erase(ply2.begin() + BuscarNombreEnVector(ply2, p2.Nombre));
        p2.haPeleado = true;
        prev_p = p2;
        ply2.push_back(p2);
        seleccionarPersonaje(ply1, 1);
        p1 = personaje_actual_J1;
        seleccionarPersonaje(ply2, 2);
        p2 = personaje_actual_J2;
        if(p1.ambiente.Nombre != ambienteJuego.Nombre && p2.ambiente.Nombre == ambienteJuego.Nombre) {
            turno_jugador1 = true;
            turno_jugador2 = false;
        } else if (p1.ambiente.Nombre == ambienteJuego.Nombre && p2.ambiente.Nombre != ambienteJuego.Nombre) {
            turno_jugador1 = false;
            turno_jugador2 = true;
        } else {
            aleatorio2 = rand() % 2;
            if(aleatorio2 == 0) {
                turno_jugador1 = true;
                turno_jugador2 = false;
            } else {
                turno_jugador1 = false;
                turno_jugador2 = true;
            }
        }
    }
    else if (p2.Salud <= 0 or p2.Energia <= 0 && ply2.size() != 0) {
        p1.Energia += p2.Energia;
        ply2.erase(ply2.begin() + BuscarNombreEnVector(ply2, p2.Nombre));
        if(ply2.size() == 0) {
            //--------------------------------------------------------------------
            cout << endl << endl << "db    db d888888b  .o88b. d888888b  .d88b.  d8888b. d888888b  .d8b.          d88b db    db  d888b   .d8b.  d8888b.  .d88b.  d8888b.       db " << endl;
                            cout << "88    88   `88'   d8P  Y8 `~~88~~' .8P  Y8. 88  `8D   `88'   d8' `8b         `8P' 88    88 88' Y8b d8' `8b 88  `8D .8P  Y8. 88  `8D      o88 " << endl;
                            cout << "Y8    8P    88    8P         88    88    88 88oobY'    88    88ooo88          88  88    88 88      88ooo88 88   88 88    88 88oobY'       88 " << endl;
                            cout << "`8b  d8'    88    8b         88    88    88 88`8b      88    88~~~88          88  88    88 88  ooo 88~~~88 88   88 88    88 88`8b         88 " << endl;
                            cout << " `8bd8'    .88.   Y8b  d8    88    `8b  d8' 88 `88.   .88.   88   88      db. 88  88b  d88 88. ~8~ 88   88 88  .8D `8b  d8' 88 `88.       88 " << endl;
                            cout << "   YP    Y888888P  `Y88P'    YP     `Y88P'  88   YD Y888888P YP   YP      Y8888P  ~Y8888P'  Y888P  YP   YP Y8888D'  `Y88P'  88   YD       VP " << endl<< endl;
            return;
        }
        p1.Mochila = ply1[BuscarNombreEnVector(ply1, p1.Nombre)].Mochila;
        ply1.erase(ply1.begin() + BuscarNombreEnVector(ply1, p1.Nombre));
        p1.haPeleado = true;
        prev_p = p1;
        ply1.push_back(p1);
        seleccionarPersonaje(ply2, 2);
        p2 = personaje_actual_J2;
        seleccionarPersonaje(ply1, 1);
        p1 = personaje_actual_J1;
        if(p1.ambiente.Nombre != ambienteJuego.Nombre && p2.ambiente.Nombre == ambienteJuego.Nombre) {
            turno_jugador1 = true;
            turno_jugador2 = false;
        } else if (p1.ambiente.Nombre == ambienteJuego.Nombre && p2.ambiente.Nombre != ambienteJuego.Nombre) {
            turno_jugador1 = false;
            turno_jugador2 = true;
        } else {
            aleatorio2 = rand() % 2;
            if(aleatorio2 == 0) {
                turno_jugador1 = true;
                turno_jugador2 = false;
            } else {
                turno_jugador1 = false;
                turno_jugador2 = true;
            }
        }
    }
    
    EmpezarJuego(ambienteJuego, p1, p2);
}

//------------------------------------------------------------------------------------------------------------------------
//Codigo

int main() {

    //Para randomizar

    srand(static_cast<unsigned int>(time(nullptr)));

    //Lectura de archivo

    int cantidad;
    string linea;
    string x;
    JugadorBatalla aux;


    //Lectura del ambiente

    ifstream archivoAmbientes("ambiente.inv");
    if (!archivoAmbientes.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<Ambiente> ambientes_introducidos;
    archivoAmbientes >> cantidad;
    archivoAmbientes.ignore();

    while(getline(archivoAmbientes,linea)) {
        Ambiente a;
        if(linea == "--");
        else {
            a.Nombre = linea;
            InsertarAmbiente(&lugar,a);
        }
    }

    archivoAmbientes.close();


    //Lectura de las especies


    ifstream archivoEspecies("especies.inv");
    if (!archivoEspecies.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    archivoEspecies >> cantidad;
    archivoEspecies.ignore();

    for (int i = 0; i < cantidad; i++) {
        Especies e;
        getline(archivoEspecies, linea);
        x = linea;
        getline(archivoEspecies, linea); 
        e.nombre = linea;

        getline(archivoEspecies, linea); 
        size_t found = linea.find(":");
        if (found!= string::npos) {
            string energiaStr = linea.substr(found + 1);
            e.Energia = stoi(energiaStr);
        }

        getline(archivoEspecies, linea); 
        found = linea.find(":");
        if (found!= string::npos) {
            string saludStr = linea.substr(found + 1);
            e.Salud = stoi(saludStr);
        }

        getline(archivoEspecies, linea); 
        e.ambiente.Nombre = linea;

        InsertarEspecie(&especie, e);
    }

    archivoEspecies.close();


//Lectura de los Accesorios

    ifstream archivoAccesorios("accesorios.inv");
    if (!archivoAccesorios.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    archivoAccesorios >> cantidad;
    archivoAccesorios.ignore();

    for(int i = 0; i < cantidad; i++) {
        Accesorios ac;
        getline(archivoAccesorios, linea);
        x = linea;
        getline(archivoAccesorios, linea);
        ac.Nombre = linea;
        getline(archivoAccesorios, linea);
        size_t found = linea.find(":");
        if (found!= string::npos) {
            string tipoStr = linea.substr(found + 1);
            ac.Tipo = tipoStr;
        }

        getline(archivoAccesorios, linea); 
        size_t found2 = linea.find(":");
        if (found2!= string::npos) {
            string valorStr = linea.substr(found2 + 1);
            ac.Valor = stoi(valorStr);
        }

        getline(archivoAccesorios, linea);
        size_t found3 = linea.find(":");
        if (found3!= string::npos) {
            string recuperacionStr = linea.substr(found3 + 1);
            ac.Tipo2 = recuperacionStr;
        }

        getline(archivoAccesorios, linea); 
        size_t found5 = linea.find(":");
        if (found5!= string::npos) {
            string energiaStr = linea.substr(found5 + 1);
            ac.Energia = stoi(energiaStr);
        }

        getline(archivoAccesorios, linea); 
        size_t found4 = linea.find(":");
        if (found4!= string::npos) {
            string contenedorStr = linea.substr(found4 + 1);
            ac.Contenedor = stoi(contenedorStr);
        }

        InsertarAccesorio(&accesorio, ac);
    }

    archivoAccesorios.close();


    //Variables de Jugador


    vector<Jugador> personajes;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    //Declaracion de Variables

    int main = 1; 
    int cont_j1 = 0;
    int cont_j2 = 0;
    int longitud_ambientes;
    int rn;
    int seleccion_personaje;
    Ambiente ambiente_jugar;
    vector<Jugador> j1;
    vector<Jugador> j2;

    //Main

    //Inicio
    
    cout<<"▪   ▐ ▄  ▌ ▐· ▄▄▄· .▄▄ · ▪         ▐ ▄     ▄▄▄ .▐▄• ▄ ▄▄▄▄▄▄▄▄   ▄▄▄· ▄▄▄▄▄▄▄▄ .▄▄▄  ▄▄▄  ▄▄▄ ..▄▄ · ▄▄▄▄▄▄▄▄  ▄▄▄ ."<< endl;
    cout<<"██ •█▌▐█▪█·█▌▐█ ▀█ ▐█ ▀. ██ ▪     •█▌▐█    ▀▄.▀· █▌█▌▪•██  ▀▄ █·▐█ ▀█ •██  ▀▄.▀·▀▄ █·▀▄ █·▀▄.▀·▐█ ▀. •██  ▀▄ █·▀▄.▀·"<< endl;
    cout<<"▐█·▐█▐▐▌▐█▐█•▄█▀▀█ ▄▀▀▀█▄▐█· ▄█▀▄ ▐█▐▐▌    ▐▀▀▪▄ ·██·  ▐█.▪▐▀▀▄ ▄█▀▀█  ▐█.▪▐▀▀▪▄▐▀▀▄ ▐▀▀▄ ▐▀▀▪▄▄▀▀▀█▄ ▐█.▪▐▀▀▄ ▐▀▀▪▄"<< endl;
    cout<<"▐█▌██▐█▌ ███ ▐█ ▪▐▌▐█▄▪▐█▐█▌▐█▌.▐▌██▐█▌    ▐█▄▄▌▪▐█·█▌ ▐█▌·▐█•█▌▐█ ▪▐▌ ▐█▌·▐█▄▄▌▐█•█▌▐█•█▌▐█▄▄▌▐█▄▪▐█ ▐█▌·▐█•█▌▐█▄▄▌"<< endl;
    cout<<"▀▀▀▀▀ █▪. ▀   ▀  ▀  ▀▀▀▀ ▀▀▀ ▀█▄▀▪▀▀ █▪     ▀▀▀ •▀▀ ▀▀ ▀▀▀ .▀  ▀ ▀  ▀  ▀▀▀  ▀▀▀ .▀  ▀.▀  ▀ ▀▀▀  ▀▀▀▀  ▀▀▀ .▀  ▀ ▀▀▀ "<< endl;
    cout<<"Elaborado por: Pedro Sabatino, Fernando Álvarez y Andrés De La Rosa"<< endl<< endl<< endl;
        



    while(main==1) {
        //Menu de principal
        Especies nuevaEspecie;
        Accesorios nuevoAccesorio;
        Ambiente nuevoAmbiente;
        int posicion;
        int posicionEliminar;
        int seleccion;
        int parte_razas = 1;
        int parte_accesorios = 1;
        int parte_ambientes = 1;
        int seleccion_personaje_1 = 0;
        int seleccion_personaje_2 = 0;
        int seleccion_especies;
        int seleccion_accesorios;
        string seleccion_nombre;
        



        cout << "***********     MENU DE INICIO     **********" << endl;
        cout << "---------------------------------------------" <<endl;
        cout << "1.- Ver las razas" << endl;
        cout << "2.- Ver Accesorios" << endl;
        cout << "3.- Ver Ambientes" << endl;
        cout << "4.- Jugar" << endl;
        cout << "5.- Salir" << endl << endl;
        cout << "---------------------------------------------" <<endl;
        cout << "¿Qué acción quiere realizar?: ";
        cin>> seleccion;
        cout << endl << endl;
        if (cin.fail()) {
            cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }
        //Selector de Opciones
        //Seleccion invalida
        switch(seleccion) {
        //Seleccion 1, razas
        case 1: 
            while(parte_razas==1) {
                if(listaVaciaEspecie(especie) == true)
                    cout << "No hay razas disponibles" << endl << endl;
                else {
                    cout << "Estas son las razas que participan en la guerra: " << endl << endl;
                    MostrarListaEspecies(especie);
                }
                cout << endl << endl;
                //Menu Razas
                int seleccion_raza;
                cout << "***********     MENU DE RAZAS     **********" << endl;
                cout << "--------------------------------------------" <<endl;
                cout << "1.- Agregar raza" << endl;
                cout << "2.- Eliminar raza" << endl;
                cout << "3.- Modificar raza" << endl;
                cout << "4.- Volver" << endl << endl;
                cout << "--------------------------------------------" <<endl;
                cout << "¿Qué acción quiere realizar?: ";
                cin>> seleccion_raza;
                cout << endl << endl;
                if (cin.fail()) {
                    cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    continue;
                }
                //Seleccion de opciones en Razas
                switch(seleccion_raza) {
                case 1: 
                    InsertarEspecie(&especie,PedirEspecie());
                    break;
                case 2:
                    cout << "Ingresa la posición de la especie que quieres eliminar: ";
                    cin >> posicionEliminar;
                    if (cin.fail()) {
                        cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        continue;
                    }
                    EliminarEspecie(&especie,posicionEliminar);
                    break;
                case 3:
                    cout << "Ingresa la posicion de la especie que quieres modificar: ";
                    cin >> posicion;
                    if (cin.fail()) {
                        cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cout << endl << "Ingrese las nuevas modificaciones para las especies" << endl;
                    nuevaEspecie = PedirEspecie();
                    ModificarEspecie(&especie, posicion, nuevaEspecie);
                    break;
                case 4:
                    parte_razas = 0;
                    break;
                default:
                    cout<<"Error, el valor ingresado no es valido" <<endl;
                    break;
                }
            
             }
            break;
        //Seleccion 2, accesorios
        case 2:
            while(parte_accesorios==1) {
                if(listaVaciaAccesorio(accesorio) == true)
                    cout << "No existen accesorios aún." << endl;
                else {
                    cout << "Estos son los accesorios disponibles: " << endl << endl;
                    MostrarListaAccesorio(accesorio);
                }
                cout << endl << endl;
                //Menu Accesorios
                int seleccion_accesorio;
                cout << "***********     MENU DE ACCESORIO     **********" << endl;
                cout << "------------------------------------------------" <<endl;
                cout << "1.- Agregar Accesorio" << endl;
                cout << "2.- Eliminar Accesorio" << endl;
                cout << "3.- Modificar Accesorio" << endl;
                cout << "4.- Volver" << endl << endl;
                cout << "------------------------------------------------" <<endl;
                cout << "¿Qué acción quiere realizar?: ";
                cin>> seleccion_accesorio;
                cout << endl << endl;
                if (cin.fail()) {
                    cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    continue;
                }
                //Seleccion de opciones en Accesorios
                switch(seleccion_accesorio) {
                case 1: 
                    InsertarAccesorio(&accesorio,PedirAccesorio());
                    break;
                case 2:
                    cout << "Ingresa la posicion del accesorio que desea eliminar: ";
                    cin >> posicionEliminar;
                    if (cin.fail()) {
                        cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        continue;
                    }
                    EliminarAccesorio(&accesorio,posicionEliminar);
                    break;
                case 3:
                    cout << "ingresa la posicion del accesorio que quieres modificar: ";
                    cin >> posicion;
                    if (cin.fail()) {
                        cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cout << endl << "Ingrese las nuevas modificaciones para los accesorios" << endl << endl;
                    nuevoAccesorio = PedirAccesorio();
                    ModificarAccesorio(&accesorio, posicion, nuevoAccesorio);
                    break;
                case 4:
                    parte_accesorios = 0;
                    break;
                default:
                    cout<<"Error, el valor ingresado no es valido" <<endl;
                    break;
                }
                
            }
            break;

        //Seleccion 3, ambientes
        case 3:
            while(parte_ambientes==1) {
                if(listaVaciaAmbiente(lugar) == true)
                    cout << "No hay ambientes| disponibles" << endl << endl;
                else {
                    cout << "Estas son las razas que participan en la guerra: " << endl << endl;
                    MostrarListaAmbientes(lugar);
                }
                cout << endl << endl;
                //Menu Accesorios
                int seleccion_ambiente;
                cout << "***********     MENU DE AMBIENTES     **********" << endl;
                cout << "------------------------------------------------" <<endl;
                cout << "1.- Agregar Ambiente" << endl;
                cout << "2.- Eliminar Ambiente" << endl;
                cout << "3.- Modificar Ambiente" << endl;
                cout << "4.- Volver" << endl << endl;
                cout << "------------------------------------------------" <<endl;
                cout << "¿Qué acción quiere realizar?: ";
                cin>> seleccion_ambiente;
                cout << endl << endl;
                if (cin.fail()) {
                    cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    continue;
                }
                //Seleccion de opciones en Accesorios
                switch(seleccion_ambiente) {
                case 1: 
                    InsertarAmbiente(&lugar,PedirAmbiente());
                    break;
                case 2:
                    cout << "ingresa la posicion de la especie que quieres eliminar: ";
                    cin >> posicionEliminar;
                    if (cin.fail()) {
                        cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        continue;
                    }
                    EliminarAmbiente(&lugar,posicionEliminar);
                    break;
                case 3:
                    cout << "ingresa la posicion del Ambiente que quieres modificar: ";
                    cin >> posicion;
                    if (cin.fail()) {
                        cout << "Error, ingrese un valor numérico válido. Intente nuevamente." << endl << endl;
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        continue;
                    }
                    cout << endl << "Ingrese las nuevas modificaciones para el ambiente" << endl;
                    nuevoAmbiente = PedirAmbiente();
                    ModificarAmbiente(&lugar, posicion, nuevoAmbiente);
                    break;
                case 4:
                    parte_ambientes = 0;
                    break;
                default:
                    cout << "Error, el valor ingresado no es valido" << endl;
                    break;
                }
        }
        break;
        //jugar
        case 4:
            //Ingresar los personajes de jugador 1
            cout << endl << "Jugador 1 ingrese sus 3 personajes" << endl << endl;
            while(seleccion_personaje_1 != 3) {
                seleccion_personaje_1 += 1;
                seleccion_accesorios = 0;
                seleccion_especies = 0;
                seleccion_nombre = "";
                vector<Accesorios> mochila;
                Jugador jugador = {};
                Especies especie_seleccionada = {};
                cout << "*************      CREAR NOMBRE     ************" << endl;
                cout << "------------------------------------------------" << endl;
                cout << "Ingrese el nombre de su soldado: ";
                while (!(cin >> seleccion_nombre) or BuscarNombre(personajes, seleccion_nombre) == true) {
                    cout << "Error, ingreso un valor invalido o el nombre ya ha sido usado. Intente nuevamente." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << endl;
                cout << "***********     SELECCIONAR RAZAS     **********" << endl;
                cout << "------------------------------------------------" << endl;
                MostrarListaEspecies(especie);
                cout << "------------------------------------------------" << endl;
                cout << "Seleccione una raza: ";
                while (!(cin >> seleccion_especies)) {
                    cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << endl;
                especie_seleccionada = BuscarEspeciePorPosicion(especie, seleccion_especies);
                cout << "La raza seleccionada es: ";
                cout << endl << especie_seleccionada.nombre << ", " << especie_seleccionada.Energia << ", " << especie_seleccionada.Salud;
                cout << ", " << especie_seleccionada.ambiente.Nombre << endl << endl;
                cout << "************     CREAR MOCHILA     ***********" << endl;
                cout << "----------------------------------------------" << endl;
                for(int i = 0; i < 5; ++i){
                    MostrarListaAccesorio(accesorio);
                    cout << endl << "ingrese la posicion del accesorio a agregar ";
                    while (!(cin >> seleccion_accesorios)) {
                        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << endl << endl;
                    mochila.push_back(BuscarAccesorioPorPosicion(accesorio, seleccion_accesorios));
                    cout << "Ha seleccionado: " <<mochila[i].Nombre << endl << endl;
                }
                jugador.Nombre = seleccion_nombre;
                jugador.Raza = especie_seleccionada;
                jugador.Mochila = mochila;
                jugador.Fidelidad = "Desconocido";
                personajes.push_back(jugador);
            }

            cout << endl;

            cout << endl << "Jugador 2 ingrese sus 3 personajes" << endl << endl;
            while(seleccion_personaje_2 != 3) {
                seleccion_personaje_2 += 1;
                seleccion_accesorios = 0;
                seleccion_especies = 0;
                seleccion_nombre = "";
                vector<Accesorios> mochila;
                Jugador jugador = {};
                Especies especie_seleccionada = {};
                cout << "*************      CREAR NOMBRE     ************" << endl;
                cout << "------------------------------------------------" << endl;
                cout << "Ingrese el nombre de su soldado: ";
                while (!(cin >> seleccion_nombre) or BuscarNombre(personajes, seleccion_nombre) == true) {
                    cout << "Error, ingreso un valor invalido o el nombre ya ha sido usado. Intente nuevamente." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << endl;
                cout << "***********     SELECCIONAR RAZAS     **********" << endl;
                cout << "------------------------------------------------" << endl;
                MostrarListaEspecies(especie);
                cout << "------------------------------------------------" << endl;
                cout << "Seleccione una raza: ";
                while (!(cin >> seleccion_especies)) {
                    cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << endl;
                especie_seleccionada = BuscarEspeciePorPosicion(especie, seleccion_especies);
                cout << "La raza seleccionada es: ";
                cout << endl << especie_seleccionada.nombre << ", " << especie_seleccionada.Energia << ", " << especie_seleccionada.Salud;
                cout << ", " << especie_seleccionada.ambiente.Nombre << endl << endl;
                cout << "************     CREAR MOCHILA     ***********" << endl;
                cout << "----------------------------------------------" << endl;
                for(int i = 0; i < 5; ++i){
                    MostrarListaAccesorio(accesorio);
                    cout << endl << "Ingrese la posicion del accesorio a agregar: ";
                    while (!(cin >> seleccion_accesorios)) {
                        cout << "Error, ingrese un valor válido. Intente nuevamente." << endl << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << endl << endl;
                    mochila.push_back(BuscarAccesorioPorPosicion(accesorio, seleccion_accesorios));
                    cout << "Ha seleccionado: " << mochila[i].Nombre << endl << endl;
                }
                jugador.Nombre = seleccion_nombre;
                jugador.Raza = especie_seleccionada;
                jugador.Mochila = mochila;
                jugador.Fidelidad = "Desconocida";
                personajes.push_back(jugador);
            }

            cout << endl << "Presione cualquier tecla ver los personajes creados por el jugador 1...";
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << endl << endl << "Jugador 1:" << endl << endl << endl;
            for(int j = 0; j < 3; ++j) {
                cout << "Soldado " << j+1 << ":" << endl << endl;
                cout << "Nombre: " << personajes[j].Nombre << endl;
                cout << "Raza: " << personajes[j].Raza.nombre << endl;
                cout << "Mochila: " << endl;
                for(int k = 0; k < personajes[j].Mochila.size(); ++k) {
                    cout << personajes[j].Mochila[k].Nombre << endl;
                }
                cout << endl;
            }

            cout << endl << "Presione cualquier tecla ver los personajes creados por el jugador 2...";
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << endl << endl << "Jugador 2:" << endl << endl << endl;
            for(int j = 3; j < 6; ++j) {
                cout << "Soldado " << j-2 << ":" << endl << endl;
                cout << "Nombre: " << personajes[j].Nombre << endl;
                cout << "Raza: " << personajes[j].Raza.nombre << endl;
                cout << "Mochila: " << endl;
                for(int k = 0; k < personajes[j].Mochila.size(); ++k) {
                    cout << personajes[j].Mochila[k].Nombre << endl;
                }
                cout << endl << endl;
            }

            cout << endl << "Presione cualquier tecla para continuar con el juego...";
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//-----------------------------------------------------------------------------------------
    cout << endl << "███████ ███    ███ ██████  ██ ███████ ███████  █████      ███████ ██               ██ ██    ██ ███████  ██████   ██████  " << endl;
            cout << "██      ████  ████ ██   ██ ██ ██         ███  ██   ██     ██      ██               ██ ██    ██ ██      ██       ██    ██ " << endl;
            cout << "█████   ██ ████ ██ ██████  ██ █████     ███   ███████     █████   ██               ██ ██    ██ █████   ██   ███ ██    ██ " << endl;
            cout << "██      ██  ██  ██ ██      ██ ██       ███    ██   ██     ██      ██          ██   ██ ██    ██ ██      ██    ██ ██    ██ " << endl;
            cout << "███████ ██      ██ ██      ██ ███████ ███████ ██   ██     ███████ ███████      █████   ██████  ███████  ██████   ██████  " << endl<<endl;
           
            cout << "Jugador 1 representa a los humanos" << endl << "Jugador 2 representa a los Andromedanos" << endl << endl;

            for(int i = 0; i < 3; i++) {
                int nr = rand() % personajes.size();
                j1.push_back(personajes[nr]);
                personajes.erase(personajes.begin() + nr);
            }

            for(int i = 0; i < 3; i++) {  
                int nr = rand() % personajes.size();
                j2.push_back(personajes[nr]);
                personajes.erase(personajes.begin() + nr);
            }

            cout << endl << "Sus personajes han sido randomizados, presione cualquier tecla para ver los nuevos personajes: " << endl << endl;
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "========JUGADOR 1:========" << endl;
            for(int j = 0; j < j1.size(); ++j) {
                cout << "Soldado " << j+1 << ":" << endl << endl;
                cout << "Nombre: " << j1[j].Nombre << endl;
                cout << "Raza: " << j1[j].Raza.nombre << endl;
                cout << "Mochila: " << endl;
                for(int k = 0; k < j1[j].Mochila.size(); ++k) {
                    cout << j1[j].Mochila[k].Nombre << endl;
                }
                cout << endl;
            }

            cout << endl << "Presione cualquier tecla para ver los personajes del jugador 2." << endl;
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "========JUGADOR 2:========" << endl;
            for(int j = 0; j < j2.size(); ++j) {
                cout << "Soldado " << j+1 << ":" << endl << endl;
                cout << "Nombre: " << j2[j].Nombre << endl;
                cout << "Raza: " << j2[j].Raza.nombre << endl;
                cout << "Mochila: " << endl;
                for(int k = 0; k < j2[j].Mochila.size(); ++k) {
                    cout << j2[j].Mochila[k].Nombre << endl;
                }
                cout << endl;
            }
            
            cout << endl << "Presione cualquier tecla para continuar." << endl;
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            longitud_ambientes = LongitudListaAmbientes(lugar);
            aleatorio1 = rand() % longitud_ambientes;
            ambiente_jugar = BuscarAmbientePorPosicion(lugar, aleatorio1);
            
            cout << endl << "El ambiente es: " << ambiente_jugar.Nombre;

            for(int i = 0; i < j1.size(); i++) {
                aux.Nombre = j1[i].Nombre;
                aux.Salud = j1[i].Raza.Salud;
                aux.Mochila = j1[i].Mochila;
                aux.Energia = j1[i].Raza.Energia;
                aux.ambiente = j1[i].Raza.ambiente;
                aux.Contenedor = 0;
                aux.haPeleado = false;
                ply1.push_back(aux);
            }

            for(int i = 0; i < j2.size(); i++) {
                aux.Nombre = j2[i].Nombre;
                aux.Salud = j2[i].Raza.Salud;
                aux.Mochila = j2[i].Mochila;
                aux.Energia = j2[i].Raza.Energia;
                aux.ambiente = j2[i].Raza.ambiente;
                aux.Contenedor = 0;
                aux.haPeleado = false;
                ply2.push_back(aux);
            }


            seleccionarPersonaje(ply1,1);

            seleccionarPersonaje(ply2,2);

            if(personaje_actual_J1.ambiente.Nombre != ambiente_jugar.Nombre && personaje_actual_J2.ambiente.Nombre == ambiente_jugar.Nombre) {
            turno_jugador1 = true;
            turno_jugador2 = false;
            } else if (personaje_actual_J1.ambiente.Nombre == ambiente_jugar.Nombre && personaje_actual_J2.ambiente.Nombre != ambiente_jugar.Nombre) {
                turno_jugador1 = false;
                turno_jugador2 = true;
            } else {
                aleatorio2 = rand() % 2;
                if(aleatorio2 == 0) {
                    turno_jugador1 = true;
                    turno_jugador2 = false;
                } else {
                    turno_jugador1 = false;
                    turno_jugador2 = true;
                }
            }
            

            EmpezarJuego(ambiente_jugar, personaje_actual_J1, personaje_actual_J2);

            
            
            main=0;
            break;
        
        //Volver
        case 5:
        cout<<" ▄ .▄ ▄▄▄· .▄▄ · ▄▄▄▄▄ ▄▄▄·     ▄▄▌   ▄▄▄·      ▄▄▄·▄▄▄        ▐▄• ▄ ▪  • ▌ ▄ ·.  ▄▄▄· "<<endl;
        cout<<"██▪▐█▐█ ▀█ ▐█ ▀. •██  ▐█ ▀█     ██•  ▐█ ▀█     ▐█ ▄█▀▄ █·▪      █▌█▌▪██ ·██ ▐███▪▐█ ▀█ "<<endl;
        cout<<"██▀▐█▄█▀▀█ ▄▀▀▀█▄ ▐█.▪▄█▀▀█     ██▪  ▄█▀▀█      ██▀·▐▀▀▄  ▄█▀▄  ·██· ▐█·▐█ ▌▐▌▐█·▄█▀▀█ "<<endl;           
        cout<<"██▌▐▀▐█ ▪▐▌▐█▄▪▐█ ▐█▌·▐█ ▪▐▌    ▐█▌▐▌▐█ ▪▐▌    ▐█▪·•▐█•█▌▐█▌.▐▌▪▐█·█▌▐█▌██ ██▌▐█▌▐█ ▪▐▌"<<endl;
        cout<<"▀▀▀ · ▀  ▀  ▀▀▀▀  ▀▀▀  ▀  ▀     .▀▀▀  ▀  ▀     .▀   .▀  ▀ ▀█▄▀▪•▀▀ ▀▀▀▀▀▀▀  █▪▀▀▀ ▀  ▀ "<<endl;


        main=0;
            break;
        default:
            cout<<"Error, ingrese un valor válido."<<endl;
            continue;
    }
    }
    //ELiminar los punteros
    delete especie;
    delete lugar;
    delete accesorio;


    return 0;
    
}