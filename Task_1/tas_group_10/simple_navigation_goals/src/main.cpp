/**
 * This node sends fixed goals to move base via ROS Action API and receives feedback via callback functions.
 */

#include <iostream>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <actionlib/client/simple_action_client.h>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

/**
 * Callback function
 */
void doneCb(const actionlib::SimpleClientGoalState& state, const move_base_msgs::MoveBaseResultConstPtr& result) {
    ROS_INFO("Finished in state [%s]", state.toString().c_str());
}

/**
 * Callback function, called once when the goal becomes active
 */
void activeCb() {
    ROS_INFO("Goal just went active");
}

/**
 * Callback function, called every time feedback is received for the goal
 */
void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback) {
    ROS_INFO("[X]:%f [Y]:%f [W]: %f [Z]: %f", feedback->base_position.pose.position.x,feedback->base_position.pose.position.y,feedback->base_position.pose.orientation.w, feedback->base_position.pose.orientation.z);
}

/**
 * Main function
 */
int main(int argc, char** argv){
    ros::init(argc, argv, "simple_navigation_goals"); // init and set name
    std::vector<geometry_msgs::Pose> waypoints; // vector of goals, with position and orientation

    geometry_msgs::Pose waypoint1;
    waypoint1.position.x = 0.255777359009;
    waypoint1.position.y = 2.00751876831;
    waypoint1.position.z = 0.000;
    waypoint1.orientation.x = 0;
    waypoint1.orientation.y = 0;
    waypoint1.orientation.z = -0.739631354684;
    waypoint1.orientation.w =0.673012228098;
    waypoints.push_back(waypoint1);

    geometry_msgs::Pose waypoint2;
    waypoint2.position.x = 2.30259132385;
    waypoint2.position.y = -3.21410369873;
    waypoint2.position.z = 0.000;
    waypoint2.orientation.x = 0;
    waypoint2.orientation.y = 0;
    waypoint2.orientation.z = -0.875841292813;
    waypoint2.orientation.w = 0.482599243476;
    waypoints.push_back(waypoint2);

   

    geometry_msgs::Pose waypoint3;
    waypoint3.position.x = -2.5793800354;
    waypoint3.position.y = -14.3939094543;
    waypoint3.position.z = 0.000;
    waypoint3.orientation.x = 0;
    waypoint3.orientation.y = 0;
    waypoint3.orientation.z = -0.298622506938;
    waypoint3.orientation.w = 0.954371310523;
    waypoints.push_back(waypoint3);

    geometry_msgs::Pose waypoint4;
    waypoint4.position.x = 4.29218482971;
    waypoint4.position.y = -13.9909324646;
    waypoint4.position.z = 0.000;
    waypoint4.orientation.x = 0;
    waypoint4.orientation.y = 0;
    waypoint4.orientation.z = 0.414513096359;
    waypoint4.orientation.w = 0.910043346741;
    waypoints.push_back(waypoint4);

    /*geometry_msgs::Pose waypoint5;
    waypoint5.position.x = 1.81937599182;
    waypoint5.position.y = -1.84235143661;
    waypoint5.position.z = 0.000;
    waypoint5.orientation.x = 0;
    waypoint5.orientation.y = 0;
    waypoint5.orientation.z = -0.653312651989;
    waypoint5.orientation.w = 0.757088223889;
    waypoints.push_back(waypoint5);

    geometry_msgs::Pose waypoint6;
    waypoint6.position.x = 1.65329170227;
    waypoint6.position.y = -4.86426639557;
    waypoint6.position.z = 0.000;
    waypoint6.orientation.x = 0;
    waypoint6.orientation.y = 0;
    waypoint6.orientation.z = -0.953363714541;
    waypoint6.orientation.w = 0.301823835698;
    waypoints.push_back(waypoint6);

    geometry_msgs::Pose waypoint7;
    waypoint7.position.x = -2.69187545776;
    waypoint7.position.y = -9.87752628326;
    waypoint7.position.z = 0.000;
    waypoint7.orientation.x = 0;
    waypoint7.orientation.y = 0;
    waypoint7.orientation.z = -0.843270790715;
    waypoint7.orientation.w = 0.537488952005;
    waypoints.push_back(waypoint7);

    geometry_msgs::Pose waypoint8;
    waypoint8.position.x = -3.95239448547;
    waypoint8.position.y = -12.4453716278;
    waypoint8.position.z = 0.000;
    waypoint8.orientation.x = 0;
    waypoint8.orientation.y = 0;
    waypoint8.orientation.z = -0.581435051858;
    waypoint8.orientation.w = 0.813592822283;
    waypoints.push_back(waypoint8);

    geometry_msgs::Pose waypoint9;
    waypoint9.position.x = -3.01127052307;
    waypoint9.position.y = -13.9780454636;
    waypoint9.position.z = 0.000;
    waypoint9.orientation.x = 0;
    waypoint9.orientation.y = 0;
    waypoint9.orientation.z = -0.3105940948;
    waypoint9.orientation.w = 0.950542638852;
    waypoints.push_back(waypoint9);

    geometry_msgs::Pose waypoint10;
    waypoint10.position.x = 3.41962814331;
    waypoint10.position.y = -18.7942352295;
    waypoint10.position.z = 0.000;
    waypoint10.orientation.x = 0;
    waypoint10.orientation.y = 0;
    waypoint10.orientation.z = -0.285999992147;
    waypoint10.orientation.w = 0.95822961992;
    waypoints.push_back(waypoint10);

    geometry_msgs::Pose waypoint11;
    waypoint11.position.x = -0.00172805786133;
    waypoint11.position.y = -16.5455245972;
    waypoint11.position.z = 0.000;
    waypoint11.orientation.x = 0;
    waypoint11.orientation.y = 0;
    waypoint11.orientation.z = 0.0807430859977;
    waypoint11.orientation.w = 0.996734946745;
    waypoints.push_back(waypoint11);

    geometry_msgs::Pose waypoint12;
    waypoint12.position.x = 1.95010757446;
    waypoint12.position.y = -16.4991340637;
    waypoint12.position.z = 0.000;
    waypoint12.orientation.x = 0;
    waypoint12.orientation.y = 0;
    waypoint12.orientation.z = 0.426929426503;
    waypoint12.orientation.w = 0.904284946677;
    waypoints.push_back(waypoint12);

    geometry_msgs::Pose waypoint13;
    waypoint13.position.x = 3.37360191345;
    waypoint13.position.y = -15.1863746643;
    waypoint13.position.z = 0.000;
    waypoint13.orientation.x = 0;
    waypoint13.orientation.y = 0;
    waypoint13.orientation.z = 0.712861709457;
    waypoint13.orientation.w = 0.70130462938;
    waypoints.push_back(waypoint13);

    geometry_msgs::Pose waypoint14;
    waypoint14.position.x = 3.31435394287;
    waypoint14.position.y = -12.7759160995;
    waypoint14.position.z = 0.000;
    waypoint14.orientation.x = 0;
    waypoint14.orientation.y = 0;
    waypoint14.orientation.z = 0.794431226864;
    waypoint14.orientation.w = 0.607354118931;
    waypoints.push_back(waypoint14);

    geometry_msgs::Pose waypoint15;
    waypoint15.position.x = -1.100;
    waypoint15.position.y = -14.300;
    waypoint15.position.z = 0.000;
    waypoint15.orientation.x = 0;
    waypoint15.orientation.y = 0;
    waypoint15.orientation.z = 0.0791;
    waypoint15.orientation.w = 0.9969;
    waypoints.push_back(waypoint15);

    geometry_msgs::Pose waypoint16;
    waypoint16.position.x = 5.000;
    waypoint16.position.y = -13.600;
    waypoint16.position.z = 0.000;
    waypoint16.orientation.x = 0;
    waypoint16.orientation.y = 0;
    waypoint16.orientation.z = 0.0791;
    waypoint16.orientation.w = 0.9969;
    waypoints.push_back(waypoint16);*/




    MoveBaseClient ac("move_base", true); // action client to spin a thread by default

    while (!ac.waitForServer(ros::Duration(5.0))) { // wait for the action server to come up
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map"; // set target pose frame of coordinates

    for(int i = 0; i < waypoints.size(); ++i) { // loop over all goal points, point by point
        goal.target_pose.header.stamp = ros::Time::now(); // set current time
        goal.target_pose.pose = waypoints.at(i);
        ROS_INFO("Sending goal");
        ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb); // send goal and register callback handler
        ac.waitForResult(); // wait for goal result

        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            ROS_INFO("The base moved to %d goal", i);
        } else {
            ROS_INFO("The base failed to move to %d goal for some reason", i);
        }
    }
    return 0;
}
