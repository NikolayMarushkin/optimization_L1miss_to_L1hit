#include <iostream>
#include <ctime>

using namespace std;

#define SIZE_MATRIX 2000
#define BLOCK_SIZE_MATRIX 250
#define GRID_SIZE_MATRIX int(SIZE_MATRIX / double(BLOCK_SIZE_MATRIX))

int MatrixA[SIZE_MATRIX * SIZE_MATRIX] = { 0 };
int MatrixB[SIZE_MATRIX * SIZE_MATRIX] = { 0 };
int MatrixC[SIZE_MATRIX * SIZE_MATRIX] = { 0 };


int main() {
	clock_t start_t, end_t;
	for (int i = 0; i < SIZE_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_MATRIX; j++)
		{
			MatrixA[i * SIZE_MATRIX + j] = i + j + 1;
			MatrixB[i * SIZE_MATRIX + j] = i * SIZE_MATRIX + j + 1;
		}
	}

	start_t = clock();
	for (int n = 0; n < GRID_SIZE_MATRIX; n++)
		for (int m = 0; m < GRID_SIZE_MATRIX; m++)
			for (int iter = 0; iter < GRID_SIZE_MATRIX; iter++)
				for (int i = n * BLOCK_SIZE_MATRIX; i < (n + 1) * BLOCK_SIZE_MATRIX; i++)
					for (int j = m * BLOCK_SIZE_MATRIX; j < (m + 1) * BLOCK_SIZE_MATRIX; j++)
						for (int k = iter * BLOCK_SIZE_MATRIX; k < (iter + 1) * BLOCK_SIZE_MATRIX; k++)
							MatrixC[i * SIZE_MATRIX + j] = MatrixC[i * SIZE_MATRIX + j] + MatrixA[i * SIZE_MATRIX + k] * MatrixB[k * SIZE_MATRIX + j];

	end_t = clock();

	cout << (float)(end_t - start_t) / CLOCKS_PER_SEC << " sec. BlockMatrixMultiplication" << endl;

	system("Pause");
}
