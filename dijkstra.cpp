#include <array>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define MAX 100

struct DijkstraEdge {
  string start;
  string end;
  int distance;
  bool check;
  DijkstraEdge(string start, string end, int distance) {
    this->start = start;
    this->end = end;
    this->distance = distance;
    this->check = 0;
  }
};

struct Edge {
  string start;
  string end;
  int distance;
  Edge(string start, string end, int distance) {
    this->start = start;
    this->end = end;
    this->distance = distance;
  }
};

struct Graph {
  Edge *array[MAX];
  int size;
  bool oriented;
  Graph(bool oriented) {
    this->oriented = oriented;
    this->size = 0;
  }
  ~Graph() {
    for (int i = 0; i < size; i++) {
      delete array[i];
    }
  }
  void insert(string start, string end, int distance) {
    array[size] = new Edge(start, end, distance);
    if (oriented) {
      this->size++;
      array[size] = new Edge(end, start, distance);
    }
    this->size++;
  }
  void print() {
    for (int i = 0; i < this->size; i++) {
      cout << array[i]->start << "-" << array[i]->end << " "
           << array[i]->distance << endl;
    }
  }
};

struct Dijkstra {
  DijkstraEdge *array[100];
  int size;
  set<string> s;
  Graph *graph;
  ~Dijkstra() {
    for (int i = 0; i < size; i++) {
      delete array[i];
    }
  }
  void get_vertices(Graph &g) {
    for (int i = 0; i < g.size; i++) {
      this->s.insert(g.array[i]->start);
      this->s.insert(g.array[i]->end);
      this->graph = &g;
    }
    for (auto &it : this->s) {
      array[this->size] = new DijkstraEdge(it, "", INT_MAX);
      this->size++;
    }
  }
  void print_vertices() {
    for (auto &it : this->s) {
      cout << it << " ";
    }
    cout << endl;
  }
  void print() {
    for (int i = 0; i < size; i++) {
      cout << array[i]->start << " " << array[i]->end << " "
           << array[i]->distance << " " << array[i]->check << endl;
    }
  }
  int getDistanceTo(string s) {
    int distance = 0;
    for (int i = 0; i < size; i++) {
      if (s == array[i]->start) {
        if (array[i]->distance == INT_MAX)
          distance = 0;
        else
          distance = array[i]->distance;
      }
    }
    return distance;
  }
  void insert_dijkstra_array(string start, string end, int distance) {
    for (int i = 0; i < this->size; i++) {
      if (array[i]->start == start) {
        if (array[i]->distance > distance + getDistanceTo(end)) {
          array[i]->end = end;
          array[i]->distance = distance + getDistanceTo(end);
        }
      }
    }
  }
  int findMinIndex() {
    int min = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < this->size; i++) {
      if (array[i]->distance < min && array[i]->check != 1) {
        min = array[i]->distance;
        minIndex = i;
      }
    }
    return minIndex;
  }
  void solve(string start) {
    insert_dijkstra_array(start, start, 0);

    while (true) {
      int minIndex = findMinIndex();
      if (minIndex == -1) {
        return;
      }
      array[minIndex]->check = 1;
      start = array[minIndex]->start;
      for (int j = 0; j < graph->size; j++) {
        if (graph->array[j]->start == start) {
          insert_dijkstra_array(graph->array[j]->end, start,
                                graph->array[j]->distance);
        }
      }
    }
  }
  vector<string> solve(string start, string end) {
    solve(start);
    vector<string> v;
    bool found;
    while (true) {
      found = false;
      for (int i = 0; i < size; i++) {
        if (array[i]->start == end) { // find end
          v.push_back(end);
          end = array[i]->end;
          found = true;
        }
      }
      if (end == start) {
        v.push_back(start);
        return v;
      }
      if (end == "" || !found) {
        return v;
      }
    }
  }
};
void printReverse(vector<string> v) {
  for (auto it = v.rbegin(); it != v.rend(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

int main() {
  Graph g(false);
  // g.insert("s", "a", 6);
  // g.insert("s", "b", 2);
  // g.insert("s", "c", 3);
  // g.insert("s", "d", 9);
  // g.insert("a", "b", 3);
  // g.insert("a", "e", 4);
  // g.insert("b", "e", 7);
  // g.insert("b", "f", 3);
  // g.insert("b", "c", 2);
  // g.insert("c", "d", 5);
  // g.insert("c", "f", 1);
  // g.insert("d", "g", 1);
  // g.insert("e", "f", 3);
  // g.insert("f", "g", 2);
  g.insert("A", "B", 2);
  g.insert("A", "E", 7);
  g.insert("A", "F", 4);
  g.insert("B", "F", 3);
  g.insert("B", "G", 6);
  g.insert("B", "C", 2);
  g.insert("C", "G", 4);
  g.insert("C", "D", 2);
  g.insert("D", "G", 1);
  g.insert("D", "H", 10);
  g.insert("E", "I", 1);
  g.insert("F", "E", 1);
  g.insert("F", "I", 1);
  g.insert("F", "G", 2);
  g.insert("G", "J", 2);
  g.insert("G", "K", 4);
  g.insert("H", "G", 2);
  g.insert("H", "L", 1);
  g.insert("J", "F", 1);
  g.insert("J", "I", 2);
  g.insert("J", "K", 1);
  g.insert("K", "H", 1);

  // g.print();
  Dijkstra d;
  d.get_vertices(g);
  printReverse(d.solve("A", "L"));
  cout << endl;
  d.print();
  return 0;
}
