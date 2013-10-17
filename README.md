ArdNetTool
==========

An Arduino based Internet Connectivity Tester
--------------

I wrote this code to help a few people I know test network ports at Columbus State University. They were going into all of the dorms armed with a laptop, and pinging the internet to test connectivity. This tool uses the Arduino ethernet shield and some LED's (a couple multicolored) to indicate if the port has given a valid IP address, and if the internet is available. Currently, it pings google via TCP, and has UDP tests as well.
	
Current Status of Project
--------------
Currently, the UDP ping is untested as the TCP ping works fine. The multicolor LED indicates when the Arduino is waiting for an IP address. Of note is that since the Ethernet libraries have a blocking DHCP implementation I ran into some issues. I wanted the color LED to blink or change colors while the Arduino was getting an IP address. However, this does not work with the blocking DHCP. I had to write in a short timeout for the DHCP call (in the , and request a DHCP address over and put the thing in a loop. This was not optimal, so I now use the FlexiTimer2 library to change the led colors while waiting on the Ethernet DHCP.
	
Features to Add:
--------------
I have a graphic LCD that I'm going to be using to give a GUI for the users. In addition, I now have a keypad for input, so that the user will be able to select an IP address to ping. I'm also switching Ethernet hardware to a cheaper chipset, to try to keep the cost of this thing down. 

Since the graphic LCD that I have access to operates only at 3.3v, I may switch from an Arduino Uno to a teensy 3.0. The smaller footprint and more powerful processor will also help me fit the device in a handheld unit, and multitask with networking.

I will be uploading diagrams of the device once the second prototype is built. I want this to be a handheld network testing device that can be built for under $50. I want it to be something that is higher level than the Fluke stuff that tests wires. Eventually, I'd like to have it display a condition of the network report, complete with bandwidth and latency information.
