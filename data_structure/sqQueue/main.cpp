#include "sqqueue.h"
#include <iostream>

using namespace std;

void Yanghui(int n);

void testInitQueue() {
  SqQueue Q;
  InitQueue_Sq(Q, 10, 5);
  cout << "Test InitQueue: ";
  QueueTraverse_Sq(Q);
  cout << "Queue length: " << QueueLength_Sq(Q) << endl;
  cout << "Is empty: " << QueueEmpty_Sq(Q) << endl;
  cout << endl;
}

void testEnqueue() {
  SqQueue Q;
  InitQueue_Sq(Q, 10, 5);

  cout << "Test Enqueue: ";
  Enqueue_Sq(Q, 10);
  Enqueue_Sq(Q, 20);
  Enqueue_Sq(Q, 30);
  Enqueue_Sq(Q, 40);
  Enqueue_Sq(Q, 50);
  QueueTraverse_Sq(Q);
  cout << "Queue length: " << QueueLength_Sq(Q) << endl;
  cout << endl;

  DestroyQueue_Sq(Q);
}

void testDequeue() {
  SqQueue Q;
  InitQueue_Sq(Q, 10, 5);

  Enqueue_Sq(Q, 100);
  Enqueue_Sq(Q, 200);
  Enqueue_Sq(Q, 300);

  cout << "Test Dequeue - Before: ";
  QueueTraverse_Sq(Q);

  QElemType e;
  Dequeue_Sq(Q, e);
  cout << "Dequeued: " << e << endl;
  cout << "After first dequeue: ";
  QueueTraverse_Sq(Q);

  Dequeue_Sq(Q, e);
  cout << "Dequeued: " << e << endl;
  cout << "After second dequeue: ";
  QueueTraverse_Sq(Q);
  cout << "Queue length: " << QueueLength_Sq(Q) << endl;
  cout << endl;

  DestroyQueue_Sq(Q);
}

void testGetHead() {
  SqQueue Q;
  InitQueue_Sq(Q, 10, 5);

  Enqueue_Sq(Q, 1);
  Enqueue_Sq(Q, 2);
  Enqueue_Sq(Q, 3);

  cout << "Test GetHead: ";
  QueueTraverse_Sq(Q);

  QElemType head;
  GetHead_Sq(Q, head);
  cout << "Head element: " << head << endl;
  cout << "Queue after GetHead: ";
  QueueTraverse_Sq(Q);
  cout << endl;

  DestroyQueue_Sq(Q);
}

void testClearQueue() {
  SqQueue Q;
  InitQueue_Sq(Q, 10, 5);

  Enqueue_Sq(Q, 5);
  Enqueue_Sq(Q, 10);
  Enqueue_Sq(Q, 15);

  cout << "Test ClearQueue - Before: ";
  QueueTraverse_Sq(Q);
  cout << "Queue length: " << QueueLength_Sq(Q) << endl;

  ClearQueue_Sq(Q);

  cout << "After clear: ";
  QueueTraverse_Sq(Q);
  cout << "Queue length: " << QueueLength_Sq(Q) << endl;
  cout << "Is empty: " << QueueEmpty_Sq(Q) << endl;
  cout << endl;

  DestroyQueue_Sq(Q);
}

void testEmptyQueue() {
  SqQueue Q;
  InitQueue_Sq(Q, 10, 5);

  cout << "Test Empty Queue: ";
  cout << "Is empty (should be 1): " << QueueEmpty_Sq(Q) << endl;

  Enqueue_Sq(Q, 99);
  cout << "Is empty after enqueue (should be 0): " << QueueEmpty_Sq(Q) << endl;

  QElemType e;
  Dequeue_Sq(Q, e);
  cout << "Is empty after dequeue (should be 1): " << QueueEmpty_Sq(Q) << endl;
  cout << endl;

  DestroyQueue_Sq(Q);
}

void testDestroyQueue() {
  SqQueue Q;
  InitQueue_Sq(Q, 10, 5);

  Enqueue_Sq(Q, 11);
  Enqueue_Sq(Q, 22);
  Enqueue_Sq(Q, 33);

  cout << "Test DestroyQueue - Before: ";
  QueueTraverse_Sq(Q);

  DestroyQueue_Sq(Q);
  cout << "Queue destroyed successfully" << endl;
  cout << endl;
}

void testQueueExpansion() {
  SqQueue Q;
  InitQueue_Sq(Q, 5, 3);

  cout << "Test Queue Expansion: ";
  Enqueue_Sq(Q, 1);
  Enqueue_Sq(Q, 2);
  Enqueue_Sq(Q, 3);
  Enqueue_Sq(Q, 4);
  QueueTraverse_Sq(Q);
  cout << "Queue length: " << QueueLength_Sq(Q) << endl;

  Dequeue_Sq(Q, Q.elem[Q.front]);
  cout << "After one dequeue: ";
  QueueTraverse_Sq(Q);

  Enqueue_Sq(Q, 5);
  Enqueue_Sq(Q, 6);
  Enqueue_Sq(Q, 7);
  cout << "After adding more elements (may trigger expansion): ";
  QueueTraverse_Sq(Q);
  cout << "Queue length: " << QueueLength_Sq(Q) << endl;
  cout << endl;

  DestroyQueue_Sq(Q);
}

int main() {
  testInitQueue();
  testEnqueue();
  testDequeue();
  testGetHead();
  testClearQueue();
  testEmptyQueue();
  testDestroyQueue();
  testQueueExpansion();

  cout << "Test Yanghui Triangle" << endl;
  cout << "n = 5:" << endl;
  Yanghui(5);
  cout << endl;

  cout << "n = 8:" << endl;
  Yanghui(8);
  cout << endl;

  cout << "n = 10:" << endl;
  Yanghui(10);
  cout << endl;

  return 0;
}
