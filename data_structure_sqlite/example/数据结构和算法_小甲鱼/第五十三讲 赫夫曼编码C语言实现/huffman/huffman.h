#pragma once
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

//The Huffman tree node definition
typedef struct _htNode {
	char symbol;
	struct _htNode *left, *right;
}htNode;

/*
	We "encapsulate" the entire tree in a structure
	because in the future we might add fields like "size"
	if we need to. This way we don't have to modify the entire
	source code.
*/
typedef struct _htTree {
	htNode *root;
}htTree;

//The Huffman table nodes (linked list implementation)
typedef struct _hlNode {
	char symbol;
	char *code;
	struct _hlNode *next;
}hlNode;

//Incapsularea listei
typedef struct _hlTable {
	hlNode *first;
	hlNode *last;
}hlTable;

htTree * buildTree(char *inputString);
hlTable * buildTable(htTree *huffmanTree);
void encode(hlTable *table, char *stringToEncode);
void decode(htTree *tree, char *stringToDecode);

#endif