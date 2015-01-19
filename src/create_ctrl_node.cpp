#include "ros/ros.h"
#include <math.h>
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/LaserScan.h>
#include "std_msgs/String.h"

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  ROS_INFO("I heard: [%f]", msg->range_max);

}

/**
 * This tutorial demonstrates simple sending of velocity commands to the IRobot Create in Gazebo.
 */
int main(int argc, char **argv)
{

  ros::init(argc, argv, "CreateController");

  ros::NodeHandle n;

  ros::NodeHandle l;

  ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  ros::Subscriber sub = l.subscribe("create_scan", 1, chatterCallback);


  ros::Rate loop_rate(5);

  int count = 0;

  while (ros::ok())
  {
    geometry_msgs::Twist cmd_vel;

    cmd_vel.linear.x =sin(count);
    cmd_vel.linear.y = 0;
    cmd_vel.linear.z = 0;
    cmd_vel.angular.x = 0;
    cmd_vel.angular.y = 0;
    cmd_vel.angular.z = 2*sin(count/2);


    vel_pub.publish(cmd_vel);

    ros::spinOnce();

    loop_rate.sleep();

    ++count;
  }

  return 0;
}
