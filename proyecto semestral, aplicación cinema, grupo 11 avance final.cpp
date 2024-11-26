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

//Matriz de la sala de cine.
char sala[11][20]; // 11 filas (A-K) y 20 columnas

// Función para inicializar la sala
void inicializarSala() {
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (i < 8) { // Filas A a H
                sala[i][j] = 'G'; // General
            } else { // Filas I a K
                sala[i][j] = 'P'; // Preferencial
            }
        }
    }
}

//  Req. 3 - Agregar reserva
void agregarReserva() {
    if (totalReservas >= 10) {
        cout << "No se pueden agregar más reservas.\n";
        return;
    }

    Reserva nuevaReserva;

    // Solicitar cédula
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

    // Solicitar la cantidad de sillas a reservar
    int cantidadSillas;
    do {
        cout << "Ingrese la cantidad de sillas a reservar (máximo 8): ";
        cin >> cantidadSillas;
        if (cantidadSillas < 1 || cantidadSillas > 8) {
            cout << "Error: Puede reservar entre 1 y 8 sillas.\n";
        }
    } while (cantidadSillas < 1 || cantidadSillas > 8);

    nuevaReserva.cantidadSillas = cantidadSillas;

    int costoTotal = 0;

    // Seleccionar sillas
    for (int i = 0; i < cantidadSillas; i++) {
        char fila;
        int numero;
        string tipoSilla;

        // Seleccionar fila
        do {
            cout << "Ingrese la fila de la silla " << (i + 1) << " (A-K, mayúscula o minúscula): ";
            cin >> fila;

            // Convertir a mayúscula si es necesario
            if (fila >= 'a' && fila <= 'k') {
                fila = fila - ('a' - 'A'); 
            }

            if (fila < 'A' || fila > 'K') {
                cout << "Error: La fila debe estar entre A y K.\n";
            }
        } while (fila < 'A' || fila > 'K');

        do {
            cout << "Ingrese el número de la silla " << (i + 1) << " (1-20): ";
            cin >> numero;
            if (numero < 1 || numero > 20) {
                cout << "Error: El número debe estar entre 1 y 20.\n";
            }
        } while (numero < 1 || numero > 20);

        int filaIndex = fila - 'A'; 
        int columnaIndex = numero - 1; 

        // Verificar si la silla ya está reservada
        if (sala[filaIndex][columnaIndex] == 'R' || sala[filaIndex][columnaIndex] == 'X') {
            cout << "Error: Esta silla ya está reservada. Elija otra.\n";
            i--; // Repetir este paso
            continue;
        }

        // Determinar tipo de silla y costo
        if (filaIndex < 8) { // General
            tipoSilla = "General";
            costoTotal += 8000;
            sala[filaIndex][columnaIndex] = 'R'; // Marcar como reservada (General)
        } else { // Preferencial
            tipoSilla = "Preferencial";
            costoTotal += 11000;
            sala[filaIndex][columnaIndex] = 'X'; // Marcar como reservada (Preferencial)
        }

        // Guardar información de la silla
        nuevaReserva.sillas[i].fila = filaIndex;
        nuevaReserva.sillas[i].numero = numero;
        nuevaReserva.sillas[i].tipo[0] = tipoSilla[0]; // Guardar carácter inicial
    }

    nuevaReserva.pagada = false;

    reservas[totalReservas] = nuevaReserva;
    totalReservas++;

    // Mostrar detalles de la reserva
    cout << "Reserva creada con éxito.\n";
    cout << "Cédula: " << nuevaReserva.cedula << "\n";
    cout << "Sillas reservadas:\n";

    for (int i = 0; i < cantidadSillas; i++) {
        char filaLetra = nuevaReserva.sillas[i].fila + 'A'; // Convertir índice a letra
        cout << "Silla " << (i + 1) << ": Fila " << filaLetra
             << ", Número " << nuevaReserva.sillas[i].numero
             << ", Tipo: " << (nuevaReserva.sillas[i].tipo[0] == 'G' ? "General" : "Preferencial") << "\n";
    }

    cout << "Costo total de la reserva: $" << costoTotal << "\n";
}

// Req. 7 - Visualizar sillas del cine.
void visualizarSillas() {
    cout << "--(Pantalla)  G:general, P:Preferencial, R:Reservada (General), X:Reservada (Preferencial)\n|\n->";
    for (int i = 0; i < 20; ++i) {
        cout << "==";
    }
    cout << "\n\n";

    for (int i = 0; i < 11; ++i) {
        cout << char('A' + i) << " ";
        for (int j = 0; j < 20; ++j) {
            cout << sala[i][j] << " ";
        }
        cout << endl;
    }
}

// Req. 4 - Eliminar una reserva. 
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

