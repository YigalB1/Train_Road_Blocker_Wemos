class train_state {
    public:
        int state= 0; // the state of the train
        int nxt_state = 0; // temp to hold next state (should be local, not public)
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

    // see excel file with all states for this state machine
    switch (state) {
        case 0:    // Gate is closed, no train
            if (!l_flag && !r_flag) { // wait for train
                nxt_state = 0;
                gate_open = false;
            }
            else if (l_flag && !r_flag) { // arriving from left
                nxt_state = 1;
                gate_open = true;
            }
            else if (!l_flag && r_flag) { // arriving from right
                nxt_state = 4;
                gate_open = true;
            }
            break;

        case 1:    // Train arriving from left
             if (!l_flag && !r_flag) { // wait for train
                nxt_state = 2;
                gate_open = false;
            }
            else if (l_flag && !r_flag) { // still arriving from left
                nxt_state = 1;
                gate_open = true;
            }
            else if (!l_flag && r_flag) { // ERROR 1
                nxt_state = 4;
                gate_open = true;
            }
            break;
        case 2:    // your hand is a few inches from the sensor
        ;
        break;
        case 3:    // your hand is nowhere near the sensor
        ;
        break;
  } // of switch case
  state = nxt_state; 

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