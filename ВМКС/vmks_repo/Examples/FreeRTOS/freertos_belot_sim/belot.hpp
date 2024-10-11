#ifndef BELOT_H
#define BELOT_H

#include "belot_common.hpp"
#include "deck.hpp"
#include "card.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include <stdint.h>

#define NUM_TEAMS         2
#define NUM_PLAYERS       4
#define CARDS_PER_PLAYER  8
#define TRICKS_PER_GAME   8

typedef enum
{
  BidNone = 0,
  BidPass = 1,
  BidClubs = 2,
  BidDiamonds = 3,
  BidHearts = 4,
  BidSpades = 5,
  BidNoTrumps = 6,
  BidAllTrumps = 7,
  BidContra = 8,
  BidRecontra = 9
}
bid_t;

class Belot
{
  private:
    Deck deck;
    game_mode_t game_mode;
    uint8_t joined_players;
    uint8_t player_in_turn;
    int8_t bid_winner;
    int8_t dealer;
    uint8_t multiplier;
    uint8_t pass_counter;
    uint8_t tricks_played;
    uint16_t score_game[NUM_TEAMS];
    uint16_t score_round[NUM_TEAMS];
    const char *player_names[NUM_PLAYERS];
    QueueHandle_t player_card_inputs[NUM_PLAYERS];
    SemaphoreHandle_t player_turn_semaphors[NUM_PLAYERS];
    Card trick[NUM_PLAYERS];
    Card previous_trick[NUM_PLAYERS];
    bid_t bids[NUM_PLAYERS];

    bid_t current_highest_bid();
    int8_t calculate_score_round(uint8_t first_card);
    void calculate_score_game();

  public:
    Belot();
    int8_t join(const char *name, QueueHandle_t card_input, SemaphoreHandle_t turn_semaphor);
    void signal_next_player();
    int8_t get_dealer_id();
    void split_deck();
    int draw_cards(Card *cards_buf, size_t num_cards);
    int give_cards_to_player(Card *cards_buf, size_t num_cards, int8_t player_id);
    const bid_t *view_bids();
    int bid(bid_t bid, int8_t player_id);
    bool bidding_over();
    game_mode_t get_game_mode();
    int return_card(Card *card);
    const Card *view_trick();
    const Card *view_previous_trick();
    int play_card(Card *card, int8_t player_id);
};

int8_t find_winning_card(const Card *cards, uint8_t first_card, game_mode_t game_mode);

#endif