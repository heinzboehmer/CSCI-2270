/*Code written by Heinz Boehmer and Alejandro Gonzalez*/

#include <string>
#include <vector>

using namespace std;

struct PlayerNodeOpenAddressing {
  vector<string> yearID;
  vector<string> teamID;
  vector<string> leagueID;
  string playerID;
  vector<string> salary;
  string firstName;
  string lastName;
  string birthYear;
  string birthCountry;
  string weight;
  string height;
  string bats;
  string throws;

  PlayerNodeOpenAddressing() {};

  PlayerNodeOpenAddressing(string cYearID, string cTeamID, string cLeagueID, string cPlayerID,
          string cSalary, string cFirstName, string cLastName, string cBirthYear,
          string cBirthCountry, string cWeight, string cHeight, string cBats,
          string cThrows) {
    yearID.push_back(cYearID);
    teamID.push_back(cTeamID);
    leagueID.push_back(cLeagueID);
    playerID = cPlayerID;
    salary.push_back(cSalary);
    firstName = cFirstName;
    lastName = cLastName;
    birthYear = cBirthYear;
    birthCountry = cBirthCountry;
    weight = cWeight;
    height = cHeight;
    bats = cBats;
    throws = cThrows;
  }
};

class PlayerHashOpenAddressing {

public:
  PlayerHashOpenAddressing();
  virtual ~PlayerHashOpenAddressing();
  void setTableSize(int size);
  void addToTable(string cYearID, string cTeamID, string cLeagueID, string cPlayerID,
          string cSalary, string cFirstName, string cLastName, string cBirthYear,
          string cBirthCountry, string cWeight, string cHeight, string cBats,
          string cThrows);
  void printHash();
  void searchAndPrint(string firstName, string lastName);
  int getTableSize();
  int getCollisions();
  int getInitialSearchOperations();

protected:

private:
  int hashSum(string firstName, string lastName);
  int collisions;
  int initialSearchOperations;
  int searchOperations;
  int tableSize;
  PlayerNodeOpenAddressing **table;

};
