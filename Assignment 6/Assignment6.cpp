#include <iostream>
#include <sstream>
#include "Queue.h"

using namespace std;

Queue q(6);

int menu() {

  cout << "======Main Menu=====\n1. Enqueue word\n2. Dequeue word\n" <<
          "3. Print queue\n4. Enqueue sentence\n5. Quit" << endl;

  int choice;
  cin >> choice;

  switch (choice) {

    case 1: {
      string enWord;
      cout << "word: ";
      cin.ignore();
      getline(cin, enWord);

      q.enqueue(enWord);
      return 0;

    }

    case 2: {

      cout << q.dequeue() << endl;
      return 0;

    }

    case 3: {

      q.printQueue();
      return 0;

    }

    case 4: {

      if (q.queueIsFull()) {

        cout << "Queue full" << endl;
        return 0;

      }

      cout << "sentence: ";

      string tWord;
      string ttWord;

      cin.ignore();
      getline(cin, tWord);

      stringstream ss(tWord); //converts sentence into stringstream to split into words

    	while (ss >> ttWord) { //splits sentence into words and enqueues
        q.enqueue(ttWord);
      }
      return 0;

    }

    case 5: {

      cout << "Goodbye!"<< endl;
      return 1;

    }

    default: {return 0;}

  }


}

int main() {

  while (!menu()) {};

  return 0;

}
