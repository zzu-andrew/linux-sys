#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
	//We build the tree depending on the string
	htTree *codeTree = buildTree("beep boop beer!");
	//We build the table depending on the Huffman tree
	hlTable *codeTable = buildTable(codeTree);

	//We encode using the Huffman table
	encode(codeTable,"beep boop beer!");
	//We decode using the Huffman tree
	//We can decode string that only use symbols from the initial string
	decode(codeTree,"0011111000111");
	//Output : 0011 1110 1011 0001 0010 1010 1100 1111 1000 1001
	return 0;
}