#include "RLEList.h"

#define ADD_NEW_LINE 2
/**
 * Here we define the structure of the RLEList_t
 * which has 3 parameters:
 *   c: to store the input character
 *   numOfOccrances: to store the times the character c has appeared in a row.
 *   next: a pointer to hte next node in the list, and to NULL if it's the last node.
 */
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

void _writeDigits(char* str, int digitsNum){
    while (digitsNum){
        str[digitsNum-1]= digitsNum%10;
        digitsNum /= 10;
    }
    
}

RLEList RLEListCreate(){
    RLEList new = malloc(sizeof(*new));
    if(!new){
        free(new);
        return NULL;
    }
    new->c = '\0';
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

    if(!list || !map_function){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list){
        list->c = map_function(list->c);
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result){
    char* str;
    int i = 0;

    if (!result)
    {
        return NULL;
    }else if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    
    str = malloc(sizeof(char) * _neededCells(list));
    int digits;
    if(!str){
        free(str);
        *result = RLE_LIST_ERROR;
        return NULL;
    }

    while(list){
        str[i] = list->c;
        digits = _digitCounter(list->numOfOccurances);
        _writeDigits(&str[++i], digits);
        str[i + digits] = '\n';
        list = list->next;
        i++;
    }
    *result = RLE_LIST_SUCCESS;
    return str;
}
