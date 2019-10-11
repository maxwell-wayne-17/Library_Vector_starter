#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/algorithm/string.hpp>

#include "../includes_usr/datastructures.h"
#include "../includes_usr/fileIO.h"
using namespace std;

const char SEPARATOR = ',';
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	books.clear();

	ifstream inputFile;
	inputFile.open(filename, ios::in);
	if (!inputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	string line = "";
	while(getline(inputFile, line)){
		book newBook;

		vector<string> data;
		boost::split(data, line,[](char c){return c == ',';});

		newBook.book_id = stoi(data[0]);

		newBook.title = data[1];
		newBook.author = data[2];

		newBook.state = static_cast<book_checkout_state>(stoi(data[3]));

		newBook.loaned_to_patron_id = stoi(data[4]);
		books.push_back(newBook);

	}

	if (books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}

	inputFile.close();
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) // added code but score did not change
{
	if (books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}

	fstream outputFile;
	outputFile.open(filename, ios_base::out);

	if (!outputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	for (int i = 0; i < int(books.size()); i++){
		outputFile << to_string(books[i].book_id) << "," << books[i].title << ","
				<< books[i].author << "," << to_string(books[i].state)
				<< "," << books[i].loaned_to_patron_id << endl;
	}

	outputFile.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	patrons.clear();

	ifstream inputFile;
	inputFile.open(filename, ios::in);
	if (!inputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	string line = "";
	while(getline(inputFile, line)){
		patron newPat;

		vector<string> data;
		boost::split(data, line,[](char c){return c == ',';});

		newPat.patron_id = stoi(data[0]);

		newPat.name = data[1];

		newPat.number_books_checked_out = stoi(data[2]);

		patrons.push_back(newPat);

	}

	if (patrons.empty()){
		return NO_PATRONS_IN_LIBRARY;
	}

	inputFile.close();
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	if (patrons.empty()){
			return NO_PATRONS_IN_LIBRARY;
		}

		ofstream outputFile;
		outputFile.open(filename);

		if (!outputFile.is_open()){
			return COULD_NOT_OPEN_FILE;
		}

		for (int i = 0; i < int(patrons.size()); i++){
			outputFile << to_string(patrons[i].patron_id) << "," << patrons[i].name << ","
					<< to_string(patrons[i].number_books_checked_out) << endl;
		}

		outputFile.close();
		return SUCCESS;

}
