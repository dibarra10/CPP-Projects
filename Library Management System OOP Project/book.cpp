#include <string>
#include <stdexcept>
#include "book.h"

Book::Book(std::string book_title, std::string author_first, std::string author_last, std::string book_isbn, bool book_available)
: title(book_title), author({author_first, author_last}), isbn(book_isbn), available(book_available) {
    

    //Title check
    
        if (book_title.empty()) {
            throw std::invalid_argument("Invalid title");
        }

        for (char c : book_title) {
            if (!(std::isalpha(c) || std::isspace(c) || c == '-' || c == ':')) {
                throw std::invalid_argument("Invalid title");
            }
        }
    

    //Author check
   
        if (author_first.empty() && author_last.empty()) {
            throw std::invalid_argument("Invalid author");
        }

        for (char c : author_first) {
            if (!(std::isalpha(c))) {
                throw std::invalid_argument("Invalid author");
            }
        }

        for (char c : author_last) {
            if (!(std::isalpha(c))) {
                throw std::invalid_argument("Invalid author");
            }
        }
    

    //ISNB check
    
        if (book_isbn.empty()) {
            throw std::invalid_argument("Invalid ISBN");
        }

        int i = 0;
        for (char c : book_isbn) {
            if (c >= '0' && c <= '9'){
                i++;
            } else {
                throw std::invalid_argument("Invalid ISBN");
            }

        }

        if (i != 13 && i != 10) {
            throw std::invalid_argument("Invalid ISBN");
        }
    
}




    

    // TODO(student)}

Book::Book(std::string book_title, AuthorName book_author, std::string book_isbn, bool book_available)
: title(book_title), author(book_author), isbn(book_isbn), available(book_available) {
    // TODO(student)

        //Title check
    
        if (book_title.empty()) {
            throw std::invalid_argument("Invalid title");
        }

        for (char c : book_title) {
            if (!(std::isalpha(c) || std::isspace(c) || c == '-' || c == ':')) {
                throw std::invalid_argument("Invalid title");
            }
        }
    

    //Author check
   
        if (book_author.first_name.empty() && book_author.last_name.empty()) {
            throw std::invalid_argument("Invalid author");
        }

        for (char c : book_author.first_name) {
            if (!(std::isalpha(c))) {
                throw std::invalid_argument("Invalid author");
            }
        }

        for (char c : book_author.last_name) {
            if (!(std::isalpha(c))) {
                throw std::invalid_argument("Invalid author");
            }
        }
    

    //ISNB check
    
        if (book_isbn.empty()) {
            throw std::invalid_argument("Invalid ISBN");
        }

        int i = 0;
        for (char c : book_isbn) {
            if (c >= '0' && c <= '9'){
                i++;
            } else {
                throw std::invalid_argument("Invalid ISBN");
            }

        }

        if (i != 13 && i != 10) {
            throw std::invalid_argument("Invalid ISBN");
        }
}

const std::string& Book::get_title() const {
    // TODO(student)
    return title;
}

const AuthorName& Book::get_author() const {
    // TODO(student)
    return author;
}

const std::string& Book::get_isbn() const {
    // TODO(student)
    return isbn;
}

bool Book::is_available() const {
    // TODO(student)
    return available;
}

bool Book::borrow_book() {
    // TODO(student)
    if (available) {
        available = false;
        return true;
    }   
    return false;
}

bool Book::return_book() {
    // TODO(student)
    if (!available) {
        available = true;
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    // TODO(student)

    os << "title: \"" << book.get_title() << "\" by " 
    << book.get_author().first_name << " " << book.get_author().last_name
    << ", isbn: " << book.get_isbn();    
    return os;
}