// Req. 5 - Pagar una reserva con efectivo.
void pagarReservaEnEfectivo() {
    int cedula, costoReserva;
    // Solicitar cédula
    do {
        cout << "Ingrese la cédula del cliente que desea pagar la reserva (entre 8 y 11 dígitos): ";
        cin >> cedula;
        if (!validarCedula(cedula)) {
            cout << "Error: La cédula debe tener entre 8 y 11 dígitos.\n";
        }
    } while (!validarCedula(cedula));
    // Buscar reserva asociada
    bool reservaEncontrada = false;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].cedula == cedula && !reservas[i].pagada) {
            reservaEncontrada = true;
            cout << "Reserva encontrada.\n";
            cout << "Ingrese el costo de la reserva: ";
            cin >> costoReserva;
            // Solicitar pago
            int montoPagado;
            do {
                cout << "Ingrese el monto con el que desea pagar (debe ser igual o mayor al costo de la reserva): ";
                cin >> montoPagado;
                if (montoPagado < costoReserva) {
                    cout << "Error: El monto ingresado es insuficiente.\n";
                }
            } while (montoPagado < costoReserva);
            // Calcular cambio
            int cambio = montoPagado - costoReserva;
            // Actualizar la caja y la reserva
            caja += costoReserva;
            reservas[i].pagada = true;
            // Confirmar transacción
            cout << "Pago exitoso. Monto pagado: $" << montoPagado << ".\n";
            if (cambio > 0) {
                cout << "Cambio devuelto: $" << cambio << ".\n";
            }
            cout << "Gracias por su compra.\n";
            break;
        }
    }
    if (!reservaEncontrada) {
        cout << "No se encontró una reserva pendiente para esta cédula.\n";
    }
}

// Req. 1 - Crear una tarjeta.
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

// Req. 2 - Recargar una tarjeta.
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
        // Recarga posterior: mínimo 70,000
        do {
            cout << "Ingrese el monto a recargar (mínimo 50,000): ";
            cin >> montoRecarga;
            if (montoRecarga < 70000) {
                cout << "Monto de recarga inválido. Debe ser al menos 50,000.\n";
            }
        } while (montoRecarga < 70000);
        // Actualizar saldo
        saldos[indice] += montoRecarga;
    }
    // Actualizar la caja
    sumacaja = montoRecarga;
    caja += sumacaja;
    cout << "Recarga exitosa. Nuevo saldo: $" << saldos[indice] << "\n";
    cout << "Gracias por usar el sistema.\n";
}

// Req. 8 - Visualizar dinero en caja.
void visualizarCaja() {
    cout << "El dinero actual en caja es: " << caja << endl;
}

// Req. 6 - Pagar una reserva con la tarjeta CINEMA.
void pagarReservaConTarjeta() {
    int cedula, indice, costoReserva;
    float costoConDescuento;

    // Solicitar cédula
    do {
        cout << "Ingrese la cédula del cliente que desea pagar la reserva (entre 8 y 11 dígitos): ";
        cin >> cedula;
        if (!validarCedula(cedula)) {
            cout << "Error: La cédula debe tener entre 8 y 11 dígitos.\n";
        } else if (!cedulaRegistrada(cedula)) {
            cout << "Esta cédula no tiene una tarjeta registrada.\n";
        }
    } while (!validarCedula(cedula) || !cedulaRegistrada(cedula));

    // Buscar reserva asociada
    bool reservaEncontrada = false;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].cedula == cedula && !reservas[i].pagada) {
            reservaEncontrada = true;
            cout << "Reserva encontrada.\n";
            cout << "Ingrese el costo de la reserva: ";
            cin >> costoReserva;

            // Aplicar descuento del 10% por usar la tarjeta CINEMA
            costoConDescuento = costoReserva * 0.9;

            // Obtener índice de la cédula
            indice = obtenerIndiceCedula(cedula);
            if (indice == -1) {
                cout << "Error interno: No se encontró la cédula en la base de datos.\n";
                return;
            }

            // Verificar saldo suficiente
            if (saldos[indice] >= costoConDescuento) {
                saldos[indice] -= costoConDescuento;
                caja += costoConDescuento; // Añadir a la caja
                reservas[i].pagada = true;
                cout << "Pago exitoso con descuento del 10%. Monto pagado: $" << costoConDescuento << ".\n";
                cout << "Su nuevo saldo es: $" << saldos[indice] << ".\n";
                cout << "Gracias por usar la tarjeta CINEMA.\n";
            } else {
                cout << "Saldo insuficiente para pagar la reserva con descuento.\n";
            }
            break;
        }
    }

    if (!reservaEncontrada) {
        cout << "No se encontró una reserva pendiente para esta cédula.\n";
    }
}

int main() {
    cout << "Proyecto semestral - aplicación cinema";
    cout << "\nintegrantes:";
    cout << "\n-Alisson Mariam Pérez Acosta.";
    cout << "\n-Ángel David Martínez Cruz.";
    cout << "\n-Kevin Alejandro Muñoz Nasmin.";
    cout << "\n-Jaider Adrian Rueda Córdoba.";
    cout << "\n-Veronica Torres Zamora.";
    cout << "\nBienvenido a CINEMA, por favor eliga una opción.\n";

    do {
        cout << "\n¿Qué te gustaría hacer?\n";
        cout << "1. Crear una tarjeta CINEMA\n2. Recargar una tarjeta CINEMA\n3. Crear una reserva\n4. Eliminar una reserva existente\n";
        cout << "5. Pagar una reserva en efectivo\n6. Pagar una reserva con la tarjeta CINEMA\n7. Visualizar las sillas del cine\n8. Visualizar el dinero en caja\n9. Salir del menú\n";
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
                pagarReservaEnEfectivo();
                break;
            case 6:
                pagarReservaConTarjeta();
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
