
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "SharedFunction.h"

#include <string>
#include <vector>

class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   //Constrcutor for loading a file
   LinkedList(std::string load);
   virtual ~LinkedList();
   
   int length();
   
   void addFront(Tile* tile);
   void addBack(Tile* tile);
   
   //Take methods delete the tile from the linked list
   bool takeTile(Tile* tile);
   Tile* takeFront();
   Tile* takeBack();
   //Get does not delete tile from the linked list
   Tile* getTileAt(int t);
   
   bool contains(Tile* tile);
   std::string toString();

private:

   Node* head;

};

#endif // ASSIGN2_LINKEDLIST_H
