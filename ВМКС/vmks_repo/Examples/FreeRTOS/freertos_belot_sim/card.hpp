#ifndef CARD_H
#define CARD_H

#include "belot_common.hpp"

#define NUM_OF_SUITES 4
#define NUM_OF_VALUES 8

typedef enum __attribute__((packed))
{
  Clubs = 0,
  Diamonds = 1,
  Hearts = 2,
  Spades = 3,
  InvalidSuite
}
card_suite_t;

typedef enum __attribute__((packed))
{
  Seven = 0,
  Eight = 1,
  Nine = 2,
  Ten = 3,
  Jack = 4,
  Queen = 5,
  King = 6,
  Ace = 7,
  InvalidValue
}
card_value_t;

class Card
{
  private:
    card_suite_t suite;
    card_value_t value;

  public:
    Card();
    Card(card_suite_t suite_init, card_value_t value_init);
    card_suite_t get_suite() const;
    card_value_t get_value() const;
    int get_strength(game_mode_t gamemode) const;
    int get_points(game_mode_t gamemode) const;
    int print(char *buf) const;
    friend bool operator==(const Card lhs, const Card rhs);
    friend bool operator!=(const Card lhs, const Card rhs);
};

extern const Card NO_CARD;

card_suite_t game_mode_to_card_suite(game_mode_t game_mode);

#endif
