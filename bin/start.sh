sudo rmmod v4l2loopback
sudo modprobe v4l2loopback devices=4
screen -dmS $USER ./../../lpmtX2/bin/lpmtX2 
TITLE="lpmtX2"
WINDOW_XID=$(xwininfo -tree -root -all | egrep $TITLE | sed -e 's/^ *//' | cut -d\  -f1)
gst-launch-1.0 ximagesrc xid=$WINDOW_XID ! video/x-raw,framerate=30/1 ! videoconvert ! queue ! -vvv v4l2src device=/dev/video4

#screen -dmS $USER ./remoteX-1
