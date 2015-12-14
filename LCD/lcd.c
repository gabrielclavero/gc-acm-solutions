/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int s;              /*ver explicacion del problema, este es el s de ahi*/
char ***lcd = NULL;   /*en cada celda de este arreglo quedará la codificación lcd de cada dígito del numero*/
char digitos[9];        /*arreglo con los digitos del numero a imprimir (n de la explicacion del problema), como el numero mayor es 99 999 999 la cantidad de digitos maxima es 8, y dejo una celda mas para el \0*/

void char_a_lcd(char digito, short int rango);
int imprimir_lcd(short int cant_digitos);
void cargar_digitos(void);
int crear_matriz(void);
void destruir_matriz(void);


void cargar_digitos(void)
{
        char c;
        char c2;
        unsigned short int i = 0;

        c2 = '\0';
        c = getchar();
        while(c != '\n' && c != EOF) {
                if(c != ' ') {  /*ignoramos input con espacios, solo queremos los digitos del numero n*/
                        if(!(c == '0' && i == 0)) {/* 007 es lo mismo que 7, así que no guardaremos los ceros de adelante*/
                                digitos[i] = c;
                                i++;
                        } else {
                                c2 = c;
                        }
                } else if (c == ' ' && i != 0)  break;
                c = getchar();
        }
        if (c2 == '0' && i == 0) {      /*el input con un solo cero debe ser aceptado*/
                digitos[0] = c2; digitos[1] = '\0';
        } else 
                digitos[i] = '\0';
}

int imprimir_lcd(short int cant_digitos)
{
        short int i, j, k;
        
        /*vamos imprimiendo renglon por renglon por eso el for que recorre los renglones esta mas afuera*/
        
        for(i=0; i<2*s+3; i++) {
                if(i) printf("\n");       /*no imprimamos cuando  i == 0*/
                for(k=0; k<=cant_digitos-1; k++) {
                        for(j=0; j<s+2; j++) {
                                if(j == s+1 && k != cant_digitos-1) {
                                        printf("%c", lcd[k][i][j]);
                                        printf(" ");    /*There has to be exactly one column of blanks between two digits.*/
                                } else {
                                        printf("%c", lcd[k][i][j]);
                                }
                        }
                }
        }
        printf("\n\n"); /*Imprimir una línea vacía debajo de cada número*/
        
        return 0;
}

