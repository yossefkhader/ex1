#include "RLEList.h"
#include <stdlib.h>

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

typedef enum{
    REMOVE_NULL_ARGUMENT,
    REMOVE_SUCSSES,
    REMOVE_NOT_SUITABLE
} RemoveResult;

RemoveResult _rCase1(RLEList list){
    if(!list){
        return REMOVE_NULL_ARGUMENT;
    }
    if(list->numOfOccurances > 1){
        list->numOfOccurances--;
        return REMOVE_SUCSSES;
    }
    return REMOVE_NOT_SUITABLE;
}

RemoveResult _rCase2(RLEList list, RLEList prev){
    RLEList tmp;
    if(!list){
        return REMOVE_NULL_ARGUMENT;
    }else if(!prev){
        tmp = list;
        list = list->next;
        free(tmp);
        return REMOVE_SUCSSES;
    }else if(!(list->next)){
        prev->next=NULL;
        free(list);
        return REMOVE_SUCSSES;
    }
    tmp = list;
    list = list->next;
    free(tmp);
    
    if(prev->c == list->c){
        prev->numOfOccurances += list->numOfOccurances;
        prev->next = list->next;
        free(list);
        return REMOVE_SUCSSES;
    }
    
    prev->next = list;
    return REMOVE_SUCSSES;
}

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

RLEListResult RLEListAppend(RLEList list, char value) 
{
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list->next != NULL){
      list = list->next;
    }

    if(list->c == value){
        list->numOfOccurances = list->numOfOccurances + 1;
    }

    RLEList ptr = RLEListCreate();
    if(!ptr)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    ptr->c = value;
    ptr->next = NULL;
    list->next = ptr;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    int count = 0;
    if(!list){
        return -1;
    }
    while(list)
    {    
        count += list->numOfOccurances;
        list = list->next;
    }
    return count;
}

RLEListResult RLEListRemove(RLEList list, int index){
 RLEList prev = NULL;
 int count = list->numOfOccurances;
 
 if(!list){
    return RLE_LIST_NULL_ARGUMENT;
 }else if(index < 0){
    return RLE_LIST_INDEX_OUT_OF_BOUNDS;
 }
 
 while(count < index+1 || list)
 {
    prev = list;
    list = list->next;
    count += list->numOfOccurances;
 }
    if(!list){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    switch (_rCase1(list)){
    case REMOVE_NULL_ARGUMENT:
        return RLE_LIST_ERROR;
        break;
    case REMOVE_SUCSSES:
        return REMOVE_SUCSSES;
    default: 
        break;
    }

    switch(_rCase2(list, prev)){
    case REMOVE_NULL_ARGUMENT:
        return RLE_LIST_ERROR;
        break;
    case REMOVE_SUCSSES:
        return REMOVE_SUCSSES;
    default:
        break;
    }

    return RLE_LIST_ERROR;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    int count = 0;
    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    while((count != index)||(list))
    {
        list = list->next;
        count+=list->numOfOccurances;
    }
    if(!list){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    
    *result = RLE_LIST_SUCCESS;
    
    return list->c;
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
