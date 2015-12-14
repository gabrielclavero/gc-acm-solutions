/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_IMAGE 250
#define MAX_SIZE_BUF 100
#define TERMINAR 1


char image[MAX_SIZE_IMAGE][MAX_SIZE_IMAGE];
unsigned short int m = 0, n = 0;
char buffer[MAX_SIZE_BUF];
char *comando[6];

void clear_buf(void);
unsigned int handle_input(void);
void free_comando(unsigned int j);
unsigned int process_comando(unsigned int j);
void print_output(void);

void i_command(unsigned int j);
void c_command(unsigned int j);
void l_command(unsigned int j);
void v_command(unsigned int j);
void h_command(unsigned int j);
void k_command(unsigned int j);
void f_command(unsigned int j);
void s_command(unsigned int j);

void clear_buf(void)
{
        unsigned int i;
        for(i=0; i<MAX_SIZE_BUF; i++)
                buffer[i] = '\0';
}

/*devolvemos cantidad de palabras j (parámetros) leídas que cumple 1<=j<=6*/
unsigned int handle_input(void)
{
        unsigned int i = 0, j = 0;      /*i contador de longitud de parametros, j contador de parametros*/
        char c;
        
        clear_buf();
        c = getchar();
        
        while(j < 6) {
                if(c != ' ' && c != '\n') {
                        if(i<MAX_SIZE_BUF) {
                                buffer[i] = c;
                                i++;
                                
                        } else {
                                printf("BUFFER OVERFLOW"); i = 0; clear_buf();
                        }
                } else {
                        if(i) {
                                comando[j] = (char *) malloc(sizeof(char)*(i+1));
                                if(comando[j] != NULL) {
                                        comando[j] = strncpy(comando[j], buffer, i);
                                        comando[j][i] = '\0';
                                        j++;
                                        i = 0;
                                        clear_buf();
                                } else return -1;
                        }
                }
                if(c != '\n')
                        c = getchar();
                else 
                        break;
        }
        return j;
}

void free_comando(unsigned int j)
{
        unsigned int i;
        for(i=0; i<j; i++) {
                free(comando[j]);
                comando[j] = NULL;
        }
}

/*j: cantidad de parámetros (contando el nombre del comando), en el comando a procesar*/
unsigned int process_comando(unsigned int j)
{
        if(!strncmp("I", comando[0], strlen(comando[0]))) {
                i_command(j);
        } else if (!strncmp("C", comando[0], strlen(comando[0]))) {
                c_command(j);
        } else if (!strncmp("L", comando[0], strlen(comando[0]))) {
                l_command(j);
        } else if (!strncmp("V", comando[0], strlen(comando[0]))) {
                v_command(j);    
        } else if (!strncmp("H", comando[0], strlen(comando[0]))) {
                h_command(j);
        } else if (!strncmp("K", comando[0], strlen(comando[0]))) {
                k_command(j); 
        } else if (!strncmp("F", comando[0], strlen(comando[0]))) {
                f_command(j);
        } else if (!strncmp("S", comando[0], strlen(comando[0]))) {
                s_command(j);
        } else if (!strncmp("X", comando[0], strlen(comando[0]))) {
                return TERMINAR;
        } 
        return 0;
}

void i_command(unsigned int j)
{
        unsigned short int i, k;
        if(j==3) {        /*este comando necesita 3 parámetros, contando el nombre del comando*/
                n = (unsigned short int) strtol(comando[2], NULL, 10);
                m = (unsigned short int) strtol(comando[1], NULL, 10);
                for(i=0; i<n; i++) {
                        for(k=0; k<m; k++) {
                                image[i][k] = 'O';
                        }
                }
        }
}

void c_command(unsigned int j)
{        
        unsigned short int i, k;
        if(j == 1) {
                for(i=0; i<n; i++) {
                        for(k=0; k<m; k++) {
                                image[i][k] = 'O';
                        }
                } 
        }
        
}

