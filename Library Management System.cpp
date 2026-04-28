// Written by : Arianna Almond
// Created: 2/9/26
// Purpose: a library management system that allows you to check for a specific book and check out the book

#include <iostream>
using namespace std;
#include <string>


const int MAX_BOOKS = 50;
const int MAX_MEMBERS = 50;

struct date { //represents a calendar date used by the library system
	int day;
	int month;
	int year;

};
struct book {  //represents a single book in the library’s collection
	string title;
	string author;
	int unumber; // unique id book number
	bool checkedout;
	date returnDate;

};

struct member {  //represents a person who can borrow books from the library
	string mname; // member name
	int memberID;
	int borrowedUnum[10];   // stores book unique ID only
	int borrowedCount;     // initializes books borrowed
};

int Findbookunum(book books[], int count, int searchUnum);  // looks for unique ID #, takes the parameters if book, searched for ID
bool validateMemberID(member members[], int count, int id); // validates the members unique ID number w/ their info, id number and # of books
void printBook(book data);

book makeBook() { //Creates a book using user input
	book info;
	info.checkedout = false;
	info.returnDate = { 0, 0, 0 };
	cout << "             *Welcome to Our Library System*            " << endl; // diplays info for user to input
	cout << "Please enter the book title: \n";
	cin.ignore();
	getline(cin, info.title);   // Displays title w/ spaces
	cout << "Author: \n";
	getline(cin, info.author);  // Displays author's name w/ spaces
	cout << "Unique Identifier Number: \n";
	cin >> info.unumber;   // inputs the ID Number for the book
	return info;    // returns the info based on what the user input
}
 void printBook(book data) { //Displays all information about a book
	cout << "Book: \n" << data.title << endl; //Outputs the book's data to the user (MUST output all, not just 1)
	cout<< "Author: " << data.author << endl;  // outputs the author's name that matches in the system
	cout<< "ID: " << data.unumber << endl;  // outputs the ID number of the book that matches in the system
	
	cout << "Checked Out: " << (data.checkedout ? "Yes" : "No") << endl;
	if (data.checkedout) {  // outputs info if the book is checked out
		cout << "Due Date: "
			<< data.returnDate.month << "/"
			<< data.returnDate.day << "/"
			<< data.returnDate.year << endl;
	}
 }
 int findBookByID(book catalog[], int unum, int tnum) { // function that outputs all books found that match the ID # in the library management
	 for (int i = 0; i <= tnum; i++) {  // loops to outputs uniqe ID number of the user's book in the array
		 cout << "The book for this ID number is: " << unum << endl;
		 if (catalog[i].unumber == unum) {   //output -1 if its false
			 return i;
		 }
	 }

	 return -1;
 }
 static void addBook(book data, book catalog[], int& num) { // sata=book, catalog = array, &num= saves the total number of books & passes the new total into main
	 if (num < MAX_BOOKS) {
		 catalog[num] = data; // saves the book into the correct index, tells the computer where to save the book
		 num++; // continuously adds the book to its assigned index
	 }

	 else {
		 cout << "Library is full \nNo books can be added" << endl;
	 }
 }
 void printAllBooks(book catalog[], int numBooks) { //outputs books in the catalog
	 if (numBooks == 0) {  // no books in catalog
		 cout << "No books available in ctalog" << endl;
		 return;
	 }
	 for (int i = 0; i < numBooks; i++) {
		 cout << "\n**Book " << (i + 1) << " **" << endl;
		 printBook(catalog[i]);  // loops through to print the books and calls the function
	 }
 }
 bool validateMemberID(member members[], int count, int id) {
	 for (int i = 0; i < count; i++) {
		 if (members[i].memberID == id) {
			 return true;
		 }
	 }
	 return false;
 }

