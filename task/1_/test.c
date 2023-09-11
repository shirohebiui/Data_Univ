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

int cmp_str(int std_str, int cmp_str) {
    int change = std_str;
    for(int i=0; i<NAME_SPACE; i++) {
        if(students[std_str].name[i] > students[cmp_str].name[i]) {
            change = cmp_str;
            break;
        }
    }
    return change;
}

void sort_name() {
    int std = 0;
    for(int std = 0; std < N_STUDENTS ; std++) {
        int change = std;
        for(int cmp=std; cmp<N_STUDENTS; cmp++) {
            if(strcmp(students[std].name, students[cmp].name) > 0) {
                printf("change %s %s\n", students[std].name, students[cmp].name);
                change = cmp_str(change, cmp_str(std, cmp));
            }
        }
        if(change != std) {
            swap(&students[std], &students[change]);
        }
    }
}

void print_all() {
    for(int i=0; i<N_STUDENTS; i++) {
        printf("%d : %s %d %f\n", i, students[i].name, students[i].height, students[i].weight);
    }
}

int main(void) {
    print_all();
    sort_name();
    print_all();
    return 0;
}