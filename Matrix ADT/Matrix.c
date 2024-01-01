/***
 * Author: Mignot Mesele
 * Title: Matrix.c
 * Purpose: Matrix ADT
 * ***/

#include"Matrix.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
	int column;
	double data;
}EntryObj;

typedef struct MatrixObj{
	List *adj;
	int area;
	int nnz;
}MatrixObj;

Entry newEntry(int column, double data){
	Entry E = malloc(sizeof(EntryObj));
	E->column = column;
	E->data = data;
	return E;
}

void freeEntry(Entry* pE){
	if(pE !=NULL && *pE != NULL){
		free(*pE);
		*pE = NULL;
	}
}

Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->adj = malloc((n+1)*sizeof(List));
	M->area = n;
	M->nnz = 0;
	for( int i = 1; i <= n; i++){
		M->adj[i] = newList();
	}
	return M;
}

void freeMatrix(Matrix* pM){
	if(pM != NULL && *pM != NULL){
		makeZero(*pM);
		for(int i = 1; i <= (*pM)->area; i++){
			freeList(&((*pM)->adj[i]));
		}
		free((*pM)->adj);
		free(*pM);
		(*pM) = NULL;
	}
}
int size(Matrix M){
	return M->area;
}

int NNZ(Matrix M){
	return M->nnz;
}


int equals(Matrix A, Matrix B){
	if((A == NULL) || (B == NULL)){
                exit(EXIT_FAILURE);
        }
	if(size(A) != size(B)){
		return 0;
	}
        if(NNZ(A) != NNZ(B)){
		return 0;
        }
	Entry AE;
	Entry BE;
	for(int i = 1; i <= size(A); i++){
		if(length(A->adj[i]) != length(B->adj[i])){
			return 0;
		}
		moveFront(A->adj[i]);
                moveFront(B->adj[i]);
                while((index(A->adj[i]) >= 0) &&  (index(B->adj[i]) >= 0)){
                        AE = get(A->adj[i]);
                        BE = get(B->adj[i]);
                        if(AE->column == BE->column){
                                if(AE->data == BE->data){
                                	moveNext(A->adj[i]);
                                	moveNext(B->adj[i]);
				}else{
					return 0;
				}
			}else{
				return 0;
			}
                }
	}
	return 1;
}

void makeZero(Matrix M){
	for(int i = 1; i <= M->area; i++){
		moveFront(M->adj[i]);
		while(index(M->adj[i]) >= 0){
			Entry E =get(M->adj[i]);
			freeEntry(&E);
			M->nnz--;
			moveNext(M->adj[i]);
		}
		clear(M->adj[i]);
	}
}
 
void changeEntry(Matrix M, int i, int j, double x){
	if((i < 1) || (i>M->area) || (j<1) || (j > M->area)){
		printf("not in span\n");
		exit(EXIT_FAILURE);
	}
	Entry I;
	moveFront(M->adj[i]);
	if(list_is_empty(M->adj[i])){
		if(x != 0.0){
			Entry E = newEntry(j, x);
                        append(M->adj[i], E);
                        M->nnz++;
			return;
                }else{
			return;
                }
	}
	I = get(M->adj[i]);
	while(index(M->adj[i]) != -1 && j  > I->column ){
		moveNext(M->adj[i]);
		if(index(M->adj[i]) != -1){
			I = get(M->adj[i]);
		}
	}
	if(index(M->adj[i]) == -1){
		if(x != 0.0){
			Entry E = newEntry(j, x);
			append(M->adj[i], E);
			M->nnz++;
		}
	}else if(j < I->column){
		if(x != 0.0){
			Entry E = newEntry(j, x);
                	insertBefore(M->adj[i], E);
                        M->nnz++;
                }
	}else if(I->column == j){
		if(x == 0.0){
			freeEntry(&I);
			delete(M->adj[i]);
			M->nnz--;
		}else{
			I->data = x;
		}
	}
}

Matrix copy(Matrix A){
	Matrix CM = newMatrix(A->area);
	for (int i = 1; i <= A->area; i++){
		if(!(list_is_empty(A->adj[i]))){
			moveFront(A->adj[i]);
			for (int j =0 ; j < length(A->adj[i]); j++){
				Entry E = get(A->adj[i]);
				changeEntry(CM, i, E->column, E->data);
				moveNext(A->adj[i]);
			}
		}
	}
	return CM;
}
Matrix transpose(Matrix A){
	Matrix T = newMatrix(A->area);
	for(int i = 1; i <= A->area; i++){
		if(!(list_is_empty(A->adj[i]))){
			moveFront(A->adj[i]);
			for (int j =0 ; j < length(A->adj[i]); j++){
				Entry E = get(A->adj[i]);
				changeEntry(T, E->column, i,E->data);
				moveNext(A->adj[i]);
			}
		}
	}
	return T;
}
Matrix scalarMult(double x, Matrix A){
	Matrix xA = newMatrix(A->area);
	for(int i = 1; i <= A->area; i++){
		moveFront(A->adj[i]);
		while(index(A->adj[i]) >= 0){
			Entry E = get(A->adj[i]);
			changeEntry(xA,i,E->column, ((E->data) * x));
			moveNext(A->adj[i]);
		}
	}
	return xA;
}

