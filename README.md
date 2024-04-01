![Image alt](https://github.com/S-Sushka/ARDUINO_LCD1602/blob/main/schemes/scheme_2.png)

## What`s going here?

### Start work example:
```cpp
#include <LCD1602.h>

LCD1602 LCD(uint8_t RS_PIN, uint8_t EN_PIN, uint8_t D0_PIN, ..., uint8_t D7_PIN);

void setup()
{
  LCD.begin();
}

void loop()
{
}
```

### Constructors:
```cpp
LCD1602::LCD1602(uint8_t RS_PIN, uint8_t EN_PIN, uint8_t D0_PIN, ..., uint8_t D7_PIN);
// OR
LCD1602::LCD1602(uint8_t RS_PIN, uint8_t EN_PIN, uint8_t D4_PIN, ..., uint8_t D7_PIN);
```

### We can print...
#### ...chars:
```cpp
void print(char symbol);
```
#### ...strings:
```cpp
void print(const char *str);
void print(String *str);
```
#### ...numbers:
```cpp
void print(int32_t number);
```
