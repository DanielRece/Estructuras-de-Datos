#include<iostream> //para usar cin, cout ...
#include<fstream> // para poder leer archivos
#include<string> // para usar el tipo string

using namespace std;


const int MAX_ELEMS = 20;


struct Mat_elem{
     double valor;
     int i; // fila
     int j; // columna
};

//escribe e en cout (sin salto de linea al final)
void mostrar(Mat_elem e);
bool menor(Mat_elem e1,Mat_elem e2);

typedef Mat_elem Array_elems[MAX_ELEMS];

Mat_elem new_Mat_elem(double d, int i, int j);

struct Lista_elems{
    Array_elems entradas;
    int num_entradas = 0;
};

bool aniadir(Lista_elems & l, Mat_elem  e); // aniade el elemento e a l, si está llena devuelve false
bool aniadir_ord(Lista_elems & l, Mat_elem  e); // l está ordenada (según el orden lexicográfico de los pares i,j en Mat_elem) e1 < e2 si y sólo si:
                                                 //  e1.i < e2.i || ((e1.i == e2.i) && e1.j < e2.j).
                                                 // inserta e en l ordenadamente,
int len(const Lista_elems & l); // número de elementos en l
Mat_elem get_elem(const Lista_elems & l, int i); // i <len(l)

struct MatrizKK{
    Lista_elems m;
    double k;
    int f;
    int c;
};


//escribe en cout mat
void mostrar(MatrizKK R);

bool leer(string file_name, MatrizKK & mat);

bool comprobar_suma(MatrizKK R, MatrizKK S);

MatrizKK suma(MatrizKK R,MatrizKK S);

MatrizKK traspuesta(MatrizKK R);



int main(){
    string nombre_1;
    MatrizKK R;
    string S_T;
    cout << "Nombre del archivo para acceder a la matriz kk";
    cin >> nombre_1;
    if(leer(nombre_1, R)){
        cout<< R.k<<endl<<R.c << endl<<R.f<<endl;
        mostrar(R);
    }
    cout << "Suma 'S' o Traspuesta 'T'";
    cin >> S_T;
    if (S_T == "S"){
        string nombre_2;
        MatrizKK S;
        cout << "nombre del archivo para acceder a la matriz kk 2";
        cin >> nombre_2;
        if(leer(nombre_1, R)){
            cout<< R.k<<endl<<R.c << endl<<R.f<<endl;
            mostrar(R);
        }
        if(comprobar_suma(R,S)){
            MatrizKK T = suma(R,S);
            mostrar(T);
        } else {
            cout << "Suma no definida";
        }
    } else if (S_T == "T") {
        MatrizKK T = traspuesta(R);
        mostrar (T);
    } else {
        cout << "Hay que especificar si queremos una suma 'S' o una traspuesta 'T'";
    }
     return 0;
}



Mat_elem new_Mat_elem(double d, int i, int j){
         Mat_elem result;
         result.valor = d;
         result.i = i;
         result.j = j;
         return result;
}

bool menor(Mat_elem e1,Mat_elem e2){
     return e1.i < e2.i || ((e1.i == e2.i) && e1.j < e2.j);
}
//añade e a la lista l
bool aniadir(Lista_elems & l, Mat_elem  e){
     bool result = true;
     if(l.num_entradas<MAX_ELEMS){
         l.entradas[l.num_entradas] = e;
         l.num_entradas++;
     }
     else{
         result = false;
     }
     return result;
}

bool aniadir_ord(Lista_elems & l, Mat_elem  e){
  bool result = true;
  if(l.num_entradas<MAX_ELEMS){
     int pos = 0;
     while(pos < l.num_entradas && menor(l.entradas[pos],e)){
       pos++;
     }
     for(int i=l.num_entradas;i >=  pos;i--){
       l.entradas[i+1] = l.entradas[i];
     }
     l.entradas[pos] = e;
     l.num_entradas++;
  }
  else{
      result = false;
  }
  return result;
}

int len(const Lista_elems & l){
    return l.num_entradas;
}

Mat_elem get_elem(const Lista_elems & l, int i){
    return l.entradas[i];
}

