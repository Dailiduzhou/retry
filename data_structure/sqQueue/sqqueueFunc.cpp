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

void division(int R[][100], int n, int result[]) {
  int pre = n;
  int group = 0;
  SqQueue Q;
  InitQueue_Sq(Q, n + 10, QUEUEINCREMENT);

  for (int e = 0; e < n; ++e) {
    Enqueue_Sq(Q, e);
  }

  int i = -1;
  int clash[100] = {0};

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

void printGroups(int result[], int n, int groupCount) {
  for (int g = 1; g <= groupCount; ++g) {
    SqQueue groupQueue;
    InitQueue_Sq(groupQueue, n, QUEUEINCREMENT);

    for (int i = 0; i < n; ++i) {
      if (result[i] == g) {
        Enqueue_Sq(groupQueue, i);
      }
    }

    cout << "Group " << g << ": ";
    QueueTraverse_Sq(groupQueue);
    DestroyQueue_Sq(groupQueue);
  }
}

int main() {
  const int n = 6;
  int R[100][100] = {0};

  // Conflict relations: 0-1, 0-3, 1-2, 1-4, 2-5, 3-4, 4-5
  R[0][1] = 1;
  R[1][0] = 1;
  R[0][3] = 1;
  R[3][0] = 1;
  R[1][2] = 1;
  R[2][1] = 1;
  R[1][4] = 1;
  R[4][1] = 1;
  R[2][5] = 1;
  R[5][2] = 1;
  R[3][4] = 1;
  R[4][3] = 1;
  R[4][5] = 1;
  R[5][4] = 1;

  cout << "Conflict Matrix:" << endl;
  cout << "  0 1 2 3 4 5" << endl;
  for (int i = 0; i < n; ++i) {
    cout << i << " ";
    for (int j = 0; j < n; ++j) {
      cout << R[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  int result[100] = {0};
  division(R, n, result);

  int maxGroup = 0;
  for (int i = 0; i < n; ++i) {
    if (result[i] > maxGroup) {
      maxGroup = result[i];
    }
  }

  cout << "Division Result: ";
  for (int i = 0; i < n; ++i) {
    cout << "[" << i << "]=" << result[i] << " ";
  }
  cout << endl << endl;

  cout << "Groups:" << endl;
  printGroups(result, n, maxGroup);

  return 0;
}
