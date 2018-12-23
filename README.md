# optimization L1miss to L1hit
L1 cache miss L2 cache hit -> L1 cache hit

Алгоритм: блочное умножение двух матриц
#define SIZE_MATRIX 1000
#define BLOCK_SIZE_MATRIX 250

Если SIZE_MATRIX = BLOCK_SIZE_MATRIX, тогда "no miss L1 cache", иначе "L1 miss cache"

SIZE_MATRIX = BLOCK_SIZE_MATRIX: 2.942 sec.
SIZE_MATRIX != BLOCK_SIZE_MATRIX: 1.969 sec.

#### [L1 cache miss.exe](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/L1%20cache%20miss.exe)
![L1_miss](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/L1_miss.jpg)
#### [L1 cache not miss.exe](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/L1%20cache%20no%20miss.exe)
![L1_miss](https://github.com/NikolayMarushkin/optimization_L1miss_to_L1hit/blob/master/L1_no_miss.jpg)



