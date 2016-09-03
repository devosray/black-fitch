#include <iostream>
#include <sstream>
#include <cassert>

#include "prac3Tests.h"

#include "book.h"
#include "Library.h"

using namespace std;

void addBooksToLibrary(Book **books, Library &lib, int numBooks)
{
    for (int i = 0; i < numBooks; i++) {
        //cout << books[i]->getTitle() << endl;

    	lib += books[i];
    }
}

/*
Returns a pointer to an array of book pointers
*/
Book** createBooks(string prefix, int numBooks)
{
    // **books -> *bookArray[numBooks] -> book

    //cout << endl << "POINTERS: ------------" << endl;

    Book **books = new Book*[numBooks];
    //cout << &books << endl;

    //cout << "\t" << books << endl;

    for (int i = 0; i < numBooks; i++) {
        Book *tmpBook = new Book(prefix + "_Title_" + to_string(i), \
        prefix + "_Author_" + to_string(i), prefix + "_ISBN_" + to_string(i));

        *(books + i) = tmpBook;
        //cout << "\t\t" << (*books + i) << endl;
    }

    return books;
}

void deleteBooks(Book **books, int numBooks)
{
    // **books -> *bookPtrArray[numBooks] -> book

    // Delete each book
    for (int i = 0; i < numBooks; i++) {
        //cout << "delete: " << *(books + i) << endl;

        // Each pointer in array
        delete *(books + i);
        *(books + i) = 0;
        //cout << " = " << *(books + i) << endl;
    }

    //cout << "delete array: " << books << endl;

    delete [] books;
    books = 0;
}

/*
Produces mock output for Library::print()

*/
ostringstream createMockLibraryPrintOutput(Book **books, string libraryName, int numBooks, int librarySize)
{
    ostringstream expectedOutput;

    expectedOutput << "Inventory of " << libraryName << endl;
	expectedOutput << "===================================\n";

    // Books
    for (int i = 0; i < numBooks; i++) {
		expectedOutput << i + 1 << ". " << books[i]->getTitle() \
        << " - " << books[i]->getAuthor() \
        << " - " << books[i]->getISBN() << endl;
	}

    // Empty slots
    for (int i = numBooks; i < librarySize; i++)
    {
        expectedOutput << i + 1 << ". [Empty Space]\n";
    }

    expectedOutput << "==================================" << endl;

    return expectedOutput;
}

ostringstream captureLibraryPrintOutput(Library &lib)
{
    // http://stackoverflow.com/questions/4810516/c-redirecting-stdout

	// Redirect cout to our output stream
    ostringstream output;

	streambuf *oldCoutBuffer = cout.rdbuf();
	cout.rdbuf(output.rdbuf());
    cout << flush;

	// Capture output
	lib.print();

	// Reset cout
	cout.rdbuf(oldCoutBuffer);

    return output;
}

bool BookContructor()
{
    cout << "Test: BookContructor() = ";
    string title = "My Title";
    string author = "Some Author";
    string ISBN = "7345";

    Book testBook(title, author, ISBN);

    assert(title==testBook.getTitle());
    assert(author==testBook.getAuthor());
    assert(ISBN==testBook.getISBN());

    cout << "PASS\n";

    return true;
}

bool BookSetAndGetFunctions()
{
    cout << "Test: BookSetAndGetFunctions() = ";

    Book testBook;
    string title = "Book Title";
    string author = "Book Author";
    string ISBN = "98473287572";
    string genre = "Book Genre";

    testBook.setTitle(title);
    testBook.setAuthor(author);
    testBook.setISBN(ISBN);
    testBook.setGenre(genre);

    assert(title==testBook.getTitle());
    assert(author==testBook.getAuthor());
    assert(ISBN==testBook.getISBN());
    assert(genre==testBook.getGenre());

    cout << "PASS\n";

    return true;
}

