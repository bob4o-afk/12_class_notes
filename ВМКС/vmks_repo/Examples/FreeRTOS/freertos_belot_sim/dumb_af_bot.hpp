#ifndef DUMB_AF_BOT_H
#define DUMB_AF_BOT_H

#include "card.hpp"
#include "belot.hpp"
#include "belot_common.hpp"

#include <stdint.h>

#define DUMB_AF_BOT_STATE_SIZE sizeof(dumb_af_bot_state_t)

typedef struct
{
  game_mode_t game_mode;
  int8_t player_id;
  const Card *hand;
  const Card *trick;
  const Card *previous_trick;
  const bid_t *bids;
  bool all_trumps_announced;
  //other stuff
}
dumb_af_bot_state_t;

int dumb_af_bot_init(void *state, int8_t player_id, const Card *hand, const Card *trick, const Card *previous_trick, const bid_t *bids);
bid_t dumb_af_bot_bid(void *state);
int dumb_af_bot_choose_card(void *state);
int dumb_af_bot_set_game_mode(void *state, game_mode_t game_mode);

#endif