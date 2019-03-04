#include <iostream>
#include <ros/ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include <geometry_msgs/Vector3.h>

#define obstacle_distance 0.5

int obstacle_number = 0;
int flag_1 = 0;
int flag_2 = 0;
int flag_turn = 0;
double secs_object1 = 0;
double time_interval = 0;

int Duration_time;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  
  ROS_INFO("I heard: [%f]", msg->angle_min);
  std::vector<float> range;
  range = msg->ranges;

  if ( range[631] <= obstacle_distance && range[713] > obstacle_distance )
  {
     flag_1 = 1; 
  }
  if( range[631] > obstacle_distance && range[713] <= obstacle_distance  && flag_1 == 1)
  {   
     flag_2 = 1;
  }  
          
  if(flag_1 && flag_2)
  {
     ROS_INFO("I have measured the obstacle_distance!");
     obstacle_number++;
     //if(obstacle_number == 1)  secs_object1 = ros::Time::now().toSec();
     //if(obstacle_number == 2)  time_interval = ros::Time::now().toSec() - secs_object1;
     //while(time_interval > 0) printf("%f", time_interval);

     flag_1 = 0;
     flag_2 = 0;
  }
}


int main( int argc, char** argv )
{
   ros::init(argc, argv, "autonomous_parking");
   ROS_INFO_STREAM("Subscribe the date of the  laser!");
   ros::NodeHandle n;
   ros::Rate(60);
   geometry_msgs::Vector3 servo;
   servo.y = 1500;

   ros::Subscriber sub = n.subscribe("/scan", 1000, chatterCallback);
   ros::Publisher pub = n.advertise<geometry_msgs::Vector3>("servo", 1);
  
   while(ros::ok())
   {
      if(obstacle_number < 2)
      {
         servo.x = 1500;
         servo.y = 1500; 
         pub.publish(servo);
         //ros::spinOnce();
         ROS_INFO_STREAM("forward!!!!");
      }

      if(obstacle_number >= 2)
      {
         servo.x = 1800;
         servo.y = 1500 ; 
         pub.publish(servo);
         //ros::spinOnce();
         ROS_INFO_STREAM("stop!!!!");
         //ros::Duration(2).sleep();
         //flag_turn = 1;
      }

      /*if(flag_turn == 1)
      {
          servo.x = 1500;
          servo.y = 1800 ;
          pub.publish(servo);
          ros::Duration(1).sleep();
          pub.publish(servo);
          printf("fhiwofhwiouhfjkshsdhf");
      }*/
      //parking();
      
      //ros::Duration(0.04).sleep();

      ros::spinOnce();
      //ros::spin();
   }
   return 0;



   
}
