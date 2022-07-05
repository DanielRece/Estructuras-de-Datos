#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct Par_l_f{
   char letra;
   int frecuencia;
};

struct Par_l_c{
	char letra;
	string clave;
};

template <typename T>
struct Nodo_arbol{
	bool es_hoja = true;
	T dato;
	int frecuencia_acumulada = 0;
	Nodo_arbol<T> *hijo_iz = NULL;
	Nodo_arbol<T> *hijo_dr = NULL;
};

template <typename T>
using Abb_frec =  Nodo_arbol<T>*;

template <typename T>
using Abb_huff =  Nodo_arbol<T>*;

template <typename T>
struct Comp_abb_huff{//el orden con el que se relacionarán los arboles de huffman
	bool operator()(Abb_huff<T> a1, Abb_huff<T> a2){
		return a1 ->frecuencia_acumulada > a2 -> frecuencia_acumulada;
	};
};

template <typename T>
Nodo_arbol<T>* abb_vacio(){
	return NULL;
};

template <typename T>
bool es_abb_vacio(Nodo_arbol<T>* a){
	return a == NULL;
};

template <typename T>
void liberar_abb(Nodo_arbol<T>* & a){
	if(!es_abb_vacio(a)){
		liberar_abb(a->hijo_iz);
		liberar_abb(a->hijo_dr);
		delete a;
	};
};

template <typename T>
Abb_huff<T> plantar(Abb_huff<T> ah1, Abb_huff<T> ah2){//crea un nuevo arbol de huffman a partir de otros 2
	Nodo_arbol<T> *nodo = new Nodo_arbol<T>;
	nodo -> es_hoja = false;
	nodo->hijo_iz = ah1;
	nodo->hijo_dr = ah2;
	nodo->frecuencia_acumulada = ah1->frecuencia_acumulada + ah2->frecuencia_acumulada;
	return nodo;
};

void insertar(Abb_frec<Par_l_f> &a, Par_l_f e){//inserta en un arbol de frecuencias el par letra frecuencia
	if(es_abb_vacio(a)){
		a = new Nodo_arbol<Par_l_f>;
		a->dato = e;
	}else if(int(e.letra) < int(a->dato.letra)){
		insertar(a->hijo_iz,e);
	}else if(int(e.letra) > int(a->dato.letra)){
		insertar(a->hijo_dr,e);
	}else{
		a->dato.frecuencia += e.frecuencia;
	};
};

void insertar(Abb_frec<Par_l_c> &a, Par_l_c e){//inserta en un arbol de frecuencias el par letra clave
	if(es_abb_vacio(a)){
		a = new Nodo_arbol<Par_l_c>;
		a->dato = e;
	}else if(int(e.letra) < int(a->dato.letra)){
		insertar(a->hijo_iz,e);
	}else{
		insertar(a->hijo_dr,e);
	};
};

void tabla_codigos(Abb_huff<Par_l_f> ah, string s, Abb_frec<Par_l_c> &af){//instertamos en una tabla de frecuencias el código 0`s y 1`s asociado a las letras que estan en el arbol de huffman, el código se crea según se va recorriendo el arbold de huffman
	if (ah->es_hoja){
		Par_l_c lc;
		lc.letra = ah->dato.letra;
		lc.clave = s;
		insertar(af,lc);
	}else{
		tabla_codigos(ah -> hijo_iz, s+"0", af);
		tabla_codigos(ah -> hijo_dr, s+"1", af);
	};
};

void abb_frec_a_vector(Abb_frec<Par_l_f> &af, vector<Abb_huff<Par_l_f>> &vec){//cramos un vector que contendrá los pares letra frecuencia
	if(!es_abb_vacio(af)){
		vec.push_back(af);
		abb_frec_a_vector(af -> hijo_iz, vec);
		af -> hijo_iz = NULL;
		abb_frec_a_vector(af -> hijo_dr, vec);
		af -> hijo_dr = NULL;
	};
};

