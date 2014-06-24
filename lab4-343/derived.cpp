#ifndef DERIVED
#define DERIVED

#include "base.cpp"

class Derived : public Base {

friend ostream& operator<<(ostream& out, const Derived& d) {
    d.print(out);
    return out;
}	

public:
	
	int quantity;

	Derived() : quantity(0) {}

	virtual bool operator<(Base& other) {
		Derived temp = dynamic_cast<Derived&>(other);
		return quantity < temp.quantity;
	}

	virtual bool operator==(Base& other) {
		Derived temp = dynamic_cast<Derived&>(other);
		return (quantity == temp.quantity);
	}

	virtual void setQuantity(int newQuant) {
		quantity = newQuant;
	}

	virtual void print(ostream& out) const {
		out << "\tDerived, id: " << id << endl;
	}
};

#endif