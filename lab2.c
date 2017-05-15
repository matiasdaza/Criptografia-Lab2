    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>


    /* FUNCIONES DEFINIDAS ALGORITMO AES*/
    int Hexadecimal(int A[128],int indice); 
    void ShiftRow(int Baux[32]);
    void MixColumn (int BSalida[32]);
    char * conToBin (int n);
    

     /* FUNCIONES PARA TRABAJAR EN GF2*/
    int * getpolinomio(int B[128],int inicio, int fin, int pol);
    int * sumpolinomio(int *p1,int *p2, int *p3, int *p4);
    void final(int *pres);


    int main(void)
    {
       int i, A[128], B[128], indice=1;
       unsigned semilla = (unsigned)time(NULL);
       

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
        printf("\n");
        printf("Matriz de entrada A: "); 
        printf("\n");

        i=1;
        while (i<=128){
            printf ("%d", A[i]);
            
            if(indice==8){
                printf(" ");
                indice=0;   
            }
            indice++;
            if (i==32 || i == 64 || i == 96 || i == 128){
                printf("\n");
                
            }
            i++;
        }
        
        indice=1;
        Hexadecimal(A, indice);
        return 0;

    }

    //Generamos B

     int Hexadecimal(int A[128], int indice){ //

        printf("\n");
        printf("Matriz A en Hexadecimal: "); 
        printf("\n");

        int  i, j=0, Baux[32], L,R; 
        i = indice*8;   
        while( i <= 128 ){


            R = A[i]*1 + A[i-1]*2 + A[i-2]*4 + A[i-3]*8;
            L = A[i-4]*1 + A[i-5]*2 + A[i-6]*4 + A[i-7]*8;

            if (indice < 11)
                printf("B%d  = %X%X ", indice-1, L,R); //Con %X se le da formato hex en pantalla 
            else
                printf("B%d = %X%X ", indice-1, L,R); //Con %X se le da formato hex en pantalla

            printf(" ");

            if (indice == 4 || indice == 8 || indice == 12 || indice == 16)
                printf("\n");

            Baux[j]=L;
            j++;
            Baux[j]=R;
            j++;
                
            indice=indice+1;
            i=indice*8;
        
        }
            
        ShiftRow(Baux);   
        
    }


    void ShiftRow(int Baux[32]){
        int i=0, j=1, x=0, BEntrada[32], BSalida[32];


    //Aquí hacemos las asignaciones para ordenar la matriz de la forma necesaria para realizar el Shift Row
    //BEntrada es la matriz de entrada para el shift row que lo ocuparemos solo para mostrarlo en la entrada
    //y BSalida es la matriz luego de aplicado el Shift Row y con la que haremos el Mix Column

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

    void MixColumn(int BSalida[32])
    {
        int i, j, k, l, r, m, n, x, aux, inicio, fin, ind=0,B[128];
        int *p1,*p2,*p3,*p4,*pres;


        char str[5],bin[134];  

        const int MatPol[4][4] = { { 02, 03, 01, 01 },
                                   { 01, 02, 03, 01 },
                                   { 01, 01, 02, 03 },
                                   { 03, 01, 01, 02 }};

        /*B[16] = { BO(0,7)     B4(8,15)    B8(16,23)   B12(24,31)   },
                  { B5(32,39)   B9(40,47)   B13(48,55)  B1(56,63)    },
                  { B10(64,71)  B14(72,79)  B2(80,87)   B6(88,95)    },
                  { B15(96,103) B3(104,111) B7(112,119) B11(120,127) };  
        */
        int indB[16] = {0,32,64,96,8,40,72,104,16,48,80,112,24,56,88,120};
        i=0;
        j=1;
        printf("\n");
        //Aquí la matriz BSalida de 32 bits enteros la convertimos a su equivalente en binario con la parte 
        //izquierda(l) y derecha (r) en la función conToBin, luego los 8 bits los guardamos como string en str.
        printf("Matriz B 8 bits: \n" );
            while (i <= 32){

                l = BSalida[i];
                i++;
                r = BSalida[i];
                i++;

                strcpy(str,conToBin(l));
                strcat(str,conToBin(r));
                printf("%s ", str);
                if (j==4){
                    printf("\n");
                    j=0;
                }
                j++;
                strcat(bin,str);     
            }

        //Pasamos la matriz de char a int
        for (i=0; i<=127; i++){
            B[i] = bin[i]-48;
        }
           

        printf("\n");
        //Matriz shiftrow multiplicada por la matriz de polinomios
        printf("Matriz final: \n\n");
           
        ind=k=aux=m=n=x=0;
        while(k < 16){

            while (m <= 3){

                while (n <= 3){
                    aux = MatPol[m][n];
                    n++;
                    inicio = indB[k];
                    fin = inicio+7;
                    k++;
                    p1 = getpolinomio(B,inicio,fin,aux);
                    
                    aux = MatPol[m][n];
                    n++;
                    inicio = indB[k];
                    fin = inicio+7;
                    k++;
                    p2 = getpolinomio(B,inicio,fin,aux);
                   
                    aux = MatPol[m][n];
                    n++;
                    inicio = indB[k];
                    fin = inicio+7;
                    k++;
                    p3 = getpolinomio(B,inicio,fin,aux);
                    
                    aux = MatPol[m][n];
                    n++;
                    inicio = indB[k];
                    fin = inicio+7;
                    k++;
                    p4 = getpolinomio(B,inicio,fin,aux);
                   
                    //pres guarda el resultado de cada fila por cada columna
                    pres = sumpolinomio(p1,p2,p3,p4);

                    printf("C[%d] ",x);
                    x++; 

                    for (i=0;i<=7;i++){
                        
                        printf("%d ",pres[i]);
                    }
                    final(pres);
                    printf("\n");
            
                }
                
                m++;
                n=0;
                k=ind*4;
                aux=0;
                
                  
            }
            ind++;
            k=ind*4;
            m=n=0;
            
            printf("\n");
            

        }
        /*r1[128] = { CO(0,7)    C4(32,39)  C8(64,71)   C12(96,103)  },
                    { C1(8,15)   C5(40,47)  C9(72,79)   C13(104,111) },
                    { C2(16,23)  C6(48,55)  C10(80,87)  C14(112,119) },
                    { C3(24,31)  C7(56,63)  C11(88,95)  C15(120,127) };  
        */
        


    }    
    void final(int *pres)
    {
        //Con la matriz final mostramos nuevamente la parte izquierda y derecha como hexadecimal
        int L,R;

            L = pres[0]*8 + pres[1]*4 + pres[2]*2 + pres[3]*1;
            R = pres[4]*8 + pres[5]*4 + pres[6]*2 + pres[7]*1;

            printf(" %X%X ", L,R);
            
    }
    

    int * getpolinomio(int B[128],int inicio, int fin, int pol)
    {
        int i,n, *p;
        p=malloc((1+fin)*sizeof(int));
        int Pirreducible[8] = {0,0,0,1,1,0,1,1};
        
            //si polinomio es 1 el resultado será la misma matriz
            if (pol == 01){
                for (i=0;i<=7;i++){
                    p[i] = B[inicio];
                    inicio++;
                }
                return(p); 
            }

            //si polinomio es 2(x) el resultado será la misma matriz con un deslizamiento a la izquierda
            if (pol == 02){
                for (i=0;i<=6;i++){
                    p[i] = B[inicio+1];
                    inicio++;
                }
                return(p);
                                                                                                           
            }
            //si polinomio es 3(x+1) el resultado será la misma matriz con un deslizamiento a la izquierda +
            //la matriz original
            if (pol == 03){
                
                    p[0] = B[inicio+1]+B[inicio];
                    p[1] = B[inicio+2]+B[inicio+1];
                    p[2] = B[inicio+3]+B[inicio+2];
                    p[3] = B[inicio+4]+B[inicio+3];
                    p[4] = B[inicio+5]+B[inicio+4];
                    p[5] = B[inicio+6]+B[inicio+5];
                    p[6] = B[inicio+7]+B[inicio+6];
                    p[7] = 0+B[inicio+7];
                
                    for (n=0;n<=7;n++){

                        if (p[n] == 2)
                            p[n]=0;
                            
                        if (B[inicio]==1){
                            if (p[n] == Pirreducible[n])
                                p[n]=0;
                            
                            else
                                p[n]=1;
                        }
                    }
                    return(p);
            }       
        
    }
    
    int * sumpolinomio(int *p1,int *p2, int *p3, int *p4)
    {
        int i,n, *p;
        p=malloc((8)*sizeof(int));
        
        for (i=0;i<=7;i++){
            if (p1[i]==p2[i] || p3[i]==p4[i])
                p[i]=0;
            if (p1[i]!=p2[i] || p3[i]!=p4[i])
                p[i]=0;
            if (p1[i]==p2[i]==p3[i]==p4[i])
                p[i]=0;
            else 
                p[i]=1;
        }
        return(p);
    }


    char * conToBin (int n) // Función que retorna el puntero del valor en binario
    {   
        int j;

        char  *string;
        string = malloc(sizeof(char)*4);

        char *hexToBin[16] = {"0000", "0001", "0010", "0011", "0100", "0101","0110", "0111", 
                              "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

        for(j = 0; j < 16; j++){
            if(n == j)
                strcat(string, hexToBin[j]);
        }      
        return string;
       
    }
