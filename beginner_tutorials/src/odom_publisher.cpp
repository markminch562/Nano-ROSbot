#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>

class odom_combine
{
    public:
        void chatterCallback(const geometry_msgs::PoseStamped& msg){
            odom.header.stamp = msg.header.stamp;
            odom.header.frame_id = "odom";
            odom.child_frame_id = "base_link";
            odom.pose.pose.position.x = msg.pose.position.x * 0.001;
            odom.pose.pose.position.y = msg.pose.position.y * 0.001;
            odom.pose.pose.position.z = msg.pose.position.z * 0.001;
            odom.pose.pose.orientation = msg.pose.orientation;
            //ROS_INFO("recived value");
            //ROS_INFO("value of: %f",msg.pose.position.x);

            //ros also need to broacast a tranform for the odometry as well
            odom_trans.header.stamp = msg.header.stamp;
            odom_trans.header.frame_id = "odom";
            odom_trans.child_frame_id = "base_footprint";
            odom_trans.transform.translation.x = odom.pose.pose.position.x;
            odom_trans.transform.translation.y = odom.pose.pose.position.y;
            odom_trans.transform.translation.z = odom.pose.pose.position.z;
            odom_trans.transform.rotation = odom.pose.pose.orientation;

            odom_broadcaster.sendTransform(odom_trans);
    
        }
        void chatterCallback2(const geometry_msgs::TwistStamped& msg2){
            odom.twist.twist.linear.x = msg2.twist.linear.x * 0.001;
            odom.twist.twist.angular = msg2.twist.angular;
        }
        void sendPub(){
            pub.publish(odom);
            
            //ROS_INFO("recived twist of: %f", odom.twist.twist.linear.x);
        }
 
        odom_combine(){
            sub1 = nh.subscribe("point_odom", 1, &odom_combine::chatterCallback, this);
            sub2 = nh.subscribe("twist_odom", 1, &odom_combine::chatterCallback2, this);
            pub = nh.advertise<nav_msgs::Odometry>("odometry", 1);
        }

        void send_data(){
            ros::Rate r(10);
            while(ros::ok()){
                sendPub();
      
                ros::spinOnce();
                r.sleep();  
            }
        }
     
    private:
        ros::NodeHandle nh;
        ros::Publisher pub;
        ros::Subscriber sub1;
        ros::Subscriber sub2;
        nav_msgs::Odometry odom;
        geometry_msgs::TransformStamped odom_trans;
        tf::TransformBroadcaster odom_broadcaster;
        
};
void chatterCallback(const geometry_msgs::PoseStamped& msg){
    
}

int main(int argc, char** argv){
    ros::init(argc, argv, "odometry_publisher");
    odom_combine sender;
    //ros::NodeHandle nh;
    
    //ros::Subscriber sub = nh.subscribe("chatter", 1000, &chatterCallback);
    //ros::Subscriber points = nh.subscribe("point_odom", 1, &callback1);
    sender.send_data();


}