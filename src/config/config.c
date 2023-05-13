#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../random/random.h"

int setParam(char* argv[], int *pI);
int setParamWrapper(char* sArgument, char* sOption, char* argv[], void func (char*), int *pI, int nIncr);
void setPossbileArgs(void);
void init(void);

void setSize(char* sSize);
void setN(char* sN);
void setSeed(char* sSeed);
void setVS();
void setVAS();
void setHS();
void setHAS();

SConfig* pConf; // config is the input from the arguments

void extractConfig(int argc, char* argv[]) {
  init();
  
  for (int i = 1; i < argc; i++) {
    setParam(argv, &i);
  }
}

void init(void) {
  pConf = (SConfig*)malloc(sizeof(SConfig));
  
  pConf->nSize = DEFAULT_SIZE;
  pConf->n = DEFAULT_IMAGES_AMOUNT;
  
  setRandSeed((int) time(NULL));
  pConf->nSeed = getRandSeed();
  determineLineTypes(pConf->nSeed);

  setPossbileArgs();
}

void determineLineTypes(int nSeed) {
  if (pConf->fTypesProvided) return;

  switch (nSeed % 4) {
    case 0: // create a horizontal asymmetric line
      pConf->asstype = asymmetric;
      pConf->vhtype = horizontal;
      break;
    case 1: // create a horizontal symmetric line
      pConf->asstype = symmetric;
      pConf->vhtype = horizontal;
      break;
    case 2: // create a vertical asymmetric line
      pConf->asstype = asymmetric;
      pConf->vhtype = vertical;
      break;
    case 3: // create a vertical symmetric line
      pConf->asstype = symmetric;
      pConf->vhtype = vertical;
      break;
  }

  pConf->fTypesProvided = 0;
}

void setPossbileArgs(void) {
  sPossibleArgs[0] = "-size";
  sPossibleArgs[1] = "-n";
  sPossibleArgs[2] = "-o";
  sPossibleArgs[3] = "-seed";
  sPossibleArgs[4] = "-vs";
  sPossibleArgs[5] = "-sv";
  sPossibleArgs[6] = "-va";
  sPossibleArgs[7] = "-av";
  sPossibleArgs[8] = "-hs";
  sPossibleArgs[9] = "-sh";
  sPossibleArgs[10] = "-ha";
  sPossibleArgs[11] = "-ah";
}

// this funciton is created in order to follow config encapsulation and imutability outside this file
SConfig* getConfig(void) {
  return pConf;
}

void showConfig(void) {
  printf("\n#---- Current Config ----#\n");
  printf("n --> %d\n", pConf->n);
  printf("size --> %d\n", pConf->nSize);
  printf("seed --> %d\n", pConf->nSeed);
  printf("o --> %s\n", pConf->o);
  printf("vh --> %d\n", pConf->vhtype);
  printf("ass --> %d\n", pConf->asstype);
  printf("#---- End of Current Config ----#\n");
}

void setSize(char* sSize) {
  pConf->nSize = atoi(sSize);
}

void setN(char* sN) {
  pConf->n = atoi(sN);
}

void setSeed(char* sSeed) {
  pConf->nSeed = atoi(sSeed);
  pConf->fSeedProvided = 1;
  determineLineTypes(pConf->nSeed);
}

void changeSeed(int nSeed) {
  pConf->nSeed = nSeed;
  determineLineTypes(pConf->nSeed);
}

void setO(char* sO) {
  pConf->o = sO;
}

void setVS() {
  pConf->vhtype = vertical;
  pConf->asstype = symmetric;
  pConf->fTypesProvided = 1;
}

void setVAS() {
  pConf->vhtype = vertical;
  pConf->asstype = asymmetric;
  pConf->fTypesProvided = 1;
}

void setHS() {
  pConf->vhtype = horizontal;
  pConf->asstype = symmetric;
  pConf->fTypesProvided = 1;
}

void setHAS() {
  pConf->vhtype = horizontal;
  pConf->asstype = asymmetric;
  pConf->fTypesProvided = 1;
}

int setParam(char* argv[], int *pI) {
  char* sArgument = argv[*pI];
  
  if ( // I could have iterated over sPossbileArgs, but I decided to hardcode it in order to keep the code simple. 
    setParamWrapper(sArgument, sPossibleArgs[0], argv, setSize, pI, 1) ||
    setParamWrapper(sArgument, sPossibleArgs[1], argv, setN, pI, 1) || 
    setParamWrapper(sArgument, sPossibleArgs[2], argv, setO, pI, 1) || 
    setParamWrapper(sArgument, sPossibleArgs[3], argv, setSeed, pI, 1) ||
    setParamWrapper(sArgument, sPossibleArgs[4], argv, setVS, pI, 0) || 
    setParamWrapper(sArgument, sPossibleArgs[5], argv, setVS, pI, 0) || 
    setParamWrapper(sArgument, sPossibleArgs[6], argv, setVAS, pI, 0) || 
    setParamWrapper(sArgument, sPossibleArgs[7], argv, setVAS, pI, 0) ||
    setParamWrapper(sArgument, sPossibleArgs[8], argv, setHS, pI, 0) ||
    setParamWrapper(sArgument, sPossibleArgs[9], argv, setHS, pI, 0) || 
    setParamWrapper(sArgument, sPossibleArgs[10], argv, setHAS, pI, 0) || 
    setParamWrapper(sArgument, sPossibleArgs[11], argv, setHAS, pI, 0) 
  ) return 1; // if at least one of args matchs with option then there is no need to check for others for now
  
  // if the code got to this line, then the passed argument is invalid for the system
  printf("Error: Invalid argument is passed! Possible arguments are: \n");
  for (int i = 0; i < POSSIBLE_ARGS_SIZE; i++) {
    printf("%s ", sPossibleArgs[i]);
  } printf("\n");

  return 0;
}

// wrapper to avoid code repetetions in setParam (every config option is being set by the same logic, the only difference is in the value of sOption)
int setParamWrapper(char* sArgument, char* sOption, char* argv[], void func (char*), int *pI, int nIncr) {
  if (strcmp(sArgument, sOption) == 0) {
    if (nIncr) *pI = *pI + 1;
    
    func(argv[*pI]);
    return 1;
  }

  return 0; // the argument is not the same as option
}