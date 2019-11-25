#include"mbed.h"
#include <stdio.h>
#include "i2c.h"
#define decode_bcd(x)	((x >> 4) * 10 + (x & 0x0F))
#define encode_bcd(x)	((((x/10) & 0x0F) << 4) + (x % 10)) 

//using namespace std;


DigitalOut col1(p8);
DigitalOut col2(p7);
DigitalOut col3(p6);
DigitalOut col4(p5);
//temperature sensor
DigitalOut clk(p27);  
DigitalOut rst(p28);  
DigitalOut data(p30); 
// LCD Commands
// -------------------------------------------------------------------------
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80
// flags for display entry mode
// -------------------------------------------------------------------------
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
// flags for display on/off and cursor control
// -------------------------------------------------------------------------
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00
// flags for display/cursor shift
// -------------------------------------------------------------------------
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00
// flags for function set
// -------------------------------------------------------------------------
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00
///*********************************************
//Project : I2C to LCD Interface-Routine
//Port PCF8574 : 7 6 5 4 3 2 1 0
// D7 D6 D5 D4 BL EN RW RS
//**********************************************/
#define PCF8574T 0x27
I2C i2c(p32, p31);// SDA, SCL//

static unsigned char wr_lcd_mode(char c, char mode) {
 char ret = 1;
 char seq[5];
 static char backlight = 8;
 if (mode == 8) {
 backlight = (c != 0) ? 8 : 0;
 return 0;
 }
 mode |= backlight;
 seq[0] = mode; // EN=0, RW=0, RS=mode
 seq[1] = (c & 0xF0) | mode | 4; // EN=1, RW=0, RS=1
 seq[2] = seq[1] & ~4; // EN=0, RW=0, RS=1
 seq[3] = (c << 4) | mode | 4; // EN=1, RW=0, RS=1
 seq[4] = seq[3] & ~4; // EN=0, RW=0, RS=1
 i2c.start();
i2c.write(PCF8574T << 1);
 uint8_t i;
 for (i = 0; i < 5; i++) {
 i2c.write(seq[i]);
 wait(0.002);
}
ret = 0;
 i2c.stop();
 if (!(mode & 1) && c <= 2)
 wait(0.2); // CLS and HOME
 return ret;
}
void EdgeClock(){ 
 wait(0.000001); 
 clk = 1; 
 wait(0.000001); 
 clk=0; 
  
}
unsigned char lcd_command(char c) {
 wr_lcd_mode(c, 0);
}
unsigned char lcd_data(char c) {
 wr_lcd_mode(c, 1);
}
void lcd_init(void) {
 char i;

 // High-Nibble von Byte 8 = Display Control:
 // 1DCB**** D: Disp on/off; C: Cursor on/off B: blink on/off
char init_sequenz[] = { 0x33, 0x32, 0x28, 0x0C, 0x06, 0x01 };
 wait(1); // Delay power-up
 for (i = 0; i < sizeof(init_sequenz); i++) {
 lcd_command(init_sequenz[i]);
 }
}
void lcd_backlight(char on) {
 wr_lcd_mode(on, 8);
}
//function to convert from ASCII to value
int asciiToValue(int asciiVal){
	return decode_bcd(asciiVal);
}


//function to convert from value to ASCII
int valueToAscii(int val){
	return encode_bcd(val);
}
void lcd_Alpha() { //row1
	lcd_data('A');
lcd_data('B');
lcd_data('C');
lcd_data('D');
lcd_data('E');
lcd_data('F');
lcd_data('G');
lcd_data('H');
lcd_data('I');
lcd_data('J');
lcd_data('K');
lcd_data('L');
lcd_data('M');

		for (int i=7;i>0;i--){//Write on row3 
		lcd_data(' ');
	}
	lcd_data('a');
lcd_data('b');
lcd_data('c');
lcd_data('d');
lcd_data('e');
lcd_data('f');
lcd_data('g');
lcd_data('h');
lcd_data('i');
lcd_data('j');
lcd_data('k');
lcd_data('l');
lcd_data('m');

for (int i=7;i>0;i--){//Write on row2
		lcd_data(' ');
	}
lcd_data('N');
lcd_data('O');
lcd_data('P');
lcd_data('Q');
lcd_data('R');
lcd_data('S');
lcd_data('T');
lcd_data('U');
lcd_data('V');
lcd_data('W');
lcd_data('X');
lcd_data('Y');
lcd_data('Z');
	for (int i=7;i>0;i--){//Write on row4
		lcd_data(' ');
	}
	lcd_data('n');
lcd_data('o');
lcd_data('p');
lcd_data('q');
lcd_data('r');
lcd_data('s');
lcd_data('t');
lcd_data('u');
lcd_data('v');
lcd_data('w');
lcd_data('x');
lcd_data('y');
lcd_data('z');
wait (3);
}

