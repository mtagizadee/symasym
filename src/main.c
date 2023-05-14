#include <stdio.h>
#include "config/config.h"
#include "symasym/symasym.h"

int main(int argc, char* argv[]) {
  extractConfig(argc, argv); // extract the config from the command line

  showConfig();
  generateImages(); // generate all required images

  return 0;
}