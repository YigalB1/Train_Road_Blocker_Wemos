#include <Servo.h>
#include <classes.h>

#define trigPin1 12 // D6 // Trig Pin
#define echoPin1 13 // D7 // Echo Pin
#define trigPin2 0  // D3 // Trig Pin
#define echoPin2 14 // D5 // TEchoig Pin


// servo is GPIO2 - D4

long duration, distance; // Duration used to calculate distance

Servo myservo;  // create servo object to control a servo
Ultrasonic_Sensor  r_ultrasonic_sensor;
Ultrasonic_Sensor  l_ultrasonic_sensor;

//int measure_dist();
int x=10;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  myservo.attach(2);  // attaches the servo on GPIO2 to the servo object

  r_ultrasonic_sensor.trig_pin = trigPin1;
  r_ultrasonic_sensor.echo_pin = echoPin1;
  l_ultrasonic_sensor.trig_pin = trigPin2;
  l_ultrasonic_sensor.echo_pin = echoPin2;
  

  
} // of setup()

void loop()
{
  int pos;
  

  //dist = measure_dist();
  r_ultrasonic_sensor.dist = r_ultrasonic_sensor.measure_dist();
  l_ultrasonic_sensor.dist = l_ultrasonic_sensor.measure_dist();
  Serial.print(r_ultrasonic_sensor.dist);
  Serial.print("  ");
  Serial.println(l_ultrasonic_sensor.dist);
  delay(100);

  return;

  int xxxx; // TMP TMP TBDDDDDDDDD
  xxxx=17;
  //Serial.println(x);
  if (xxxx<10) {
    myservo.write(x); 
    delay(2000);
    if (x==10) 
      x=90;
    else
      x=10;
  } // of if
  //myservo.write(0);
  delay(500);
  return;

   
  for (pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
  {                                   // in steps of 1 degree
    myservo.write(pos);               // tell servo to go to position in variable 'pos'
    delay(15);                        // waits 15ms for the servo to reach the position
  } // of for
  for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    myservo.write(pos);               // tell servo to go to position in variable 'pos'
    delay(15);                        // waits 15ms for the servo to reach the position
  } // of for
} // of loop()




