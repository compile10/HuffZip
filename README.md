# HuffZip


This program can compress any file using huffman encoding. 

Type "make" or "make all" on linux to compile the program.  
Type "make clean" to remove .o files and the program.  


## Commands 

-i input file  
-o output file  
-v verbose mode  
## Files

List of files | Description
------------- | -----------
code.h |           Provided by Prof. Darrell Long, stack library. 
decode.c |         The main function for decoding and tge loadTree function.
decode.h  |        Declaration for decode.c
encode.c  |        The main function for encoding and dumpTree.
encode.h   |       declaration for encode.c
huffman.c  |       For building the treeNode, and other treeNode functions.
huffman.h  |       The struct for treeNode is located here, and declaration for treenode functions.
Makefile   |       Makefile for compiling the project (see instructions above). 
queue.c    |       The priority functions are located here.
queue.h    |       Declaration for priority queue functions.
stack.c    |       The basic stack function
stack.h    |       Declaration for stack.c, provided by Prof. Darrell Long

