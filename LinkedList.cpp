
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
}

LinkedList::~LinkedList() {
   Node* node = head;
   Node* prevNode = nullptr;

   while (node != nullptr){
      prevNode = node;
      node = node->next;
      delete prevNode;
      prevNode = nullptr;
   }
}

LinkedList::LinkedList(LinkedList& other){
   Node* node = other.head;

   while (node != nullptr){
      Tile* tile = new Tile(*(node->tile));
      addBack(tile);
      node = node->next;
   }
}

LinkedList::LinkedList(std::string load) {
   if(load != ""){
      std::vector<std::string> list = SharedFunction::split(load, ',');
      std::string tileString = list.at(0);
      int shape = tileString.back() - '0';
      char colour = tileString.front();
      Tile* tile = new Tile(colour, shape);

      head = new Node(tile, nullptr);
      Node* prevNode = head;
      for(unsigned int i = 1; i<list.size() && list.at(i) != "\n"; i++){
         std::string tileString = list.at(i);
         int shape = tileString.back() - '0';
         char colour = tileString.front();
         Tile* tile = new Tile(colour, shape);
         prevNode->next = new Node(tile, nullptr);
         prevNode = prevNode->next;
      }
   }else{
      head = nullptr;
   }

}

int LinkedList::length(){
   Node* node = head;
   int count = 0;

   while(node != nullptr){
      node = node->next;
      count++;
   }

   return count;
}

void LinkedList::addFront(Tile* tile){
   if(head == nullptr){
      head = new Node(tile, nullptr);
   }else{
      Node* nextNode = head;
      head = new Node(tile, nextNode);
   }
}

void LinkedList::addBack(Tile* tile){
   if(head == nullptr){
      head = new Node(tile, nullptr);
   }else{
      Node* node = head;
      Node* nodePrev = nullptr;
      while(node != nullptr){
         nodePrev = node;
         node = node->next;
         if(node == nullptr){
            nodePrev->next = new Node(tile, nullptr);
         }
      }
   }
}

bool LinkedList::takeTile(Tile* tile){
   bool removed = false;
   Node* node = head;
   Node* prevNode = nullptr;

   while(node != nullptr && !removed) {
      if(node->tile->equals(tile)) {
         if(prevNode == nullptr){
            head = node->next;
         }else {
            prevNode->next = node->next;
         }
         delete node;
         node = nullptr;
         removed = true;
      }else {
         prevNode = node;
         node = node->next;
      }
   }

   return removed;
}

Tile* LinkedList::takeFront(){
   Tile* returnTile = nullptr;

   if(head != nullptr) {
      Node* nextNode = head->next;
      returnTile = new Tile(*head->tile);
      delete head;
      head = nextNode;
   }

   return returnTile;
}

Tile* LinkedList::takeBack(){
   Tile* returnTile = nullptr;

   if(head != nullptr){
      Node* node = head;
      Node* prevNode = nullptr;
      while(node->next != nullptr){
         prevNode = node;
         node = node->next;
      }
      if(prevNode == nullptr){
         head = nullptr;
      }else{
         prevNode->next = nullptr;
      }
      returnTile = new Tile(*node->tile);
      delete node;
   }

   return returnTile;
}

Tile* LinkedList::getTileAt(int t){
   Node* returnTile = head;

   for(int j = 0; j < t;j++){
      returnTile = returnTile->next;
   }

   return returnTile->tile;
}

std::string LinkedList::toString(){
   std::string linkedListString = "";
   Node* node = head;

   while(node != nullptr){
      linkedListString += node->tile->toString();
      if (node->next != nullptr){
         linkedListString += ",";
      }
      node = node->next;
   }

   return linkedListString;
}

bool LinkedList::contains(Tile* tile){
   bool found = false;
   Node* node = head;

   while(node != nullptr && !found){
      if(node->tile->equals(tile)){
         found = true;
      }
      node = node->next;
   }

   return found;
}
