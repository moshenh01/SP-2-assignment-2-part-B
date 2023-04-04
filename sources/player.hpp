#ifndef PLAYER_HPP
#define PLAYER_HPP 

    #include <string>
    #include <iostream>
    #include <vector>
    #include "card.hpp"

    using namespace std;
    using namespace ariel;

    class Player{
        private:
        string name;
        vector<Card> handCards;
        vector<Card> takenCards;
        bool isWinner;
        bool hasCards;
        int numOfWins;
        


        public:
        Player(string name);
        int stacksize();
        int cardesTaken();
        void addCard(const Card& card);
        void addTakenCard(const Card& card);
        Card getTopCard();
        string getName();
        bool getHasCards(); 
        void setHasCards(bool hasCards);
        bool getIsWinner();
        void setIsWinner(bool isWinner);
        int getNumOfWins();
        void setNumOfWins(int numOfWins);
        void addNumOfWins();

        

        
    };



#endif // PLAYER_HPP