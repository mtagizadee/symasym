#include <stdint.h>
#include <stdlib.h>
#include "symasym.h"
#include "../config/config.h"

void generateImage() {
  SConfig* pConf = getConfig();
  uint8_t image = (uint8_t*) malloc(pConf->nSize * pConf->nSize * sizeof(uint8_t) * STEP_SIZE);

}
