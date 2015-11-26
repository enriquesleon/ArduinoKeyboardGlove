#include <SoftwareSerial.h>  

const long  PIN31= 0x80000000;
const long  PIN30= 0x40000000;
const long  PIN29= 0x20000000;
const long  PIN28= 0x10000000;
const long  PIN27= 0x08000000;
const long  PIN26= 0x04000000;
const long  PIN25= 0x02000000;
const long  PIN24= 0x01000000;
const long  PIN23= 0x00800000;
const long  PIN22= 0x00400000;
const long  PIN21= 0x00200000;
const long  PIN20= 0x00100000;
const long  PIN19= 0x00080000;
const long  PIN18= 0x00040000;
const long  PIN17= 0x00020000;
const long  PIN16= 0x00010000;
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




 
const int NLOAD = 40;
const int CLK  = 41;
const int CLKNE = 42;
const int SER_OUT  = 43;
boolean long_press = false;

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
    if(time_diff > 500){
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
char grab_char(unsigned long char_value){
  char out_char = 0;
  switch(char_value){    
    case PIN31:
      break;
    case PIN30:
      break;
    case PIN29:
      break;
    case PIN28:
      break;
    case PIN27:
      break;
    case PIN26:
      break;
    case PIN25:
      break;
    case PIN24:
      break;
    case PIN23:
      break;
    case PIN22:
      break;
    case PIN21:
      break;
    case PIN20:
      break;
    case PIN19:
      break;
    case PIN18:
      break;
    case PIN17:
      break;
    case PIN16:
      break;
    case PIN15:
      if(long_press){
        out_char = '.';
      }
      else out_char = 'p';
      break;
    case PIN14:
      if(long_press){
        out_char = '?';
      }
      else out_char = 'o';
      break;
    case PIN13:
      if(long_press){
        out_char = ',';
      }
      else out_char = 'n';
      break;
    case PIN12:
      if(long_press){
        out_char = '-';
      }
      else out_char = 'm';
      break;
    case PIN11:
      if(long_press){
        out_char = ':';
      }
      else out_char = 'l';
      break;
    case PIN10:
      if(long_press){
        out_char = '\"';
      }
      else out_char = 'k';
      break;
    case PIN09:
      if(long_press){
        out_char = '\'';
      }
      else out_char = 'j';
      break;
    case PIN08:
      if(long_press){
        out_char = '/';
      }
      else out_char = 'i';
      break;
    case PIN07:
      if(long_press){
        out_char = '.';
      }
      else out_char = 'h';
      break;
    case PIN06:
      if(long_press){
        out_char = '?';
      }
      else out_char = 'g';
      break;
    case PIN05:
      if(long_press){
        out_char = ',';
      }
      else out_char = 'f';
      break;
    case PIN04:
      if(long_press){
        out_char = '-';
      }
      else out_char = 'e';
      break;
    case PIN03:
      if(long_press){
        out_char = ':';
      }
      else out_char = 'd';
      break;
    case PIN02:
      if(long_press){
        out_char = '\"';
      }
      else out_char = 'c';
      break;
    case PIN01:
      if(long_press){
        out_char = '\'';
      }
      else out_char = 'b';
      break;
    case PIN00:
      if(long_press){
        out_char = '/';
      }
      else out_char = 'a';
      break;
    case 0:
      break;
                                                                                         
  }
  return out_char;
}


