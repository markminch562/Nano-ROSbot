#!/usr/bin/env python
import rospy
import roslib
from nav_msgs.msg import Odometry
import tf

def handle_odom_tf(msg):

    a = msg.pose.pose.orientation
    br = tf.TransformBroadcaster()
    br.sendTransform((msg.pose.pose.position.x,msg.pose.pose.position.y,msg.pose.pose.position.z),
                     (0,0,msg.pose.pose.orientation.z,msg.pose.pose.orientation.w),
                     rospy.Time.now(),
                     "base_link",
                     "odom_tf")



if __name__ == '__main__':
    rospy.init_node('odom_tf_broadcaster')
    rospy.Subscriber('/odometry',Odometry, handle_odom_tf)
    rospy.spin()