/*  Mohamad Khadra
 MAK180017
 CS1337-0U2
 Conway's Game of Life
 Notes:
 When loading in patterns from a file make sure to utilize MAXSIZE to enlarge the array, also if you want the pattern to be loaded
 at a specific point in the grid, then you can adjust the variables xpos and ypos from the readinfromfile function.
 The output of the program could be improved by implementing graphics.
 For very large arrays the program is not very fast, so if a very large array size is needed for the grid make sure to improve
 the code.
 The output for what represents a live cell and a dead cell can be changed if a different output is desired.
 The loop for displaying the game is infinite so make sure to just exit the program when done or there could be a loop control
 variable to stop the game after a certain amount of iterations.
 
 REMEMBER TO ALWAYS USE GETLINE WHEN READING IN FILENAMES
 */
#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
//#include <conio.h> // For kbhit()

using namespace std;

int main()
{
    chooseinitialization(); // User will choose how to initialize grid.
    displaygrid(); // Display the original grid.
    //system("pause"); // User will press enter before game starts.
    while(true) // Infinite Loop to keep making an infinite number of generations.
    {
        newgeneration(); // Calculate the new generation using the rules.
        displaynewgrid(); // Display the new generation.
        //if(kbhit()) // If the keyboard is hit then pause the program to observe the current generation.
            //system("pause");
        copygrid(); // Exchange contents of gridone and gridtwo.
        system("clear"); // Clear the screen for each generation.
    }
    return 0;
}
