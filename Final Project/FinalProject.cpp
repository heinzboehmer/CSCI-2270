/*Code written by Heinz Boehmer and Alejandro Gonzalez*/

#include <iostream>
#include <fstream>
#include "hashChaining.h"
#include "hashOpenAddressing.h"

using namespace std;

PlayerHashChaining hashChaining;
PlayerHashOpenAddressing hashOpenAddressing;

int menu() {

  cout << "1. Query hash table\n2. Quit Program" << endl;

  int choice;
  cin >> choice;

  switch (choice) {

    case 1: {
      cin.ignore();

      string first;
      cout << "Enter player's first name:" << endl;
      getline(cin, first);

      string last;
      cout << "Enter player's last name:" << endl;
      getline(cin, last);

      hashChaining.searchAndPrint(first, last);
      hashOpenAddressing.searchAndPrint(first, last);

      return 0;
    }

    case 666: {
      hashChaining.printHash();
      return 0;
    }

    case 2: {
      cout << "Goodbye!" << endl;
      return 1;
    }

    default: return 0;

  }

}

void buildHash(char *filename) {
  string yearID;
  string teamID;
  string leagueID;
  string playerID;
  string salary;
  string firstName;
  string lastName;
  string birthYear;
  string birthCountry;
  string weight;
  string height;
  string bats;
  string throws;

  ifstream inFile; //open file
	inFile.open(filename);

  getline(inFile, yearID, '\n'); //ignore first line

  while (inFile.good()) { //read data
    getline(inFile, yearID, ',');
    getline(inFile, teamID, ',');
    getline(inFile, leagueID, ',');
    getline(inFile, playerID, ',');
    getline(inFile, salary, ',');
    getline(inFile, firstName, ',');
    getline(inFile, lastName, ',');
    getline(inFile, birthYear, ',');
    getline(inFile, birthCountry, ',');
    getline(inFile, weight, ',');
    getline(inFile, height, ',');
    getline(inFile, bats, ',');
    getline(inFile, throws, '\n');
    if(inFile.eof()) break;

    hashChaining.addToTable(yearID, teamID, leagueID, playerID, salary, firstName, lastName, birthYear,
                            birthCountry, weight, height, bats, throws);
    hashOpenAddressing.addToTable(yearID, teamID, leagueID, playerID, salary, firstName, lastName, birthYear,
                            birthCountry, weight, height, bats, throws);
  }

  cout << endl;
  cout << "Hash table size: " << hashChaining.getTableSize() << endl;
  cout << "Collisions using open addressing: " << hashOpenAddressing.getCollisions() << endl;
  cout << "Collisions using chaining: " << hashChaining.getCollisions() << endl;
  cout << "Search operations using open addressing: " << hashOpenAddressing.getInitialSearchOperations() << endl;
  cout << "Search operations using chaining: " << hashChaining.getInitialSearchOperations() << endl;
  cout << endl;

}

int main(int argc, char *argv[]) {

  char *filename = argv[1];
  int tableSize = stoi(argv[2]);

  hashChaining.setTableSize(tableSize);
  hashOpenAddressing.setTableSize(tableSize);
  buildHash(filename);

  while (menu() != 1) {}

  return 0;
}
