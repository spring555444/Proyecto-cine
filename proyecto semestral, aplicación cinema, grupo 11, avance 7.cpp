#include <iostream>
using namespace std;

// Definición de estructuras
int selector, id, sumacaja, cambio, caja;
bool idexist;

// Estructura para usuario
struct usuario {
    int id;
    bool poseetarjeta;
    int saldotarjeta;
    bool poseereserva;
};

// Estructura para silla
struct Silla {
    char tipo[220];
    int fila;
    int numero;
};

// Estructura para reserva
struct Reserva {
    int cedula;
    Silla sillas[220];
    int cantidadSillas;
    bool pagada;
};

// Constantes y variables globales
const int MAX_IDS = 1000000;
int ids[MAX_IDS], contador = 0, tipo_de_reserva = 0;
Reserva reservas[220];
int totalReservas = 0;

// Variables para saldos y recargas
int saldos[MAX_IDS] = {0};
bool primeraRecargaFlag[MAX_IDS] = {false};

// Función para validar la cédula
bool validarCedula(int cedula) {
    int digitos = 0;
    int temp = cedula;
    while (temp > 0) {
        temp /= 10;
        digitos++;
    }
    return digitos >= 8 && digitos <= 11;
}

// Función para verificar si una cédula ya está registrada
bool cedulaRegistrada(int cedula) {
    for (int i = 0; i < contador; i++) {
        if (ids[i] == cedula) {
            return true;
        }
    }
    return false;
}

// Función para obtener el índice de una cédula
int obtenerIndiceCedula(int cedula) {
    for (int i = 0; i < contador; i++) {
        if (ids[i] == cedula) {
            return i;
        }
    }
    return -1; // No encontrado
}

// Función para visualizar las sillas
void visualizarSillas() {
    const int filas = 11; // A a K (11 filas)
    const int columnas = 20; // 20 sillas por fila

    // Matriz para la sala
    char sala[filas][columnas];

    // Inicializar la matriz
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i < 8) { // Filas A a H (0 a 7)
                sala[i][j] = 'G'; // General
            } else { // Filas I a K (8 a 10)
                sala[i][j] = 'P'; // Preferencial
            }
        }
    }

    // Mostrar la pantalla
    cout << "--(Pantalla)  G:general, P:Preferencial.\n|\n->";
    for (int i = 0; i < columnas; ++i) {
        cout << "==";
    }
    cout << "\n\n";

    // Mostrar la sala
    for (int i = 0; i < filas; ++i) {
        // Etiqueta de la fila (A a K)
        cout << char('A' + i) << " ";
        for (int j = 0; j < columnas; ++j) {
            cout << sala[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para agregar una reserva
void agregarReserva() {
    if (totalReservas >= 10) {
        cout << "No se pueden agregar más reservas.\n";
        return;
    }

    Reserva nuevaReserva;

    do {
        cout << "Ingrese la cédula del cliente (entre 8 y 11 dígitos): ";
        cin >> nuevaReserva.cedula;
        if (!validarCedula(nuevaReserva.cedula)) {
            cout << "Error: La cédula debe tener entre 8 y 11 dígitos.\n";
        }
    } while (!validarCedula(nuevaReserva.cedula));

    // Verificar si la cédula está registrada
    if (!cedulaRegistrada(nuevaReserva.cedula)) {
        cout << "Esta cédula no tiene una tarjeta registrada. Por favor, cree una tarjeta primero.\n";
        return;
    }

    nuevaReserva.pagada = false;
    nuevaReserva.cantidadSillas = 1;
    nuevaReserva.sillas[0].tipo[0] = 'G';
    nuevaReserva.sillas[0].fila = 1;
    nuevaReserva.sillas[0].numero = 1;

    reservas[totalReservas] = nuevaReserva;
    totalReservas++;
    cout << "Reserva agregada.\n";
}

// Función para eliminar una reserva
void eliminarReserva() {
    int cedula;
    do {
        cout << "Ingrese la cédula de la reserva que desea eliminar (entre 8 y 11 dígitos): ";
        cin >> cedula;
        if (!validarCedula(cedula)) {
            cout << "Error: La cédula debe tener entre 8 y 11 dígitos.\n";
        }
    } while (!validarCedula(cedula));

    // Verificar si la cédula está registrada
    if (!cedulaRegistrada(cedula)) {
        cout << "Esta cédula no tiene una tarjeta registrada.\n";
        return;
    }

    bool reservaEncontrada = false;

    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].cedula == cedula && !reservas[i].pagada) {
            for (int j = i; j < totalReservas - 1; j++) {
                reservas[j] = reservas[j + 1];
            }
            totalReservas--;
            reservaEncontrada = true;
            cout << "Reserva encontrada y eliminada exitosamente.\n";
            break;
        }
    }

    if (!reservaEncontrada) {
        cout << "Reserva no encontrada o ya está pagada, no se puede eliminar.\n";
    }
}

