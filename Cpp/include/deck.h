#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Suit {
    Hearts,
    Diamonds,
    Spades,
    Clubs,
    Joker
};

class Card
{
private:
    int rank;
    Suit suit;
public:
    Card(int rank, Suit suit);
    
    bool operator == (Card const &other)
    {
        return rank == other.rank;
    }

    bool operator < (Card const &other)
    {
        return rank < other.rank;
    }

    bool operator > (Card const &other)
    {
        return rank > other.rank;
    }

    int get_rank() { return this->rank; }
    Suit get_suit() { return this->suit; }
    

    friend ostream & operator << (ostream &out, const Card &c);
};

class Deck
{
private:
    vector<Card> cards;
public:
    Deck();
    friend ostream & operator << (ostream &out, const Deck &d);
    int size();
    void shuffle();
    void sort();
    Card take();
    void put(Card card);
    void remove_jokers();
    vector<int> remove_duplicates();
    Card pick_by_random();
    void sort_by_suit();
    void sort_by_value();
    vector<Card> get_cards() { return this->cards; }
    void set_cards(vector<Card> c) { this->cards = c; }
    
    static void insert(vector<Card> &cardlist, Card card);
};
