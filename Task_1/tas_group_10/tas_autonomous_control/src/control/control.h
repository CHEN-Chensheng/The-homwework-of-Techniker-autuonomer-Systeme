#ifndef CONTROL_H
#define CONTROL_H

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int16MultiArray.h"
#include <math.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>

#define PI             	        3.14159265
#define CAR_LENGTH              0.350
#define SCALE_FAKTOR_STEERING   500
#define LINEAR_SCALE		7200
#define ANGLE_SCALE		500/30*180/PI

class control
{
public:
    control();

    ros::NodeHandle nh_;
    ros::Publisher control_servo_pub_;
    ros::Subscriber cmd_sub_;

    double cmd_linearVelocity;
    double cmd_angularVelocity;

    int cmd_speed;	// 0 ~~ 3000
    int cmd_angle;	// 0 ~~ 3000

    geometry_msgs::Vector3 control_servo;

private:
    /* subscribe the cmd message from move_base */
    void cmdCallback(const geometry_msgs::Twist::ConstPtr& msg);


};

#endif
