#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "book.h"
#include "member.h"
#include "library.h"
#include "lms_utilities.h"

int read_list_of_books(Library& library, const std::string& filename) {

    //output error message if file cannot be opened
    std::ifstream book_file(filename);
    std::string line;
    int books_added = 0;

    if (!book_file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    /* Text file format:
     * Every 3 lines of the text file contains the title in the first, authors first and last name in the second, and isbn in the third line, separated by spaces.
     * For example:
     * The Great Gatsby
     * Scott Fitzgerald
     *  1234567890
     *
     */

    while(std::getline(book_file, line)) {
        std::string title = line;

        std::getline(book_file, line);
        std::istringstream x(line);
        std::string author_first;
        std::string author_last;
        x >> author_first >> author_last;

        std::getline(book_file, line);
        std::string isbn = line;

        try {
            library.add_book(Book(title, author_first, author_last, isbn));
            //std::cout << "Added book: " << title << " by " << author_first << " " << author_last << " with ISBN: " << isbn << std::endl;
        } catch (const std::invalid_argument& e) {
            continue;
        }

        books_added++;
    
    }

    //return the number of books added to the library

    return books_added;


}

int read_list_of_members(Library& library, const std::string& filename) {


    // TODO(student)

    std::ifstream member_file(filename);
    std::string line;
    int members_added = 0;

    int member_id = 1000;


    if (!member_file.is_open()) {
    throw std::runtime_error("Cannot open " + filename);
    }


    while(std::getline(member_file, line)) {
        std::istringstream x(line);
        std::string first_name;
        std::string last_name;
;

        x >> first_name >> last_name;

        try {
            library.register_member(Member(first_name, last_name, member_id));
            //std::cout << "Added member: " << first_name << " " << last_name << " with ID: " << member_id << std::endl;
        } catch (const std::invalid_argument& e) {
            continue;
        }

        members_added++;
        member_id++;
    }

    return members_added;
}

int read_list_of_borrowed_books(Library& library, const std::string& filename) {
    // TODO(student)
    int books_borrowed = 0;

    std::ifstream borrowed_books_file(filename);

    if (!borrowed_books_file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::string line;
    std::string isbn;
    std::string member_id;

    while(std::getline(borrowed_books_file, line)) {
        std::istringstream x(line);

        x >> isbn >> member_id;

        std::string message;
        if (library.borrow_book(isbn, std::stoi(member_id), message)) {
            books_borrowed++;
        }
    }

    return books_borrowed;
}



int read_list_of_returned_books(Library& library, const std::string& filename) {
    int books_returned = 0;
    std::ifstream returned_books_file(filename);


    if (!returned_books_file.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::string line;
    std::string isbn;

    while(std::getline(returned_books_file, line)) {
        std::istringstream x(line);

        x >> isbn;

        std::string message;
        if (library.return_book(isbn, message)) {
            books_returned++;
        }
    }

    return books_returned;
}
