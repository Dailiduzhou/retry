#include "sqqueue.h"
#include <iostream>
#include <vector>

using namespace std;

void Yanghui(int n) {
  SqQueue Q;
  for (int i = 1; i <= n; ++i) {
    cout << ' ';
  }
  QElemType e;

  cout << '1' << endl;
  InitQueue_Sq(Q, n + 2, 20);
  Enqueue_Sq(Q, 0);
  Enqueue_Sq(Q, 1);
  Enqueue_Sq(Q, 1);

  int k = 1;

  while (k < n) {
    for (int i = 1; i < n - k; ++i) {
      cout << ' ';
    }

    Enqueue_Sq(Q, 0);
    do {
      QElemType s;
      Dequeue_Sq(Q, s);
      GetHead_Sq(Q, e);

      if (e) {
        cout << e << ' ';
      } else {
        cout << endl;
      }
      Enqueue_Sq(Q, s + e);
    } while (e != 0);
    k++;
  }

  Dequeue_Sq(Q, e);
  while (!QueueEmpty_Sq(Q)) {
    Dequeue_Sq(Q, e);
    cout << e << ' ';
  }
}

void division(int R[][], int n, int result[]) {
  int pre = n;
  int group = 0;
  SqQueue Q;
  InitQueue_Sq(Q, n, QUEUEINCREMENT);

  for (int e = 0; e < n; ++e) {
    Enqueue_Sq(Q, e);
  }
  int i = -1;
  std::vector<int> clash(n);
  while (!QueueEmpty_Sq(Q)) {
    Dequeue_Sq(Q, i);
    if (i < pre) {
      group++;
      for (int j = 0; j < n; ++j) {
        clash[j] = 0;
      }
    }
    if (clash[i] == 0) {
      result[i] = group;
      for (int j = 0; j < n; ++j) {
        clash[j] += R[i][j];
      }
    } else {
      Enqueue_Sq(Q, i);
    }

    pre = i;
  }
}
