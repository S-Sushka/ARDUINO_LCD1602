#ifndef LCD1602_H_
#define LCD1602_H_

#include <Arduino.h>

class LCD1602
{
	int8_t RS_PIN = -1;
	int8_t EN_PIN = -1;
	
	int8_t D0_PIN = -1;
	int8_t D1_PIN = -1;
	int8_t D2_PIN = -1;
	int8_t D3_PIN = -1;
	int8_t D4_PIN = -1;
	int8_t D5_PIN = -1;
	int8_t D6_PIN = -1;
	int8_t D7_PIN = -1;
	
	int8_t dataBus = -1;
	
	
	uint8_t XCursor = 0;
	uint8_t YCursor = 0;
	
	bool isCursor = false;
	bool isBlink = false;
	
	
	void sendByte(uint8_t _byte);
	void latch();
	void sendNibble(uint8_t _nibble);
	
public:
	enum 
	{
		SCREEN_CLEAR = 0x01,
		CURSOR_RETURN = 0x02,
		INPUT_SET = 0x04,
		DISPLAY_SWITCH = 0x08,
		SHIFT = 0x10,
		FUNCTION_SET = 0x20,
		CGRAM_AD_SET = 0x40,
		DDRAM_AD_SET = 0x80
	};

	LCD1602(uint8_t _RS_PIN, uint8_t _EN_PIN, uint8_t _D4_PIN, uint8_t _D5_PIN, uint8_t _D6_PIN, uint8_t _D7_PIN);
	
	LCD1602(uint8_t _RS_PIN, uint8_t _EN_PIN, uint8_t _D0_PIN, uint8_t _D1_PIN, uint8_t _D2_PIN, uint8_t _D3_PIN,
			uint8_t _D4_PIN, uint8_t _D5_PIN, uint8_t _D6_PIN, uint8_t _D7_PIN);
	

	void sendCommand(uint8_t command);
	void sendData(uint8_t data);
	
	
	void begin();

	void cursor(bool on);
	void blink(bool on);
	bool getCursor();
	bool getBlink();
	
	
	void setCursor(uint8_t x, uint8_t y);
	uint8_t get_X_Cursor();
	uint8_t get_Y_Cursor();

	
	void clear();	
	
	void print(char symbol);
	void print(const char *str);
	void print(String str);
	
	void print(int8_t number);
	void print(int16_t number);
	void print(int32_t number);
	
	void print(uint8_t number);
	void print(uint16_t number);
	void print(uint32_t number);
};

#endif
