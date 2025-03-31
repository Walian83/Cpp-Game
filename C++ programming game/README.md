<!-- ABOUT THE PROJECT -->
#  Awesome 2D Fantasy Shooter

## Game Description
Run around and kill enemies that are spawning, get the highest score you can and relax by enjoying the music.

Features:
* Kill incoming enemies
* Relaxing music with fantasy vibes
* Get the highest score you can

## Controls / How to Play
- Use "WASD" to walk around
- Use "Spacebar" to shoot

## Dependencies
* SDL library

## Target platforms
Support Windows x86/x64

Instructions to build on Windows platforms:
1) Load .sln solution with Visual Studio;
2) Select Release configuration, and x64 Architecture;
3) Compile and run the project.

## Benchmarks

Below are two benchmarks which were completed using the performance profiler. As for the CPU performance, it seems to jump slightly whenever there's an input. As for the memory, its usage jumps up when there are objects (and their instances) in the game. More objects = higher RAM usage, although these are some minmal changes at the moment. In this case, it's the amount of bullets on screen/in-game that affects the usage.

CPU Usage
![CPU Usage](https://user-images.githubusercontent.com/91696197/205948562-676e4cdd-3031-492b-82bb-6448699dd73e.png)

Memory Usage
![Memory Usage](https://user-images.githubusercontent.com/91696197/205949152-a75bae90-b8d2-4dfa-8a1a-23e99652d8f6.png)

The screenshot below shows the CPU benchmark of the game, completed using the performance profiler. In the screenshot we can observe that there's a slight spike in the CPU usage in the very beginning when everything is loading (character sprites, tilemap, music, the SDL window, etc.). Then the usage settles down and remains relatively low and steady throughout the game. There are spikes whenever something happens, e.g. bullet spawns, however, these are negligible. Most CPU usage is due to IO and Kernel as can be observed below. 

Final CPU Usage
![CPU Usage - Final](https://user-images.githubusercontent.com/91696197/212234958-0d9ac57b-e342-4d44-9410-88f818bf86fb.png)

The screenshot below shows the Memory (RAM) benchamrk of the game, again, completed using the performance profiler. This screenshot shows memory usage with snapshots at different points in the game. What can be concluded from this is that the memory usage depends on factors such as activating functions and number of objects on the screen. The first snapshot is where the memory usage is the lowest and it is also where there are two enemies on the screen, and the player. The second snapshot is where it rises. As we can see, there's some score saved and only one enemy on the screen, with the other outside of it. The third snapshot was taken immediately after one of the enemies was killed, which activated a function and sent him outside of the screen borders. The fourth, last snapshot is where there was a slightly longer break between the snapshot and the function being activated. Therefore, the enemy usage is slightly lower, but still higher than in the first two, and definitely comparable to the third one. However, a memory leak can be observed, as the memory usage keeps rising (gets to 9 GB on the screenshot, and still going).

Final Memory Usage
![Memory Usage - final](https://user-images.githubusercontent.com/91696197/212234962-64f8e676-d0be-496c-9574-17c9917ac9d3.png)

In conclusion, the CPU and Memory usage aren't very high, which is understandable since the game isn't very big and/or complex. However, it does seem like a bit much at times, considering how simple the game is. Moreover, there is a memory leak somewhere. Some of the things that could have been done in order to improve the code would be using object pooling for the bullets, or writing more efficient code for tilemap collision since the current one is an overkill.
