#ifndef RANDOM_H
#define RANDOM_H

int getRandSeed(void); // Returns a random seed
void setRandSeed(int nSeed); // Sets the random number seed to nSeed
int randint(int min, int max); // Returns a random integer between min and max

#endif