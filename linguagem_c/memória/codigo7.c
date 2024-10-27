#include <stdio.h>

// O que vai conter str?

int main(){
	char *str = "Hello, World!";
	str[0] = 'B';
	printf("%s\n", str);

	return 0;
}
