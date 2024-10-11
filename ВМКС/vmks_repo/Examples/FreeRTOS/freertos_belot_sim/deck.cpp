#include "deck.hpp"
#include "card.hpp"

#include <cstddef>
#include <stdlib.h>
#include <string.h>

static const card_suite_t new_deck_suits[NUM_OF_SUITES] = {Hearts, Clubs, Diamonds, Spades};
static const card_value_t new_deck_values[NUM_OF_VALUES] = {Ace, /* Missing 2 - 6 */ Seven, Eight, Nine, Ten, Jack, Queen, King};

Deck::Deck()
{
  // Why the hell did I bother implementing a proper new deck order? It's not even correct, as cards 2 - 6 are missing!
  for (int i = 0; i < NUM_OF_VALUES; i++)
  {
    cards[i] = Card(new_deck_suits[0], new_deck_values[i]);
    cards[NUM_OF_VALUES + i] = Card(new_deck_suits[1], new_deck_values[i]);
    cards[2 * NUM_OF_VALUES + i] = Card(new_deck_suits[2], new_deck_values[NUM_OF_VALUES - i - 1]);
    cards[3 * NUM_OF_VALUES + i] = Card(new_deck_suits[3], new_deck_values[NUM_OF_VALUES - i - 1]);
  }

  start = 0;
  end = DECK_SIZE - 1;
  remaining = DECK_SIZE;
}

int Deck::draw(Card *card_ptr)
{
  if (card_ptr == NULL)
  {
    return -1;
  }
  if (remaining == 0)
  {
    return -2;
  }

  *card_ptr = cards[start];
  start = (start + 1) % DECK_SIZE;
  remaining--;

  return 0;
}

int Deck::draw_multiple(Card *cards_buf, size_t num_cards)
{
  if (cards_buf == NULL)
  {
    return -1;
  }
  if (remaining < num_cards)
  {
    return -2;
  }

  if (start + num_cards > DECK_SIZE)
  {
    size_t first_portion = num_cards - (start + num_cards) % DECK_SIZE;
    memcpy((void *) cards_buf, (const void *) (cards + start), first_portion * sizeof(Card));
    memcpy((void *) (cards_buf + first_portion), (const void *) cards, (num_cards - first_portion) * sizeof(Card));
  }
  else
  {
    memcpy((void *) cards_buf, (const void *) (cards + start), num_cards * sizeof(Card));
  }

  start = (start + num_cards) % DECK_SIZE;
  remaining -= num_cards;

  return 0;
}

int Deck::add(Card *card_ptr)
{
  if (card_ptr == NULL)
  {
    return -1;
  }
  if (remaining >= DECK_SIZE)
  {
    return -2;
  }

  end = (end + 1) % DECK_SIZE;
  cards[end] = *card_ptr;
  remaining++;

  return 0;
}

int Deck::add_multiple(Card *cards_buf, size_t num_cards)
{
  if (cards_buf == NULL)
  {
    return -1;
  }
  if (remaining > DECK_SIZE - num_cards)
  {
    return -2;
  }

  if (end + num_cards >= DECK_SIZE)
  {
    size_t first_portion = num_cards - (end + 1 + num_cards) % DECK_SIZE;
    memcpy((void *) (cards + end), (const void *) cards_buf, first_portion * sizeof(Card));
    memcpy((void *) cards, (const void *) (cards_buf + first_portion), (num_cards - first_portion) * sizeof(Card));
  }
  else
  {
    memcpy((void *) (cards + end), (const void *) cards_buf, num_cards * sizeof(Card));
  }

  end = (end + num_cards) % DECK_SIZE;
  remaining += num_cards;

  return 0;
}

// Uses the Fisher–Yates algorithm
void Deck::shuffle()
{
  Card buf;
  size_t pos;

  for (int i = remaining; i > 0; i--)
  {
    // random is NOT thread-safe but using it here is fine because only one thread modifies the deck at a time (the dealer)
    pos = (size_t) random() % i;
    buf = cards[(start + i) % DECK_SIZE];
    cards[(start + i) % DECK_SIZE] = cards[(start + pos) % DECK_SIZE];
    cards[(start + pos) % DECK_SIZE] = buf;
  }
}

// Moving the start and end counters without copying any cards can have the same effect but I've implemented it this way for the sake of realism
void Deck::split()
{
  Card buf[DECK_SIZE];
  // random is NOT thread-safe but using it here is fine because only one thread modifies the deck at a time (the dealer)
  size_t pos = (size_t) random() % remaining;
  draw_multiple(buf, pos);
  add_multiple(buf, pos);
}

// Requires at least 577 bytes of buffer
int Deck::print(char *buf)
{
  char card_text[18];
  size_t pos = 0;

  for (uint8_t i = 0; i < DECK_SIZE; i++)
  {
    cards[i].print(card_text);
    strcpy(buf + pos, card_text);
    pos += strlen(card_text);
    buf[pos] = '\n';
    pos++;
  }

  return 0;
}
