#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "TMVA/Reader.h"

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
  rc::check("ref_vs_xml", [](const std::array<double, 4> &l0) {
    std::vector<std::string> vars({"var1+var2", "var1-var2", "var3", "var4"});
    IClassifierReader *ref = new reference::ReadMLP(vars);
    TMVA::Reader *reader = new TMVA::Reader( "!Color:Silent" );
		Float_t var1, var2;
		Float_t var3, var4;
		reader->AddVariable( "myvar1 := var1+var2", &var1 );
		reader->AddVariable( "myvar2 := var1-var2", &var2 );
		reader->AddVariable( "var3",                &var3 );
		reader->AddVariable( "var4",                &var4 );

		// Spectator variables declared in the training have to be added to the reader, too
		Float_t spec1,spec2;
		reader->AddSpectator( "spec1 := var1*2",   &spec1 );
		reader->AddSpectator( "spec2 := var1*3",   &spec2 );

		reader->BookMVA( "MLP method", "./TMVAClassification_MLP.weights.xml" );

    std::vector<double> input;
    input.insert(input.begin(), l0.begin(), l0.end());
    var1 = l0[0];
    var2 = l0[1];
    var3 = l0[2];
    var4 = l0[3];
    float refval = ref->GetMvaValue(input);
    float xmlval = reader->EvaluateMVA( "MLP method" );

    RC_ASSERT(fabs(refval - xmlval)<0.001);
  });
  rc::check("intermediate_vs_xml", [](const std::array<double, 4> &l0) {
    std::vector<std::string> vars({"var1+var2", "var1-var2", "var3", "var4"});
    IClassifierReader *ref = new intermediate::ReadMLP(vars);
    TMVA::Reader *reader = new TMVA::Reader( "!Color:Silent" );
		Float_t var1, var2;
		Float_t var3, var4;
		reader->AddVariable( "myvar1 := var1+var2", &var1 );
		reader->AddVariable( "myvar2 := var1-var2", &var2 );
		reader->AddVariable( "var3",                &var3 );
		reader->AddVariable( "var4",                &var4 );

		// Spectator variables declared in the training have to be added to the reader, too
		Float_t spec1,spec2;
		reader->AddSpectator( "spec1 := var1*2",   &spec1 );
		reader->AddSpectator( "spec2 := var1*3",   &spec2 );

		reader->BookMVA( "MLP method", "./TMVAClassification_MLP.weights.xml" );

    std::vector<double> input;
    input.insert(input.begin(), l0.begin(), l0.end());
    var1 = l0[0];
    var2 = l0[1];
    var3 = l0[2];
    var4 = l0[3];
    float refval = ref->GetMvaValue(input);
    float xmlval = reader->EvaluateMVA( "MLP method" );

    RC_ASSERT(fabs(refval - xmlval)<0.001);
  });
  rc::check("PR_vs_xml", [](const std::array<double, 4> &l0) {
    std::vector<std::string> vars({"var1+var2", "var1-var2", "var3", "var4"});
    IClassifierReader *ref = new PR::ReadMLP(vars);
    TMVA::Reader *reader = new TMVA::Reader( "!Color:Silent" );
		Float_t var1, var2;
		Float_t var3, var4;
		reader->AddVariable( "myvar1 := var1+var2", &var1 );
		reader->AddVariable( "myvar2 := var1-var2", &var2 );
		reader->AddVariable( "var3",                &var3 );
		reader->AddVariable( "var4",                &var4 );

		// Spectator variables declared in the training have to be added to the reader, too
		Float_t spec1,spec2;
		reader->AddSpectator( "spec1 := var1*2",   &spec1 );
		reader->AddSpectator( "spec2 := var1*3",   &spec2 );

		reader->BookMVA( "MLP method", "./TMVAClassification_MLP.weights.xml" );

    std::vector<double> input;
    input.insert(input.begin(), l0.begin(), l0.end());
    var1 = l0[0];
    var2 = l0[1];
    var3 = l0[2];
    var4 = l0[3];
    float refval = ref->GetMvaValue(input);
    float xmlval = reader->EvaluateMVA( "MLP method" );

    RC_ASSERT(fabs(refval - xmlval)<0.001);
  });

  return 0;
}
