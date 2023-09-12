#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_STUDENTS  4
#define NAME_SPACE 3

typedef struct student_info {
    char    name[10];
    int     height;
    float   weight;
} student_info;

student_info students[N_STUDENTS] = {
    {"이순신", 172, 83.4},
    {"홍길동", 167, 72.5},
    {"김유신", 159, 70.8},
    {"유관순", 163, 58.4}
};

student_info *swap(student_info *std_struct, student_info *swap_struct) {
    struct student_info tmp;
    tmp = *std_struct;
    *std_struct = *swap_struct;
    *swap_struct = tmp;
}

void print_all() {
    for(int i=0; i<N_STUDENTS; i++) {
        printf("%d : %s %d %.2f\n", i, students[i].name, students[i].height, students[i].weight);
    }
    printf("\n");
}

void sort_name() {
    for(int std = 0; std < N_STUDENTS - 1 ; std++) {
        bool FLAG = 0;
        int change = std;
        for(int cmp=std+1; cmp<N_STUDENTS; cmp++) {
            if(strcmp(students[change].name, students[cmp].name) > 0) {
                if(!FLAG) FLAG = 1;
                printf("%d %d\n", change, cmp);
                change = cmp;
            }
        }
        if(FLAG) {
            swap(&students[std], &students[change]);
            print_all();
        }
    }
}


int main(void) {
    print_all();
    sort_name();
    print_all();
    return 0;
}