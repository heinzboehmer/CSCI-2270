#include <iostream>
#include <queue>
#include "Graph.h"

using namespace std;

template <class T>
Graph<T>::Graph() {

}

template <class T>
Graph<T>::~Graph() {

}

template <class T>
void Graph<T>::addEdge(T v1, T v2, int weight) {

  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].name == v1){
      for(int j = 0; j < vertices.size(); j++){
        if(vertices[j].name == v2 && i != j){
            adjVertex<T> av;
            av.v = &vertices[j];
            av.weight = weight;
            vertices[i].adj.push_back(av);
        }
      }
    }
  }

}

template <class T>
void Graph<T>::addVertex(T name) {

  bool found = false;

  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].name == name){
      found = true;
    }
  }

  if(found == false){
    vertex<T> v;
    v.name = name;
    v.district = -1;
    v.ID=count;
    count++;
    vertices.push_back(v);
  }

}

template <class T>
void Graph <T>::displayEdges() {

  for(int i = 0; i < vertices.size(); i++){
    cout <<  vertices[i].district << ":" << vertices[i].name << "-->";

    for(int j = 0; j < vertices[i].adj.size(); j++){
      cout << vertices[i].adj[j].v->name;
      if(j != vertices[i].adj.size()-1) cout << "***";
    }

    cout<<endl;
  }

}

template <class T>
void Graph <T>::assignDistricts() {

  int district = 1;

  for(int i = 0; i < vertices.size(); i++) {
      if(!vertices[i].visited) {
        BFTraversalLabel(vertices[i].name, district);
        district++;
      }
  }

  for(int i=0; i<vertices.size(); i++) {
    vertices[i].visited=false;
  }

}

template <class T>
void Graph <T>::BFTraversalLabel(T startingCity, int distID) {

  vertex<T> *n;
  queue<vertex<T>*> q;
  vertex<T> *vertex = findVertex(startingCity);

  (*vertex).visited = true;
  (*vertex).district = distID;
  q.push(vertex);

  while(!q.empty()) {
    n = q.front();
    q.pop();

    for(int i=0; i<n->adj.size(); i++) {
      if(!(*n).adj[i].v->visited) {
        (*n).adj[i].v->visited = true;
        (*n).adj[i].v->district = distID;
        q.push((*n).adj[i].v);
      }
    }
  }

}

template <class T>
vertex<T> *Graph <T>::findVertex(T name) {

  for(int i=0; i<vertices.size(); i++) {
    if(vertices[i].name == name) return &vertices[i];
  }

  return NULL;

}

template <class T>
void Graph <T>::shortestPath(T startingCity, T endingCity) {

  vertex<T> *n;
  queue<vertex<T>*> q;
  vertex<T> *startVertex = findVertex(startingCity);
  vertex<T> *endVertex = findVertex(endingCity);

  if(startVertex == NULL || endVertex == NULL) {
    cout << "One or more cities doesn't exist" << endl;
    return;
  }

  if(startVertex->district != endVertex->district) {
    cout << "No safe path between cities" << endl;
    return;
  }

  if(startVertex->district == -1 || endVertex->district == -1) {
    cout << "Please identify the districts before checking distances" << endl;
    return;
  }

  startVertex->visited = true;
  startVertex->distance = 0;

  q.push(startVertex);

  int previous[vertices.size()];

  for(int i=0; i<vertices.size(); i++) previous[i]=-1;

  while(!q.empty()) {
    n = q.front();
    q.pop();

    for(int i=0; i<(*n).adj.size(); i++) {
      if(!(*n).adj[i].v->visited) {
        (*n).adj[i].v->distance = (*n).distance + 1;
        previous[(*n).adj[i].v->ID] = (*n).ID;
        (*n).adj[i].v->visited = true;
        q.push((*n).adj[i].v);
      }
    }
  }

  int edgesTraversed=1;
  int index=previous[endVertex->ID];
  string path;
  string nextCity;

  while(previous[index] != -1) {
    edgesTraversed++;
    for(int i=0; i<vertices.size(); i++) {
      if(vertices[i].ID==index) {
        nextCity=vertices[i].name;
        break;
      }
    }
    path=nextCity+","+path;
    index=previous[index];
  }

  path=startVertex->name+","+path+endVertex->name;

  cout << edgesTraversed << "," << path << endl;

  for(int i=0; i<vertices.size(); i++) {
    vertices[i].visited=false;
  }

  return;

}
