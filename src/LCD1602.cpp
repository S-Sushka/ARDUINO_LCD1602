#include<LCD1602.h>

LCD1602::LCD1602(uint8_t _RS_PIN, uint8_t _EN_PIN, uint8_t _D4_PIN, uint8_t _D5_PIN, uint8_t _D6_PIN, uint8_t _D7_PIN)
{
	dataBus = 4;
	
	
	RS_PIN = _RS_PIN;
	EN_PIN = _EN_PIN;
	
	D4_PIN = _D4_PIN;
	D5_PIN = _D5_PIN;
	D6_PIN = _D6_PIN;
	D7_PIN = _D7_PIN;
	
	
	pinMode(RS_PIN, OUTPUT);
	pinMode(EN_PIN, OUTPUT);
	
	pinMode(D4_PIN, OUTPUT);
	pinMode(D5_PIN, OUTPUT);
	pinMode(D6_PIN, OUTPUT);
	pinMode(D7_PIN, OUTPUT);
}

LCD1602::LCD1602(uint8_t _RS_PIN, uint8_t _EN_PIN, uint8_t _D0_PIN, uint8_t _D1_PIN, uint8_t _D2_PIN, uint8_t _D3_PIN,
			uint8_t _D4_PIN, uint8_t _D5_PIN, uint8_t _D6_PIN, uint8_t _D7_PIN)
{
	dataBus = 8;
	
	
	RS_PIN = _RS_PIN;
	EN_PIN = _EN_PIN;
	
	D0_PIN = _D0_PIN;
	D1_PIN = _D1_PIN;
	D2_PIN = _D2_PIN;
	D3_PIN = _D3_PIN;
	D4_PIN = _D4_PIN;
	D5_PIN = _D5_PIN;
	D6_PIN = _D6_PIN;
	D7_PIN = _D7_PIN;
	

	pinMode(RS_PIN, OUTPUT);
	pinMode(EN_PIN, OUTPUT);
	
	pinMode(D0_PIN, OUTPUT);
	pinMode(D1_PIN, OUTPUT);
	pinMode(D2_PIN, OUTPUT);
	pinMode(D3_PIN, OUTPUT);
	pinMode(D4_PIN, OUTPUT);
	pinMode(D5_PIN, OUTPUT);
	pinMode(D6_PIN, OUTPUT);
	pinMode(D7_PIN, OUTPUT);
}



// >>> LOW LEVEL

void LCD1602::sendCommand(uint8_t command) 
{
	digitalWrite(RS_PIN, 0);
	
	if (dataBus == 4) 
	{
		sendNibble(command >> 4);
		sendNibble(command & 0x0F);
	}
	else 
		sendByte(command);
}

void LCD1602::sendData(uint8_t data) 
{
	digitalWrite(RS_PIN, 1);
	
	if (dataBus == 4) 
	{
		sendNibble(data >> 4);
		sendNibble(data & 0x0F);
	}
	else 
		sendByte(data);
}



void LCD1602::sendNibble(uint8_t _nibble) 
{
	if ((_nibble & 0x01) == 0) digitalWrite(D4_PIN, 0);
	else 				   	   digitalWrite(D4_PIN, 1);
	
	if ((_nibble & 0x02) == 0) digitalWrite(D5_PIN, 0);
	else 					   digitalWrite(D5_PIN, 1);
	
	if ((_nibble & 0x04) == 0) digitalWrite(D6_PIN, 0);
	else 					   digitalWrite(D6_PIN, 1);
	
	if ((_nibble & 0x08) == 0) digitalWrite(D7_PIN, 0);
	else 					   digitalWrite(D7_PIN, 1);
	
	latch();
}

void LCD1602::latch() 
{
	digitalWrite(EN_PIN, 1);
	delay(1);
	digitalWrite(EN_PIN, 0);
	delay(1);
}

