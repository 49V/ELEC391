
volatile int A, B, C;
int off_pwm;
double dutyCyclePercentage;
int dutyRaw;

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
  //THE P MOSFETS ARE ACTIVE LOW
  duty_cycle = 0;
  off_pwm = 255;
  //port D controls pin 0-7
  DDRD = B11111100;  // sets Arduino pins 2 - 7 as outputs
  
//  StartupSequence(100);
 // StartupSequence(100);
 // StartupSequence(100);
 //
  StartupSequence(25);
  StartupSequence(25);
  StartupSequence(10);
  StartupSequence(10);
  StartupSequence(10);
  
  InitialiseIO();
  InitialiseInterrupt();
  
}

void loop() {
  // This is where we take our PWM value
  
    // put your main code here, to run repeatedly:
  
          if (Serial.available() > 0) {
                // read the incoming byte:
                //Also remember, our duty input to our P type mosfet is a active low!
                dutyRaw = Serial.parseInt();
                duty_cycle = 255 - dutyRaw;
                dutyCyclePercentage = ((double)dutyRaw / 255.0) * 100.0;
                
                
                // say what you got:
                Serial.print("Duty Cycle: ");
       
                Serial.println(dutyCyclePercentage, DEC);

        }
         
  
}  


void StartupSequence(int startupDelay){
  
  Serial.println("Startup Sequence");
  
  //Phase 1
  Serial.println("Startup Sequence phase 1");
   PORTD = B01110000;
   delay (startupDelay);
  
 //Phase 2
  Serial.println("Startup Sequence phase 2");
   PORTD = B00111000;
   delay (startupDelay);
  
 //Phase 3
 Serial.println("Startup Sequence phase 3");
   PORTD = B00101100;
   delay (startupDelay);
  
 //Phase 4
 Serial.println("Startup Sequence phase 4");
   PORTD = B01001100;   
   delay (startupDelay);
   
 //Phase 5
  Serial.println("Startup Sequence phase 5");
   PORTD = B11001000;
   delay (startupDelay);
 //Phase 6
 Serial.println("Startup Sequence phase 6");
   PORTD = B11100000;
   delay (startupDelay);
   
}



void InitialiseIO(){
  pinMode(A0, INPUT);	   // Pin A0 is input to which a switch is connected
  pinMode(A1, INPUT);	   // Pin A1 is input to which a switch is connected
  pinMode(A2, INPUT);	   // Pin A2 is input to which a switch is connected
 Serial.println("initial IO"); 
}

void InitialiseInterrupt(){
  cli();		// switch interrupts off while messing with their settings  
  PCICR =0x02;          // Enable PCINT1 interrupt
  PCMSK1 = 0b00000111;
  sei();		// turn interrupts back on
  
  Serial.println("initialize interrupt");
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
  
  //Phase 1
    if((A == 0) && (B == 1) && (C == 1))
  {
   PORTD = B01110000; 
   analogWrite(A_high, duty_cycle);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, off_pwm);
  }
  
  //Phase 2
   else if((A == 0) && (B == 0) && (C == 1))
  {  
   PORTD = B00111000;
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, duty_cycle);
   
  }
  
  //Phase 3
   else if((A == 0) && (B == 0) && (C == 0))
  {   
   PORTD = B00101100;
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, duty_cycle);
  }
  
  //Phase 4
   else if((A == 1) && (B == 0) && (C == 0))
  {  
   PORTD = B01001100;   
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, duty_cycle);
   analogWrite(C_high, off_pwm);
  }
  
  //Phase 5
   else if((A == 1) && (B == 1) && (C == 0))
  {  
   PORTD = B11001000;
   analogWrite(A_high, off_pwm);
   analogWrite(B_high, duty_cycle);
   analogWrite(C_high, off_pwm);
  }
  
  //Phase 6
   else if((A == 1) && (B == 1) && (C == 1))
  {  
   PORTD = B11100000;
   analogWrite(A_high, duty_cycle);
   analogWrite(B_high, off_pwm);
   analogWrite(C_high, off_pwm);
  }
  
  else
  {
   Serial.print("You shouldn't be here"); 
  }

  
}