bool leer(string file_name, MatrizKK  & mat){
     ifstream archivo;
     int f,c;
     double k,valor;
     bool result = true;
     archivo.open(file_name.c_str());
     archivo >> k >> f >> c;
     mat.k = k;
     mat.f = f;
     mat.c = c;
     for(int i = 0; i < f ; i ++){
       for(int j = 0; j < c; j ++){
          archivo >> valor;
          if(valor!=k){
               Mat_elem e;
               e = new_Mat_elem(valor,i,j);
               result = aniadir(mat.m,e);
               if(!result){
                   return false;
               }
          }
         }
      }
     archivo.close();
     return true;
}

void mostrar(Mat_elem e){
  cout << "("<< e.valor << "," << e.i<< ","<<e.j<<")";
}
void mostrar(MatrizKK mat){
    cout << "[";
    for(int i = 0; i < len(mat.m) ; i ++){
          if(i!=0){cout << ",";}
          mostrar(get_elem(mat.m,i));
    }
    cout << "],"<< mat.k << "," << mat.f << "," << mat.c;
    cout << endl;
}



bool comprobar_suma(MatrizKK R, MatrizKK S){
    return (R.f == S.f && R.c == S.c);
}

/* Recibe 2 matrices KK que se pueden sumar y devuelve la suma */
MatrizKK suma(MatrizKK R, MatrizKK S){
	MatrizKK T;
    T.k = R.k + S.k;
    T.f = R.f;
    T.c = R.c;
    int pos1 = 0;
    int pos2 = 0;
    /* Suponemos que los elementos de MatrizKK.m.entradas están ordenados por filas y columnas, de igual manera, devolvemos una matriz ordenada */
    while (pos1 < R.m.num_entradas && pos2 < S.m.num_entradas) {
        if(R.m.entradas[pos1].i == S.m.entradas[pos2].i && R.m.entradas[pos1].j == S.m.entradas[pos2].j){
            if (T.k != R.m.entradas[pos1].valor + S.m.entradas[pos2].valor){
                Mat_elem e;
                e.valor = R.m.entradas[pos1].valor;
                e.i = R.m.entradas[pos1].i;
                e.j = R.m.entradas[pos1].j;
                aniadir_ord(T.m, e);
            }
            pos1++;
            pos2++;
        } else if (R.m.entradas[pos1].i < S.m.entradas[pos2].i && R.m.entradas[pos1].j < S.m.entradas[pos2].j) {
            Mat_elem e;
            e.valor = R.m.entradas[pos1].valor + S.k;
            e.i = R.m.entradas[pos1].i;
            e.j = R.m.entradas[pos1].j;
            aniadir_ord(T.m, e);
            pos1++;
        } else {
            Mat_elem e;
            e.valor = S.m.entradas[pos2].valor + R.k;
            e.i = S.m.entradas[pos2].i;
            e.j = S.m.entradas[pos2].j;
            aniadir_ord(T.m, e);
            pos2++;
        }
    }
    for (int Rrestantes= pos1; Rrestantes < R.m.num_entradas; Rrestantes++){
        Mat_elem e;
        e.valor = R.m.entradas[Rrestantes].valor + S.k;
        e.i = R.m.entradas[Rrestantes].i;
        e.j = R.m.entradas[Rrestantes].j;
        aniadir_ord(T.m, e);
    }
    for (int Srestantes= pos2; Srestantes < S.m.num_entradas; Srestantes++){
        Mat_elem e;
        e.valor = S.m.entradas[Srestantes].valor + R.k;
        e.i = S.m.entradas[Srestantes].i;
        e.j = S.m.entradas[Srestantes].j;
        aniadir_ord(T.m, e);
    }
}
/* Recibe una matriz kk y devuelve su traspuesta como matriz kk */

MatrizKK traspuesta(MatrizKK R){
	MatrizKK Traspuesta;
    Traspuesta.f = R.c;
    Traspuesta.c = R.f;
    Traspuesta.k = R.k;
    for (int ent = 0; ent < R.m.num_entradas; ent++){
        Mat_elem e;
        e.valor = R.m.entradas[ent].valor;
        e.i = R.m.entradas[ent].j;
        e.j = R.m.entradas[ent].j;
        aniadir_ord(Traspuesta.m, e);
    }
    return Traspuesta;
}
