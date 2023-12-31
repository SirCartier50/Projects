/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{4}
 * Sparse.c
 * main implementation for conducting sparse matrix operations
 ***/

#include<string.h>

#include"Matrix.h"

#define MAX_LEN 1000

int main(int argc, char* argv[]) {
    	FILE* in, * out;
    	char line[MAX_LEN];
	int size, nnz_A, nnz_B, row, column;
	int counter = 0;
	double val;
	char* token;
	Matrix A, B, C, D, E, F, G, Z, Y, X;
/*File io checks and open in and out files*/
	if (argc != 3) {
        	printf("Usage: %s <input file> <output file>\n", argv[0]);
        	exit(1);
    	}

    	in = fopen(argv[1], "r");
    	if (in == NULL) {
        	printf("Unable to open file %s for reading\n", argv[1]);
        	exit(1);
    	}

    	out = fopen(argv[2], "w");
    	if (out == NULL) {
        	printf("Unable to open file %s for writing\n", argv[2]);
        	exit(1);
    	}
/*gets the size and non zero count for both Matrices construct the Matrix*/
	if(fgets(line, MAX_LEN, in) != NULL){
		token = strtok(line, " ");
                if (token != NULL) {
                        size = atoi(token);
                        token = strtok(NULL, " ");
                }
                if (token != NULL) {
                        nnz_A = atoi(token);
                        token = strtok(NULL, " ");
                }
                if (token != NULL) {
                        nnz_B = atoi(token);
                }
    		A = newMatrix(size);
		B = newMatrix(size);
	}
	fgets(line, MAX_LEN, in);
/*adds to Matrix A*/
	while (fgets(line, MAX_LEN, in) != NULL) {
        	if (counter > nnz_A-1) {
                        break;
                }
		token = strtok(line, " ");
        	if (token != NULL) {
            		row = atoi(token);
            		token = strtok(NULL, " ");
        	}
        	if (token != NULL) {
            		column = atoi(token);
			token = strtok(NULL, " ");
        	}
		if(token != NULL){
			val = atof(token);
		}
		changeEntry(A, row, column, val);
		counter++;
		
    	}
/*reset counter and add to Matrix B*/
	counter = 0;
	while (fgets(line, MAX_LEN, in) != NULL) {
		if (counter > nnz_B-1) {
                        break;
                }
                token = strtok(line, " ");
                if (token != NULL) {
                        row = atoi(token);
                        token = strtok(NULL, " ");
                }
                if (token != NULL) {
                        column = atoi(token);
                        token = strtok(NULL, " ");
                }
                if(token != NULL){
                        val = atof(token);
                }
                changeEntry(B, row, column, val);
                counter++;
        }
/*print matrix*/
/*A*/
	fprintf(out, "A has %d non-zero entries:\n", nnz_A);
	printMatrix(out, A);
	fprintf(out, "\n");
	fprintf(out, "B has %d non-zero entries:\n", nnz_B);
        printMatrix(out, B);
        fprintf(out, "\n");
/*1.5*A*/
	fprintf(out,"(1.5)*A =\n");
   	C = scalarMult(1.5, A);
   	printMatrix(out, C);
   	fprintf(out, "\n");
/*A+B*/
	fprintf(out,"A+B =\n");
   	D = sum(A, B);
   	printMatrix(out, D);
   	fprintf(out, "\n");
/*A+A*/
	fprintf(out,"A+A =\n");
   	E = sum(A, A);
   	printMatrix(out, E);
   	fprintf(out, "\n");
/*B-A*/
	fprintf(out,"B-A =\n");
   	Z = diff(B, A);
   	printMatrix(out, Z);
   	fprintf(out, "\n");
/*A-A*/
	fprintf(out,"A-A =\n");
   	Y = diff(A, A);
   	printMatrix(out, Y);
   	fprintf(out, "\n");
/*transposed*/
	fprintf(out,"Transpose(A) =\n");
   	F = transpose(A);
   	printMatrix(out, F);
   	fprintf(out, "\n");
/*A*B*/
	fprintf(out, "A*B =\n");
   	G = product(A, B);
   	printMatrix(out, G);
   	fprintf(out, "\n");
/*B*B*/
	fprintf(out, "B*B =\n");
   	X = product(B, B);
   	printMatrix(out, X);
   	fprintf(out, "\n");
/*free and dip*/
	freeMatrix(&A);
   	freeMatrix(&B);
   	freeMatrix(&C);
   	freeMatrix(&D);
   	freeMatrix(&E);
   	freeMatrix(&Z);
   	freeMatrix(&Y);
   	freeMatrix(&F);
   	freeMatrix(&G);
   	freeMatrix(&X);
	fclose(in);
	fclose(out);
	return 0;
}
