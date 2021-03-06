/**
Użycie: Zmień wartości MDN, MN, FILEN skompiluj i odpal ./radix
Kompilacja: gcc radixSort.c -o radix -lrt
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MDN 14 // maks. dlugosc napisu
#define MN 50000 // maks il napisow
#define FILEN "50tys.txt"
#define MAX 60000l
#define MLD 1000000000.0 

char **A,**B,**T;
int min = 0, max = 0, N[MN], X[MN];

void drukuj(char **A,int n)
{
  // drukuje  drugie litery napisow i napisy  
  int i;
  for (i=0;i<n;i++){
    printf("[%i][%i] %s\n",i,N[i],A[i]);  
  }
}

void czytaj(char **A, int ilosc)
{
	char tmp[MDN];
	int i=0, y=0, size; 

	FILE *file = fopen( FILEN, "r" );

	if ( file == 0 )
	{
		printf( "Could not open file\n" );
	}
	else 
	{
		char *result;
		for (i = 0; i <= MN-1; ++i) 
		{
			result = fgets (tmp, MDN, file);
			if (result != NULL) 
			{
				size = strlen(tmp)-1;
				A[i] = (char*) malloc(sizeof(char)*(size+1));
				strcpy(A[i],tmp);
		  		N[i] = size;
			}
		}
	}
}

 int check(int x, int p, int j){
   if(p<=x) return *(A[j]+p);
   else return 0;
 }

void countingSort(char **A, char **B, int k, int p, int n)
{
	int i,j;
	int C[k+1];
	for (i=0;i<=k;i++) C[i]=0;
// 	printf("=====Wydruk Kontrolny => C[*(*(A+j)+p)] += 1\n");	//kontrola
	for (j=0;j<=n-1;j++){
	  C[check(N[j],p,j)] += 1;	//ilosc powtorzen liter
// 	  printf("%c %i\n",*(*(A+j)+p), C[*(*(A+j)+p)]);
	}
// 	printf("=============================================\n");
	for (i=1;i<=k;i++) C[i] += C[i-1];
	
//  	printf("=====Wydruk Kontrolny => *B[C[*(*(A+j)+p)]-1]=*A[j]\n");
	for (j=n-1;j>=0;j--){
// 	  	printf("B[%i] = A[%i]\tX[%i] = N[%i]\n", C[check(N[j],p,j)]-1, j, C[check(N[j],p,j)]-1, j); 		//kontrola
	        X[C[check(N[j],p,j)]-1]= N[j];
	        B[C[check(N[j],p,j)]-1]= A[j];
		C[check(N[j],p,j)] -= 1;
		}
// 	 	printf("=============================================\n");
}

int main()
{
	int n=MN;	// stringi
	int p, k=255;
	struct timespec tp0,tp1;
	double sp;

	A=(char**) malloc(n*sizeof(char*));
	B=(char**) malloc(n*sizeof(char*));
	czytaj(A,n); 

	int i;
	for(i=0, min=*N;i<n;i++)if (min > strlen(*(A+i))) min = strlen(*(A+i));
	for(i=0, max=*N;i<n;i++)if (max < strlen(*(A+i))) max = strlen(*(A+i));
	//printf("min = %i\tmax = %i\n",min,max);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
	for(p=max-1;p>=0;p--)
	{
	// 	  printf("p = %i\n",p);			//kontrola
	countingSort(A,B,k,p,n);
	T=A; 
	A=B; 
	B=T;

	int i;
	for(i=0;i<MN;i++) N[i]=X[i];
	} 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);

	printf("=====Wydruk Kontrolny=====\n");
	printf("\nWynik: \n"); drukuj(A,n);

	printf("\nPROCESS:\n"); 

	printf("stop  %12lu  %12lu \n",tp1.tv_sec, tp1.tv_nsec);

	printf("start %12lu  %12lu \n",tp0.tv_sec, tp0.tv_nsec);
	sp=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);

	printf("czas   %3.5lf\n",sp);   

return 0;
}
