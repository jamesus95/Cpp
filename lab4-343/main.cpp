#include "base.cpp"
#include "derived.cpp"
#include "container.cpp"
#include <cassert>
#include <vector>
#include <string>

using namespace std;

int main() {

	string A = "James";
	const string B = "James";

	assert(A == B);

	if(A == B) {cout << "A == B";}

	// // ids and quantities are all 0
	// Base* B = new Base();
	// Base* C = new Base();
	// Derived* D = new Derived();
	// Derived* E = new Derived();

	// // default case
	// assert(!(*B < *C) && !(*C < *B));
	// assert(!(*D < *E) && !(*E < *D));

	// // case 1
	// B->setID(13); C->setID(42);

	// D->setID(55); E->setID(5);
	// // D->setQuantity(2); E->setQuantity(98);

	// assert(*B < *C);
	// // assert(*D < *E);
	// cout << "B->id = " << B->id << endl;
	// cout << "C->id = " << C->id << endl;
	// // cout << "base(D)->id = " << dynamic_cast<Base*>(D)->id << endl;
	// // cout << "base(E)->id = " << dynamic_cast<Base*>(E)->id << endl;
	// cout << "D->id = " << D->id << endl;
	// cout << "E->id = " << E->id << endl;

	// cout << "\n================== testing container operator<<" << endl;
	// Container con;
	// con.insert(B);
	// con.insert(C);
	// cout << "Container = " << con << endl;

	// con.insert(D);
	// con.insert(E);
	// cout << "Container = " << con << endl;


	// cout << "Finished." << endl;

	// vector<Base*> v;
	// v.push_back(new Base());
	// cout << *v[0] << endl;


	// return 0;


}