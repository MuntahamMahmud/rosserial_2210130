#include <ros.h>                  
#include <geometry_msgs/Twist.h>   


int in1 = 2;
int in2 = 3;
int enA = 4;  


int in3 = 5;
int in4 = 6;
int enB = 7;






ros::NodeHandle nh;

void cmdVelCallback(const geometry_msgs::Twist& msg) {
  float linear_x = msg.linear.x;   
  float angular_z = msg.angular.z; 


  if (linear_x > 0) {
    moveForward(linear_x);
    
  } else if (linear_x < 0) {
    moveBackward(-linear_x);
  } else if (angular_z > 0) {
    turnLeft(angular_z);

  } else if (angular_z < 0) {
    turnRight(-angular_z);

  } else {
    stopMotors();
  }
}


ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel_new", &cmdVelCallback);

void setup() {
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);


  nh.initNode();     
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce(); 
  delay(1);       
}





void moveForward(float speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255 * speed); 

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255 * speed);
}


void moveBackward(float speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255 * speed );

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255 * speed);
}


void turnLeft(float speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255 * speed);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255 * speed);
}


void turnRight(float speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255 * speed);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255 * speed);
}


void stopMotors() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
