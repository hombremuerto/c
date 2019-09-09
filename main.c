#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define BENCH(Func) \
    printf("Benchmarking %s\n", #Func);\
    _Generic((Func), \
    	int (*)(int): bench1((Func)),\
    	int (*)(int, int): bench2((Func)),\
    	int (*)(int, int, int): bench3((Func)),\
	    int (*)(int, int, int, int): bench4((Func)),\
	    default : puts("Cannot bench this type of function. Function should take 1-4 int and should return int")\
	)
	
#define TEST(Func, Times) \
    printf("Testing %s\n", #Func);\
    _Generic((Func), \
    	int (*)(int): test1((Func), (Times)),\
    	int (*)(int, int): test2((Func), (Times)),\
    	int (*)(int, int, int): test3((Func), (Times)),\
	    int (*)(int, int, int, int): test4((Func), (Times)),\
	    default : puts("Cannot bench this type of function. Function should take 1-4 int and should return int")\
	)
	
int* getRandomInts(unsigned int size) {
	int *arr = (int*)malloc(size * sizeof(int));
	for (unsigned int i = 0; i < size; ++i) {
		arr[i] = rand();
		arr[i] <<= 16;
		arr[i] += rand();
	}
	return arr;
}

int* getRandomSmallInts(unsigned int size) {
	int *arr = (int*)malloc(size * sizeof(int));
	for (unsigned int i = 0; i < size; ++i) {
		arr[i] = rand() % 100;
		arr[i] -= 50;
	}
	return arr;
}

const unsigned int benchIters = 100 * 1000 * 1000;
#pragma GCC push_options
#pragma GCC optimize ("O0")
void bench1(int (*f)(int)) {
	int *x = getRandomInts(benchIters);
	clock_t begin = clock();
	for (unsigned int i = 0; i < benchIters; ++i) {
		f(x[i]);
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Benchmark took %lf sec\n", time_spent);
	free(x);
}
void bench2(int (*f)(int, int)) {
	int *x = getRandomInts(benchIters);
	int *y = getRandomInts(benchIters);
	clock_t begin = clock();
	for (unsigned int i = 0; i < benchIters; ++i) {
		f(x[i], y[i]);
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Benchmark took %lf sec\n", time_spent);
	free(x);
	free(y);
}
void bench3(int (*f)(int, int, int)) {
	int *x = getRandomInts(benchIters);
	int *y = getRandomInts(benchIters);
	int *z = getRandomInts(benchIters);
	clock_t begin = clock();
	for (unsigned int i = 0; i < benchIters; ++i) {
		f(x[i], y[i], z[i]);
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Benchmark took %lf sec\n", time_spent);
	free(x);
	free(y);
	free(z);
}
void bench4(int (*f)(int, int, int, int)) {
	int *x = getRandomInts(benchIters);
	int *y = getRandomInts(benchIters);
	int *z = getRandomInts(benchIters);
	int *w = getRandomInts(benchIters);
	clock_t begin = clock();
	for (unsigned int i = 0; i < benchIters; ++i) {
		f(x[i], y[i], z[i], w[i]);
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Benchmark took %lf sec\n", time_spent);
	free(x);
	free(y);
	free(z);
	free(w);
}
void test1(int (*f)(int), int iters) {
	int *x = getRandomSmallInts(iters);
	for (int i = 0; i < iters; ++i) {
		int res = f(x[i]);
		printf("For x1 = %d func returned %d\n", x[i], res);
	}
	for (int i = 0; i < 2; ++i) {
    	int y1 = (i & 1) ? INT_MIN : INT_MAX;
    	int res = f(y1);
    	printf("For x1 = %d func returned %d\n", y1, res);
	}
	free(x);
}
void test2(int (*f)(int, int), int iters) {
	int *x1 = getRandomSmallInts(iters);
	int *x2 = getRandomSmallInts(iters);
	for (int i = 0; i < iters; ++i) {
		int res = f(x1[i], x2[i]);
		printf("For x1 = %d, x2 = %d func returned %d\n", x1[i], x2[i], res);
	}
	for (int i = 0; i < 4; ++i) {
    	int y1 = (i & 1) ? INT_MIN : INT_MAX;
    	int y2 = (i & 2) ? INT_MIN : INT_MAX;
    	int res = f(y1, y2);
    	printf("For x1 = %d, x2 = %d func returned %d\n", y1, y2, res);
	}
	free(x1);
	free(x2);
}
void test3(int (*f)(int, int, int), int iters) {
	int *x1 = getRandomSmallInts(iters);
	int *x2 = getRandomSmallInts(iters);
	int *x3 = getRandomSmallInts(iters);
	for (int i = 0; i < iters; ++i) {
		int res = f(x1[i], x2[i], x3[i]);
		printf("For x1 = %d, x2 = %d, x3 = %d func returned %d\n", x1[i], x2[i], x3[i], res);
	}
	for (int i = 0; i < 8; ++i) {
    	int y1 = (i & 1) ? INT_MIN : INT_MAX;
    	int y2 = (i & 2) ? INT_MIN : INT_MAX;
    	int y3 = (i & 4) ? INT_MIN : INT_MAX;
    	int res = f(y1, y2, y3);
    	printf("For x1 = %d, x2 = %d, x3 = %d func returned %d\n", y1, y2, y3, res);
	}
	free(x1);
	free(x2);
	free(x3);
}
void test4(int (*f)(int, int, int, int), int iters) {
	int *x1 = getRandomSmallInts(iters);
	int *x2 = getRandomSmallInts(iters);
	int *x3 = getRandomSmallInts(iters);
	int *x4 = getRandomSmallInts(iters);
	for (int i = 0; i < iters; ++i) {
		int res = f(x1[i], x2[i], x3[i], x4[i]);
		printf("For x1 = %d, x2 = %d, x3 = %d, x4 = %d func returned %d\n", x1[i], x2[i], x3[i], x4[i], res);
	}
	for (int i = 0; i < 16; ++i) {
    	int y1 = (i & 1) ? INT_MIN : INT_MAX;
    	int y2 = (i & 2) ? INT_MIN : INT_MAX;
    	int y3 = (i & 4) ? INT_MIN : INT_MAX;
    	int y4 = (i & 8) ? INT_MIN : INT_MAX;
    	int res = f(y1, y2, y3, y4);
    	printf("For x1 = %d, x2 = %d, x3 = %d, x4 = %d func returned %d\n", y1, y2, y3, y4, res);
	}
	free(x1);
	free(x2);
	free(x3);
	free(x4);
}
#pragma GCC pop_options

/*
   DO NOT TOUCH CODE ABOVE
*/
/*
   DO NOT TOUCH CODE ABOVE
*/
/*
   DO NOT TOUCH CODE ABOVE
*/
/*
   DO NOT TOUCH CODE ABOVE
*/
int ggg(int x) {
	int z;
	int y;
	z = abs(x % 7);
	if (x < INT_MIN + z) {
		return INT_MIN;
	}
	y = x - z;
	if (y == x ) {
		y-=7;
	}
	
	return y;
}

int f(int x, int y, int z) { return x + y + z;
}

int main()
{
 
    //TEST(ggg, 20);
    
    //BENCH(ggg);
    if (-2){
    	puts("ggg");
	}
	return 0;
}
