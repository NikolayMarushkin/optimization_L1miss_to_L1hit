#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

#define SIZE_MATRIX 1000
#define BLOCK_SIZE_MATRIX 250 // L1 miss - 250, no miss 1000
#define GRID_SIZE_MATRIX int(SIZE_MATRIX / double(BLOCK_SIZE_MATRIX))

int 
MatrixA[SIZE_MATRIX][SIZE_MATRIX] = { 0 }, 
MatrixB[SIZE_MATRIX][SIZE_MATRIX] = { 0 }, 
MatrixC[SIZE_MATRIX][SIZE_MATRIX] = { 0 };


int main() {
	clock_t start_t, end_t;
	for (int i = 0; i < SIZE_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_MATRIX; j++)
		{
			MatrixA[i][j] = i * SIZE_MATRIX + j + 1;
			MatrixB[i][j] = i * SIZE_MATRIX + j + 1;
		}
	}
	
	start_t = clock();
	for (int n = 0; n < GRID_SIZE_MATRIX; n++)
		for (int m = 0; m < GRID_SIZE_MATRIX; m++)
			for (int iter = 0; iter < GRID_SIZE_MATRIX; iter++)
				for (int i = n * BLOCK_SIZE_MATRIX; i < (n + 1) * BLOCK_SIZE_MATRIX; i++)
					for (int j = m * BLOCK_SIZE_MATRIX; j < (m + 1) * BLOCK_SIZE_MATRIX; j++)
						for (int k = iter * BLOCK_SIZE_MATRIX; k < (iter + 1) * BLOCK_SIZE_MATRIX; k++)
							MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
	end_t = clock();
	cout << (float)(end_t - start_t) / CLOCKS_PER_SEC << " sec. BlockMatrixMultiplication" << endl;
	system("Pause");
}