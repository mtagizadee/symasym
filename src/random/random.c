#include <stdlib.h>
#include <time.h>
#include "random.h"

int getRandSeed(void) {
  int nSeed = (int) time(NULL), nRand = randint(10, 1000), nRand2 = randint(10, 1000);

  return (nSeed / nRand) + nRand2;
}

void setRandSeed(int nSeed) {
  srand(nSeed);
}

int randint(int nMin, int nMax) {
  return (rand() % (nMax - nMin + 1)) + nMin;
} 