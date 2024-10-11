#ifndef DECK_H
#define DECK_H

#include "card.hpp"

#include <cstddef>

#define DECK_SIZE (NUM_OF_SUITES * NUM_OF_VALUES)

class Deck
{
  private:
    // Ring buffer
    Card cards[DECK_SIZE];
    size_t start;
    size_t end;
    size_t remaining;

  public:
    Deck();
    int draw(Card *card_ptr);
    int draw_multiple(Card *cards_buf, size_t num_cards);
    int add(Card *card_ptr);
    int add_multiple(Card *cards_buf, size_t num_cards);
    void shuffle();
    void split();
    int print(char *buf);
};

#endif
