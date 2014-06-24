//
//  inputmanager.h

#ifndef inputmanager_h
#define inputmanager_h

#include <iostream>
#include <string>

using namespace std;

class InputManager {
    
public:

    struct Transaction {

        char instructionID;     // B, R, H or S (valid)
        int userID;             // Ex. 1234 (4 digits)
        char mediaType;         // D (DVD)
        char movieCategory;     // F, C, D (valid)
        string mediaDetails;    // C month(XX), year(XXXX),
                                // director(firstName lastName)
                                // F movieTittle, year(XXXX)
    };

    // may split into different managers
    // using inheritance for open-closed

    void parseTransactions(const istream&);
	void initializeUser(const istream&);
    void initializeMovie(const istream&);

	string getNextMovie();
	bool hasNextMovie();

    string getNextUser();
    bool hasNextUser();

    Transaction getNextTransaction();
    bool hasNextTransaction();

private:

	string[] movieDetails;
    int movieCount;

    string[] userDetails;
    int userCount;

	Transaction[] transactions;
    int transactionCount;

};

#endif