// Función para crear una tarjeta cinema
void crearTarjetacinema() {
    while (true) {
        do {
            cout << "Ingresa tu número de I.D. o C.C. (entre 8 y 11 dígitos, 0 para volver al menú principal): ";
            cin >> id;
            if (id == 0) {
                return;
            }
            if (!validarCedula(id)) {
                cout << "Error: La cédula debe tener entre 8 y 11 dígitos.\n";
            }
        } while (!validarCedula(id));

        if (cedulaRegistrada(id)) {
            cout << "Este número de identificación ya tiene asociada una tarjeta.\n";
        } else {
            if (contador < MAX_IDS) {
                ids[contador] = id;
                saldos[contador] = 0; // Inicializar saldo
                primeraRecargaFlag[contador] = true; // Marcar que aún no se ha recargado
                contador++;
                cout << "Su tarjeta de número " << id << " se ha agregado correctamente.\n";
                break;
            } else {
                cout << "Lo sentimos, la base de datos está llena.\n";
                break;
            }
        }
    }
}

// Función para recargar una tarjeta cinema
void recargarunaTarjetacinema() {
    int cedula;
    int montoRecarga;
    char respuesta;

    do {
        cout << "Ingrese la cédula del dueño de la tarjeta (entre 8 y 11 dígitos): ";
        cin >> cedula;
        if (!validarCedula(cedula)) {
            cout << "Error: La cédula debe tener entre 8 y 11 dígitos.\n";
        } else if (!cedulaRegistrada(cedula)) {
            cout << "Esta cédula no tiene una tarjeta registrada. Por favor, cree una tarjeta primero.\n";
        }
    } while (!validarCedula(cedula) || !cedulaRegistrada(cedula));

    int indice = obtenerIndiceCedula(cedula);
    if (indice == -1) {
        // Esto no debería pasar, pero por seguridad
        cout << "Error interno: cédula no encontrada.\n";
        return;
    }

    if (primeraRecargaFlag[indice]) {
        // Primera recarga: mínimo 70,000
        do {
            cout << "Ingrese el monto a recargar (mínimo 70,000): ";
            cin >> montoRecarga;
            if (montoRecarga < 70000) {
                cout << "Monto de recarga inválido. Debe ser al menos 70,000.\n";
            }
        } while (montoRecarga < 70000);

        // Actualizar saldo y marcar que ya no es la primera recarga
        saldos[indice] += montoRecarga;
        primeraRecargaFlag[indice] = false;
    } else {
        // Recarga posterior: mínimo 50,000
        do {
            cout << "Ingrese el monto a recargar (mínimo 50,000): ";
            cin >> montoRecarga;
            if (montoRecarga < 50000) {
                cout << "Monto de recarga inválido. Debe ser al menos 50,000.\n";
            }
        } while (montoRecarga < 50000);

        // Actualizar saldo
        saldos[indice] += montoRecarga;
    }

    // Actualizar la caja
    sumacaja = montoRecarga;
    caja += sumacaja;

    cout << "Recarga exitosa. Nuevo saldo: $" << saldos[indice] << "\n";
    cout << "Gracias por usar el sistema.\n";
}

// Función para visualizar el dinero en caja
void visualizarCaja() {
    cout << "El dinero actual en caja es: " << caja << endl;
}

// Función principal
int main() {
    cout << "Bienvenido al menú del cinema.\n";

    do {
        cout << "\n¿Qué te gustaría hacer?\n";
        cout << "1. Crear una tarjeta cinema\n2. Recargar una tarjeta cinema\n3. Crear una reserva\n4. Eliminar una reserva existente\n";
        cout << "5. Pagar una reserva en efectivo\n6. Pagar una reserva con la tarjeta cinema\n7. Visualizar las sillas del cine\n8. Visualizar el dinero en caja\n9. Salir del menú\n";
        cin >> selector;

        switch (selector) {
            case 1:
                crearTarjetacinema();
                break;
            case 2:
                recargarunaTarjetacinema();
                break;
            case 3:
                agregarReserva();
                break;
            case 4:
                eliminarReserva();
                break;
            case 5:
                // Lógica de pago en efectivo
                cout << "Funcionalidad aún no implementada.\n";
                break;
            case 6:
                // Lógica de pago con tarjeta
                cout << "Funcionalidad aún no implementada.\n";
                break;
            case 7:
                visualizarSillas();
                break;
            case 8:
                visualizarCaja();
                break;
            case 9:
                cout << "Gracias.\n";
                break;
            default:
                cout << "Opción no válida, ingresa otra opción.\n";
        }
    } while (selector != 9);

    return 0;
}
