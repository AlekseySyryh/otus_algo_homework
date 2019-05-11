#include "Performance.h"
#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"

int main() {
    SingleArray<int> singleArray;
    Test(singleArray,100000);
    VectorArray<int> vectorArray;
    Test(vectorArray,100000);
    FactorArray<int> factorArray;
    Test(factorArray,100000);

    return 0;
}