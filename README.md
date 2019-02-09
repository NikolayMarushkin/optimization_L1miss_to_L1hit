# Отчет: L1 cache miss -> L1 cache hit
Для данной задачи будут рассмотрены алгоритмы умножения матриц
#### Характеристики компьютера:

- CPU: Intel Core i7-8700K (L1	384 Kb, L2	1.5 Mb, L3	12 Mb)
- RAM: DDR4 16 Gb
#### Стандартный алгоритм умножениия матриц:

```с++
for (int i = 0; i < SIZE_MATRIX; i++) 
	{
		for (int j = 0; j < SIZE_MATRIX; j++)
		{
			for (int k = 0; k < SIZE_MATRIX; k++)
			{
				MatrixC[i * SIZE_MATRIX + j] += MatrixA[i * SIZE_MATRIX + k] * MatrixB[k * SIZE_MATRIX + k];
			}
		}
	}
```

##### У данного подхода есть недостаток: при возрастащей размерности матрицы, процессор не сможет эффективно использовать кэш-память, поэтому необходимо использовать другой алгоритм: Блочное умножение матриц.

Чтобы узнать какой максимальный размер блока матрицы использовать для получения L1 cache miss:
* int = 4 byte

* 384 Kb = 393 216 byte

* Количество элементов int в матрице = 393 216 byte / 4 byte = 98 304

* Размерность (высота/ширина) квадратной матрицы sqrt(98 304) = ~314

Чтобы узнать какой максимальный размер блока матрицы использовать для получения L3 cache miss:
* int = 4 byte

* 12 Mb = 12 582 912 byte

* Количество элементов int в матрице = 12 582 912 byte / 4 byte = 3 145 728

* Размерность (высота/ширина) квадратной матрицы sqrt(3 145 728) = ~1774



### Алгоритм: Блочное умножение матриц

```с++
for (int n = 0; n < GRID_SIZE_MATRIX; n++)
		for (int m = 0; m < GRID_SIZE_MATRIX; m++)
			for (int iter = 0; iter < GRID_SIZE_MATRIX; iter++)
				for (int i = n * BLOCK_SIZE_MATRIX; i < (n + 1) * BLOCK_SIZE_MATRIX; i++)
					for (int j = m * BLOCK_SIZE_MATRIX; j < (m + 1) * BLOCK_SIZE_MATRIX; j++)
						for (int k = iter * BLOCK_SIZE_MATRIX; k < (iter + 1) * BLOCK_SIZE_MATRIX; k++)
							MatrixC[i * SIZE_MATRIX + j] = MatrixC[i * SIZE_MATRIX + j] + MatrixA[i * SIZE_MATRIX + k] * MatrixB[k * SIZE_MATRIX + j];


```

### Используя блочное умножение матриц:
* при размере блока: #define BLOCK_SIZE_MATRIX 2000 и размере матрицы #define SIZE_MATRIX 2000


24.4s

![L1_miss](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/BLOCK_SIZE_MATRIX%202000%20%23define%20SIZE_MATRIX%202000.jpg)

* при размере блока: #define BLOCK_SIZE_MATRIX 2 и размере матрицы #define SIZE_MATRIX 2000

16.31s

![L1_miss](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/BLOCK_SIZE_MATRIX%202%20SIZE_MATRIX%202000.jpg)

* при размере блока: #define BLOCK_SIZE_MATRIX 125 и размере матрицы #define SIZE_MATRIX 2000

12.45s

![L1_miss](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/BLOCK_SIZE_MATRIX%20125%20SIZE_MATRIX%202000.jpg)

* при размере блока: #define BLOCK_SIZE_MATRIX 250 и размере матрицы #define SIZE_MATRIX 2000
6.62s
![L1_miss](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/1%20BLOCK_SIZE_MATRIX%20250%20%23define%20SIZE_MATRIX%202000.jpg)

* при размере блока: #define BLOCK_SIZE_MATRIX 250 и размере матрицы #define SIZE_MATRIX 2000 и замене строки

6.1s

![L1_miss](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/2%20BLOCK_SIZE_MATRIX%20250SIZE_MATRIX%202000.jpg)


```с++
//Замена стоки
MatrixC[i * SIZE_MATRIX + j] += MatrixA[i * SIZE_MATRIX + k] * MatrixB[k * SIZE_MATRIX + j];
//На
MatrixC[i * SIZE_MATRIX + j] = MatrixC[i * SIZE_MATRIX + j] + MatrixA[i * SIZE_MATRIX + k] * MatrixB[k * SIZE_MATRIX + j];
```
 
## Вывод: 

*В результате исследования было однаружено, что:*

* Для умножения матриц, при возрастающей размерности, необходимо использовать алгоритм блочного умножения матриц;
* При размерности (высота/ширина) блока свыше 1500 элементов или совпадающим с размерностью матрицы, начинаются пропуски кэшей L1, L2, L3 и появляется большой % Memory Bound;
* При размерах блока мнного меньшего размера матрицы, например = 2, ситуация улучшается уменьшаются пропуски кэшей L1, L2, L3 и уменьшается % Memory Bound;
* При расчете выше: "Размерность (высота/ширина) квадратной матрицы" видно что, если брать размер блока свыше 314 элементов, то появляются пропуски кэшей, отсюда следует, что нужно брать размерность не слишком маленькую и не слишком большую, а приближенную к данному размеру;
* При замене строк, % Memory Bound и Back-End-Bound уменьшется.



