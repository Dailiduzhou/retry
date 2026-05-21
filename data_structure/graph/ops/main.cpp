#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Vertex {
public:
  int val;
  Vertex(int x) : val(x) {}
};

class Graph {
private:
  vector<int> vertices;
  vector<vector<int>> adjmat;
};
