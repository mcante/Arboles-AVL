#include <conio.h>
#include <iostream>
#include <stdio.h>

using namespace std;

/*
Estructura:
Dato: clave o espacio donde se almacenará el número solicitado al usuario.
alturaIzq: Mantendrá el valor de la altura izquierda del nodo
alturaDere: Mantendrá el valor de la altura derecha del nodo
fe: Almacenará el factor equilibrio

Punteros:
Izq: Apunta a la izquierda del nodo
Dere: Apunta a la derecha del nodo
padre: Apunta hacía el padre del nodo
*/
typedef struct nodo{
	int dato;
   	struct nodo *izq, *dere, *padre;
   	int fe, alturaIzq, alturaDere;
   	
	char nombre[50];
	char apellido[50];
	char direccion[150];
	
}arbol, *parbol;

int sw=0; // Si es 1= insertar, 0=fe

/*
Punteros Declarados:
raiz: Mantendrá el enlace a la raíz o cabeza de todo el arbol, este puntero se asigna una vez y se modifica si se reestructura o elimina nodo.
nuevo: Almacenará cada nuevo nodo que se cree.
recorrer: recorre el arbol para encontra x nodo 
PadreAB: Mantiene el puntero del padre de un nodo X con el que se esté trabajando.
sHijo: Mantiene el puntero Hijo según el nodo que se esté trabajando.
predecesor: Mantiene el puntero en el nodo que relevará al padre cuando este sea modificado o eliminado.
abuelo: Mantiene el puntero en el padre del padre del nodo que se este trabajando.
hijoHijo: Mantiene el punteror en el hijo del hijo.
*/
arbol *raiz, *nuevo, *recorrer; //Crea las estructuras de tipo puntero.
int buscado=0; //Variable para guardar un valor buscado

arbol *PadreAB, *sHijo, *predecesor, *abuelo, *hijoHijo;

//Recorridos pre, in, post
void preorden(arbol *recorrer);
void inorden(arbol *recorrer);
void postorden(arbol *recorrer);
void insertarNuevo(arbol *recorrer, arbol *nuevo, arbol *padre);
void agregarDatos();
int exiteenArbol(arbol *recorrer, int buscado);
void verArbol(arbol recorrer, int n);
void graficarArbol(arbol, int, int);
void dibujarCuadro(int,int,int,int);
void eliminarNodo(arbol *recorrer, int buscado);
void estadoFactorEquilibrio(arbol *recorrer);
void necesidadEquilibrar(arbol *recorrer);

void vaciarArbol(arbol *recorrer);

//funciones que reestructuran el árbol
void rotarII();
void rotarDD();
void rotarID();
void rotarDI();

parbol nuevoNodo();

//Variable "nuevo" almacenará una nueva hoja para el árbol.
parbol nuevoNodo(){	
	nuevo = new (arbol); //Crea la reserva de espacio en memoria.
	cout<<"Ingrese su NIT: "; cin>>nuevo->dato;
	cout<<"Ingrese su Nombre: "; cin>>nuevo->nombre;
	cout<<"Ingrese su Apellido: "; cin>>nuevo->apellido;
	cout<<"Ingrese su direccion: "; cin>>nuevo->direccion;
	
	
	nuevo->izq=NULL; //Punteros a tierra
	nuevo->dere=NULL; //Punteros a tierra
	nuevo->alturaIzq=0; //Setea en cero la altura izquierda el nodo
	nuevo->alturaDere=0; //Setea en cero la altura derecha el nodo
	nuevo->fe= nuevo->alturaDere-nuevo->alturaIzq; //Calculo del factor equilibrio, podría asignarse el valor cero desde la entrada.
	
	return nuevo;
}

