# fluid-simulator
My attempt at building a fluid simulator in C++

Built in Visual Studio 2019, Graphics built using OpenGL

Before you run, make sure:
 - includes is linked in Include Directories
   > Properties -> VC++ Directories -> Include Directories -> <Edit...>
 - lib is linked in Library Directories
   > Properties -> VC++ Directories -> Library Directories -> <Edit...>
 - glfw3.lib and opengl32.lib are added to Additional Dependencies
   > Properties -> Linker -> Input -> Additional Dependencies -> <Edit...>
 - Platform and the debugger are set to x64
   > Debug: x64, Properties -> Platform: x64
 - glad.c is added to the Source Files

Troubleshooting:
 - Sometimes CL.exe won't work, usually you're already running the program so close and simply rebuild and it should be fixed
