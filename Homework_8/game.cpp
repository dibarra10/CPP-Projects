#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "game.h"

using std::string, std::vector;


void Game::LoadDeckFromFile(string const& file_name) {
    // TODO(student) initialize suits, deck, and draw_pile from the given file
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + file_name);
    }

    //Iterate through the file and create cards and suits accordingly

    string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string rank, suit, fluff;

        iss >> rank >> suit >> fluff;

        /////////////////////////////////////////////////////////////////////
        //check if rank and suit are valid (non-empty and alphanumeric)
        if (rank.empty() || suit.empty()) {
            throw std::runtime_error("Invalid file format: " );
        }

        if (!fluff.empty()) {
            throw std::runtime_error("Invalid file format: " );
        }

        
        for (char c : rank) {
            if (!std::isalnum(c)) {
                throw std::runtime_error("Invalid file format: " );
            }
        }

        for (char c : suit) {
            if (!std::isalnum(c)) {
                throw std::runtime_error("Invalid file format: " );
            }
        }

        //////////////////////////////////////////////////////////////////////

        // Create a new card and add it to the deck and draw pile
        try{
            Card* card = new Card(rank, suit);
            deck.push_back(card);
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("");
        }
        

        if (suits.empty()) {
            suits.push_back(suit);
        } else {
            // Check if the suit is already in the suits vector
            bool suit_exists = false;
            for (const string& s : suits) {
                if (s == suit) {
                    suit_exists = true;
                    break;
                }
            }
            // If the suit is not in the suits vector, add it
            if (!suit_exists) {
                suits.push_back(suit);
            }
        }

    }

    // for draw pile reverse deck and assign to draw pile
    draw_pile = vector<Card*>(deck.rbegin(), deck.rend());  

}

void Game::AddPlayer(bool x) {
    // TODO(student) add a new player to the game

    // Create a new player and store in heap and add it to the players vector

    Player* player = new Player(x);
    players.push_back(player);


}

void Game::DrawCard(Player* player) {
    // TODO(student) Move the top card of the draw pile to the Player's hand
    // If the draw pile is empty, flip the discard pile to create a new one

    if (draw_pile.empty()) {

        if (discard_pile.size() == 1) {
            throw std::runtime_error("Not enough cards to draw.");
        }

        std::cout << "Draw pile empty, flipping the discard pile." << std::endl;

        // Move all but the top card of the discard pile to the draw pile
        Card* top_card = discard_pile.back();
        discard_pile.pop_back();
        draw_pile = vector<Card*>(discard_pile.rbegin(), discard_pile.rend());
        discard_pile.clear();
        discard_pile.push_back(top_card);

    }

    // Draw card into player's hand
    player->AddToHand(draw_pile.back());
    draw_pile.pop_back();
    
}

Card* Game::Deal(size_t x) {
    // TODO(student) Flip the top card of the draw pile as the initial discard
    // then deal num_cards many cards to each player

    draw_pile.back()->Play();
    discard_pile.push_back(draw_pile.back());
    draw_pile.pop_back();

    //iterate through players and deal 1 card at a time until each player has num_cards many cards
    for (size_t i = 0; i < x; ++i) {
        for (Player* player : players) {
            DrawCard(player);
        }
    }
 
    

    // Return the initially discarded card
    return discard_pile.back();
    
}

string Game::MostPlayedSuit() {
    // TODO(student) Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits

    string most_played_suit;

    //Add up the number of times each suit has been played by iterating through the deck and checking the times played for each card and adding it to a running total for each suit
    vector<size_t> suit_counts(suits.size(), 0);
    for (Card* card : deck) {
        for (size_t i = 0; i < suits.size(); ++i) {
            if (card->suit() == suits[i]) {
                suit_counts[i] += card->times_played();
                break;
            }
        }
    }

    // Find the suit with the highest count
    size_t max_count = 0;
    for (size_t i = 0; i < suits.size(); ++i) {
        if (suit_counts[i] > max_count) {
            max_count = suit_counts[i];
            most_played_suit = suits[i];
        }
    }


    return most_played_suit;
}

int Game::RunGame() {
    // TODO(student) Run the game and return the number of the winning player

    string rank, suit;
    rank = discard_pile.back()->rank();
    suit = discard_pile.back()->suit();

    while (true) {
        for (size_t i = 0; i < players.size(); ++i) {
            Player* player = players[i];
            std::cout << "Player " << i << "'s turn!" << std::endl;
            
            Card* card_to_play = player->PlayCard(rank, suit);

            if (card_to_play == nullptr) {
                try{
                    DrawCard(player);
                } catch (const std::runtime_error& e) {
                    std::cout << "Player " << i << " cannot draw a card." << std::endl;
                    return -1;
                }
                
                std::cout << "Player " << i << " draws a card." << std::endl;
                
            } else {

                card_to_play->Play();
                discard_pile.push_back(card_to_play);

                //Check if the card played is an 8, if so place down the 8 into discard pile and prompt the player to choose a suit and place a new card with rank 8 without creating a new card in the deck and place that card into the discard pile with the chosen suit
                if (card_to_play->rank() == "8") {
                    
                    std::string new_suit = player->NextSuit(suits, card_to_play->suit());
                    rank = "8";
                    suit = new_suit;
                    std::cout << "Player " << i << " plays " << card_to_play->rank() << " " << card_to_play->suit() << " and changes the suit to " << new_suit << '.' << std::endl;



                } else {

                    rank = card_to_play->rank();
                    suit = card_to_play->suit();

                    std::cout << "Player " << i << " plays " << card_to_play->rank() << " " << card_to_play->suit() << '.' << std::endl;

                    if (player->GetHandSize() == 0) {
                        //std::cout << "Player " << i << " wins!" << std::endl;
                        return i;
                    }
                }
            }
        }


    //return {};
    }

}
