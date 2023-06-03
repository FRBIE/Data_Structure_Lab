#include <stdio.h>
#include<stdlib.h>
#include "include/queue.h"
/**
 * initQueue函数用于初始化队列，
 * 将队列的队头指针front和队尾指针rear都设置为0，
 * 表示队列为空。
*/
// 初始化队列
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}
/**
 * isQueueEmpty函数用于判断队列是否为空。
 * 当队头指针front和队尾指针rear相等时，
 * 表示队列为空，函数返回1；否则，返回0。
*/
// 判断队列是否为空
int isQueueEmpty(const Queue* q) {
    return (q->front == q->rear);
}
/**
 * isQueueFull函数用于判断队列是否已满。
 * 当队尾指针rear的下一个位置等于队头指针front时，
 * 表示队列已满，函数返回1；否则，返回0。
*/
// 判断队列是否已满
int isQueueFull(const Queue* q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);
}
/**
 * enqueue函数用于将元素入队。
 * 首先，判断队列是否已满，
 * 若已满则打印提示信息并返回；若未满，
 * 则将元素添加到队尾，并将队尾指针rear循环后移一位。
*/
// 入队操作
void enqueue(Queue* q, char element) {
    // 判断队列是否已满
    if (isQueueFull(q)) {
        printf("队列已满，无法入队。\n");
        return;
    }

    // 将元素添加到队尾
    q->data[q->rear] = element;
    q->rear = (q->rear + 1) % MAX_SIZE;
}
/**
 * dequeue函数用于出队操作，
 * 即从队列中删除并返回队头元素。
 * 首先，判断队列是否为空，
 * 若为空则打印提示信息并返回空字符('\0')；
 * 若不为空，则获取队头元素，
 * 将队头指针front循环后移一位，并返回队头元素。
*/
// 出队操作
char dequeue(Queue* q) {
    // 判断队列是否为空
    if (isQueueEmpty(q)) {
        printf("队列为空，无法出队。\n");
        return '\0';
    }

    // 获取队头元素并移动front指针
    char element = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return element;
}
/**
 * printQueue函数用于输出队列的所有元素。
 * 首先，判断队列是否为空，若为空则打印提示信息；
 * 若不为空，则按顺序输出队列的元素。
*/
// 输出队列元素
void printQueue(const Queue* q) {
    if (isQueueEmpty(q)) {
        printf("队列为空。\n");
        return;
    }

    printf("队列元素：");
    int i = q->front;
    while (i != q->rear) {
        printf("%c ", q->data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}
/**
 * releaseQueue函数用于释放队列，
 * 即将队列的队头指针front和队尾指针rear都设置为0，
 * 表示队列为空。
*/
// 释放队列
void releaseQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int main() {
    Queue q;
    char element;
    printf("初始化队列");
    printf("\n");

    // 初始化队列
    initQueue(&q);
    printf("队列已初始化。\n");
    printf("\n");
    system("pause");
    printf("判断队列是否非空");
    printf("\n");
    // 判断队列是否非空
    if (isQueueEmpty(&q)) {
        printf("队列为空。\n");
    } else {
        printf("队列不为空。\n");
    }
    printf("依次进队元素a、b、c、d");
    printf("\n");
    // 依次进队元素a、b、c、d
    enqueue(&q, 'a');
    enqueue(&q, 'b');
    enqueue(&q, 'c');
    enqueue(&q, 'd');
    system("pause");
    printf("出队一个元素，输出该元素");
    printf("\n");
    // 出队一个元素，输出该元素
    element = dequeue(&q);
    printf("出队元素：%c\n", element);
    system("pause");
    // 依次进队元素e、f、g
    printf("依次进队元素e、f、g");
    printf("\n");
    enqueue(&q, 'e');
    enqueue(&q, 'f');
    enqueue(&q, 'g');
    printf("输出出队序列");
    printf("\n");
    // 输出出队序列
    printf("出队序列：");
    while (!isQueueEmpty(&q)) {
        element = dequeue(&q);
        printf("%c ", element);
    }
    printf("\n");
    system("pause");
    // 释放队列
    releaseQueue(&q);
    printf("队列已释放。\n");
    system("pause");
    return 0;
}





