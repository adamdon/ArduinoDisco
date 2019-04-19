const int buttonPin = 2; 
const int ledPin =  13;     

int buttonState = 0;       



void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}





void loop()
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
