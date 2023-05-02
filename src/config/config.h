#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_SIZE 32
#define DEFAULT_IMAGES_AMOUNT 1

#define POSSIBLE_ARGS_SIZE 12

typedef enum LineType {asymmetric, symmetric, horizontal, vertical} LineType;

char* sPossibleArgs[POSSIBLE_ARGS_SIZE];

typedef struct SConfig {
  LineType vhtype; // vertical or horizontal
  LineType asstype; // asymmetric or symmetric
  int nSize;
  int n; // number of images to be generated
  char *o; // output file name
  int nSeed; 
  int fTypesProvided; // identifies that line types are provided by arguments or not
  int fSeedProvided;  // identifies that seed is provided by arguments or not
} SConfig;


void extractConfig(int argc, char* argv[]); // extracts arguments and set them to the config state
SConfig* getConfig(void); // returns the current state of the config
void showConfig(void); // shows the current state of the config
void determineLineTypes(int nSeed); // determines by the seed what are the types of line if they were not provided in arguments

#endif