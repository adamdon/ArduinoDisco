const int buttonPin = 2; 
const int ledPin =  13;     

int intLoopCount = 0;

int buttonState;  
int ledState = HIGH;         // the current state of the output pin
int lastButtonState = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup()
{
  Serial.begin(9600);// for debuggin cls output
  
  pinMode(ledPin, OUTPUT); //setting pin 13 as an output
  pinMode(buttonPin, INPUT); //setting pin 2 as an input

  digitalWrite(ledPin, ledState); //defult state
}


void loop()
{
  intLoopCount++;
  
  //loopHoldToRun();
  loopToggleToRun();
  
  printToSerial("New loop", intLoopCount);
}

static void loopToggleToRun()
{
  int reading = digitalRead(buttonPin); //(HIGH or LOW reading)

   if (reading != lastButtonState)
   {
    lastDebounceTime = millis();
   }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == HIGH)
      {
        ledState = !ledState;
      }
      
    }
  }

  digitalWrite(ledPin, ledState);

//  if (buttonState == HIGH)
//  {
//    runPattern(50);
//  }
//  else
//  {
//    digitalWrite(ledPin, LOW);
//  }
  
  lastButtonState = reading;  
}






//unused
static void loopHoldToRun() //hold in pin 2 button to run pattern
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)
  {
    runPattern(50);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}







//
//worker methods
//
static void runPattern(int intWaitTime)
{
    digitalWrite(ledPin, HIGH); 
    delay(intWaitTime);                       
    digitalWrite(ledPin, LOW);    
    delay(intWaitTime); 
    digitalWrite(ledPin, HIGH); 
    delay(intWaitTime * 10);                       
    digitalWrite(ledPin, LOW);    
    delay(intWaitTime); 
}


static void printToSerial(String strMessage, int intLoopCount)
{
  Serial.print(strMessage + " - Loop iteration: " + intLoopCount + "\n");
}
