#include "belot.hpp"
#include "belot_common.hpp"
#include "card.hpp"
#include "player.hpp"
#include "dumb_af_bot.hpp"

#include <stdlib.h>

#define THREAD_STACK_SIZE 2048
#define PLAYERS 6
#define NOISE_PIN 34

typedef struct
{
  int (*bot_init)(void *state, int8_t player_id, const Card *hand, const Card *trick, const Card *previous_trick, const bid_t *bids);
  bid_t (*bot_bid)(void *state);
  int (*bot_choose_card)(void *state);
  int (*bot_set_game_mode)(void *state, game_mode_t game_mode);
  void *bot_state;
}
player_args_t;

static void play_belot(void *pvParameters);
static void think_really_hard(void);

SemaphoreHandle_t uart_mutex = xSemaphoreCreateMutex();

static Belot *lobby = NULL;
static SemaphoreHandle_t lobby_mutex;

static const char *player_names[PLAYERS] = {"Asen", "Boris", "Violeta", "Georgi", "Dimitar", "Elena"};
static TaskHandle_t player_handles[PLAYERS];
static const size_t bot_state_sizes[PLAYERS] = {DUMB_AF_BOT_STATE_SIZE, DUMB_AF_BOT_STATE_SIZE, DUMB_AF_BOT_STATE_SIZE, DUMB_AF_BOT_STATE_SIZE, DUMB_AF_BOT_STATE_SIZE, DUMB_AF_BOT_STATE_SIZE};
static player_args_t player_args[PLAYERS] =
{
  {.bot_init = dumb_af_bot_init, .bot_bid = dumb_af_bot_bid, .bot_choose_card = dumb_af_bot_choose_card, .bot_set_game_mode = dumb_af_bot_set_game_mode, .bot_state = NULL},
  {.bot_init = dumb_af_bot_init, .bot_bid = dumb_af_bot_bid, .bot_choose_card = dumb_af_bot_choose_card, .bot_set_game_mode = dumb_af_bot_set_game_mode, .bot_state = NULL},
  {.bot_init = dumb_af_bot_init, .bot_bid = dumb_af_bot_bid, .bot_choose_card = dumb_af_bot_choose_card, .bot_set_game_mode = dumb_af_bot_set_game_mode, .bot_state = NULL},
  {.bot_init = dumb_af_bot_init, .bot_bid = dumb_af_bot_bid, .bot_choose_card = dumb_af_bot_choose_card, .bot_set_game_mode = dumb_af_bot_set_game_mode, .bot_state = NULL},
  {.bot_init = dumb_af_bot_init, .bot_bid = dumb_af_bot_bid, .bot_choose_card = dumb_af_bot_choose_card, .bot_set_game_mode = dumb_af_bot_set_game_mode, .bot_state = NULL},
  {.bot_init = dumb_af_bot_init, .bot_bid = dumb_af_bot_bid, .bot_choose_card = dumb_af_bot_choose_card, .bot_set_game_mode = dumb_af_bot_set_game_mode, .bot_state = NULL}
};

void setup()
{
  pinMode(NOISE_PIN, INPUT);
  //srandom(analogRead(NOISE_PIN));
  srandom(0);

  lobby_mutex = xSemaphoreCreateMutex();
  if (lobby_mutex == NULL)
  {
    big_oof();
  }

  Serial.begin(38400);
  // Without some delay here Arduino IDE misses the first output
  delay(1000);
  // We can skip taking and giving uart_mutex here because no other threads are running yet
  Serial.println("The lobby is open!");
  delay(1000);

  for (uint8_t i = 0; i < PLAYERS; i++)
  {
    if (bot_state_sizes[i])
    {
      player_args[i].bot_state = malloc(bot_state_sizes[i]);
      if (player_args[i].bot_state == NULL)
      {
        big_oof();
      }
    }
    if (xTaskCreate(play_belot, player_names[i], THREAD_STACK_SIZE, (void *) &player_args[i], 1, &player_handles[i]) != pdPASS)
    {
      big_oof();
    }
  }
}

void loop()
{}

static void play_belot(void *pvParameters)
{
  Player player = Player(pcTaskGetName(NULL));
  player_args_t *args = (player_args_t *) pvParameters;

  // Games loop
  while (true)
  {
    player.join_or_start_game(&lobby, lobby_mutex);

    int8_t id = player.get_id();
    // The following methods on the Player class return pointers, so the bot can save them in its state. This way there is no need to pass many arguments to the other bot functions.
    args->bot_init(args->bot_state, id, player.view_hand(), player.view_trick(), player.view_previous_trick(), player.view_bids());

    // Rounds loop
    while (true)
    {
      int8_t dealer_id = player.get_dealer_id();

      if (id == dealer_id)
      {
        player.deal_first();
      }
      else if ((id + 1) % NUM_PLAYERS == dealer_id)
      {
        player.split_deck();
      }
      player.collect_cards();
      while (!player.bidding_over())
      {
        player.bid(args->bot_bid(args->bot_state));
      }
      if (player.get_game_mode() == AllPass)
      {
        player.end_round();
        continue;
      }
      if (id == dealer_id)
      {
        player.deal_second();
      }
      player.collect_cards();
      args->bot_set_game_mode(args->bot_state, player.get_game_mode());
      // Tricks loop
      for (uint8_t i = 0; i < TRICKS_PER_GAME; i++)
      {
        think_really_hard();
        player.play_card(args->bot_choose_card(args->bot_state));
      }
      player.end_round();
    }
    player.end_game();
  }
}

static void think_really_hard(void)
{
  vTaskDelay(1000);
}
