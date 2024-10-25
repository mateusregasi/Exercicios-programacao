#include <stdio.h>

void f(){
	int x;
	printf("%p\n", &x);
}

int main(){
	int x, y;
	printf("%p\n", &x);
	printf("%p\n", &y);
	f();
	return 0;
}

