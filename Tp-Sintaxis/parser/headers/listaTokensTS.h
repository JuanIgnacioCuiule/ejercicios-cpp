typedef struct Nodo {
  struct Nodo* ant;
  TOKEN token;
  char cadena[33];
  struct Nodo* sig;
  int linea;
} Nodo;

typedef struct Simbolo {
  TOKEN token;
  char cadena[33];
} Simbolo;

void agregar(Nodo** cola, TOKEN token, char cadena[], int linea);
void agregarSimbolo(Simbolo tabla[], TOKEN token, char cadena[]);
int estaEnTS(Simbolo tabla[], TOKEN token, char cadena[]);
void mostrar(Nodo* lista);
void mostrarTabla(Simbolo tabla[]);