#include "deck.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono> 

using namespace std;

/*
 * Help functions to randomize numbers quickly and more accurately than the built in rand function
 */
static unsigned int g_seed;

// Used to seed the generator.           
inline void fast_srand(int seed) {
    g_seed = seed;
}

// Compute a pseudorandom integer.
// Output value in range [0, 32767]
inline int fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

/**
 * Help function to convert Suit enum to string
*/
const string SuitToString(Suit s) {
    switch (s) {
        case Suit::Hearts:
            return "H";
        case Suit::Diamonds:
            return "D";
        case Suit::Spades:
            return "S";
        case Suit::Clubs:
            return "C";
        case Suit::Joker:
            return "Joker";
    }
    return "";
}

Card::Card(int rank, Suit suit)
{
    this->rank = rank;
    this->suit = suit;
}

/**
 * Overload of << operator for Card class
*/
ostream & operator << (ostream &out, const Card &c)
{
    string r;
    switch(c.rank) {
        case 1:
            r = 'A';
            break;
        case 11:
            r = 'J';
            break;
        case 12:
            r = 'Q';
            break;
        case 13:
            r = 'K';
            break;
        default:
            r = to_string(c.rank);
            break;
    }

    if (SuitToString(c.suit) == "Joker")
        out << "Joker";
    else
        out << r << SuitToString(c.suit);
    return out;
}

/**
 * Create a deck of 52 cards
*/
Deck::Deck() {
    for (Suit s = Suit::Hearts; s <= Suit::Clubs; s = Suit(s + 1)) {
        for (int r=1; r<14; r++) {
            cards.push_back(Card(r, s));
        }
    }
    for (int i = 0; i < 3; i++)
        cards.push_back(Card(0, Suit::Joker));
}

/**
 * Overload of << operator for Deck class
*/
ostream & operator << (ostream &out, const Deck &d)
{
    string separator;
    for (auto i: d.cards) {
        out << separator << i;
        separator = ", ";
    }

    return out;
}

/** 
 * Return number of cards in deck
 * 
*/
int Deck::size()
{
    return this->cards.size();
}

/**
 * Shuffle all the cards in deck in ranom order. 
*/
void Deck::shuffle()
{
    auto rng = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(this->cards.begin(),this->cards.end(), rng);
}

/**
 * Sort the deck according to card rank. All aces, the all two's, then all threes, ...
*/
void Deck::sort()
{
    vector<Card> sorted_cards; // Empty temporary deck

    while (this->size() > 0) {
        // Go through the deck from left to right, insert the deck in the appropriate spot
        Deck::insert(sorted_cards, this->take()); //Take a card from the old deck, insert it into the new one
    }

    this->cards = sorted_cards;
}

/**
 * Take the top card from the deck 
*/
Card Deck::take() {
    Card c = this->cards.back();
    this->cards.pop_back();
    return c;
}

/**
 * Put a card on top of the deck 
*/
void Deck::put(Card card) {
    cards.push_back(card);
}

/*
 * Removes the duplicates from deck
 */
vector<int> Deck::remove_duplicates()
{
    int x = 0;
    vector<int> found_indexes;
    for (int i = 0; i < cards.size(); i++)
    {
        x = -1;
        for (int j = 0; j < cards.size(); j++)
        {
            x++;
            if (i == j || (cards[i].get_rank() == 0 || cards[j].get_rank() == 0))
                continue;
            if (cards[i] == cards[j] && cards[i].get_suit() == cards[j].get_suit())
            {
                if (found_indexes.size() > 0)
                {
                    if (find(found_indexes.begin(), found_indexes.end(), j) != found_indexes.end())
                        found_indexes.push_back(x);
                }
                else
                    found_indexes.push_back(x);
            }
        }
    }

    reverse(found_indexes.begin(), found_indexes.end());
    for (auto i :found_indexes)
        cards.erase(cards.begin() + i);

    return found_indexes;
}

/*
 * Picks a random card in the deck
 */
Card Deck::pick_by_random()
{
    fast_srand(std::chrono::system_clock::now().time_since_epoch().count());
    int card_index = fast_rand() % cards.size();
    Card temp = cards[card_index];
    cards.erase(cards.begin() + card_index);
    return temp;
}

/*
 * Removes the jokers from deck
 */
void Deck::remove_jokers()
{
    int x = 0;
    vector<int> found_indexes;

    for (auto c : cards)
    {
        if (c.get_suit() == Suit::Joker)
            found_indexes.push_back(x);
        x++;
    }

    reverse(found_indexes.begin(), found_indexes.end());
    for (auto x : found_indexes)
        cards.erase(cards.begin() + x);
}

void Deck::insert(vector<Card> &cardlist, Card card) {
    bool did_add = false;
    if (cardlist.size() == 0)
    {
        cardlist.push_back(card);
        did_add = true;
    }
    else
    {    
        for (int i = 0; i < cardlist.size(); i++)
        {
            if (card > cardlist[i])
                continue;
            cardlist.insert(cardlist.begin() + i, card);
            did_add = true;
            break;
        }
    }

    if (!did_add)
        cardlist.push_back(card);
    return;
}

/*
 * Sort by suit
 */
void Deck::sort_by_suit() {
    vector<Card> sortedSuits;
    
    for (Suit s = Suit::Hearts; s <= Suit::Joker; s = Suit(s + 1))
    {
        for (int r = 0; r < 14; r++)
        {
            for (auto c : cards)
            {
                if (c.get_rank() == r && c.get_suit() == s)
                {
                    sortedSuits.push_back(c);
                }
            }
        }
    } 
    this->cards = sortedSuits;
}

/**
 * Sort by Value
 */
void Deck::sort_by_value() {
    vector<Card> sortedValue;

    for (int r = 0; r < 14; r++)
    {
        for (Suit s = Suit::Hearts; s <= Suit::Joker; s = Suit(s+1))
        {
            for (auto c : cards)
            {
                if (c.get_rank() == r && c.get_suit() == s)
                {
                    sortedValue.push_back(c);
                }
            }
        }
    }
    this->cards = sortedValue;
}