/*Variables:
nuevo: Nueva hoja del arbol
recorrer: Es el puntero que esta señalando hacia la raiz del arbol, esta variable recorre el arbol hasta encontrar un espacio null donde guardar el nuevo nodo.
PadreAB: Mantiene un puntero al nodo anterior para referirse a el como el padre del nuevo nodo.

Funciones involucradas:
Recursivamente se llama así mismo hasta encontrar la ubicación donde se guardará el nuevo nodo, envío como parámetros (La dirección del lado del árbol hacía donde entrará, La nueva hoja, Referencia al padre).
*/
void insertarNuevo(arbol *recorrer, arbol *nuevo, arbol *PadreAB){
	
	if (raiz==NULL){ //Si es el primer nodo entonces la raíz aún será nula porque no existe nada dentro de ella.		
		raiz=nuevo; //Asignar a la raíz el valor del nuevo nodo creado...
		raiz->padre=NULL;
	}else{
		if(nuevo->dato <= recorrer->dato){
			if(recorrer->izq!=NULL){
				PadreAB=recorrer->izq;
				//BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
				insertarNuevo(recorrer->izq, nuevo, PadreAB);
			}else{
				recorrer->izq=nuevo;
				nuevo->padre=PadreAB;
				return;
			}
		}else if (nuevo->dato > recorrer->dato){
			if (recorrer->dere!=NULL){
				PadreAB=recorrer->dere;
				//BBcout<<"Padre: "<<PadreAB->dato<<" Nuevo: "<<nuevo->dato<<endl;
				insertarNuevo(recorrer->dere, nuevo, PadreAB);	
			}else{
				recorrer->dere=nuevo;
				nuevo->padre=PadreAB;
				return;
			}
		}
	}
}

//Funcion que devuelve la altura de las ramas y su factor equilibrio, sólo devuelve valores más no calcula nada.
void estadoFactorEquilibrio(arbol *recorrer){
	if (recorrer != NULL) {
		cout<<"Dato: "<<recorrer->dato<<endl;
		cout<<"Izquierda: "<<recorrer->alturaIzq<< ", Derecha: "<<recorrer->alturaDere<<", Factor de Equilibrio: "<<recorrer->fe<<endl;
	    estadoFactorEquilibrio(recorrer->izq);
	    estadoFactorEquilibrio(recorrer->dere);
	}
}

//Recorrido preOrden
void preorden(arbol *recorrer){
	if (recorrer != NULL) {
		cout<<"\nNIT: "<<recorrer->dato<<endl;
		cout<<"Nombre: "<<recorrer->nombre<<endl;
		cout<<"Apellido: "<<recorrer->apellido<<endl;
		cout<<"Direccion: "<<recorrer->direccion<<endl;
	    preorden(recorrer->izq);
	    preorden(recorrer->dere);
	}
}

//Recorrido InOrden
void inorden(arbol *recorrer){
  	if (recorrer != NULL) {
    	inorden(recorrer->izq);
    	cout<<"\nNIT: "<<recorrer->dato<<endl;
		cout<<"Nombre: "<<recorrer->nombre<<endl;
		cout<<"Apellido: "<<recorrer->apellido<<endl;
		cout<<"Direccion: "<<recorrer->direccion<<endl;
    	inorden(recorrer->dere);
  	}
}

//Recorrido postOrden
void postorden(arbol *recorrer){
  	if (recorrer != NULL) {
    	postorden(recorrer->izq);
    	postorden(recorrer->dere);
    	cout<<"\nNIT: "<<recorrer->dato<<endl;
		cout<<"Nombre: "<<recorrer->nombre<<endl;
		cout<<"Apellido: "<<recorrer->apellido<<endl;
		cout<<"Direccion: "<<recorrer->direccion<<endl;
  	}
}



//Variar el arbol
void vaciarArbol(arbol *recorrer){
  	if (recorrer != NULL) {
    	postorden(recorrer->izq);
    	postorden(recorrer->dere);
    	
    	if (recorrer->dato == raiz->dato){
    		raiz=NULL;
		}else{
			delete(recorrer);//Liberamos la memoria.
		}
  	}
}


//Imprime el árbol en vertical con el fin de no montar valores. La forma de verlo es rotarla 90 grados a la derecha.
/*
El puntero se va hasta el tope de la derecha, mientras va entrando cada vez más a la derecha va aumentando
espacios en "X" para simular la altura o profundidad del nodo en el arbol.
En cada impresión de nodo salta una línea hacía abajo.
De esta forma los nodos nunca se rozan y siempre se mantienen ordenados según la forma del árbol.
*/
void verArbol(arbol *recorrer, int n){
     if(recorrer==NULL)
          return;
     verArbol(recorrer->dere, n+1);

     for(int i=0; i<n; i++)
         cout<<"   ";

     cout<< recorrer->dato <<endl;

     verArbol(recorrer->izq, n+1);
}

