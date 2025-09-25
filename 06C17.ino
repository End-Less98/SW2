
int led = 7;        
int period = 100; // period: 100 to 10000 (unit: us)
float duty = 0;   // duty: 0 to 100 (unit: %)
float Light = 100.0 / (500000/period); // duty 증감율

void setup() 
{
  pinMode(led, OUTPUT);
}

void loop() 
{
  set_period();
  set_duty();
}

void set_period()
{
  int on_time = period / 100.0 * int(duty);
  digitalWrite(led, HIGH);
  delayMicroseconds(on_time);

  digitalWrite(led, LOW);
  delayMicroseconds(period - on_time);
}

void set_duty()
{
  duty += Light;
  if (duty <= 0 || duty >= 100)
  {
    Light = -Light;
  }
}
