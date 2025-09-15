#define PIN_LED 7
unsigned int toggle;

void setup() 
{
  pinMode(PIN_LED, OUTPUT);
  toggle = 0;
  digitalWrite(PIN_LED, toggle); // turn on lED.
  delay(1000); // wait for 1,000 milliseconds
}

void loop()
{
  if (toggle < 11)
  {
    toggle = ++toggle;
    int i = (toggle % 2); // LED value.
    digitalWrite(PIN_LED, i); // update LED status.
    delay(100); // wait for 100 milliseconds
  }
  else
  {
    while(1)
    {
      
    }
  }
}
