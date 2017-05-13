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
  IClassifierReader() : fStatusIsClean(true) {}
  virtual ~IClassifierReader() {}

  // return classifier response
  virtual double GetMvaValue(const std::vector<double> &inputValues) const = 0;

  // returns classifier status
  bool IsStatusClean() const { return fStatusIsClean; }

protected:
  bool fStatusIsClean;
};

#endif
namespace safe {
#include "thenew.class.C"
}
namespace reference {
#include "theref.class.C"
}

int main() {
  rc::check("GetMvaValue", [](const std::array<double, 4> &l0) {
    std::vector<std::string> vars({"var1+var2", "var1-var2", "var3", "var4"});
    safe::ReadMLP *saf = new safe::ReadMLP(vars);
    reference::ReadMLP *ref = new reference::ReadMLP(vars);
    std::vector<double> input;
    input.insert(input.begin(), l0.begin(), l0.end());
    float refval = ref->GetMvaValue(input);
    float safval = saf->GetMvaValue(input);

    RC_ASSERT(refval == safval);
  });

  return 0;
}
