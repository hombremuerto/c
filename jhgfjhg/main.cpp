#include <stdio.h>

#define BENCH(Func) _Generic((Func), \
	    int : puts("func!"),\
	    default : puts("default")\
	);

void benchImpl(int (*f)(int, int)) {
	//printf("Benchmarking %s\n", #Func);
}

int add(int x, int y) {
	return x + y;
}

int main()
{
 BENCH(8);
 return 0;
}