//Imprime el árbol en horizontal o en su forma normal.
/*
Utilizando la librería conio.h se puede indicar la ubicación de cada impresión del nodo.
Si entra a la derecha suma 5 espacios en X u 1 espacio en Y, inversamente si va hacia la izquierda resta los
5 espacios en X u 1 espacio en Y.
*/
void graficarArbol(arbol *recorrer, int x, int y){
	
	if(recorrer==NULL)
        return;
        
    graficarArbol(recorrer->dere, x+5, y+1);
    
    gotoxy(x,y); cprintf("%d", recorrer->dato);	
	
    graficarArbol(recorrer->izq, x-5, y+1);
    
}

//Función para buscar un dato en el árbol según si es mayor o menor así mismo va navegando en el arbol hasta encontrar el dato buscado.
int existeNodo=0; //Si es 0 no existe, y si es 1 si existe.
int buscarDato(arbol *recorrer, int buscado){
	if (recorrer==NULL){
		cout<<"Arbol Vacio o el nodo no existe"<<endl;
	}else{
		if(buscado<recorrer->dato){
			buscarDato(recorrer->izq, buscado);
		}else if (buscado>recorrer->dato){
			buscarDato(recorrer->dere, buscado);
		}else{
			existeNodo=1;
			PadreAB=recorrer->padre;
			//ABBcout<<"Padre: "<<PadreAB->dato<<" Nodo buscado: "<<recorrer->dato<<endl;
			cout<<"\n\nEl nodo SI existe"<<endl;
			cout<<"NIT: "<<recorrer->dato<<endl;
			cout<<"Nombre: "<<recorrer->nombre<<endl;
			cout<<"Apellido: "<<recorrer->apellido<<endl;
			cout<<"Direccion: "<<recorrer->direccion<<endl;
			
			
			return existeNodo;
		}
	}
}


//Función que devuelve 0 si el dato existe en un arbol y 1 si no existe.
//Esta función es utilizada por la función Insertar para validar que el nodo que se ingresa no existe en el árbol, si no existe deja insertar.
int exiteenArbol(arbol *recorrer, int buscado){
	if (recorrer==NULL){
		return 1;
	}else{
		if(buscado<recorrer->dato){
			exiteenArbol(recorrer->izq, buscado);
		}else if (buscado>recorrer->dato){
			exiteenArbol(recorrer->dere, buscado);
		}else{
			return 0;
		}
	}
}


//Analizar si el arbol no está vacío y si el nodo a eliminar no es la raíz. 
/*
Si el árbol es vacío lo notifica y si el nodo a eliminar es la raíz también lo indica con el fin de impedir la eliminación y mantener el control.
Si el el arbol no es vacío y nodo a eliminar no es la raíz entonces se llama a eliminar para proceder con el borrado del nodo.
*/
arbol *analizarAB;
void arbolVacio(arbol *recorrer, int buscado){
	analizarAB=recorrer;
	bool existeNodo=false;
	
	if (analizarAB==NULL){
		cout<<"Arbol Vacio"<<endl;
		return;
	}else{
		if(analizarAB->dato==buscado){
			cout<<"No se puede eliminar la Raiz"<<endl;
			return;
		}
		else{
			eliminarNodo(recorrer, buscado);
		}
	}
}


