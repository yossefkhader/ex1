#include "AsciiArtTool.h"

#define CHUNK_SIZE 256

RLEList asciiArtRead(FILE* in_stream){
    RLEList list = RLEListCreate();
    RLEListResult result;
    char buffer[CHUNK_SIZE];
    
    if(!list || !in_stream){
        RLEListDestroy(list);
        return NULL;
    }

    while(fgets(buffer, CHUNK_SIZE, in_stream)!=NULL){
        
        for (int i = 0; i<CHUNK_SIZE-1; i++)
        {
            result = RLEListAppend(list, buffer[i]);
            if(result == RLE_LIST_NULL_ARGUMENT){
                RLEListDestroy(list);
                return NULL;
            }
        }
    }

    return list;
    
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    RLEListResult result = RLE_LIST_SUCCESS;
    int i=0;
    char c;
    
    if(!list || !out_stream){
        return RLE_LIST_NULL_ARGUMENT;
    }

    c = RLEListGet(list, i, &result);
    
    if(result == RLE_LIST_NULL_ARGUMENT){
        return result;
    }else if(result == RLE_LIST_INDEX_OUT_OF_BOUNDS){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(c!=0){
        fprintf(out_stream,"%c",c);
        i++;
        c = RLEListGet(list, i, &result);
    }

    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    char* str;
    int len;
    RLEListResult result;

    if(!list || !out_stream){
        return RLE_LIST_NULL_ARGUMENT;
    }

    str = RLEListExportToString(list, &result);
    
    if(!str){
        return result;
    }

    for (int i = 0; i < strlen(str); i++){
        fprintf(out_stream,"%c", str[i]);
    }
    
    free(str);   
    return RLE_LIST_SUCCESS;
}