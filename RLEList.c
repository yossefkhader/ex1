#include "RLEList.h"

struct RLEList_t{
    char c;
    int numOfOccurances;
    RLEList next;
};

//yossef: 8,7,2,1
//aaseel: 5,4,3,6
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

void RLEListRemove(RLEList list, int index)
{
 int count = 0;
 while(count != index-1)
 {
    list = list->next;
 }
 RLEList before = list;
 list = list->next;
 RLEList after = list->next;
  if(index==0)
  {
    if(list->numOfOccurances == 1)
    {
    _freeNode(list);
    before->next = after;  
    }
       else{
           list->numOfOccurances = list->numOfOccurances-1;
           }
  }
  else if(list->next==NULL)
  {
    if(list->numOfOccurances == 1)
    {
      _freeNode(list);
    before->next = NULL;
    }
    else{
     list->numOfOccurances = list->numOfOccurances-1;
    }
  }
  else {
     if(list->numOfOccurances == 1)
    {
    _freeNode(list);
    if(before->c == after->c)
    {
      before->numOfOccurances += after->numOfOccurances; 
      before->next = after->next;
    }
    else
    before->next = after;  
    }
    else{
     list->numOfOccurances = list->numOfOccurances-1;

  }  
}