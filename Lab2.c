#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int Hexadecimal(int A[128], int indice);
char valHex(int R);
void mostrar(int Baux[32]);
void MixColumn (int BSalida[32]);
int binario (int BSalida[32]);

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
    //printf("\n");

   indice=1;
   Hexadecimal(A, indice);
   printf("\n");
   return 0;
}

//Generamos B

int Hexadecimal(int A[128], int indice){
    int L,R, i, j=0, Baux[32];
    char auxL, auxR;
    i=indice*8;   
    while(i<=128){
       
        //printf("VUEEEEELLTAAAA !!!! \n");
        R= A[i]*1 + A[i-1]*2 + A[i-2]*4 + A[i-3]*8;  
        L=  A[i-4]*1 + A[i-5]*2 + A[i-6]*4 + A[i-7]*8;
        printf("\n");   
        if(R <=9 && L <= 9){           
            printf(" Hexadecimal B%d = %d%d ", indice-1, L,R);
            Baux[j]=L;
            j++;
            Baux[j]=R;
            j++;

        }
        if(R > 9 && L <= 9){           
            auxR=valHex(R);
            printf(" Hexadecimal B%d = %d%c ", indice-1, L,auxR);
            Baux[j]=L;
            j++;
            Baux[j]=R;
            j++;
        }

        if(R <=9 && L > 9){           
            auxL=valHex(L);       
            printf(" Hexadecimal B%d = %c%d ", indice-1, auxL,R);
            Baux[j]=L;
            j++;
            Baux[j]=R;
            j++;
        }
        if(R > 9 && L > 9){           
            auxR=valHex(R);
            auxL=valHex(L);       
            printf(" Hexadecimal B%d = %c%c ", indice-1, auxL, auxR);
            Baux[j]=L;
            j++;
            Baux[j]=R;
            j++;
        }
        //printf("\n");
        
        indice=indice+1;
        i=indice*8;
        //j=j+2;
        //

        
    }
    printf("\n");
    mostrar(Baux);

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

void mostrar(int Baux[32]){
    int i=0, j=1, x=0, BEntrada[32], BSalida[32];
    char aux;

//Aquí hacemos las asignaciones para ordenar la matriz de la forma necesaria para realizar el Shift Row
//BEntrada es la matriz de entrada para el shift row que lo ocuparemos solo para mostrarlo en la entrada
//y BSalida es la matriz luego de aplicado el Shift Row y con la que haremos el Mix Colum

    //0
    BEntrada[0]=BSalida[0]=Baux[0];
    BEntrada[1]=BSalida[1]=Baux[1];
    //1
    BEntrada[8]=BSalida[14]=Baux[2];
    BEntrada[9]=BSalida[15]=Baux[3];
    //2
    BEntrada[16]=BSalida[20]=Baux[4];
    BEntrada[17]=BSalida[21]=Baux[5];
    //3
    BEntrada[24]=BSalida[26]=Baux[6];
    BEntrada[25]=BSalida[27]=Baux[7];
    //4
    BEntrada[2]=BSalida[2]=Baux[8];
    BEntrada[3]=BSalida[3]=Baux[9];
    //5
    BEntrada[10]=BSalida[8]=Baux[10];
    BEntrada[11]=BSalida[9]=Baux[11];
    //6
    BEntrada[18]=BSalida[22]=Baux[12];
    BEntrada[19]=BSalida[23]=Baux[13];
    //7
    BEntrada[26]=BSalida[28]=Baux[14];
    BEntrada[27]=BSalida[29]=Baux[15];
    //8
    BEntrada[4]=BSalida[4]=Baux[16];
    BEntrada[5]=BSalida[5]=Baux[17];
    //9
    BEntrada[12]=BSalida[10]=Baux[18];
    BEntrada[13]=BSalida[11]=Baux[19];
    //10
    BEntrada[20]=BSalida[16]=Baux[20];
    BEntrada[21]=BSalida[17]=Baux[21];
    //11
    BEntrada[28]=BSalida[30]=Baux[22];
    BEntrada[29]=BSalida[31]=Baux[23];
    //12
    BEntrada[6]=BSalida[6]=Baux[24];
    BEntrada[7]=BSalida[7]=Baux[25];
    //13
    BEntrada[14]=BSalida[12]=Baux[26];
    BEntrada[15]=BSalida[13]=Baux[27];
    //14
    BEntrada[22]=BSalida[18]=Baux[28];
    BEntrada[23]=BSalida[19]=Baux[29];
    //15
    BEntrada[30]=BSalida[24]=Baux[30];
    BEntrada[31]=BSalida[25]=Baux[31];
    
//Mostramos BEntrada

    printf("\n \n Matriz B de entrada para Shift Row \n \n ");
    for(i=0; i < 32; i = i+1){
        //printf(" valor de i: %d ",i);
        if(j==9)
        {
            printf("\n");
            j=1;
        }
        if(i%2==0){
            printf(" ");
        }
        if(BEntrada[i]>9){
            aux=valHex(BEntrada[i]);
            printf("%c", aux);
        }
        else{
            printf("%u",BEntrada[i]);
        }
        j++;

    }

//Mostramos BSalida

    j=1;
    printf("\n \n Matriz B de salida luego del Shift Row \n \n ");
    for(x=0; x < 32; x = x+1){
        //printf(" x-%d ",x);
        
        if(j==9)
        {
            printf("\n");
            j=1;
        }
        if(x%2==0){
            printf(" ");

        }
        if(BSalida[x]>9){
            aux=valHex(BSalida[x]);
            printf("%c", aux);
        }
        else{
            printf("%u",BSalida[x]);
        }
        j++;


    }
    MixColumn(BSalida);
}

void MixColumn (int BSalida[32]){
    int L, R, i, Binario[8];
    int P1[8]={0,0,0,0,0,0,0,1};
    int P2[8]={0,0,0,0,0,0,1,0};
    int P3[8]={0,0,0,0,0,0,1,1};

    for (i=0; i<8; i++){
        //printf("%u", P1[i] );
       


    }
    binario(BSalida);


}

int binario (int BSalida[32]){
    int dividendo, resto, divisor = 2, binario[4], i=0, binAux[4]={0,0,0,0}, j=0, vuelta=1, x=0;
    int B1[8], B2[8], B3[8], B4[8], B5[8], B6[8], B7[8], B8[8], B9[8], B10[8], B11[8], B12[8], B13[8], B14[8], B15[8], B16[8];
    
    while(x<31){
        j=0;
        while(j<2){
            i=0;
            dividendo = BSalida[x+j];
            //printf("\nNÚMERO DECIMAL= %d \n", dividendo);
            while(dividendo >= divisor){ //Mientras el dividendo sea mayor o igual que el divisor, es decir, mayor o igual que 2.
                resto = dividendo % 2;
                 //printf("\nhola3= %d \n", resto);
                if(resto == 1){
                    binario[i] = 1; //Si el resto es igual a 1 concatenamos 1 a la variable string llamada binario
                }
                else{
                    binario [i]= 0; // Sino concatemanos 0
                }
                dividendo = dividendo/2; // Actualizamos el valor del dividendo dividiendolo entre 2.
            
                i++;
            }
            if(dividendo == 1)
                binario[i]=1; // Por último sí el valor final del dividendo es 1 concatenamos 1 sino concatenamos 0.
            else
                binario [i]= 0;

            //printf("Número Binario: ");
            i++;
            //printf("valor de i: %d \n\n", i);
            if( i < 4 ){
                if(i==1){
                    binAux[0]=0;
                    binAux[1]=0;
                    binAux[2]=0;
                    binAux[3]=binario[0];
                }
                if(i==2){
                    binAux[0]=0;
                    binAux[1]=0;
                    binAux[3]=binario[0];
                    binAux[2]=binario[1];
                }
                if(i==3){
                    binAux[0]=0;
                    binAux[3]=binario[0];
                    binAux[2]=binario[1];
                    binAux[1]=binario[2];
                }
                
            }else{
                binAux[3]=binario[0];
                binAux[2]=binario[1];
                binAux[1]=binario[2];
                binAux[0]=binario[3];
                
            }
            //printf("\nvalor de x: %d\n", x );
            for (i=0; i<4; i++){
                    //printf("%u", binAux[i]);
                    if(x==0){
                        if(j==0)
                            B1[i]=binAux[i];
                        if(j==1)
                            B1[4+i]=binAux[i];
                    }
                    if(x==2){
                        if(j==0)
                            B2[i]=binAux[i];
                        if(j==1)
                            B2[4+i]=binAux[i];
                    }
                    if(x==4){
                        if(j==0)
                            B3[i]=binAux[i];
                        if(j==1)
                            B3[4+i]=binAux[i];
                    }
                    if(x==6){
                        if(j==0)
                            B4[i]=binAux[i];
                        if(j==1)
                            B4[4+i]=binAux[i];
                    }
                    if(x==8){
                        if(j==0)
                            B5[i]=binAux[i];
                        if(j==1)
                            B5[4+i]=binAux[i];
                    }
                    if(x==10){
                        if(j==0)
                            B6[i]=binAux[i];
                        if(j==1)
                            B6[4+i]=binAux[i];
                    }
                    if(x==12){
                        if(j==0)
                            B7[i]=binAux[i];
                        if(j==1)
                            B7[4+i]=binAux[i];
                    }
                    if(x==14){
                        if(j==0)
                            B8[i]=binAux[i];
                        if(j==1)
                            B8[4+i]=binAux[i];
                    }
                    if(x==16){
                        if(j==0)
                            B9[i]=binAux[i];
                        if(j==1)
                            B9[4+i]=binAux[i];
                    }
                    if(x==18){
                        if(j==0)
                            B10[i]=binAux[i];
                        if(j==1)
                            B10[4+i]=binAux[i];
                    }if(x==20){
                        if(j==0)
                            B11[i]=binAux[i];
                        if(j==1)
                            B11[4+i]=binAux[i];
                    }if(x==22){
                        if(j==0)
                            B12[i]=binAux[i];
                        if(j==1)
                            B12[4+i]=binAux[i];
                    }if(x==24){
                        if(j==0)
                            B13[i]=binAux[i];
                        if(j==1)
                            B13[4+i]=binAux[i];
                    }if(x==26){
                        if(j==0)
                            B14[i]=binAux[i];
                        if(j==1)
                            B14[4+i]=binAux[i];
                    }if(x==28){
                        if(j==0)
                            B15[i]=binAux[i];
                        if(j==1)
                            B15[4+i]=binAux[i];
                    }
                    if(x==30){
                        if(j==0)
                            B16[i]=binAux[i];
                        if(j==1)
                            B16[4+i]=binAux[i];
                    }
                    

                }
            //printf("Largo: %d \n", sizeof binario / sizeof *binario );
            j++;
        }
        x=x+j;
        //printf("\nvalor de x222: %d\n", x ); 

    }    
    printf("\n\n");
    printf("Matriz B en binario: \n\n");
    for(j=1; j<=16; j++){
        printf(" ");
        if(j==1){
            for (i=0; i<8; i++){
                printf("%u", B1[i]);                       
            }
        }
        if(j==2){
            for (i=0; i<8; i++){
                printf("%u", B2[i]);                       
            }
        }
        if(j==3){
            for (i=0; i<8; i++){
                printf("%u", B3[i]);                       
            }
        }
        if(j==4){
            for (i=0; i<8; i++){
                printf("%u", B4[i]);                       
            }
        }
        if(j==5){
            for (i=0; i<8; i++){
                printf("%u", B5[i]);                       
            }
        }
        if(j==6){
            for (i=0; i<8; i++){
                printf("%u", B6[i]);                       
            }
        }
        if(j==7){
            for (i=0; i<8; i++){
                printf("%u", B7[i]);                       
            }
        }
        if(j==8){
            for (i=0; i<8; i++){
                printf("%u", B8[i]);                       
            }
        }
        if(j==9){
            for (i=0; i<8; i++){
                printf("%u", B9[i]);                       
            }
        }
        if(j==10){
            for (i=0; i<8; i++){
                printf("%u", B10[i]);                       
            }
        }
        if(j==11){
            for (i=0; i<8; i++){
                printf("%u", B11[i]);                       
            }
        }
        if(j==12){
            for (i=0; i<8; i++){
                printf("%u", B12[i]);                       
            }
        }
        if(j==13){
            for (i=0; i<8; i++){
                printf("%u", B13[i]);                       
            }
        }
        if(j==14){
            for (i=0; i<8; i++){
                printf("%u", B14[i]);                       
            }
        }
        if(j==15){
            for (i=0; i<8; i++){
                printf("%u", B15[i]);                       
            }
        }
        if(j==16){
            for (i=0; i<8; i++){
                printf("%u", B16[i]);                       
            }
        }
        if(j%4==0){
            printf("\n");
        }

    }        
    return 0;
}