void registerMember(member members[], int& count) { // registers the member if not full

	if (count >= MAX_MEMBERS) {
		cout << "Unable to add member" << endl;
		return;
	}

	member r;
	r.borrowedCount = 0;

	cout << "Enter new member ID: ";
	cin >> r.memberID;

	if (validateMemberID(members, count, r.memberID)) {
		cout << "Error: ID already exists" << endl;
		return;
	}

	cin.ignore();
	cout << "Enter name here: ";
	getline(cin, r.mname);

	members[count] = r;
	count++;

	cout << "Account Created " << endl;  // creates a new account for member
}


member* login(member members[], int count)  // points to the login information stired at member
{
	int id;
	cout << "Enter member ID: " << endl; // allows user to enter ID
	cin >> id;

	for (int i = 0; i < count; i++) // loops member's ID number
	{
		if (members[i].memberID == id)   // if member found is the same as member id then the ID will be successful
		{
			cout << "Login Successful" << endl;
			return &members[i];           // returns member info when login is successful
		}
	}

	cout << "ID is invalid" << endl;
	return nullptr;
}

int Findbookunum(book books[], int count, int searchUnum) { // locates book by unique number, loops through library to find it
	for (int i = 0; i < count; i++) {
		if (books[i].unumber == searchUnum) {
			return i;
		}
	}
	return -1;
}

void viewMemberInfo(member* m, book books[], int bookCount) {
	member* currentUser = nullptr;

	if (m == nullptr)
		return;

	cout << "\nMember Info\n";  // outputs member id and name
	cout << "ID: " << m->memberID << endl;
	cout << "Name: " << m->mname << endl;

	if (m->borrowedCount == 0)  // points to the borrowed book amount
	{
		cout << "No books borrowed\n";
		return;
	}

	for (int i = 0; i < m->borrowedCount; i++)
	{
		int index = findBookByID(books, bookCount, m->borrowedUnum[i]);
		if (index != -1)
		{
			printBook(books[index]);
		}
	}
}

void checkoutBook(member* m, book books[], int bookCount) {  // checks the amount of books checked out by member
	if (m == nullptr) {
		cout << "Error: Member not logged in" << endl;
		return;
	}

	if (m->borrowedCount >= 10) {  // outputs if the max amount of books has been reached
		cout << "Error: Maximum number of borrowed books (10) has been reached" << endl;
		return;
	}
	int id;
	cout << "Enter the book ID to check out: ";
	cin >> id;
	int index = Findbookunum(books, bookCount, id);
	if (index == -1) {
		cout << "Error: Book with ID " << id << " not found" << endl;
		return;
	}

	
	if (books[index].checkedout) {// verfifies the book is not already checked out
		cout << "Error: Book is already checked out" << endl;
		return;
	}

	date due;  // assigns due date
	cout << "Enter due date (day / month / year): ";  
	cin >> due.day >> due.month >> due.year;

	books[index].checkedout = true;  //updates book with checkedout and gives a due date
	books[index].returnDate = due;

	m->borrowedUnum[m->borrowedCount] = id;  // updates member borrowed count
	m->borrowedCount++;

	cout << "Success! " << books[index].title << " has been checked out." << endl;
}


void checkInBook(book books[], int bookCount, member* m){  // allows the use to check in book after it was checked out
	if (m == nullptr) {
	cout << "No member logged in" << endl;  // outputs if nothing is input for member log in
	return;
	}

	int bookid;  // initilaizes book id
	cout << "Enter the book ID to check in: ";  // allows the user to input the book id
	cin >> bookid;

	
	int bookIndex = Findbookunum(books, bookCount, bookid); // verifies the  book exists in library
	if (bookIndex == -1) {
		cout << "Book ID: " << bookid << " not found in catalog" << endl;  // outputs book Id
		return;
	}

	
	if (!books[bookIndex].checkedout) { // verifies if the book is currently checked out
		cout << "Book is not currently checked out" << endl;
		return;
	}

	
	int memberBookIndex = -1; // verifies the logged in member actually has this book
	for (int i = 0; i < m->borrowedCount; i++) {
		if (m->borrowedUnum[i] == bookid) {
			memberBookIndex = i;
			break;
		}
	}

		if (memberBookIndex == -1) {
		cout << "This book is not in your borrowed list" << endl;  // if indes is -1 then the book is not borrowed
		return; 

	}

	books[bookIndex].checkedout = false; // marks book as returned
	books[bookIndex].returnDate = { 0, 0, 0 };   // return date

		for (int i = memberBookIndex; i < m->borrowedCount - 1; i++) {  	// removes book ID from member's borrowed list by shifting elements left

		m->borrowedUnum[i] = m->borrowedUnum[i + 1];  // points to the borrowed unique book ID
	}
	m->borrowedCount--;  // subtracts borrowed count from member

	cout << books[bookIndex].title << "\" has been checked in" << endl;  // outputs the book that has been checked out by the user
}



