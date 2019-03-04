#include "control/control.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "autonomous_control");
    control autonomous_control;

    ros::Rate loop_rate(50);

    while(ros::ok())
    {
        ROS_INFO("Automatic Control! Use the AUX switch on the controller to trigger this mode");

	// Here sets the linear velocity, where the saturation is configured.
	if(autonomous_control.cmd_speed > 2000)
	{
	    autonomous_control.control_servo.x = 2000;
	}
	else if(autonomous_control.cmd_speed < 1000)
	{
	    autonomous_control.control_servo.x = 1000;
	}
	else
	{
	    autonomous_control.control_servo.x = double(autonomous_control.cmd_speed);
	}
	
	// Here sets the steering angle, where the saturation is configured.
	if(autonomous_control.cmd_angle > 2000)
	{
	    autonomous_control.control_servo.y = 2000;
	}
	else if(autonomous_control.cmd_angle < 1000)
	{
	    autonomous_control.control_servo.y = 1000;
	}
	else
	{
	    autonomous_control.control_servo.y = double(autonomous_control.cmd_angle);
	}

        autonomous_control.control_servo_pub_.publish(autonomous_control.control_servo);

        ros::spinOnce();
        loop_rate.sleep();

    }

    return 0;

}
