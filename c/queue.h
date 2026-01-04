#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>


#define MAXQUEUE 10

typedef struct item
{
    long arrive;        //一位顾客加入队列的时间
    int processtime;    //该顾客咨询时花费的时间
} Item;

typedef struct node
{
    Item item;
    struct node * next;
} Node;

typedef struct queue
{
    Node * front;   // 指向队列首节点的指针
    Node * rear;    // 指向队列尾节点的指针
    int items;      // 队列中的项目数
} Queue;
// 操作：初始化队列


void InitializeQueue(Queue * pq);
// 操作：检查队列是否已满
bool QueueIsFull(const Queue * pq);
// 操作：检查队列是否为空
bool QueueIsEmpty(const Queue * pq);
// 操作：返回队列中的项目数
int QueueItemCount(const Queue * pq);
// 操作：在队列末尾添加项目
bool EnQueue(Item item, Queue * pq);
// 操作：从队列首部删除项目
bool DeQueue(Item * pitem, Queue * pq);
// 操作：清空队列
void EmptyTheQueue(Queue * pq);
#endif