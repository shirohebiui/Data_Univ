#include <stdio.h>
int stack[1000];
int top;

void push(int data) {
	stack[top++] = data;
}

int pop() {
	if(top > 0) {
        return stack[--top];
	} else {
        return -1;
	}
}

int IsEmpty() {
	if(top > 0) {
        return 0;
	} else {
        return 1;
	}
}
long rec() {
	while(IsEmpty() == 0) {
		return pop() * rec();
	}
	return 1;
}
long fac(int N) {
	for(int i=1; i<=N; i++) {
		push(i);
	}
	return rec();
}

int main() {
	// int N;
	// scanf("%d", &N);
	// long result=1;
	// for(int i=1; i<=N; i++) {
	// 	result *= i;
	// }
	// printf("%ld\n", result);

	
	printf("%ld\n", fac(4));
	printf("%ld\n", fac(10));
	
	return 0;
}