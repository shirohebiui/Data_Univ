#include <stdio.h>
#include <string.h>
#define  MAX_TERMS 100

typedef struct {
    int row;
    int col;
    int value;
} element;
typedef struct SparseMatrix {
    element data[MAX_TERMS];
    int rows; // 행의 개수
    int cols; // 열의 개수
    int terms; // 항의 개수
} SparseMatrix;

SparseMatrix x1 = { {{1,1,5},{2,2,9}}, 3, 3, 2};
SparseMatrix y1 = { {{0,0,5},{2,2,9}}, 3, 3, 2};

SparseMatrix x2 = { {{0,0,1},{0,1,2},{0,2,3},{1,0,1},{1,1,2},{1,2,3},{2,0,1},{2,1,2},{2,2,3}}, 3, 3, 9};
SparseMatrix y2 = { {{0,0,1},{0,1,1},{0,2,1},{1,0,1},{1,1,1},{1,2,1},{2,0,1},{2,1,1},{2,2,1}}, 3, 3, 9};

SparseMatrix x3 = { {{0,0,7},{0,2,2},{1,2,3},{2,0,7}}, 3, 3, 4};
SparseMatrix y3 = { {{0,1,5},{0,2,8},{1,2,4},{2,0,4},{2,2,1}}, 3, 3, 5};

void print_result(int data[][MAX_TERMS], int col, int row) {
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            printf("%2d ", data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void cal_matrix(SparseMatrix *a, SparseMatrix *b) {
    int data[MAX_TERMS][MAX_TERMS] = {0, };
    for(int i=0; i<a->terms; i++) {
        for(int j=0; j<b->terms; j++) {
            if(a->data[i].col == b->data[j].row) {
                //printf("%d %d += %d*%d\n", a->data[i].row, b->data[j].col, a->data[i].value, b->data[j].value);
                data[a->data[i].row][b->data[j].col] += a->data[i].value*b->data[j].value;
            }
        }
    }
    print_result(data, b->cols, b->rows);
}

void print_matrix(SparseMatrix *a, SparseMatrix *b) {
    int count = 0;
    for(int i=0; i<a->rows; i++) {
        for(int j=0; j<a->cols; j++) {
            if(a->data[count].row == i && a->data[count].col == j && count < a->terms) {
                printf("%2d ", a->data[count++].value);
            } else {
                printf("%2d ", 0);
            }
        }
        printf("\n");
    }
    printf("--------\n");

    count = 0;
    for(int i=0; i<b->rows; i++) {
        for(int j=0; j<b->cols; j++) {
            if(b->data[count].row == i && b->data[count].col == j && count < b->terms) {
                printf("%2d ", b->data[count++].value);
            } else {
                printf("%2d ", 0);
            }
        }
        printf("\n");
    }
    printf("========\n");
}

int main() {
    print_matrix(&x1, &y1);
    cal_matrix(&x1, &y1);

    print_matrix(&x2, &y2);
    cal_matrix(&x2, &y2);

    print_matrix(&x3, &y3);
    cal_matrix(&x3, &y3);

    return 0;
}