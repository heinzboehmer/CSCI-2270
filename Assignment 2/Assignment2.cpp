#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct words { //declare global struct

  string word;
  int count;

};

words *wordArray=new words[100]; //declare global array in heap
int arraySize=100;  //declare global array size to keep track of when array doubling is needed
int arrayDoubled=0;
int numTotalUniqueWords=0;

void doubleArray(int size) {    //function to double array

  words *aDouble=new words[size*2];

  for (int x=0; x<size; x++) {
    aDouble[x]=wordArray[x];
  }

  delete []wordArray;
  wordArray=aDouble;
  arraySize=arraySize*2;
  arrayDoubled++;

}

int commonWord(string comparisonWord) { //function to check for common words and whitespaces

  string words[52]={"the", "be", "to", "of", "and", "a", "in", "that", "have",
                    "i", "it", "for", "not", "on", "with", "he", "as", "you",
                    "do", "at", "this", "but", "his", "by", "from", "they",
                    "we", "say", "her", "she", "or", "an", "will", "my", "one",
                    "all", "would", "there", "their", "what", "so", "up", "out",
                    "if", "about", "who", "get", "which", "go", "me", " ", ""};

  for (int z=0; z<52; z++) {

    if (words[z]==comparisonWord) {
      return 1;
    }

  }

  return 0;

}

string removeWhitespace(string word) { //function to remove leading whitespaces

  if (isspace(word[0])) {

    for (int r=0; r<(word.length()-1); r++) {
    word[r]=word[r+1];
    }

    word.resize (word.length()-1);

  }

  return word;

}

int readText(string filename) { //function to read text file and populate array

  string tWord; //string to hold output of getline before analysis
  int match=0;
  int i=0; //index of next available slot in array

  ifstream inFile; //open file
	inFile.open(filename);

	while (inFile >> tWord) { //read data

    match=0;

    if (commonWord(tWord)!=1) { //check if word is common

  		for (int j=0; j<i; j++) { //check if word is already in array

        if (wordArray[j].word==tWord) {

          match=1;
          wordArray[j].count=wordArray[j].count+1; //if a match is found, increase count
          numTotalUniqueWords++; //increase total unique words counter
          break;

  			}
  		}

  		if (match!=1) { //only runs if no match is found

        if (i+1>arraySize) { //call double array function if array is full
          doubleArray(arraySize);
        }

  			wordArray[i].word=tWord; //add new word to array
        wordArray[i].count=1;

        numTotalUniqueWords++; //increase total unique words counter
        i++; //increase next available slot index
  		}

    }

  }

  if (match==1) { //i wont increase unless the last word in text is not a match,
    i++;          //but i is returned to count number of unique words, so if
  }               //last word is a match, i is increased

  return i;

}

void sortArray() { //insertionSort used to sort array from largest to smallest

  int index;
  words indexStruct;
  int j;

  for (int i=1; i<arraySize; i++) {

      index=wordArray[i].count;
      indexStruct=wordArray[i];

      j=i;

      while(j>0 && wordArray[j-1].count<index) {

          wordArray[j]=wordArray[j-1];
          j=j-1;

      }

      wordArray[j]=indexStruct;

  }

}

void printArray(int topWords, int uniqueWords, int totalUniqueWords) { //print results in cog-friendly format

  for (int s=0; s<topWords; s++) {
    cout << wordArray[s].count << " - " << wordArray[s].word << endl;
  }

  cout << "#" << endl;
  cout << "Array doubled: " << arrayDoubled << endl;
  cout << "#" << endl;
  cout << "Unique non-common words: " << uniqueWords << endl;
  cout << "#" << endl;
  cout << "Total non-common words: " << totalUniqueWords;

}

int main(int argc, char *argv[]) {

  int numUniqueWords; //hold unique word count for use as argument in print function
  numUniqueWords=readText(argv[1]);
  sortArray();
  printArray(stoi(argv[2]), numUniqueWords, numTotalUniqueWords);

  return 0;
}
