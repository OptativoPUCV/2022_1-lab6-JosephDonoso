#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid_fila(int fil, Node* n){
  int valoresAux[9];
  for( int i = 0; i < 10; i++){
    valoresAux[i] = 0;
  }

  for( int i = 0; i < 9; i++){
    if( n->sudo[fil][i] != 0){
      if( valoresAux[ n->sudo[fil][i] - 1] != 1){
        valoresAux[ n->sudo[fil][i] - 1] = 1;
      }
      else{
        return 0;
      }
    }
  }

  return 1;
}

int is_valid_columna(int col, Node* n){
  int valoresAux[9];
  for( int i = 0; i < 10; i++){
    valoresAux[i] = 0;
  }

  for( int i = 0; i < 9; i++){
    if( n->sudo[i][col] != 0){
      if( valoresAux[ n->sudo[i][col] - 1] != 1){
        valoresAux[ n->sudo[i][col] - 1] = 1;
      }
      else{
        return 0;
      }
    }
  }

  return 1;
}

int is_valid_submatrix(int subM, Node* n){
  int valoresAux[9];
  for( int i = 0; i < 10; i++){
    valoresAux[i] = 0;
  }
 
  for(int p = 0;p < 9; p++){
      int i = 3*(subM / 3) + (p / 3) ;
      int j = 3*(subM % 3) + (p % 3) ;
      if( n->sudo[i][j] != 0){
        if( valoresAux[ n->sudo[i][j] - 1] != 1){
        valoresAux[ n->sudo[i][j] - 1] = 1;
        }
        else{
          return 0;
        }
      }
      
  }

  return 1;
}

int is_valid(Node* n){
  
  for( int i = 0; i < 9; i++){
    if ( !is_valid_fila(i, n) || !is_valid_columna(i, n) || !is_valid_submatrix(i, n) ){
      return 0;
    }
  }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){

        if (n->sudo[i][j] == 0){

          for ( int k = 1; k < 10; k++){
            Node* nuevoEstado = copy( n );
            nuevoEstado->sudo[i][j] = k;
            if( is_valid(nuevoEstado) ){
              pushBack( list , nuevoEstado );
            }
          }
          return list;

        }

      }
    }
  return list;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if( n->sudo[i][j] == 0 ) return 0; 
    }
  }

    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push( pila, initial );
  *cont = 0;
  while(!is_empty(pila)){
    *cont += 1;
    Node* n = top( pila );
    pop( pila );
    if (is_final( n )) return n;
    List* adyacentes = get_adj_nodes( n );
    while(!is_empty( adyacentes)){
      push( pila, last(adyacentes) );
      popBack ( adyacentes );
    }
    free(n);
  }

  return NULL;
}




/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/