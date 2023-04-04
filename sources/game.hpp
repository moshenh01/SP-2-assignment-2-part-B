#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <iostream>
#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

    class Game{

        public:
        Game(Player& player1, Player& player2);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void addLog(string log);
        void playWar(vector<Card> pile1,vector<Card> pile2,Player& ply1,Player& ply2);
        void caseAceAndTwo(Card p1Card, Card p2Card);
        void determinesWinner(Player& player1, Player& player2);
        bool getIsDraw();
        

        private:
        Player& player1;
        Player& player2;
        vector<std::string> log;
        int drawRate;
        bool isDraw;
    };


#endif
