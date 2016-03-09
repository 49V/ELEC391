
volatile int A, B, C;
int dutyCycle;
int off_pwm;

//H Bridge inputs
int A_low  = 2; 
int A_high = 3;

int B_low  = 4;
int B_high = 5;

int C_high = 6;
int C_low  = 7;

//PWM Variable
int duty_cycle;


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
  duty_cycle = 0;
  off_pwm = 255;
   //port D controls pin 0-7
  DDRD = B11111100;  // sets Arduino pins 2, 4, and 7 as outputs
  
  
  InitialiseIO();
  InitialiseInterrupt();
  
}

void loop() {
  // This is where we take our PWM value
  
    // put your main code here, to run repeatedly:
  
          if (Serial.available() > 0) {
                // read the incoming byte:
                //Also remember, our duty input to our P type mosfet is a active low!
                duty_cycle = 255 - Serial.parseInt();
                
                // say what you got:
                Serial.print("I received: ");
                Serial.println(duty_cycle, DEC);

        }
         
  
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
                
  //A Low   2 
  //A High  3
 
  //B Low   4
  //B High  5   
  
  //C High  6
  //C Low   7
                        
  //For PWM I am going to have to use analogWrite instead of writing to ports directly.                        
              
  A = digitalRead(A0);
  B = digitalRead(A1);
  C = digitalRead(A2);
  
    if((A == 0) && (B == 1) && (C == 1))
  {
   Serial.print("Phase 1 \n");
   PORTD = B00010000; 
   analogWrite(A_high, duty_cycle);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, off_pwm);
  }
  
   else if((A == 0) && (B == 0) && (C == 1))
  {
   Serial.print("Phase 2 \n");
   PORTD = B00010000;
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, duty_cycle);
   
  }
  
   else if((A == 0) && (B == 0) && (C == 0))
  {
   Serial.print("Phase 3 \n"); 
   PORTD = B00000100;
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, duty_cycle);
  }
  
   else if((A == 1) && (B == 0) && (C == 0))
  {
   Serial.print("Phase 4 \n");
   PORTD = B00000100;   
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, duty_cycle);
   analogWrite(C_high, off_pwm);
  }
  
   else if((A == 1) && (B == 1) && (C == 0))
  {
   Serial.print("Phase 5 \n");
   PORTD = B10000000;
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, duty_cycle);
   analogWrite(C_high, off_pwm);
  }
  
   else if((A == 1) && (B == 1) && (C == 1))
  {
   Serial.print("Phase 6 \n"); 
   PORTD = B10000000;
   analogWrite(A_high, duty_cycle);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, off_pwm);
  }
  
  else
  {
   Serial.print("WARNING; CATASTROPHIC FAILURE"); 
  }

  
}
