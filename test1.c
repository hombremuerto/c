#include <stdio.h>
#include <time.h>

int main(){
	time_t t;
	srand(time(&t));
	int num[10];
	int outer, inner, ctr, buf;
	for (ctr = 0; ctr < 10; ctr++) {
		num[ctr] = (rand() % 99) + 1;
	}
	for (ctr = 0; ctr < 10; ctr++) {
		printf("   %d\n", num[ctr]);
	}
	
	for (outer = 0; outer < 9; outer++) {
		for (inner = outer; inner < 10; inner++) {
			if (num[inner] < num[outer]) {
				buf = num[inner];
				num[inner] = num[outer];
				num[outer] = buf;
			}
		}
		
	}
	for (ctr = 0; ctr < 10; ctr++) {		
		printf(" %d\n", num[ctr]);
		}
	return 0;
	
	
}
