# Nano-ROSbot
Working project for a ROS controlled robot that creates a SLAM map of its enviorment
<h1>
Currently a work in progress
</h1>
<p>
This robot currently works by having Odometry sent to the jetson nano over a TCP connection by using the ROS's roslaunch rosserial_server socket.launch
and using a ESP32. The ESP32 was chosen for this project because of its high clock rate and seperate core for sending wifi messages which allows for one part of the controller to focus only on 
preforming odometry calculations and another for sending messages so there is almost never any fear of motor interupts being missed during a normal serial message.
</p>
<p> The scan information for the bot is created using a old Xbox 360 kinect that is converting a depth cloud to laser scan topic.
</p>
<p>
currently to launch the project you can use run roslaunch beginner_tutorials test1.launch and then roslaunch serialserver socket.launch. <n>
for some reason currently there is a problem that hasnt been solved where tf frames are droped if serialserver is launched first.
</p>
