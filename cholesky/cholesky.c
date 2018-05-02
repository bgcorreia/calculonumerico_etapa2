#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
/*-----------------------------------------------------------------------------
* Function: nrerror
* Description: SHOW A MESSAGE AND EXIT
*-----------------------------------------------------------------------------*/
void nrerror(char error_text[])
{
	printf("%s\n", error_text);
	exit(0);
};

/*-----------------------------------------------------------------------------
* Function: checkSymmetric
* Description: CHECK IF THE SQUARE MATRIX IS SYMMETRIC
*-----------------------------------------------------------------------------*/
void checkSymmetric(double **A, int n) {
int i,j;
for (i = 0; i < n; i++) {
for (j = i; j < n; j++)
if(A[i][j] != A[j][i])
nrerror("SEM SIMETRIA!");
}
}

/*-----------------------------------------------------------------------------
* Function: showSystem
* Description: SEND THE SYSTEM TO STANDART OUTPUT
*-----------------------------------------------------------------------------*/
void showSystem(double **A, int n, char c) {
int i,j;
printf("\n%*c[%c]\n", 7*n,' ', c);
for (i = 0; i < n; i++) {
for (j = 0; j < n; j++)
printf("|%+02.5lf|\t ", A[i][j]);
printf("\n");
}
}

/*-----------------------------------------------------------------------------
* Function: showArray
* Description: SEND THE ARRAY TO STANDART OUTPUT
*-----------------------------------------------------------------------------*/
void showArray(double *X, int n, char c) {
int i;
printf("\n");
for (i = 0; i < n; i++) {
printf("%c[%d] = %2.5lf\n",c,i, X[i]);
}
}
/*-----------------------------------------------------------------------------
* Function: createArray
* Description: RETURN ONE POINTER FOR A ARRAY [N]
*-----------------------------------------------------------------------------*/
double *createArray(int N)
{
double *array;

if (( array = malloc( N*sizeof( double ))) == NULL ) {
nrerror("SEM MEMORIA!");
}

return array;
}

/*-----------------------------------------------------------------------------
* Function: createMatrix
* Description: RETURN ONE POINTER FOR A MATRIX [N,N]
*-----------------------------------------------------------------------------*/
double **createMatrix(int N)
{
double **matrix;
int i;

/* N IS THE NUMBER OF ROWS */
if (( matrix = malloc( N*sizeof( double* ))) == NULL ) {
nrerror("SEM MEMORIA!");
}

/* N IS THE NUMBER OF COLUMNS */
for ( i = 0; i < N; i++ )
{
if (( matrix[i] = malloc( N*sizeof( double ))) == NULL )
{
nrerror("SEM MEMORIA!");
}
}

/* NxN MATRIX */
return matrix;
}

/*-----------------------------------------------------------------------------
* Function: Cholesky
* Description: THE CHOLESKY DECOMPOSITION
*-----------------------------------------------------------------------------*/
double **cholesky(double **A, int n)
{
int i, j, k;
double sum;
double **G;

/* CREATE THE MATRIX WITH THE SAME SIZE OF A */
G = createMatrix(n);

for (k = 0; k < n; k++)
for (i = 0; i <= k; i++)
{
/* THE SUM IS THE SAME FOR BOTH SITUACION */
sum = 0;
for (j = 0; j < i; j++)
{
sum += G[i][j] * G[k][j];
}

/* CALCULATE THE Gkk AND Gjk */
if (i == k)
{
if(A[i][i] - sum <= 0)
nrerror("NAO DEFINIDA POSITIVA");
G[i][i] = sqrt(A[i][i] - sum);
}
else
G[k][i] = 1.0 / G[i][i] * (A[k][i] - sum);
}

/* RETURN THE DECOMPOSITION */
return G;
}

/*-----------------------------------------------------------------------------
* Function: choleskySolucion
* Description: SOLVE THE SYSTEM PREVIOLYS CALCULATED
*-----------------------------------------------------------------------------*/
void choleskySolucion(double **a, int n, double b[], double x[])
{
int i,j;
double sum;

/* SOLVE THE SYSTEM AND STORE THE ANSWER Y IN X */
for(i = 0; i < n; ++i) {
sum = 0;

for(j = 0; j < i; ++j)
sum += a[i][j] * x[j];

x[i] = (b[i] - sum) / a[i][i];
}

/* showArray(x,n,'y'); */

/* SOLVE THE SYSTEM USING 'Y' CALCULATED BEFORE, AND STORE THE ANSWER IN X */
for (i=n-1;i>=0;i--) {
sum=0;
for(j = i+1; j < n; j++)
sum += a[j][i] * x[j];

x[i] = (x[i] - sum) / a[i][i];
}

/* showArray(x,n,'x'); */

}

/*-----------------------------------------------------------------------------
* Function: main
* Description:
*-----------------------------------------------------------------------------*/
int main()
{
int i,resp;
double **A; /* MATRIX A */
double **G; /* CHOLESKY ANSWER */
double *B; /* ARRAY B */
double *X; /* RESULT */
int N = 3; /* SIZE OF DATA */

/***************************************************************************
* PUT THE EDSON's CODE BELOW
*/

A = createMatrix(N);
B = createArray(N);
X = createArray(N);

A[0][0] = 25; A[0][1] = 15; A[0][2] = -5;
A[1][0] = 15; A[1][1] = 18; A[1][2] = 0;
A[2][0] = -5; A[2][1] = 0; A[2][2] = 11;
/*A[3][0] = 8; A[3][1] = -10; A[3][2] = 18; A[3][3] = 46;
*/
B[0] = 1;
B[1] = 0;
B[2] = 0;
/*B[3] = 0;
*/

/***************************************************************************/

/* CHECK IF THE SYSTEM READ IS REALLY SYMMETRIC */
checkSymmetric(A, N);

/* SHOW THE SYSTEM READ */
showSystem(A,N,'A');

/* CALCULATE THE CHOLESKY MATRIX AND STORE IN G */
G = cholesky(A, N);

/* SHOW THE MATRIX CALCULATED WITH CHOLESKY METHOD */
showSystem(G,N,'G');

/* SOLVE THE SYSTEM Ax=B USING THE CHOLESKY MATRIX CALC BEFORE */
choleskySolucion(G, N, B, X);

/* SHOW THE ANSWER */
showArray(X,N,'x');

/* CHANGE THE ARRAY B AND SOLVE THE SYSTEM WITH THE SAME CHOLESKY MATRIX */
do
{
printf("\nDeseja alterar o vetor B?\n\t1 - Sim\n\t0 - Nao\n# ");
scanf("%d", &resp);
if(resp)
{
for(i=0;i<N;i++)
{
printf("B[%03d]=",i);
scanf("%lf", &B[i]);
}

choleskySolucion(G, N, B, X);
showArray(X,N,'x');

}
}while(resp);

/* REALEASE THE MATRIX CREATED IN BEGINNING */
free(A);
free(G);
free(B);
free(X);

return 1;
}
