//This variable takes our value from



volatile int A, B, C;

//Variables for our PWM shit :)
int dutyCycle;
int dutyRaw;
int offPwm = 255;
double dutyCyclePercentage;

//Moshe, since you can't seem to get this through your fucking thick skull. Wire things properly. You just spent hours on having A_high in port 2 instead of 3
//The only pwm pins are 2,5,6

//H Bridge inputs
int A_low  = 2; 
int A_high = 3;

int B_low  = 4;
int B_high = 5;

int C_high = 6;
int C_low  = 7;

  //A Low   2 
  //A High  3
 
  //B Low   4
  //B High  5   
  
  //C High  6
  //C Low   7



void setup()
{
  Serial.begin(9600);
  Serial.println("Boe");
  
  DDRD = B11111100;  // sets Arduino pins 2 - 7 as outputs
  //Initialize all inputs as off
  PORTD = B0101000;
  
  //Initialize our duty cycle as 100%
  //Remember we are switching the P Mosfets high so these are active
  dutyCycle = 0;
  
  //We need to increase the frequency on the PWM pins so let us do that
  //Timers 0 controls Pins 5 and 6
  TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  
  //Timer 2 controls pin 3
  TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
  
  
  InitialiseIO();
  InitialiseInterrupt();
}

void loop() {
  
  dutyCycle = (255.0/1023.0)*analogRead(A5);
  //Serial.print("\n");
  //Serial.print(dutyCycle);
  
}  

void InitialiseIO(){
  pinMode(A0, INPUT);	   // Pin A0 is input to which a switch is connected
  pinMode(A1, INPUT);	   // Pin A1 is input to which a switch is connected
  pinMode(A2, INPUT);	   // Pin A2 is input to which a switch is connected
  
}

void InitialiseInterrupt(){
  cli();		// switch interrupts off while messing with their settings  
  PCICR =0x02;          // Enable PCINT1 interrupt
  PCMSK1 = 0b00000111;
  sei();		// turn interrupts back on
}

ISR(PCINT1_vect) {    // Interrupt service routine. Every single PCINT8..14 (=ADC0..5) change
            // will generate an interrupt: but this will always be the same interrupt routine
              
                
  A = digitalRead(A0);
  B = digitalRead(A1);
  C = digitalRead(A2);
  
  //We need to add some code to read Alex's value
  //We are going to read a value on our analog pin
  //We will need to assign this value to our dutyCycle
  
  //int sensorValue = analogRead(A5);
  //float voltage = sensorValue *(5.0/1023.0);
  //We need to scale this voltage then to a max value of 255 
  //dutyCycle = voltage*51;
  
  
  
//The phases are changed around a little for hall sensor values but the commutation is the same per phase



  //A Low   2 
  //A High  3
 
  //B Low   4
  //B High  5   
  
  //C High  6
  //C Low   7

    if((A == 0) && (B == 1) && (C == 1))
  {
   //Serial.print("Phase 1 \n");
   //B high, A low
   PORTD = B01001100;
   analogWrite(B_high, dutyCycle);
  }
  
   else if((A == 1) && (B == 1) && (C == 1))
  {
   //Serial.print("Phase 2 \n");
   //C high, A low
   analogWrite(B_high,offPwm);
   PORTD = B00101100;
   analogWrite(C_high,dutyCycle);
   
  }
  
   else if((A == 1) && (B == 1) && (C == 0))
  {
  //Serial.print("Phase 3 \n");
  //C high, B Low 
  PORTD = B00111000;
  analogWrite(C_high,dutyCycle);
  }
  
   else if((A == 1) && (B == 0) && (C == 0))
  {
  //Serial.print("Phase 4 \n");
   //A high, B Low
   analogWrite(C_high,offPwm);
   PORTD = B01110000;
   analogWrite(A_high, dutyCycle);
  }
  
   else if((A == 0) && (B == 0) && (C == 0))
  {
  //Serial.print("Phase 5 \n");
   //A high, C low
   PORTD = B11100000;
   analogWrite(A_high, dutyCycle);
  }
  
   else if((A == 0) && (B == 0) && (C == 1))
  {
   //Serial.print("Phase 6 \n");
   //B High, C Low
   analogWrite(A_high, offPwm);
   PORTD = B11001000;
   analogWrite(B_high, dutyCycle);
  }
  else
  {
   //Serial.print("WARNING; CATASTROPHIC FAILURE"); 
  }

  
}
