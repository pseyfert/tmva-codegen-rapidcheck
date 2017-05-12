#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#ifdef reference
#include "reference/TMVA_MLP_Forward1stLoop.h"
#else
#include "safe/TMVA_MLP_Forward1stLoop.h"
#endif
#include <pthread.h>

struct nerv {
  IClassifierReader* reader;
  std::vector<float> args;
};

void* calc(void* args) {
  struct nerv* a = (struct nerv*) args;
  float result = (a->reader)->GetMvaValue(a->args);
  printf("%f\n",result);
  return NULL;
}


int main() {
  IClassifierReader* foobar = new ReadMLP_Forward1stLoop({ "nPlanes", "dSlope", "dp", "slope2", "dby", "dbx", "day" });
  std::vector<float> hurz = {6,0.01,10,0.33,0.12,0.11,0.3};

  pthread_t child;
  struct nerv a;
  a.reader = foobar;
  a.args = hurz;
  pthread_create(&child, NULL, calc, (void*)&a);
  std::vector<float> hurz2 = {6,0.01,10,0.33,0.12,0.11,0.3};
  printf("%f\n",foobar->GetMvaValue(hurz2));
  pthread_join(child, NULL);
  delete foobar;
  return 0;
}

