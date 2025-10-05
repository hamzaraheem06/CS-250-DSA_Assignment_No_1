#include "uno.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>  // For rand() and srand()
#include <numeric>  // For std::fill

using namespace std;

struct Card {
    std::string color;  // Red, Green, Blue, Yellow
    std::string value;  // 0-9, Skip, Reverse, Draw Two

    Card(std::string c = "", std::string v = "") : color(c), value(v) {}
};

UNOGame::UNOGame(int numPlayers) {}


// Derived class that implements the UNOGame interface
class UNOGameImpl : public UNOGame {
private:
    int numPlayers;
    vector<vector<Card>> playerHands;  // Each player's hand
    vector<Card> deck;
    vector<Card> discardPile;
    int currentPlayer;
    bool clockwise;  // true = clockwise, false = counter-clockwise
    int winner;
    vector<bool> unoCalled;  // Tracks if each player called UNO when down to 1 card

    int getNextPlayer() const {
        if (clockwise) {
            return (currentPlayer + 1) % numPlayers;
        } else {
            return (currentPlayer - 1 + numPlayers) % numPlayers;
        }
    }

    void moveToNextPlayer() {
        currentPlayer = getNextPlayer();
    }

public:
    // Initialize game with given number of players
    UNOGameImpl(int numPlayers)
        : UNOGame(numPlayers), numPlayers(numPlayers), currentPlayer(0),
          clockwise(true), winner(-1), unoCalled(numPlayers, false) {
        playerHands.resize(numPlayers);
    }

    virtual ~UNOGameImpl() {}

    // Shuffle and deal cards to players
    virtual void initialize() {
        deck.clear();
        discardPile.clear();
        for (vector<Card>& hand : playerHands) {
            hand.clear();
        }
        winner = -1;
        currentPlayer = 0;
        clockwise = true;
        fill(unoCalled.begin(), unoCalled.end(), false);  // Reset UNO flags

        // Create deck
        vector<string> colors;
        colors.push_back("Red");
        colors.push_back("Green");
        colors.push_back("Blue");
        colors.push_back("Yellow");

        // Add numbered cards (0-9)
        for (size_t c = 0; c < colors.size(); c++) {
            const string& color = colors[c];
            deck.push_back(Card(color, "0"));  // One 0 per color
            for (int i = 1; i <= 9; i++) {
                deck.push_back(Card(color, to_string(i)));  // Two of each 1-9
                deck.push_back(Card(color, to_string(i)));
            }
        }

        // Add action cards (Skip, Reverse, Draw Two - two each per color)
        for (size_t c = 0; c < colors.size(); c++) {
            const string& color = colors[c];
            deck.push_back(Card(color, "Skip"));
            deck.push_back(Card(color, "Skip"));
            deck.push_back(Card(color, "Reverse"));
            deck.push_back(Card(color, "Reverse"));
            deck.push_back(Card(color, "Draw Two"));
            deck.push_back(Card(color, "Draw Two"));
        }

        // Shuffle with fixed seed 1234
        mt19937 rng(1234);
        shuffle(deck.begin(), deck.end(), rng);

        // Seed rand for reproducible "forget" chance
        srand(1234);

        // Deal 7 cards to each player
        for (int i = 0; i < 7; i++) {
            for (int p = 0; p < numPlayers; p++) {
                playerHands[p].push_back(deck.back());
                deck.pop_back();
            }
        }

        // Top card starts discard pile
        discardPile.push_back(deck.back());
        deck.pop_back();
    }

