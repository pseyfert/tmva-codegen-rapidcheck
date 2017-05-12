#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "rapidcheck.h"

#include <pthread.h>

namespace safe
{
#include "./safe/TMVA_MLP_Forward1stLoop.h"
  struct nerv {
    IClassifierReader* reader;
    std::vector<float> args;
  };
  void* calc( void* args )
  {
    struct nerv* a = (struct nerv*)args;
    float result   = ( a->reader )->GetMvaValue( a->args );
    printf( "%f\n", result );
    return NULL;
  }
}
namespace reference
{
#include "./reference/TMVA_MLP_Forward1stLoop.h"
  struct nerv {
    IClassifierReader* reader;
    std::vector<float> args;
  };
  void* calc( void* args )
  {
    struct nerv* a = (struct nerv*)args;
    float *returnf = new float();
    *returnf   = ( a->reader )->GetMvaValue( a->args );
    return returnf;
  }
}



int main()
{
  rc::check( "safe", []( const std::array<float, 7>& l0 ) {

      std::vector<float> input;
      input.insert( input.begin(), l0.begin(), l0.end() );
      safe::ReadMLP_Forward1stLoop* classifier =
      new safe::ReadMLP_Forward1stLoop( {"nPlanes", "dSlope", "dp", "slope2", "dby", "dbx", "day"} );
      pthread_t child;
      struct safe::nerv a;
      a.reader = classifier;
      a.args   = input;

      float threadval;
      float *joinedf = NULL;

      pthread_create( &child, NULL, safe::calc, (void*)&a );
      float hereval = classifier->GetMvaValue( input );
      pthread_join( child, (void **)&joinedf );

      threadval = *joinedf;
      free(joinedf);
      delete classifier;

      RC_ASSERT( threadval == hereval );
      } );
  rc::check( "reference", []( const std::array<float, 7>& l0 ) {

      std::vector<float> input;
      input.insert( input.begin(), l0.begin(), l0.end() );
      reference::ReadMLP_Forward1stLoop* classifier =
      new reference::ReadMLP_Forward1stLoop( {"nPlanes", "dSlope", "dp", "slope2", "dby", "dbx", "day"} );
      pthread_t child;
      struct reference::nerv a;
      a.reader = classifier;
      a.args   = input;

      float threadval;
      float *joinedf = NULL;

      pthread_create( &child, NULL, reference::calc, (void*)&a );
      float hereval = classifier->GetMvaValue( input );
      pthread_join( child, (void **)&joinedf );

      threadval = *joinedf;
      delete joinedf;
      delete classifier;

      RC_ASSERT( threadval == hereval );
      } );

  return 0;
}
