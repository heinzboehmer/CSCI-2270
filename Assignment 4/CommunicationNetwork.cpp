/*
Heinz Ulrich Boehmer Fiehn
Assignment 3
Rhonda Hoenigman
*/

#include "CommunicationNetwork.h"
#include <iostream>
#include <fstream>

using namespace std;

CommunicationNetwork::CommunicationNetwork() {

  head=NULL;
  tail=NULL;

}

CommunicationNetwork::~CommunicationNetwork() {

}

void CommunicationNetwork::addCity(string newCity, string previousCity) {

  if (head==NULL) {
    return;
  }

  City *currentAdd=head;
  City *newAdd=new City(newCity, NULL, "");

  if (previousCity=="First") {

    newAdd->next=head;
    head=newAdd;

  }

  while(currentAdd->cityName!=previousCity) {

    if (currentAdd==tail) {return;}
    currentAdd=currentAdd->next;

  }

  newAdd->next=currentAdd->next;
  currentAdd->next=newAdd;

  if (newAdd->next==NULL) {tail=newAdd;}

}

void CommunicationNetwork::buildNetwork() {

  string cities[10]={"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis",
                    "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};

  for (int i=0; i<10; i++) {

    City *n1=new City(cities[i], NULL, "");

    if(head==NULL) {

      head=n1;
      tail=n1;

    }

    else {

      City *current=head;

      while(current->next!=NULL) {
          current=current->next;
      }

      current->next=n1;
      tail=n1;

    }

  }

  printNetwork();

}

void CommunicationNetwork::transmitMsg(char *filename) {

  if (head==NULL) {
    cout << "Empty list" << endl;
    return;
  }

  string tWord;

  ifstream inFile; //open file
	inFile.open(filename);

	while (inFile >> tWord) { //read data

    City *currentMessage=head;

    while (currentMessage->next!=NULL) {

      currentMessage->message=tWord;
      cout << currentMessage->cityName << " received " << currentMessage->message << endl;
      currentMessage->message="";
      currentMessage=currentMessage->next;

    }

    currentMessage->message=tWord;
    cout << currentMessage->cityName << " received " << currentMessage->message << endl;
    currentMessage->message="";
    currentMessage=currentMessage->next;

  }

}

void CommunicationNetwork::printNetwork(){

  if (head==NULL) {
    return;
  }

  City *currentPrint=head;

  cout << "===CURRENT PATH===" << endl;

  while(currentPrint->next!=NULL) {
      cout << currentPrint->cityName << " -> ";
      currentPrint=currentPrint->next;
  }

  cout << currentPrint->cityName <<" -> NULL\n==================" << endl;

}
