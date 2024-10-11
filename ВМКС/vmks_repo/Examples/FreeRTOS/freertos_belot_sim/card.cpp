#include "card.hpp"
#include "belot_common.hpp"

#include <string.h>
#include <stdint.h>
#include <cstddef>

const Card NO_CARD = Card(InvalidSuite, InvalidValue);

//                                                           7   8   9  10   J   Q   K   A  INVALID
static const int8_t no_trump_strenghts[NUM_OF_VALUES + 1] = {0,  1,  2,  6,  3,  4,  5,  7, -1};
static const int8_t trump_strenghts[NUM_OF_VALUES + 1]    = {8,  9, 14, 12, 15, 10, 11, 13, -1};
static const int8_t no_trump_points[NUM_OF_VALUES + 1]    = {0,  0,  0, 10,  2,  3,  4, 11, -1};
static const int8_t trump_points[NUM_OF_VALUES + 1]       = {0,  0, 14, 10, 20,  3,  4, 11, -1};

Card::Card() : suite{InvalidSuite}, value{InvalidValue}
{}

Card::Card(card_suite_t suite_init, card_value_t value_init) : suite{suite_init}, value{value_init}
{}

card_suite_t Card::get_suite() const
{
  return suite;
}

card_value_t Card::get_value() const
{
  return value;
}

int Card::get_strength(game_mode_t gamemode) const
{
  switch (gamemode)
  {
    case NoTrumps: return no_trump_strenghts[(size_t) value];
    case ClubsTrump: return suite == Clubs ? trump_strenghts[(size_t) value] : no_trump_strenghts[(size_t) value];
    case DiamondsTrump: return suite == Diamonds ? trump_strenghts[(size_t) value] : no_trump_strenghts[(size_t) value];
    case HeartsTrump: return suite == Hearts ? trump_strenghts[(size_t) value] : no_trump_strenghts[(size_t) value];
    case SpadesTrump: return suite == Spades ? trump_strenghts[(size_t) value] : no_trump_strenghts[(size_t) value];
    case AllTrumps: return trump_strenghts[(size_t) value];
    default: return -2;
  }
}

int Card::get_points(game_mode_t gamemode) const
{
  switch (gamemode)
  {
    case NoTrumps: return no_trump_points[(size_t) value];
    case ClubsTrump: return suite == Clubs ? trump_points[(size_t) value] : no_trump_points[(size_t) value];
    case DiamondsTrump: return suite == Diamonds ? trump_points[(size_t) value] : no_trump_points[(size_t) value];
    case HeartsTrump: return suite == Hearts ? trump_points[(size_t) value] : no_trump_points[(size_t) value];
    case SpadesTrump: return suite == Spades ? trump_points[(size_t) value] : no_trump_points[(size_t) value];
    case AllTrumps: return trump_points[(size_t) value];
    default: return -2;
  }
}

// Requires at least 18 bytes of buffer
int Card::print(char *buf) const
{
  const char *value_text = NULL;
  const char *suite_text = NULL;

  if (buf == NULL)
  {
    return -1;
  }

  switch (value)
  {
    case Seven: value_text = "Seven"; break;
    case Eight: value_text = "Eight"; break;
    case Nine: value_text = "Nine"; break;
    case Ten: value_text = "Ten"; break;
    case Jack: value_text = "Jack"; break;
    case Queen: value_text = "Queen"; break;
    case King: value_text = "King"; break;
    case Ace: value_text = "Ace"; break;
    default: value_text = ""; break;
  }
  switch (suite)
  {
    case Clubs: suite_text = " of Clubs"; break;
    case Diamonds: suite_text = " of Diamonds"; break;
    case Hearts: suite_text = " of Hearts"; break;
    case Spades: suite_text = " of Spades"; break;
    default: suite_text = ""; break;
  }
  strcpy(buf, value_text);
  strcpy(buf + strlen(value_text), suite_text);

  return 0;
}

bool operator==(const Card lhs, const Card rhs)
{
  return (lhs.suite == rhs.suite && lhs.value == rhs.value);
}

bool operator!=(const Card lhs, const Card rhs)
{
  return (lhs.suite != rhs.suite || lhs.value != rhs.value);
}

card_suite_t game_mode_to_card_suite(game_mode_t game_mode)
{
  switch (game_mode)
  {
    case ClubsTrump: return Clubs;
    case DiamondsTrump: return Diamonds;
    case HeartsTrump: return Hearts;
    case SpadesTrump: return Spades;
    default: return InvalidSuite;
  }
}
