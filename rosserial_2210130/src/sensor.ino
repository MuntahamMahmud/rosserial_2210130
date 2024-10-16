#include <ros.h>
#include <std_msgs/Float32MultiArray.h>

#define trig 2
#define echo 4
#define pot_pin A5

ros::NodeHandle nh;  

std_msgs::Float32MultiArray sensor_data_msg;  // Message object
ros::Publisher pub("sensor_data", &sensor_data_msg);  

void setup() {
  nh.initNode();             
  nh.advertise(pub);            

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pot_pin, INPUT);

  // Reserve space for 2 data points in the message array
  sensor_data_msg.data_length = 2;
  sensor_data_msg.data = (float*)malloc(2 * sizeof(float));
}

void loop() {
  float distance = getDistance();  
  float potValue = analogRead(pot_pin);  
  float potMapped = map(potValue, 0, 1023, 0, 100) / 100.0;  // Map to [0.0, 1.0]

  
  sensor_data_msg.data[0] = potMapped;
  sensor_data_msg.data[1] = distance;


  pub.publish(&sensor_data_msg);

  nh.spinOnce();
  delay(500);    
}

float getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  float distance = (duration * 0.034) / 2;  // Convert duration to distance (cm)
  return distance;
}
