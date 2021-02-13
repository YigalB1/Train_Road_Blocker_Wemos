#define in_range_const  10

class train_state {
    public:
        int state= 0; // the state of the train

        bool l_flag = false; // from left sensor
        bool r_flag = false; // from right sensor
        bool gate_open = false; // activating servo

    private:   
        int nxt_state = 0; // temp to hold next state
        bool none,l_only,r_only,both;


public: void change_state() {

    none   = !l_flag && !r_flag;
    l_only =  l_flag && !r_flag;
    r_only = !l_flag &&  r_flag;
    both   =  l_flag &&  r_flag;

    if (both) {
        Serial.println("Error 0 - both sensors active???");
        } // of if 
    

    // see excel file with all states for this state machine
    switch (state) {
        case 0:    // Gate is closed, no train
            if (none) { // wait for train
                nxt_state = 0;
                gate_open = false;
            }
            else if (l_only) { // arriving from left
                nxt_state = 1;
                gate_open = true;
            }
            else if (r_only) { // arriving from right
                nxt_state = 4;
                gate_open = true;
            }
            break;

        case 1:    // Train arriving from left
            if (none) { // passed the left sensor
                nxt_state = 2;
                gate_open = true;
            }
            else if (l_only) { // still arriving from left
                nxt_state = 1;
                gate_open = true;
            }
            else if (r_only) { // ERROR 1
                nxt_state = 10  ;
                gate_open = true;
            }
            break;

        case 2:    // Train passed left, moving to right
            if (none) { // passed left sensorm before right
                nxt_state = 2;
                gate_open = true;
            }
            else if (l_only) { // ERROR 2
                nxt_state = 10;
                gate_open = true;
            }
            else if (r_only) { // arrived right sensor
                nxt_state = 3  ;
                gate_open = true;
            }
        break;

        case 3:    // In right sensor
            if (none) { // finished passing, close gate
                nxt_state = 0;
                gate_open = false;
            }
            else if (l_only) { // ERROR 3
                nxt_state = 10;
                gate_open = true;
            }
            else if (r_only) { // arrived right sensor
                nxt_state = 3  ;
                gate_open = true;
            }
        break; // finished left to right


        case 4:    // passing from right
            if (none) { // passed rioght sensor, twards left
                nxt_state = 5;
                gate_open = false;
            }
            else if (l_only) { // ERROR 4
                nxt_state = 10;
                gate_open = true;
            }
            else if (r_only) { // still in right sensor
                nxt_state = 4  ;
                gate_open = true;
            }
        break;

        case 5:    // Between sensors, while right to left
            if (none) { // still between sensors
                nxt_state = 5;
                gate_open = true;
            }
            else if (l_only) { // arrived left sensor from right
                nxt_state = 6;
                gate_open = true;
            }
            else if (r_only) { // ERROR 5
                nxt_state = 10  ;
                gate_open = true;
            }
        break;

        case 6:    // Between sensors, while right to left
            if (none) { // finished left sensor form right, done, back to start
                nxt_state = 0;
                gate_open = false;
            }
            else if (l_only) { // still in left sensor from right
                nxt_state = 6;
                gate_open = true;
            }
            else if (r_only) { // ERROR 6
                nxt_state = 10  ;
                gate_open = true;
            }
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
    bool in_range;

  
  void measure_dist() { 
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
    dist = int(distance);
    if ((dist < in_range_const) && (dist > 2)) {
        in_range = true;
    }   
    else {
        in_range = false;
        }
    //return(int(distance));
  } // of measure_dist()
};  // of Ultrasonic_Sensor class