#include <stdio.h>
#include <stdlib.h>

int main(){
	char *p = "Hello, World";
	char *str = (char *) malloc(sizeof(char) * 14);
	for(int i=0; i<14; i++) str[i] = p[i];
	printf("%s\n", str);
}
