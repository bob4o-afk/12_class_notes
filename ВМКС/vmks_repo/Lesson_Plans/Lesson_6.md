# --- Тема 6 ---

Дата на провеждане 22.10.2021

Теми: Работа с регистри и външни прекъсвания. Подробно разглеждане на вътрешната структура на микроконтролер ATMega328P.

## План на часа
- Преговор
	* Ядро
	* Регистри на ядрото
	* Задача мигащ светодиод с регистри - GitLab Repo -> Examples/Register_Blink
	* Прекъсвания теория
	* [Външни прекъсвания](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
	* Задача бутон да сменя състоянието на светодиод - GitLab Repo -> Examples/
		- Реално приложение (веднага сменя състоянието на светодиода но извежда съобщение когато успее) -> External_interrupt
		- Прост пример за toggle на светодиод с бутон -> EXTI_Demo
		- Пример за toggle на светодиод с бутон (като EXTI_Demo но само с регистри) -> EXTI0_Register_Demo
- RTuinoOS пример за context switching (https://github.com/PeterVranken/RTuinOS)
- FreeRTOS пример за реална програма (мигащ светодиод и четене на потенциометър)
- Таймери
	* Какво представляват
	* Как работят

-----

### Допълнително:
Как се използва ШИМ сигнал с analogWrite -> https://www.arduino.cc/en/Tutorial/Foundations/PWM
Разликата между проене нагоре/надолу/двете -> https://www.mathworks.com/help/physmod/sps/ref/pwmgenerator.html
Тук има документация за delay функциите(и не само) който са от самия пакет библиотеки на компилатора (avr-gcc)
	-> https://www.nongnu.org/avr-libc/user-manual/group__util__delay.html


Всяка ардуино програма има `main.c` файл в който опростено изглежда така:
```C++
#include "Arduino.h"


void main()
{
  init();
  setup();
  
  while(1)
  {
    loop();
    checkUART();
  }
}
```

Тези файлове може да намерите и разгледате в GitLab в папка Other Useful Files
или направо от файловете на вашия компютър (пътищата са примерни за Windows x64 за Linux вижте в интернет къде са):
`..\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino`
`..\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.3\cores\arduino`


```C++
void _delay_ms(uint16_t i)
{
    i *= 4000;
  for(; i > 0 ; i++){}
}
```

Това което ви показах в час (горното) беше опростен пример за `delay()` функцията показващ как тя работи, а истинските функции за изчакване може да намерите във файлове `delay.h` и `delay_basic.h` в директория на Arduino IDE-то (пътищата са примерни за Windows x64, за Linux вижте в интернет къде са):
`..\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\util`
`..\AppData\Local\Arduino15\packages\arduino\tools\avr-gcc\4.8.1-arduino5\avr\include\util`
`..\AppData\Local\Arduino15\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7\avr\include\util`
Разликата е че са частично на асемблер и има сметки за броя цикли, така че да може да подавате променливи.