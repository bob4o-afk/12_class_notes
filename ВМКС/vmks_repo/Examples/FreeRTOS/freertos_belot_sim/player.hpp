#ifndef PLAYER_H
#define PLAYER_H

#include "belot.hpp"
#include "card.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include <stdint.h>

class Player
{
  private:
    const char *name;
    int8_t player_id;
    Belot *game;
    bool created_game;
    uint8_t cards_received;
    QueueHandle_t card_input;
    SemaphoreHandle_t turn_semaphor;
    Card hand[CARDS_PER_PLAYER];

    void wait_for_turn();
    int deal_two();
    int deal_three();
  
  public:
    Player(const char *name);
    ~Player();
    int join_or_start_game(Belot **lobby, SemaphoreHandle_t lobby_mutex);
    int end_game();
    int8_t get_id();
    int8_t get_dealer_id();
    void split_deck();
    int deal_first();
    int deal_second();
    void end_turn();
    void collect_cards();
    const Card *view_hand();
    const bid_t *view_bids();
    int bid(bid_t bid);
    bool bidding_over();
    game_mode_t get_game_mode();
    void end_round();
    const Card *view_trick();
    const Card *view_previous_trick();
    int play_card(uint8_t card_num);
};

#endif