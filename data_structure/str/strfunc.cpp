

int Index_BF(char S[], char T[], int pos) {
  int i = pos;
  int j = 0;
  while (S[i + j] != '\0' && T[j] != '\0') {
    if (S[i + j] == T[j]) {
      ++j;
    } else {
      ++i;
      j = 0;
    }
  }
  if (T[j] == '\0') {
    return i;
  } else {
    return -1;
  }
}
