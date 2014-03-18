#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define N 512
int matrixa[N][N];
int matrixb[N][N];
int matrixc[N][N];

void computeMatrix(int, int);/* function header */
void printa();/*output a*/
void printb();/*output b*/
void printc();/*output c*/


int main(argc, argv)
int argc;
char *argv[];
{
    int randint, myid, numprocs, i ,j , procID;
    double seconds,time_spent;
    int verifymat[10][2];
    clock_t start, end;/*Time for the task*/
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Status status;
    if(myid == 0){
        for (i = 0 ; i < N ; i ++){
            for( j = 0; j < N ; j++){
                randint = rand() % 2;
                matrixa[i][j] = randint;
                randint = rand() % 2;
                matrixb[i][j] = randint;
            }
        }
        for (i=0 ; i<10 ;i++){
            for (j=0; j<2; j++){
                verifymat[i][j] = rand() % 512;
            }
        }
       /* printa();
        printb();Used for testing and verification*/
        start = clock();
        MPI_Bcast(matrixb,N*N,MPI_INT,0,MPI_COMM_WORLD);/*Send B to all processors */
        for( i=1; i < numprocs; i ++){/*Send only a portion of A to each process */
            MPI_Send(matrixa  + (i*(N/numprocs)), ((N*N)/numprocs), MPI_INT,i,i, MPI_COMM_WORLD);
        }

        computeMatrix(0, N/numprocs);/*Compute the root's portion*/
        
        for(i=1 ; i < numprocs ; i ++){/*Get matrix C from the processors */
            MPI_Recv(matrixc + (i*(N/numprocs)), ((N*N)/numprocs), MPI_INT,i,i, MPI_COMM_WORLD, &status);
        }
        end = clock();
        /*printc();Used for testing and verification*/
        time_spent = (double)(end-start)/CLOCKS_PER_SEC;
        printf(" %f with %i processors\n", time_spent, numprocs);
        for (i=0 ; i<10 ; i++){/*Verify matrix contents*/
            printf("c[%d][%d]=%d\n", verifymat[i][0],verifymat[i][1], matrixc[verifymat[i][0]][verifymat[i][1]]);
        }
    }
    else{
        /*All the processors get the B Matrix */
        MPI_Bcast(matrixb,N*N,MPI_INT,0,MPI_COMM_WORLD);
        /*All the processors get a certain part of A Matrix */
        MPI_Recv(matrixa + (myid*(N/numprocs)), ((N*N)/numprocs), MPI_INT, 0 , myid, MPI_COMM_WORLD, &status);
        computeMatrix( (myid*(N/numprocs)), (N/numprocs));/*Compute the matrix for this node */
        MPI_Send(matrixc + (myid*(N/numprocs)), ((N*N)/numprocs), MPI_INT, 0 , myid, MPI_COMM_WORLD);
        /*Send back to root*/
    }/*End else*/
    MPI_Finalize();
    return 0;
}
/*Computes a certain part of a matrix*/
void computeMatrix(int start, int stop){
    int i,j,k;
    for(i=start; i<start + stop; i ++){
        for(j=0; j<N; j++){
            matrixc[i][j] = 0;
            for(k=0 ; k<N; k++){
                matrixc[i][j] += matrixa[i][k] * matrixb[k][j];
            }
        }
    }
}
/*Prints matrixa, used for testing purposes*/
void printa(){
    int i,j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%d",matrixa[i][j]);
            printf(" ");
        }
        printf("\n");
    }
 
}
/*prints matrixb,uset for testing purposes*/
void printb(){
    int i,j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%d",matrixb[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}
/*prints matrixc, used for testing purposes*/
void printc(){
    int i,j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%d",matrixc[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

