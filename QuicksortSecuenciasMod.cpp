#include <iostream>
#include <time.h>



using namespace std;

const string FLECHA = "↓";


struct par_int{
  int primero ;
  int segundo ;
};

par_int new_par(int p,int s){
    par_int result;
    result.primero = p;
    result.segundo = s;
    return result;
};

bool operator <=(par_int e1,par_int e2){
  return e1.segundo<=e2.segundo;
};

void mostrar(par_int e){
    cout << "("<<e.primero<<","<<e.segundo<<")";
};




template <typename T>
struct Nodo_sec{
       T dato;
       Nodo_sec<T> * sig = NULL;
};

template <typename T>
struct Secuencia{
  Nodo_sec<T> * primero;
  Nodo_sec<T> * anterior; //puntero al anterior al actual
};

template <typename T>
Secuencia<T> crear(){
  Secuencia<T> s;
  s.primero = new Nodo_sec<T>;
  s.anterior = s.primero;
  return s;
};

template <typename T>
void insertar(Secuencia<T>& s,T e){
  Nodo_sec<T> * new_node = new Nodo_sec<T>;
  new_node->dato = e;
  new_node->sig = s.anterior->sig;
  s.anterior->sig = new_node;
  s.anterior = new_node;
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
void reiniciar(Secuencia<T>& s){
  s.anterior = s.primero;
}

template<typename T>
bool fin(Secuencia<T> s){
  return s.anterior->sig == NULL;
}

template<typename T>
void liberar(Secuencia<T> s){
     reiniciar(s);
     while(!fin(s)){
         eliminar(s);
     }
     delete s.primero;
}

template<typename T>  // debe existir una procedimiento void mostrar(T dato) que mande
                      //la representación de dato a cout
void mostrar(Secuencia<T> s){
    Nodo_sec<T> * aux = s.primero;
    while(aux->sig != NULL){
      if(aux == s.anterior){
        cout << FLECHA;
      }
      mostrar(aux->sig->dato);
      cout <<  " ";
      aux = aux->sig;
    }
    cout << endl;
}

template <typename T>
bool es_vacia(Secuencia<T> s){
    return s.primero->sig == NULL;
}


template<typename T>
void ordenar_burbuja(Secuencia<T> s){
      //s es no vacía
      reiniciar(s);
      bool changed = true;
      while(changed){
        changed = false;
        reiniciar(s);
        T anterior = actual(s);
        eliminar(s);
        while(!fin(s)){
          if(anterior<=actual(s)){
            insertar(s,anterior);
            anterior = actual(s);
            eliminar(s);
          }
          else{
            avanzar(s);
            changed = true;
          }
        }
        insertar(s,anterior);
        //mostrar(s);
      }
      reiniciar(s);
}

// función modificada para que actúe sobre la propia secuencia dada, sin que necesite devolver parámetros
template<typename T>
void quick_sort(Secuencia<T>& s){
    if(!es_vacia(s)){
      Secuencia<T> menores = crear<T>();
      Secuencia<T> iguales = crear<T>();
      reiniciar(s);
      T pivote = actual(s);
      while(!fin(s)){
        if(!(actual(s)<=pivote)){
          avanzar(s);
        }
        else if (!(pivote <= actual(s))){
		   insertar(menores,actual(s));
		   eliminar(s);
        }
        else{
          insertar(iguales,actual(s));
		  eliminar(s);
        }
      }
	  quick_sort(s);
	  quick_sort(menores);
	  while(!fin(menores)){
        insertar(s,actual(menores));
        avanzar(menores);
      }
	  reiniciar(iguales);
      while(!fin(iguales)){
        insertar(s,actual(iguales));
        avanzar(iguales);
      }
	  reiniciar(s);
	  liberar(menores);
      liberar(iguales);
    }
}

int main(){
    Secuencia<int> s = crear<int>();
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
    quick_sort(s);
	reiniciar(s);
	while(!fin(s)) {
		cout << actual(s);
		cout << ",";
		avanzar(s);
	}
	cout <<" FIN.";
    liberar(s);
    return 0;
}