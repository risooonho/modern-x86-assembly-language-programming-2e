//------------------------------------------------
//               Ch16_03.cpp
//------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <random>
#include "Ch16_03.h"
#include "AlignedMem.h"

using namespace std;

void LinkedListPrefetch(void)
{
    const int num_nodes = 8;
    LlNode* list1 = LlCreate(num_nodes);
    LlNode* list2a = LlCreate(num_nodes);
    LlNode* list2b = LlCreate(num_nodes);

    LlTraverse(list1);
    LlTraverseA_(list2a);
    LlTraverseB_(list2b);

    int node_fail;
    const char* fn = "Ch16_03_LinkedListPrefetchResults.txt";

    cout << "Results for LinkedListPrefetch\n";

    if (LlCompare(num_nodes, list1, list2a, list2b, &node_fail))
        cout << "Linked list compare OK\n";
    else
        cout << "Linked list compare FAILED - node_fail = " << node_fail << '\n';

    LlPrint(list1, fn,  "----- list1 -----",  0);
    LlPrint(list2a, fn, "----- list2a -----", 1);
    LlPrint(list2b, fn, "----- list2b -----", 1);

    cout << "Linked list results saved to file " << fn << '\n';

    LlDelete(list1);
    LlDelete(list2a);
    LlDelete(list2b);
}

int main()
{
    LinkedListPrefetch();
    LinkedListPrefetch_BM();
    return 0;
}
