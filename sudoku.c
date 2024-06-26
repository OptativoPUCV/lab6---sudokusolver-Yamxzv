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

int is_valid(Node* n)
{
   for (int i = 0; i < 9; i++)
   {
      int fila[10] = {0};
      int columna[10] = {0};
      for (int j = 0; j < 9; j++)
      {
         if (n->sudo[i][j] != 0)
         {
            if (fila[n->sudo[i][j]] == 1)
            {
               return 0;
            }
            fila[n->sudo[i][j]] = 1;
         }

         if (n->sudo[j][i] != 0)
         {
            if (columna[n->sudo[j][i]] == 1)
            {
               return 0;
            }
            columna[n->sudo[j][i]] = 1;
         }
      }
   }
   for (int i = 0; i < 9; i += 3)
   {
      for (int j = 0; j < 9; j += 3)
      {
         int sub_fila[10] = {0};
         int sub_columna[10] = {0};
         for (int k = 0; k < 3; k++)
         {
            for (int l = 0; l < 3; l++)
            {
               if (n->sudo[i + k][j + l] != 0)
               {
                  if (sub_fila[n->sudo[i + k][j + l]] == 1)
                  {
                     return 0;
                  }
                  sub_fila[n->sudo[i + k][j + l]] = 1;
               }

               if (n->sudo[j + l][i + k] != 0)
               {
                  if (sub_columna[n->sudo[j + l][i + k]] == 1)
                  {
                     return 0;
                  }
                  sub_columna[n->sudo[j + l][i + k]] = 1;
               }
            }
         }
      }
   }

   return 1;
}


List* get_adj_nodes(Node* n)
{
   List* list=createList();
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         if (n->sudo[i][j] == 0)
         {
            for (int num = 1; num <= 9; num++)
            {
               Node* actual = copy(n);
               actual->sudo[i][j] = num;
               if (is_valid(actual))
               {
                  pushBack(list, actual);
               }
            }
            return list;
         }
      }
   }
   return list;
}

int is_final(Node* n)
{
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         if (n->sudo[i][j] == 0)
         {
            return 0;
         }  
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack* stack = createStack();
   push(stack, initial);
   while (!is_empty(stack))
   {
      Node* actual = top(stack);
      pop(stack);
      if (is_final(actual))
      {
         return actual;
      }

      List* adj = get_adj_nodes(actual);
      Node* aux = first(adj);
      while (aux)
      {
         push(stack, aux);
         aux = next(adj);
      }
      free(actual);
   }
   return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/