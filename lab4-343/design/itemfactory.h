
#ifndef itemfactory_h
#define itemfactory_h

#define ITEM_TYPES 1

class ItemFactory {
    
public:

    pure virtual Item* createItem(char itemCode) const;
    
private:
    
    Item* originalItems[ITEM_TYPES];  // instances of each movie
    int hash(char ch) const;          // maps movie code to correct constructor
    
};

#endif
