void bbsort(int *num) {
  for (int i = 0; i < 10; ++i) {
    for (int j = 10 - i - 1; j > 0; --j) {
      if (num[j - 1] < num[j]) {
        int temp = num[j - 1];
        num[j - 1] = num[j];
        num[j] = temp;
      }
    }
  }
}

int Merge(int *a, int *b, int *c) {
  bbsort(a);
  bbsort(b);

  int i = 0;
  int j = 0;
  int k = 0;

  while (i < 10 && j < 10) {
    if (a[i] > b[j]) {
      if (k == 0 || c[k - 1] != a[i]) {
        c[k++] = a[i];
      }
      i++;
      while (i < 10 && a[i] == a[i - 1])
        i++;
    } else if (a[i] < b[j]) {
      if (k == 0 || c[k - 1] != b[j]) {
        c[k++] = b[j];
      }
      j++;
      while (j < 10 && b[j] == b[j - 1])
        j++;
    } else {
      if (k == 0 || c[k - 1] != a[i]) {
        c[k++] = a[i];
      }
      i++;
      j++;
      while (i < 10 && a[i] == a[i - 1])
        i++;
      while (j < 10 && b[j] == b[j - 1])
        j++;
    }
  }

  while (i < 10) {
    if (k == 0 || c[k - 1] != a[i]) {
      c[k++] = a[i];
    }
    i++;
  }

  while (j < 10) {
    if (k == 0 || c[k - 1] != b[j]) {
      c[k++] = b[j];
    }
    j++;
  }

  return k;
}