void l_command(unsigned int j)
{
        unsigned short int i, k;
        if(j == 4) {
                /*restamos 1 a la coordenada porque la matriz es de indice cero y las coordenadas de los pixeles no*/
                k = (unsigned short int) strtol(comando[1], NULL, 10)-1; 
                i = (unsigned short int) strtol(comando[2], NULL, 10)-1; 
                /*if(i>=0 && i < m && j>=0 && j < n) esto no hace falta porque el unsigned short int me restringe los valores de i y j, entonces esto siempre es verdad*/
                        image[i][k] = comando[3][0];      /*tal vez debamos checar que el color sea un solo caracter simple aquí*/
        }
}
                
                
                
void v_command(unsigned int j)
{
        unsigned short int x, y1, y2, tmp, i;
        if(j == 5) {
                x = (unsigned short int) strtol(comando[1], NULL, 10)-1; 
                y1 = (unsigned short int) strtol(comando[2], NULL, 10)-1;
                y2 = (unsigned short int) strtol(comando[3], NULL, 10)-1;
                if(y1 > y2) {   /*con esto nos aseguramos que y1 <= y2*/
                        tmp = y2;
                        y2 = y1;
                        y1 = tmp;
                }
                if(x < m && y1 < m && y2 < m) { /*si todos los valores están en el rango...*/
                        for(i=y1; i<=y2; i++) {
                                image[i][x] = comando[4][0];
                        }
                }
        }            
}

void h_command(unsigned int j)
{
        unsigned short int x1, x2, y, tmp, i;
        if(j == 5) {
                x1 = (unsigned short int) strtol(comando[1], NULL, 10)-1; 
                x2 = (unsigned short int) strtol(comando[2], NULL, 10)-1;
                y = (unsigned short int) strtol(comando[3], NULL, 10)-1;
                if(x1 > x2) {   /*con esto nos aseguramos que x1 <= x2*/
                        tmp = x2;
                        x2 = x1;
                        x1 = tmp;
                }
                if(y < n && x1 < m && x2 < m) { /*si todos los valores están en el rango...*/
                        for(i=x1; i<=x2; i++) {
                                image[y][i] = comando[4][0];
                        }
                }
        }
}

void k_command(unsigned int j)
{
        unsigned short int x1, x2, y1, y2, i, k, tmp;
        if(j == 6) {
                x1 = (unsigned short int) strtol(comando[1], NULL, 10)-1; 
                x2 = (unsigned short int) strtol(comando[2], NULL, 10)-1;
                y1 = (unsigned short int) strtol(comando[3], NULL, 10)-1;
                y2 = (unsigned short int) strtol(comando[4], NULL, 10)-1;
                printf("%s", comando[4]);
                if(x1 > x2) {
                        tmp = x2;
                        x2 = x1;
                        x1 = tmp;
                }
                if(y1 > y2) {
                        tmp = y2;
                        y2 = y1;
                        y1 = tmp;
                }
                if(y1<n && y2<n && x1<m && x2<m) {
                        printf("y1 %i y2 %i x1 %i x2 %i", y1, y2, x1, x2);
                        for(i=y1; i<=y2; i++) {
                                for(k=x1; k<=x2; k++) {
                                        image[i][k] = comando[5][0];
                                        printf("ueeeeee\n");
                                }
                        }
                }
        }
}

void f_command(unsigned int j){}
void s_command(unsigned int j){}

void print_output(void)
{
        unsigned short int i, j;
        
        for(i=0; i<n; i++) {
                for(j=0; j<m; j++) {
                        putchar(image[i][j]);
                        if(j==m-1) putchar('\n');
                }
        }
}

int main(void) 
{
        unsigned int i = 0, j = 0;
        
        while(1) {
                j = handle_input();
                if(j > 0) {                             /*debemos tener un parámetro por lo menos (el nombre del comando) para procesarlo*/
                        i = process_comando(j);
                        if(i == TERMINAR) { free_comando(j); return 0; }
                        print_output();
                        free_comando(j);
                } 
                else if(j == -1) { printf("FALLO DE MEMORIA"); return -1; }
        }

        return 0;
}
        