/*
Punteros utilizadas: *recorrer, *PadreAB, *sHijo, *predecesor, *abuelo;
Evalúa cual es los tres casos principales aplica la eliminación
*/
void eliminarNodo(arbol *recorrer, int buscado){
	
	if (recorrer!=NULL){ // Se asegura que el arbol no esté vacío.
		if(buscado < recorrer->dato){ //Si el dato a encontrar es menos que busque por la rama izquierda.
			PadreAB=recorrer; //Se hace una copia de recorrer en el padre antes de la siguiente recursiva...
			eliminarNodo(recorrer->izq, buscado); //Entra recursivamente a la rama izquierda.
		}else if(buscado > recorrer->dato){ //Si el dato a encontrar es mayor que busque por la rama derecha.
			PadreAB=recorrer; //Se hace una copia de recorrer en el padre antes de la siguiente recursiva...
			eliminarNodo(recorrer->dere, buscado); //Entra recursivamente a la rama derecha.
		}else{
					
			//El elemento a eliminar es hoja, aplica al caso 1	
			if (recorrer->izq==NULL && recorrer->dere==NULL){//Condiciones para aplicar al caso 1
				if(PadreAB->izq==recorrer){ //Detectamos si el nodo a eliminar esta a la izquierda del Padre
					PadreAB->izq=NULL; //Si está a la izquierda del Padre solo tendremos que ponerl al Padre en su parte izquierda a Null
					delete(recorrer); //Liberamos la memoria.
				}else{ //Si el nodo no estaba a la izquierda, entonces estará a la derecha del Padre
					PadreAB->dere=NULL; //Ponemos a Null su parte derecha del Padre
					delete(recorrer);//Liberamos la memoria.
				} 
			}else//Sino cumple lo anterior entonces no es hoja...
			
				//Si el nodo a eliminar tiene un hijo se aplica el caso 2
				if((recorrer->izq == NULL && recorrer->dere != NULL)|| (recorrer->izq != NULL && recorrer->dere == NULL)){	//Condiciones para aplicar al caso 2
				
					if(recorrer->izq == NULL && recorrer->dere != NULL){ //Detectando el hijo del nodo a eliminar, si el hijo está a la derecha...
						sHijo=recorrer->dere; //Guardamos la dirección del nodo hijo
						//abuelo=recorrer->padre; //Guardamos la dirección del padre del padre
						if(PadreAB->izq==recorrer){//Detectamos si el nodo a eliminar está a la izquierda de padre...
							PadreAB->izq=sHijo;//Asignamos el nodo hijo del nodo eliminado al Padre en su parte izquierda.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer); //Liberamos la memoria del nodo descartado...
						}else{ //Si el nodo a eliminar no estaba a la izquierda del Padre, entonces estará a la derecha...
							PadreAB->dere=sHijo; //Asignamos el nodo hijo del nodo eliminado al Padre en su parte derecha.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer); //Liberamos la memoria del nodo descartado...
						}	 
					}else{//Si el hijo del nodo a eliminar no estaba a la derecha, entonces estará a la izquierda...
						sHijo=recorrer->izq;//Guardamos la dirección del nodo hijo
						if(PadreAB->izq==recorrer){ //Detectamos si el nodo a eliminar está a la derecha de padre...
							PadreAB->izq=sHijo;//Asignamos el nodo hijo del nodo eliminado al Padre en su parte izquierda.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer);//Liberamos la memoria del nodo descartado...
						}else{ //Si el nodo a eliminar no estaba a la izquierda del Padre, entonces estará a la derecha...
							PadreAB->dere=sHijo;//Asignamos el nodo hijo del nodo eliminado al Padre en su parte derecha.
							sHijo->padre=PadreAB; //Enlazamos al hijo al nuevo padre
							delete(recorrer);//Liberamos la memoria del nodo descartado...
						}
					}
				}else{
					
					//Si no se cumple ninguno de las condiciones anteriores es porque el nodo tiene dos hijos y aplica al caso 3
					
					if(recorrer->izq != NULL && recorrer->dere != NULL){//Condiciones para aplicar al caso 3
						//Encontraremos al predecesor, es decir al nodo más a la derecha de la rama izquierda.
						
						predecesor=recorrer->izq; //asignamos al predecesor la posición izquierda del nodo a eliminar
						//Si el nodo a sustituir al padre no tiene hijos...
						if(predecesor->izq == NULL && predecesor->dere ==NULL){ //Si las partes izquierda y derecha son nulas entonces el nodo a subir no tiene hijos y además es el predecesor que sustituirá al nodo a eliminar.
							recorrer->dato=predecesor->dato; //Asignamos el dato del nuevo predecesor al nodo a eliminar
							recorrer->izq=NULL;
							delete(predecesor);	//Liberamos la memoria del nodo descartado...
						}else{
							predecesor=recorrer->dere; //asignamos al predecesor la posición derecha del nodo a eliminar
							//Si el nodo a sustituir al padre no tiene hijos...
							if(predecesor->izq == NULL && predecesor->dere ==NULL){ //Si las partes izquierda y derecha son nulas entonces el nodo a subir no tiene hijos y además es el predecesor que sustituirá al nodo a eliminar.
								recorrer->dato=predecesor->dato;//Asignamos el dato del nuevo predecesor al nodo a eliminar
								recorrer->dere=NULL;
								delete(predecesor);	//Liberamos la memoria del nodo descartado...
							}else{
								predecesor=recorrer->izq; //asignamos al predecesor la posición izquierda del nodo a eliminar
								if(predecesor->dere==NULL){ //Si el predecesor no tiene hijos a la derecha él será el seleccionado
									recorrer->dato=predecesor->dato; //Asignar el dato de predecesor al nodo a eliminar...
									recorrer->izq=predecesor->izq;//Redireccionamos su parte izquierda para los hijos de ese lado.
									sHijo=predecesor->izq;
									sHijo->padre=recorrer;
									delete(predecesor); //Liberamos la memoria del nodo descartado...
								}else{
									predecesor=recorrer->dere;//Asinamos a predecesor la posición derecha del nodo a eliminar
									if(predecesor->izq==NULL){ //Si el predecesor no tiene hijos a la izquierda, él será el seleccionado.
									recorrer->dato=predecesor->dato; //Asignar el dato de predecesor al nodo a eliminar...
									recorrer->dere=predecesor->dere;//Redireccionamos su parte izquierda para los hijos de ese lado.
									sHijo=predecesor->dere;
									sHijo->padre=recorrer;
									delete(predecesor);//Liberamos la memoria del nodo descartado...
									}else{
										predecesor=recorrer->izq; //Asignamos a predecesor la posición izquierda del nodo a eliminar...
										sHijo=predecesor; //Hacemos una copia de la posición de predecesor 
										
										while(sHijo->dere!=NULL){ //Recorreremos hasta el más a la derecha de la rama izquierda...
											predecesor=sHijo; //Guardar la posición anterior en predecesor y el Hijo estará una posición adelante.
											sHijo=sHijo->dere; //Nos movemos una posición más adelante para el siguiente ciclo.
										}
										//cout<<"\nPredecesor: "<<predecesor->dato<<" sHijo: "<<sHijo->dato<<" Recorrer: "<<recorrer->dato<<endl;
										recorrer->dato=sHijo->dato; //Asignamos al nodo a eliminar el dato de valor mas a la derecha de la rama izquierda
										predecesor->dere=sHijo->izq;//Apuntamos a la derecha al predecesor la dirección izquierda del Hijo
										hijoHijo=sHijo->izq;
										hijoHijo->padre=predecesor;
										//predecesor->izq=NULL; //Quitamos el apuntador del nodo izquierdo del predecesor porque ya no existirá en esa posición
										delete(sHijo);
										
									}
								}
							}
						
						
						}
			}
				}
			}	
	}else{
		cout<<"El nodo no se encuentra en el arbol"<<endl;
	}
}