Abb_huff<Par_l_f> vector_a_abb_huff(vector<Abb_huff<Par_l_f>> vec){//construimos el arbol de huffman haciendo uso de las colas con prioridad y el comparador de arboles de huffman
	priority_queue<Abb_huff<Par_l_f>,vector<Abb_huff<Par_l_f>>,Comp_abb_huff<Par_l_f>> q(vec.begin(),vec.end());
	while (q.size()>1) {
		Abb_huff<Par_l_f> ah1 = q.top();
		q.pop();
		Abb_huff<Par_l_f> ah2 = q.top();
		q.pop();
		Abb_huff<Par_l_f> ah3 = plantar(ah1,ah2);
		q.push(ah3);
	};
	Abb_huff<Par_l_f> resultado = q.top();
	q.pop();
	return resultado;
};

void codifica_letra(Abb_frec<Par_l_c> af, char l, string &s){//modificamos el valor de s, que pasará a ser el código-clave de la tabla
	if (int(l) == int(af-> dato.letra)){
		s = af -> dato.clave;
	}else if (int(l) < int(af->dato.letra)) {
		codifica_letra(af->hijo_iz,l, s);
	}else{
		codifica_letra(af->hijo_dr,l, s);
	};
};

void codifica_mensaje(Abb_frec<Par_l_c> af, string mensaje, string &codificacion){//codificamos el mensaje y lo almacenamos en codificacion
	int cont = 0;
	string l_cod;
	while (cont < mensaje.length()){
		char letra = mensaje[cont];
		codifica_letra(af,letra,l_cod);
		codificacion += l_cod;
		cont +=1;
	};
};

string decodifica_clave(Abb_huff<Par_l_f> ah, string &codigo){//recuperamos el mensaje original recorriendo el arbol de huffman
	string mensaje = "";
	Nodo_arbol<Par_l_f> *aux = ah;
	while (codigo.length() > 0) {
		Nodo_arbol<Par_l_f> *aux = ah;
		while (!aux->es_hoja){
			if(int(codigo[0]) == int('0')){
				codigo.erase(0,1);
				aux = aux ->hijo_iz;
			}else{
				codigo.erase(0,1);
				aux = aux ->hijo_dr;
			};	
		};
		mensaje += aux->dato.letra;
	};
	mensaje += aux->dato.letra;
	return mensaje;
};

// Las siguientes funciones se han usado para ir probando el código, muestran las distintas estructuras por pantalla
void muestra_dato(Par_l_f dato){
	cout << dato.letra <<","<< dato.frecuencia << "\n";
};

void muestra_dato(Par_l_c dato){
	cout << dato.letra <<","<< dato.clave << "\n";
};

template <typename T>
void muestra_abb(Nodo_arbol<T>* a){
	if(!es_abb_vacio(a)){
		muestra_abb(a -> hijo_iz);
		muestra_dato(a -> dato);
		muestra_abb(a -> hijo_dr);
	};
};

void muestra_vector(vector<Nodo_arbol<Par_l_f>*> vec){
	int cont = 0;
	while (cont<vec.size()) {
		Abb_frec<Par_l_f> af = vec[cont];
		muestra_abb(af);
		cont += 1;
		};
};

int main(){
	cout<<"Inserte el texto a procesar: ";
	string texto;
	getline(cin,texto);
	Abb_frec<Par_l_f> af = abb_vacio<Par_l_f>();
	// El siguiente bucle inserta el texto en el árbol de frecuencias
	for(int i = 0; i < texto.length(); i++){
		char c = texto[i];
		Par_l_f lf;
		lf.letra = c;
		lf.frecuencia = 1;
		insertar(af,lf);
	};
	// muestra_abb(af);
	vector<Abb_huff<Par_l_f>> vec;
	abb_frec_a_vector(af, vec);
	// muestra_vector(vec);
	Abb_huff<Par_l_f> ah = vector_a_abb_huff(vec);
	// muestra_abb(ah);
	Abb_frec<Par_l_c> cods = abb_vacio<Par_l_c>();
	tabla_codigos(ah,"",cods);
	// muestra_abb(cods);
	string mensaje_codificado;
	codifica_mensaje(cods, texto, mensaje_codificado);
	cout<< "Mensaje codificado: " << mensaje_codificado << "\n";
	string mensaje_alterado = decodifica_clave(ah, mensaje_codificado);
	cout<< "Mensaje decodificado: " << mensaje_alterado << "\n";
	liberar_abb(ah);
	liberar_abb(cods);
	return 0;
}
