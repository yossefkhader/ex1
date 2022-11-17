#include "RLEList.h"

struct RLEList_t{
    char c;
    int numOfOccurances;
    RLEList next;
};

typedef enum{
    REMOVE_NULL_ARGUMENT,
    REMOVE_SUCSSES,
    REMOVE_NOT_SUITABLE
}RemoveResult;

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



//implement the functions here
int RLEListSize(RLEList list)
{
    int count = 0;
    while(list != NULL)
    {    
        count += list->numOfOccurances;
        list = list->next;
    }
    // if(count == 0)
    // return -1;
    // else
    return count;
}

void  RLEListAppend(RLEList list, char value) 
{
    while(list->next != NULL)
    {
      list = list->next;
    }
    if(list->c == value)
     list->numOfOccurances = list->numOfOccurances + 1;
    else 
     {
        RLEList ptr = malloc(sizeof(*ptr));
        if(!ptr)
        {
            return NULL;
        }
        ptr->c = value;
        list->next = ptr;
        list = list->next;
        list->next = NULL;
     }
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
 int count = 0;
 while(count != index)
 {
    list = list->next;
 }
 if(list->c!=NULL)
 {
   *result = RLE_LIST_SUCCESS;
   return list->c;
 }
 else 
 {
//   *result = RLE_LIST_NULL_ARGUMENT;
  return NULL;
 }
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
    }

    switch(_rCase2(list, prev)){
    case REMOVE_NULL_ARGUMENT:
        return RLE_LIST_ERROR;
        break;
    case REMOVE_SUCSSES:
        return REMOVE_SUCSSES;
    }

    return RLE_LIST_ERROR;
}