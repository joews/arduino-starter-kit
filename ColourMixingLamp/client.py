#!/usr/bin/env python

import gtk.gdk
import sys
import time
import serial

w = gtk.gdk.get_default_root_window()
usb_serial = serial.Serial("/dev/ttyACM1", 9600);

#From http://stackoverflow.com/questions/1605350/how-can-i-grab-the-color-of-a-pixel-on-my-desktop-linux
#Colours don't seem to match colours on screen!
def PixelAt(x, y):
    sz = w.get_size()
    pb = gtk.gdk.Pixbuf(gtk.gdk.COLORSPACE_RGB,False,8,sz[0],sz[1])
    pb = pb.get_from_drawable(w,w.get_colormap(),0,0,0,0,sz[0],sz[1])
    pixel_array = pb.get_pixels_array()
    #print pixel_array[y][x]
    return pixel_array[y][x]

def millis():
    return int(time.time() * 1000)

def get_mouse_pos():
    (x,y,mods) = w.get_pointer()
    return (x,y)

i = 0
last = 0
while True:
    now = millis()

    #Update every tenth of a second
    if last != now and millis() % 100 == 0:
        (x,y) = get_mouse_pos()
        rgb = PixelAt(x, y)
        cmd = ",".join([str(px) for px in rgb]) + ";"
        print cmd
        usb_serial.write(cmd)

    last = now
