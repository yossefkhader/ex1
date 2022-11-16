#include "RLEList.h"

#define INITIAL_VALUE NULL
#define ADD_NEW_LINE 2

struct RLEList_t{
    char c;
    int numOfOccurances;
    RLEList next;
};

int _nodeCounter(RLEList list){
    int counter = 0;
    while(list){
        counter++;
        list = list->next;
    }
    return counter;
}

int _digitCounter(int num){
    int counter = 0;
    if(num < 0){
        num *= -1;
    }
    while(num > 0){
        num /= 10;
        counter++;
    }
    return counter;
}

int _neededCells(RLEList list){
    int digitCounter = 0, nodeNumber = _nodeCounter(list);
    
    nodeNumber *= ADD_NEW_LINE;
    while(list){
        digitCounter += _digitCounter(list->numOfOccurances);
        list = list->next;
    }

    return nodeNumber + digitCounter;
}

void _writeDigits(char* str, int num){
    for (int i = _digitCounter(num)-1; i >= 0; i--){
        str[i]= num%10;
        num /= 10;
    }
    
}

RLEList RLEListCreate(){
    RLEList new = malloc(sizeof(*new));
    if(!new){
        return NULL;
    }
    new->c = INITIAL_VALUE;
    new->next = NULL;
    return new;
}

void RLEListDestroy(RLEList list){
    RLEList tmp;
    while(list){
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    RLEList curr;
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }
    curr = list;
    while(curr){
        curr->c = map_function(curr->c);
        curr = curr->next;
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result){
    char* str;
    int i = 0;

    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    
    str = malloc(sizeof(char) * _neededCells(list));
    
    if(!str){
        free(str);
        *result = RLE_LIST_ERROR;
        ///todo: check if the error is suitable
        return NULL;
    }

    while(list){
        str[i] = list->c;
        _writeDigits(str[++i], list->numOfOccurances);
        str[i + _digitCounter(list->numOfOccurances)] = '\n';
        list = list->next;
        i++;
    }
    *result = RLE_LIST_SUCCESS;
    return str;
}
