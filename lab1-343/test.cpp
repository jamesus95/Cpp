#include "poly.h"
#include <iostream>

using namespace std;




int main() {

	Poly count[8];

	cout << "Constructors" << endl;
	count[0] = Poly();
	count[1] = Poly(1);
	count[2] = Poly(0);
	count[3] = Poly(-1);
	count[4] = Poly(0, 1);
	count[5] = Poly(1, 1);
	count[6] = Poly(-1, 1);
	count[7] = Poly(1, -1);

	for (int i = 0; i < 8; i++) {
		cout << count[i] << endl;
	}

	cout << "add" << endl;
	count[0].setCoeff(2,2);
	count[0].setCoeff(4,4);
	count[0].setCoeff(3,3);
	count[2].setCoeff(2,2);
	count[2].setCoeff(4,4);
	count[2].setCoeff(3,3);

	cout << count[0] << endl;
	cout << count[2] << endl;

	Poly p = count[0] + count[2];

	cout << p << endl;

	p = p - count[0] - count[2];

	cout << p << endl;

	p = p - count[0];

	cout << p << endl;

	p.setCoeff(-1,-1);
	cout << p.getCoeff(-2) << endl;

	return 0;
}