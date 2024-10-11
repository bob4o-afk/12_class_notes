#define THREAD_STACK_SIZE   1024

static void say_name(__attribute__((unused)) void *args);
static void error(void);

SemaphoreHandle_t uart_mutex;

TaskHandle_t asen_handle = NULL;
TaskHandle_t boris_handle = NULL;

void setup()
{
  uart_mutex = xSemaphoreCreateMutex();
  if (uart_mutex == NULL)
  {
    error();
  }

  Serial.begin(115200);
  delay(1000);

  xTaskCreate(say_name, "Asen", THREAD_STACK_SIZE, NULL, 1, &asen_handle);
  xTaskCreate(say_name, "Boris", THREAD_STACK_SIZE, NULL, 1, &boris_handle);

  delay(1000);
  vTaskSuspend(asen_handle);
  vTaskSuspend(boris_handle);
}

void loop()
{}

static void say_name(__attribute__((unused)) void *args)
{
  char *name = pcTaskGetName(NULL);

  while (true)
  {
    //while (xSemaphoreTake(uart_mutex, portMAX_DELAY) != pdTRUE);
    Serial.print(name);
    Serial.println(" kazva Zdravei!");
    /*
    if (xSemaphoreGive(uart_mutex) != pdTRUE)
    {
      error();
    }
    */
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

static void error(void)
{
  while (true);
}