void lcd_num(){
lcd_data('0');
lcd_data('1');
lcd_data('2');
lcd_data('3');
lcd_data('4');
lcd_data('5');
lcd_data('6');
lcd_data('7');
lcd_data('8');
lcd_data('9');
lcd_data('.');
	for (int i=29;i>0;i--){//Write on row3 
		lcd_data(' ');
	}
	lcd_data('.');
lcd_data('9');
lcd_data('8');
lcd_data('7');
lcd_data('6');
lcd_data('5');
lcd_data('4');
lcd_data('3');
lcd_data('2');
lcd_data('1');
lcd_data('0');

	
	
}
void lcd_clear(){
	
	for(int i=87;i>0;i--)
	{lcd_data(' ');
	}
	
	
}
void lcd_test(){
	lcd_data('H');
}
void displayVal(int val1, int val2 , int val3){
	
	char line[10];
	//print third digit MS
	sprintf(line, "%d",val1);
		EdgeClock(); 
	} 	
	//print second digit
	for (int j = 0; j < 8 ; j++) { 	
		data = arr[val2][j]; 
		EdgeClock(); 
	}
	//print first digit LS
	for (int j = 0; j < 8 ; j++) { 	
		data = arr[val3][j]; 
		EdgeClock(); 
	}
	
	wait(0.2);// Paused to show 
}

void parseMyReading(unsigned int temp){
	
	int dig1, dig2, dig3, dig4;
	float ctemp;
	ctemp = temp * 0.0625;
	
	dig1 = int(temp)%10;
	dig2 = temp/10;
	
	//display Celsius reading
	displayVal(dig1,dig2,12);
	
	float tempf;
	
	tempf = (temp * (1.8)) + 32;
	
	dig3 = int(tempf)%10;
	dig4 = tempf/10;
	
	wait(1.5);
	
	//display  Farenheit reading
	displayVal(dig3,dig4,15);
	
	wait(1.5);
}
void parseMyTime(int sec, int min, int hour, int day, int date, int month, int year){
	int minuteDig1, minuteDig2, hrDig1, hrDig2, dateDig1, dateDig2, monthDig1, monthDig2, yrDig1, yrDig2;
	
	minuteDig1 = min % 10;
	minuteDig2 = min / 10;
	
	hrDig1 = hour % 10;
	hrDig2 = hour / 10;
	
	
	displayVal(minuteDig1, minuteDig2, hrDig1);	
	
	dateDig1 = date % 10;
	dateDig2 = date / 10;
	
	monthDig1 = month % 10;
	monthDig2 = month / 10;
	
	yrDig1 = year % 10;
	yrDig2 = year / 10;
	
	wait(3.2);
	
	displayVal(dateDig1, dateDig2, 0);
	wait(1.5);
	displayVal(monthDig1, monthDig2, 0);
	wait(1.5);
	displayVal(yrDig1, yrDig2, 13);
	wait(3.31);
	
	
	
}







int main() {
lcd_init();
//lcd_Alpha();
//lcd_clear();
//lcd_num();
//lcd_clear();
//	for (int i=22;i>0;i--){ //nasty hardcode
//		lcd_data(' ');
//	}
		rst = 0; 
	EdgeClock(); 
	rst = 1; 
	EdgeClock(); 
	
	
	int sec, min, hour, day, date, month, year;
	
	//start time
	i2c.start();
	
	i2c.write(0xD0);
	
	i2c.write(0x00);
	
	i2c.write(0x00);
	
	i2c.stop();
	
  i2c.start();
	
	i2c.write(0xD0);
	
	i2c.write(0x00);
	
	i2c.write(0x00);	//we want 0
	
	i2c.write(0x00); //we want 0 minutes
		
	i2c.write(0x62); //we want 2 hours
			
	i2c.write(0x01); //we want day 1
				
	i2c.write(0x12); //we want date 11
					
	i2c.write(0x11);	//we want month 11
						
	i2c.write(0x19);	//we want year 19
	
	i2c.start();
	
	i2c.write(0xD0);
	
	i2c.write(0x0E);
	
	i2c.write(0x20);
	
	i2c.write(0);
	
	i2c.stop();
	
	//read temp
	unsigned int temp;	
	
	//start i2c communication using object
	i2c.start();	
	
	//arbitrary address for communications
	i2c.write(0x90);
	
	//access the 1-byte configuration register
	i2c.write(0xAC);
	
	//configure itself to continuously monitor temperature
	i2c.write(0x2);
	
	//communication from master is over. BYE
	i2c.stop();
	
	//collect data continuously
	i2c.start();
	
	i2c.write(0x90);
	
	//initiate temperature conversions
	i2c.write(0x51);
	
	i2c.stop();
	
	i2c.start();
	
	//writing to tell it to read 
	i2c.write(0x90);
	
	i2c.write(0xAA);	
	
	//continuously read from sensors
	while(1){
	
	// read from clock
	i2c.start();
	
	i2c.write(0xD0);
	
	i2c.write(0x00);
	
	i2c.start();
	
	i2c.write(0xD1);	
	
	sec   = i2c.read(1);	//ACK
	min   = i2c.read(1);
	hour  = i2c.read(1);
	day   = i2c.read(1);
	date  = i2c.read(1);
	month = i2c.read(1);
	year  = i2c.read(0);	//NACK
	
	//convert BCD to decimal 
	sec   = decode_bcd(sec);
	min   = decode_bcd(min);
	hour  = decode_bcd(hour);
	day   = decode_bcd(day);
	date  = decode_bcd(date);
	month = decode_bcd(month);
	year  = decode_bcd(year);
	
	parseMyTime(sec, min, hour, day, date, month, year);
	
	
	i2c.stop();
		
		//start communication with temp module
		i2c.start();
	
		//take reading from temperature module
		i2c.write(0x91);
		
		//get the first input
		temp = i2c.read(0);
		
		//end communications
		i2c.stop();
		
		//analyze reading from temperature sensor
		parseMyReading(temp);		


}
	}
// -------------------------------------------------------------------------