//
//  item.h

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item {
    
public:
    
    pure virtual Item* createEmptyMovie() const;
    pure virtual bool setData(string);   // data string comes from outside
    
protected:
    
    int id;

};

#endif
