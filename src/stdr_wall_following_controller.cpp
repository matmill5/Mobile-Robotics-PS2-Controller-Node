// This node: check a predetermined-size box in front of the robot and publish whether if there is any obsticle in it.
#include <ros/ros.h> //Must include this for all ROS cpp projects
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h> //Including the Float32 class from std_msgs
#include <std_msgs/Bool.h> // boolean message 
#include <geometry_msgs/Twist.h> //twist control
#include <vector>
#include <cmath>

bool leftObstacle = false;
bool rightObstacle = false;
int state = 0;

ros::Subscriber lidar_alarm_front_subscriber_;
ros::Subscriber lidar_alarm_left_subscriber_;

ros::Publisher stdr_cmd_vel_publisher_;

void frontCallback (const std_msgs::Bool& check) {
    leftObstacle = check.data;
}

void leftCallback (const std_msgs::Bool& check) {
    rightObstacle = check.data;
}

void stateCheck () {
    
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "stdr_wall_following_controller"); //name this node
    ros::NodeHandle nh; 

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 1);
    stdr_cmd_vel_publisher_ = pub; //! do we need to do this? -->> let's make this global, so callback can use it

    // Create a Subscriber object and have it subscribe to the lidar topic
    ros::Subscriber lidar_alarm_front_subscriber_ = nh.subscribe("robot0/lidar_alarm_front", 1, frontCallback);
    ros::Subscriber lidar_alarm_right_subscriber_ = nh.subscribe("robot0/lidar_alarm_left", 1, leftCallback);

    while(ros::ok){
        switch (state) {
            case 0:

                stateCheck();
                break;
            case 1:

                stateCheck();
                break;
            
        }

        ros::spinOnce();
    }

    //ros::spin();    // this is essentially a "while(1)" statement, except it
                    // forces refreshing wakeups upon new data arrival
                    // main program essentially hangs here, but it must stay alive to keep the callback function alive
    return 0; // should never get here, unless roscore dies
}