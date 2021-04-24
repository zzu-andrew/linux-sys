//
// Created by andrew on 2021/4/22.
//


#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <thread>
#include <atomic>

// a simple global linked list:
struct Node { int value; Node* next; };
std::atomic<Node*> list_head (nullptr);

void append (int val) {     // append an element to the list
    Node* oldHead = list_head.load();
    Node* newNode = new Node {val,oldHead};

    // what follows is equivalent to: list_head = newNode, but in a thread-safe way:
    while (!list_head.compare_exchange_weak(oldHead,newNode))
        newNode->next = oldHead;
}

int main ()
{
    // spawn 10 threads to fill the linked list:
    std::vector<std::thread> threads;
    threads.reserve(10);
    for (int i=0; i<10; ++i) threads.emplace_back(append,i);
    for (auto& th : threads) th.join();

    // print contents:
    for (Node* it = list_head; it!=nullptr; it=it->next)
        std::cout << ' ' << it->value;
    std::cout << '\n';

    // cleanup:
    Node* it;
    it = list_head;
    while (it) { list_head=it->next; delete it;
        it = list_head;
    }

    return 0;
}


