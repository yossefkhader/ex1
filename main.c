#include "AsciiArtTool.h"

#define ARG_SIZE 4
#define FLAG 1
#define SOURCE 2
#define TARGET 3
#define CHUNK_SIZE 256
#define INVERTED 'i'
#define ENCODED 'e'
#define SPACE ' '
#define AT '@'

void _invert(RLEList list, FILE* output)
{
    RLEListResult result = RLE_LIST_SUCCESS;
    int i=0;
    char c;
    
    if(!list || !output){
        //error
        return;
    }

    c = RLEListGet(list, i, &result);
    
    if(result == RLE_LIST_NULL_ARGUMENT){
                //error

        return ;
    }

    while(c!=0){
        if(c == SPACE)
        {
            c = AT;
            fprintf(output,"%c",c);
        }
        else if(c == AT)
        {
            c = SPACE;
            fprintf(output,"%c",c);
        }
        else{
            fprintf(output,"%c",c);
        }
        i++;
        c = RLEListGet(list, i, &result);
    }

    return;
}


int main(int argc, char** argv)
{ 
    RLEList list;

    if(argc != ARG_SIZE)
    {
        return 0;
    }
    
    FILE* input = fopen(argv[SOURCE], "r");
    if(!input){
        return 0;
    }

    FILE* output = fopen(argv[SOURCE], "w+");
    if(!output){
        fclose(input);
        return 0;
    }

    list = asciiArtRead(input);
    if(argv[FLAG][1] == ENCODED)
    {
        asciiArtPrintEncoded(list, output);
    }
    else if(argv[FLAG][1] == INVERTED)
    {
        _invert(list ,output);
    }
    else
    {
        fclose(input);
        fclose(output);    
        return 0;
    }



    fclose(input);
    fclose(output);
    return 1;

}