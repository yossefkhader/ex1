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
        int i=0;
        while(buffer[i] != '\0'){
            result = RLEListAppend(list, buffer[i]);
            if(result == RLE_LIST_NULL_ARGUMENT){
                RLEListDestroy(list);
                return NULL;
            }
            i++;
        }
        
    }
    return list;
    
}


void asciiArtPrint(RLEList list, FILE *out_stream){
    RLEListResult result = RLE_LIST_SUCCESS;
    int i=0;
    char c;
    
    if(!list || !out_stream){
        return;
    }

    c = RLEListGet(list, i, &result);
    
    if(result == RLE_LIST_NULL_ARGUMENT){
        return;
    }

    while(c!=0){
        fprintf(out_stream,"%c",c);
        i++;
        c = RLEListGet(list, i, &result);
    }

    return;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    char* str;
    RLEListResult result;

    if(!list || !out_stream){
        return RLE_LIST_NULL_ARGUMENT;
    }

    str = RLEListExportToString(list, &result);
    
    if(!str){
        return result;
    }
    fprintf(out_stream,"%s", str);
    free(str);
    return RLE_LIST_SUCCESS;
}