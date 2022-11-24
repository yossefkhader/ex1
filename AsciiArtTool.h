#ifndef __AsciiArtTool_H__
#define __AsciiArtTool_H__

#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief 
/// @param in_stream 
/// @return 
RLEList asciiArtRead(FILE* in_stream);

/// @brief 
/// @param list 
/// @param out_stream 
/// @return 
void asciiArtPrint(RLEList list, FILE *out_stream);

/// @brief 
/// @param list 
/// @param out_stream 
/// @return 
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif