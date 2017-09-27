/*
Heinz Ulrich Boehmer Fiehn
Assignment 3
Rhonda Hoenigman
*/

#include <iostream>
#include <fstream>
#include "WordAnalysis.h"

using namespace std;

WordAnalysis::WordAnalysis(int size) {
  words=new word[size];
  timesDoubled=0;
  index=0;
  wordCount=0;
}

WordAnalysis::~WordAnalysis() {
}

void WordAnalysis::doubleArrayAndAdd(string wordToAdd) {    //function to double array

  word *aDouble=new word[index*2];

  for (int x=0; x<index; x++) {
    aDouble[x]=words[x];
  }

  delete []words;
  words=aDouble;
  words[index].w=wordToAdd;
  words[index].count=1;
  timesDoubled++;

}

bool WordAnalysis::checkIfCommonWord(string comparisonWord) { //function to check for common words and whitespaces

  string cWords[50]={"the","be","to","of","and","a","in","that","have","i","it",
                    "for","not","on","with","he","as","you","do","at","this",
                    "but","his","by","from","they","we","say","her","she","or",
                    "an","will","my","one","all","would","there","their","what",
                    "so","up","out","if","about","who","get","which","go","me"};

  for (int z=0; z<50; z++) {

    if (cWords[z]==comparisonWord) {
      return true;
    }

  }

  return false;

}

bool WordAnalysis::readDataFile(char *filename) { //function to read text file and populate array

  string tWord;
  int match=0;

  ifstream inFile; //open file
	inFile.open(filename);

  if (!(inFile.good())) {
    return false;
  }

	while (inFile >> tWord) { //read data

    match=0;

    if (checkIfCommonWord(tWord)!=true) { //check if word is common

  		for (int j=0; j<index; j++) { //check if word is already in array

        if (words[j].w==tWord) {

          match=1;
          words[j].count=(words[j].count)+1; //if a match is found, increase count
          wordCount++; //increase total unique words counter

  			}
  		}

  		if (match!=1) { //only runs if no match is found

        if ((index+1)>((1 << timesDoubled)*100)) { //call double array function if array is full
          doubleArrayAndAdd(tWord);
        }

        else {

    			words[index].w=tWord; //add new word to array
         words[index].count=1;

        }

        wordCount++; //increase total unique words counter
        index++; //increase next available slot index
  		}

    }

  }

  sortData();
  return true;

}

void WordAnalysis::sortData() { //insertionSort used to sort array from largest to smallest

  int indexSort=0;
  word indexStruct;
  int j;

  for (int i=1; i<index; i++) {

      indexSort=words[i].count;
      indexStruct=words[i];

      j=i;

      while(j>0 && words[j-1].count<indexSort) {

          words[j]=words[j-1];
          j=j-1;

      }

      words[j]=indexStruct;

  }

}

int WordAnalysis::getWordCount() {
  return wordCount;
}

int WordAnalysis::getUniqueWordCount() {
  return index;
}

int WordAnalysis::getArrayDoubling() {
  return timesDoubled;
}

void WordAnalysis::printCommonWords(int topWords) { //print results in cog-friendly format

  for (int s=0; s<topWords; s++) {
    cout << words[s].count << " - " << words[s].w << endl;
  }


}
