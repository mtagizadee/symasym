#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_SIZE 32
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
} SConfig;


void extractConfig(int argc, char* argv[]);
SConfig* getConfig(void);
void showConfig(void);

#endif