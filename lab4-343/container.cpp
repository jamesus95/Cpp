#include "base.cpp"
#include "derived.cpp"

class Container {

friend ostream& operator<<(ostream& out, const Container& con) {
    for (int i = 0; i < con.size; ++i) {
        out << *(con.collection[i]) << ",\t";    
    }
    return out;
}

public:

    Base* collection[10];
    int size;

    Container() {
        size = 0;
    }
    ~Container() {
        size = 0;
    }

    void insert(Base* b) {
        if(size < 10) {
            collection[size] = b;
            size++;
        }
    }

    // not used in this example
    Base* getByID(int id) {
        for (int i = 0; i < size; ++i) {
            if(collection[i]->id == id)
                return collection[i];
        }
    }

};