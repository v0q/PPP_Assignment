# PPP_Assignment2
PPP Assignment 2 Super Stardust HD Prototyping<br />
Super Stardust © by Housemarque<br />
https://github.com/v0q/PPP_Assignment2

# Installation instructions:

qmake<br />
make clean<br />
make<br />
./super_stardust<br />
<br />
If the ship is moving sideways (rotated 90 degrees),<br />
Remove the #ifdef LINUX ... #endif (leave what's in <br />
DARWIN defs in the code). This was a bit of a hacky<br />
solution where on the uni machines the models and texture<br />
coordinates were rotated 90 degrees and I wasn't able to<br />
figure out what was wrong within the time limit.<br />
<br />
The places where this hacky solution is used are:<br />
Player.cpp 	- lines: 	56	 - 63<br />
Player.cpp 	- lines: 	118	 - 122<br />
World.cpp 	- lines:	 43	 - 50<br />

# Instructions:

Moving:<br />
Game Controller
<p>Left stick to move<br />
Right stick to aim and fire</p>
Keyboard
<p>W 	- up<br />
S 	-	down<br />
A 	- left<br />
D 	- right<br />
<br />
SPACE 	- shoot<br />
<br />
LEFT ARROW 		- turn aim ccw<br />
RIGHT ARROW 	- turn aim cw</p>

# Initial design
![here](SSClasses.png)
![here](GLClasses.png)