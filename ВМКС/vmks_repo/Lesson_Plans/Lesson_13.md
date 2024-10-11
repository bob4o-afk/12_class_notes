# --- Тема 13 ---

Дата на провеждане 7.1.2022

Теми: Работа със 7-сегментен индикатор. Светодиоди и гама корекция.

## План на часа
- Какво е гама корекция и с какво е полезна - нелинейност на човешкото око
- [Как се прави гама корекция - формули](https://hackaday.com/2016/08/23/rgb-leds-how-to-master-gamma-and-hue-for-perfect-brightness/)
- Задачи  
	1. Гама корекция при димиране на единичен светодиод с PWM [PWM_Gamma_Correction](https://gitlab.com/tues-embedded/vmks/-/blob/master/Examples/PWM_Gamma_Correction/PWM_Gamma_Correction.ino)
	2. Гама корекция при димиране на светодиод WS2812 "NeoPixel" [RGB_Gamma_Correction](https://gitlab.com/tues-embedded/vmks/-/blob/master/Examples/RGB_Gamma_Correction/RGB_Gamma_Correction.ino)

Присъствено

-----

### Допълнително:

Гама корекция при преливане между два цвята на светодиод WS2812 "NeoPixel" [RGB_Gamma_Correction_Multicolor](https://gitlab.com/tues-embedded/vmks/-/blob/master/Examples/RGB_Gamma_Correction_Multicolor/RGB_Gamma_Correction_Multicolor.ino) - червено-жълто-зелено-жълто-червено, като за пример тук съм използвал LUT за да може да не се изчислява гама корекцията run-time и може да се ползва дробно число за гама коефициента, като съм ви качил и код за [генериране на Look-Up таблица](https://gitlab.com/tues-embedded/vmks/-/blob/master/Examples/Gamma_LUT_generator/Gamma_LUT_generator.ino) за зададена гама.

Качил съм ви и два скрипта за MatLab.
С [Gamma_Graph](https://gitlab.com/tues-embedded/vmks/-/blob/master/Other%20Useful%20Files/Gamma_Graph.m) може да видите нелинейността при зададена стойност на гама коефициента.
С [Fade_Gamma_Graph](https://gitlab.com/tues-embedded/vmks/-/blob/master/Other%20Useful%20Files/Fade_Gamma_Graph.m) може да видите, че възприеманата яркост не се променя за примера с преливането между червено и зелено, като също на графиката се изчертава промяната на тона на цвета от което може да видите, че в началото и в края скоростта с която се променя тона се променя(това също може да се компенсира, но става доста по-сложно и не е особенно нужно тъй като на практика е незабележимо в повечето случаи).

Тона(Hue) на цвета е основна характеристика на всеки цвят заедно с наситеност(Saturation) и яркост(Brightness).
Освен RGB цветовото представяне, цветовете често се представляват с тези характеристики под формата на HSL/HSV/HSI цветово представяне, като в папка [Useful Pictures\Color Models](https://gitlab.com/tues-embedded/vmks/-/tree/master/Useful%20Pictures/Color%20Models) ще намерите примери за тях. Разликата между HSL/HSV/HSI е как е представена зависимостта между тон,наситеност и яркост и понеже за яркостта(Lightness/Value/Intensity) е използвано различно име и от там са различните съкращения.
Може да видите какво е [Additive vs Subtractive color mixing](https://www.google.bg/search?q=additive+vs+subtractive+color+mixing&tbm=isch&ved=2ahUKEwiu6JSDiLr1AhXL6aQKHb4_BZIQ2-cCegQIABAA&oq&gs_lcp=CgNpbWcQARgAMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnMgoIIxDvAxDqAhAnOgcIIxDvAxAnUK09WK09YLumAWgDcAB4AIABWogBWpIBATGYAQCgAQGqAQtnd3Mtd2l6LWltZ7ABCsABAQ&sclient=img&ei=PwzmYe7MI8vTkwW-_5SQCQ&bih=821&biw=1728)

[Какво е тон на цвета](https://en.wikipedia.org/wiki/Hue)