/*
Se calcula la altura de cada rama y su factor de equilibrio.
La función se va hasta la izquierda del arbol para luego empezar a mandar los datos de altura a los niveles superiores del arbol.
Si la altura de la rama izquierda es mayor que la derecha entonces sube el valor de la rama izquierda para luego calcular el
factor de equilibrio del nodo padre, así hasta llegar al nodo raíz.
*/
int altura(arbol *recorrer){
	if (recorrer == NULL)//Si el nodo está vació entonces que salga.
		return 0 ; //Devuelve el valor cero.
	else{
		recorrer->alturaIzq=altura (recorrer->izq);
		recorrer->alturaDere=altura (recorrer->dere);
		recorrer->fe=recorrer->alturaDere-recorrer->alturaIzq;
		
		if (recorrer->alturaIzq > recorrer->alturaDere)
			return recorrer->alturaIzq + 1;
		else
			return recorrer->alturaDere + 1;
	}
}


/*
Esta función analiza durante una busqueda si existe un factor de equilibrio que sea 2 o -2, si fuera el caso apunta al padre a ese nodo y
luego apunta al hijo para evaluar si el signo de este es positivo o negativo y así determinar el tipo de rotación que se necesita para
balancear el árbol.
El funcionamiento es:
Buscar el valor (-2) o (2) en el factor equilibrio de cualquier nodo del arbol.
Si es (-2) significa que existe desbalance a la izquierda y si el hijo es también (-) negativo significa que es el caso Rotación Izquierda Izquierda, y si fuera positivo es una Rotación Izquierda Derecha.
Si es (2) significa que existe desbalance a la derecha y si el hijo es también (+) positivo significa que es el caso Rotación Derecha Derecha, y si fuera negativo es una Rotación Derecha Izquierda.
*/
//arbol *PadreAB, *sHijo, *predecesor;
void necesidadEquilibrar(arbol *recorrer){ //Con esta función analizo si es necesario equilibrar el árbol, esta función busca el valor -2 o 2.
	if (recorrer != NULL) {
		
		necesidadEquilibrar(recorrer->izq);
	    necesidadEquilibrar(recorrer->dere);

		if ((recorrer->fe==2)||(recorrer->fe==-2)){
			system("cls");
			cout<<"Es necesario equilibrar el arbol"<<endl;
			
			PadreAB=recorrer;
			sHijo=PadreAB->dere;
			
			//Identificar Si es el caso  RDD, Rotación Derecha, Derecha.
			if ((PadreAB->fe>1)&&(sHijo->fe>0)){
				cout<<"Rotacion derecha derecha."<<endl;
				cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
				getch();
				rotarDD();
				altura(raiz);
				return;
			//Identificar Si es el caso  RDI, Rotación Derecha, Izquierda.
			}else if((PadreAB->fe>1)&&(sHijo->fe<0)){
				cout<<"Rotacion derecha izquierda."<<endl;
				cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
				getch();
				rotarDI();
				altura(raiz);
				return;
			}else{
				
				PadreAB=recorrer;
				sHijo=PadreAB->izq;
				
				//Identificar Si es el caso  RII, Rotación Izquierda, Izquierda.
				if((PadreAB->fe<-1)&&(sHijo->fe<0)){
					cout<<"Rotacion izquierda izquierda."<<endl;
					cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
					getch();
					rotarII();
					altura(raiz);
					return;
				//Identificar Si es el caso  RID, Rotación Izquierda, Derecha.	
				}else if((PadreAB->fe<-1)&&(sHijo->fe>0)){
					cout<<"Rotacion izquierda Derecha."<<endl;
					cout<<" Padre: "<<PadreAB->dato<<" Hijo: "<<sHijo->dato<<endl;
					getch();
					rotarID();
					altura(raiz);
					return;
				}
			}
			return;
		}	
	}
}


