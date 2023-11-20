# include <stdio.h>
# include <stdlib.h>
 
 
// 프로그램 5.2에서 다음과 같은 부분을 복사한다. 
// ================ 원형큐 코드 시작 =================
typedef struct { // 요소 타입
    int id;
    int arrival_time;
    int service_time;
} element;            // 교체!
// ================ 원형큐 코드 종료 =================
// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 100 //*1번
typedef struct { // 큐 타입
    element  data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;
 
// 오류 함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
 
// 초기화 함수
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}
 
// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}
 
// 포화 상태 검출 함수
int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
 
// 원형큐 출력 함수
void queue_print(QueueType *q)
{
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
            int i = q->front;
            do {
                i = (i + 1) % (MAX_QUEUE_SIZE);
                printf("%d | ", q->data[i]);
                if (i == q->rear)
                    break;
            } while (i != q->front);
        }
    printf("\n");
}
 
// 삽입 함수
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}
 
// 삭제 함수
element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("큐가 공백상태입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}
 
// 삭제 함수
element peek(QueueType *q)
{
    if (is_empty(q))
        error("큐가 공백상태입니다");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======
#define BANKER 3
int main(void) 
{
    int minutes = 60;
    int total_wait = 0;
    int total_customers = 0;
    int service_time[BANKER] = 0;
    int service_customer;
    QueueType queue;
    init_queue(&queue);
 
    srand(34); //srand(time(NULL)); //*2번
    for (int clock = 0; clock < minutes; clock++) {
        printf("현재시각=%d\n", clock);
        //*3번 70%
        if ((rand()%10) < 7) { //if ((rand()%10) < 3) {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            //*4번 최대 서비스시간 10분
            customer.service_time = rand() % 10+1;//rand() % 3+1;
            enqueue(&queue, customer);
            printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", 
                customer.id, customer.arrival_time, customer.service_time);
        }
        for(int i=0; i<BANKER; i++) {
            if (service_time[i] > 0) {
                printf("\t\t\t 은행원[%d]: ", i);
                printf("고객 %d 업무처리중입니다. \n", service_customer);
                service_time[i]--;
            }
            else {
                if (!is_empty(&queue)) {
                    element customer = dequeue(&queue);
                    service_customer = customer.id;
                    service_time[i] = customer.service_time;

                    printf("\t\t\t 은행원[%d]: ", i);
                    printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
                        customer.id, clock, clock - customer.arrival_time);
                    total_wait += clock - customer.arrival_time;
                }
            }
        }
    }
    printf("전체 대기 시간=%d분 \n", total_wait);
    return 0;
}