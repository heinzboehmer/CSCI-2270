#include <iostream>
#include <fstream>
#include "MovieTree.h"

using namespace std;

MovieTree m;

int menu() {

  cout << "======Main Menu======\n1. Find a movie\n2. Rent a movie\n" <<
          "3. Print the inventory\n4. Delete a movie\n5. Count the movies"
          << "\n6. Quit" << endl;

  int choice;
  cin >> choice;

  switch (choice) {

    case 1: {
      cin.ignore();

      string title;
      cout << "Enter title:" << endl;
      getline(cin, title);

      m.findMovie(title);

      return 0;
    }

    case 2: {
      cin.ignore();

      string title;
      cout << "Enter title:" << endl;
      getline(cin, title);

      m.rentMovie(title);

      return 0;
    }

    case 3: {
      m.printMovieInventory();
      return 0;
    }

    case 4: {
      cin.ignore();

      string title;
      cout << "Enter title:" << endl;
      getline(cin, title);

      m.deleteMovieNode(title);

      return 0;
    }

    case 5: {
      cout << "Tree contains: " << m.countMovieNodes() << " movies." << endl;
      return 0;
    }

    case 6: {
      cout << "Goodbye!" << endl;
      return 1;
    }

    default: return 0;

  }

}

void buildTree(char *filename) {

  string strRanking;
  int tRanking;
  string tTitle;
  string strReleaseYear;
  int tReleaseYear;
  string strQuantity;
  int tQuantity;

  string tLine;

  ifstream inFile; //open file
	inFile.open(filename);

  while (!inFile.eof()) { //read data
    getline(inFile, strRanking, ',');
    tRanking=stoi(strRanking);

    getline(inFile, tTitle, ',');

    getline(inFile, strReleaseYear, ',');
    tReleaseYear=stoi(strReleaseYear);

    getline(inFile, strQuantity, '\n');
    tQuantity=stoi(strQuantity);

    m.addMovieNode(tRanking, tTitle, tReleaseYear, tQuantity);
  }

}

int main(int argc, char *argv[]) {

  char *filename=argv[1];

  buildTree(filename);

  while (menu()!=1) {}

  return 0;
}
