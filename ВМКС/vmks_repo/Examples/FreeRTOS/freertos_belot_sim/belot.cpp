#include "freertos/projdefs.h"
#include "belot.hpp"
#include "belot_common.hpp"
#include "deck.hpp"
#include "card.hpp"
#include "debug.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include <stdint.h>
#include <HardwareSerial.h>

Belot::Belot() : deck(), game_mode{AllPass}, joined_players{0}, player_in_turn{0}, bid_winner{-1}, dealer{1}, multiplier{1}, pass_counter{0}, tricks_played{0}
{
  for (uint8_t i = 0; i < NUM_TEAMS; i++)
  {
    score_game[i] = 0;
    score_round[i] = 0;
  }

  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
  {
    player_names[i] = NULL;
    // Not sure what to do with these here. ¯\_(ツ)_/¯
    //player_card_inputs[i] = ;
    //player_turn_semaphors[i] = ;
    trick[i] = Card();
    previous_trick[i] = Card();
    bids[i] = BidNone;
  }

  deck.shuffle();
}

int8_t Belot::join(const char *name, QueueHandle_t card_input, SemaphoreHandle_t turn_semaphor)
{
  uint8_t player_id = joined_players;

  if (player_id >= NUM_PLAYERS)
  {
    return -1;
  }

  player_names[player_id] = name;
  player_card_inputs[player_id] = card_input;
  player_turn_semaphors[player_id] = turn_semaphor;

  joined_players++;

  if (joined_players == NUM_PLAYERS)
  {
    #ifdef DEBUG
    while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
    Serial.print(player_names[0]);
    Serial.print(" and ");
    Serial.print(player_names[2]);
    Serial.print(" started a game against ");
    Serial.print(player_names[1]);
    Serial.print(" and ");
    Serial.print(player_names[3]);
    Serial.println(".");
    if (xSemaphoreGive(uart_mutex) != pdTRUE)
    {
      big_oof();
    }
    #endif
    if (xSemaphoreGive(player_turn_semaphors[player_in_turn]) != pdTRUE)
    {
      big_oof();
    }
  }

  return player_id;
}

void Belot::signal_next_player()
{
  player_in_turn = (player_in_turn + 1) % NUM_PLAYERS;
  if (xSemaphoreGive(player_turn_semaphors[player_in_turn]) != pdTRUE)
  {
    big_oof();
  }
}

int8_t Belot::get_dealer_id()
{
  return dealer;
}

void Belot::split_deck()
{
  deck.split();
}

int Belot::draw_cards(Card *cards_buf, size_t num_cards)
{
  return deck.draw_multiple(cards_buf, num_cards);
}

int Belot::give_cards_to_player(Card *cards_buf, size_t num_cards, int8_t player_id)
{
  if (cards_buf == NULL)
  {
    return -1;
  }
  if (player_id < 0 || player_id >= NUM_PLAYERS)
  {
    return -2;
  }

  for (size_t i = 0; i < num_cards; i++)
  {
    if (xQueueSendToBack(player_card_inputs[player_id], &cards_buf[i], portMAX_DELAY) != pdTRUE)
    {
      return -3;
    }
  }

  return 0;
}

const bid_t *Belot::view_bids()
{
  return (const bid_t *) bids;
}

// TODO: contras can be overruled
int Belot::bid(bid_t bid, int8_t player_id)
{
  bid_t highest_bid = current_highest_bid();

  if (bid == BidNone)
  {
    return -1;
  }
  if (bid == BidPass)
  {
    bids[player_id] = bid;
    pass_counter++;
    if (bidding_over())
    {
      // When the curent player ends his turn, the player_in_turn counter will be incremented and the dealer will deal the last cards
      player_in_turn = (dealer + NUM_PLAYERS - 1) % NUM_PLAYERS;
    }
    return 0;
  }
  if (bid <= highest_bid)
  {
    return -2;
  }
  if (bid == BidContra)
  {
    multiplier = 2;
  }
  else if (bid == BidRecontra)
  {
    multiplier = 4;
  }
  else
  {
    switch (bid)
    {
      case BidNoTrumps: game_mode = NoTrumps; break;
      case BidClubs: game_mode = ClubsTrump; break;
      case BidDiamonds: game_mode = DiamondsTrump; break;
      case BidHearts: game_mode = HeartsTrump; break;
      case BidSpades: game_mode = SpadesTrump; break;
      case BidAllTrumps: game_mode = AllTrumps; break;
      default: break;
    }
    bid_winner = player_id;
  }
  bids[player_id] = bid;
  pass_counter = 0;

  return 0;
}