    // Play one turn of the game
    virtual void playTurn() {
        if (isGameOver()) return;

        Card topCard = discardPile.back();
        vector<Card>& currentHand = playerHands[currentPlayer];

        // Find a playable card
        int playableIndex = -1;

        // Priority: color match, value match, action card (Skip > Reverse > Draw Two)
        // First, look for color matches
        for (size_t i = 0; i < currentHand.size(); i++) {
            if (currentHand[i].color == topCard.color) {
                playableIndex = static_cast<int>(i);
                break;
            }
        }

        // If no color match, look for value match
        if (playableIndex == -1) {
            for (size_t i = 0; i < currentHand.size(); i++) {
                if (currentHand[i].value == topCard.value) {
                    playableIndex = static_cast<int>(i);
                    break;
                }
            }
        }

        if (playableIndex != -1) {
            // Play the card
            Card playedCard = currentHand[playableIndex];
            size_t prevSize = currentHand.size();
            discardPile.push_back(playedCard);
            currentHand.erase(currentHand.begin() + playableIndex);

            // UNO! Check: Did we just drop to 1 card?
            if (prevSize == 2 && currentHand.size() == 1) {
                // Assume AI calls with 50% chance (for realism; set to true for perfect AI)
                bool callsUno = (rand() % 2 == 0);
                if (callsUno) {
                    unoCalled[currentPlayer] = true;
                    cout << "Player " << currentPlayer << " shouts 'UNO!'" << endl;
                } else {
                    // Penalty: Draw 2
                    for (int i = 0; i < 2 && !deck.empty(); i++) {
                        currentHand.push_back(deck.back());
                        deck.pop_back();
                    }
                    unoCalled[currentPlayer] = true;  // Still "call" it after penalty, per rules
                    cout << "Player " << currentPlayer << " forgot UNO! Drew 2 cards as penalty." << endl;
                    // Reset if now >1 (which it will be)
                    if (currentHand.size() > 1) {
                        unoCalled[currentPlayer] = false;
                    }
                }
            }

            // Check for winner
            if (currentHand.size() == 0) {
                winner = currentPlayer;
                unoCalled[currentPlayer] = false;  // Reset on win
                return;
            }

            // Handle action cards
            if (playedCard.value == "Skip") {
                moveToNextPlayer();  // Skip next player
            } else if (playedCard.value == "Reverse") {
                clockwise = !clockwise;  // Reverse direction
            } else if (playedCard.value == "Draw Two") {
                int nextPlayer = getNextPlayer();
                // Next player draws 2 cards
                size_t nextPrevSize = playerHands[nextPlayer].size();
                for (int i = 0; i < 2 && !deck.empty(); i++) {
                    playerHands[nextPlayer].push_back(deck.back());
                    deck.pop_back();
                }
                // Reset UNO flag if drew and now >1
                if (nextPrevSize == 1 && playerHands[nextPlayer].size() > 1) {
                    unoCalled[nextPlayer] = false;
                }
                moveToNextPlayer();  // Skip next player
            }
        } else {
            // No playable card, draw one
            if (!deck.empty()) {
                Card drawnCard = deck.back();
                deck.pop_back();

                // Check if drawn card is playable
                if (drawnCard.color == topCard.color || drawnCard.value == topCard.value) {
                    // Play it
                    discardPile.push_back(drawnCard);

                    // Handle action cards for drawn card
                    if (drawnCard.value == "Skip") {
                        moveToNextPlayer();
                    } else if (drawnCard.value == "Reverse") {
                        clockwise = !clockwise;
                    } else if (drawnCard.value == "Draw Two") {
                        int nextPlayer = getNextPlayer();
                        // Next player draws 2 cards
                        size_t nextPrevSize = playerHands[nextPlayer].size();
                        for (int i = 0; i < 2 && !deck.empty(); i++) {
                            playerHands[nextPlayer].push_back(deck.back());
                            deck.pop_back();
                        }
                        // Reset UNO flag if drew and now >1
                        if (nextPrevSize == 1 && playerHands[nextPlayer].size() > 1) {
                            unoCalled[nextPlayer] = false;
                        }
                        moveToNextPlayer();
                    }
                } else {
                    // Can't play, add to hand
                    size_t prevSize = currentHand.size();
                    currentHand.push_back(drawnCard);
                    // Reset UNO flag if drew when at 1 (now >1)
                    if (prevSize == 1) {
                        unoCalled[currentPlayer] = false;
                    }
                }
            }
        }

        // Move to next player
        moveToNextPlayer();
    }

    // Return true if game has a winner
    virtual bool isGameOver() const {
        return winner != -1;
    }

    // Return index of winner
    virtual int getWinner() const {
        return winner;
    }

    // Return current state as string
    virtual string getState() const {
        string state = "Player " + to_string(currentPlayer) + "'s turn, Direction: ";
        state += clockwise ? "Clockwise" : "Counter-clockwise";
        state += ", Top: " + discardPile.back().color + " " + discardPile.back().value;
        state += ", Players cards: ";

        for (int i = 0; i < numPlayers; i++) {
            state += "P" + to_string(i) + ":" + to_string(playerHands[i].size());
            if (i < numPlayers - 1) state += ", ";
        }

        return state;
    }
};