void LCD1602::sendByte(uint8_t _byte) 
{
	if ((_byte & 0x01) == 0) digitalWrite(D0_PIN, 0);
	else 					 digitalWrite(D0_PIN, 1);
	
	if ((_byte & 0x02) == 0) digitalWrite(D1_PIN, 0);
	else 					 digitalWrite(D1_PIN, 1);
	
	if ((_byte & 0x04) == 0) digitalWrite(D2_PIN, 0);
	else 					 digitalWrite(D2_PIN, 1);
	
	if ((_byte & 0x08) == 0) digitalWrite(D3_PIN, 0);
	else 					 digitalWrite(D3_PIN, 1);
	
	if ((_byte & 0x10) == 0) digitalWrite(D4_PIN, 0);
	else 					 digitalWrite(D4_PIN, 1);
	
	if ((_byte & 0x20) == 0) digitalWrite(D5_PIN, 0);
	else 					 digitalWrite(D5_PIN, 1);
	
	if ((_byte & 0x40) == 0) digitalWrite(D6_PIN, 0);
	else 					 digitalWrite(D6_PIN, 1);
	
	if ((_byte & 0x80) == 0) digitalWrite(D7_PIN, 0);
	else 					 digitalWrite(D7_PIN, 1);
	
	latch();
}



// >>> HIGH LEVEL

void LCD1602::begin() 
{
	delay(15);
	
	sendCommand(this->CURSOR_RETURN | 0x01);
	delay(5);
	sendCommand(this->CURSOR_RETURN | 0x01);
	delay(1);
	sendCommand(this->CURSOR_RETURN | 0x01);
	
	sendCommand(this->CURSOR_RETURN);
	
	sendCommand(this->FUNCTION_SET | 0x08);
	sendCommand(this->DISPLAY_SWITCH);
	sendCommand(this->SCREEN_CLEAR);
	sendCommand(this->INPUT_SET | 0x02);
	
	sendCommand(this->DISPLAY_SWITCH | 0x04);
}


void LCD1602::cursor(bool on) 
{
	if (on) 
	{
		if (!isBlink) 
			sendCommand(this->DISPLAY_SWITCH | 0b00000110);
		else
			sendCommand(this->DISPLAY_SWITCH | 0b00000111);
		
		isCursor = true;
	}
	else 
	{
		sendCommand(this->DISPLAY_SWITCH | 0b00000100);
		isCursor = false;
		isBlink = false;
	}
}

void LCD1602::blink(bool on) 
{
	if (on) 
	{
		sendCommand(this->DISPLAY_SWITCH | 0b00000111);
		isCursor = true;
		isBlink = true;
	}
	else 
	{
		if (!isCursor)
			sendCommand(this->DISPLAY_SWITCH | 0b00000100);
		else
			sendCommand(this->DISPLAY_SWITCH | 0b00000110);
		
		isBlink = false;
	}
}


void LCD1602::setCursor(uint8_t x, uint8_t y) 
{
	if (y == 0)
		sendCommand(this->DDRAM_AD_SET | x);
	else
		sendCommand(this->DDRAM_AD_SET | 0x40 | x);
	
	XCursor = x;
	YCursor = y;
}


void LCD1602::clear() 
{
	sendCommand(this->SCREEN_CLEAR);
}



// >>> PRINT FUNCTIONS

void LCD1602::print(char symbol) 
{
	sendData(symbol);
}

void LCD1602::print(const char *str) 
{
	uint16_t length = strlen(str);
	
	for (uint16_t i = 0; i < length; i++) 
		print((char)str[i]);
}

void LCD1602::print(String str) 
{
	uint16_t length = str.length();
	
	for (uint16_t i = 0; i < length; i++) 
		print((char)str[i]);
}

	
void LCD1602::print(int8_t number) { print((int32_t)number); }
void LCD1602::print(int16_t number) { print((int32_t)number); }
void LCD1602::print(int32_t number) 
{
	if (number < 0) 
	{
		sendData('-');
		print((uint32_t)(number*-1));
	}
	else
		print((uint32_t)number);
}
	
void LCD1602::print(uint8_t number) { print((uint32_t)number); }
void LCD1602::print(uint16_t number) { print((uint32_t)number); }
void LCD1602::print(uint32_t number) 
{
	char numberAsString[10] = {0};
	uint8_t pointer = 9;

	bool showZero = false;
	
	
	while (number > 0) 
	{
		numberAsString[pointer] = number % 10;
		
		number /= 10;
		pointer--;
	}	
	
	
	for (uint8_t i = 0; i < 10; i++) 
	{
		if (numberAsString[i] > 0 || showZero) 
		{
			showZero = true;
			sendData(numberAsString[i] + 0x30);
		}
	}
}



// >>> GETTERS

bool LCD1602::getCursor() {return isCursor;}
bool LCD1602::getBlink() {return isBlink;}
uint8_t LCD1602::get_X_Cursor() {return XCursor;}
uint8_t LCD1602::get_Y_Cursor() {return YCursor;}