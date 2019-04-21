const int buttonPin = 2; 
const int ledPin =  13;     

int intLoopCount = 0;
bool isActionRunning = false;

int currentButtonState;  
int ledState = HIGH;         // the current state of the output pin
int lastButtonState = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // last time buttonPin was toggled in mil-seconds since program start
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

  if(isActionRunning == true)
  {
    runPattern(50);
  }
  
  printToSerial(isActionRunning, intLoopCount);
}



static void loopToggleToRun()
{
  int reading = digitalRead(buttonPin); //(HIGH is putton pressesd or LOW if not)

   //note any type of change
   if (reading != lastButtonState) // if the current HIGH/LOW on the button pin had changed
   {
      lastDebounceTime = millis(); // reset the debouncing timer
   }


  //make sure the change is not just noise 
  if ((millis() - lastDebounceTime) > debounceDelay) //if total time from lastDebounceTime is > 50
  {
    //confirm change
    if(reading != currentButtonState)
    {
      currentButtonState = reading;

      //confirm that change is a press in only 
      if(currentButtonState == HIGH)
      {
        isActionRunning = !isActionRunning; //flip toggle 
      }
             
    }
    
  }

  
  lastButtonState = reading;  
}






//unused
static void loopHoldToRun() //hold in pin 2 button to run pattern
{
  currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == HIGH)
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

static void printToSerial(String strMessage)
{
  Serial.print(strMessage + " - Loop iteration: " + "\n");
}


static void printToSerial(bool isActionRunning, int intLoopCount)
{
  String strMessage = "";

  if(isActionRunning == true)
  {
     strMessage = "true";
  }
  else
  {
    strMessage = "false";
  }

  Serial.print(strMessage + " - Loop iteration: " + intLoopCount + "\n");
}
