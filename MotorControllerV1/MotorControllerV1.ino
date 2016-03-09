//For P and N type mosfets, remember:
// P pulls to a high voltage
// N pulls to a low voltage
//One of the things that we also need to remember is how the drain to source channel
//is activated in both.
//For an N-type, we need to pull the gate above a certain voltage
//For a P-type, we need to pull the gate to ground

//The P Type MOSFET will allow current flow when the input is low
//The N type MOSFET will allow current flow when the input is high

//The first input pulls low

// These two pins control the input driver for A
int pinA_high = 6;
int pinA_low = 7;

//These two pins control the input driver for B
int pinB_high = 4;
int pinB_low = 5;

//These two pins control the input driver for C
int pinC_high = 2;
int pinC_low = 3;

int delay_time = 1000;

void setup() {
  
  Serial.begin(9600);      // open the serial port at 9600 bps:
  // put your setup code here, to run once:
  pinMode(pinA_high, OUTPUT);
  pinMode(pinA_low, OUTPUT);
  pinMode(pinB_high, OUTPUT);
  pinMode(pinB_low, OUTPUT);
  pinMode(pinC_high, OUTPUT);
  pinMode(pinC_low, OUTPUT);
  
}

void loop() {
  // For now we are just going to go through a pre-ordained cycle
  //Let us hope we did the logic right the first time :)
  //Consider separating each step using a function call
    // put your setup code here, to run once:
 
 //As it stands, both shouldn't drive at the same time
  
  //Phase 1
  Serial.print("Phase 1 \n");
  //pinA_high = 1;
  //TO allow current flow through the P Type MOSFET, we need a low signal!
  digitalWrite(pinA_high, LOW);
  //pinA_low  = 0;
  digitalWrite(pinA_low, LOW);
  
  
  //pinB_high = 0;
  digitalWrite(pinB_high, HIGH);
  //pinB_low  = 1;
  digitalWrite(pinB_low, HIGH);
  
  //pinC_high = 0;
  digitalWrite(pinC_high, HIGH);
  //pinC_low  = 0;
  digitalWrite(pinC_low, LOW);
  delay(delay_time);
  
  //Phase 2
  Serial.print("Phase 2 \n");
  //pinA_high = 0;
  digitalWrite(pinA_high, HIGH);
  //pinA_low  = 0;
  digitalWrite(pinA_low, LOW);
  
  //pinB_high = 0;
  digitalWrite(pinB_high, HIGH);
  //pinB_low  = 1;
  digitalWrite(pinB_low, HIGH);
  
  //pinC_high = 1;
  digitalWrite(pinC_high, LOW);
  //pinC_low  = 0;
  digitalWrite(pinC_low, LOW);
  delay(delay_time);
  
  //Phase 3
  Serial.print("Phase 3 \n");
  //pinA_high = 0;
  digitalWrite(pinA_high, HIGH);
  //pinA_low  = 1;
  digitalWrite(pinA_low, HIGH);
  
  //pinB_high = 0;
  digitalWrite(pinB_high, HIGH);
  //pinB_low  = 0;
  digitalWrite(pinB_low, LOW);
  
  //pinC_high = 1;
  digitalWrite(pinC_high, LOW );
  //pinC_low  = 0;
  digitalWrite(pinC_low, LOW);
  delay(delay_time);
  
  //Phase 4
  Serial.print("Phase 4 \n");
  //pinA_high = 0;
  digitalWrite(pinA_high, HIGH);
  //pinA_low  = 1;
  digitalWrite(pinA_low, HIGH);
  
  //pinB_high = 1;
  digitalWrite(pinB_high, LOW);
  //pinB_low  = 0;
  digitalWrite(pinB_low, LOW);
  
  //pinC_high = 0;
  digitalWrite(pinC_high, HIGH);
  //pinC_low  = 0;
  digitalWrite(pinC_low, LOW);
  delay(delay_time);
  
  //Phase 5
  Serial.print("Phase 5 \n");
  //pinA_high = 0;
  digitalWrite(pinA_high, HIGH);
  //pinA_low  = 0;
  digitalWrite(pinA_low, LOW);
  
  //pinB_high = 1;
  digitalWrite(pinB_high, LOW);
  //pinB_low  = 0;
  digitalWrite(pinB_low, LOW);
  
  //pinC_high = 0;
  digitalWrite(pinC_high, HIGH);
  //pinC_low  = 1;
  digitalWrite(pinC_low, HIGH);
  delay(delay_time);
  
  //Phase 6
  Serial.print("Phase 6 \n");
  //pinA_high = 1;
  digitalWrite(pinA_high, LOW);
  //pinA_low  = 0;
  digitalWrite(pinA_low, LOW);
  
  //pinB_high = 0;
  digitalWrite(pinB_high, HIGH);
  //pinB_low  = 0;
  digitalWrite(pinB_low, LOW);
  
  //pinC_high = 0;
  digitalWrite(pinC_high, LOW);
  //pinC_low  = 1;
  digitalWrite(pinC_low, HIGH);
  delay(delay_time);
  
}

\
