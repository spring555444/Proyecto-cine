#include <iostream>
using namespace std;

// Definición de estructuras
struct usuario {
    int id;
    bool poseetarjeta;
    int saldotarjeta;
    bool poseereserva;
};

struct Silla {
    char tipo[220];
    int fila;
    int numero;
};

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
    cout << "Ingrese la cédula de la reserva que desea eliminar: ";
    cin >> cedula;

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

// Función para mostrar todas las reservas
void mostrarReservas() {
    if (totalReservas == 0) {
        cout << "No hay reservas para mostrar.\n";
        return;
    }
    
    for (int i = 0; i < totalReservas; i++) {
        cout << "Reserva " << i + 1 << " - Cédula: " << reservas[i].cedula;
        cout << ", Estado de pago: " << (reservas[i].pagada ? "Pagada" : "No pagada") << "\n";
    }
}

// Función principal
int main() {
    int selector, id;
    bool idexist;
    cout << "Bienvenido al menú del cinema.\n";

    do {
        cout << "\n¿Qué te gustaría hacer?\n";
        cout << "1. Crear una tarjeta cinema\n2. Recargar una tarjeta cinema\n3. Crear una reserva\n4. Eliminar una reserva existente\n";
        cout << "5. Pagar una reserva en efectivo\n6. Pagar una reserva con la tarjeta cinema\n7. Visualizar las sillas del cine\n8. Visualizar el dinero en caja\n9. Salir del menú\n";
        cin >> selector;

        switch (selector) {
            case 1:
            {
                while (true) {
                    cout << "Ingresa tu número de I.D. o C.C. (0 para volver al menú principal): ";
                    cin >> id;
                    if (id == 0) {
                        break;
                    }
                    idexist = false;
                    for (int i = 0; i < contador; ++i) {
                        if (ids[i] == id) {
                            idexist = true;
                            break;
                        }
                    }
                    if (idexist) {
                        cout << "Este número de identificación ya tiene asociada una tarjeta.\n";
                    } else {
                        if (contador < MAX_IDS) {
                            ids[contador] = id;
                            contador++;
                            cout << "Su tarjeta de número " << id << " se ha agregado correctamente.\n";
                            break;
                        } else {
                            cout << "Lo sentimos, la base de datos está llena.\n";
                        }
                    }
                }
            }
            break;
            case 2:
            {
                // Lógica para recargar una tarjeta
                string cedula;
                int saldo = 0;
                int montoRecarga;

                cout << "Ingrese la cédula del dueño de la tarjeta: ";
                cin >> cedula;
                cout << "Ingrese el saldo inicial de la tarjeta: ";
                cin >> saldo;

                if (saldo < 70000) {
                    cout << "Saldo inicial inválido. Debe ser al menos 70,000.\n";
                    break;
                }

                char opcion;
                cout << "¿Desea recargar su tarjeta? (s/n): ";
                cin >> opcion;

                if (opcion == 's' || opcion == 'S') {
                    cout << "Ingrese el monto a recargar: ";
                    cin >> montoRecarga;
                    if (montoRecarga % 50000 != 0) {
                        cout << "Monto de recarga inválido.\n";
                        break;
                    }
                    saldo += montoRecarga;
                    cout << "Nuevo saldo: $" << saldo << "\n";
                }

                cout << "Gracias por usar el sistema.\n";
            }
            break;
            case 3:
                agregarReserva();
                break;
            case 4:
                eliminarReserva();
                break;
            case 5:
                // Lógica de pago en efectivo
                break;
            case 6:
                // Lógica de pago con tarjeta
                break;
            case 7:
                // Lógica para visualizar las sillas
                break;
            case 8:
                // Lógica para visualizar el dinero en caja
                break;
            default:
                if (selector != 9)
                    cout << "Opción no válida, ingresa otra opción.\n";
        }
    } while (selector != 9);

    cout << "Gracias.\n";
    return 0;
}