#include <iostream>
#include <ctime>
//include correct libraries


/*

To find which algorithm was more efficient, I added a counter into each of the algorithms
that was increased whenever a swap occured. I then made a function that created arrays of
random ints and passed these into the different sorting algorithms. After testing with
different sized arrays, I found that selectSort was the most efficient.

*/


using namespace std;

int swapQuick=0;
int swapShell=0;
int swapRadix=0;
int loopQuick=0;
int loopShell=0;
int loopRadix=0;

int arraySize=1000000;

void printList(int arr[], int length){
  for (int i = 0; i<length; i++){
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}

void quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        loopQuick++;
        while (arr[i] < pivot)
            i++;
            loopQuick++;
        while (arr[j] > pivot)
            j--;
            loopQuick++;
        if (i <= j) {
            swapQuick++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

void shellSort (int ar[], int size) {

  int j;

  for (int gap = size / 2; gap > 0; gap /= 2) {
    loopShell++;
    for (int i = gap; i < size; ++i) {
      loopShell++;
      int temp = ar[i];

      for (j = i; j >= gap && temp < ar[j - gap]; j -= gap) {
        loopShell++;
        ar[j] = ar[j - gap];
        swapShell++;
      }

      ar[j] = temp;
    }
  }

}

int getMax(int arr[], int n) {

  int max = arr[0];

  for (int i = 1; i < n; i++) {
    loopRadix++;
    if (arr[i] > max)
      max = arr[i];
  }

  return max;

}

void countSort(int arr[], int n, int expo) {

  int output[n];
  int i, count[10] = {0};

  for (i = 0; i < n; i++) {
    loopRadix++;
    count[(arr[i] / expo) % 10]++;
  }

  for (i = 1; i < 10; i++) {
    loopRadix++;
    count[i] += count[i - 1];
  }

  for (i = n - 1; i >= 0; i--) {
    loopRadix++;
    swapRadix++;
    output[count[(arr[i] / expo) % 10] - 1] = arr[i];
    count[(arr[i] / expo) % 10]--;
  }

  for (i = 0; i < n; i++) {
    loopRadix++;
    swapRadix++;
    arr[i] = output[i];
  }

}

void radixSort(int *arr, int n) {
  int m = getMax(arr, n);

  for (int expo = 1; m / expo > 0; expo *= 10) {
    loopRadix++;
    countSort(arr, n, expo);
  }

}

void randArray(int *array1, int *array2, int* array3, int size) {

  int r;

  for (int i=0; i<size; i++) {
      r=rand()%1000;
      array1[i]=array2[i]=array3[i]=r;
  }

}

int main(){

  int *largeArray1=new int[arraySize];
  int *largeArray2=new int[arraySize];
  int *largeArray3=new int[arraySize];

  //Generate array
  int start = clock();
  randArray(largeArray1, largeArray2, largeArray3, arraySize);
  cout << endl << "The array is being generated" << endl;
  int stop = clock();
  cout<< "Time elapsed: " <<(stop-start)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl << endl;

  //radixSort
  start = clock();
  radixSort(largeArray1, arraySize);
  cout << "When ordered with radixSort, the algorithm performs " << loopRadix << " loops and  " << swapRadix << " swaps." << endl;
  // printList(largeArray1, arraySize);
  // cout << endl << endl;
  stop = clock();
  cout<< "Time elapsed: " <<(stop-start)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl << endl;

  //shellSort
  start = clock();
  shellSort(largeArray2, arraySize);
  cout << "When ordered with shellSort, the algorithm performs " << loopShell << " loops and  " << swapShell << " swaps." << endl;
  // printList(largeArray2, arraySize);
  // cout << endl << endl;
  stop = clock();
  cout<< "Time elapsed: " <<(stop-start)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl << endl;

  //quickSort
  start = clock();
  quickSort(largeArray3, 0, arraySize-1);
  cout << "When ordered with quickSort, the algorithm performs " << loopQuick << " loops and  " << swapQuick << " swaps." << endl;
  // printList(largeArray3, arraySize);
  // cout << endl << endl;
  stop = clock();
  cout<< "Time elapsed: " <<(stop-start)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl << endl;

  return 0;
}
