How to Build and Run the PPM Image Test.

To simplify development, we will draw pictures by writing
an image output file that can be viewed using an image viewer app.
This way the sources will build and run on all systems.
Realtime or live graphics display libraries for C++ are often
operating-system specific or involve more steps to get them going.

This image writing utility provides a minimal inteface to
create an image, clear the image, plot a pixel in a color,
and write the image to an output file.
That's all we need to build a ray tracer.

Let's try running an example to write an image file.

Download source files test.c, easyppm.h, and easyppm.c into your directory.

LINUX lab command-line build
============================
Use the cd command to navigate to the folder that holds the source files.
Run the make command
make -f Makefile_Linux.txt
Run the program by typing and entering...
./test


GUI based IDE build for VS Code, Visual Studio, Repl.IT, etc.
=============================================================
Add source files test.c, easyppm.h, and easyppm.c to your project.
Click the run/build button.


Windows Visual Studio 2022 command-line build
=============================================
Requires MS Visual Studio compiler
https://visualstudio.microsoft.com/vs/community/

Use the Windows search to open X64 Native Tools Command Prompt
Use the cd command to navigate to the folder that holds the source files.
Run the make command
nmake -f Makefile_Win.txt
Run the program by typing and entering...
test