1 - DESCRIPTION OF PROJECT CURRENT STATE
	6/6/2014 8:30pm
	Currently the program reads in the test data, and processes the transactions.  There are no errors when running on the provided test data.  However, the program leaks a small amount of memory (discussed more in part 5).

2 - LIST OF HASH TABLES
	A - ITEM LEVEL HASH
		- NOTE: Currently only Movie inherits from Item, but if out store contained more types of items, they would go in this hash as well.

		- DESCRIPTION
		Each Item has a type which is a character.  In Inventory the characters are hashed and the Item is placed into the appropriate container (ItemContainer and children classes) inside the Inventory.  Inventory contains an array of these containers that is 26 long (one for each letter).

		- HASH FUNCTION/VALUES
		(int)(type - 'A') % 26
		Movie Items type = 'M'

		- SHORT COMINGS
		Our HashFunction is limited to 26 different types of items but could be altered (breaking open/close) to include more.
		Modulus takes care of lower case letters, however, other invalid characters are not supported, and proper input in expected.

	B - MOVIE LEVEL HASH
		- DESCRIPTION
		Each Movie has a genre which is a character.  In MovieContainer the characters are hashed and the Movie is placed into the appropriate container (BinTree from Lab3) inside MovieContainer.  MovieContainer contains an array of these containers that is 26 long (one for each letter).

		- HASH FUNCTION/VALUES
		(int)(type - 'A') % 26
		Classic Movies genre = 'C'
		Comedy Movies genre = 'F'
		Drama Movies genre = 'D'

		- SHORT COMINGS
		(See 2.A.SHORTCOMINGS)

3 - DESCRIPTION OF THE MOVIE DATA READ PROCESS
	A - OVERVIEW
		i 	- get the movie type letter from the input
		ii 	- get the appropriate movie from the MovieFactory
		iii	- call the movies setData() function
		iv 	- setData() gets the information it needs from the input
		v 	- puts the movie into the Inventory

	B - BAD MOVIE DATA
		- MOVIE CHARACTER
		If the movie character is not a supported character the MovieFactory will return NULL, and the rest of that movies data will be gotten from the input and thrown away.

		- MOVIE DATA
		It is expected that all input is formatted correctly if a proper movie character is read.
			Classic = C <Director>, <Title>, <Actor> <Month> <Year>
			Comedy 	= F <Director>, <Title>, <Year>
			Drama	= D <Director>, <Title>, <Year>
		If the movie data is not in the proper format behavior is undefined.

	C - SETDATA FUNCTIONS
		- MOVIE SETDATA
		The Movie class contains all the functions for gettings data that are shared between the classes.
			Function 		Expected Format Of Input
			getDirector()	<Director>,
			getTitle()		<Title>,
			getYear()		<Year>

		- CLASSIC SETDATA
		The Classic class has extra functions for getting data because it has more fields to fill.
			getActor()		<ActorFirstName> <ActorLastName>
			getMonth()		<Month>

		- PROCESS
		Each setData helper function takes in the input that the movies are contained in, and extracts their data in their respective expected formats.  The setData() function for each type of movie calls the helper functions in individual pre-defined orders.
			(See 3.B.MOVIE DATA)

4 - DESCRIPTION OF THE TRANSACTION DATA READ PROCESS
	A - OVERVIEW
		i 	- gets the transaction type from the input 
		ii 	- gets the appropriate transaction from the TransactionFacorty
		iii - calls the transactions setData() function
		iv 	- setData() gets the information it needs from the input
		v 	- puts the transaction into the transaction queue

		NOTE: Different transaction require different data.  Not all transactions will use all types of data disgussed in section 4.  If a data is unused the transaction will not be discarded if the data is NULL.

	B - BAD TRANSACTION
		- TRANSACTION CHARACTER
		If the transaction character is not a supported character the TransactionFactory will return NULL.  The transaction input is peeked at to check whether or not there is more information associated with that transaction, and is thrown away with accordingly.

		- CUSTOMER ID
		If the Customer ID for the transaction is invalid, the transaction will contain a NULL for the customer field.  If the transactions customer field is NULL the transaction will be discarded as invalid. 
		(See 4.A.NOTE)

		- MOVIE
		If the Movie for the transaction is invalid, the transaction will contain a NULL for the movie field.  Movies are invalid if they are not a supported genre, or if they are not in the store's inventory.  If the transaction movie field is NULL the transaction will be discarded as invalid. 
		(See 4.A.NOTE)

	C - PARTIAL MOVIE TRANSACTION DATA
		Movies created from the transaction input are only for comparison.  They only contain the required data to locate the movie in the store's inventory.
			Classic = <Month> <Year> <Actor>
			Comedy 	= <Title>, <Year>
			Drama	= <Director>, <Title>,
		Partial movie data is expected in these formats, and behavior is undefined if they are not formatted correctly.

	D - SETDATA FUNCTIONS
		- BORROW / RETURN SETDATA
		Borrow and Return each contain functions to get the Customer that is doing the borrow or return, and the Item that they are borrowing or returning.
			Function 			Expected Data
			setCustomer()		<Customer ID>
			setItem()			<Partial Movie Data>

		- DISPLAYUSER
		DisplayUser contains a function to get the Customer who's transaction history is being displayed.
			setCustomer()		<Customer ID>

		- DISPLAYINVENTORY
		DisplayInventory does not require any data.

5 - BUGS / WORKAROUNDS / SHAME
	A - C-STR COMPARISON (Workaround)
	When comparing std::string references equal strings were returning false when compared with the == operator.  Using the strcmp() function and converting the strings to type char[] solved this problem.

	B - LINEAR HASH vs. REAL HASH (Shame)
	For simplicity the hash function for differentiating movie genres and item types are both linear hashes.  This is very constrictive in the sense that, if the store grew very large and started carring many types of items or movies, it would not be able to contain them all without alteration.
	(breaks open/close)
	Additionally, the hash function does not handle collision.  Collision is handled by the user.  No two items or movies can have the same item or genre character.
	Ex. Classic and Comedy both start with 'C', but their codes are 'C' and 'F' respectively.

	C - IMPROPER TEXT FORMATTING (Shame)
	Currently incorrect movie formatting is not supported.  If a user puts in an incorrect movie format in the movie file, or an incorrect partial movie in the commands file, the program will crash.

	D - BUGS
	Our program works as expected with the given test files provided.  We did not have time to test any further extraneous cases.

6 - PROUD
	A - FOLLOWED DESIGN
	In our implementation we followed our design (that we worked on separate from our design groups) exactly with only minor changes.

	B - OPEN / CLOSE
	Our design does a good job of following the open closed principle.  Our inheritance allows for you to add new movies, items, or transactions without editing those files, or any files that use them.  However, it is not implemented perfectly by any means, and can be improved upon (but it works).