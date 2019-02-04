#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

/*
while(scnnaer1.next())
{
  element = scanner1.hasNext();

  element = scanner1.next();
  val = std::atoi(element.cstr())
}

*/

using namespace std;

#include "../Utilities/Utils.h"
#include "../Utilities/Scanner.h"
#include "../Utilities/ScanLine.h"

#define NUM_THREADS 9

struct thread_data{

int arrayLeft[3][3];
int arrayRight[3][3];
int resultArray[3][3];
int rowLeft;
int columnRight;
}
void *matrix_mult(void *t) {

struct thread_data *my_data;
my_data = (struct thread_data *) t;

  int x,y,z;

  x = my_data->leftArray[rowLeft][0]*rightArray[0][columnRight];
  y = my_data->leftArray[rowLeft][1]*rightArray[1][columnRight];
  z = my_data->leftArray[rowLeft][2]*rightArray[2][columnRight];

  my_data->resultArray[rowLeft][columnRight] = x + y + z;

}

//int main (int argc, char *argv[]) {
int main () {

pthread_t threads[NUM_THREADS];
thread_data data;

data.leftArray[0][1] = 1;
data.leftArray[0][2] = 2;
data.leftArray[0][3] = 3;
data.leftArray[1][1] = 4;
data.leftArray[1][2] = 5;
data.leftArray[1][3] = 6;
data.leftArray[2][1] = 7;
data.leftArray[2][2] = 8;
data.leftArray[2][3] = 9;

data.rightArray[0][1] = 1;
data.rightArray[0][2] = 2;
data.rightArray[0][3] = 3;
data.rightArray[1][1] = 4;
data.rightArray[1][2] = 5;
data.rightArray[1][3] = 6;
data.rightArray[2][1] = 7;
data.rightArray[2][2] = 8;
data.rightArray[2][3] = 9;

for(int row = 0; row < 3; row++) {
  for(int column = 0; column < 3; column++) {
  //I think we might have to put our thread creation function here. I need to think about it more.
  //I'm unsure if a single thread we create will run 'matrixMath' once and then terminate,
  //or just go on and loop when we don't want it to.
  data.rowLeft = row;
  data.columnRight = column;
  rc = pthread_create(&threads[i], NULL, matrix_mult, (void *)&data);

  if (rc) {
     cout << "Error:unable to create thread," << rc << endl;
     exit(-1);
  }

    }
  }
}
