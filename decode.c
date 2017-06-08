# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <getopt.h>
# include "bv.h"
# include "huffman.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int main(int argc, char **argv)
{
	int sFile = 0;
	int oFile = 0;
//	bool verboseMode = false;
	
	uint32_t magicNum = 0xdeadd00d; 
	uint64_t oSize; 
	uint16_t treeSize;
	
	char c;
	
        while ((c = getopt(argc, argv, "vi:o:")) != -1) //picks between flags
	{
		switch(c)
		{
			case 'v':
			{
//				verboseMode = true;
				break;
			}
			case 'i':
			{
				sFile = open(optarg, O_RDONLY);
				break;
			}
			case 'o':
			{
			        oFile = creat(optarg, S_IRUSR| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				break;
			}
			
		}
	}

	if( oFile == 0 )
	{
		oFile = creat("oFile", S_IRUSR| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	}	

	if( sFile == 0 )
	{
		printf("You must enter an input file using -i!\n");
		return -1;	
	}

	
	uint32_t buf; 	//buffer for use in read operations
	
	read(sFile, &buf, 4); //Reads magic number into buffer 

	if( buf != magicNum )
	{
		printf("Woops! This file either is not an encoded file or is corrupt.\n");
		return -1; 
	}


	read(sFile, &oSize, 8); //Read in size of oFile
	read(sFile, &treeSize, 2); //Read in treeSize

	uint8_t savedTree[treeSize];

	read(sFile, savedTree, treeSize);

	
	
	treeNode *root = loadTree(savedTree, treeSize);

	bitV *holdVec = newVec(oSize);
	uint64_t lengthCount = 0; 
	uint8_t codebuff; 
	
	while(read(sFile, &codebuff, 1) != 0)
	{
		
		holdVec -> v[lengthCount] = codebuff; 
		lengthCount++;
		holdVec -> l = lengthCount * 8; 
	}
	

	treeNode *found; 
	int32_t current;
	uint32_t d = 0;
	uint8_t symbol;
	for( uint64_t i = 0; i < oSize; i++)
	{
		found = root;
		current = -1;
		while( current == -1 )
		{
			current = stepTree(found, &found, valBit(holdVec, d));
			d++;
			 
		} 
		symbol = current; 
		write(oFile, &symbol, sizeof(uint8_t)); 
	}
	

	delTree(root); 
	return 0;
}
