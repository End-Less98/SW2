
#include <Servo.h>
#include <math.h>

// Arduino pin assignment
#define PIN_SERVO 10
#define PIN_TRIG 12
#define PIN_ECHO 13

// configurable parameters
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25       // sampling interval (unit: msec)
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL)     // coefficent to convert duration to distance

Servo myServo;
unsigned long MOVING_TIME = 3000; // moving time is 3 seconds
int startAngle = 0; // 0°
int stopAngle  = 90; // 90°
int steps = 100;

void setup() {
  pinMode(PIN_TRIG, OUTPUT);  // sonar TRIGGER
  pinMode(PIN_ECHO, INPUT);   // sonar ECHO
  digitalWrite(PIN_TRIG, LOW);  // turn-off Sonar 
  
  myServo.attach(PIN_SERVO);
  myServo.write(startAngle); // Set position

  // initialize serial port
  Serial.begin(57600);
}

void loop() {

  float distance = USS_measure(PIN_TRIG, PIN_ECHO); // read distance
  
  if (50<distance && distance<100)   // 거리가 5cm~10cm 사이가 되면 차단기가 열림. 그후 몇초뒤 닫힘. 
  {
    smoothstep();
  }
  
  Serial.print(",distance:");  Serial.print(distance);
  Serial.println("");
}

void sigmoid()
{
    for (int i=0; i<=steps; i++)
    {
      float sigmoidInput = mapfloat(i, 0, steps, -5.0, 5.0);
      float sigmoid_progress = 1.0 / (1.0 + exp(-sigmoidInput))*90.0;
      myServo.write(sigmoid_progress);
      delay(30);
    }
    
    delay(3000);

    for (int i=0; i<=steps; i++)
    {
      float sigmoidInput = mapfloat(i, 0, steps, 5.0, -5.0);
      float sigmoid_progress = 1.0 / (1.0 + exp(-sigmoidInput))*90.0;
      myServo.write(sigmoid_progress);
      delay(30);
    }
}

void smoothstep()
{
    for (int i=0; i<=steps; i++)
    {
      float smoothstepInput = mapfloat(i, 0, steps, 0.0, 1.0);
      float smoothstep_progress = smoothstepInput*smoothstepInput*(3.0-2.0*smoothstepInput)*90;
      myServo.write(smoothstep_progress);
      delay(30);
    }
    
    delay(3000);

    for (int i=0; i<=steps; i++)
    {
      float smoothstepInput = mapfloat(i, 0, steps, 1.0, 0.0);
      float smoothstep_progress = smoothstepInput*smoothstepInput*(3.0-2.0*smoothstepInput)*90;
      myServo.write(smoothstep_progress);
      delay(30);
    }
}

// get a distance reading from USS. return value is in millimeter.
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)

{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}
