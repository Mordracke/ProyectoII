#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

const int tamano = 10; // Tamano del tablero

// Estructura para representar un jugador
struct Jugador {
    string nombre;
    char tablero[tamano][tamano];
    int puntos; // Puntos acumulados por el jugador
};

// Función para inicializar el tablero con agua ('~')
void inicializarTablero(char tablero[][tamano], int tamano) {
    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            tablero[i][j] = '~';
        }
    }
}

// Función para imprimir el tablero
void imprimirTablero(char tablero[][tamano], int tamano) {
    cout << "  ";
    for (int i = 0; i < tamano; ++i) {
        cout << setw(2) << i;
    }
    cout << endl;
    for (int i = 0; i < tamano; ++i) {
        cout << i << " ";
        for (int j = 0; j < tamano; ++j) {
            cout << setw(2) << tablero[i][j];
        }
        cout << endl;
    }
}

// Función para colocar un barco en el tablero
void colocarBarco(char tablero[][tamano], int fila, int columna, int tamano) {
    if (fila >= 0 && fila < tamano && columna >= 0 && columna < tamano) {
        tablero[fila][columna] = 'B';
    } else {
        cout << "Posicion fuera del tablero." << endl;
    }
}

// Función para disparar a una posición en el tablero del oponente
void disparar(Jugador& jugador, Jugador& oponente, int fila, int columna, int tamano) {
    if (fila >= 0 && fila < tamano && columna >= 0 && columna < tamano) {
        if (oponente.tablero[fila][columna] == 'B') {
            cout << "¡Has hundido un barco en la posicion (" << fila << ", " << columna << ")!" << endl;
            jugador.tablero[fila][columna] = 'X'; // Marcar el barco como hundido en el tablero del jugador
            oponente.tablero[fila][columna] = 'X'; // Marcar el barco como hundido en el tablero del oponente
            // Asignar puntos al jugador por hundir un barco
            jugador.puntos++;
        } else if (oponente.tablero[fila][columna] == '~') {
            cout << "Agua en la posicion (" << fila << ", " << columna << ")." << endl;
            jugador.tablero[fila][columna] = 'O'; // Marcar el agua en el tablero del jugador
            oponente.tablero[fila][columna] = 'O'; // Marcar el agua en el tablero del oponente
        } else {
            cout << "Ya has disparado en la posicion (" << fila << ", " << columna << ")." << endl;
        }
    } else {
        cout << "Posicion fuera del tablero." << endl;
    }
}


// Función para imprimir el estado del juego (tablero del jugador y disparos al oponente)
void imprimirEstadoJuego(Jugador& jugador, Jugador& oponente, int tamano) {
    cout << "Estado del juego para " << jugador.nombre << ":" << endl;
    cout << "Puntos: " << jugador.puntos << endl;
    cout << "Barcos restantes del oponente (" << oponente.nombre << "): ";
    int barcosRestantes = 0;
    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            if (oponente.tablero[i][j] == 'B') {
                barcosRestantes++;
            }
        }
    }
    cout << barcosRestantes << endl;
    cout << "Tablero del jugador:" << endl;
    imprimirTablero(jugador.tablero, tamano);
}

// Función para verificar si el juego ha terminado (cuando un jugador hunde todos los barcos del oponente)
bool juegoTerminado(Jugador& oponente) {
    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            if (oponente.tablero[i][j] == 'B') {
                return false; // quedan barcos en el tablero del oponente
            }
        }
    }
    return true; // Todos los barcos del oponente han sido hundidos
}

