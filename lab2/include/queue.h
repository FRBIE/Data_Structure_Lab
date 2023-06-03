
#define MAX_SIZE 10

typedef struct {
    char data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q);
int isQueueEmpty(const Queue* q);
int isQueueFull(const Queue* q);
void enqueue(Queue* q, char element);
char dequeue(Queue* q);
void printQueue(const Queue* q);
void releaseQueue(Queue* q);

