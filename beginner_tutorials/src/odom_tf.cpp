#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

//nav_msgs::Odometry odom_tf;

void poseCallback(const nav_msgs::Odometry& msg){
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg.pose.pose.position.x, 
                        msg.pose.pose.position.y, 0.0));
    tf::Quaternion q;
    
}



int main(int argc, char** argv){

}