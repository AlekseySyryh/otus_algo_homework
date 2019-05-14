#include "Performance.h"
#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"
#include "MatrixArray.h"
#include "LinkedList.h"
#include "DoubleLinkedList.h"
#include "SpaceArray.h"
#include "STLVector.h"
#include "STLDeque.h"
#include "STLForwardList.h"
#include "STLList.h"


int main() {
    const size_t tests = 100000;
    SingleArray<int> singleArray;
    Test(singleArray,tests);
    VectorArray<int> vectorArray;
    Test(vectorArray,tests);
    FactorArray<int> factorArray;
    Test(factorArray,tests);
    MatrixArray<int> matrixArray;
    Test(matrixArray,tests);
    LinkedList<int> linkedList;
    Test(linkedList,tests);
    DoubleLinkedList<int> doubleLinkedList;
    Test(doubleLinkedList,tests);
    SpaceArray<int> spaceArray;
    Test(spaceArray,tests);
    STLVector<int> stlVector;
    Test(stlVector, tests);
    STLDeque<int> stlDeque;
    Test(stlDeque, tests);
    STLForwardList<int> stlForwardList;
    Test(stlForwardList, tests);
    STLList<int> stlList;
    Test(stlList, tests);
    return 0;
}