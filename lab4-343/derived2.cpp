#ifndef DERIVED2
#define DERIVED2

#include "base.cpp"

class Derived2 : public Base {

friend ostream& operator<<(ostream& out, const Derived2& d) {
    d.print(out);
    return out;
}   

public:
    
    int quantity;

    Derived2() : quantity(0) {}

    virtual bool operator<(Base& other) {
        Derived2 temp = dynamic_cast<Derived2&>(other);
        return quantity < temp.quantity;
    }

    virtual bool operator==(Base& other) {
        Derived2 temp = dynamic_cast<Derived2&>(other);
        return (quantity == temp.quantity);
    }

    virtual void setQuantity(int newQuant) {
        quantity = newQuant;
    }

    virtual void print(ostream& out) const {
        out << "\tDerived2, id: " << id << endl;
    }

    virtual void sayHello() const {
        cout << "Hello, Derived2." << endl;
    }
};

#endif