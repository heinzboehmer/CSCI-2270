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

  deleteNetwork();

}

void CommunicationNetwork::addCity(string newCity, string previousCity) {

  if (head==NULL) {
    return;
  }

  City *currentAdd=head;
  City *newAdd=new City(newCity, NULL, NULL, "");

  if (previousCity=="First") {

    newAdd->next=head;
    newAdd->previous=NULL;
    head->previous=newAdd;
    head=newAdd;

  }

  while(currentAdd->cityName!=previousCity) {

    if (currentAdd==tail) {return;}
    currentAdd=currentAdd->next;

  }

  newAdd->next=currentAdd->next;
  currentAdd->next=newAdd;
  newAdd->previous=currentAdd;
  if(currentAdd!=tail) {newAdd->next->previous=newAdd;}

  if (newAdd->next==NULL) {tail=newAdd;}

}

void CommunicationNetwork::buildNetwork() {

  string cities[10]={"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis",
                    "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};

  City *current;
  City *n1;

  for (int i=0; i<10; i++) {

    n1=new City(cities[i], NULL, NULL, "");

    if(head==NULL) {

      head=n1;
      tail=n1;

    }

    else {

      current=head;

      while(current->next!=NULL) {
          current=current->next;
      }

      current->next=n1;
      n1->previous=current;

    }

  }

  tail=n1;

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

  City *currentMessage;

	while (inFile >> tWord) { //read data

    currentMessage=head;

    while (currentMessage->next!=NULL) {

      currentMessage->message=tWord;
      cout << currentMessage->cityName << " received " << currentMessage->message << endl;
      currentMessage->message="";
      currentMessage=currentMessage->next;

    }

    while (currentMessage->previous!=NULL) {

      currentMessage->message=tWord;
      cout << currentMessage->cityName << " received " << currentMessage->message << endl;
      currentMessage->message="";
      currentMessage=currentMessage->previous;

    }

    currentMessage->message=tWord;
    cout << currentMessage->cityName << " received " << currentMessage->message << endl;
    currentMessage->message="";

  }

}

void CommunicationNetwork::printNetwork(){

  if (head==NULL) {
    cout << "===CURRENT PATH===\nNULL";
    cout << "\n==================" << endl;
    return;
  }

  City *currentPrint=head;

  cout << "===CURRENT PATH===\nNULL <- ";

  while(currentPrint->next!=NULL) {
    cout << currentPrint->cityName << " <-> ";
    currentPrint=currentPrint->next;
  }

  cout << currentPrint->cityName <<" -> NULL\n==================" << endl;

}

void CommunicationNetwork::deleteCity(string delCity) {

  if (head==NULL) {
    return;
  }

  City *currentDelete=head->next;
  City *previousDelete=head;

  if (head->cityName==delCity) {
    head=currentDelete;
    delete previousDelete;
    previousDelete=head;
    previousDelete->previous=NULL;
    currentDelete=currentDelete->next;
    return;
  }

  while (currentDelete!=NULL) {

    if (currentDelete->cityName==delCity) {

      previousDelete->next=currentDelete->next;
      delete currentDelete;
      currentDelete=previousDelete->next;
      if (currentDelete!=NULL) {currentDelete->previous=previousDelete;}
      else {tail=previousDelete;}
      return;

    }

    else {

      previousDelete=currentDelete;
      currentDelete=currentDelete->next;

    }

  }

  if (currentDelete==NULL) {cout << delCity << " not found" << endl;}

}

void CommunicationNetwork::deleteNetwork() {

  if (head==NULL) {
    return;
  }

  City *deleteAll=head;
  City *deleteAllNext=head->next;

  while (deleteAllNext!=NULL) {

    cout << "deleting " << deleteAll->cityName << endl;
    delete deleteAll;
    deleteAll=deleteAllNext;
    deleteAllNext=deleteAll->next;

  }

  cout << "deleting " << deleteAll->cityName << endl;
  delete deleteAll;
  head=NULL;
  tail=NULL;

}
