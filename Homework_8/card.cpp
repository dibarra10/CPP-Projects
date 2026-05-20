#include <stdexcept>
#include <string>
#include "card.h"

// TODO(student) Initialize attributes
Card::Card(std::string rank, std::string suit) : rank_{rank}, suit_{suit}, times_played_{0} {
    // TODO(student) Implement constructor checks

    if (rank.empty() || suit.empty()) {
        throw std::invalid_argument("Rank and suit cannot be empty.");
    }
    for (char c : rank) {
        if (!std::isalnum(c)) {
            throw std::invalid_argument("Rank must be alphanumeric.");
        }
    }
    for (char c : suit) {
        if (!std::isalnum(c)) {
            throw std::invalid_argument("Suit must be alphanumeric.");
        }
    }

}

std::string Card::rank() const {
    // TODO(student) Implement getter
    return rank_;
}

std::string Card::suit() const {
    // TODO(student) Implement getter
    return suit_;
}

std::size_t Card::times_played() const {
    // TODO(student) Implement getter
    return times_played_;
}

bool Card::CanBePlayed(std::string const& rank , std::string const& suit) const {
    // TODO(student) Return whether or not this card can legally be played

    // Special case for 8s: can be played on any card
    if (rank_ == "8") {
        return true;
    }
    
    //Check rank and suit against active card and return true if either matches
    if (rank_ == rank || suit_ == suit) {
        return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    return os << card.rank() << " " << card.suit();
}
