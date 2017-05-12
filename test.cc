#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "rapidcheck.h"

namespace safe
{
#include "./safe/TMVA_MLP_Forward1stLoop.h"
}
namespace reference
{
#include "./reference/TMVA_MLP_Forward1stLoop.h"
}

int main()
{
  rc::check( "GetMvaValue__", []( const std::array<float, 7>& l0 ) {
    safe::ReadMLP_Forward1stLoop* saf =
        new safe::ReadMLP_Forward1stLoop( {"nPlanes", "dSlope", "dp", "slope2", "dby", "dbx", "day"} );
    reference::ReadMLP_Forward1stLoop* ref =
        new reference::ReadMLP_Forward1stLoop( {"nPlanes", "dSlope", "dp", "slope2", "dby", "dbx", "day"} );
    std::vector<float> input;
    input.insert( input.begin(), l0.begin(), l0.end() );
    float refval = ref->GetMvaValue__( input );
    float safval = saf->GetMvaValue__( input );

    RC_ASSERT( refval == safval );
  } );
  rc::check( "GetMvaValue", []( const std::array<float, 7>& l0 ) {
    safe::ReadMLP_Forward1stLoop* saf =
        new safe::ReadMLP_Forward1stLoop( {"nPlanes", "dSlope", "dp", "slope2", "dby", "dbx", "day"} );
    reference::ReadMLP_Forward1stLoop* ref =
        new reference::ReadMLP_Forward1stLoop( {"nPlanes", "dSlope", "dp", "slope2", "dby", "dbx", "day"} );
    std::vector<float> input;
    input.insert( input.begin(), l0.begin(), l0.end() );
    float refval = ref->GetMvaValue( input );
    float safval = saf->GetMvaValue( input );

    RC_ASSERT( refval == safval );
  } );

  return 0;
}
