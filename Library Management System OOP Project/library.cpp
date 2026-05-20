#include <iostream>
#include <sstream>
#include <string>
#include "library.h"
#include "lms_utilities.h"

void Library::add_book(Book new_book) {
    // TODO(student)
    books.push_back(new_book);
}

void Library::register_member(Member new_member) {
    members.push_back(new_member);
    // TODO(student)
}

bool Library::borrow_book(const std::string& isbn, int member_id, std::string& message) {
    // Check if book is available and if isbn is in the library
    // If the book is not available, set message to "Book ISBN: {isbn} not available" and return false
    std::string book_title;
    bool book_available = false;
    bool book_found = false;

    std::string member_msg = "";
    std::string book_msg = "";
    

    for (Book x : books){
        if (x.get_isbn() == isbn) {
            book_title = x.get_title();
            book_available = x.is_available();
            book_found = true;
            book_msg = " borrowed " + operator<<(std::ostringstream(), x).str();
            break;
        }
    }

    //Check if member is registered
    // If the member is not registered, set message to "Member ID: {member_id} not found" and return false
    bool member_registered = false;
    for (Member member : members) {
        if (member.get_id() == member_id) {
            member_registered = true;
            member_msg = operator<<(std::ostringstream(), member).str();
            
            break;
        }
    }



    if (!book_available || !book_found) {
        message = "Book ISBN: " + isbn + " not available";
        return false;
    }

    if (!member_registered) {
        message = "Member " + std::to_string(member_id) + " not found";
        return false;
    }

    // If the book is available and the member is registered, set message to "Book \"{book_title}\" borrowed by member ID: {member_id}" and return true
    // set the book to unavailable
    for (auto& x : books) {
       if (x.get_isbn() == isbn) {
            x.borrow_book();
            break;
       }
     }

    //Use opertator<< to set the message
    message = member_msg + book_msg;

    return true;



}

bool Library::return_book(const std::string& isbn, std::string& message) {

    //Check if book is unavailable and if isbn is in the library
    // If the book is not unavailable, set message to "Book ISBN: {isbn} not currently borrowed" and return false
    std::string book_title;
    bool book_unavailable = false;
    bool book_found = false;
    for (Book x : books){
        if (x.get_isbn() == isbn) {
            book_title = x.get_title();
            book_unavailable = !x.is_available();
            book_found = true;
            break;
        }
    }

    if (!book_found) {
        message = "Book ISBN: " + isbn + " not found";
        return false;
    }

    if (!book_unavailable) {
        message = "Book ISBN: " + isbn + " still available (cannot be returned)";
        return false;
    }


    //set the book to available
    for (auto& x : books) {
       if (x.get_isbn() == isbn) {
            x.return_book();
            break;
       }
     }
    message = "Book \"" + book_title + "\" returned";
    return true;

}

void Library::display_available_books(std::ostream& os) {
    // TODO(student)

    for (const auto& book : books) {
        if (book.is_available()) {
            os << book << std::endl;
        }
    }
    // use the ostream parameter, NOT std::cout
}

void Library::display_library_members(std::ostream& os) {
    // TODO(student)
    // use the ostream parameter, NOT std::cout

    for (const auto& member : members) {
        os << member << std::endl;
    }
}

bool Library::is_book_available(const std::string& isbn) {
    // TODO(student)

    for (auto& x : books) {
        if (x.get_isbn() == isbn) {
            return x.is_available();
        }
    }

    return false;
}
