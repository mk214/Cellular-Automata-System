#ifndef Header_h
#define Header_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
//#include <conio.h> // For kbhit()

using namespace std;

const int MAXSIZE = 60; // Maximum size of the grid.
bool gridone[MAXSIZE][MAXSIZE] = {}; // First grid will be used for generation that will be tested.
bool gridtwo[MAXSIZE][MAXSIZE] = {}; // Grid that will be used to store and display new generation.
int generation = 1; // Counter for which generation is appearing on the screen.

void chooseinitialization();
void randominitialization();
void readinfromfile();
bool didfileopen(string,ifstream &);
void skipcomments(ifstream &);
void displaygrid();
void newgeneration();
int neighborRule(int,int);
void displaynewgrid();
void copygrid();

void chooseinitialization() // For the user to choose how they want the grid to be initialized.
{
    int choice; // Variable will hold user choice for how they want the grid to be initialized.
    cout << "Welcome to the Game of Life!" << endl; // Explain details to the user.
    cout << "Enter 1 to have the grid be randomly initialized" << endl;
    cout << "Enter 2 to have the grid initialized from a file" << endl;
    cin >> choice; // User will enter option.
    
    while(choice != 1 && choice != 2) // Input validation for numbers other than 1 or 2.
    {
        cout << "This is not a valid entry, you have to enter 1 or 2, try again" << endl;
        cin >> choice;
    }
    if(choice == 1) // Condition for random initialization of grid.
        randominitialization();
    if(choice == 2) // Condition to initialize grid from file.
        readinfromfile();
}
void randominitialization() // Randomly initialize the grid.
{
    int initialize, random; // Variables will be used to initialize grid one array.
    srand(time(NULL)); // Seed random number generator.
    
    cout << "How many cells did you want to be initialized?" << endl; // Ask the user the percentage of cells they want to be initialized.
    cin >> initialize; // User will enter percentage.
    
    for(int i = 0; i < MAXSIZE; i++) // Loop to initialize grid one array.
    {
        for(int j = 0; j < MAXSIZE; j++)
        {
            random = (rand() % 100) <= initialize; // Based on percentage chosen by user that percentage of grid one will be initialized.
            gridone[i][j] = random; // Store into grid one.
        }
    }
}
void readinfromfile()
{
    ifstream inputfile; // Input file for data.
    string filename; // Name of file.
    string capture; // Captures lines from text file.
    int i = 0; // Counter to move on to a new row when reading in a pattern file, to know when rest of pattern has to be on a new row.
    bool filestatus; // To check file status when opening the file.
    int xpos = 15, ypos = 10; // Starting positions for the grid to be loaded in from the file at a specific position.
    
    cout << "What is the name of the file you would like to use?" << endl;
    getline(cin,filename); // User will enter the file they want to use.
    
    filestatus = didfileopen(filename,inputfile); // Check file status.
    
    while(filestatus == false) // Error condition if file didn't open.
    {
        cout << "The file name " << filename << " did not work, would you like to try again?" << endl; // Explain error.
        cout << "You can also type exactly Quit or quit if you don't want to try again" << endl;
        getline(cin,filename); // Try another file name.
        if(filename == "Quit" || filename == "quit") // If user wants to quit.
            exit(0); // Terminate the program.
        filestatus = didfileopen(filename,inputfile); // Check file status again.
    }
    
    while(!inputfile.eof()) // Read in data from file.
    {
        skipcomments(inputfile); // Skip all comments and new lines.
        capture = ""; // Reset string to capture data from file each time loop iterates.
        getline(inputfile,capture); // Get entire line.
        for(int k = 0; k < capture.length(); k++) // Go through contents of line to find the cells of the grid that should be set to true.
            if(capture[k] == 'O') // When an O is found, then set the cell to true.
                gridone[i+xpos][k+ypos] = true;
        i++; // Increment i to make sure the next pattern line that is read in, is set on a new row in the grid.
    }
    inputfile.close(); // Close input file.
}
bool didfileopen(string filename, ifstream &inputfile)
{
    inputfile.open(filename);
    if(!inputfile)
        return false;
    else
        return true;
}
void skipcomments(ifstream &inputfile) // Skip over blank spaces and comment lines.
{
    string textline; // Temporary variable that will capture line that is not needed.
    char ch; // Used for peek.
    ch = inputfile.peek(); // Peek into file.
    while(ch == '#' || ch == '\n') // Check file for blank space or comments.
    {
        getline(inputfile,textline); // Capture the unnecessary line.
        if(ch == '#') // Only display comment lines, don't display empty lines captured by getline.
            cout << textline << endl; // Display comment line.
        ch = inputfile.peek(); // Check next character.
    }
}
void displaygrid() // Display the original grid one.
{
    for(int i = 0; i < MAXSIZE; i++) // Nested for loop to display contents of grid one.
    {
        for(int j = 0; j < MAXSIZE; j++)
        {
            if(gridone[i][j] == 1)
                cout << "O" << " "; // True cells will be represented by O
            if(gridone[i][j] == 0)
                cout << "." << " "; // False cells will be represented by .
        }
        cout << endl; // For formatting.
    }
    cout << "Generation: " << generation << endl; // Display the first generation.
}
void newgeneration() // Function will utilize the number of neighbors to determine which cells stay alive.
{
    int neighbors; // Value to be accepted from neighborRule function
    for(int i = 0; i < MAXSIZE; i++) // Loop to iterate through all cells in grid.
    {
        for(int j = 0; j < MAXSIZE; j++)
        {
            neighbors = neighborRule(i,j); // Check for the number of neighbors at the current cell being checked.
            if(gridone[i][j] == true && neighbors == 2) // If the cell is alive and has two neighbors it says alive.
                gridtwo[i][j] = true;
            if(gridone[i][j] == true && neighbors == 3) // If the cell is alive and has three neighbors it stays alive.
                gridtwo[i][j] = true;
            if(gridone[i][j] == true && neighbors == 1) // If the cell is alive and has 1 neighbor it dies from loneliness.
                gridtwo[i][j] = false;
            if(gridone[i][j] == true && neighbors == 0) // If the cell is alive and has no neighbors it dies from loneliness.
                gridtwo[i][j] = false;
            if(gridone[i][j] == true && neighbors > 3) // If the cell is alive and has more than 3 neighbors it dies from overcrowding.
                gridtwo[i][j] = false;
            if(gridone[i][j] == false && neighbors == 3) // If the cell is dead and has 3 neighbors it comes alive.
                gridtwo[i][j] = true;
        }
    }
}
int neighborRule(int row, int col)
{
    int neighbors = 0; // Will hold the number of neighbors near a cell.
    int currentrow = 0, currentcol = 0; // Coordinates of directions being checked around the cell.
    
    int directionx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // All 8 horizontal directions to be checked.
    int directiony[8] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // All 8 vertical directions to be checked.
    
    
    for(int i = 0; i < 8; i++) // Loop through all 8 directions of directionx and directiony.
    {
        currentrow = 0; // Reset currentrow for each iteration of the loop.
        currentcol = 0; // Reset currentcol for each iteration of the loop.
        currentrow = row + directionx[i]; // row and col will be passed from newgeneration function that will be checking
        // each cell, and passing the coordinates of that cell to this function neighborrule
        // to check the neighbors around that cell.
        currentcol = col + directiony[i];
        if(currentrow < 0 || currentrow >= MAXSIZE || currentcol < 0 || currentcol >= MAXSIZE)
            continue; // If the coordinates being checked go out of bounds of array, don't check that direction
        // and go on next iteration of loop.
        neighbors += gridone[currentrow][currentcol]; // Since bool array of 1 and 0 , the number of neighbors can be determined
        // by adding the neighbors of the cell together.
    }
    return neighbors; // Return the calculated number of neighbors.
}
void displaynewgrid() // Display the new grid made by newgeneration function.
{
    for(int i = 0; i < MAXSIZE; i++) // Display the contents of the new grid.
    {
        for(int j = 0; j < MAXSIZE; j++)
        {
            if(gridtwo[i][j] == 1)
                cout << "O" << " ";
            if(gridtwo[i][j] == 0)
                cout << "." << " ";
        }
        cout << endl;
    }
    generation++; // Increment the generation.
    cout << "Generation: " << generation << endl; // Display the generation count.
}
void copygrid() // Once second grid is done being displayed copy it into grid one so the new generation can be processed again.
{
    for(int i = 0; i < MAXSIZE; i++)
        for(int j = 0; j < MAXSIZE; j++)
            gridone[i][j] = gridtwo[i][j]; // Copy gridtwo onto gridone
}
#endif
