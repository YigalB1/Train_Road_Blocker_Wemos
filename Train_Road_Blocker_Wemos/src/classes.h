class train_state {
    public:
        int state= 0; // the state of the train
        bool l_flag = false; // from left sensor
        bool r_flag = false; // from right sensor
        bool gate_open = false; // activating servo

void change_state() {
    if (l_flag && r_flag) {
        Serial.println("Error1 - both sensors active???");
    } // of if 
    if (!l_flag && !r_flag) {
        Serial.println("Error2 - no sensor active??? Shouldnt be here");
    } // of if 

    switch (state) {
        case 0:    // Gate is closed, no train
            if (l_flag) { // train arrving from left
                state = 1;
                gate_open = true;
            }
            else if (r_flag){ // train arrving from right
                state = 3;
                gate_open = true;
            }
            else {
                Serial.println("Error3 -  Shouldnt be here");
            }
        break;
        case 1:    // Train arriving from left
            if (l_flag) { // no change
                state = 1;
                gate_open = true;
            }
            else {
                state = 3;
                gate_open = true;
            }
        break;
        case 2:    // your hand is a few inches from the sensor
        Serial.println("medium");
        break;
        case 3:    // your hand is nowhere near the sensor
        Serial.println("bright");
        break;
  } // of switch case

 } // of change_state()
}; // of train_state class


class Ultrasonic_Sensor {
  public: 
  int trig_pin;
  int echo_pin;
  int dist;

  
  int measure_dist() { 
    long duration, distance; // Duration used to calculate distance
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    duration = pulseIn(echo_pin, HIGH);
    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration/58.2;
    //Serial.println(distance);
    //Delay 50ms before next reading.
    delay(50);
    return(int(distance));
  } // of measure_dist()
};  // of Ultrasonic_Sensor class