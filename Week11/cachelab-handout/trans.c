//2016024893
/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]);
/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";


void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int block_size, block_row, block_col;
    int row, col, tmp, diagonal;

    if(N==64)
    {
        transpose_64_64(M,N,A,B);
    }

    else
    {
        if(N==32) block_size=8;
        else block_size=16;

        for(block_col=0;block_col<M;block_col+=block_size)
        {
            for(block_row=0;block_row<N;block_row+=block_size)
            {
                for(row=block_row;(row<N)&&(row<block_row+block_size);row++)
                {
                    for(col=block_col;(col<M)&&(col<block_col+block_size);col++)
                    {
                        if(row!=col) B[col][row]=A[row][col];
                        else
                        {
                            tmp=A[row][col];
                            diagonal=row;
                        }
                    }
                    if(block_row==block_col) B[diagonal][diagonal]=tmp;
                }
            }   
        }
    }

}

void transpose_64_64(int M, int N, int A[N][M], int B[M][N])
{
    int tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8;
    int i,j,k,t;

    for(i=0;i<N;i+=8)
    {
        for(j=0;j<M;j+=8)
        {
            for(k=i;k<i+4;k++)
            {
                tmp1=A[k][j+0];
                tmp2=A[k][j+1];
                tmp3=A[k][j+2];
                tmp4=A[k][j+3];
                tmp5=A[k][j+4];
                tmp6=A[k][j+5];
                tmp7=A[k][j+6];
                tmp8=A[k][j+7];

                B[j+0][k]=tmp1;
                B[j+1][k]=tmp2;
                B[j+2][k]=tmp3;
                B[j+3][k]=tmp4;
                B[j+0][k+4]=tmp5;
                B[j+1][k+4]=tmp6;
                B[j+2][k+4]=tmp7;
                B[j+3][k+4]=tmp8;           
            }

            for(k=j;k<j+4;k++)
            {
                tmp5=A[i+4][k];
                tmp6=A[i+5][k];
                tmp7=A[i+6][k];
                tmp8=A[i+7][k];

                tmp1=B[k][i+4];
                tmp2=B[k][i+5];
                tmp3=B[k][i+6];
                tmp4=B[k][i+7];

                B[k][i+4]=tmp5;
                B[k][i+5]=tmp6;
                B[k][i+6]=tmp7;
                B[k][i+7]=tmp8;

                B[k+4][i+0]=tmp1;
                B[k+4][i+1]=tmp2;
                B[k+4][i+2]=tmp3;
                B[k+4][i+3]=tmp4;

                for(t=0;t<4;t++) B[k+4][i+t+4]=A[i+t+4][k+4];
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

