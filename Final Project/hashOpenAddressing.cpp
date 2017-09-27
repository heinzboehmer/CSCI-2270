/*Code written by Heinz Boehmer and Alejandro Gonzalez*/

#include <iostream>
#include <vector>
#include "hashOpenAddressing.h"

using namespace std;

PlayerHashOpenAddressing::PlayerHashOpenAddressing() {

  collisions = 0;
  searchOperations = 0;
  initialSearchOperations = 0;

}

PlayerHashOpenAddressing::~PlayerHashOpenAddressing(){

  for(int i = 0; i < tableSize; i++) {
    if(table[i] != NULL) delete table[i];
  }

}

void PlayerHashOpenAddressing::setTableSize(int size) {

  tableSize = size;
  table = new PlayerNodeOpenAddressing*[size];


}

// int PlayerHashOpenAddressing::hashSum(string firstName, string lastName) {
//
//   int sum = 0;
//
//   for(int i = 0; i < (firstName + lastName).length(); i++) {
//     sum += (firstName + lastName)[i];
//   }
//
//   return sum % tableSize;
//
// }

int PlayerHashOpenAddressing::hashSum(string firstName, string lastName) {
    // Based on work of Paul Larson & George V Reilly from Microsoft.
    const char *str = (firstName + lastName).c_str();
    unsigned int hash = 1;
    while (*str) hash = hash * 101  +  *str++;
    return hash % tableSize;
}

void PlayerHashOpenAddressing::addToTable(string cYearID, string cTeamID, string cLeagueID, string cPlayerID,
                                          string cSalary, string cFirstName, string cLastName, string cBirthYear,
                                          string cBirthCountry, string cWeight, string cHeight, string cBats,
                                          string cThrows) {

  if(tableSize == 0) {
    cout << "Table size is 0" << endl;
    return;
  }

  int index = hashSum(cFirstName, cLastName);
  int count = 1;
  bool add = true;

  if(table[index] == NULL) table[index] = new PlayerNodeOpenAddressing(cYearID, cTeamID, cLeagueID, cPlayerID, cSalary, cFirstName,
                                                                      cLastName, cBirthYear, cBirthCountry, cWeight, cHeight, cBats,
                                                                      cThrows);

  else {
    if(table[index]->playerID != cPlayerID) collisions++;
    while(table[index] != NULL) {
      if(table[index]->playerID == cPlayerID) {
        table[index]->yearID.push_back(cYearID);
        table[index]->teamID.push_back(cTeamID);
        table[index]->leagueID.push_back(cLeagueID);
        table[index]->salary.push_back(cSalary);
        add = false;
        break;
      }
      index++;
      count++;
      if(count == tableSize) {
        cout << endl << "No more space available" << endl;
        return;
      }
      initialSearchOperations++;
      if(index == tableSize) index = 0;
    }

    if(add) table[index] = new PlayerNodeOpenAddressing(cYearID, cTeamID, cLeagueID, cPlayerID, cSalary, cFirstName, cLastName,
                                                        cBirthYear, cBirthCountry, cWeight, cHeight, cBats, cThrows);
  }

}

void PlayerHashOpenAddressing::printHash() {

  for(int i = 0; i < tableSize; i++) {
    if(table[i] == NULL) continue;

    // cout << table[i]->firstName << " " << table[i]->lastName << endl;
    cout << table[i]->playerID << endl;
  }

}

void PlayerHashOpenAddressing::searchAndPrint(string firstName, string lastName) {

  int searchIndex = hashSum(firstName, lastName);
  int count = 1;
  searchOperations = 0;

  if(table[searchIndex] == NULL) {
    cout << "\nPlayer not found.\n" << endl;
    return;
  }

  while(!(table[searchIndex]->firstName == firstName && table[searchIndex]->lastName == lastName)) {
    searchIndex++;
    if(searchIndex == tableSize) searchIndex = 0;
    searchOperations++;
    count++;
    cout << count << endl;
    if(table[searchIndex] == NULL || count == tableSize) {
      cout << "\nPlayer not found.\n" << endl;
      return;
    }
  }

  cout << endl;
  cout << "Search operations using open addressing: " << searchOperations << endl << endl;
  cout << "First name: " << table[searchIndex]->firstName << endl;
  cout << "Last name: " << table[searchIndex]->lastName << endl;
  cout << "Year born: " << table[searchIndex]->birthYear << endl;
  cout << "Country born: " << table[searchIndex]->birthCountry << endl;
  cout << "Weight: " << table[searchIndex]->weight << endl;
  cout << "Height: " << table[searchIndex]->height << endl;
  cout << "Bats: " << table[searchIndex]->bats << endl;
  cout << "Throws: " << table[searchIndex]->throws << endl;
  cout << "Teams and salary: " << endl;
  for(int i = 0; i < table[searchIndex]->teamID.size(); i++) {
    cout << table[searchIndex]->yearID[i] << "," << table[searchIndex]->teamID[i] << "," << table[searchIndex]->leagueID[i] << ","
    << table[searchIndex]->salary[i] << endl;
  }
  cout << endl;

}

int PlayerHashOpenAddressing::getTableSize() {

  return tableSize;

}

int PlayerHashOpenAddressing::getCollisions() {

  return collisions;

}

int PlayerHashOpenAddressing::getInitialSearchOperations() {

  return initialSearchOperations;

}
