#include "RLEList.h"

struct RLEList_t{
    char c;
    int numOfOccurances;
    RLEList next;
};

//yossef: 8,7,2,1
//aaseel: 5,4,3,6
//implement the functions here