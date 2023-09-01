#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20
/*? añadir un nodo a la lista,*/
/*	? eliminarlo de la lista,*/
/*	? guardar la lista completa en un archivo (modo append y binario),*/
/*	? recuperar/leer esa lista del archivo (al momento de iniciar el programa y cuando el*/
/*											usuario lo solicite),*/
/*	? realizar búsquedas de mediciones:*/
/*	? Por el tipo de sensor*/
/*	? Por el valor medido. En el caso del valor medido, especificar si se busca*/
/*	mediciones cuyo valor supere un umbral X (ingresado por teclado) o*/
/*	mediciones menores a X umbral o mediciones de exactamente el mismo*/
/*	valor.*/
/*	? Mostrar el contenido de la lista para visualizar todos sus elementos*/
/*	? Mostrar la lista ordenada cronológicamente según la fecha de la medición*/
/*	(dd/mm/aaaa).*/
struct fecha{
int dia;
int mes;
int anio;
};
struct hora{
	int horas;
	int minutos;
};

struct sensores{
	char marca_sensor[50];
	char tipo[50];
	char unidad_medida[10];
	
}sensor[3];
struct mediciones{
	int nro_med;
	struct sensores modulo;
	struct fecha date;
	struct hora horario;
	int valor;
	char comentarios[300];
	struct mediciones *next;
	struct mediciones *prev;
};


