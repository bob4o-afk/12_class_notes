#include "freertos/projdefs.h"
#include "player.hpp"
#include "belot.hpp"
#include "belot_common.hpp"
#include "card.hpp"
#include "debug.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include <stdint.h>

Player::Player(const char *new_name) : player_id{-1}, game{NULL}, created_game{false}, cards_received{0}
{
  // Not a big deal if name is NULL, Serial.print does check for NULL pointers.
  // Constructors can't return an error and I just can't be bothered with C++ exceptions for this.
  name = new_name;
  card_input = xQueueCreate(CARDS_PER_PLAYER, sizeof(Card));
  turn_semaphor = xSemaphoreCreateBinary();

  if (card_input == NULL || turn_semaphor == NULL)
  {
    big_oof();
  }

  for (uint8_t i = 0; i < CARDS_PER_PLAYER; i++)
  {
    hand[i] = Card();
  }
}

Player::~Player()
{
  vQueueDelete(card_input);
  vSemaphoreDelete(turn_semaphor);
}

void Player::wait_for_turn()
{
  while (xSemaphoreTake(turn_semaphor, portMAX_DELAY) != pdTRUE);
}

int Player::join_or_start_game(Belot **lobby, SemaphoreHandle_t lobby_mutex)
{
  if (lobby == NULL || lobby_mutex == NULL)
  {
    return -1;
  }

  #ifdef DEBUG
  while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
  Serial.print(name);
  Serial.println(" entered the lobby.");
  if (xSemaphoreGive(uart_mutex) != pdTRUE)
  {
    big_oof();
  }
  #endif

  while (player_id < 0)
  {
    if (xSemaphoreTake(lobby_mutex, portMAX_DELAY) == pdTRUE)
    {
      if (*lobby == NULL)
      {
        // No existing game, create a new one
        try
        {
          game = new Belot;
          *lobby = game;
        }
        catch (__attribute__((unused)) int err)
        {
          big_oof();
        }
        created_game = true;
        player_id = game->join(name, card_input, turn_semaphor);
      }
      else
      {
        game = *lobby;
        player_id = game->join(name, card_input, turn_semaphor);
      }
      if (xSemaphoreGive(lobby_mutex) != pdTRUE)
      {
        big_oof();
      }
    }
  }

  // Wait for enough players to join
  wait_for_turn();
  // If you created the game, free the lobby
  if (created_game)
  {
    while (xSemaphoreTake(lobby_mutex, portMAX_DELAY) != pdTRUE);
    *lobby = NULL;
    if (xSemaphoreGive(lobby_mutex) != pdTRUE)
    {
      big_oof();
    }
  }
  
  return 0;
}

int Player::end_game()
{
  if (game == NULL)
  {
    return -1;
  }

  if (created_game)
  {
    delete game;
  }
  game = NULL;
  created_game = false;
  player_id = -1;

  return 0;
}

int8_t Player::get_id()
{
  return player_id;
}

int8_t Player::get_dealer_id()
{
  return game->get_dealer_id();
}

void Player::split_deck()
{
  #ifdef DEBUG
  while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
  Serial.print(name);
  Serial.print("(");
  Serial.print(player_id);
  Serial.print(")");
  Serial.println(" splits the deck.");
  if (xSemaphoreGive(uart_mutex) != pdTRUE)
  {
    big_oof();
  }
  #endif
  game->split_deck();
  end_turn();
}

int Player::deal_two()
{
  Card buf[2];

  #ifdef DEBUG
  while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
  Serial.print(name);
  Serial.print("(");
  Serial.print(player_id);
  Serial.print(")");
  Serial.println(" deals 2 cards to each player.");
  if (xSemaphoreGive(uart_mutex) != pdTRUE)
  {
    big_oof();
  }
  #endif

  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
  {
    if (game->draw_cards(buf, 2))
    {
      return -1;
    }
    if (game->give_cards_to_player(buf, 2, (player_id + i) % NUM_PLAYERS))
    {
      return -2;
    }
  }
  
  return 0;
}

int Player::deal_three()
{
  Card buf[3];

  #ifdef DEBUG
  while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
  Serial.print(name);
  Serial.print("(");
  Serial.print(player_id);
  Serial.print(")");
  Serial.println(" deals 3 cards to each player.");
  if (xSemaphoreGive(uart_mutex) != pdTRUE)
  {
    big_oof();
  }
  #endif

  for (uint8_t i = 0; i < NUM_PLAYERS; i++)
  {
    if (game->draw_cards(buf, 3))
    {
      return -1;
    }
    if (game->give_cards_to_player(buf, 3, (player_id + i) % NUM_PLAYERS))
    {
      return -2;
    }
  }
  
  return 0;
}

int Player::deal_first()
{
  int error_code = deal_three();
  error_code += deal_two();
  end_turn();
  return error_code;
}

int Player::deal_second()
{
  int error_code = deal_three();
  end_turn();
  return error_code;
}

void Player::end_turn()
{
  game->signal_next_player();
  wait_for_turn();
}

void Player::collect_cards()
{
  while (cards_received < CARDS_PER_PLAYER && xQueueReceive(card_input, &hand[cards_received], 0) == pdTRUE)
  {
    cards_received++;
  }
}

const Card *Player::view_hand()
{
  return (const Card *) hand;
}

const bid_t *Player::view_bids()
{
  return game->view_bids();
}

int Player::bid(bid_t bid)
{
  #ifdef DEBUG
  while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
  Serial.print(name);
  Serial.print("(");
  Serial.print(player_id);
  Serial.print(")");
  switch (bid)
  {
    case BidPass: Serial.println(": pass"); break;
    case BidNoTrumps: Serial.println(": no trumps"); break;
    case BidClubs: Serial.println(": clubs"); break;
    case BidDiamonds: Serial.println(": diamonds"); break;
    case BidHearts: Serial.println(": hearts"); break;
    case BidSpades: Serial.println(": spades"); break;
    case BidAllTrumps: Serial.println(": all trumps"); break;
    case BidContra: Serial.println(": contra"); break;
    case BidRecontra: Serial.println(": re-contra"); break;
    default: Serial.println(": "); break;
  }
  if (xSemaphoreGive(uart_mutex) != pdTRUE)
  {
    big_oof();
  }
  #endif
  int error_code = game->bid(bid, player_id);
  if (!error_code)
  {
    end_turn();
  }
  
  return error_code;
}

bool Player::bidding_over()
{
  return game->bidding_over();
}

game_mode_t Player::get_game_mode()
{
  return game->get_game_mode();
}

void Player::end_round()
{
  for (uint8_t i = 0; i < CARDS_PER_PLAYER; i++)
  {
    if (hand[i] != NO_CARD)
    {
      game->return_card(&hand[i]);
    }
  }

  end_turn();
}

const Card *Player::view_trick()
{
  return game->view_trick();
}

const Card *Player::view_previous_trick()
{
  return game->view_previous_trick();
}

int Player::play_card(uint8_t card_num)
{
  char card_text[20];

  if (card_num >= CARDS_PER_PLAYER)
  {
    return -1;
  }
  if (hand[card_num] == NO_CARD)
  {
    return -2;
  }

  hand[card_num].print(card_text);
  #ifdef DEBUG
  while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
  Serial.print(name);
  Serial.print("(");
  Serial.print(player_id);
  Serial.print(")");
  Serial.print(": ");
  Serial.println(card_text);
  if (xSemaphoreGive(uart_mutex) != pdTRUE)
  {
    big_oof();
  }
  #endif

  int error_code = game->play_card(&hand[card_num], player_id);
  if (!error_code)
  {
    end_turn();
  }
  
  return error_code;
}
