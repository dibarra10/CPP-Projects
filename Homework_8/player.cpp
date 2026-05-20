#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "player.h"

using std::vector, std::string, std::size_t;

// TODO(student) Initialize attributes
Player::Player(bool is_AI) : is_AI(is_AI), hand{} {

}

void Player::AddToHand(Card* c) {
    // TODO(student) Add the card c to the player's hand
    hand.push_back(c);
}

size_t Player::GetHandSize() {
    // TODO(student) Implement getter
    return hand.size();
}

std::string Player::GetHandString() {
    // TODO(student) Implement getter
    std::ostringstream oss;
   
    for (Card* card : hand) {
        oss << card->rank() << " " << card->suit();
        if (card != hand.back()) {
            oss << ", ";
        }
    }

    return oss.str();
}

Card* Player::PlayCard(string const& rank, string const& suit) {
    // TODO(student) Choose a card to play and return the chosen card.


    //parameters are the rank and suit of the active card


    //Check whether player is an ai or human and implement logic accordingly

    if (is_AI) {
        // Iterate through player's hand and return the first card that can be played
        // if no card can be played, must draw a card, so return nullptr

        int i = 0;
        bool card_found = false;

        for (Card* card : hand) {
            
            if (card->CanBePlayed(rank, suit)) {
                // Remove the card from the player's hand and return it
                card_found = true;
                hand.erase(hand.begin() + i);
                return card;
            }

            i++;
        }

        if (!card_found) {
            return nullptr;
        }


    } 



        // Prompt the user to choose a card to play until they choose a valid card
            std::cout << "Your hand contains: " << GetHandString() << '.' << std::endl;
            std::cout << "The next card played must be a " << rank << " or " << suit << "." << std::endl;
            std::cout << "What would you like to play? (enter \"draw card\" to draw a card)\n";


            std::string input;


        while (true) {
            std::getline(std::cin, input);
            std::istringstream iss(input);

            if (input == "draw card") {
                return nullptr;
            }

            std::string card_rank, card_suit, fluff;
            iss >> card_rank >> card_suit >> fluff;

            //check if input card has valid rank and suit

            if (card_rank.empty() || card_suit.empty()) {
                std::cout << "Invalid card. Try again." << std::endl;
                continue;
            }

            if(!fluff.empty()) {
                std::cout << "Invalid card. Try again." << std::endl;
                continue;
            }
     
            bool valid_suit = true;
            for (char c : card_suit) {
                if (!std::isalpha(c)) {
                    valid_suit = false;
                    break;
                }
            }
            if (!valid_suit) {
                std::cout << "Invalid card. Try again. 5" << std::endl;
                continue;
            }



            ////////////////////////////////////////////

            //Check if the card is in the player's hand and can be played on the active card

            int i = 0;
            bool card_found = false;

            for (Card* card : hand) {
                if (card->rank() == card_rank && card->suit() == card_suit) {
                    if (card->CanBePlayed(rank, suit)) {
                        // Remove the card from the player's hand and return it
                        card_found = true;
                        hand.erase(hand.begin() + i);
                        return card;
                    } else {
                        std::cout << "You can't play that card. Try again." << std::endl;
                        card_found = true;
                        break;
                    }
                }
                i++;
            }

            if (!card_found) {
                std::cout << "You don't have that card. Try again." << std::endl;
            }
        }


    
    
    return nullptr;
   
}

std::string Player::NextSuit(vector<string> const& suits, string const& suit) {
    // TODO(student) Choose the next suit (after playing an 8)

    // Check if player is ai

    if(is_AI){
        return suit;
    }

    std::cout << "What suit would you like to declare?" << std::endl;

    //prompt the user to choose a suit until they choose a valid suit
    while (true) {
       
        std::string input;
        std::getline(std::cin, input);
        for (const std::string& s : suits) {
            if (s == input) {
                return input;
            }
        }

        std::cout << "That's not a suit in this deck. Try again." << std::endl;
    }
    
}