struct mediciones *nuevo(struct mediciones *actual);
void cargar(struct mediciones *actual);
void imprimir(struct mediciones *actual);
struct mediciones *borrar(int i,struct mediciones *actual);
void archivo(struct mediciones *actual);
void leerarchivo(struct mediciones *nuevalista);
void busqueda(struct mediciones *actual);
void busqueda_sensor(struct mediciones *actual,char cad[MAX]);
void busqueda_valor(struct mediciones *actual,int valor,int opc);
void burbuja(struct mediciones *actual);//si la quisiera imprimir necesito la nueva cabecera por eso no es void
int intercambiar(struct mediciones *anterior,struct mediciones *siguiente);
int main(int argc, char *argv[]) {
	
	struct mediciones *actual=NULL;//al inicio apunta al nulo,es decir es un alista vacia
	struct mediciones *nuevalista=NULL;
	int opc;
	int i;
	do{
		printf("\n1)añadir un nodo a la lista\n");
		printf("2)eliminar nodo de la lista\n");
		printf("3)guardar la lista completa en un archivo(modoappendybinario)\n");
		printf("4)recuperar/leer esa lista del archivo,\n");
		printf("5)realizar búsquedas:Por el tipo de sensor.Por el valor medido. En el caso del valor medido, especificar si se busca*/mediciones cuyo valor supere un umbral X (ingresado por teclado) o*/mediciones menores a X umbral o mediciones de exactamente el mismo valor.\n");
		printf("6)Mostrar la lista paravisualizar todos sus elementos.\n");
		printf("7)Mostrar la lista ordenada alfabéticamente según el nombre del archivo.\n");
		printf("8)salir.\n");
		scanf("%d",&opc);
		
		switch(opc){
		case 1:
			system("cls");
			actual=nuevo(actual);
			cargar(actual);
			break;
		case 2:
			system("cls");
			printf("A continuacion seimprimen los nodos existentes en la lista\n");
			imprimir(actual); 
			printf("ingrese el nro de medicion que desea eliminar\n");
			scanf("%d",&i);
			actual=borrar(i,actual);//le envio el primer puntero de la lista
			
			break;
		case 3:
			system("cls");
			printf("A continuacion se guardan  los nodos existentes de la lista en un archivo\n");
			archivo(actual);
			break;
		case 4:
			system("cls");
			
			leerarchivo(nuevalista);
			break;
		case 5:
			system("cls");
			busqueda(actual);
			
			break;
		case 6:
			system("cls");
			imprimir(actual);
			break;
		case 7:
			system("cls");
			printf("A continuacion se ordena la lista en orden alfabetico y se imprime en pantalla\n");
			burbuja(actual);//le envio la cabecera actual,para que burbuja la modifque o no.
			imprimir(actual);
			break;
		case 8:
			printf("........Saliendo.......\n");
			
			break;
		default:
			printf("Opcion no valida\n");
			break;
			
		}
		
	}while(opc!=8);
	return 0;
}
struct mediciones *nuevo(struct mediciones *actual){ 
	
struct mediciones *nuevo=(struct mediciones*)malloc(sizeof(struct mediciones));
	if(actual==NULL){
		nuevo->prev=NULL;
		nuevo->next=NULL;
		actual=nuevo;
	}else{
		actual->prev=nuevo;
		nuevo->next=actual;
		nuevo->prev=NULL; 
		actual=nuevo;
	}
	return actual;
}
void cargar(struct mediciones *actual){
	struct mediciones *primero=actual;
	char marca_sensor[50];
	int nro_med;
	char tipo[50];
	char unidad_medida[10];
	int dia;
	int mes;
	int anio;
	int horas;
	int minutos;
	int valor;
	char comentarios[300];
	fflush(stdin);
	printf("Ingrese numero de medicion\n");
	scanf("%d",&nro_med);	
	printf("Ingrese marca de sensor\n");
	fflush(stdin);
	fgets(marca_sensor,50,stdin);
	printf("Ingrese tipo de sensor(que mide)\n");
	fflush(stdin);
	fgets(tipo,50,stdin);
	printf("Ingrese unidad de medida de sensor\n");
	fflush(stdin);
	fgets(unidad_medida,10,stdin);
	printf("Ingrese dia de medicion\n");
	scanf("%d",&dia);
	printf("Ingrese mes de medicion\n");
	scanf("%d",&mes);
	printf("Ingrese anio de medicion\n");
	scanf("%d",&anio);
	printf("Ingrese hora de medicion\n");
	scanf("%d",&horas);
	printf("Ingrese minutos de medicion\n");
	scanf("%d",&minutos);
	printf("Ingrese valor de medicion\n");
	scanf("%d",&valor);
	printf("Ingrese comentarios de medicion\n");
	fflush(stdin);
	fgets(comentarios,300,stdin);
	
	primero->nro_med=nro_med;
	strcpy(primero->modulo.marca_sensor,marca_sensor);
	strcpy(primero->modulo.tipo,tipo);
	strcpy(primero->modulo.unidad_medida,unidad_medida);
	primero->date.dia=dia;
	primero->date.mes=mes;
	primero->date.anio=anio;
	primero->horario.horas=horas;
	primero->horario.minutos=minutos;
	primero->valor=valor;
	strcpy(primero->comentarios,comentarios);
		
/*		strcpy(primero->modulo.marca_sensor ,medicion[n].modulo.marca_sensor);*/
/*		strcpy(primero->modulo.tipo,medicion[n].modulo.tipo);*/
/*		strcpy(primero->modulo.unidad_medida,medicion[n].modulo.unidad_medida);*/
/*		primero->date.dia=medicion[n].date.dia;*/
/*		primero->date.mes=medicion[n].date.mes*/
/*		primero->.date.anio=medicion[n].date.anio;*/
/*		primero->horario.horas=medicion[n].horario.horas;*/
/*		primero->horario.minutos=medicion[n].horario.minutos;*/
/*		primero->valor=medicion[n].valor;*/
/*		strcpy(primero->comentarios,medicion[n].comentarios);*/
		
	
}
void imprimir(struct mediciones *actual){
	struct mediciones *q=actual;
	if(actual==NULL){
		printf("Lista vacia");
	}else{
		while(q!=NULL){
			printf("Numero de medicion %d\n",q->nro_med);
			printf("Sensor: %s\n",q->modulo.marca_sensor);
			printf("Tipo de sensor: %s\n",q->modulo.tipo);
			printf("Unidad de medida de sensor: %s\n",q->modulo.unidad_medida);
			printf("Fecha de medicion:%02d/%02d/%d\n",q->date.dia,q->date.mes,q->date.anio);
			printf("Hora de la medicion: %02d:%02d\n",q->horario.horas,q->horario.minutos);
			printf("Valor medido: %d %s\n",q->valor,q->modulo.unidad_medida);
			printf("Comentarios u observaciones: %s\n",q->comentarios);
		q=q->next;	
		}
	}
}
struct mediciones *borrar(int i,struct mediciones *actual){
	struct mediciones *current;
/*	struct mediciones *siguiente;*/
/*	struct mediciones *anterior;*/
	if(actual==NULL){
		printf("Lista vacia\n");
	}else{
		if(actual!=NULL && actual->nro_med==i){
		current=actual;
		actual=actual->next;//seguir este orden
		/*current->next->prev=NULL;*/ //aca me presento un error por que? tanto asi como si lo pusiera antes de la sentencia anterior
		//hago que el puntero cabecera apunte al sigiente
		free(current);//libero de info el espacio de memoria que ocupaba current
		}
		else{
			current=actual;
			while(current!=NULL && current->nro_med!=i){
				current=current->next;
			}
			if(current==NULL){
				printf("No se encontro medicion con numero  de medicion %d",i);
			}else{
				if(current->nro_med==i){
					current->prev->next=current->next;//ver con los dibujos de los bloques, se entiende mejor  tambien podria ponerle nombres de variables
					current->next->prev=current->prev;
					free(current);
					
					
					
				}else{
					printf("No se encontro medicion con numero  de medicion %d",i);
				}
			}
			
		}
	}
	return actual;
}
	void archivo(struct mediciones *actual){
		struct mediciones *q=actual;//le asigno el puntero cabecera asi no lo modifico por error
		FILE *archivo;
		archivo=fopen("lista_mediciones.bin","ab");//modo append
		if(archivo!=NULL){
			printf("archivo abierto con exito\n");
			while(q!=NULL){
				fwrite(q,sizeof(struct mediciones),1,archivo);
				q=q->next;
			};
			fclose(archivo);	
			printf("Se guardo la lista\n");
		}
		else{
			printf("error al abrir archivo");
		}
	}		
