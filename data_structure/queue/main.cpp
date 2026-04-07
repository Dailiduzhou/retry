#include "queue.h"
#include <iostream>

using namespace std;

void testInitQueue() {
  LinkQueue Q;
  InitQueue_L(Q);
  cout << "Test InitQueue: ";
  QueueTraverse(Q);
  cout << "Queue length: " << QueueLength_L(Q) << endl;
  cout << "Is empty: " << QueQueueEmpty_L(Q) << endl;
  cout << endl;
}

void testEnqueue() {
  LinkQueue Q;
  InitQueue_L(Q);

  cout << "Test Enqueue: ";
  Enqueue_L(Q, 10);
  Enqueue_L(Q, 20);
  Enqueue_L(Q, 30);
  Enqueue_L(Q, 40);
  Enqueue_L(Q, 50);
  QueueTraverse(Q);
  cout << "Queue length: " << QueueLength_L(Q) << endl;
  cout << endl;

  DestroyQueue_L(Q);
}

void testDequeue() {
  LinkQueue Q;
  InitQueue_L(Q);

  Enqueue_L(Q, 100);
  Enqueue_L(Q, 200);
  Enqueue_L(Q, 300);

  cout << "Test Dequeue - Before: ";
  QueueTraverse(Q);

  QElemType e;
  Dequeue_L(Q, e);
  cout << "Dequeued: " << e << endl;
  cout << "After first dequeue: ";
  QueueTraverse(Q);

  Dequeue_L(Q, e);
  cout << "Dequeued: " << e << endl;
  cout << "After second dequeue: ";
  QueueTraverse(Q);
  cout << "Queue length: " << QueueLength_L(Q) << endl;
  cout << endl;

  DestroyQueue_L(Q);
}

void testGetHead() {
  LinkQueue Q;
  InitQueue_L(Q);

  Enqueue_L(Q, 1);
  Enqueue_L(Q, 2);
  Enqueue_L(Q, 3);

  cout << "Test GetHead: ";
  QueueTraverse(Q);

  QElemType head;
  GetHead(Q, head);
  cout << "Head element: " << head << endl;
  cout << "Queue after GetHead: ";
  QueueTraverse(Q);
  cout << endl;

  DestroyQueue_L(Q);
}

void testClearQueue() {
  LinkQueue Q;
  InitQueue_L(Q);

  Enqueue_L(Q, 5);
  Enqueue_L(Q, 10);
  Enqueue_L(Q, 15);

  cout << "Test ClearQueue - Before: ";
  QueueTraverse(Q);
  cout << "Queue length: " << QueueLength_L(Q) << endl;

  ClearQueue_L(Q);

  cout << "After clear: ";
  QueueTraverse(Q);
  cout << "Queue length: " << QueueLength_L(Q) << endl;
  cout << "Is empty: " << QueQueueEmpty_L(Q) << endl;
  cout << endl;

  DestroyQueue_L(Q);
}

void testEmptyQueue() {
  LinkQueue Q;
  InitQueue_L(Q);

  cout << "Test Empty Queue: ";
  cout << "Is empty (should be 1): " << QueQueueEmpty_L(Q) << endl;

  Enqueue_L(Q, 99);
  cout << "Is empty after enqueue (should be 0): " << QueQueueEmpty_L(Q)
       << endl;

  QElemType e;
  Dequeue_L(Q, e);
  cout << "Is empty after dequeue (should be 1): " << QueQueueEmpty_L(Q)
       << endl;
  cout << endl;

  DestroyQueue_L(Q);
}

void testDestroyQueue() {
  LinkQueue Q;
  InitQueue_L(Q);

  Enqueue_L(Q, 11);
  Enqueue_L(Q, 22);
  Enqueue_L(Q, 33);

  cout << "Test DestroyQueue - Before: ";
  QueueTraverse(Q);

  DestroyQueue_L(Q);
  cout << "Queue destroyed successfully" << endl;
  cout << endl;
}

int main() {
  testInitQueue();
  testEnqueue();
  testDequeue();
  testGetHead();
  testClearQueue();
  testEmptyQueue();
  testDestroyQueue();

  return 0;
}
