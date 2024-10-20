using namespace std;
#include <iostream>

struct usuario{
    int id;
    bool poseetarjeta;
    int saldotarjeta;
    bool poseereserva;
}

int main()
{
    int selector, id, bloq, MAX_IDS = 1000000, ids[MAX_IDS], contador=0, bloqueador=1, tipo_de_reserva=0;
    bool idexist;
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
                while (1) {
                   cout << "Ingresa tu numero de I.D. o C.C. de lo contrario oprima 0 para volver al menú principal:\n";
                   cin>>id;
                   if (id == 0) 
                   {
                       break; 
                   }
                   idexist = 0;
                   for (int i = 0; i < contador; ++i) 
                   {
                       if (ids[i] == id) 
                        {
                          idexist = 1;
                          break;
                        }
                    }
                    if (idexist==1)
                    {
                       cout << "Este número de identificación ya tiene asociada una tarjeta.\n";
                    }else 
                    {
                       if (contador < MAX_IDS) {
                           ids[contador] = id;
                           contador++;
                           cout << "Su tarjeta de número " << id << " se ha agregado correctamente.\n";
                           break;
                        } else 
                        {
                           cout << "Lo sentimos, la base de datos está llena, no se pueden agregar más tarjetas por el momento.\n";
                        }
                    }
                }
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
                    if (reserva==1)
                       tipo_de_reserva=1;
                    if (reserva==2)
                       tipo_de_reserva=2;
                    cout<<tipo_de_reserva;
                    switch (reserva)
                    {
                        case 1:
                        {
                            cout<<"Ingrese su número de identificación. (0 si desea regresar al menú anterior) \n";
                            
                            cin>>id;
                            if (id==0)
                              break;
                            cout<<"\n¿Cuántas sillas le gustaría reservar? (mínimo 1, máximo 8)\n";
                            cin>>cant1;
                            do
                            {
                                if (cant1>8)
                                {
                                   cant1=0;
                                   cout<<"\nel máximo número de sillas disponibles para reserva son 8, ingrese otra cantidad.\n";
                                   cin>>cant1;
                                }
                                else
                                {
                                   cant2=cant1;
                                }
                            }while(cant1>8);
                            switch(cant2)
                            {
                                case 1:
                                {
                                    cout<<"caso 1";
                                }
                                break;
                                case 2:
                                {
                                    cout<<"caso 2";
                                }
                                break;
                                case 3:
                                {
                                    cout<<"caso 3";
                                }
                                break;
                                case 4:
                                {
                                    cout<<"caso 4";
                                }
                                break;
                                case 5:
                                {
                                    cout<<"caso 5";
                                }
                                break;
                                case 6:
                                {
                                    cout<<"caso 6";
                                }
                                break;
                                case 7:
                                {
                                    cout<<"caso 7";
                                }
                                break;
                                case 8:
                                {
                                    cout<<"caso 8";
                                }
                                break;
                            }
                            cout<<"reserva de "<<cant2<<" sillas, asociada a la id "<< id <<" ha sido creada con exito.";
                            break;
                        }
                        break;
                        case 2:
                        {
                            cout<<"ingrese su número de identificación. (0 si desea regresar al menú anterior)\n";
                            cin>>id;
                            if (id==0)
                            break;
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
                                    case 2:
                                    {
                                        
                                    }
                                    break;
                                    case 3:
                                    {
                                        
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