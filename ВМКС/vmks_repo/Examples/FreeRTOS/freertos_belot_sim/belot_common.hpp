#ifndef BELOT_COMMON_H
#define BELOT_COMMON_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <HardwareSerial.h>

typedef enum
{
  AllPass,
  ClubsTrump,
  DiamondsTrump,
  HeartsTrump,
  SpadesTrump,
  NoTrumps,
  AllTrumps
}
game_mode_t;

// Executes if we encounter an unrecoverable error. Not necessarily an out-of-memory error.
static inline void big_oof(void)
{
  vTaskSuspendAll();
  Serial.println("\nNema RAM! Susipaha go toia mikrokontroler...");
  while (true);
}

#endif
