#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>
#include "game.hpp"
#include "player.hpp"
#include <exception>

using namespace std;
void dealingCards(Player& player1, Player& player2);


Game :: Game(Player& p1, Player& p2): player1(p1), player2(p2) //this->player is pointer to the Player object
{
    //compare the addresses of the players
  
    
    dealingCards(p1, p2);
    
    player1.setHasCards(true);
    player2.setHasCards(true);
    this->log = vector<string>();
    this->drawRate = 0;
    this->isDraw = false;
   
};
void Game :: caseAceAndTwo(Card p1Card, Card p2Card)
{
    int val1 = p1Card.getValue();
    int val2 = p2Card.getValue();
    if(val1 == 14 && val2 == 2){
        //winner is val2
        string docTurn = player1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + player2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + player2.getName() + " Wins! \n";

        this->log.push_back(docTurn);

        player2.addTakenCard(p1Card);
        player2.addTakenCard(p2Card);
        player2.addNumOfWins();
    }
    else{//val1 == 2 && val2 == 14
        //winner is val1
        string docTurn = player1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + player2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + player1.getName() + " Wins! \n";

        this->log.push_back(docTurn);

        player1.addTakenCard(p1Card);
        player1.addTakenCard(p2Card);
        player1.addNumOfWins();

    }

    
};


void dealingCards(Player& player1, Player& player2)
{
    // Create a deck of cards
    std::vector<Card> deck;
    // std::cout << "CLUBS: " << static_cast<int>(Card::Suit::CLUBS) << std::endl;
    // std::cout << "DIAMONDS: " << static_cast<int>(Card::Suit::DIAMONDS) << std::endl;
    // std::cout << "HEARTS: " << static_cast<int>(Card::Suit::HEARTS) << std::endl;
    // std::cout << "SPADES: " << static_cast<int>(Card::Suit::SPADES) << std::endl;

     for (int i = 2; i <= 14; ++i) {
         for (int j = static_cast<int>(Card::Suit::CLUBS); j <= static_cast<int>(Card::Suit::SPADES); ++j) {
            Card::Suit suit = static_cast<Card::Suit>(j);
            Card card(i, suit);
            //cout << card.getValue() << " of " << card.getSuitString(card.getSuit()) << endl;
            deck.push_back(card);
        }

    }
    
     // Shuffle the deck
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    
    // Deal the cards
    //printf("%zu , %lu \n",deck.size(),static_cast<unsigned long>(5));
    for (int i = 0; i < deck.size()-1; i=i+2) {
        player1.addCard(deck[static_cast<unsigned long>(i)]);
        player2.addCard(deck[static_cast<unsigned long>(i+1)]);
     
    }
    // cout << "Player 1 has " << player1.stacksize() << " cards" << endl;
    // cout << "Player 2 has " << player2.stacksize() << " cards" << endl;
    
};

void Game :: playTurn()
{
      if (&this->player1 == &this->player2)
    {
        throw std::runtime_error ("Players can't be the same!");
    }
    // Check if both players have cards
    // cout << "Player 1 has " << player1.stacksize() << " cards" << endl;
    // cout << "Player 2 has " << player2.stacksize() << " cards" << endl;
    
    if(player1.getHasCards() &&  player2.getHasCards()){

        // Get top card from each player's hand
        Card p1Card = player1.getTopCard();
        Card p2Card = player2.getTopCard();
        
        // Get the value of each card
        int val1 = p1Card.getValue();
        int val2 = p2Card.getValue();

        // Determine winner of the turn
        if(((val1 == 2) && (val2 == 14)) || ((val1 ==14) && (val2 == 2))){
            caseAceAndTwo(p1Card, p2Card);
            return;
        }
        
        if (val1 > val2) {
            std:string docTurn = player1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + player2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + player1.getName() + " Wins! \n";
            this->log.push_back(docTurn); 
            
            player1.addTakenCard(p1Card);
            player1.addTakenCard(p2Card);

            player1.addNumOfWins();
           
            
            //cout << player1.getName() << " Wins!\n" << endl;

        } else if (val2 > val1) {
            std::string docTurn = player1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + player2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + player2.getName() + " Wins! \n";
            this->log.push_back(docTurn);
            player2.addTakenCard(p1Card);
            player2.addTakenCard(p2Card);
            player2.addNumOfWins();
           
            //cout << player2.getName() << " Wins!\n" << endl;

        }
        else {
            std::string docTurn = "\r" + player1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + player2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + "Draw! ";
            this->log.push_back(docTurn);
            this->drawRate++;

            
            if(player1.getHasCards() && player2.getHasCards()){
               
                //cout << "Draw!\n" << endl;

                vector<Card> pile1;
                vector<Card> pile2;
                //the first two cards
                pile1.push_back(p1Card);
                pile2.push_back(p2Card);
                //the upside down cards
                pile1.push_back(player1.getTopCard());
                pile2.push_back(player2.getTopCard());
                //in this func we wiil draw the next two open cards and compare agian
                playWar(pile1,pile2, player1, player2);
            }
            else{//return cards to players
                player1.addTakenCard(p1Card);
                player1.addTakenCard(p2Card);
                
                determinesWinner(player1,player2);
            }
        }
    }
    else{
        //in case that in the first 5 turns the game end we can replace the throw with return
        //or we can add try catch in the main.
        if(player1.getIsWinner() || player2.getIsWinner() || this->isDraw){
            throw std::runtime_error("Game is over!");
            //return;
        }
        determinesWinner(player1,player2);
    }

    
    
};

