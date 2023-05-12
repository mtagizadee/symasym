#include <stdlib.h>
#include <time.h>
#include "random.h"

int getRandSeed(void) {
  int nSeed = (int) time(NULL);
  int nRand = randint(10, 10000);

  return nSeed + nRand;
}

void setRandSeed(int nSeed) {
  srand(nSeed);
}

int randint(int nMin, int nMax) {
  return (rand() % (nMax - nMin + 1)) + nMin;
} 