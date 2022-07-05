#include <iostream>
#include <string>
#include <string.h>

using namespace std; 

template <typename T>
struct Nodo_sec{
       T dato;
       Nodo_sec<T> *sig = NULL;
};

template <typename T>
struct Secuencia{
  Nodo_sec<T> *primero = NULL;
  Nodo_sec<T> *anterior = NULL; //puntero al anterior al actual
};

template <typename T>
struct Nodo_arbol;

template <typename T>
using Abb =  Nodo_arbol<T> *;

template <typename T>
struct Nodo_arbol{
       T dato;
       Abb<T> hijo_izdo = NULL, hijo_dcho = NULL;
};

template <typename T>
Secuencia<T> crear(){
  Secuencia<T> s;
  s.primero = new Nodo_sec<T>;
  s.anterior = s.primero;
  return s;
};

template <typename T>
void eliminar(Secuencia<T>& s){
  if(s.anterior->sig != NULL){
    Nodo_sec<T> * aux = s.anterior->sig;
    s.anterior->sig = aux->sig;
    delete aux;
  }
  else{
    throw runtime_error(" final de la  secuencia");
  }
};

template<typename T>
void reiniciar(Secuencia<T>& s){
  s.anterior = s.primero;
}


template <typename T>
T actual(const Secuencia<T>& s){
  if(s.anterior->sig != NULL){
    return s.anterior->sig->dato;
  }
  else{
    throw runtime_error(" final de la  secuencia");
  }
};

template<typename T>
void avanzar(Secuencia<T>& s){
  if(s.anterior->sig != NULL){
    s.anterior = s.anterior->sig;
  }
  else{
    throw runtime_error("final de la  secuencia");
  }
}

template<typename T>
void liberar(Secuencia<T> s){
     reiniciar(s);
     while(!fin(s)){
         eliminar(s);
     }
     delete s.primero;
}

template <typename T>
void insertar(Secuencia<T>& s,T e){
  Nodo_sec<T> *new_node = new Nodo_sec<T>;
  new_node->dato = e;
  new_node->sig = s.anterior->sig;
  s.anterior->sig = new_node;
  s.anterior = new_node;
};

template<typename T>
bool fin(Secuencia<T> s){
  return s.anterior->sig == NULL;
};

template <typename T>
Secuencia<T> concatenar(Secuencia<T> s1, Secuencia<T> s2){
	Secuencia<T> s = s1;
	while (!fin(s)){
		avanzar(s);
	};
	s.anterior->sig = s2.primero;
	return s;
};

template <typename T>
Abb<T> abb_vacio(){
       return NULL;
}

template <typename T>
bool es_abb_vacio(Abb<T> a){
     return a == NULL;
}

template <typename T>
void liberar_a(Abb<T> & a){
       if(a!=NULL){
           liberar_a(a->hijo_izdo);
           liberar_a(a->hijo_dcho);
           delete a;
       }
}

template <typename T>
void insertar_a(Abb<T> & a,T e){
     if(es_abb_vacio(a)){
        a = new Nodo_arbol<T>;
        a->dato = e;
     }
     else if(!(a->dato<= e)){
          insertar_a(a->hijo_izdo,e);
     }
     else{
          insertar_a(a->hijo_dcho,e);
     }
}


template <typename T>
void in_orden_aux(const Abb<T> & a,Secuencia<T> & s){
     if(!es_abb_vacio(a)){
          in_orden_aux( a->hijo_izdo, s);
          insertar(s,a->dato);
          in_orden_aux( a->hijo_dcho, s);
     }
}


template <typename T>
Secuencia<T> in_orden(const Abb<T> & a){
     Secuencia<T> result = crear<T>();
     in_orden_aux(a,result);
     return result;
}

template <typename T>
Secuencia<T> ordenar_abb(Secuencia<T> s){
      Abb<T> a=NULL;
      reiniciar(s);
      while(!fin(s)){
          insertar_a(a,actual(s));
          avanzar(s);
      }
      Secuencia<T> result = in_orden(a);
      //cout << a << endl;
      liberar_a(a);
      return  result;
}


int main(){
	Secuencia<int> s = crear<int>();
	Secuencia<int> s_1;
	cout << "CREANDO SECUENCIA: ";
    for(int i = 0; i< 30; i++){
      int n = rand() %10;
      insertar(s,n);
    }
    reiniciar(s);
	while(!fin(s)) {
		cout << actual(s);
		cout << ",";
		avanzar(s);
	}
	cout << " FIN DE LA SECUENCIA.\n";
	cout <<"ORDENANDO LA SECUENCIA: ";
	s_1 = ordenar_abb(s);
	reiniciar(s_1);
	while(!fin(s_1)) {
		cout << actual(s_1);
		cout << ",";
		avanzar(s_1);
	}
	cout <<" FIN.";
    liberar(s);
	liberar(s_1);
    return 0;
};















		
		
	
	
	
	
	
	
	
	








