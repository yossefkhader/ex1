#include "RLEList.h"
#include <stdlib.h>

#define INITIAL_VALUE '\0'
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

RLEList _nodeCreate(){
    RLEList new = malloc(sizeof(*new));
    if(!new){
        free(new);
        return NULL;
    }
    return new;
}

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



/// @brief the func checks if the list is suitable for the second case of removal
/// @param node RLEList pointer for the node that we need to remove 
/// @param prev RLEList pointer for the previous node of that we need to remove
/// @return REMOVE_NULL_ARGUMENT if node 
RemoveResult _rCase2(RLEList node, RLEList prev){
    RLEList tmp;

    if(!node){
        return REMOVE_NULL_ARGUMENT;
    }else if(prev->c == INITIAL_VALUE && node->next == NULL){
        RLEListDestroy(node);
        return REMOVE_SUCSSES;
    }else if(prev->c == INITIAL_VALUE){
        tmp = node;
        node = node->next;
        prev->next = node;
        free(tmp);
        return REMOVE_SUCSSES;
    }else if(node->next == NULL){
        prev->next=NULL;
        free(node);
        return REMOVE_SUCSSES;
    }

    tmp = node;
    node = node->next;
    free(tmp);
    
    if(prev->c == node->c){
        prev->numOfOccurances += node->numOfOccurances;
        prev->next = node->next;
        free(node);
        return REMOVE_SUCSSES;
    }else{
        prev->next = node;
    }
    
    return REMOVE_SUCSSES;
}

int _nodeCounter(RLEList list){
    int counter = 0;
    if(list->c == INITIAL_VALUE){
        return 0;
    }
    while(list){
        if(list->c == INITIAL_VALUE){
            list = list->next;
            continue;
        }
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

/// @brief this function counts the needed cells for exporting the list to a string
/// @param list RLE list that we need to calculate 
/// @return 0 if the the entered list Is NULL or the list is just the dummy node, else it will return the needed number of cells
int _neededCells(RLEList list){
    int digitCounter = 0, nodeNumber = _nodeCounter(list);
    if(!list || list->c == INITIAL_VALUE){
        return 0;
    }
    nodeNumber *= ADD_NEW_LINE;
    while(list){
        if(list->c == INITIAL_VALUE){
            list= list->next;
            continue;
        }
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
    RLEList new = _nodeCreate();
    if(!new){
        free(new);
        return NULL;
    }    
    new->c = INITIAL_VALUE;
    new->numOfOccurances = 0;
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
    RLEList ptr;
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list->next != NULL){
      list = list->next;
    }

    if(list->c == value){
        list->numOfOccurances++;
        return RLE_LIST_SUCCESS;
    }

    ptr = _nodeCreate();
    if(!ptr)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    ptr->c = value;
    ptr->next = NULL;
    ptr->numOfOccurances =1;
    list->next = ptr;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    int count = 0;
    if(!list){
        return -1;
    }else if(list->c == INITIAL_VALUE && list->next == NULL){
        return 0;
    }
    while(list!= NULL)
    {    
        count += list->numOfOccurances;
        list = list->next;
    }
    return count;
}

RLEListResult RLEListRemove(RLEList list, int index){
    RLEList prev = NULL;
    int count;

    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }else if(index < 0){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }else if(list->c == INITIAL_VALUE && list->next == NULL){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    prev = list;
    list = list->next;
    count = list->numOfOccurances;

    while(count < index+1 && list){
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
            return RLE_LIST_SUCCESS;
        default: 
            break;
    }

    switch(_rCase2(list, prev)){
        case REMOVE_NULL_ARGUMENT:
            return RLE_LIST_ERROR;
            break;
        case REMOVE_SUCSSES:
            return RLE_LIST_SUCCESS;
        default:
            break;
    }

    return RLE_LIST_ERROR;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    int count = 0;
    if(!list){
        if(!result){
            return 0;
        }
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }else if(list->c ==INITIAL_VALUE && list->next==NULL){
        if(!result){
            return 0;
        }
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    while(count < index+1 && list){
        list = list->next;
        count += list->numOfOccurances;
    }
    if(!list){
        if(!result){
            return 0;
        }
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    
    if(!result){
        return list->c;
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
    }else if(list->c == INITIAL_VALUE && list->next == NULL){
        *result = RLE_LIST_ERROR;
        return NULL;
    }

    str = malloc(sizeof(char) * _neededCells(list));
    int digits;
    if(!str){
        free(str);
        *result = RLE_LIST_ERROR;
        return NULL;
    }

    list = list->next;
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
