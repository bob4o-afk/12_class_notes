#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 6
#define MIN_DELAY 30

#define TOP_ROW 2
#define MID_ROW 3
#define BOT_ROW 4
#define UP_BUTTON 6
#define DOWN_BUTTON 5
#define NOISE A0

#define PLAYER 1
#define CAR 2
#define EMPTY 0
#define CRASH 3

Adafruit_NeoPixel top_row(NUM_PIXELS, TOP_ROW, NEO_GRB);
Adafruit_NeoPixel mid_row(NUM_PIXELS, MID_ROW, NEO_GRB);
Adafruit_NeoPixel bot_row(NUM_PIXELS, BOT_ROW, NEO_GRB);

// Video RAM - every element corresponds to one pixel
int vram[3][NUM_PIXELS] = {{0}};  // 2 - TOP, 1 - MID, 0 - BOT
int player_pos = 1;
int next_car_in = 1;
int delay_time = 500;
int crashed = 0;

void setup()
{
  pinMode(TOP_ROW, OUTPUT);
    pinMode(MID_ROW, OUTPUT);
    pinMode(BOT_ROW, OUTPUT);
    pinMode(UP_BUTTON, INPUT);
    pinMode(DOWN_BUTTON, INPUT);
    pinMode(NOISE, INPUT);
    
    // LED strip initialization
    top_row.begin();
    mid_row.begin();
    bot_row.begin();
  
    // set the seed for the random number generator
    int seed = analogRead(NOISE) * 42;
    randomSeed(seed);
  
    Serial.begin(9600);
}

void loop()
{
    int i;
    int new_car;
    
    // update player position
  if (digitalRead(UP_BUTTON) == HIGH)
    {
        player_pos++;
    }
    else if (digitalRead(DOWN_BUTTON) == HIGH)
    {
        player_pos--;
    }
    if (player_pos > 2)
    {
      player_pos = 2;
    }
    else if (player_pos < 0)
    {
      player_pos = 0;
    }
    
    // draw the player
    for (i = 0; i < 3; i++)
    {
        if (player_pos == i)
        {
            // detect collision
            if (vram[i][1] == CAR)
            {
              vram[i][0] = CRASH;
                crashed = 1;
            }
            else
            {
              vram[i][0] = PLAYER;
            }
        }
        else
        {
            vram[i][0] = vram[i][1];
        }
    }
  
    // move everything one pixel to the left
    for (i = 1; i < (NUM_PIXELS - 1); i++)
    {
        vram[0][i] = vram[0][i + 1];
        vram[1][i] = vram[1][i + 1];
        vram[2][i] = vram[2][i + 1];
    }
    
    // generate next car
    for (i = 0; i < 3; i++)
    {
        vram[i][NUM_PIXELS - 1] = EMPTY;
    }
    next_car_in--;
    if (next_car_in == 0)
    {
        new_car = random(3);
        vram[new_car][NUM_PIXELS - 1] = CAR;
        next_car_in = 3;
    }
    
    // render the image
    // Note: this was originally made for a couple of younger kids who hadn't learned about switch-case yet
    for (i = 0; i < NUM_PIXELS; i++)
    {
        if (vram[0][i] == EMPTY)
        {
          bot_row.setPixelColor(i, bot_row.Color(0, 0, 0));
        }
        else if (vram[0][i] == CAR)
        {
          bot_row.setPixelColor(i, bot_row.Color(0, 0, 255));
        }
        else if (vram[0][i] == PLAYER)
        {
          bot_row.setPixelColor(i, bot_row.Color(0, 255, 0));
        }
        else if (vram[0][i] == CRASH)
        {
          bot_row.setPixelColor(i, bot_row.Color(255, 0, 0));
        }
      
        if (vram[1][i] == EMPTY)
        {
          mid_row.setPixelColor(i, mid_row.Color(0, 0, 0));
        }
        else if (vram[1][i] == CAR)
        {
          mid_row.setPixelColor(i, mid_row.Color(0, 0, 255));
        }
        else if (vram[1][i] == PLAYER)
        {
          mid_row.setPixelColor(i, mid_row.Color(0, 255, 0));
        }
        else if (vram[1][i] == CRASH)
        {
          mid_row.setPixelColor(i, mid_row.Color(255, 0, 0));
        }
      
        if (vram[2][i] == EMPTY)
        {
          top_row.setPixelColor(i, top_row.Color(0, 0, 0));
        }
        else if (vram[2][i] == CAR)
        {
          top_row.setPixelColor(i, top_row.Color(0, 0, 255));
        }
        else if (vram[2][i] == PLAYER)
        {
          top_row.setPixelColor(i, top_row.Color(0, 255, 0));
        }
        else if (vram[2][i] == CRASH)
        {
          top_row.setPixelColor(i, top_row.Color(255, 0, 0));
        }
    }
    top_row.show();
    mid_row.show();
    bot_row.show();
    Serial.println(delay_time);
    // stop the game if crashed
    if (crashed)
    {
        while (1);
    }
    // delay before the next frame
    else
    {
        delay(delay_time);
    }
    // slowly make the game faster
    if (delay_time > MIN_DELAY)
    {
        delay_time--;
    }
} 