bid_t Belot::current_highest_bid()
{
  bid_t highest_bid = BidNone, next_bid;

  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
  {
    next_bid = bids[(dealer + 1 + i) % NUM_PLAYERS];
    if (next_bid > highest_bid)
    {
      highest_bid = next_bid;
    }
  }

  return highest_bid;
}

bool Belot::bidding_over()
{
  bid_t highest_bid = current_highest_bid();

  switch (highest_bid)
  {
    case BidNone: return false;
    case BidPass: return pass_counter == NUM_PLAYERS;
    default: return pass_counter == NUM_PLAYERS - 1;
  }
}

game_mode_t Belot::get_game_mode()
{
  return game_mode;
}

int Belot::return_card(Card *card)
{
  if (card == NULL)
  {
    return -1;
  }

  deck.add(card);
  *card = NO_CARD;

  return 0;
}

const Card *Belot::view_trick()
{
  return (const Card*) trick;
}

const Card *Belot::view_previous_trick()
{
  return (const Card*) previous_trick;
}

int Belot::play_card(Card *card, int8_t player_id)
{
  if (card == NULL)
  {
    return -1;
  }
  if (player_id < 0 || player_id >= NUM_PLAYERS)
  {
    return -2;
  }

  trick[player_id] = *card;
  return_card(card);

  if (trick[(player_id + 1) % NUM_PLAYERS] != NO_CARD)
  {
    int8_t winning_team = calculate_score_round((player_id + 1) % NUM_PLAYERS);

    #ifdef DEBUG
    while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
    Serial.print("\nScore:\nEven team - ");
    Serial.println(score_round[0]);
    Serial.print("Odd team - ");
    Serial.println(score_round[1]);
    Serial.println();
    if (xSemaphoreGive(uart_mutex) != pdTRUE)
    {
      big_oof();
    }
    #endif

    for (uint8_t i = 0; i < NUM_PLAYERS; i++)
    {
      trick[i] = NO_CARD;
    }

    tricks_played++;
    if (tricks_played == TRICKS_PER_GAME)
    {
      score_round[winning_team] += 10;
      tricks_played = 0;
      calculate_score_game();
    }
  }

  return 0;
}

int8_t Belot::calculate_score_round(uint8_t first_card)
{
  
  int8_t winning_player_id = find_winning_card(trick, first_card, game_mode);
  uint8_t winning_team = winning_player_id % 2;

  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
  {
    score_round[winning_team] += trick[i].get_points(game_mode);
    previous_trick[i] = trick[i];
    trick[i] = NO_CARD;
  }
  player_in_turn = (winning_player_id + NUM_PLAYERS - 1) % NUM_PLAYERS;

  return winning_team;
}

void Belot::calculate_score_game()
{
  // TODO
  while (true)
  {
    vTaskDelay(1000);
  }
}

int8_t find_winning_card(const Card *cards, uint8_t first_card, game_mode_t game_mode)
{
  if (cards == NULL)
  {
    return -1;
  }
  if (game_mode == AllPass)
  {
    return -2;
  }
  
  card_suite_t requested_suite = cards[first_card].get_suite();
  uint8_t highest_strenght = cards[first_card].get_strength(game_mode);
  uint8_t winning_card_num = first_card;

  for (uint8_t i = 1; i < NUM_PLAYERS; i++)
  {
    Card next_card = cards[(first_card + i) % NUM_PLAYERS];

    if (game_mode == NoTrumps || game_mode == AllTrumps)
    {
      if (next_card.get_suite() == requested_suite && next_card.get_strength(game_mode) > highest_strenght)
      {
        highest_strenght = next_card.get_strength(game_mode);
        winning_card_num = (first_card + i) % NUM_PLAYERS;
      }
    }
    else if (next_card.get_strength(game_mode) > highest_strenght)
    {
      highest_strenght = next_card.get_strength(game_mode);
      winning_card_num = (first_card + i) % NUM_PLAYERS;
    }
  }

  return winning_card_num;
}
