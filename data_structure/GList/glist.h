#ifndef GLIST_H_
#define GLIST_H_

enum class ElemTag : int { ATOM = 0, LIST = 1 };
typedef int AtomType;

typedef struct GLNode {
  ElemTag tag;
  union {
    AtomType data;
    struct {
      struct GLNode *hp; // points to head
      struct GLNode *tp; // points to tail
    } ptr;
  };
} *GList;

void OutputGList(GList LS);

#endif // !GLIST_H_