bool BookExtractionOperator()
{
    cout << "Test: BookExtractionOperator() = ";

    Book testBook;
    string title = "Book Title";
    string author = "Book Author";
    string ISBN = "98473287572";
    string genre = "Book Genre";

    testBook.setTitle(title);
    testBook.setAuthor(author);
    testBook.setISBN(ISBN);
    testBook.setGenre(genre);

    std::ostringstream expectedOutput;
    expectedOutput << title << " - " << author << " - " << ISBN;

    ostringstream output;
    output << testBook;

    assert(expectedOutput.str()==output.str());
    cout << "PASS\n";
    return true;

}

/*
TESTS:
- Adds books correctly using +=
- Default library size of 5
- Print outputs correctly
*/
bool LibraryAdd5BooksAndPrint()
{
	cout << "Test: LibraryAdd4BooksAndPrint() = ";

	ostringstream output;
	ostringstream expectedOutput;

	// Library Constructor with string
	string libName = "Lib Name";
	Library lib(libName);

	int numBooks = 5;

	// Create books
    Book **books = createBooks("A",numBooks);

    addBooksToLibrary(books, lib, numBooks);
    expectedOutput = createMockLibraryPrintOutput(books, libName, numBooks, 5);
	output = captureLibraryPrintOutput(lib);

	//cout << expectedOutput.str();
	//cout << output.str();

	assert(expectedOutput.str()==output.str());

    deleteBooks(books, 5);

	cout << "PASS" << endl;

	return true;
}


Book** getBooksFromLibraryByName(Book** books, Library &lib, int numBooks)
{
    Book **copyBooks = new Book*[numBooks];

    for (int i = 0; i < numBooks; i++) {
        copyBooks[i] = lib.getBook(books[i]->getTitle());
    }

    return copyBooks;
}

/*
The copy constructor needs to make a copy of each book in the inventory
of the old library and add it to the new library.
*/
bool LibraryCopyContructorCreatesDeepCopy()
{
	cout << "Test: LibraryCopyContructor() = ";
    int numBooks = 5;
    string libName = "Library A";

    // Create a library
    Library libA(libName);

    // Fill it with books
    Book **booksA = createBooks(libName, numBooks);
    addBooksToLibrary(booksA, libA, numBooks);

    //libA.print();

    // Create deep copy
    Library libB(libA);
    Book **booksB = getBooksFromLibraryByName(booksA, libB, numBooks);

    // Change all the books in Library A
    for (int i = 0; i < numBooks; i++) {
        booksA[i]->setTitle("EDIT_" + to_string(i));
    }

    // Compare with the books in the other library
    ostringstream expectedLibA = createMockLibraryPrintOutput(booksA, libName, numBooks, numBooks);
    ostringstream expectedLibB = createMockLibraryPrintOutput(booksB, libName, numBooks, numBooks);
    ostringstream outputLibA = captureLibraryPrintOutput(libA);
    ostringstream outputLibB = captureLibraryPrintOutput(libB);

    //cout << outputLibA.str();
    //cout << outputLibB.str();

    assert(expectedLibA.str()==outputLibA.str());
    assert(expectedLibB.str()==outputLibB.str());

    deleteBooks(booksA, numBooks);
    deleteBooks(booksB, numBooks);

    cout << "PASS" << endl;
    return true;
}

bool runTests()
{

	BookContructor();
	BookSetAndGetFunctions();
	BookExtractionOperator();

	LibraryAdd5BooksAndPrint();
    LibraryCopyContructorCreatesDeepCopy();

/*
    LibraryConstructorWithName();
    LibraryDefaultSizeOf5();

    LibraryAddBookOperator();
    LibraryDoesNotAddBookWhenFull();

    LibraryRemoveBookOperator();
    LibraryReturnsWhenEmptyAndRemoveBook();

    LibraryAssignmentOperatorCreatesCopy();
    LibraryPostIncrementIncreasesLibrarySize();
    LibraryPreDecrementDecreasesLibrarySize();
    LibraryPreDecrementRemovesLastBookIfFull();

    LibraryGetBook();
    LibraryGetBookReturnsNullIfNotFound();

    LibraryIsFullReturnsTrueIfFull();
    LibraryIsFullReturnsFalseIfNotFull();


    LibraryPrintWhenEmpty();
*/

    return true;
}