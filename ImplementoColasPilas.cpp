// pilas con estructura enlazada

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std; 
typedef int elemento;

struct nodo {
	elemento dato;
	nodo* sig;
};	

struct pila{
	nodo * ultimo = NULL;
	int profundidad = 0;
};

pila pila_vacia(){
	pila resultado;
	return resultado;
};

void apilar(elemento e, pila & p) {
	nodo* aux = new nodo;
	aux -> dato = e;
	aux -> sig = p.ultimo;
	p.ultimo = aux;
	p.profundidad = p.profundidad + 1;
};

void desapilar(pila & p){
	nodo* aux = p.ultimo -> sig;
	delete p.ultimo;
	p.ultimo = aux;
	p.profundidad = p.profundidad - 1;
};

elemento cima(pila p) {
	return p.ultimo -> dato;
};

bool es_vacia(pila p){
	return p.profundidad == 0;
};

int cant_elementos(pila p){
	return p.profundidad;
};

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
	std::cout<<"\nSacando ";
	std::cout<<cant_elementos(p);
	std::cout<<" elementos de la pila: ";
	while(!es_vacia(p)){
		std::cout<<cima(p);
		desapilar(p);
		std::cout<<", ";
	}
	std::cout<<"FIN.";
	return 0;
}

// pilas con arrays

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std; 
typedef int elemento;
const int capacidad_inicial = 2;

struct pila{
    elemento* cuerpo;
    int ultimo;
    int capacidad;
};

pila pila_vacia(){
	pila p;
	p.cuerpo = new elemento[capacidad_inicial];
    p.ultimo = 0;
    p.capacidad = capacidad_inicial;
	return p;
};

void duplica_capacidad(pila & p){
	elemento* nueva_lista = new elemento[2*p.capacidad];
	for(int i = 0;i<p.ultimo;i++){
	nueva_lista[i] = (p.cuerpo)[i];
	}
	delete[] (p.cuerpo);
	p.cuerpo = nueva_lista;
	p.capacidad = 2*p.capacidad;
};

void apilar(elemento e, pila & p) {
	if (p.ultimo == p.capacidad - 1){
		duplica_capacidad(p);
	};
	p.cuerpo[p.ultimo] = e; 
	p.ultimo = p.ultimo+1;
};

elemento cima(pila p) {
	return p.cuerpo[p.ultimo-1];
};

// devuelve true si la pila no contiene elementos, independientemente de que tenga o no memoria asignada
bool es_vacia(pila p){
	return p.ultimo == 0;
};

//ocuparse de desapilar solo cuando hay algún elemento en la pila
void desapilar(pila & p){
	p.ultimo = p.ultimo-1; //cuando se apile el siguiente elemento se eliminará
};

// deja inutilizada la pila, emplear solo al acabar de trabajar con ella
void libera_memoria(pila & p){
	delete[] p.cuerpo;
	p.ultimo = 0;
	p.capacidad = 0;
};

int cant_elementos(pila p){
	return p.ultimo;
};

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
	std::cout<<"\nSacando ";
	std::cout<<cant_elementos(p);
	std::cout<<" elementos de la pila: ";
	while(!es_vacia(p)){
		std::cout<<cima(p);
		desapilar(p);
		std::cout<<", ";
	}
	libera_memoria (p);
	std::cout<<"FIN.";
	return 0;
}

// cola con arrays

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std; 
typedef int elemento;
const int capacidad_inicial = 2;
const int constante_vaciado = 1;

struct cola{
    elemento* cuerpo;
	int primero;
    int ultimo;
    int capacidad;
};	

cola cola_vacia(){
	cola c;
	c.cuerpo = new elemento[capacidad_inicial];
	c.primero = 0;
    c.ultimo = -1;
    c.capacidad = capacidad_inicial;
	return c;
};

bool es_vacia(cola c){
	return (c.ultimo < c.primero);
};

//requerido cuando se llene la memoria, no se contempa que la capacidad inicial sea 0
void duplica_capacidad(cola & c){
	elemento* nueva_lista = new elemento[2*c.capacidad];
	for(int i = 0;i<=c.ultimo;i++){
	nueva_lista[i] = (c.cuerpo)[i];
	}
	delete[] (c.cuerpo);
	c.cuerpo = nueva_lista;
	c.capacidad = 2*c.capacidad;
};

