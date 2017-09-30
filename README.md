# How to use
  1. Read master branch's [README.md](https://github.com/mavlink/mavros/blob/master/mavros/README.md#installation)(options)
  2. sudo apt-get install python-catkin-tools python-rosinstall-generator -y

# How to build
```
mkdir mavros_ws/src
cd mavros_ws
catkin init
cd src
git clone https://github.com/SIA-UAVGP/mavros.git
cd mavros
git checkout uavcomp
cd ..
git clone https://github.com/SIA-UAVGP/mavlink-kinetic mavlink
cd mavlink
git checkout master
cd ../..
catkin build mavros
```
  
# How to connect to pixhawk
  Read px4's [doc](http://dev.px4.io/pixhawk-companion-computer.html)
```
roslaunch mavros px4.launch
```
  
  Press safety switch here!
  
```
rosrun mavros mavsafety arm
```
  
```
rosrun mavros offb_node
```

# Simulating with gazebo
```
make posix_sitl_default gazebo
```
```
roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14557"
```
  
# Get the topic's messages
```
rqt_graph
```
```
rosrun rqt_topic rqt_topic
```
