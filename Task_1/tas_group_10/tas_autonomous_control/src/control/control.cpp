#include "control.h"

control::control()
{
    control_servo_pub_ = nh_.advertise<geometry_msgs::Vector3>("servo", 1);

    cmd_sub_ = nh_.subscribe<geometry_msgs::Twist>("cmd_vel", 1000, &control::cmdCallback,this);
}

void control::cmdCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    double temp_angle = 0;
    cmd_linearVelocity = msg->linear.x;
    cmd_angularVelocity = msg->angular.z;
    
    if ((cmd_linearVelocity < 0.000001) && (cmd_linearVelocity > -0.000001))
    {
	cmd_speed = 1500;
        cmd_angle = 1500;
    }
    else
    {
	cmd_speed = 1500 + int(cmd_linearVelocity*LINEAR_SCALE);
	temp_angle = atan(cmd_angularVelocity/cmd_linearVelocity*CAR_LENGTH);
	if ((temp_angle < 0.05) && (temp_angle > -0.05))
	{
	    temp_angle = 0;
	}
        cmd_angle = 1500 - int(ANGLE_SCALE*temp_angle);
    }

}

