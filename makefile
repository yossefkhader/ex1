CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = AsciiArtTool.exe
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors $(DEBUG_FLAG)
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
main.o : main.c AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
AsciiArtTool.o : AsciiArtTool.c AsciiArtTool.h RLEList.h RLEList.o
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $@
clean:
	rm -f $(OBJS) $(EXEC)
