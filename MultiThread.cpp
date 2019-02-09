#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"

#define NUM_THREADS 9
using namespace std;

int leftArray[3][3];
int rightArray[3][3];
int resultArray[3][3];

struct thread_data {
  int rowLeft;
  int columnRight;
};

void *matrix_mult(void *t) {
  struct thread_data *my_data;
  my_data = (struct thread_data *) t;

  int x,y,z;

  x = leftArray[my_data->rowLeft][0]* rightArray[0][my_data->columnRight];
  y = leftArray[my_data->rowLeft][1]* rightArray[1][my_data->columnRight];
  z = leftArray[my_data->rowLeft][2]* rightArray[2][my_data->columnRight];

  resultArray[my_data->rowLeft][my_data->columnRight] = x + y + z;
  pthread_exit(NULL);
}

//int main (int argc, char *argv[]) {
int main (int argc, char*argv[]) {

  int rc;
  int i;
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  void *status;
  int threadCount = 0;
  thread_data *data[9];


  string inFile1 = "";
  string inFile2 = "";
  string stringNumber = "";

  Scanner input1, input2;

  Utils::CheckArgs(2, argc, argv, "infilename (first matrix) infilename2 (second matrix)");

  inFile1 = static_cast<string>(argv[1]);
  inFile2 = static_cast<string>(argv[2]);

  input1.openFile(inFile1);
  input2.openFile(inFile2);

  //leftArray
  for(int x = 0; x < 3 && input1.hasNext(); x++){
    for(int y = 0; y < 3; y++){

    stringNumber = input1.next();
    leftArray[x][y] = stoi(stringNumber);
  }
}

  //rightArray
  for(int x = 0; x < 3 && input2.hasNext(); x++){
    for(int y = 0; y < 3; y++){

    stringNumber = input2.next();
    rightArray[x][y] = stoi(stringNumber);
  }
}

  // Initialize and set thread joinable
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  int j = 0;
  for(int row = 0; row < 3; row++) {
    for(int column = 0; column < 3; column++) {

      cout << "main() : creating thread, " << i << endl;

      data[j] = new thread_data;
      data[j]->rowLeft = row;
      data[j]->columnRight = column;

      rc = pthread_create(&threads[threadCount], NULL, matrix_mult, (void *)&(*data[j]));
      threadCount++;
      j++;

      if (rc) {
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
      }
      i++;
    }
  }

  // free attribute and wait for the other threads
  // waits for all threads to complete before they continue
  pthread_attr_destroy(&attr);
  for( i = 0; i < NUM_THREADS; i++ ) {
     rc = pthread_join(threads[i], &status);
     if (rc) {
        cout << "Error:unable to join," << rc << endl;
        exit(-1);
     }

     cout << "Main: completed thread id :" << i ;
     cout << "  exiting with status :" << status << endl;
  }

  cout << resultArray[0][0] << " " << resultArray[0][1] << " " << resultArray[0][2] << endl;
  cout << resultArray[1][0] << " " << resultArray[1][1] << " " << resultArray[1][2] << endl;
  cout << resultArray[2][0] << " " << resultArray[2][1] << " " << resultArray[2][2]<< endl;
  //pthread_exit(NULL);
}
