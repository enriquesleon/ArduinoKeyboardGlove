#include <SoftwareSerial.h>  

const long  PIN15= 0x00008000;
const long  PIN14= 0x00004000;
const long  PIN13= 0x00002000;
const long  PIN12= 0x00001000;
const long  PIN11= 0x00000800;
const long  PIN10= 0x00000400;
const long  PIN09= 0x00000200;
const long  PIN08= 0x00000100;
const long  PIN07= 0x00000080;
const long  PIN06= 0x00000040;
const long  PIN05= 0x00000020;
const long  PIN04= 0x00000010;
const long  PIN03= 0x00000008;
const long  PIN02= 0x00000004;
const long  PIN01= 0x00000002;
const long  PIN00= 0x00000001;

// declared array containing pin values used to compare with char_value variable inside grab_char
long pins[13] = {PIN00,PIN01,PIN02,PIN03,PIN04,PIN05,PIN06,PIN07,PIN08,PIN09,PIN10,PIN11,PIN12};

// the 3 different modes denoted by the special pin numbers
const long modes[3] = {PIN13,PIN14,PIN15}; 

// default mode set to PIN13, will change over the duration of the program depending on user desired input
long current_mode = PIN13;   
 
boolean long_press = false;

const int size = 79;
const int partition_size = 13;

char char_array[size] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.! :?&$#@\n\b\t\v\f\'\"";

char find_char(int part, unsigned long value){
	int position = part*partition_size;
	char found_char = 0;
	int i;
	for(i = 0; i < partition_size; i++){
		if(pins[i] == value){
			found_char = char_array[position];
			break;	
		}
		position++;
	}
	return found_char;
}

char grab_char(unsigned long char_value){
  	char out_char = 0;
	// test to see if the char_value is first equal to any of the modes, if not it must be reffering to 
	// an ascii character that needs to be returned. A for loop is utilized to navigate all possible ascci characters
	// once the char_value finds the pin it is equal to, it returns the ascci value assocoiated with one of the corresponding arrays
  	if(char_value == modes[0]){
		current_mode = modes[0];
	} else if (char_value == modes[1]){
		current_mode = modes[1];
	} else if (char_value == modes[2]){
		current_mode = modes[2];
	} else {	
		if(current_mode == modes[0]  && !long_press){
			out_char = find_char(0, char_value);
  		} else if (current_mode == modes[0]  && long_press){
			out_char = find_char(1, char_value);
  		} else if(current_mode == modes[1]  && !long_press){
			out_char = find_char(2, char_value);
  		} else if (current_mode == modes[1]  && long_press){
			out_char = find_char(3, char_value);
  		} else if(current_mode == modes[2]  && !long_press){
			out_char = find_char(4, char_value);
  		} else if (current_mode == modes[2]  && long_press){
			out_char = find_char(5, char_value);
  		}
	}
  return out_char;
}

const int NLOAD = 40;
const int CLK  = 41;
const int CLKNE = 42;
const int SER_OUT  = 43;

void setup() {
  pinMode(NLOAD,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(CLKNE,OUTPUT);
  pinMode(SER_OUT,INPUT);
  reset_Register();
  Serial.begin(9600);
}

void loop() {  
  char out;
  if((out = grab_char(grab_char_value()))!=0){
    Serial.print(out);
  }
}

unsigned long read_single_state(){
  unsigned long state = 0x00000000;
  digitalWrite(CLKNE,LOW);
  digitalWrite(NLOAD,LOW);
  delay(1);
  digitalWrite(NLOAD,HIGH);
  for(int i = 0; i<15; i++){
    if(digitalRead(SER_OUT)){
      state++;
    }
    state = state << 1;
    clock_pulse();
  }
  if(digitalRead(SER_OUT)){
      state++;
      }
  reset_Register();
  return state;
}

unsigned long grab_char_value(){
  unsigned long stop_time;
  unsigned long time_diff;
  long_press = false;
  unsigned long state = debounced_value();
  unsigned long current_state = state;
  unsigned long intial_time = millis();
  if(state){
    while(state = read_single_state()){
      current_state = state;
    }
    
    stop_time = millis();
    time_diff = stop_time - intial_time;
    if(tlime_diff > 500){
      long_press = true;
    }
  }
  delay(10);
  return current_state;
}

unsigned long debounced_value(){
  unsigned long initial_state= read_single_state();
  delay(2);
  unsigned long next_state = read_single_state();
  if(initial_state&&(initial_state == next_state)){
     return next_state;
  }
  else return 0x00000000;
}

void reset_Register(){
    digitalWrite(CLKNE,HIGH);
    digitalWrite(CLK,LOW);
    digitalWrite(NLOAD,HIGH);
}

void clock_pulse(){
  digitalWrite(CLK,LOW);
  digitalWrite(CLK,HIGH);
  digitalWrite(CLK,LOW);
}
