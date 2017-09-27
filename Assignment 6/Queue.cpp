#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue(int qs) {

  queueSize=qs;
  arrayQueue=new string[queueSize];
  queueHead=0;
  queueTail=0;

}

Queue::~Queue() {}

void Queue::enqueue(string word) {

  if (queueIsFull()) { //checks if queue is full

    cout << "Queue is full." << endl;
    return;

  }

  if (queueTail==queueSize-1) { //wraps around

    arrayQueue[queueTail]=word; //adds word
    queueTail=0;

  }

  else {

    arrayQueue[queueTail]=word; //adds word if there is no need to wrap around
    queueTail++;

  }

  queueCount++; //increases count of words in queue

  cout << "E: " << word << "\nH: " << queueHead << "\nT: " <<
  queueTail << endl; //cog print format

}

string Queue::dequeue() {

  string tempWord;

  if (queueIsEmpty()) { //checks if queue is empty

    return "Queue is empty.";

  }

  if (queueHead==queueSize-1) { //wraps around

    tempWord=arrayQueue[queueHead]; //dequeues
    queueHead=0;

  }

  else {

    tempWord=arrayQueue[queueHead]; //dequeues if no need to wrap around
    queueHead++;

  }

  queueCount--; //decreases count of words in queue

  cout << "H: " << queueHead << "\nT: " << queueTail << "\nword: "; //cog

  return tempWord;

}

void Queue::printQueue() {

  if (queueCount==0) { //checks if queue is empty

    cout << "Empty" << endl;
    return;

  }

  for (int i=0; i<queueCount; i++) {

    if (queueHead+i<queueSize) { //prints up to last queue index
      cout << queueHead+i << ": " << arrayQueue[queueHead+i] << endl;
    }

    else { //wraps around and continues printing
      cout << i-queueSize+queueHead << ": " <<
      arrayQueue[i-queueSize+queueHead] << endl;
    }

  }

}

bool Queue::queueIsFull() {

  if (queueCount==queueSize) {return true;}
  else {return false;}

}

bool Queue::queueIsEmpty() {

  if (queueCount==0) {return true;}
  else {return false;}

}
