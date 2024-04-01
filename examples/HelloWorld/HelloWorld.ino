#include <LCD1602.h>

#define _RS_PIN 2
#define _EN_PIN 3

#define _D4_PIN 4
#define _D5_PIN 5
#define _D6_PIN 6
#define _D7_PIN 7

LCD1602 LCD(_RS_PIN, _EN_PIN, _D4_PIN, _D5_PIN, _D6_PIN, _D7_PIN);

void setup()
{  
  LCD.begin();

  LCD.setCursor(2, 0);
  LCD.print("Hello World!");
}

void drawOrnament(String str) 
{
  LCD.setCursor(0, 1);
  LCD.print(str);
  delay(100);
}

void loop()
{
  drawOrnament(">>>          <<<");
  drawOrnament(" >>>        <<< ");
  drawOrnament("  >>>      <<<  ");
  drawOrnament("   >>>    <<<   ");
  drawOrnament("    >>>  <<<    ");
  drawOrnament("     >>><<<     ");
  drawOrnament("     <<<>>>     ");
  drawOrnament("    <<<  >>>    ");
  drawOrnament("   <<<    >>>   ");
  drawOrnament("  <<<      >>>  ");
  drawOrnament(" <<<        >>> ");
  drawOrnament("<<<          >>>");
}