void leerarchivo(struct mediciones *nuevalista){
			
	struct mediciones ia;
	struct mediciones *primero;//
	struct mediciones *anterior=nuevalista; // usare otra varible para manipular lista , es decir p apunta la direccion de mem de lista
	
	FILE *archivo;
	archivo=fopen("lista_mediciones.bin","rb");
	
	if(archivo!=NULL){
		/*fseek(archivo,0,SEEK_SET);*/
		int regresa = fread(&ia,sizeof(struct mediciones),1,archivo);
		while(regresa==1){
			struct mediciones *primero=nuevo(&ia);//me reserva memoria para puntero tipo struct
			
			primero->nro_med=ia.nro_med;
			strcpy(primero->modulo.marca_sensor,ia.modulo.marca_sensor);
			strcpy(primero->modulo.tipo,ia.modulo.tipo);
			strcpy(primero->modulo.unidad_medida,ia.modulo.unidad_medida);
			primero->date.dia=ia.date.dia;
			primero->date.mes=ia.date.mes;
			primero->date.anio=ia.date.anio;
			primero->horario.horas=ia.horario.horas;
			primero->horario.minutos=ia.horario.minutos;
			primero->valor=ia.valor;
			strcpy(primero->comentarios,ia.comentarios);
			
			//regresa = fread(q,sizeof(struct imagenes),1,archivo);
			if(anterior==NULL){ //en la primera iteracion,analizar bien esto porque en reservar ya se solucion. nunca entrta en esta condicion*/
				
				nuevalista = primero;//la nueva cabecera sera el nuevo
			}
			else{
				/* p es el nodo anterior*/
				anterior->prev=primero;// que q sig apunte a los datos que venian de la main
				primero->next=anterior;
				anterior=primero;//ahora p apuntara a la diccion de memoria de q, p siempre sera la cabezera en esta caso por ser una lista tipo filo
				
				
			}
			
			anterior = primero ; // anterior = nuevo ;
			
			printf("---------------------------------------------------------\n");
			printf("Numero de medicion %d\n",anterior->nro_med);
			printf("Sensor: %s\n",anterior->modulo.marca_sensor);
			printf("Tipo de sensor: %s\n",anterior->modulo.tipo);
			printf("Unidad de medida de sensor: %s\n",anterior->modulo.unidad_medida);
			printf("Fecha de medicion:%02d/%02d/%d\n",anterior->date.dia,anterior->date.mes,anterior->date.anio);
			printf("Hora de la medicion: %02d:%02d\n",anterior->horario.horas,anterior->horario.minutos);
			printf("Valor medido: %d %s\n",anterior->valor,anterior->modulo.unidad_medida);
			printf("Comentarios u observaciones: %s\n",anterior->comentarios);	
			
			regresa = fread(&ia,sizeof(struct mediciones),1,archivo);
			
		}
		
		fclose(archivo);
	}else{
		printf("No se pudo abrir el archivo\n");
	}
			
}
void busqueda(struct mediciones *actual){
	struct mediciones *q=actual;//asigno la cabecera
	int opc,valor,c;
	char cad[MAX];
	printf("BUSCAR\n1)Tipo sensor\n2)Valor\n3)salir\n");
	scanf("%d",&opc);
	switch(opc){
	case 1:
		printf("INGRESE EL TIPO DE SENSOR A BUSCAR\n:");
		
		fflush(stdin);
		fgets(cad,MAX,stdin);
		busqueda_sensor(q,cad);
		break;
	case 2:
		printf("INGRESE EL VALOR MEDIDO A BUSCAR\n:");
		scanf("%d",&valor);
		printf("1)Buscar valor medido  igual a %d\n:",valor);
		printf("2)Buscar valor medido mayor a %d\n:",valor);
		printf("3)Buscar valor medido menor a %d\n:",valor);
		scanf("%d",&c);
		busqueda_valor(q,valor,c);
		
		break;
	
	case 3:
		printf("Saliendo...\n:");
		break;
	default:
		printf("opcion no exisente\n:");
		break;
		
	}
}
void busqueda_sensor(struct mediciones *actual,char cad[MAX]){
	struct mediciones *q=actual;
	int cont=0;
	if(q==NULL){
		printf("Lista vacia");
	}else{
		while(q!=NULL){
			if(strcmp(q->modulo.tipo,cad)==0){
				printf("Dato encontrado a continacion se  muestran los datos\n");
				
				printf("Numero de medicion %d\n",q->nro_med);
				printf("Sensor: %s\n",q->modulo.marca_sensor);
				printf("Tipo de sensor: %s\n",q->modulo.tipo);
				printf("Unidad de medida de sensor: %s\n",q->modulo.unidad_medida);
				printf("Fecha de medicion:%02d/%02d/%d\n",q->date.dia,q->date.mes,q->date.anio);
				printf("Hora de la medicion: %02d:%02d\n",q->horario.horas,q->horario.minutos);
				printf("Valor medido: %d %s\n",q->valor,q->modulo.unidad_medida);
				printf("Comentarios u observaciones: %s\n",q->comentarios);
				
				cont++;
			}
			q=q->next;
		};
		if(cont==0){
			printf("No existe ese sensor %s\n ",cad);
		}
	}
}
void busqueda_valor(struct mediciones *actual,int valor,int opc){
	struct mediciones *q=actual;
	int cont=0;
	if(q==NULL){
		printf("Lista vacia");
	}else{
		if(opc==1){
			while(q!=NULL){
				if(q->valor==valor){
					printf("Dato/s encontrado a continacion se  muestran los datos de la/s mediciones de valor %d \n",valor);
					
					printf("Numero de medicion %d\n",q->nro_med);
					printf("Sensor: %s\n",q->modulo.marca_sensor);
					printf("Tipo de sensor: %s\n",q->modulo.tipo);
					printf("Unidad de medida de sensor: %s\n",q->modulo.unidad_medida);
					printf("Fecha de medicion:%02d/%02d/%d\n",q->date.dia,q->date.mes,q->date.anio);
					printf("Hora de la medicion: %02d:%02d\n",q->horario.horas,q->horario.minutos);
					printf("Valor medido: %d %s\n",q->valor,q->modulo.unidad_medida);
					printf("Comentarios u observaciones: %s\n",q->comentarios);
					
					cont++;
				}
				q=q->next;
			};
		}else{
			if(opc==2){
				while(q!=NULL){
					if(q->valor>valor){
						printf("Dato/s encontrado a continacion se  muestran los datos con valor de medicion mayor a %d MB\n",valor);
						
						printf("Numero de medicion %d\n",q->nro_med);
						printf("Sensor: %s\n",q->modulo.marca_sensor);
						printf("Tipo de sensor: %s\n",q->modulo.tipo);
						printf("Unidad de medida de sensor: %s\n",q->modulo.unidad_medida);
						printf("Fecha de medicion:%02d/%02d/%d\n",q->date.dia,q->date.mes,q->date.anio);
						printf("Hora de la medicion: %02d:%02d\n",q->horario.horas,q->horario.minutos);
						printf("Valor medido: %d %s\n",q->valor,q->modulo.unidad_medida);
						printf("Comentarios u observaciones: %s\n",q->comentarios);
						
						cont++;
					}
					q=q->next;
				};
				
			}else{
				if(opc==3){
					while(q!=NULL){
						if(q->valor<valor){
							printf("Dato/s encontrado a continacion se muestran los datos con tamnio menor a %d MB\n",valor);
							
							printf("Numero de medicion %d\n",q->nro_med);
							printf("Sensor: %s\n",q->modulo.marca_sensor);
							printf("Tipo de sensor: %s\n",q->modulo.tipo);
							printf("Unidad de medida de sensor: %s\n",q->modulo.unidad_medida);
							printf("Fecha de medicion:%02d/%02d/%d\n",q->date.dia,q->date.mes,q->date.anio);
							printf("Hora de la medicion: %02d:%02d\n",q->horario.horas,q->horario.minutos);
							printf("Valor medido: %d %s\n",q->valor,q->modulo.unidad_medida);
							printf("Comentarios u observaciones: %s\n",q->comentarios);
								
							cont++;
						}
						q=q->next;
					};
					
				}else{
					printf("la opcion %d no existe\n ",opc);
				}
			}
		}
}
}
void burbuja(struct mediciones *actual){
		struct mediciones *q=actual;
		int intercambio;
		do{
			q=actual;//como cambie solo los datos en las direcciones de memoria y no la direccion de memoria en si puedo hacer esto??
			intercambio=0;
			while(q->next!=NULL){
				if(q->date.anio > q->next->date.anio){
					intercambiar(q,q->next);
					intercambio=1;
				}else{
					if(q->date.anio == q->next->date.anio){
						if(q->date.mes > q->next->date.mes){
							intercambiar(q,q->next);
							intercambio=1;
						}else{
							if(q->date.mes == q->next->date.mes){
								if(q->date.dia > q->next->date.dia){
									intercambiar(q,q->next);
									intercambio=1;
								}
							}
						}
					}
				}
				q=q->next;
			}
		}while(intercambio);
		
	}
	int intercambiar(struct mediciones *anterior,struct mediciones *siguiente){
			//creo variables temporales
			char marca_sensor[50];
			int nro_med;
			char tipo[50];
			char unidad_medida[10];
			int dia;
			int mes;
			int anio;
			int horas;
			int minutos;
			int valor;
			char comentarios[300];
			// a copio los datos de la lista en las v temprorales
			
			
			nro_med=anterior->nro_med;
			strcpy(marca_sensor,anterior->modulo.marca_sensor);
			strcpy(tipo,anterior->modulo.tipo);
			strcpy(unidad_medida,anterior->modulo.unidad_medida);
			dia=anterior->date.dia;
			mes=anterior->date.mes;
			anio=anterior->date.anio;
			horas=anterior->horario.horas;
			minutos=anterior->horario.minutos;
			valor=anterior->valor;
			strcpy(comentarios,anterior->comentarios);
			
			//guardo los datos del siguiente en anterior
			anterior->nro_med=siguiente->nro_med;
			strcpy(anterior->modulo.marca_sensor,siguiente->modulo.marca_sensor);
			strcpy(anterior->modulo.tipo,siguiente->modulo.tipo);
			strcpy(anterior->modulo.unidad_medida,siguiente->modulo.unidad_medida);
			anterior->date.dia=siguiente->date.dia;
			anterior->date.mes=siguiente->date.mes;
			anterior->date.anio=siguiente->date.anio;
			anterior->horario.horas=siguiente->horario.horas;
			anterior->horario.minutos=siguiente->horario.minutos;
			anterior->valor=siguiente->valor;
			strcpy(anterior->comentarios,siguiente->comentarios);
			
			//los datos guardados en las variables temporales que eran del orirginalmente anterior pasaan al puntero siguiente en la lista
			siguiente->nro_med=nro_med;
			strcpy(siguiente->modulo.marca_sensor,marca_sensor);
			strcpy(siguiente->modulo.tipo,tipo);
			strcpy(siguiente->modulo.unidad_medida,unidad_medida);
			siguiente->date.dia=dia;
			siguiente->date.mes=mes;
			siguiente->date.anio=anio;
			siguiente->horario.horas=horas;
			siguiente->horario.minutos=minutos;
			siguiente->valor=valor;
			strcpy(siguiente->comentarios,comentarios);
			return 1;
		}