void char_a_lcd(char digito, short int rango)
{
        short int i;
        
        if(digito == '0') {
                for(i=1; i< s+1; i++) 
                        lcd[rango][0][i] = '-';
                        
                for(i=1; i<2*s + 2; i++) 
                        lcd[rango][i][0] = '|';
                        
                for(i=1; i<2*s + 2; i++) 
                        lcd[rango][i][s+1] = '|';
                        
                for(i=1; i< s+1; i++) 
                        lcd[rango][2*s + 2][i] = '-';
                
                for(i=0; i<s+2; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = ' ';
        } 
        else if(digito == '1') {
                for(i=1; i<2*s+2; i++) {
                        if (i!= (int)ceil((2*s+3)/2))
                                lcd[rango][i][s+1] = '|';
                }                    
        } 
        else if(digito == '2') {
                for(i=1; i<(int)ceil((2*s+3)/2); i++)
                        lcd[rango][i][s+1] = '|';
                for(i=(int)ceil((2*s+3)/2)+1; i<2*s+2; i++)
                        lcd[rango][i][0] = '|';
                for(i=1; i<s+1; i++)
                        lcd[rango][0][i] = '-';        
                for(i=1; i<s+1; i++)
                        lcd[rango][2*s+2][i] = '-';
                for(i=1; i<s+1; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = '-';        
        }
        else if(digito == '3') {
                for(i=1; i<s+1; i++)
                        lcd[rango][0][i] = '-';        
                for(i=1; i<s+1; i++)
                        lcd[rango][2*s+2][i] = '-';
                for(i=1; i<s+1; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = '-';
                for(i=1; i<2*s+2; i++) {
                        if(i != (int)ceil((2*s+3)/2))
                                lcd[rango][i][s+1] = '|';
                }
        }
        else if(digito == '4') {
               for(i=1; i<2*s+2; i++) {
                        if(i != (int)ceil((2*s+3)/2))
                                lcd[rango][i][s+1] = '|';
                }
                for(i=1; i<s+1; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = '-';
                for(i=1; i<(int)ceil((2*s+3)/2); i++)
                        lcd[rango][i][0] = '|';
        }
        else if(digito == '5') {
                for(i=1; i<s+1; i++)
                        lcd[rango][0][i] = '-';        
                for(i=1; i<s+1; i++)
                        lcd[rango][2*s+2][i] = '-';
                for(i=1; i<s+1; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = '-'; 
                for(i=1; i<(int)ceil((2*s+3)/2); i++)
                        lcd[rango][i][0] = '|';
                for(i=(int)ceil((2*s+3)/2)+1; i<2*s+2; i++)
                        lcd[rango][i][s+1] = '|';
        }
        else if(digito == '6') {
                for(i=1; i<s+1; i++)
                        lcd[rango][0][i] = '-';        
                for(i=1; i<s+1; i++)
                        lcd[rango][2*s+2][i] = '-';
                for(i=1; i<s+1; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = '-';  
                for(i=1; i<2*s+2; i++) {
                        if (i!= (int)ceil((2*s+3)/2))
                                lcd[rango][i][0] = '|';
                }
                for(i=(int)ceil((2*s+3)/2)+1; i<2*s+2; i++)
                        lcd[rango][i][s+1] = '|';
        }
        else if(digito == '7') {
                for(i=1; i<2*s+2; i++) {
                        if (i!= (int)ceil((2*s+3)/2))
                                lcd[rango][i][s+1] = '|';
                }
                for(i=1; i<s+1; i++)
                        lcd[rango][0][i] = '-';  
        }
        else if(digito == '8') {
                for(i=1; i<s+1; i++)
                        lcd[rango][0][i] = '-';        
                for(i=1; i<s+1; i++)
                        lcd[rango][2*s+2][i] = '-';
                for(i=1; i<s+1; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = '-';
                for(i=1; i<2*s+2; i++) {
                        if (i!= (int)ceil((2*s+3)/2))
                                lcd[rango][i][s+1] = '|';
                }
                for(i=1; i<2*s+2; i++) {
                        if (i!= (int)ceil((2*s+3)/2))
                                lcd[rango][i][0] = '|';
                }
        }
        else if(digito == '9') {
                for(i=1; i<s+1; i++)
                        lcd[rango][0][i] = '-';        
                for(i=1; i<s+1; i++)
                        lcd[rango][2*s+2][i] = '-';
                for(i=1; i<s+1; i++)
                        lcd[rango][(int)ceil((2*s+3)/2)][i] = '-';   
                for(i=1; i<2*s+2; i++) {
                        if (i!= (int)ceil((2*s+3)/2))
                                lcd[rango][i][s+1] = '|';
                }
                for(i=1; i<(int)ceil((2*s+3)/2); i++)
                        lcd[rango][i][0] = '|';
        }
}

int crear_matriz(void)
{
        unsigned short int i, j, k;
        
        lcd = (char ***) malloc(sizeof(char **)*9);     /*en realidad solo necesitamos 8 celdas, porque 99 999 999 es el numero mas grande que nos van a dar, pero si pones 8 se tilda cuando quieras imprimir un numero de 8 cifras*/
        if (lcd == NULL) return -1;
        
        for(i=0; i<9; i++) {
                lcd[i] = (char **) malloc(sizeof(char *)*(2*s + 4));    /*de nuevo agregamos una celda mas de la que necesitamos para evitar off-by-one errores*/
                if(lcd[i] == NULL) return -1;
        
                for(j = 0; j<2*s + 4; j++) {
                        lcd[i][j] = (char *) malloc(sizeof(char)* (s + 3));
                        if(lcd[i][j] == NULL) return -1;
                }
        }
        /*llenamos todas las celdas con espacio en blanco*/
        for(k=0; k<9; k++) {
                for(i=0; i<2*s+3; i++) {
                        for(j=0; j < s + 2; j++) {
                                lcd[k][i][j] = ' ';
                        }
                }
        }
        return 0;
}

void destruir_matriz(void)
{
       unsigned short int i, j; 
       
       for(i=0; i<9; i++) {
                for(j = 0; j<2*s + 4; j++) {
                        free(lcd[i][j]);
                        lcd[i][j] = NULL;
                }
                free(lcd[i]);
                lcd[i] = NULL;
        }
        free(lcd);
        lcd = NULL;
}

int main(void)
{
        unsigned short int i;
        
        while(1) {
                if(scanf("%u", &s) == 1) {
                        cargar_digitos();
                        if((s == 0) && (digitos[0] == '0') && (digitos[1] == '\0')) return 0;   /*nos vamos si el input para s y para n fue un cero exactamente*/
                        
                        crear_matriz();
                
                        i = 0;
                        while(digitos[i] != '\0') {
                                char_a_lcd(digitos[i], i);
                                i++;
                        }
                        imprimir_lcd(i);
                        destruir_matriz();
                }                
        }
        return 0;
}
