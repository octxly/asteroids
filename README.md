# Asteroids
A simple game of asteroids made for the Arduino Nano and a 128x64 black and white display.

It's literally asteroids, except now the asteroids are procedurally generated :)

## Why is the code so weird?
The nano has 2kb of ram, however half of it is taken up by the screen buffer (128x64=8192 bits), so that leaves just 1kb for literally everything.
This project uses many optimization techniques that can be found on the full write-up on my website.

__Find the full write-up and demonstration on my website [here](https://julianrees.ca/projects/asteroids)__
