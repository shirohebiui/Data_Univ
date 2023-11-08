#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int FLAG = 0; //괄호검사 FLAG
//char의 저장공간은 1byte라서 2자리이상 연산과정에서 overflow가 날 수 있음
//따라서 long형으로 공간을 넓게 잡음
typedef long element;        // 교체!
                            // 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
                            // ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 1000
 
 
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;
 
// 스택 초기화 함수
void init_stack(StackType *s)
{
    s->top = -1;
}
 
// 공백 상태 검출 함수
int is_empty(StackType *s)
{
    return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType *s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
    //printf("push %d : %c\n", s->top, s->data[s->top]);
}
// 삭제함수
element pop(StackType *s)
{
    //printf("pop %d : %c\n", s->top, s->data[s->top]);
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러pop\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러peek\n");
        exit(1);
    }
    else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 
 
// 연산자의 우선순위를 반환한다.
int prec(char op)
{
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': case '%': return 2; //mod연산에 대한 우선순위 추가
    }
    return -1;
}
// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[] , char stack[])
{
    int top = 0; //stack 의 top
    int cnt = 0; //괄호검사
    char ch, top_op;
    StackType s;
    init_stack(&s);
    //모든 stdout출력을 -> stack에 push로 대체함
    for (int i = 0; i < strlen(exp); i++) {
        //printf("ptr : %d : %s\n", i, &exp[i]);
        ch = exp[i];
        switch (ch) {
        case ' ': //공백무시
            break;
        case '+': case '-': case '*': case '/': case '%': //mod연산 조건 추가
            while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
                stack[top++] = pop(&s);
            push(&s, ch);
            break;
        case '(':
            push(&s, ch);
            cnt++;
            break;
        case ')':
            if(--cnt < 0) {
                FLAG = 1;
                return;
            }
            top_op = pop(&s);
            while (top_op != '(') {
                stack[top++] = top_op;
                top_op = pop(&s);
            }
            break;

        default:
            // 0~9의 숫자들을 묶음으로 읽어서 push
            do {
                stack[top++] = exp[i++];
            }while(exp[i] <= '9' && exp[i] >= '0');
            stack[top++] = ' '; // 숫자와 숫자 구분을 위해 공백추가
            i--; 				// exp의 포인터가 숫자의 마지막에 위치하도록 조정
            break;
        }
    }
    if(cnt != 0) {
        FLAG = 1;
        return;
    }
    while (!is_empty(&s))
        stack[top++] = pop(&s);
}

void st_print(char *stack) { //스택에 저장된값을 바닥부터 읽음
    for(int i=0; i<strlen(stack); i++) {
        switch (stack[i])
        {
        case '+': case '-': case '*': case '/': case '%':
            printf("%c", stack[i]);
            break;
        case ' ':
            printf(" ");
            break;
        default:
            printf("%c", stack[i]);
            break;
        }
    }
}

int digit(int k) { //입력된 자릿수를 리턴
    int d = 10; int t=1;
    while(k >= d) {
        d *= 10;
        t++;
    }
    return t;
}

int cal_2(char cmd, int op2, int op1) { //피연산자 둘을 입력된 연산자로 연산 후 리턴
    // printf("cal : %c %d %d\n", cmd, op1, op2); //test code
    switch (cmd) //연산기호에 따른 결과값출력
    {
        case '+': 
            return op1+op2;
        case '-': 
            return op1-op2;
        case '*': 
            return op1*op2;
        case '/': 
            return op1/op2;
        case '%':
            return op1%op2;
    }
    //5개의 연산 기호 외의 입력이 있다면 오류
    fprintf(stderr, "예상치 못한 연산기호\n");
    exit(1);
    return 0;
}

int cal(char stack[]) {
    StackType s;
    init_stack(&s);
    int tmp;
    for(int i=0; stack[i] != '\0'; i++) {
        switch (stack[i])
        {
        case ' ':
            break;
        case '+': case '-': case '*': case '/': case '%': //연산기호가 나오면
            /* test code
            printf("top : %d %d\n", s.data[s.top], s.data[s.top - 1]);
            tmp = cal_2(stack[i], pop(&s), pop(&s));
            push(&s, tmp);
            printf("result : %d\n\n", tmp);
            */
            push(&s, cal_2(stack[i], pop(&s), pop(&s))); //op1(pop), op2(pop)를 연산 후 결과를 push
            break;
        default:
            // printf("push : %d\n", atoi(&stack[i])); //test code
            push(&s, atoi(&stack[i])); //문자를 숫자로 바꿔 push
            i += digit(atoi(&stack[i])); //자릿수만큼 문자열포인터 이동
            break;
        }
    }
    return pop(&s);
}

int main(void)
{
    char text[MAX_STACK_SIZE];
    char stack[MAX_STACK_SIZE];
    printf("[ itsys:hw3 508 ] run\n");
    while(1) {
        FLAG = 0; //괄호검사 FLAG 초기화
        memset(text, '\0', MAX_STACK_SIZE); //공간 초기화
        memset(stack, '\0', MAX_STACK_SIZE); //공간 초기화
        fflush(stdin); //버퍼를 비워서 다시 입력받을 준비
    
        printf("수식입력 (q:quit): ");
        scanf("%[^\n]s", text); //공백포함 문자열 입력받음
        if(!strcmp(text,"q")) { //q입력시 프로세스 종료
            printf("[ itsys:hw3 509 ]\n");
            return 1;
        }
        infix_to_postfix(text, stack); //text을 후위표기식으로 변환 -> stack에 저장
        if(FLAG) { //FLAG == 1은 곧 괄호검사가 실패했음을 의미
            fprintf(stderr, "괄호검사 실패!!!\n");
            continue;
        }
        printf("       후위표기식: ");
        st_print(stack); //stack에 저장된값을 바닥부터 읽음
        printf("\n\t\t   ");
        printf("%s = %d\n\n", text, cal(stack)); //후위표기식의 계산결과를 출력
    }
    fprintf(stderr, "예기치 못한 종료\n");
    
    return 0;
}