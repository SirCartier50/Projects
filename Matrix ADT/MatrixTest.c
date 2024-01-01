/***
 * Author: Mignot Mesele
 * Title: MatrixTest.c
 * Purpose: Testing file for Matrix ADT
 * ***/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=100;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H, Z, Y, X;
	printf("size: %d\n", size(A));
   changeEntry(A, 1,1,1.5); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

printf("A\n");
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");



printf("B\n");
   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");
printf("(1.5)*A\n");
   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");
printf("A+B\n");
   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");
printf("A+A\n");
   E = sum(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");
printf("B-A\n");
   Z = diff(B, A);
   printf("%d\n", NNZ(Z));
   printMatrix(stdout, Z);
   printf("\n");
printf("A-A\n");
   Y = diff(A, A);
   printf("%d\n", NNZ(Y));
   printMatrix(stdout, Y);
   printf("\n");
printMatrix(stdout, A);
printf("transpose\n");
   F = transpose(B);
   printf("%d\n", size(F));
   printMatrix(stdout, F);
   printf("\n");

printf("A*B\n");
   G = product(A, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");
printf("X\n");
   X = product(B, B);
   printf("%d\n", NNZ(X));
   printMatrix(stdout, X);
   printf("\n");

printf("H\n");
   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("here\n");
   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );
printf("another\n");
   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
printf("ge\n");
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&X);
   freeMatrix(&H);
   freeMatrix(&Z);
   freeMatrix(&Y);
   return EXIT_SUCCESS;
}

/*
 * Output of this program:
 * 9
 * 1: (1, 1.0) (2, 2.0) (3, 3.0)
 * 2: (1, 4.0) (2, 5.0) (3, 6.0)
 * 3: (1, 7.0) (2, 8.0) (3, 9.0)
 *
 * 6
 * 1: (1, 1.0) (3, 1.0)
 * 2: (2, 1.0)
 * 3: (1, 1.0) (2, 1.0) (3, 1.0)
 *
 * 9
 * 1: (1, 1.5) (2, 3.0) (3, 4.5)
 * 2: (1, 6.0) (2, 7.5) (3, 9.0)
 * 3: (1, 10.5) (2, 12.0) (3, 13.5)
 *
 * 9
 * 1: (1, 2.0) (2, 2.0) (3, 4.0)
 * 2: (1, 4.0) (2, 6.0) (3, 6.0)
 * 3: (1, 8.0) (2, 9.0) (3, 10.0)
 *
 * 0
 *
 * 6
 * 1: (1, 1.0) (3, 1.0)
 * 2: (2, 1.0) (3, 1.0)
 * 3: (1, 1.0) (3, 1.0)
 *
 * 7
 * 1: (1, 2.0) (2, 1.0) (3, 2.0)
 * 2: (2, 1.0)
 * 3: (1, 2.0) (2, 2.0) (3, 2.0)
 *
 * 9
 * 1: (1, 1.0) (2, 2.0) (3, 3.0)
 * 2: (1, 4.0) (2, 5.0) (3, 6.0)
 * 3: (1, 7.0) (2, 8.0) (3, 9.0)
 *
 * true
 * false
 * true
 * 0
 * */


