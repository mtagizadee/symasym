#include <stdlib.h>
#include <time.h>
#include "random.h"

int getRandSeed(void) {
  int nSeed = (int) time(NULL);
  return nSeed;
}

void setRandSeed(int nSeed) {
  srand(nSeed);
}

int randint(int nMin, int nMax) {
  return (rand() % (nMax - nMin + 1)) + nMin;
} 