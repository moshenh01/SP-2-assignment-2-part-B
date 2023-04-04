#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

Player :: Player(string name)
{
    this->name = name;
    
    this->handCards = vector<Card>();
    this->takenCards = vector<Card>();
    this->isWinner = false;
    this->hasCards = false;
    this->numOfWins = 0;

};




int Player :: stacksize()
{
    return this->handCards.size();
};

int Player :: cardesTaken()
{
    return ((this->takenCards.size()));
};



void Player :: addCard(const Card& card)//card is a const reference so it can't be changed
{
    this->handCards.push_back(card);
};

void Player :: addTakenCard(const Card& card)
{
    this->takenCards.push_back(card);
};


Card Player :: getTopCard()
{
    if(this->handCards.size() == 1)
    {
        hasCards = false;
        //std::cout << "No cards in hand!" << std::endl;
        Card card = this->handCards.back();
        this->handCards.pop_back();
        return card; 
    }
    else if(this->handCards.size() == 0)
    {
       throw std::runtime_error ("No cards in hand!");
    }
    else{
        Card card = this->handCards.back();
        this->handCards.pop_back();
        return card;
    }
};

std::string Player :: getName()
{
    return this->name;
};

bool Player :: getHasCards()
{
    return this->hasCards;
};
bool Player :: getIsWinner()
{
    return this->isWinner;
};
int Player :: getNumOfWins()
{
    return this->numOfWins;
};
void Player :: setIsWinner(bool isWinner)
{
    this->isWinner = isWinner;
};
void Player :: setNumOfWins(int numOfWins)
{
    this->numOfWins = numOfWins;
};
void Player :: setHasCards(bool hasCards)
{
    this->hasCards = hasCards;
};
void Player :: addNumOfWins()
{
    this->numOfWins++;
};


