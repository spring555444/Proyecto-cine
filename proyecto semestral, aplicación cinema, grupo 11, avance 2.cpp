using namespace std;
#include <iostream>
int main()
{
    int selector, id, bloq;
    cout<<"Bienvenido al menú del cinema. \n";
    do
    {
        cout<<"qué te gustaría hacer? \n \n";
        cout<<"1. Crear una tarjeta cinema. \n2. Recargar una tarjeta cinema. \n3. Crear una reserva. \n4. Eliminar una reserva existente. \n5. Pagar una reserva en efectivo. \n6. Pagar una reserva con la tarjeta cinema. \n7. Visualizar las sillas del cine. \n8. Visualizar el dinero en caja. \n9. Salir del menú.\n \n";
        cin>>selector;
        
        switch (selector)
        {
            case 1:
            {
                
            }
            break;
            case 2:
            {
                
            }
            break;
            case 3:
            {
                int reserva, cant1, cant2;
                cout<<"\n \nQué tipo de asiento te gustaría reservar?\n \n";
                do
                {
                    cout<<"1. Sillas generales: $8,000. \n2. Sillas Preferenciales: $11,000. \n \n3. Para regresar al menú principal. \n \n";
                    cin>>reserva;
                    switch (reserva)
                    {
                        case 1:
                        {
                            cout<<"Ingrese su número de identificación. \n";
                            cin>>id;
                            cout<<"\n¿Cuántas sillas le gustaría reservar? (mínimo 1, máximo 8)";
                            cin>>cant1;
                            if(cant1>8)
                              cout<<"\nel máximo número de sillas disponibles para reserva son 8, ingrese otro número.\n";
                            else
                              cant2=cant1;
                            do
                            {
                                switch(cant2)
                                {
                                    case 1:
                                    {
                                        
                                    }
                                    break;
                                }
                            }while(cant2<9);
                        }
                        break;
                        case 2:
                        {
                            cout<<"ingrese su número de identificación. \n";
                            cin>>id;
                            cout<<"\n¿Cuántas sillas le gustaría reservar? (mínimo 1, máximo 8)";
                            cin>>cant1;
                            if(cant1>8)
                              cout<<"\nel máximo número de sillas disponibles para reserva son 8, ingrese otro número.\n";
                            else
                              cant2=cant1;
                            do
                            {
                                switch(cant2)
                                {
                                    case 1:
                                    {
                                        
                                    }
                                    break;
                                }
                            }while(cant2<9);
                        }
                        break;
                        default:
                        if (reserva!=3)
                            cout<<"\nOpción no valida, ingresa otra opción.\n \n";
                    }
                }while(reserva!=3);
            }
            break;
            case 4:
            {
                
            }
            break;
            case 5:
            {
                
            }
            break;
            case 6:
            {
                
            }
            break;
            case 7:
            {
                
            }
            break;
            case 8:
            {
                
            }
            break;
            default:
               if(selector!=9)
                 cout<<"\nOpción no valida, ingresa otra aopción. \n";
        }
    }while(selector!=9);
    cout<<"Gracias.";
}