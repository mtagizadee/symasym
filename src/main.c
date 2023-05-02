#include <stdio.h>
#include "config/config.h"

int main(int argc, char* argv[]) {
  extractConfig(argc, argv);
  showConfig();
}