void Game:: determinesWinner(Player& player1, Player& player2)
{
    if(player1.cardesTaken() > player2.cardesTaken()){
        player1.setIsWinner(true);
        
    }
    else if(player1.cardesTaken() < player2.cardesTaken()){
        player2.setIsWinner(true);
        //cout << "\n" << player2.getName() << " is the winner!" << endl;
    }
    else{
        this->isDraw = true;
        //cout << "Draw!\n" << endl;
    }
};

void  Game :: playWar(vector<Card> pile1,vector<Card> pile2,Player& ply1,Player& ply2)// check if its ok*****
{
   if (ply1.getHasCards() && ply2.getHasCards()){

   
        // Get top card from each player's hand
        Card p1Card = ply1.getTopCard();
        Card p2Card = ply2.getTopCard();
        
        // cout << p1.getName() << " played " << p1Card.getValue() << " of " << p1Card.getSuitString(p1Card.getSuit()) << " ";
        // cout << p2.getName() << " played " << p2Card.getValue() << " of " << p2Card.getSuitString(p2Card.getSuit()) << " ";
        
        int val1 = p1Card.getValue();
        int val2 = p2Card.getValue();
        if(((val1 == 2) && (val2 == 14)) || ((val1 ==14) && (val2 == 2))){
            caseAceAndTwo(p1Card, p2Card);
            return;
        }
        
        // Determine winner of the turn
        if (val1 > val2) {
            std::string docTurn = ply1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + ply2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + ply1.getName() + " Wins! \n";
            this->log.back() += docTurn;
            

            ply1.addTakenCard(p1Card);
            ply1.addTakenCard(p2Card);
            player1.addNumOfWins();
            
            //add cards to winner
            for(Card c : pile1){
                //cout<<c.getValue()<<endl;
                ply1.addTakenCard(c);
            }
            for(Card c : pile2){
                //cout<<c.getValue()<<endl;
                ply1.addTakenCard(c);
            }

        } else if (val2 > val1) {
            std::string docTurn = ply1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + ply2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + ply2.getName() + " Wins! \n";
            this->log.back() += docTurn;

            ply2.addTakenCard(p1Card);
            ply2.addTakenCard(p2Card);
            player2.addNumOfWins();
           
            for(Card c : pile1){
                //cout<<c.getValue()<<endl;
                ply2.addTakenCard(c);
            }
            for(Card c : pile2){
                //cout<<c.getValue()<<endl;
                ply2.addTakenCard(c);
            }

        }
        else {
            std::string docTurn = "\r" + player1.getName() + " played " + p1Card.strValue() + " of " + p1Card.getSuitString(p1Card.getSuit()) + " ,"
                            + player2.getName() + " played " + p2Card.strValue() + " of " + p2Card.getSuitString(p2Card.getSuit()) + " "
                            + "Draw! ";
            this->log.back() += docTurn;
            this->drawRate++;

            if(ply1.getHasCards() && ply2.getHasCards()){
                
                pile1.push_back(p1Card);
                pile2.push_back(p2Card);
                pile1.push_back(ply1.getTopCard());
                pile2.push_back(ply2.getTopCard());
                playWar(pile1,pile2, ply1, ply2);
            }
            else{//return cards to players
                ply1.addTakenCard(p1Card);
                ply1.addTakenCard(p2Card);
                //every player get his cards back.
                for(Card c : pile1){
                    ply1.addTakenCard(c);
                }
                for(Card c : pile2){
                    ply2.addTakenCard(c);
                }
                determinesWinner(ply1,ply2);
            }
        }
    }
    else{//in this case we got in each pile one card upside down but one or buth player has no cards
        //so thet will get there cards back
        for(Card c : pile1){
            ply1.addTakenCard(c);
        }
        for(Card c : pile2){
            ply2.addTakenCard(c);
        }
        determinesWinner(ply1,ply2);
    }
   
    
};

void Game :: addLog(std::string log)
{
    this->log.push_back(log);
};

void Game :: printLastTurn()
{
    cout << this->log.back() << endl;
};

void Game :: playAll()
{
    if(player1.getIsWinner() || player2.getIsWinner() || this->isDraw){
            throw std :: runtime_error("Game is over!*");
    }
    
    while(player1.getHasCards() && player2.getHasCards()){

        playTurn();
        
    }
    //for deteminig the winner
    determinesWinner(player1,player2);
   
    
};

void Game :: printWiner()
{
    if(!player1.getIsWinner() && !player2.getIsWinner() && !this->isDraw){
        //throw std :: runtime_error("Game is NOT over!*");
    }
    if (player1.getIsWinner())
    {
         cout<< player1.getName() << " is the winner in the Game!\n" << endl; 
    }
    else if (player2.getIsWinner())
    {
        cout << player2.getName() << " is the winner in the Game!\n" << endl;
    }
    else if(this->isDraw){
        throw std :: runtime_error("Game is Drow!*");
    }

    else
    {
        
        cout << "FIX CODE !\n" << endl;
    }
    
   
};

void Game :: printLog()
{
    for (std::string s : this->log)
    {
        cout << s << endl;
    }
};

void Game :: printStats()
{
    printf("\n%s Stats:\n\n", player1.getName().c_str());
    cout << player1.getName() << " Win rate: " << player1.getNumOfWins() << "/" << this->log.size() << endl;
    cout <<player1.getName() << " won cards: " << player1.cardesTaken()<< endl;


    printf("\n%s Stats:\n\n", player2.getName().c_str());
    cout << player2.getName() << " Win rate: " << player2.getNumOfWins() << "/" << this->log.size() << endl;
    cout <<player2.getName() << " won cards: " << player2.cardesTaken()<< endl;

    printf("\nGame Stats:\n\n");
    cout << "Total turns: " << this->log.size() << endl;
    cout << "Draw rate: " << this->drawRate << "/" << this->log.size() << endl;
   
    
}; 
bool Game :: getIsDraw()
{
    return this->isDraw;
};

