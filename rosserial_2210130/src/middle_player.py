#! usr/bin/env python3

import rospy
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import Twist

class Middleman:
    def __init__(self):
        rospy.init_node('middle_man',anonymous=True)
        self.pub=rospy.Publisher("/cmd_vel_new",Twist,queue_size=10)
        rospy.Subscriber('/sensor_data',Float32MultiArray,self.sensor_clbk)

        rospy.Subscriber('/cmd_vel',Twist,self.command_clbk)
    
    def sensor_clbk(self,msg):

        self.pot_value=msg.data[0]
        self.current_distance=msg.data[1]




    def command_clbk(self,msg):
       
        velocity=Twist()
        self.current_linear_x=msg.linear.x
        self.current_angular_z=msg.angular.z
        msg.linear.y=0
        msg.linear.z=0
        msg.angular.x=0
        msg.angular.y=0

       
        if self.current_distance>20:

            if self.pot_value==0:
                self.avg_linear_x=(self.current_linear_x * 0)
                self.avg_angular_z=(self.current_angular_z * 0)
            if self.pot_value==1:
                self.avg_linear_x=self.current_linear_x 
                self.avg_angular_z=self.current_angular_z
            else:
                self.avg_linear_x=(self.current_linear_x * 0.6)
                self.avg_angular_z=(self.current_angular_z * 0.6)
        else:
            self.avg_linear_x = 0  

           
            if self.current_distance <= 20:
                
                self.avg_angular_z = 1  
            else:
                self.avg_angular_z = 0  

                
        velocity.linear.x=self.avg_linear_x
        velocity.angular.z=self.avg_angular_z   


            
        self.pub.publish(velocity)

if __name__=="__main__":
    node=Middleman()
    rospy.spin()







