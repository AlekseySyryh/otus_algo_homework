#include "Performance.h"
#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"
#include "MatrixArray.h"
#include "LinkedList.h"

int main() {
    const size_t tests = 100000;
    /*SingleArray<int> singleArray;
    Test(singleArray,tests);
    VectorArray<int> vectorArray;
    Test(vectorArray,tests);
    FactorArray<int> factorArray;
    Test(factorArray,tests);
    MatrixArray<int> matrixArray;
    Test(matrixArray,tests);*/
    LinkedList<int> linkedList;
    Test(linkedList,tests);
    return 0;
}