#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
   int i, j, aux, ind;
   int P1[8] = {0,0,0,0,0,0,0,1} , P2[8] = {0,0,0,0,0,0,1,0}, P3[8] = {0,0,0,0,0,0,1,1};
      
   
   	const int MatC[4][4] = { { 02, 03, 01, 01 },
                         	{ 01, 02, 03, 01 },
                          	{ 01, 01, 02, 03 },
                          	{ 03, 01, 01, 02 }};


   //Recorre la matriz C para multiplicar con la matriz B


   for (i = 0; i< 4; i++){
     for (j = 0; j< 4; j++){
       
          aux = MatC[i][j];

          if ( aux == 01 ){

				for (ind = 0; ind < 8; ind++){

   					printf("%d ", P1[ind]);
		
   				}
   				printf("\n");  
          	}
          if ( aux == 02 ){

          		for (ind = 0; ind < 8; ind++){

   					printf("%d ", P2[ind]);
		
   				}
   				printf("\n");
       		}
          if ( aux == 03 ){

          		for (ind = 0; ind < 8; ind++){

   					printf("%d ", P3[ind]);
		
   				}
   				printf("\n");
	        }
        }
    }
  
  	printf("\n");
   

  
}  


  
  
    
        
  

  
 

