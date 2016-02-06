# 1942 - Feed The Birds

# FIX:
- add audio sounds  
	start sound -- DONE
	shootFish sound
	birdTwitting
	explosion
	gameOver
	loopSound
	collisionSound

- start screen
    CSD UOC
    new bg ?

- replace "explosion" bitmaps with "koutsoulies"
    

#BUGS
- escape button takes time to close the game!
- an mas xtuphsoun thn wra pou erxontai oi sidefighters k dn exoun kollhsei akoma ston superace
    tote de "kollane" akrivws dipla tou...uparxei keno!
    kai to paixnidi ginetai poluuu argo !


# EXCEPTION META APO WIN STO STARTSCREEN..........(happened once)!
Exception thrown at 0x5DB8FAE2 (d3d9.dll) in 1942-FeedTheBirds.exe: 0xC0000005: Access violation reading location 0x00000014.
If there is a handler for this exception, the program may be safely continued.
STACKFRAME
UpdateTexture() d3d9.dll
allegro 5,0,10'monolith
frames below may be incorrect or missing
.....

#EXCEPTION
meta apo Win -> epistrofh se StartScreen:
exception sthn draw_background() ths Terrain.cpp:
#45.	al_draw_bitmap(this->bgImage, this->x, this->y, 0);
Call Stack:
    startNewGame->
    displayMainScreen()->
    drawBackground()