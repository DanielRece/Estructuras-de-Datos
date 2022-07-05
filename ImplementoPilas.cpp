#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std; 


typedef int elemento;

struct nodo {
	elemento dato;
	nodo* sig;
};	

typedef nodo* pila;



pila pila_vacia(){
	return NULL;
}

elemento cima(pila p) {
	return p ->dato;
}

void apilar(elemento e, pila & p) {
	nodo* aux = new nodo;
	aux -> dato = e;
	aux -> sig = p;
	p = aux;
}

void desapilar(pila & p){
	nodo* aux = p -> sig;
	delete p;
	p = aux;
}
	

int main(){
	pila p = pila_vacia();
	elemento e;
    string respuesta;
    std::cout<<"\nDesea agregar un dato (s/n): ";
    std::cin>>respuesta;
	while(respuesta=="s"){
		std::cout<<"Escribe un dato: ";
		std::cin>>e;
		apilar(e,p);
		std::cout<<"\nDesea agregar otro dato (s/n): ";
		std::cin>>respuesta;
	}
	std::cout<<"\nSacando elementos de la pila: ";
	while(p != pila_vacia()){
		std::cout<<cima(p);
		desapilar(p);
		if(p != pila_vacia()){
		std::cout<<" , ";
		}else{
		std::cout<<".";}
		}
	return 0;
}