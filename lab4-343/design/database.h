//
//  database.h

#ifndef database_h
#define database_h

#include "tree.h"
#include "item.h"

class GenericDatabase {
    
public:
    
    Database();
    Database(const Database&);
    ~Database();
    pure virtual int getItemCount(Item*) const;
    
private:

    Tree itemTrees;
    ItemStock itemCount[];
    
    pure virtual Item* findByID(int) const;
    pure virtual void displayAll() const;
    pure virtual int hash(Item*) const;

    pure virtual bool addItem(Item*);

};


#endif
