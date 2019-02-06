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
/*
while(scnnaer1.next())
{
  element = scanner1.hasNext();
  element = scanner1.next();
  val = std::atoi(element.cstr())
}
*/
struct thread_data {
  int leftArray[3][3];
  int rightArray[3][3];
  int resultArray[3][3];
  int rowLeft;
  int columnRight;
};

void *matrix_mult(void *t) {
  struct thread_data *my_data;
  my_data = (struct thread_data *) t;

  int x,y,z;

  x = my_data->leftArray[my_data->rowLeft][0]* my_data->rightArray[0][my_data->columnRight];
  y = my_data->leftArray[my_data->rowLeft][1]* my_data->rightArray[1][my_data->columnRight];
  z = my_data->leftArray[my_data->rowLeft][2]* my_data->rightArray[2][my_data->columnRight];

  my_data->resultArray[my_data->rowLeft][my_data->columnRight] = x + y + z;
  pthread_exit(NULL);
}



//int main (int argc, char *argv[]) {
int main () {

  int rc;
  int i;
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  void *status;
  int threadCount = 0;
  struct thread_data data = {};

  data.leftArray[0][0] = 1;
  data.leftArray[0][1] = 2;
  data.leftArray[0][2] = 3;
  data.leftArray[1][0] = 4;
  data.leftArray[1][1] = 5;
  data.leftArray[1][2] = 6;
  data.leftArray[2][0] = 7;
  data.leftArray[2][1] = 8;
  data.leftArray[2][2] = 9;

  data.rightArray[0][0] = 1;
  data.rightArray[0][1] = 2;
  data.rightArray[0][2] = 3;
  data.rightArray[1][0] = 4;
  data.rightArray[1][1] = 5;
  data.rightArray[1][2] = 6;
  data.rightArray[2][0] = 7;
  data.rightArray[2][1] = 8;
  data.rightArray[2][2] = 9;

  // Initialize and set thread joinable
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(int row = 0; row < 3; row++) {
    for(int column = 0; column < 3; column++) {

      cout << "main() : creating thread, " << i << endl;

      data.rowLeft = row;
      data.columnRight = column;

      rc = pthread_create(&threads[threadCount], NULL, matrix_mult, (void *)&data);
      threadCount++;

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

  cout << data.resultArray[0][0] << " " << data.resultArray[0][1] << " " << data.resultArray[0][2] << endl;
  cout << data.resultArray[1][0] << " " << data.resultArray[1][1] << " " << data.resultArray[1][2] << endl;
  cout << data.resultArray[2][0] << " " << data.resultArray[2][1] << " " << data.resultArray[2][2]<< endl;
  //pthread_exit(NULL);
}
