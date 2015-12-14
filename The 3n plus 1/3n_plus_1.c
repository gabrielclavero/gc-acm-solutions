/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int i, j, k, n, aux_i;

    int **a;

    a = (int **) malloc(sizeof(int *));
    a[0] = (int *)malloc(sizeof(int)*3);
    
    i = 0;
    while(scanf("%i %i", &a[i][0], &a[i][1])!=EOF){
        i++;
        a = realloc(a, sizeof(int *)*(i+1));
        a[i] = (int *)malloc(sizeof(int)*2);
    }
    a[i] = NULL;
    
    k=0;
    while(a[k] != NULL) {

       i = a[k][0];
        j = a[k][1];
 
     if(i > j) {
        aux_i = j;
       j = i;
        i = aux_i;
   }

    a[k][2] = 0;

    while(i<=j) {
           n = 1;   
             aux_i = i;
       while(aux_i!=1) {                
          
          if(!(aux_i % 2)) {
            aux_i = aux_i/2;
          }
          else {
             aux_i = 3*aux_i + 1;
             }
          n++;
       }
       if(n > a[k][2]) {
            a[k][2] = n;
       }
       i++;
    }
    k++;
}


k=0;
   while(a[k] != NULL) {
        printf("%i %i %i\n", a[k][0], a[k][1], a[k][2]);
        k++;
    }

    return 0;
}