//no se contempla que la capacidad inicial sea 0
void en_cola(cola & c, elemento e){
	if (c.ultimo == c.capacidad -1){
		duplica_capacidad(c);
	};
	c.ultimo = c.ultimo+1;
	c.cuerpo[c.ultimo] = e; 
}

//libera memoria
void reduce_capacidad(cola & c){
	elemento* nueva_lista = new elemento[c.capacidad - constante_vaciado];
	for(int i = 0;i<=c.ultimo-c.primero;i++){
	nueva_lista[i] = c.cuerpo[i+c.primero];
	}
	delete[] c.cuerpo;
	c.cuerpo = nueva_lista;
	c.ultimo = c.ultimo - c.primero;
	c.primero = 0;
	c.capacidad = c.capacidad - constante_vaciado;
};

// imponiendo constante_vaciado = 1 elimina elementos cada vez que los saca de la cola
void fuera_cola(cola & c){
	if (c.primero >= constante_vaciado) {
		reduce_capacidad(c);
	};
	c.primero = c.primero+1;
};

//requiere cola no vacia
elemento ultimo_en_cola(cola c) {
	return c.cuerpo[c.ultimo];
};

//requiere cola no vacia
elemento primero_en_cola(cola c) {
	return c.cuerpo[c.primero];
};

int cant_elementos(cola c){
	return c.ultimo - c.primero + 1;
};

// deja inutilizada la cola, emplear solo al acabar de trabajar con ella
void libera_memoria(cola & c){
	delete[] c.cuerpo;
	c.primero = 0;
	c.ultimo = 0;
	c.capacidad = 0;
};

int main(){
	cola c = cola_vacia();
	elemento e;
    string respuesta;
    std::cout<<"\nDesea agregar un dato (s/n): ";
    std::cin>>respuesta;
	while(respuesta=="s"){
		std::cout<<"Escribe un dato: ";
		std::cin>>e;
		en_cola(c,e);
		std::cout<<"\nDesea agregar otro dato (s/n): ";
		std::cin>>respuesta;
	}
	std::cout<<"\nSacando ";
	std::cout<<cant_elementos(c);
	std::cout<<" elementos de la cola: ";
	while(!es_vacia(c)){
		std::cout<<primero_en_cola(c);
		fuera_cola(c);
		std::cout<<", ";
	}
	libera_memoria (c);
	std::cout<<"FIN.";
	return 0;
}

// cola con estructura enlazada

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std; 
typedef int elemento;

struct nodo {
	elemento dato;
	nodo* sig;
	nodo* ant;
};	

struct cola{
	nodo* primero = NULL;
	nodo* ultimo = NULL;
	int profundidad = -1;
};

cola cola_vacia(){
	cola resultado;
	return resultado;
};

bool es_vacia(cola c){
	return c.profundidad == -1;
};

void en_cola(cola & c, elemento e){
	if(c.ultimo == NULL) {
		nodo* aux = new nodo;
		aux -> dato = e;
		aux -> sig = c.ultimo;
		aux -> ant = c.primero;
		c.primero = aux;
		c.ultimo = aux;
	}else{
		nodo* aux = new nodo;
		aux -> dato = e;
		aux -> sig = NULL;
		aux -> ant = c.ultimo;
		c.ultimo -> sig = aux;
		c.ultimo = aux;
	};
	c.profundidad = c.profundidad +1;
};

void fuera_cola(cola & c){
	nodo* aux = c.primero -> sig;
	delete c.primero;
	c.primero = aux;
	c.profundidad = c.profundidad - 1;
};

elemento ultimo_en_cola(cola c) {
	return c.ultimo -> dato;
};

//requiere cola no vacia
elemento primero_en_cola(cola c) {
	return c.primero -> dato;
};

int cant_elementos(cola c){
	return c.profundidad + 1;
};

int main(){
	cola c = cola_vacia();
	elemento e;
    string respuesta;
    std::cout<<"\nDesea agregar un dato (s/n): ";
    std::cin>>respuesta;
	while(respuesta=="s"){
		std::cout<<"Escribe un dato: ";
		std::cin>>e;
		en_cola(c,e);
		std::cout<<"\nDesea agregar otro dato (s/n): ";
		std::cin>>respuesta;
	}
	std::cout<<"\nSacando ";
	std::cout<<cant_elementos(c);
	std::cout<<" elementos de la cola: ";
	while(!es_vacia(c)){
		std::cout<<primero_en_cola(c);
		fuera_cola(c);
		std::cout<<", ";
	}
	std::cout<<"FIN.";
	return 0;
};

