#include <stdio.h>
#include "config/config.h"
#include "random/random.h"

int main(int argc, char* argv[]) {
  extractConfig(argc, argv);
  showConfig();

  int nSeed = getRandSeed();
  setRandSeed(nSeed);

  printf("\nSeed -> %d\n", nSeed);

  printf("%d\n", randint(1, 10));

}