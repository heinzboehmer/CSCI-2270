/*Code written by Heinz Boehmer and Alejandro Gonzalez*/

#include <iostream>
#include <vector>
#include "hashChaining.h"

using namespace std;

PlayerHashChaining::PlayerHashChaining() {

  collisions = 0;
  searchOperations = 0;
  initialSearchOperations = 0;

}

PlayerHashChaining::~PlayerHashChaining(){

  PlayerNode *tmp;
  PlayerNode *previous;

  for(int i = 0; i < tableSize; i++) {
    if(table[i] != NULL) {
      tmp = table[i];
      while(tmp != NULL) {
        previous = tmp;
        tmp = tmp->next;
        delete previous;
      }
    }
  }

}

void PlayerHashChaining::setTableSize(int size) {

  tableSize = size;
  table = new PlayerNode*[size];

}

// int PlayerHashChaining::hashSum(string firstName, string lastName) {
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

int PlayerHashChaining::hashSum(string firstName, string lastName) {
    // Based on work of Paul Larson & George V Reilly from Microsoft.
    const char *str = (firstName + lastName).c_str();
    unsigned int hash = 1;
    while (*str) hash = hash * 101  +  *str++;
    return hash % tableSize;
}

void PlayerHashChaining::addToTable(string cYearID, string cTeamID, string cLeagueID, string cPlayerID,
        string cSalary, string cFirstName, string cLastName, string cBirthYear,
        string cBirthCountry, string cWeight, string cHeight, string cBats,
        string cThrows) {

  if(tableSize == 0) {
    cout << "Table size is 0" << endl;
    return;
  }

  int index = hashSum(cFirstName, cLastName);

  if(table[index] == NULL) table[index] = new PlayerNode(cYearID, cTeamID, cLeagueID, cPlayerID, cSalary, cFirstName, cLastName,
                                                          cBirthYear, cBirthCountry, cWeight, cHeight, cBats, cThrows);

  else {
    if(table[index]->playerID != cPlayerID) collisions++;
    PlayerNode *tmp = table[index];
    bool add = true;
    while(tmp->next != NULL) {
      if(tmp->playerID == cPlayerID){
        add = false;
        tmp->yearID.push_back(cYearID);
        tmp->teamID.push_back(cTeamID);
        tmp->leagueID.push_back(cLeagueID);
        tmp->salary.push_back(cSalary);
        break;
      }
      initialSearchOperations++;
      tmp = tmp->next;
    }

    if(add && tmp->playerID != cPlayerID) {
      PlayerNode *newPlayer = new PlayerNode(cYearID, cTeamID, cLeagueID, cPlayerID, cSalary, cFirstName, cLastName, cBirthYear,
                      cBirthCountry, cWeight, cHeight, cBats, cThrows);
      tmp->next = newPlayer;
      newPlayer->previous = tmp;
    }
  }

}

void PlayerHashChaining::printHash() {

  PlayerNode *tmp;

  for(int i = 0; i < tableSize; i++) {
    if(table[i] == NULL) continue;

    tmp = table[i];
    cout << tmp->firstName << " " << tmp->lastName;
    // cout << tmp->playerID;
    tmp = tmp->next;

    while(tmp != NULL) {
      // cout << "\n" << tmp->firstName << " " << tmp->lastName;
      // cout << "\n" << tmp->playerID;
      cout << " -> " << tmp->firstName << " " << tmp->lastName;
      // cout << " -> " << tmp->playerID;
      tmp = tmp->next;
    }

    cout << endl;
  }

}

void PlayerHashChaining::searchAndPrint(string firstName, string lastName) {

  PlayerNode *tmp = table[hashSum(firstName, lastName)];
  bool found = false;
  searchOperations = 0;

  while(tmp != NULL) {
    if(tmp->firstName == firstName && tmp->lastName == lastName) {
      found = true;
      cout << endl;
      cout << "Search operations using chaining: " << searchOperations << endl << endl;
      cout << "First name: " << tmp->firstName << endl;
      cout << "Last name: " << tmp->lastName << endl;
      cout << "Year born: " << tmp->birthYear << endl;
      cout << "Country born: " << tmp->birthCountry << endl;
      cout << "Weight: " << tmp->weight << endl;
      cout << "Height: " << tmp->height << endl;
      cout << "Bats: " << tmp->bats << endl;
      cout << "Throws: " << tmp->throws << endl;
      cout << "Teams and salary: " << endl;
      for(int i = 0; i < tmp->teamID.size(); i++) {
        cout << tmp->yearID[i] << "," << tmp->teamID[i] << "," << tmp->leagueID[i] << "," << tmp->salary[i] << endl;
      }
      cout << endl;
    }
    if(!found) searchOperations++;
    tmp = tmp->next;
  }

  if(!found) cout << "\nPlayer not found.\n" << endl;

}

int PlayerHashChaining::getTableSize() {

  return tableSize;

}

int PlayerHashChaining::getCollisions() {

  return collisions;

}

int PlayerHashChaining::getInitialSearchOperations() {

  return initialSearchOperations;

}