//Rotación Derecha Izquierda
void rotarDI(){
	if (PadreAB==raiz){
		
		hijoHijo=sHijo->izq; //Ubico al hijo del hijo...
		
		raiz=hijoHijo; //Cambiar el apuntador de la raíz.
		
		hijoHijo->padre=NULL; //Aseguro que el padre de la raíz se quede en NULL
		
		hijoHijo->dere=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		if(sHijo->izq!=NULL){
			sHijo->izq=hijoHijo->izq;
		}else{
			sHijo->izq=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		}
		
		//sHijo->dere=NULL; // Apuntar a Null la parte derecha del hijo, ya que ahora no tendrá Hijos...
		
		hijoHijo->izq=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		if(PadreAB->izq==NULL){
			PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a nu
		}

		PadreAB->dere=NULL; //el antiguo padre debe apuntar ahora a null
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}else{
		
		abuelo=PadreAB->padre;
		
		hijoHijo=sHijo->izq; //Ubico al hijo del hijo...
		
		hijoHijo->padre=abuelo; //Aseguro que el padre de la raíz se quede apuntando al abuelo
		
		hijoHijo->dere=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		
		if(sHijo->izq!=NULL){
			sHijo->izq=hijoHijo->izq;
		}else{
			sHijo->izq=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		}
		
		//sHijo->dere=NULL; // Apuntar a Null la parte derecha del hijo, ya que ahora no tendrá Hijos...
		
		hijoHijo->izq=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		if(PadreAB->izq==NULL){
			PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		
		PadreAB->dere=NULL; //el antiguo padre debe apuntar ahora a null
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
		
		abuelo->dere=hijoHijo;
	}
}


//Rotación  Izquierda Derecha
void rotarID(){
	if (PadreAB==raiz){
		
		hijoHijo=sHijo->dere; //Ubico al hijo del hijo...
		
		raiz=hijoHijo; //Cambiar el apuntador de la raíz.
		
		hijoHijo->padre=NULL; //Aseguro que el padre de la raíz se quede en NULL
		
		hijoHijo->izq=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
		
		sHijo->dere=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			

		PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a null 
		
		hijoHijo->dere=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		
		if(PadreAB->dere==NULL){
			PadreAB->dere=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}else{
		
		abuelo=PadreAB->padre;
		
		hijoHijo=sHijo->dere; //Ubico al hijo del hijo...
		
		hijoHijo->padre=abuelo; //Aseguro que el padre de la raíz se quede apuntando al abuelo
		abuelo->izq=hijoHijo;
		
		hijoHijo->izq=sHijo; // el nuevo padre debe apuntar al hijo izquierdo.		
		sHijo->padre=hijoHijo; //El hijo debe apuntar a su nuevo padre.
				
		sHijo->dere=NULL; //Apuntar a Null la parte izquierda del hijo, ya que ahora no tendrá hijos...			
		
		
		hijoHijo->dere=PadreAB; //El nuevo padre debe apuntar al hijo derecho.
		
		PadreAB->izq=NULL; //El antiguo padre debe apuntar ahora a null 
		
		if(PadreAB->dere==NULL){
			PadreAB->dere=NULL; //El antiguo padre debe apuntar ahora a nu
		}
		PadreAB->padre=hijoHijo; //Apuntar al nuevo padre ...
	}
}

//Rotación  Derecha Derecha
void rotarDD(){
	if (PadreAB==raiz){
		raiz=sHijo;
		
		//sHijo->dere=hijoHijo;
		//hijoHijo->padre=sHijo;
		//hijoHijo->dere=NULL;
		
		sHijo->izq=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->dere=NULL;
		
		sHijo->padre=NULL;
		
	}else{
		abuelo=PadreAB->padre;
		abuelo->dere=PadreAB->dere;
		sHijo->padre=abuelo;
		sHijo->izq=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->dere=NULL;
	}
}


//Rotación  Izquierda Izquierda
void rotarII(){
	if(PadreAB==raiz){
		raiz=sHijo;
		
		hijoHijo=sHijo->izq;
		
		sHijo->dere=PadreAB;
		PadreAB->izq=NULL;
		PadreAB->padre=sHijo;
		
		sHijo->padre=NULL;
		
		//PadreAB->dere=hijoHijo;
		//hijoHijo->padre=PadreAB;
		
		//sHijo->dere=PadreAB;
		
		
	}else{
		abuelo=PadreAB->padre;
		abuelo->izq=PadreAB->izq;
		sHijo->padre=abuelo;
		sHijo->dere=PadreAB;
		PadreAB->padre=sHijo;
		PadreAB->izq=NULL;
	}	
}

//Dibuja dos cuadrados para hacer la carátula
void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;
    for (i=x1+1;i<x2;i++){
        gotoxy(i,y1); cputs("-") ;//linea horizontal superior
        gotoxy(i,y2); cprintf("-") ;//linea horizontal inferior
    }
    for (i=y1+1;i<y2;i++){
        gotoxy(x1,i); cprintf("|") ;//linea vertical izquierda
        gotoxy(x2,i); cprintf("|") ;//linea vertical derecha
    }
}


//Con el fin de automatizar o apresurar el ingreso masivo de datos se genera esta función
/*
Pregunta cuántos datos se ingresarán y en base a la cantidad irá solicitando los datos en forma contínua.
*/
void agregarDatos(){
	system("cls");
	int x;
	cout<<"Cuantos datos desea insertar? ";cin>>x;
	for (int i=1; i<=x;i++){
		cout<<"\nIngrese registro "<<i<<endl;
		recorrer=raiz; //Se apunta a recorrer en al mismo nodo donde apunta la raíz
		nuevo=nuevoNodo(); //Almacena el nuevo nodo para luego insertarlo en el arbol.
		
		if (nuevo->dato!=0){
			if (exiteenArbol(recorrer, nuevo->dato)==1){ //Evalua si el nodo ya existe en el arbol.
				PadreAB=raiz;
				insertarNuevo(recorrer, nuevo, PadreAB);
					
				//BBaltura(recorrer);
				//BBnecesidadEquilibrar(recorrer);
			}else{
				cout<<"El numero ya existe en el arbol"<<endl;
				getch();
			}
		}else{
			vaciarArbol(raiz);
			system("cls");
			verArbol(raiz, 0);
			cout<<"El arbol ha sido eliminado porque ingreso el numero cero "<<endl;
			getch();
			i=x;
			return;
		}
		
		verArbol(raiz,0);
	}
}


//Crea una introducción o carátula para el proyecto.
void intro(){
	clrscr();//limpia TODA LA pantalla
 
    //crea una ventana COMPLETA de fondo azul claro
    window(1,1,80,25);
    textbackground(LIGHTBLUE);//fondo de la pantalla AZUL CLARO
    clrscr();
 
    //Ventana de fondo o sombra NEGRA
    window(4,4,79,24);//crea una ventana en estar cordenadas
    textbackground(BLACK);
    clrscr();
 
    //ventana principal donde se solicitan datos
    window(2,2,77,22);//crea una ventana en estar cordenadas
    textbackground(GREEN);//fondo de la pantalla verde
    textcolor(YELLOW);//color de la letra amarillo
    clrscr();
    dibujarCuadro(1,1,75,21);//Cuadro grande
    dibujarCuadro(3,3,73,5);//Cuadro titulo
    gotoxy(16,4);
    textcolor(WHITE);//establece el color de fondo en blanco

    return;
}

int main(){
	intro();
	cprintf("Proyecto de arbol AVL --- UMG-Chinautla");
    gotoxy(3,7);cprintf("Curso de Estructura de Datos");
    gotoxy(3,9);cprintf("Ingeniero Manolo Guerra");
    gotoxy(3,11);cprintf("Melvin Randolfo Cante Guerra - 5990-14-1106");
    gotoxy(3,18);cprintf("Presione cualquier tecla para continuar...");
    getch();
    clrscr();
    
	int opcion;
	while (opcion!=11){
		system("cls");
		cout<<"************************** MENU **************************\n\n";
		cout<<"1.  Ingresar datos\n";
		cout<<"2.  Mostrar PreOrden\n";
		cout<<"3.  Mostrar InOrden\n";
		cout<<"4.  Mostrar PostOrden\n";
		cout<<"5.  Graficar Arbol - Rotado 90 grados\n";
		cout<<"6.  Graficar Arbol - Normal\n";
		cout<<"7.  Altura del arbol\n";
		cout<<"8.  Eliminar dato\n";
		cout<<"9.  Buscar dato\n";
		cout<<"10. Vaciar el arbol\n";
		cout<<"11. Salir\n";
		cout<<"Seleccione una opcion\n";
		cin>>opcion;
		
		recorrer=raiz;
		
		switch(opcion){
			case 1:
				agregarDatos();
				break;
			case 2:
				cout<<"____________PREORDEN__________"<<endl;
				preorden(recorrer);
				getch();
				break;
			case 3:
				cout<<"____________INORDEN__________"<<endl;
				inorden(recorrer);
				getch();
				break;
			case 4:
				cout<<"____________POSTORDEN__________"<<endl;
				postorden(recorrer);
				getch();
				break;
			case 5:
				system("cls");
				cout<<"____________ARBOL AVL - ROTADO 90 GRADOS A LA IZQUIERDA__________"<<endl;
				verArbol(recorrer, 0);
				getch();
				break;
			case 6:
				system("cls");
				gotoxy(25,2);cprintf("____________ARBOL AVL__________");
				//cout<<"____________ARBOL AVL__________"<<endl;
				graficarArbol(recorrer, 40, 5);
				getch();
				break;
			case 7:
				cout<<"La Altura del arbol es: "<<altura(recorrer)<<endl;
				getch();
				break;
			case 8:
				cout<<"Dato a eliminar: ";cin>>buscado;
				arbolVacio(recorrer, buscado); //Evalua si existe, luego procede a eliminar.
				recorrer=raiz; //Volver a asinar a recorrer el puntero raiz
				//BBaltura(recorrer); //Evaluar nuevamente la altura del arbol
				//BBrecorrer=raiz; //Volver a asinar a recorrer el puntero raiz
				//BBnecesidadEquilibrar(recorrer); //Evaluar si es necesario equilibrarlo
				cout<<"\nHecho";
				getch();
				break;
			case 9:
				cout<<"Nodo a buscar: ";cin>>buscado;
				buscarDato(recorrer, buscado);
				getch();
				break;
			case 10:
				cout <<"Vaciar Arbol"<<endl;
				vaciarArbol(recorrer);
				
				getch();
				break;
			case 11:
				break;
			default:
				cout<<"No es una opcion correcta";
				break;
		}
	}
	
	intro();
	cprintf("Gracias por Utilizar este Software");
    gotoxy(25,8);cprintf("By. Melvin Cante");
    gotoxy(2,20);cprintf(".");
    
	return 0;
}



