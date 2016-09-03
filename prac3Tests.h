#ifndef PRAC3_TESTS_H
#define PRAC3_TESTS_H

class Book;
class Library;

#include <sstream>

using namespace std;

bool runTests();

// Utility functions
void addBooksToLibrary(Book **books, Library &lib, int numBooks);
Book** createBooks(std::string prefix, int numBooks);
ostringstream createMockLibraryPrintOutput(Book **books, std::string libraryName, int numBooks, int librarySize);
ostringstream captureLibraryPrintOutput(Library &lib);
void deleteBooks(Book **books, int numBooks);

// Tests
bool BookContructor();
bool BookSetAndGetFunctions();
bool BookExtractionOperator();
bool LibraryAdd4BooksAndPrint();

/*
bool LibraryCopyContructorCreatesDeepCopy();
bool LibraryConstructorWithName();
bool LibraryDefaultSizeOf5();
bool LibraryAddBookOperator();
bool LibraryDoesNotAddBookWhenFull();
bool LibraryRemoveBookOperator();
bool LibraryReturnsWhenEmptyAndRemoveBook();
bool LibraryAssignmentOperatorCreatesCopy();
bool LibraryPostIncrementIncreasesLibrarySize();
bool LibraryPreDecrementDecreasesLibrarySize();
bool LibraryPreDecrementRemovesLastBookIfFull();
bool LibraryGetBook();
bool LibraryGetBookReturnsNullIfNotFound();
bool LibraryIsFullReturnsTrueIfFull();
bool LibraryIsFullReturnsFalseIfNotFull();
bool LibraryPrint();
bool LibraryPrintWhenEmpty();
*/
#endif