// Función para mostrar los puntos de los jugadores de mayor a menor
void mostrarPuntosOrdenados(Jugador jugadores[], int numJugadores) {
    // Ordenar los jugadores por puntos en orden descendente
    for (int i = 0; i < numJugadores - 1; ++i) {
        for (int j = 0; j < numJugadores - i - 1; ++j) {
            if (jugadores[j].puntos < jugadores[j + 1].puntos) {
                swap(jugadores[j], jugadores[j + 1]);
            }
        }
    }
    
    // Mostrar los puntos de los jugadores
    cout << "Puntos de los jugadores (de mayor a menor):" << endl;
    for (int i = 0; i < numJugadores; ++i) {
        cout << jugadores[i].nombre << ": " << jugadores[i].puntos << " puntos" << endl;
    }
}


void interfaz(){
    int opcion;
    Jugador jugadores[3]; // Declaración e inicialización de los jugadores fuera del switch
    string ganador; // Declaración de la variable ganador fuera del switch
    int maxPuntos = 0; // Declaración e inicialización de la variable maxPuntos fuera del switch
    int jugadorActual = 0; // Declaración e inicialización de la variable jugadorActual fuera del switch
    do{
        cout << "BIENVENIDO A BATALLA NAVAL" << endl;
        cout << "ELIGE UNA DE LAS SIGUIENTES OPCIONES: " << endl;
        cout << "1. INICIAR PARTIDA" << endl;
        cout << "2. VER LA MÁXIMA PUNTUACIÓN DE ANTERIORES PARTICIPANTES" << endl;
        cout << "3. SALIR DEL JUEGO" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            // Inicializar jugadores
            for (int i = 0; i < 3; ++i) {
                cout << "Ingrese el nombre del Jugador " << i+1 << ": ";
                cin >> jugadores[i].nombre;
                inicializarTablero(jugadores[i].tablero, tamano);
                jugadores[i].puntos = 0;
            }

            //colocación de barcos
            for (int i = 0; i < 3; ++i) {
                cout << "Jugador " << jugadores[i].nombre << ", coloque sus barcos:" << endl;
                for (int j = 0; j < 3; ++j) {
                    int fila, columna;
                    cout << "Ingrese la fila y columna para el barco " << j + 1 << ": ";
                    cin >> fila >> columna;
                    colocarBarco(jugadores[i].tablero, fila, columna, tamano);
                }
            }

            
            jugadorActual = 0; // Reiniciar el jugador actual
            int otroJugador; // otroJugador dentro del case 1
            while (!juegoTerminado(jugadores[(jugadorActual + 1) % 3])) {
                imprimirEstadoJuego(jugadores[jugadorActual], jugadores[(jugadorActual + 1) % 3], tamano);
                cout << jugadores[jugadorActual].nombre << ", ingrese coordenadas para disparar: ";
                int fila, columna;
                cin >> fila >> columna;
                disparar(jugadores[jugadorActual], jugadores[(jugadorActual + 1) % 3], fila, columna, tamano);

                // Cambiar al siguiente jugador
                jugadorActual = (jugadorActual + 1) % 3;
            }

            // Determinar al ganador basado en los puntos
            maxPuntos = 0; // Reiniciar maxPuntos
            ganador = ""; // Reiniciar el ganador
            for (int i = 0; i < 3; ++i) {
                if (jugadores[i].puntos > maxPuntos) {
                    maxPuntos = jugadores[i].puntos;
                    ganador = jugadores[i].nombre;
                }
            }

            // Mostrar al ganador
            cout << "¡El ganador es: " << ganador << " con " << maxPuntos << " puntos!" << endl;
            break;
        case 2: 
            cout << "Mostrando los puntajes de los jugadores" << endl;
            // Llamar a la función para mostrar los puntos de los jugadores
            mostrarPuntosOrdenados(jugadores, 3); // Suponiendo que tienes 3 jugadores
            break;
        case 3:
            cout << "Saliendo del Juego" << endl;
            cout << "Juego Creado por David Morales"<<endl;
            cout << "Juego Creado por Jojan Acosta"<<endl;
            break;
        default:
            cout << "Opción no valida. Por favor, elija una opción valida." << endl;
            break;
        }
    }while(opcion != 3);
}
int main(){
    interfaz();
    return 0;
}