#define LED_ROW1 11  // Active HIGH | Inactive LOW
#define LED_ROW2 10 // Active HIGH | Inactive LOW
#define LED_ROW3 9  // Active HIGH | Inactive LOW
#define LED_COL1 8  // Active LOW  | Inactive HIGH
#define LED_COL2 7  // Active LOW  | Inactive HIGH
#define LED_COL3 6  // Active LOW  | Inactive HIGH

#define BTN_ROW1 A3 // Active OUTPUT-LOW | Inactive INPUT - PULLUP
#define BTN_ROW2 A4 // Active OUTPUT-LOW | Inactive INPUT - PULLUP
#define BTN_ROW3 A5 // Active OUTPUT-LOW | Inactive INPUT - PULLUP
#define BTN_COL1 A0 // Active OUTPUT-LOW | Inactive INPUT - PULLUP
#define BTN_COL2 A1 // Active OUTPUT-LOW | Inactive INPUT - PULLUP
#define BTN_COL3 A2 // Active OUTPUT-LOW | Inactive INPUT - PULLUP

const uint8_t led_col[3] = {LED_COL1, LED_COL2, LED_COL3};
const uint8_t led_row[3] = {LED_ROW1, LED_ROW2, LED_ROW3};

const uint8_t btn_col[3] = {BTN_COL1, BTN_COL2, BTN_COL3};
const uint8_t btn_row[3] = {BTN_ROW1, BTN_ROW2, BTN_ROW3};

uint8_t state_1[3][3] =
{
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

void setup()
{
  int i = 0;

  for (i = 0; i < 3; i++)
  {
    pinMode(led_row[i], OUTPUT);
    digitalWrite(led_row[i], LOW);
    pinMode(led_col[i], OUTPUT);
    digitalWrite(led_col[i], HIGH);

    pinMode(btn_row[i], INPUT_PULLUP);
    pinMode(btn_col[i], INPUT_PULLUP);
  }
}

void loop()
{
  // Button scan
  for (byte col = 0; col < 3; col++)
  {
    pinMode(btn_col[col], OUTPUT);
    digitalWrite(btn_col[col], LOW);
    for (byte row = 0; row < 3; row++)
    {
      state_1[row][col] = !digitalRead(btn_row[row]);
    }
    pinMode(btn_col[col], INPUT_PULLUP);
  }

  // Transpose
  for (int i = 0; i < 3; i++)
  {
    for (int j = i + 1; j < 3; j++)
    {
      int temp;
      temp = state_1[i][j];
      state_1[i][j] = state_1[j][i];
      state_1[j][i] = temp;
    }
  }

  // LED update
  for (byte col = 0; col < 3; col++)
  {
    for (byte row = 0; row < 3; row++)
    {
      digitalWrite(led_row[row], state_1[row][col]);
    }
    digitalWrite(led_col[col], LOW);
    delay(5);
    digitalWrite(led_col[col], HIGH);
    for (byte row = 0; row < 3; row++)
    {
      digitalWrite(led_row[row], LOW);
    }
  }
}
