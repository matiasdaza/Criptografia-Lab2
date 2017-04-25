#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int Hexadecimal(int A[128],int indice); //, int indice
void mostrar(int Baux[32]);
void MixColumn (int BSalida[32]);
//int conversor (int auxB, int base1, int base2);



int main(void)
{
   int i, A[128], B[128], indice=1, Mat[128];
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
   

//Mostramos Matriz A y guardamos Mat con numero binario
    
    printf("Matriz de entrada A: "); 
    printf("\n");

    i=1;
    while (i<=128){
        printf ("%d", A[i]);
        i++;
        if(indice==8){
            printf("\n");
            indice=0;   
        }
        indice=indice+1;
    }
    
   
    printf("\n");
    printf("\n");

    

    indice=1;
    Hexadecimal(A, indice);
    return 0;

}

//Generamos B

 int Hexadecimal(int A[128], int indice){ //

    int  i, j, k=5, Baux[32], auxL[64], auxR[64],L,R, N[8]; //En N guardamos el número completo de 8 bits

    i = indice*8;   
    while( i <= 128 ){

        N[7] = A[i];   //R4
        N[6] = A[i-1]; //R3
        N[5] = A[i-2]; //R2
        N[4] = A[i-3]; //R1
        N[3] = A[i-4]; //L4
        N[2] = A[i-5]; //L3 
        N[1] = A[i-6]; //L2
        N[0] = A[i-7]; //L1

        
        printf("\n"); 
        //Con %X se le da formato hex en pantalla 
        printf(" Hexadecimal B%d = %X%X ", indice-1, (N[3] *1 + N[2]*2 + N[1]*4 + N[0]*8),N[7]*1 + N[6]*2 + N[5]*4 + N[4]*8); 

        for (j=1; j <= 8; j++){         //Arreglo para los 8 bits binarios
            auxL[j] = N[j];
            printf("%d", auxL[j] ); 
        }


                  
        indice=indice+1;
        i=indice*8;
        
    }
    system("pause");   
    //mostrar(Baux);   
    
}


void mostrar(int Baux[32]){
    int i=0, j=1, x=0, BEntrada[32], BSalida[32];


//Aquí hacemos las asignaciones para ordenar la matriz de la forma necesaria para realizar el Shift Row
//BEntrada es la matriz de entrada para el shift row que lo ocuparemos solo para mostrarlo en la entrada
//y BSalida es la matriz luego de aplicado el Shift Row y con la que haremos el Mix Column

    //0
    BEntrada[0]=BSalida[0]=Baux[0];
    printf("%d %d %d \n",BEntrada[0], BSalida[0], Baux[0]  );
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

    
    printf("\n \n Matriz B de entrada para Shift Row: \n \n");
    for(i=0; i < 32; i = i+1){
        
        if(j==9)
        {
            printf("\n");
            j=1;
        }
        if(i%2==0){
            printf(" ");
        }
 
        printf("%X", BEntrada[i]);

        j++;

    }

//Mostramos BSalida

    j=1;
    printf("\n \n Matriz B de salida luego del Shift Row: \n \n");
    for(x=0; x < 32; x = x+1){

        
        if(j==9)
        {
            printf("\n");
            j=1;
        }
        if(x%2==0){
            printf(" ");

        }
        printf("%X", BSalida[x]);

        j++;


    }
    printf("\n");
    MixColumn(BSalida);
    
}

void MixColumn (int BSalida[32]){
   int i, j,k=0, aux,  auxP, ind, bin, L[16], R[16], auxL[32], auxR[32];
   int P1[8] = {0,0,0,0,0,0,0,1} , P2[8] = {0,0,0,0,0,0,1,0}, P3[8] = {0,0,0,0,0,0,1,1};
   char hex[16] ;
   
    const int MatPol[4][4] = { { 02, 03, 01, 01 },
                               { 01, 02, 03, 01 },
                               { 01, 01, 02, 03 },
                               { 03, 01, 01, 02 }};


   
    i=0;
    for (j = 0; j < 16; j++){
        while (i < 32){

            auxL[i] = BSalida[i];
            auxR[i+1] = BSalida[i+1];

            //hex[j];
            //strcat(hex,L);
            //strcat(hex,R);
        
        //bin = HexToBinary(auxB);
        //bin = conversor(auxB,2,10);
            printf("%d %d ", auxL[i],auxR[i+1]);
            i = i + 2;
        }
    }    
    printf("\n");


    //Recorre la matriz C para multiplicar con la matriz BSalida
    for (i = 0; i< 4; i++){
     for (j = 0; j< 4; j++){
       
          auxP = MatPol[i][j];

          if ( auxP == 01 ){

                for (ind = 0; ind < 8; ind++){

                    //printf("%d ", P1[ind]);
        
                }
                printf("\n");  
            }
          if ( auxP  == 02 ){

                for (ind = 0; ind < 8; ind++){

                    //printf("%d ", P2[ind]);
        
                }
                printf("\n");
            }
          if ( auxP  == 03 ){

                for (ind = 0; ind < 8; ind++){

                    //printf("%d ", P3[ind]);
        
                }
                printf("\n");
            }
        }
    }
    
}


/*int conversor(int auxB,int base1,int base2)
{
   int alg, mult=1, n2=0;

    while (auxB > 0){
        alg = auxB % base1;
        auxB = auxB / base1;
        n2 = (alg*mult) + n2;
        mult = base2 * mult;
    }
    return n2;
}
*/


//int HextoBin (int auxB[4])

/*int binario (int x){
    int dividendo, resto, divisor = 2, binario[4], i=0, binAux[4]={0,0,0,0}, j;
    printf("\nNÚMERO DECIMAL= %d \n", x);
    dividendo = x;
    //printf("\nhola1= %d \n", dividendo);
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
        //printf("\n Dividendo /2 = %d", dividendo);
    
        i++;
    }
    if(dividendo == 1)
        binario[i]=1; // Por último sí el valor final del dividendo es 1 concatenamos 1 sino concatenamos 0.
    else
        binario [i]= 0;
    //printf("valor de i: %d \n\n", i);

    for (j=0; j<4; j++){
            printf("%u", binario[j]);

        }

    //printf("\n\n");
    printf("Número Binario: ");
    i++;
    printf("valor de i: %d \n\n", i);
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
    for (i=0; i<4; i++){
            printf("%u", binAux[i]);

        }
    //printf("Largo: %d \n", sizeof binario / sizeof *binario );
    return 0;


}

*/