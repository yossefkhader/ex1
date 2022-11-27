#include "AsciiArtTool.h"

#define ARG_SIZE 4
#define FLAG 1
#define SOURCE 2
#define TARGET 3
#define CHUNK_SIZE 256
#define MINUS '-'
#define INVERTED 'i'
#define ENCODED 'e'
#define SPACE ' '
#define AT '@'

void error (char* message, char* filename)
{
    fprintf(stderr, "%s %s\n" ,message ,filename ? filename : "");

}

char invertChar(char c){
    if(c == SPACE){
        return AT;
    }else if(c == AT){
        return SPACE;
    }
    return c;
}


int main(int argc, char** argv)
{ 
    RLEList list;
    RLEListResult result;

    if(argc != ARG_SIZE)
    {
        error("Usage: AsciiArtTool <flags> <source> <target>", NULL);
        return 0;
    }
    
    FILE* input = fopen(argv[SOURCE], "r");
    if(!input){
        error("Error: cannot open", argv[SOURCE]);
        return 0;
    }

    FILE* output = fopen(argv[TARGET], "w");
    if(!output){
        error("Error: cannot open", argv[TARGET]);
        fclose(input);
        return 0;
    }

    list = asciiArtRead(input);
    if(!list)
    {
        error("Failed at creating RLEList", NULL);
        return 0;

    }
    if(argv[FLAG][0] == MINUS && argv[FLAG][1] == ENCODED)
    {
        asciiArtPrintEncoded(list, output);
    }
    else if(argv[FLAG][0] == MINUS && argv[FLAG][1] == INVERTED)
    {
        result =  RLEListMap(list, invertChar);
        if(result != RLE_LIST_SUCCESS)
        {
            error("Failed at inverting" , NULL);
            RLEListDestroy(list);
            fclose(input);
            fclose(output);
        }
        asciiArtPrint(list, output);

    }
    else
    {
        error("Error: wrong flag" , argv[FLAG]);
        RLEListDestroy(list);
        fclose(input);
        fclose(output);    
        
        return 0;
    }


    RLEListDestroy(list);
    fclose(input);
    fclose(output);
    return 1;

}