#ifndef PRAC3_TASK2_TESTS_H
#define PRAC3_TASK2_TESTS_H

class Book;
class Library;

#include <sstream>

using namespace std;

bool runTests();

// Utility functions
bool addBooksToLibrary(Book **books, Library &lib, int numBooks);
void popFromBookArray(Book** books, int index, int numBooks);
Book** createBooks(std::string prefix, int numBooks);
void deleteBooks(Book **books, int numBooks);
void createMockLibraryPrintOutput(Book **books, std::string libraryName, int numBooks, int librarySize, ostringstream &);
void captureLibraryAddBookOutput(Library &lib, Book* book, ostringstream &);
void captureLibraryPrintOutput(Library &lib, ostringstream &);
Book** getBooksFromLibraryByName(Book** books, Library &lib, int numBooks);

// Tests
bool BookConstructor();
bool BookSetAndGetFunctions();
bool BookExtractionOperator();
bool LibrarySetAndGetName();
bool LibraryAdd5BooksAndPrint();
bool LibraryCopyContructorCreatesDeepCopy();
bool LibraryDoesNotAddBookWhenFull();
bool LibraryRemoveBookOperator();
bool LibraryAssignmentOperatorCreatesDeepCopy();
bool LibraryPostIncrementIncreasesLibrarySize();
bool LibraryPreDecrementDecreasesLibrarySize();
bool LibraryPreDecrementRemovesLastBookIfFull();
bool LibraryGetBook();
bool LibraryIsFull();
bool LibraryRemoveAllSpace();

#endif
