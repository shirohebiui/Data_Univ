#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX 10000

char map[MAX][MAX] = {
{ '1', '1', '1', '1', '1', '1' },
{ 'e', '0', '1', '0', '0', '1' },
{ '1', '0', '0', '0', '1', '1' },
{ '1', '0', '1', '0', '1', '1' },
{ '1', '0', '1', '0', '0', 'x' },
{ '1', '1', '1', '1', '1', '1' },
};
int W = 6, H = 6;

typedef struct _stack {
	int x;
	int y;
}stack;

stack path[MAX];
int top = 0;

void push(int x, int y) {
	path[top].x = x;
	path[top].y = y;
	top++;
}

stack *pop() {
	return &path[--top];
}

void print() {
	for(int i=0; ; i++) {
		if(top>0) {
			stack *p = pop();
			printf("(%d, %d) ", p->y, p->x);
		} else {
			printf("\n");
			break;
		}
	}
}

void dfs(int x, int y) {
	if(x>=0 && x<W && y>=0 && y<H) {
		if(map[y][x] == 'x') {
			print();
			return;
		}
		if(map[y][x] == '0') {
			map[y][x] = '.';
			push(x, y);
			dfs(x+1, y);
			dfs(x-1, y);
			dfs(x, y+1);
			dfs(x, y-1);
			pop();
		}
	}
	
}

void search() {
	for(int i=0; i<H; i++) {
		for(int j=0; j<W; j++) {
			if(map[i][j] == 'e') {
				map[i][j] = '0';
				dfs(j, i);
				return;
			}
		}
	}
}

void print_map() {
	for(int i=0; i<H; i++) {
		for(int j=0; j<W; j++) {
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
}

int main() {
	// while(1) scanf("%s", map[H++]); ~
	print_map();
	search();
	return 0;
}