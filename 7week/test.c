#include <stdio.h>

int mystrcmp(const char* str1, const char* str2) {
    for(int i=0; ;i++) {
        if((unsigned char)(str1[0]) - (unsigned char)(str2[0]) > 0) {
            return 1;
        } else if((unsigned char)(str1[0]) - (unsigned char)(str2[0]) < 0){
            return -1;
        }
        if(str1[i] == 0 && str2[i] == 0) {
            return 0;
        }
    }
}

int main() {
    char str[6][20] = { "하하하", "호호호", "하하하하", "안녕", "호호호", "하하"};
    printf("%s - %s = %d\n",str[1], str[4], mystrcmp(str[1], str[4]));
    printf("%s - %s = %d\n",str[0], str[5], mystrcmp(str[0], str[5]));
    printf("%s - %s = %d\n",str[0], str[2], mystrcmp(str[0], str[2]));
    printf("%s - %s = %d\n",str[1], str[3], mystrcmp(str[1], str[3]));
    return 0;
}