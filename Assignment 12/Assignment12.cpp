#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

Graph<string> g;

int menu() {

  cout << "======Main Menu======\n1. Print vertices\n2. Find districts\n" <<
          "3. Find shortest path\n4. Quit" << endl;

  int choice;
  cin >> choice;

  switch (choice) {

    case 1: {
      g.displayEdges();

      return 0;
    }

    case 2: {
      g.assignDistricts();

      return 0;
    }

    case 3: {
      cin.ignore();

      string startCity;
      string endCity;

      cout << "Enter a starting city:" << endl;
      getline(cin, startCity);

      cout << "Enter an ending city:" << endl;
      getline(cin, endCity);

      g.shortestPath(startCity, endCity);

      return 0;
    }

    case 4: {
      cout << "Goodbye!" << endl;

      return 1;
    }

    default: return 0;

  }

}

void buildGraph(char *filename) {

  ifstream inFile; //open file
	inFile.open(filename);

  vector<string> cities;
  string word;
  string city;
  string fromCity;
  string toCity;
  string strWeight;
  string tmp;
  int weight;

  int index=0;

  while(getline(inFile, tmp, '\n')) {
    stringstream ssLine(tmp);
    getline(ssLine, word, ',');

    if (word == "cities") {
      while (getline(ssLine, city, ',')) {
        cities.push_back(city);
        g.addVertex(city);
      }
      continue;
    }

    else {
      fromCity = word;
      index = 0;

      while (getline(ssLine, strWeight, ',')) {
        weight=stoi(strWeight);

        if(weight != -1 && weight !=0) {
          toCity = cities[index];
          g.addEdge(fromCity, toCity, weight);
        }

        index++;
      }
    }
  }

}

int main(int argc, char *argv[]) {

  char *filename=argv[1];

  buildGraph(filename);

  while (menu()!=1) {}

  return 0;
}
