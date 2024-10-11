#include "dumb_af_bot.hpp"
#include "card.hpp"
#include "belot.hpp"
#include "belot_common.hpp"

#include <stdint.h>
#include <stdlib.h>

int dumb_af_bot_init(void *state, int8_t player_id, const Card *hand, const Card *trick, const Card *previous_trick, const bid_t *bids)
{
  if (state == NULL || hand == NULL || trick == NULL || previous_trick == NULL || bids == NULL)
  {
    return -1;
  }

  dumb_af_bot_state_t *st = (dumb_af_bot_state_t *) state;

  st->player_id = player_id;
  st->hand = hand;
  st->trick = trick;
  st->previous_trick = previous_trick;
  st->bids = bids;
  st->game_mode = AllPass;
  st->all_trumps_announced = false;

  return 0;
}

bid_t dumb_af_bot_bid(void *state)
{
  if (state == NULL)
  {
    return BidNone;
  }

  dumb_af_bot_state_t *st = (dumb_af_bot_state_t *) state;

  // 30 godini TUES, 30 godini vsichko koz!
  if (st->all_trumps_announced)
  {
    return BidPass;
  }
  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
  {
    if (st->bids[i] == BidAllTrumps)
    {
      st->all_trumps_announced = true;
      break;
    }
  }
  if (st->all_trumps_announced)
  {
    return BidPass;
  }
  else
  {
    st->all_trumps_announced = true;
    return BidAllTrumps;
  }
}

int dumb_af_bot_choose_card(void *state)
{
  if (state == NULL)
  {
    return -1;
  }

  card_suite_t requested_suite = InvalidSuite;
  dumb_af_bot_state_t *st = (dumb_af_bot_state_t *) state;
  card_suite_t trump_suite = game_mode_to_card_suite(st->game_mode);
  int8_t winning_card_id = st->player_id;

  // Determine the requested suite
  for (uint8_t i = 1; i < NUM_PLAYERS; i++)
  {
    if (st->trick[(st->player_id + i) % NUM_PLAYERS] != NO_CARD)
    {
      requested_suite = st->trick[(st->player_id + i) % NUM_PLAYERS].get_suite();
      winning_card_id = find_winning_card(st->trick, (st->player_id + i) % NUM_PLAYERS, st->game_mode);
      break;
    }
  }
  // Determine the strenght of the strongest card so far
  int winning_card_strenght = st->trick[winning_card_id].get_strength(st->game_mode);

  if (requested_suite != InvalidSuite)
  {
    // Find the first card that matches the suite and is stronger
    for (uint8_t i = 0; i < CARDS_PER_PLAYER; i++)
    {
      if (st->hand[i].get_suite() == requested_suite && st->hand[i].get_strength(st->game_mode) > winning_card_strenght)
      {
        return i;
      }
    }
    // Just throw the first card that matches the suite
    for (uint8_t i = 0; i < CARDS_PER_PLAYER; i++)
    {
      if (st->hand[i].get_suite() == requested_suite)
      {
        return i;
      }
    }
    if (trump_suite != InvalidSuite)
    {
      // Find the first card that matches the trump suite and is strong enough
      for (uint8_t i = 0; i < CARDS_PER_PLAYER; i++)
      {
        if (st->hand[i].get_suite() == trump_suite && st->hand[i].get_strength(st->game_mode) > winning_card_strenght)
        {
          return i;
        }
      }
    }
  }
  // Either we don't have a matching card or we are first in turn. In that case just throw the first card we have.
  for (uint8_t i = 0; i < CARDS_PER_PLAYER; i++)
  {
    if (st->hand[i] != NO_CARD)
    {
      return i;
    }
  }

  // We're out of cards! This shouldn't happen.
  return -2;
}

int dumb_af_bot_set_game_mode(void *state, game_mode_t game_mode)
{
  if (state == NULL)
  {
    return -1;
  }

  ((dumb_af_bot_state_t *) state)->game_mode = game_mode;

  return 0;
}
