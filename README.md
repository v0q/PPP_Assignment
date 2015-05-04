# PPP_Assignment2
PPP Assignment 2 Super Stardust HD Prototyping<br />
Super Stardust © by Housemarque<br />

# Installation instructions:

To compile type in<br />
"make"<br />
<br />
If the ship is moving sideways (rotated 90 degrees),<br />
Remove the #ifdef LINUX ... #endif (leave what's in <br />
DARWIN defs in the code). This was a bit of a hacky<br />
solution where on the uni machines the models and texture<br />
coordinates were rotated 90 degrees and I wasn't able to<br />
figure out what was wrong within the time limit.
<br />
The places where this hacky solution is used are:<br />
Player.cpp 	- lines: 	56	 - 63<br />
Player.cpp 	- lines: 	118	 - 122<br />
World.cpp 	- lines:	 43	 - 50<br />

# Instructions:

Moving:<br />
Game Controller
<p>Left stick to move
Right stick to aim and fire</p>
Keyboard
<p>W 	- up
S 	-	down
A 	- left
D 	- right

SPACE 	- shoot

LEFT ARROW 		- turn aim ccw
RIGHT ARROW 	- turn aim cw</p>