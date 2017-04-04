#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int Hexadecimal(int A[128], int indice);
char valHex(int R);

int main(void)
{
   int i, A[128], B[128], indice=1;
   unsigned semilla = (unsigned)time(NULL);
   FILE *archivo=NULL;

//Generación del número aleatoreo de 128 bits
//Mostramos en pantalla y guardamos la información en el arreglo A.
  
   srand(semilla);

    for (i = 1; i <= 128; i++){
        if(rand()%2 ==0){
            A[i]=0;
        }
        else{
            A[i]=1;
        }
    }
   

//Mostramos Matriz M

    printf("Matriz de entrada A: ");
    i=1;
    while(i<=128){
        printf("%d", A[i]);
        i++;
    if(indice==8){
        printf(" ");
        indice=0;   
        }
    indice=indice+1;
   
    }
    printf("\n");
    printf("\n");
    printf("\n");

   indice=1;
   Hexadecimal(A, indice);
}

int Hexadecimal(int A[128], int indice){
    int L,R, i;
    char auxL, auxR;
    i=indice*8;   
    while(i<=128){
       
        R= A[i]*1 + A[i-1]*2 + A[i-2]*4 + A[i-3]*8;  
        L=  A[i-4]*1 + A[i-5]*2 + A[i-6]*4 + A[i-7]*8;
        printf("\n");   
            if(R <=9 && L <= 9){           
        printf(" Hexadecimal A%d = %d%d \n", indice, L,R);
        }
        if(R > 9 && L <= 9){           
        auxR=valHex(R);
        printf(" Hexadecimal A%d = %d%c \n", indice, L,auxR);
        }

            if(R <=9 && L > 9){           
        auxL=valHex(L);       
        printf(" Hexadecimal A%d = %c%d \n", indice, auxL,R);
        }
            if(R > 9 && L > 9){           
        auxR=valHex(R);
        auxL=valHex(L);       
        printf(" Hexadecimal A%d = %c%c \n", indice, auxL, auxR);
        }
        printf("\n");
        indice=indice+1;
        i=indice*8;
    }

}


char valHex(int R){
    char aux;   
    if(R==10)
        aux='A';
    if(R==11)
        aux='B';
    if(R==12)
        aux='C';
    if(R==13)
        aux='D';
    if(R==14)
        aux='E';
    if(R==15)
        aux='F';
    return aux;

}