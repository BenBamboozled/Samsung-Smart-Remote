# Samsung-Smart-Remote
A "smart" ir remote that I created with a Node Red, nodeMCU, MQTT, HTML, and Javascript/jQuery so I can control my 32-inch Samsung TV from my phone. My TV is a few years old, and does not have any smart TV capabilities, and I wanted to be able to control it from my phone when the remote is lost or I am being lazy and do not want to get up and get the remote. In the past I used a Samsung S5 that had an IR sender and I found it useful, but unfortunately this functionality was removed starting with the S6. 


![ir remote](/screenshot.jpg)

## Required Parts
- NodeMCU, I used a ESP-12E similiar to one found here [on Amazon](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES)

- micro USB cable, to upload code and power NodeMCU

- Infrared Emitter LEDS, I used some I already had on hand but you could use these [LED Emitters from Amazon](https://www.amazon.com/Infrared-Lighting-Electronics-Components-Emitting/dp/B01BVGIZGC/ref=sr_1_4?dchild=1&keywords=ir+emitters+leds&qid=1597689163&sr=8-4)

- small gauge wire, for connecting IR leds to NodeMCU you could also use dupont cables based on how your connecting

- Optionally you may want IR receivers if you plan on creating a remote with a different device or with different codes, if that is so you can by a pack with both emitters and receivers like [these found on amazon](https://www.amazon.com/Gikfun-Infrared-Emission-Receiver-Arduino/dp/B06XYNDRGF/ref=sr_1_3?crid=IMFVEFS9Y39S&dchild=1&keywords=ir+led+receiver&qid=1597689492&sprefix=ir+leds+rec%2Caps%2C190&sr=8-3)

## Prerequisites
- Node Red provides back end for our remote webpage. You can install on a raspberry PI, Docker, your local machine, etc for more info go to https://nodered.org/docs/getting-started/

- MQTT Server, a protocol for devices to communicate. There are a few ways to do this but an open source solution would be Mosquitto read more here https://mosquitto.org/

- Arduino IDE, needed to upload code to nodeMCU board download [here](https://www.arduino.cc/en/main/software).

## Setup
1. Copy the repository 

    `git clone https://github.com/BenBamboozled/Samsung-Smart-Remote`
2. Connect the IR led emitter and nodeMCU. For connecting I referenced this image.![nodeMCU with IR emitters](https://raw.githubusercontent.com/JZ-SmartThings/SmartThings/master/Devices/TVDevice/3.3V%20PICTURES%20%26%20WIRING/IRSender.png)

3. Open arduino IDE, If you havent used a NodeMCU board before you will need to go File > Preferences and paste https://arduino.esp8266.com/stable/package_esp8266com_index.json into the Additional Boards Manager and click OK. Then click Tools > Boards > ESP8266 Boards and make sure NodeMCU 1.0 ESP 12-E is selected and then Tools > Port and make sure correct COM Port is selected. 

4. Now go to File > Open and open the irRemoteNodeMCU.INO included in the repository. You will need to add your wireless network credentials, and also the IP of you MQTT server. If you would like to make your own ir codes you can make changes to this file as well. Then upload the program to board.

5. Next Open node red and click on the hamburger button in the upper right corner, then click import. Now you can browse and import the nodeRedRemote.JSON included in repo .

6. Double click on the template at the top of the flow, now scroll to line 280 of the HTML and add the location of your node Red server. You would also need to make changes to bottom buttons to direct to your favorite channels. You can edit the file more easily through the remote.html included in the repo then paste into the template once changes are made, you would also need to make changes on functions in the nodeMCU file as well. Now click the red Deploy button at the top right of the page. 

7. If everything is configured correctly you should be able to mount the nodeMCU near your TV, if your TV has a usb you can use that or you can plug into a 5v power supply. Now go to http://LOCATION OF NODE RED/remote and try to control TV.

## HOW IT WORKS
The nodeMCU connects to your network and mqtt server and waits to get message with a code, once a message is recieved it sends out ir codes and controls the TV

The Node Red provides the back end to get to webpage, and HTML and jQuery/Javascript send a a certain code based what the user click on to the /feedback page here node red sends the code out and it is received by the nodeMCU and does the correct function based on what the user clicked. 

Everything is based on MQTT, so you could can do many more things like add integrations with home assistant and google home or alexa, I do plan on doing this in the future. You could also control things other than TVs, but you would need to get the raw ir codes with IR receiver like i mentioned earlier.

Since this is based on a Samsung universal remote it should work with most Samsungs TVs except for the favorite channel buttons on the bottom. These channels are based on my most used channels and also my cable provider. If you would want to customoize these buttons you would need to make changes to codes as mentioned above. 

I mostly use this on my phone, So I just add a shortcut to my homescreen from chrome to make it like an app on my phone. It is pretty cool because as long as im connected to my network I can control my TV, I dont need to be pointing my phone at the TV like I had to in the past with my S5.





