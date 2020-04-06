#pragma once
#ifndef _PQUEUE_H
#define _PQUEUE_H

#include "huffman.h"

//We modify the data type to hold pointers to Huffman tree nodes
#define TYPE htNode *

#define MAX_SZ 256

typedef struct _pQueueNode {
	TYPE val;
	unsigned int priority;
	struct _pQueueNode *next;
}pQueueNode;

typedef struct _pQueue {
	unsigned int size;
	pQueueNode *first;
}pQueue;

void initPQueue(pQueue **queue);
void addPQueue(pQueue **queue, TYPE val, unsigned int priority);
TYPE getPQueue(pQueue **queue);

#endif