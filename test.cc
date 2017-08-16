#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "rapidcheck.h"

#ifndef IClassifierReader__def
#define IClassifierReader__def

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() : fStatusIsClean( true ) {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual double GetMvaValue( const std::vector<double>& inputValues ) const = 0;

   // returns classifier status
   bool IsStatusClean() const { return fStatusIsClean; }

 protected:

   bool fStatusIsClean;
};

#endif

namespace intermediate {
#include "intermediate/TMVAClassification_MLP.class.C"
}
namespace reference {
#include "ref/TMVAClassification_MLP.class.C"
}
namespace PR {
#include "PR/TMVAClassification_MLP.class.C"
}

int main() {
  rc::check("ref_vs_intermediate", [](const std::array<double, 4> &l0) {
    std::vector<std::string> vars({"var1+var2", "var1-var2", "var3", "var4"});
    IClassifierReader *saf = new reference::ReadMLP(vars);
    IClassifierReader *ref = new intermediate::ReadMLP(vars);
    std::vector<double> input1;
    std::vector<double> input2;
    input1.insert(input1.begin(), l0.begin(), l0.end());
    input2.insert(input2.begin(), l0.begin(), l0.end());
    float refval = ref->GetMvaValue(input1);
    float safval = saf->GetMvaValue(input2);

    RC_ASSERT(refval == safval);
  });

  return 0;
}
