#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <fstream>

namespace ariel{
    class Card{
        public:
        enum Suit{
            CLUBS,
            DIAMONDS,
            HEARTS,
            SPADES
        };
        private:
            int value;
            Suit suit;

        public:
            Card(int value, Suit suit);
            
            int getValue();
            Suit getSuit();
            std::string getSuitString(Suit suit);
            void printCard();
            std::string strValue();
              
            static std::string strSuit(Suit suit){
                switch(suit) {
                    case HEARTS:
                        return "Hearts";
                    case DIAMONDS:
                        return "Diamonds";
                    case SPADES:
                        return "Spades";
                    case CLUBS:
                        return "Clubs";
                    default:
                        return "";
                }
            }
    };
}
#endif // CARD_HPP