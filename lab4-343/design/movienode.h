//
//  movienode.h

#ifndef movienode_h
#define movienode_h

class MovieNode{
    
    
public:
    
    ostream& operator<<(ostream&, NodeData&)
    
private:
    
    Movie* myMovie;

	NodeData* dataMovie;
    MovieNode *left;
    MovieNode *right;

	MovieNode *root;
    
};



#endif
