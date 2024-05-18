#include <iostream>
#include <vector>
#include <string>

using namespace std;




//Estructuras necesarias




struct Especies{
    string nombre;
    int Energia;
    int Salud;
    string Ambiente;
    string Fidelidad;
};

struct Accesorios {
    string Nombre;
    string Tipo;
    int Valor;
    string Tipo2;
    int Energia;
    int Contenedor;
};

struct Ambiente {
    string Nombre;
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





//Funciones





//Empiezan Funciones de Especies

Especies PedirEspecie(){
    Especies nueva_especie;
    string nuevo_nombre_raza = "";
    int nueva_energia_raza = 0;
    int nueva_salud_raza = 0;
    string nuevo_ambiente_raza = "";
    cout << "Ingresa el nombre de la raza: ";
    cin>> nuevo_nombre_raza;
    nueva_especie.nombre = nuevo_nombre_raza; 
    cout << endl << "Ingresa la energía de la raza: ";
    cin>> nueva_energia_raza;
    nueva_especie.Energia = nueva_energia_raza;
    cout << endl << "Ingresa la salud de la raza: ";
    cin>> nueva_salud_raza;
    nueva_especie.Salud = nueva_salud_raza;
    cout << endl << "Ingresa el ambiente de la raza: ";
    cin>> nuevo_ambiente_raza;
    nueva_especie.Ambiente = nuevo_ambiente_raza;
    string nueva_fidelidad_raza = "Desconocida";
    nueva_especie.Fidelidad = nueva_fidelidad_raza;
    return nueva_especie;
}

NodoEspecie* CrearNodoEspecies(Especies caracteristicas) {
    NodoEspecie *nuevo = new NodoEspecie;
    nuevo->dato = caracteristicas;
    nuevo->siguientePtr = NULL;
    return nuevo;
}

bool listaVaciaEspecie(NodoEspecie *inicio){
    return inicio==NULL;
}

void MostrarListaEspecies(NodoEspecie *inicio){
    NodoEspecie *mover;
    int contador = 0;
    if(!listaVaciaEspecie(inicio)){
        mover = inicio;
        while(mover != NULL) {
            cout << contador << ") " << mover->dato.nombre << ", " << mover->dato.Energia << ", " << mover->dato.Salud;
            cout << ", " << mover->dato.Ambiente << ", " << mover->dato.Fidelidad << endl;
            mover = mover->siguientePtr;
            contador+=1; 
        }
    }
    else
        cout << "No hay ninguna especie, añada especies para jugar" << endl;
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

void EliminarEspecie(NodoEspecie **inicio, int posicion){
    NodoEspecie *mover = NULL;
    NodoEspecie *anterior = NULL;

    if(listaVaciaEspecie(*inicio))
        cout << "No hay elementos a eliminar";
    else {
        mover = *inicio;
        int contador = 0;
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

void ModificarEspecie(NodoEspecie **inicio, int posicion, Especies nuevasCaracteristicas){
    NodoEspecie *mover = NULL;
    int contador = 0;

    if(listaVaciaEspecie(*inicio))
        cout << "No hay elementos a modificar";
    else {
        mover = *inicio;
        while((mover != NULL) && (contador != posicion)) {
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición ingresada no existe" << endl;
        else {
            mover->dato = nuevasCaracteristicas; // Actualiza las características de la especie
            cout << "Especie modificada exitosamente" << endl;
        }
    }
}

Especies BuscarEspeciePorPosicion(NodoEspecie *cabeza, int posicion){
    NodoEspecie *actual = cabeza;
    int contador = 0;

    while(actual != NULL) {
        if (contador == posicion) {
            return actual->dato;
        }
        actual = actual->siguientePtr;
        contador += 1;
    }

    cout << "No hay raza en la posicion seleccionada, le daremos la especie que este en la ultima posicion" << endl;
    return actual->dato;
}

//Terminan Funciones de Especies







//Empiezan Funciones de Accesorios

Accesorios PedirAccesorio(){
    Accesorios nuevo_accesorio;
    int seleccion_tipo_2 = 0;
    string nuevo_nombre_accesorio = "";
    string nuevo_tipo_accesorio = "";
    int nuevo_valor_accesorio = 0;
    string nuevo_tipo2_accesorio = "";
    int nueva_energia_accesorio = 0;
    int nuevo_contenedor_accesorio = 0;
    cout << "Ingresa el nombre del accesorio: ";
    cin>> nuevo_nombre_accesorio;
    nuevo_accesorio.Nombre = nuevo_nombre_accesorio; 
    cout << endl << "Ingrese el tipo del accesorio: ";
    cin>> nuevo_tipo_accesorio;
    nuevo_accesorio.Tipo = nuevo_tipo_accesorio;
    cout << endl << "Ingresa el valor del accesorio: ";
    cin>> nuevo_valor_accesorio;
    nuevo_accesorio.Valor = nuevo_valor_accesorio;
    cout << endl << "Ingresa la energia de su accesorio: ";
    cin>> nueva_energia_accesorio;
    nuevo_accesorio.Energia = nueva_energia_accesorio;
    cout << endl << "Ingresa el contenedor de su accesorio: ";
    cin>> nuevo_contenedor_accesorio;
    nuevo_accesorio.Contenedor = nuevo_contenedor_accesorio;
    cout << endl << "¿Su accesorio hace uso de un segundo tipo?" << endl <<  "Si es de adaptación indica el ambiente que adapta y si es de supervivencia indica si restaura energía o vida.";
    cout << endl << "1.- Si" << endl << "2.- No" << endl;
    cin>> seleccion_tipo_2;
    if(seleccion_tipo_2 == 1) {
    cout << endl << "ingrese el segundo tipo del accesorio: ";
    cin>> nuevo_tipo2_accesorio;
    }
    else if(seleccion_tipo_2 == 2) {
        nuevo_tipo2_accesorio = "No Tiene";
    }
    else {
        cout << endl << "El número ingresado es invalido, se asignara como segundo tipo (no tiene)";
        nuevo_tipo2_accesorio = "No Tiene";
    }
    nuevo_accesorio.Tipo2 = nuevo_tipo2_accesorio;
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
    int contador = 0;
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
        cout << "No hay elementos a eliminar";
    else {
        mover = *inicio;
        int contador = 0;
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
    int contador = 0;

    if(listaVaciaAccesorio(*inicio))
        cout << "No hay elementos a modificar";
    else {
        mover = *inicio;
        while((mover != NULL) && (contador != posicion)) {
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición ingresada no existe" << endl;
        else {
            mover->dato = nuevasCaracteristicas; // Actualiza las características de la especie
            cout << "Especie modificada exitosamente" << endl;
        }
    }
}

Accesorios BuscarAccesorioPorPosicion(NodoAccesorios *cabeza, int posicion){
    NodoAccesorios *actual = cabeza;
    int contador = 0;

    while(actual != NULL) {
        if (contador == posicion) {
            return actual->dato;
        }
        actual = actual->siguientePtr;
        contador += 1;
    }

    cout << "No hay accesorio en la posicion seleccionada" << endl;
    return cabeza->dato;
}

//Terminan Funciones de Accesorios






//Empiezan Funciones de Ambientes

Ambiente PedirAmbiente(){
    Ambiente nuevo_ambiente;
    string nuevo_nombre_ambiente = "";
    cout << "Ingresa el nombre del Ambiente: ";
    cin>> nuevo_nombre_ambiente;
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
    int contador = 0;
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

void EliminarAmbiente(NodoAmbiente **inicio, int posicion){
    NodoAmbiente *mover = NULL;
    NodoAmbiente *anterior = NULL;

    if(listaVaciaAmbiente(*inicio))
        cout << "No hay elementos a eliminar";
    else {
        mover = *inicio;
        int contador = 0;
        while((mover != NULL) && (contador != posicion)) {
            anterior = mover;
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición excede el numero de Ambientes" << endl;
        else {
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
    int contador = 0;

    if(listaVaciaAmbiente(*inicio))
        cout << "No hay elementos a modificar";
    else {
        mover = *inicio;
        while((mover != NULL) && (contador != posicion)) {
            mover = mover->siguientePtr;
            contador++;
        }
        if(mover == NULL)
            cout << "La posición ingresada no existe" << endl;
        else {
            mover->dato = nuevasCaracteristicas; // Actualiza las características de la especie
            cout << "Ambiente modificado exitosamente" << endl;
        }
    }
}

//Terminan Funciones de Ambientes







//Main

int main() {

    //Predeterminadas

    Especies humano = {"Humano",100,100,"Tierra","Desconocida"};
    Especies marciano = {"Marciano",80,100,"Marte","Desconocida"};
    Especies crypynonianos = {"Cryptnonianos",120,100,"Crypton","Desconocida"};
    Especies andromedanos = {"Andromedanos",100,100,"Andromeda","Desconocida"};

    Accesorios espada = {"Espada","Ataque",30,"No tiene",20,0 };
    Accesorios arco = {"Arco","Ataque",25,"No tiene",10,0 };
    Accesorios espadaSagrada = {"Espada Sagrada","Ataque",70,"No tiene",60,0 };
    Accesorios escudo = {"Escudo","Defensa",0,"No tiene",0,40 };
    Accesorios escudoSagrado = {"Escudo Sagrado","Defensa",0,"No tiene",0,70 };
    Accesorios botiquin = {"Botiquin","Supervivencia",60,"No tiene",0,0 };

    Accesorios adaptacionHumano = {"Adaptador de Gravedad Humana","Adaptación",0,"Tierra",0,0 };
    Accesorios adaptacionMarciano = {"Casco de Marte","Adaptación",0,"Marte",0,0 };
    Accesorios adaptacionCryptoniano = {"Adaptador Cryptoniano","Adaptación",0,"Crypton",0,0 };
    Accesorios adaptacionAndromedano = {"Casco de Andromeda","Adaptación",0,"Andromeda",0,0 };



    //Variables de Jugador

    vector<Jugador> j1;
    vector<Jugador> j2;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    //Declaracion de Variables
    int main = 1;
    NodoEspecie *especie = NULL;
    NodoAccesorios *accesorio = NULL;
    NodoAmbiente *lugar = NULL;
    
    //Asignar Predeterminadas a la lista

    InsertarEspecie(&especie, humano);
    InsertarEspecie(&especie, marciano);
    InsertarEspecie(&especie, crypynonianos);
    InsertarEspecie(&especie, andromedanos);

    InsertarAccesorio(&accesorio, espada);
    InsertarAccesorio(&accesorio, escudo);
    InsertarAccesorio(&accesorio, botiquin);
    InsertarAccesorio(&accesorio, espadaSagrada);
    InsertarAccesorio(&accesorio, escudoSagrado);
    InsertarAccesorio(&accesorio, adaptacionHumano);
    InsertarAccesorio(&accesorio, adaptacionMarciano);
    InsertarAccesorio(&accesorio, adaptacionCryptoniano);
    InsertarAccesorio(&accesorio, adaptacionAndromedano);


    

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
                //Seleccion de opciones en Razas
                switch(seleccion_raza) {
                case 1: 
                    InsertarEspecie(&especie,PedirEspecie());
                    break;
                case 2:
                    cout << "ingresa la posicion de la especie que quieres eliminar: ";
                    cin >> posicionEliminar;
                    EliminarEspecie(&especie,posicionEliminar);
                    break;
                case 3:
                    cout << "ingresa la posicion de la especie que quieres modificar: ";
                    cin >> posicion;

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
                    cout << "No hay razas disponibles" << endl << endl;
                else {
                    cout << "Estas son las razas que participan en la guerra: " << endl << endl;
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
                //Seleccion de opciones en Accesorios
                switch(seleccion_accesorio) {
                case 1: 
                    InsertarAccesorio(&accesorio,PedirAccesorio());
                    break;
                case 2:
                    cout << "ingresa la posicion de la especie que quieres eliminar: ";
                    cin >> posicionEliminar;
                    EliminarAccesorio(&accesorio,posicionEliminar);
                    break;
                case 3:
                    cout << "ingresa la posicion de la especie que quieres modificar: ";
                    cin >> posicion;

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
                //Seleccion de opciones en Accesorios
                switch(seleccion_ambiente) {
                case 1: 
                    InsertarAmbiente(&lugar,PedirAmbiente());
                    break;
                case 2:
                    cout << "ingresa la posicion de la especie que quieres eliminar: ";
                    cin >> posicionEliminar;
                    EliminarAmbiente(&lugar,posicionEliminar);
                    break;
                case 3:
                    cout << "ingresa la posicion del Ambiente que quieres modificar: ";
                    cin >> posicion;

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
                cin>> seleccion_nombre;
                cout << endl << endl;
                cout << "***********     SELECCIONAR RAZAS     **********" << endl;
                cout << "------------------------------------------------" << endl;
                MostrarListaEspecies(especie);
                cout << "------------------------------------------------" << endl;
                cout << "Seleccione una raza: ";
                cin>> seleccion_especies;
                cout << endl << endl;
                especie_seleccionada = BuscarEspeciePorPosicion(especie, seleccion_especies);
                cout << "La raza seleccionada es: ";
                cout << endl << especie_seleccionada.nombre << ", " << especie_seleccionada.Energia << ", " << especie_seleccionada.Salud;
                cout << ", " << especie_seleccionada.Ambiente << ", " << especie_seleccionada.Fidelidad << endl << endl;
                cout << "************     CREAR MOCHILA     ***********" << endl;
                cout << "----------------------------------------------" << endl;
                for(int i = 0; i < 5; ++i){
                    MostrarListaAccesorio(accesorio);
                    cout << endl << "ingrese la posicion del accesorio a agregar ";
                    cin >> seleccion_accesorios;
                    cout << endl << endl;
                    mochila.push_back(BuscarAccesorioPorPosicion(accesorio, seleccion_accesorios));
                    cout << "Ha seleccionado: " <<mochila[i].Nombre << endl;
                }
                jugador.Nombre = seleccion_nombre;
                jugador.Raza = especie_seleccionada;
                jugador.Mochila = mochila;
                j1.push_back(jugador);
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
                cin>> seleccion_nombre;
                cout << endl << endl;
                cout << "***********     SELECCIONAR RAZAS     **********" << endl;
                cout << "------------------------------------------------" << endl;
                MostrarListaEspecies(especie);
                cout << "------------------------------------------------" << endl;
                cout << "Seleccione una raza: ";
                cin>> seleccion_especies;
                cout << endl << endl;
                especie_seleccionada = BuscarEspeciePorPosicion(especie, seleccion_especies);
                cout << "La raza seleccionada es: ";
                cout << endl << especie_seleccionada.nombre << ", " << especie_seleccionada.Energia << ", " << especie_seleccionada.Salud;
                cout << ", " << especie_seleccionada.Ambiente << ", " << especie_seleccionada.Fidelidad << endl << endl;
                cout << "************     CREAR MOCHILA     ***********" << endl;
                cout << "----------------------------------------------" << endl;
                for(int i = 0; i < 5; ++i){
                    MostrarListaAccesorio(accesorio);
                    cout << endl << "Ingrese la posicion del accesorio a agregar: ";
                    cin >> seleccion_accesorios;
                    cout << endl << endl;
                    mochila.push_back(BuscarAccesorioPorPosicion(accesorio, seleccion_accesorios));
                    cout << "Ha seleccionado: " << mochila[i].Nombre << endl;
                }
                jugador.Nombre = seleccion_nombre;
                jugador.Raza = especie_seleccionada;
                jugador.Mochila = mochila;
                j2.push_back(jugador);
            }

            cout << endl << endl << "Jugador 1:" << endl;
            for(int j = 1; j < 4; ++j) {
                cout << "Soldado " << j << ":" << endl << endl;
                cout << "Nombre: " << j1[j].Nombre << endl;
                cout << "Raza: " << j1[j].Nombre << endl;
                cout << "Mochila: " << endl;
                for(int k = 0; j < 5; ++k) {
                    cout << j1[j].Mochila[k].Nombre << ", " << j1[j].Mochila[k].Tipo << ", " << j1[j].Mochila[k].Valor;
                    cout << ", " << j1[j].Mochila[k].Tipo2 << ", " << j1[j].Mochila[k].Energia << ", " << j1[j].Mochila[k].Contenedor << endl;
                }
                cout << endl;
            }


            cout << endl << endl << "Jugador 2:" << endl;
            for(int j = 1; j < 4; ++j) {
                cout << "Soldado " << j << ":" << endl << endl;
                cout << "Nombre: " << j2[j].Nombre << endl;
                cout << "Raza: " << j2[j].Nombre << endl;
                cout << "Mochila: " << endl;
                for(int k = 0; j < 5; ++k) {
                    cout << j2[j].Mochila[k].Nombre << ", " << j2[j].Mochila[k].Tipo << ", " << j2[j].Mochila[k].Valor;
                    cout << ", " << j2[j].Mochila[k].Tipo2 << ", " << j2[j].Mochila[k].Energia << ", " << j2[j].Mochila[k].Contenedor << endl;
                }
                cout << endl;
            }


            
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
        cout<<"Error, ingrese un valor válido";
    }
    }
    return 0;
    

}