Matrix sum(Matrix A, Matrix B){
	if((A == NULL) || (B == NULL)){
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		exit(EXIT_FAILURE);
	}
	if(equals(A, B)){
                Matrix A_B = scalarMult(2.0, A);
                return A_B;
        }
	Matrix A_B = newMatrix(A->area);
	Entry AE;
	Entry BE;
	for(int i = 1; i <= size(A); i++){
		moveFront(A->adj[i]);
		moveFront(B->adj[i]);
		while((index(A->adj[i]) >= 0) &&  (index(B->adj[i]) >= 0)){
			AE = get(A->adj[i]);
			BE = get(B->adj[i]);
			/*case 1: if the columns are the same then add and put in new matrix.
			 * case 2: if column from AE is less then column BE then add entry AE to matrix and only movenext on A.
			 * case 3: if column from BE was less than then add BE and move next*/
			if(AE->column == BE->column){
				changeEntry(A_B, i, AE->column, ((AE->data) + (BE->data)));
				moveNext(A->adj[i]);
				moveNext(B->adj[i]);
			}else if(AE->column < BE->column){
				changeEntry(A_B, i, AE->column, AE->data);
				moveNext(A->adj[i]);
			}else if(BE->column < AE->column){
				changeEntry(A_B, i, BE->column, BE->data);
                                moveNext(B->adj[i]);
			}
		}
		
		while(index(A->adj[i]) >= 0){
			AE = get(A->adj[i]);
			changeEntry(A_B, i, AE->column, AE->data);
                        moveNext(A->adj[i]);
		}
		while(index(B->adj[i]) >= 0){
                        BE = get(B->adj[i]);
                        changeEntry(A_B, i, BE->column, BE->data);
                        moveNext(B->adj[i]);
                }
		
	}
	return A_B;
}

Matrix diff(Matrix A, Matrix B){
        if((A == NULL) || (B == NULL)){
                exit(EXIT_FAILURE);
        }
        if(size(A) != size(B)){
                exit(EXIT_FAILURE);
        }
        Matrix A_B = newMatrix(A->area);
        Entry AE;
        Entry BE;
        for(int i = 1; i <= size(A); i++){
                moveFront(A->adj[i]);
                moveFront(B->adj[i]);
                while((index(A->adj[i]) >= 0) &&  (index(B->adj[i]) >= 0)){
                        AE = get(A->adj[i]);
                        BE = get(B->adj[i]);
                        if(AE->column == BE->column){
                                changeEntry(A_B, i, AE->column, ((AE->data) - (BE->data)));
                                moveNext(A->adj[i]);
                                moveNext(B->adj[i]);
                        }else if(AE->column < BE->column){
                                changeEntry(A_B, i, AE->column, AE->data);
                                moveNext(A->adj[i]);
                        }else if(BE->column < AE->column){
                                changeEntry(A_B, i, BE->column, -(BE->data));
                                moveNext(B->adj[i]);
                        }
                }
                
                while(index(A->adj[i]) >= 0){
                        AE = get(A->adj[i]);
                        changeEntry(A_B, i, AE->column, AE->data);
                        moveNext(A->adj[i]);
                }
                while(index(B->adj[i]) >= 0){
                        BE = get(B->adj[i]);
                        changeEntry(A_B, i, BE->column, -(BE->data));
                        moveNext(B->adj[i]);
                }

        }
        return A_B;
}
double vectorDot(List P, List Q){
        double total = 0.0;
        Entry PE;
        Entry QE;
        moveFront(P);
        moveFront(Q);
        while((index(P) >= 0) &&  (index(Q) >= 0)){
                PE = get(P);
                QE = get(Q);
                if(PE->column == QE->column){
                        total += ((PE->data) * (QE->data));
                        moveNext(P);
                        moveNext(Q);
                }else if(PE->column < QE->column){
                        moveNext(P);
                }else if(QE->column < PE->column){
                        moveNext(Q);
                }
        }
        return total;
}

Matrix product(Matrix A, Matrix B){
        if((A == NULL) || (B == NULL)){
                exit(EXIT_FAILURE);
        }
        if(size(A) != size(B)){
                exit(EXIT_FAILURE);
        }
        Matrix A_B = newMatrix(A->area);
	Matrix T = transpose(B);
	for(int i = 1; i <= size(A); i++){
		for(int j = 1; j<=size(T); j++){
			changeEntry(A_B, i, j, vectorDot(A->adj[i], T->adj[j]));
              	}
        }
	freeMatrix(&T);
        return A_B;
}



void printMatrix(FILE* out, Matrix M){
	for( int i = 1; i <= M->area; i++){
		moveFront(M->adj[i]);
		if(index(M->adj[i]) == -1){
			continue;
		}
		fprintf(out, "%d:", i);
		while(index(M->adj[i]) >= 0){
			Entry E = get(M->adj[i]);
			fprintf(out, " (%d, %.1f)", E->column, E->data);
			moveNext(M->adj[i]);
		}
		fprintf(out, "\n");
	}
}