int main() {

	book library[MAX_BOOKS];  // allows for mas books
	int bookCount = 0;  // # of books

	member members[MAX_MEMBERS] = {};
	int    memberCount = 0;  // amount of books for member

	// sets book objects with title, author, unique id number, checkedout status and return date
	book b1 = { "Let Them", "Mel Robbins", 2003, false, {0,0,0} };
	book b2 = { "The Lovely Bones","Alice Sebold", 2004, false, {0,0,0} };
	book b3 = { "The Skin I'm In", "Sharon G. Flake",2005, false, {0,0,0} };
	book b4 = { "Blueford High-Uintil We Meet Agin", "Anne Schraff",2006, false, {0,0,0} };
	book b5 = { "The Hunger Games",  "Suzanne Collins", 2007, false, {0,0,0} };

	addBook(b1, library, bookCount);  // adds books into the library
	addBook(b2, library, bookCount);
	addBook(b3, library, bookCount);
	addBook(b4, library, bookCount);
	addBook(b5, library, bookCount);

	cout << "\n**Welcome to the Library Management System *\n" << endl;
	member* currentUser = nullptr;  //no current user

	int userc = 0;
	while (currentUser == nullptr) {  // no current user, it will output to create an account
		cout << "Please register for an account by following the steps below\n1. Create a new account" << endl;
		cout << "2. Login" << endl;
		cout << "Choice: ";
		cin >> userc; // inputs user choice

		if (userc == 1) {
			registerMember(members, memberCount);  // creates a login with the user new unique ID number to register them
			// After registration, prompt to login
			cout << "\nPlease login with your new ID." << endl;
			currentUser = login(members, memberCount);
		}
		else if (userc == 2) {
			currentUser = login(members, memberCount); // allows the current member to log in to their account
		}
		else {
			cout << "Invalid choice. Please enter 1 or 2." << endl;
		}
	}
	viewMemberInfo(currentUser, library, bookCount); // outputs the members/users info
	int menuc = 0;
	bool found  = true;
	while (found) {  // while the member Id is valid/found this will be output
		cout << "\n** Library Menu **" << endl;
		cout << "Choose from from the following options below\n1. Check out a book" << endl;
		cout << "2. Check in a book" << endl;
		cout << "3. View borrowed books" << endl;
		cout << "4. View all library books" << endl;
		cout << "5. End session / Log out" << endl;
		cout << "Choice: ";
		cin >> menuc;

		switch (menuc) { // switch case to check book and member info, allows the user to call each function by the number in the list
		case 1:
			checkoutBook(currentUser, library, bookCount);
			
			cout << "\nUpdated library:" << endl;  // displays updated book info after checkout attempt
			printAllBooks(library, bookCount);
			break;
		case 2:
			checkInBook(library, bookCount, currentUser);
			break;
		case 3:
			viewMemberInfo(currentUser, library, bookCount);
			break;
		case 4:
			printAllBooks(library, bookCount);   // outputs all book
			break;
		case 5:
			cout << "Your session has ended " << currentUser->mname << "!" << endl;
			found = false;  // if not found then user is prompted 
			break;
		default:
			cout << "Invalid choice. Please enter 1–5 ONLY." << endl;  // outputs if users input does not match menu options
		}
	}

	return 0;
}
