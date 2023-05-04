#include <stdio.h>
#include "config/config.h"
#include "symasym/symasym.h"

int main(int argc, char* argv[]) {
  extractConfig(argc, argv);

  showConfig();
}