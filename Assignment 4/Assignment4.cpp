/*
Heinz Ulrich Boehmer Fiehn
Assignment 3
Rhonda Hoenigman
*/

#include "CommunicationNetwork.h"
#include <iostream>

using namespace std;

CommunicationNetwork network;

int menu(char *fName) {

  cout << "======Main Menu======\n1. Build Network\n2. Print Network Path\n" <<
          "3. Transmit Message Coast-To-Coast\n4. Add City\n5. Quit" << endl;

  int choice;
  cin >> choice;

  switch (choice) {

    case 1: {

      network.buildNetwork();
      return 0;

    }

    case 2: {

      network.printNetwork();
      return 0;

    }

    case 3: {

      network.transmitMsg(fName);
      return 0;

    }

    case 4: {

      string newCity;
      string previousCity;

      cin.ignore();
      cout << "Enter a city name: " << endl;
      getline(cin, newCity);
      cout << "Enter a previous city name: " << endl;
      getline(cin, previousCity);

      network.addCity(newCity, previousCity);
      return 0;

    }

    case 5: {

      cout << "Goodbye!" << endl;
      return 1;

    }

    default: return 0;

  }

}

int main(int argc, char *argv[]) {

  char *filename=argv[1];

  while (menu(filename)!=1) {}

  return 0;
}
