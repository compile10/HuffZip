# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <getopt.h>
# include "intstack.h"
# include "huffman.h"
# include "queue.h"
# include "code.h"
# include "bv.h"

int main(int argc, char **argv)
{

    int argument,input, leaves = 0, output;  // buff is the number of what the read input is. Argument is used for getopt. Leaves is the number treenodes there are.
    uint64_t bytesRead, bitsRead, buff, byteNumber = 0, bitNumber = 0; // bitNumber is the number of bits in the original file.
    uint16_t leaveRep; // leaveRep holds the number of bytes of the tree.
    char *file; // Holds the file name that is given by the -i argument.
    uint64_t histogram[256]; // The array that holds the number of each character exists in the array.
    bool verb = false; // Holds to see if verbose is true.
    struct stat fileSize;
    code c, table[256]; // Holds the code inside a variable and holds that also in an array.
    bitV *bitVector; // Bit Vector that will hold all the codes to be printed to the file.
    item newArrayNode; // Holds the item of the newArrayNode.
    item root; // Holds the root treeNode.
    queue *que = newQueue(256); // Holds the queue for the whole file.
    char buffer[1000]; // Char Buffer for the file.
    

    c = newCode();
    bool outputFile = false; // Creates a newCode for the variable C.


    for(int d = 0; d <= 255; d++)
    {
	histogram[d] = 0; // Makes all numbers in the histogram to 0.
    }
    while((argument = getopt(argc,argv,"i:vo:")) != -1) // Argument for input file and output file.
    {
        switch(argument)
        {
            case 'i': // i is the file that will be compressed by -i
            {
                if((input = open(optarg, O_RDONLY)) < 0)
                {
                    close(input);
                    return -1;
                }
                file = optarg;
                break;
            }
	    
	    case 'o': // o is the file that will write the compressed text into the file.
	    {
		output = creat(optarg, S_IRUSR| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		outputFile = true;
	    	break;
	    }
            case 'v': // v is the verbose arguement.
            {
                verb = true;
                break;
            }
            default:
            {
                break;
            }
        }
    }



    ++histogram[0];
    ++histogram[255]; // Adds one to the 0th and 255th index of the histogram.

    if(input != -1) // Checks if a file exists, before reading.
    {
       while((buff = read(input, buffer, 1000)) != 0)  //adds 1000 bytes at at time into histogram 
       {
          for(uint64_t index = 0; index < buff; index++)
          {
              ++histogram[(int)buffer[index]];
              ++byteNumber;
          }
       }
       close(input); 
   }

    for(int in = 0; in <= 255; in++)  //creates treenode for each char in histogram with count greater than 0
    {
        if( (histogram[in] > 0) && (!(fullQ(que))) )
       	{
            newArrayNode = newNode(in, true, histogram[in]);
            enqueue(que, newArrayNode); // Adds that arrayNode to the queue.
	    ++leaves;
        }
    }



    item first, second; // Labels the first two item variables.
    bool firstBool, secondBool; // Then labels the next two boolean variables.
    while(emptyQ(que) == false) // Keeps going until the queue until the itself if empty.
    {
        firstBool = dequeue(que, &first); // dequeues first and returns a bool if the queue is empty.
        secondBool = dequeue(que, &second); // dequeues first and returns a bool if the queue is empty.
	if(firstBool && secondBool) // If the both dequeues are true, then the first and second items are combined.
        {
	    root = join(first, second); // Combines with first and second.
	    enqueue(que, root); // Then puts that combination back into the queue.
            
	}
    }
    
 
    buildCode(root, c, table); // Builds code table from the tree 


    
    if(!(outputFile)) // Checks if the outputFile has already been specified.
    {
    	output = creat("compressed.bzip", S_IRUSR| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // If not, creates a oFile.txt for the compressed file.
    }


    uint32_t magicNumber = 0xdeadd00d;
    write(output, &magicNumber, sizeof(magicNumber)); // Writes the magic number to the file.
   
    input = open(file, O_RDONLY);	
    fstat(input, &fileSize);		
    byteNumber = (uint64_t) fileSize.st_size; 
    close(input);
    write(output, &byteNumber, sizeof(byteNumber)); // Writes the byteSize of the file

    leaveRep = (leaves * 3) - 1;
    write(output, &leaveRep, sizeof(leaveRep)); // Write the treeSize to the file.
	
    dumpTree(root, output); // Writes the tree to the file.



    input = open(file, O_RDONLY);
    bitVector = newVec(1000);

    while((buff = read(input, buffer, 1000)) != 0)  // Reads through each character and checks what the code is in the table and adds it to the bitVector.
    {
	bytesRead = 0;
	bitsRead = 0;
        for(uint64_t index = 0; index < buff; index++)
        {
	    int asciiNum = (int) buffer[index];
	    appendCode(bitVector, &bitsRead, &table[asciiNum]);
	    ++bitNumber;
	}
	bitsRead++; 
	kif( bitsRead  % 8 != 0 )
        {
                bytesRead = (bitsRead / 8) + 1;
        }
        else
        {
                bytesRead = bitsRead/8;
        }

	for(uint64_t y = 0; y < bytesRead; y++) // Writes all the bytes to the from the bitVector to the file.
        {
        	uint8_t x = (bitVector->v[y]);
        	write(output, &x, sizeof(uint8_t));
        }
    }


    if(verb == true) //prints verbose mode if flag is called
    {
	printf("Original File is %lu, leaves %d (%d) encoding %lu (%lf)", byteNumber, leaves, leaveRep, bitNumber, (double)(((double)bitNumber)/(((double)byteNumber)*8)));
    }


    close(input);
    close(output);
    delVec(bitVector);
    delTree(root);
    delQueue(que);
    return 0;
}
