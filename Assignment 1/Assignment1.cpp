#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct Item {

	string type;
	int price;
	string status;

};

int shiftArray(Item A[], int startIndex, int lastIndex, int shiftCount) {
	for (int x=startIndex; x<lastIndex-1; x++) {
		A[x]=A[x+1];
		shiftCount++;
	}
	return shiftCount;
}

void printOutput(Item A[], int lastIndex, int fileread, int filesearch, int fileshift) {
	for (int r=0; r<lastIndex; r++) {
		if (A[r].status=="for sale") {
			cout << A[r].type << ", " << "for sale" << ", " << A[r].price << endl;
		}
		if (A[r].status=="wanted") {
			cout << A[r].type << ", " << "wanted" << ", " << A[r].price << endl;
		}
	}

	cout << "#" << endl;

	cout << "file read:" << fileread << endl;
	cout << "search array:" << filesearch << endl;
	cout << "shift array:" << fileshift << endl;
}

void populateArray() {

	Item itemArray[100]; //Declare array
	string filename;
	string data;
	string ttype;
	string tprice;
	int sstprice;
	string tstatus;
	string temp;
	int i=0;
	int read=0;
	int search=0;
	int shift=0;
	int match=0;
	int blz=0;

	ifstream inFile;
	cin >> filename;
	inFile.open(filename);

	while (getline(inFile, data)) {
		stringstream ss(data);

		getline(ss, ttype, ',');
			getline(ss, temp, ' ');
		getline(ss, tstatus, ',');
			getline(ss, temp, ' ');
		getline(ss, tprice, '\n');

		stringstream ssprice(tprice);
		ssprice >> sstprice;

		match=0;

		for (int j=0; j<i; j++) {

			search++;

			if (itemArray[j].type==ttype) {

				if ((itemArray[j].status=="wanted") && (tstatus=="for sale") && (itemArray[j].price>=sstprice)) {
					cout << itemArray[j].type << " " << sstprice << endl;
					match=1;
					shift=shiftArray(itemArray, j, i, shift), read;
					i--;
					break;
				}

				if ((itemArray[j].status=="for sale") && (tstatus=="wanted") && (itemArray[j].price<=sstprice)) {
					cout << itemArray[j].type << " " << itemArray[j].price << endl;
					match=1;
					shift=shiftArray(itemArray, j, i, shift);
					i--;
					break;
				}
			}
		}

		if (match!=1) {
			itemArray[i].type=ttype;
			itemArray[i].price=sstprice;
			itemArray[i].status=tstatus;
			i++;
		}

		read++;

	}

	cout << "#" << endl;

	inFile.close();

	printOutput(itemArray, i, read, search, shift);

	cout << endl << i-1 << endl;
}

int main() {
	populateArray();
}
