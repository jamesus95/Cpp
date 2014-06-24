//
//  transaction.h

#ifndef transaction_h
#define transaction_h

class transaction {
    
public:
    
    
    
private:

		char instructionID;     // B, R, H or S (valid)
		int userID;             // Ex. 1234 (4 digits)
		char mediaType;         // D (DVD)
		char movieCategory;     // F, C, D (valid)
		string mediaDetails;    // C month(XX), year(XXXX), director(firstName lastName)
                            // F movieTittle, year(XXXX)
                            // D director(firstName lastName), movieTittle,
    
};

#endif
