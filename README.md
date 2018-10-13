# UltraSonicForkLift

This is the project for the Hackathon 2018 v2

## Description
With this project the BLG challenge should be solved.
The idea is to measure the time in which a fork lift drives loaded or free.

To do this an *Arduino Uno* with some sensors is mounted on the fork of the truck.
The Arduino Udo measures with an ultrasonic sensor if the fork of the truck is loaded.
<br>
This timed information is send in real time to a cloud running on a *Raspberry Pi*.
If the Arduino is offline the data is cached and send later.
Also the information saved permanently in case the Arduino powers of for some reason.
For this case the Arduino has a clock to always know the time. Also when it's offline and reset.

A gyro sensor should measure if the fork lift is driving or standing still.

The cloud manags a *mySQL database* from where the data can be displayed on a website.

Filter, analytics and other data processing is  planed.
On this bases optimization suggestion can be displayed.
