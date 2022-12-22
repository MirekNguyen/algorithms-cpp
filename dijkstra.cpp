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
  void solve(string start, string end) {
    solve(start);
    vector<string> v;
    while (true) {
      for (int i = 0; i < size; i++) {
        if (array[i]->start == end) { // find end
          v.push_back(end);
          end = array[i]->end;
        }
      }
      if (end == start || end == "") {
        for (auto it = v.rbegin(); it != v.rend(); it++) {
          cout << *it << " ";
        }
        cout << endl;
        return;
      }
    }
  }
};

int main() {
  Graph g(true);
  g.insert("s", "a", 6);
  g.insert("s", "b", 2);
  g.insert("s", "c", 3);
  g.insert("s", "d", 9);
  g.insert("a", "b", 3);
  g.insert("a", "e", 4);
  g.insert("b", "e", 7);
  g.insert("b", "f", 3);
  g.insert("b", "c", 2);
  g.insert("c", "d", 5);
  g.insert("c", "f", 1);
  g.insert("d", "g", 1);
  g.insert("e", "f", 3);
  g.insert("f", "g", 2);

  // g.print();
  Dijkstra d;
  d.get_vertices(g);
  d.solve("s", "e");
  cout << endl;
  d.print();
  return 0;
}
