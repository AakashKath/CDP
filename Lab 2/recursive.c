#include <stdio.h>
#include <stdlib.h>

int fact(int);
static int iglo2=0;
int iglo1=0, uglo1, uglo2;

int main(){
	int n, res;
	scanf("%d", &n);
	res=fact(n);
	printf("Although not necessary, Factorial of %d:\t%d\n", n, res);
	printf("Address of the initialized Variable:\t%d %d\n", &iglo1, &iglo2);
	printf("_main @ %lx\n", (long unsigned int)&main);
	printf("_fact @ %lx\n", (long unsigned int)&fact);
}

int fact(int n){
	int i;
	char *ptr;
	iglo1++;
	printf("Address of local variable after %d call:\t%d\n", iglo1, &i);
	ptr=(char*)malloc(n*sizeof(char));
	printf("Address of heap: %d\n", &ptr);
	if(n==1){
		return 1;
	}
	else{
		n*=fact(n-1);
	}
}
