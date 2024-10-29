//Requerimiento funcional #1:
// NOMBRE DEL MÉTODO: main/ numProductos/ nombres,precios,cantidades.
// PARÁMETROS: Ninguno/ Ninguno/ Ninguno.
// RETORNO: int/ int/ char.
// DESCRIPCIÓN: Función principal que inicia el programa e imprime el reporte de inventario./ Número total de productos a mostrar en el reporte./ Arreglos que almacenan el nombre, precio y cantidad de cada producto.

//Requerimiento funcional #2:
// NOMBRE DEL MÉTODO: main.
// PARÁMETROS: Ninguno.
// RETORNO: int (0 al terminar).
// DESCRIPCIÓN: Permite consultar el inventario de un producto ingresado por el usuario y muestra la cantidad disponible o indica si no existe.

//Requerimiento funcional #3:
// NOMBRE DEL MÉTODO: main.
// PARÁMETROS: Ninguno.
// RETORNO: int.
// DESCRIPCIÓN: Función principal del programa que inicia el proceso de actualización de inventario, recolecta datos y evalúa condiciones de reabastecimiento y estado de productos recibidos.

//Requerimiento funcional #4:
// NOMBRE DEL MÉTODO: capturarDatosProducto / mostrarInfoProducto.
// PARÁMETROS: Ninguno / Ninguno.
// RETORNO: Ninguno (void) / Ninguno (void).
// DESCRIPCIÓN: Permite ingresar los datos del producto: nombre, cantidad y precio. / Muestra en pantalla la información del producto: nombre, cantidad y precio.

#include "Producto.h"
#include <iostream>
using namespace std;
int main()
{
	int selector;

	do
	{
		cout<<"\nRequerimientos funcionales: \n \n";
		cout<<"1. ";
		    cin>>selector;
		switch (selector)
		{
		case 1:
		{
			struct Producto {
                // Atributos
                string nombre;
                int cantidad;
                float precio;
                // Métodos
                void mostrarInfoProducto();
                void capturarDatosProducto();
            };
			// Método para capturar los datos del producto
            void Producto::capturarDatosProducto()
            {
                cout << "\nIngrese el nombre del producto: ";
                cin >> nombre;
                cout << "Ingrese la cantidad de " << nombre << ": ";
                cin >> cantidad;
                cout << "Ingrese el precio unitario de " << nombre << ": ";
                cin >> precio;
            }
                Producto miProducto;
                // Capturamos datos de un producto
                miProducto.capturarDatosProducto();
                // Mostramos la información del producto ingresado
                miProducto.mostrarInfoProducto();
		}
		break;
		case 2:
		{
			char producto[20]; // Atributo: nombre del producto.
            cout << "Consulta de inventario\nIngrese el nombre del producto (i, j, k):\n";
            cin >> producto;
            if (producto[0] == 'i') 
                cout << "Cantidad disponible: a cantidad.\n";
            else if (producto[0] == 'j') 
                cout << "Cantidad disponible: b cantidad.\n";
            else if (producto[0] == 'k') 
                cout << "Cantidad disponible: b cantidad\n";
            else
                cout << "Producto no existente\n";
		}
		break;
		case 3:
		{
        int decision;
        int productosRecibidos = 0;
        int productosVerificados = 0;
        int almacenamientoActual = 0;
        int reabastecer = 0;
        cout << "Inicio del proceso de actualización de inventario." << endl;
        cout << "Ingrese la cantidad de productos recibidos: "; // productos que llegan nuevos
        cin >> productosRecibidos;
        cout << "Verificando productos..." << endl;
        cout << "Ingrese el almacenamiento actual: "; // lo que ya tenemos
        cin >> almacenamientoActual;
        if (almacenamientoActual < 12) {
            cout << "Es necesario reabastecer. Comprar más productos :)" << endl;
            reabastecer = 1; // Marcamos que se debe reabastecer
        } else {
            cout << "No es necesario comprar más productos." << endl;
        }
        // Decisión adicional en caso de productos defectuosos
        cout << "¿Los productos recibidos están en buen estado? (1 para sí, 0 para no): ";
        cin >> decision;
        if (decision == 0) {
            cout << "Volver a comprar y pedir devolución de productos defectuosos." << endl;
        }
        cout << "Proceso de actualización de inventario completo." << endl;
		}
		break;
		case 4:
		{
            int numProductos = 3; //donde 3 es un número que puede variar dependiendo de la cantidad de productos.
            char nombres[numProductos] = {'i', 'j', 'k'};
            char precios[numProductos] = {'x', 'y', 'z'};
            char cantidades[numProductos] = {'a', 'b', 'c'};
            //donde a, b, c, x, y, z, i, j, k son variables que pueden tomar cualquier valor o nombre modificando el tipo de variable.
            cout<<"Reporte de inventario.\n\n";
            cout << "producto  |  precio  |  cantidad\n";
            cout << "--------------------------------\n";
            
            for (int h = 0; h < numProductos; h++) 
            {
            cout << "    " << nombres[h] << "          " << precios[h] << "           " << cantidades[h] << endl;
            }
		}
		break;
		default:
		{
			if (selector>=5)
				cout<<"\nOpción no valida, intente de nuevo. \n";
		}
		break;
		}
	} while (selector!=5);
}