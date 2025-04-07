#define LED1 18
#define LED2 17

#define THREAD_STACK_SIZE 1024

typedef struct {
  uint32_t t;
  uint8_t pin;
} blink_args_t;

const blink_args_t args1 = { t: 1000 / portTICK_PERIOD_MS, pin: LED1 };
const blink_args_t args2 = { t: 3000 / portTICK_PERIOD_MS, pin: LED2 };


void blink(void *pvParameters);

TaskHandle_t blink1_handle = NULL;
TaskHandle_t blink2_handle = NULL;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  xTaskCreate(blink, "blink1", THREAD_STACK_SIZE, (void *const)&args1, 1, &blink1_handle);
  xTaskCreate(blink, "blink2", THREAD_STACK_SIZE, (void *const)&args2, 1, &blink2_handle);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

void blink(void *pvParameters) {
  blink_args_t *args = (blink_args_t *)pvParameters;

  while (1) {
    digitalWrite(args->pin, HIGH);
    vTaskDelay(args->t / 2);
    digitalWrite(args->pin, LOW);
    vTaskDelay(args->t / 2);
  }
}
