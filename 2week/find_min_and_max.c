#include <stdio.h>

/*
조건 : 범위와 수가 주어진 상태.
*/

#define  N_DATA  8
int data[N_DATA] = { 12, 23, 98, 45, 11, 92, 56, 79 };

int find_max() {
    int max_value = data[0];
    for(int i=0; i<N_DATA; i++) {
        max_value = max_value > data[i] ? max_value : data[i];
    }
    return max_value;
}

int find_min() {
    int min_value = data[0];
    for(int i=0; i<N_DATA; i++) {
        min_value = min_value < data[i] ? min_value : data[i];
    }
    return min_value;
}

void find_max_min(int *result) {
    result[0] = result[1] = data[0];
    for(int i=0; i<N_DATA; i++) {
        result[0] = result[0] < data[i] ? result[0] : data[i];
        result[1] = result[1] > data[i] ? result[1] : data[i];
    }
}

int main() {
    printf("version 1\n");
    printf("min : %d\n", find_min());
    printf("max : %d\n", find_max());

    printf("\n");

    int result[2];
    printf("min : %d\n", result[0]);
    printf("max : %d\n", result[1]);

    return 0;
}