/*               Ashton Keller
                 Landon Beckley
                 Group: D7
                 CAG 10:20
                 SDP Code                           */

#include <FEHLCD.h>
#include <FEHUtility.h>
#include <FEHRandom.h>



//Function Prototypes
 void drawMenu();
 int difficultyButtons();
void draw_star();
void draw_rectangle(int x, int y);
 

 /*
    Class Game contains attributes of the game
    and represents the game itself. It is a place
    that stores the number of lives and the score, and
    it contains functions to get the score, play through the
    game itself, and move the user.

    -Made by Landon
 */
 class Game
 {
     public:
        Game(int default_score = 0, int default_lives = 0);
        int getScore();
        void playGame(int);
        int move_user(int i);

     private:
        int score;
        int lives;
 };

    /*
    This is the constructor for the game class. It 
    simply sets score and lives to their default values,
    which are zero in this case.

    -Made by Landon
    */
  Game::Game(int default_score, int default_lives)
{
    score = default_score;
    lives = default_lives;
}





/*
This is a class for the enemy objects. It contains variables
for the enemies x and y positions as well as for a random
integer. Member functions include generating a random number,
getting the random number, initializing the enemy to an initial 
position based on the random number, moving the enemy, and getting
the x and y postions of the enemy.

-Made by Landon
*/
class Enemy
{
    public:
        Enemy(int default_x = 0, int default_y = 0, int default_r = 0);
        int* getR();
        void genR(int *);
        void initialize();
        void move();
        int getX();
        int getY();

    private:
        int x,y,r;

};

/*
This is a constructor for the enemy class.
It simply sets x, y, and z to their default values,
which in this case are 0.

-Made by Ashton
*/
Enemy::Enemy(int default_x, int default_y, int default_r)
{
    x = default_x;
    y = default_y;
    r = default_r;
}

 
//Made by Landon and Ashton
int main() {
    // Clear background
    LCD.Clear();
   

    /*The following code represents the menu variable declarations. These are pre-set to allow the main menu to loop while it waits for touch.
    Once touch is detected, the associated functions and conditional structures will turn off the corresponding menu variables and set any sub-menu options */
    int menu_open = 1;
    int difficulty;
    float xTouch, yTouch;
    int game_open = 1;
    int back_button = 1;
   
    Game spaceJunk;
   
   
    /*The following lines of code create the main menu. The function drawMenu draws the main title, text options, and the rectangles. The primary loop game_open loops while the game is still being played
    The secondary loop menu_open loops while the primary menu needs to be opened. */
    drawMenu();
   
    while(game_open == 1)
    {
        while(menu_open == 1)
        {

            Sleep(100);
            LCD.ClearBuffer();

         /*This next section of code detects touch in the "play game category" After the program detects touch in this region, the game ends the menu loop and clears the screen.
    It then calls the function difficult buttons to draw a sub-menu to select the level of difficulty. At this point, both menus work. The difficulty menu brings the player to a semi-functioning came.
    At this point, the actual game does not have a back-button, but all menus have working back buttons*/
         if(LCD.Touch(&xTouch, &yTouch))
        {

           
            if((xTouch > 100 && xTouch < 220) && (yTouch > 45 && yTouch < 75))
            {
                LCD.Clear();
                menu_open = 0;
                Sleep(0.1);
                difficulty = difficultyButtons();
             



                /*Difficulty function returns a zero if the player wants to return to the main menu. The other conditional statement detects a one or a two, and draws maps corresponding to the selected level of
                difficulty */
                if (difficulty != 0)
                {
                    
                    spaceJunk.playGame(difficulty);
                    menu_open = 1;

                }

                
                else if (difficulty == 0)
                {
                    menu_open = 1;


                    LCD.Clear();
                    drawMenu();
                    Sleep(100);
                    LCD.ClearBuffer();

                }


            }

             /* The next section of code belongs to the primary menu. It detects touch in the region corresponding to statistics. At this point, the menu option brings the player to a screen that prints
            the statistics that will later be controlled by a function. At this point, the menu option features a working back-button to return to the primary menu*/
            else if((xTouch > 100 && xTouch < 220) && (yTouch > 85 && yTouch < 115))
            {
               
                LCD.Clear();
                menu_open = 0;
                back_button = 1;
                Sleep(0.1);



                LCD.WriteAt("Most Recent Score: ", 10, 10);
                LCD.WriteAt(spaceJunk.getScore(), 10, 30);

                LCD.DrawRectangle(200,195,80,30);
                LCD.WriteAt("Back", 215, 200);

                Sleep(100);
                LCD.ClearBuffer();

                //Prevents previous buttons from being detected by waiting for new touch.
                while (back_button == 1)
                {
                    while (!LCD.Touch(&xTouch, &yTouch)) {}

                    if((xTouch > 200 && xTouch < 280) && (yTouch > 195 && yTouch < 225))
                    {

                       
                        back_button = 0;
                        menu_open = 1;

                        LCD.Clear();
                        drawMenu();
                        Sleep(300);
                        LCD.ClearBuffer();

                    }

                }

               
             
            }


            /* The next section of code belongs to the primary menu. It detects touch in the region corresponding to rules. The included rules are the basic instructions to operate the game. It discusses how the user moves
             and how to block enemies. */
            else if((xTouch > 80 && xTouch < 250) && (yTouch > 125 && yTouch < 155))
            {
                LCD.Clear();
                menu_open = 0;
                back_button = 1;


               
                LCD.WriteAt("Rules:",10,10);
                LCD.WriteAt("Tap the X's to move.",10,30);
                LCD.WriteAt("Block the incoming debris",10,50);
                LCD.WriteAt("From hitting your ship ",10,70);
                LCD.WriteAt("If you take too many hits,",10,90);
                LCD.WriteAt("You lose",10,110);
                LCD.WriteAt("You may adjust the game",10,130);
                LCD.WriteAt("difficulty to play with",10,150);
                LCD.WriteAt("One or Three lives.",10,170);

                LCD.DrawRectangle(200,195,80,30);
                LCD.WriteAt("Back", 215, 200);

                     
                Sleep(100);
                LCD.ClearBuffer();

                while (back_button == 1)
                {
                    while (!LCD.Touch(&xTouch, &yTouch)) {}

                    if((xTouch > 200 && xTouch < 280) && (yTouch > 195 && yTouch < 225))
                    {

                       
                        back_button = 0;
                        menu_open = 1;

                        LCD.Clear();
                        drawMenu();
                        Sleep(300);
                        LCD.ClearBuffer();

                    }

                }


            }



            /* The next section of code belongs to the primary menu. It detects touch in the region corresponding to credits. At this point, the menu option brings the player to a screen that prints
            the author names. At this point, we have no used external sources, so only author credits are included*/
            else if((xTouch > 80 && xTouch < 250) && (yTouch > 165 && yTouch < 185))
            {
                LCD.Clear();
                menu_open = 0;
                back_button = 1;


                LCD.WriteAt("Made by Ashton Keller and",10,10);
                LCD.WriteAt("Landon Beckley",10,30);
                LCD.WriteAt("OSU FEH Proteus Guide",10,50);
                LCD.WriteAt("Proteus Graphics", 10, 70);
                LCD.WriteAt("Introducton", 10, 90);

                LCD.DrawRectangle(200,195,80,30);
                LCD.WriteAt("Back", 215, 200);


               
                while (back_button == 1)
                {
                    while (!LCD.Touch(&xTouch, &yTouch)) {}

                    if((xTouch > 200 && xTouch < 280) && (yTouch > 195 && yTouch < 225))
                    {

                       
                        back_button = 0;
                        menu_open = 1;

                        LCD.Clear();
                        drawMenu();
                        Sleep(300);
                        LCD.ClearBuffer();

                    }

                }

               
            }


             /*This is the final conditional statement for the primary menu. Upon selecting this option, the game takes the player to a brief "Thanks for Playing" screen. It then sets the loop variables to false,
            thus ending the game*/
            else if((xTouch > 100 && xTouch < 220) && (yTouch > 205 && yTouch < 235))
            {
                LCD.Clear();
                LCD.WriteAt("Thanks for Playing!",0,10);
                Sleep(3.0);
                menu_open = 0;
                game_open = 0;
            }
        }
        }
        LCD.Update();
    }
    return 0;
}







//Function Definitions

/* The draw_rectangle function is designed to help the game programmers. It simply accepts the x and y input for the upper
left hand corner of a rectangle of length 120 and width 30. It prevents the draw menu function from being filled with repeating code. This was made by
Ashton Keller*/
void draw_rectangle(int x, int y)
{
    LCD.SetFontColor(BLACK);
    LCD.DrawRectangle(x,y,120,30);
    LCD.FillRectangle(x,y,120,30);
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(x,y,120,30);


}

/* The draw_star function is used to fill the primary menu screen with stars. It first fill a 3x3 array with star pixel art. It then uses random number 
to fill  the background with the star pixel art. This was made by Ashton Keller*/
void draw_star()
{
        LCD.Clear();
      
        //Creates array to draw star
        int colorarray[3][3]

        {
            {BLACK, PALEGOLDENROD,BLACK},
            { PALEGOLDENROD, PALEGOLDENROD, PALEGOLDENROD},
            {BLACK, PALEGOLDENROD,BLACK}

        };

        //loops for 325 times to draw that many stars in the background
        for(int k=0;k<325;k++)
        {
               
                //Picks random x and y values to plot the stars
                int x_rand = rand() % 321;
                int y_rand = rand() % 240;
               
                for(int i=0; i<3; i++)
                    {
                        for(int j=0; j<3; j++)
                        {

                            //plots the generated stars on the background
                            LCD.SetFontColor(colorarray[j][i]);
                            LCD.DrawPixel(i+x_rand,j+y_rand);
                           
                        }

                    }
                }  
               
               
                LCD.Update();

         

}

/* The function draw menu encapsulates the start menu graphics. This function uses the draw features found in the
LCD library  to print the title of the game to the screen. It then prints five rectangles to serve as our buttons
The LCD.Write feauture is then used to print the names of each menu category to the screen. Because this function
does not return a value, its return-type is void

-Made by Landon
*/
void drawMenu()
{
    //Draw the Menu
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    draw_star();
   

    LCD.SetFontColor(BLACK);
    LCD.DrawRectangle(100,10,120,30);
    LCD.FillRectangle(100,10,120,30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Space Junk", 100, 15);

    draw_rectangle(100,45);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Play",130,50);


    draw_rectangle(100,85);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Stats", 130, 90);

    draw_rectangle(100,125);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Rules", 130, 130);

    draw_rectangle(100,165);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Credits", 120, 170);

    draw_rectangle(100,205);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Quit", 130, 210);

    LCD.Update();

}

/*The difficulty function then creates the sub-menu that is found after clicking the play option in the main menu
Difficulty prints the options "easy", "hard", and "back" to the screen. The function then accepts touch.
If the region is touched with the "easy" option, the function will return a one. This is used in later functions
to set the number of lives and draw the specified map. A touch in the "hard" region will output a two, which
will be used to adjust the player's number of lives. A touch in the "back" region ouputs a zero, which can then
be used in combination with the drawmenu() function to return to the primary menu

-Made by Landon and Ashton
*/
int difficultyButtons()
{
    float xTouch, yTouch;
    int difficulty;
    int buttonsOpen = 1;
    LCD.WriteAt("Select Difficulty", 60, 40);

    LCD.DrawRectangle(100,80,120,30);
    LCD.WriteAt("Easy",130,85);

    LCD.DrawRectangle(100,120,120,30);
    LCD.WriteAt("Hard", 130, 125);

    LCD.DrawRectangle(100,160,120,30);
    LCD.WriteAt("Back", 130, 165);



     //This function loops while the difficulty menu needs to be open
    while(buttonsOpen == 1)
    {
        if(LCD.Touch(&xTouch, &yTouch))
            {
                //Establishes touch region to set easy boundary
                if((xTouch > 100 && xTouch < 220) && (yTouch > 80 && yTouch < 110))
                {
                    difficulty = 1;
                    LCD.Clear();
                    buttonsOpen = 0;
                }
                //Establishes region to set hard boundary
                if((xTouch > 100 && xTouch < 220) && (yTouch > 120 && yTouch < 150))
                {
                    difficulty = 2;
                    LCD.Clear();
                    buttonsOpen = 0;
                }
                //Establishes the region for the back button
                if((xTouch > 100 && xTouch < 220) && (yTouch > 160 && yTouch < 180))
                {
                   
                    difficulty = 0;     ///This variable is used to escape to the primary menu
                    LCD.Clear();
                    buttonsOpen = 0;
                   
                }





            }  
    }
    LCD.Update();
    return difficulty;
}

/*
Move user is designed to accept user touch in one of three y-levels.
If the top rgion corresponding to the top "x" is selected, the program will
cover the other two regions with black squares and then redraw the x's.
It then draws the grey rectangle where the user touched. This operatioin is the same for
the other locations. Additonally, this function returns the user's previous location. By setting
the input of the function to the output of the function, this function uses 
a switchcase structure to  animate "teleporting" by drawing a purple square
over the user's last location before covering it with another black square.

-Made by Ashton
*/
int Game::move_user(int i)
{

    LCD.ClearBuffer();

    //sets variables for user position
    float x_user, y_user;

    //waits while there is no touch to the screen
    
    //Accepts user input
    if(!LCD.Touch(&x_user,&y_user))
    {
        return i;
    }
    else if (LCD.Touch(&x_user, &y_user))
    {
        
       //teleport feature
           LCD.ClearBuffer();
           if ( (y_user > 50 && y_user < 80) || (y_user > 105 && y_user < 135) || (y_user > 170 && y_user < 200))
           {
              if(x_user > 70 && x_user < 100)  
              {
                switch (i)
                {
                    case 1:
                        LCD.SetFontColor(PURPLE);
                        LCD.DrawRectangle(70,50,30,30);
                        LCD.FillRectangle(70,50,30,30);
                        LCD.Update();
                        Sleep(100);

                        LCD.SetFontColor(BLACK);
                        LCD.DrawRectangle(70,50,30,30);
                        LCD.FillRectangle(70,50,30,30);
                        LCD.Update();
                        break;

                    case 2:
                        LCD.SetFontColor(PURPLE);
                        LCD.DrawRectangle(70,105,30,30);
                        LCD.FillRectangle(70,105,30,30);
                        LCD.Update();
                        Sleep(100);

                        LCD.SetFontColor(BLACK);
                        LCD.DrawRectangle(70,105,30,30);
                        LCD.FillRectangle(70,105,30,30);
                        LCD.Update();
                        break;

                    case 3:
                        LCD.SetFontColor(PURPLE);
                        LCD.DrawRectangle(70,170,30,30);        
                        LCD.FillRectangle(70,170,30,30);
                        LCD.Update();
                        Sleep(100);

                        LCD.SetFontColor(BLACK);
                        LCD.DrawRectangle(70,170,30,30);
                        LCD.FillRectangle(70,170,30,30);
                        LCD.Update();
                        break;
                }
              }
           }






        if((x_user > 70 && x_user < 100) && (y_user > 50 && y_user < 80))
        {
            i=1;    

            //draws black rectangles in other locations
            LCD.SetFontColor(BLACK);
            LCD.DrawRectangle(70,105,30,30);
            LCD.FillRectangle(70,105,30,30);

            LCD.DrawRectangle(70,170,30,30);
            LCD.FillRectangle(70,170,30,30);

            //Draws white x user locations
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("X", 78, 105);
            LCD.WriteAt("X", 78, 170);

            //Moves user block
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(70,50,30,30);
            LCD.FillRectangle(70,50,30,30);

            //updates LCD
            LCD.Update();

       
        }//first section of grid structure

        if((x_user > 70 && x_user < 100) && (y_user > 105 && y_user < 135))
        {
            i=2;

            //draws black rectangles in other locations
            LCD.SetFontColor(BLACK);
            LCD.DrawRectangle(70,50,30,30);
            LCD.FillRectangle(70,50,30,30);

            LCD.DrawRectangle(70,170,30,30);
            LCD.FillRectangle(70,170,30,30);

            //Draws white x user locations
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("X", 78, 50);
            LCD.WriteAt("X", 78, 170);

            //Moves user block
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(70,105,30,30);
            LCD.FillRectangle(70,105,30,30);

            //updates LCD
            LCD.Update();

       
        }//second section of grid structure

        if((x_user > 70 && x_user < 100) && (y_user > 170 && y_user < 200))
        {
            i=3;

            //draws black rectangles in other locations
            LCD.SetFontColor(BLACK);
            LCD.DrawRectangle(70,50,30,30);
            LCD.FillRectangle(70,50,30,30);

            LCD.DrawRectangle(70,105,30,30);
            LCD.FillRectangle(70,105,30,30);

            //Draws white x user locations
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("X", 78, 50);
            LCD.WriteAt("X", 78, 105);

            //Moves user block
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(70,170,30,30);
            LCD.FillRectangle(70,170,30,30);

            //updates LCD
            LCD.Update();

       
        }//third section of grid structure


        return i;
    }//touch if
   

    
}



/*
Function that contains the actual game logic
This function takes the difficulty, either a 1 or a 2, as the argument.
It initializes score to zero, clears the screen, and draws the game, which includes
the three X's, the player, the space station, and circles representing lives.
If difficulty is 1 (easy), three circles are drawn and the player is given three lives.
If difficulty is 2 (hard), one circle is drawn and the player is given one life.
Then, the enemy is generated. An instance of the enemy class is initialized, along with a int pointer
variable that stores the address of the enemy's r variable. genR() and initialize() are called to initialize the first enemy.
Next is a while loop that loops while the user has more than 0 lives. Inside the loop, it updates and displays the score and calls enemy1.move()
and move_user(). After this is a sleep statement that allows it to look like the rectangle is continuously moving across the screen.
The loop also checks for collisions. If the enemy hits the space station, remove turn a circle off, decrease lives by 1, and erase the enemy.
If the enemy hits the player, erase the enemy and increase the score. Every time a collision occurs, call genR() and initialize() again.
After the user runs out of lives, a message is displayed, it waits a few seconds, and then returns to the menu.

-Made by Landon and Ashton
*/
void Game::playGame(int d)
{
   
    //Initialize score to zero
    score = 0;

    //Draw the space station (rectangle and four 'windows')
    LCD.Clear();
    LCD.SetFontColor(GRAY);
    LCD.DrawRectangle(0,0,40,239);
    LCD.FillRectangle(0,0,40,239);
    LCD.SetFontColor(BLACK);
    LCD.DrawCircle(20, 50, 10);
    LCD.DrawCircle(20, 100, 10);
    LCD.DrawCircle(20,150,10);
    LCD.DrawCircle(20,200,10);
    LCD.SetFontColor(BLUE);
    LCD.FillCircle(20, 50, 9);
    LCD.FillCircle(20, 100, 9);
    LCD.FillCircle(20,150,9);
    LCD.FillCircle(20,200,9);

    //Draw the user in the middle position
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(70,105,30,30);
    LCD.FillRectangle(70,105,30,30);

    //If easy difficulty
    if(d == 1)
    {
        //Draw three circles to represent three lives
        LCD.SetFontColor(RED);
        LCD.DrawCircle(300,20,10);
        LCD.FillCircle(300,20,8);
        LCD.DrawCircle(270,20,10);
        LCD.FillCircle(270,20,8);
        LCD.DrawCircle(240,20,10);
        LCD.FillCircle(240,20,8);

        //Draw three X's to tell the user where to click
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("X", 78, 50);
        LCD.WriteAt("X", 78, 105);
        LCD.WriteAt("X", 78, 170);

        //Set lives to 3
        lives = 3;

    }

    //If difficulty is hard
    else if(d == 2)
    {
        //Draw one circle to represent 1 life.
        LCD.SetFontColor(RED);
        LCD.DrawCircle(300,20,10);
        LCD.FillCircle(300,20,8);

        //Draw the circles again
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("X", 78, 50);
        LCD.WriteAt("X", 78, 105);
        LCD.WriteAt("X", 78, 170);

        //Set lives = 1
        lives = 1;
       
    }

     //Sleep to give some time for the user to react initially
    Sleep(1.0);
    //Initialize enemy object
    Enemy enemy1;
    int *enemy1R = enemy1.getR();

    //Generate random number and initialize enemy at the random position
    enemy1.genR(enemy1R);
    enemy1.initialize();

    //Position of user (1= top, 2 = mid, 3 = bottom)
    int A = 2;

   //While the user has lives
    while(lives>0)
    {
        //Display the score
        LCD.SetFontColor(BLACK);
        LCD.WriteAt(score-1, 120,5);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Score: ",45,5);
        LCD.WriteAt(score, 120,5);

        //Call move to move the enemy
        enemy1.move();
        //Call move_user to check for user input
        A = move_user(A);
        //Sleep for a very small amount of time so the enemy appears to be moving across the screen
        Sleep(0.00095);

        //If the enemy hits the space station
        if(enemy1.getX() == 40)
        {
            //Erase the enemy
            LCD.SetFontColor(BLACK);
            LCD.DrawRectangle(enemy1.getX(),enemy1.getY(),20,5);
            //Re-initialize the enemy to a new random location
            enemy1.genR(enemy1R);
            enemy1.initialize();
            //Decrease lives by 1
            lives = lives - 1;

            //If 2 lives are left
            if(lives == 2)
            {
                //Fill in the first circle
                LCD.FillCircle(240,20,8);
            }
            //If 1 life is left
            else if(lives == 1)
            {
                //Fill in the second circle
                LCD.FillCircle(270,20,8);
            }
            //If no lives are left
            else if (lives == 0)
            {
                //Fill in the last circle
                LCD.FillCircle(300,20,8);
            }
            LCD.SetFontColor(WHITE);
        }
        //If enemy hits user
        else if(((enemy1.getX()>=70) && (enemy1.getX() <= 100)) && (*enemy1R == A))
        {
            //Erase the enemy
            LCD.SetFontColor(BLACK);
            LCD.DrawRectangle(enemy1.getX(),enemy1.getY(),20,5);
            //Re-initialize the enemy to a new random location
            enemy1.genR(enemy1R);
            enemy1.initialize();
            //Increase score by 1
            score = score + 1;
        }
        
    }

    /*
    Clear the screen
    Print a game over message and the final score
    Wait 5 seconds
    Clear the screen
    Return to the menu
    */
    LCD.Clear();
    LCD.WriteAt("Game Over!",10,20);
    LCD.WriteAt("Your Final Score Was: ",10,40);
    LCD.WriteAt(score,270,40);
    Sleep(5.0);
    LCD.Clear();
    drawMenu();
   
   //LCD.Update()
    while(true)
    {
        LCD.Update();
        break;
    }

}

//Returns the score (so it can be accessed outside of the game class)
//Made by Landon
int Game::getScore()
{
    return score;
}

//Returns the address of r, the random number generated for the enemy's position (so it can be accessed outside of the enemy class)
//Made by Landon
int* Enemy::getR()
{
    return &r;
}

/*Generates the random number for the enemy's position.
Takes the address of a variable
Stores a random integer between 1 and 3 as the value at that address

-Made by Landon and Ashton
*/
void Enemy::genR(int *a)
{
   //Stores a random integer between 1 and 3 as the value at address a.
    *a = (Random.RandInt() % 3) + 1;
}


/*
Function to set enemy's starting position (To be called after genR)

The function genR() generates either a 1, 2, or 3, which corresponds to the top,
middle, and bottom positions respectively. This function checks to see what the random
number is and assigns the initial postion accordingly.

-Made by Landon and Ashton
*/
void Enemy::initialize()
{
    //If 1 is generated
    if(r == 1)
    {
        //Assign coordinates to top postion and draw the rectangle
        x = 270;
        y = 55;
        LCD.DrawRectangle(x,y,20,5);
    }
    //If 2 is generated
    else if (r == 2)
    {
        //Assign coordinates to middle postion and draw the rectangle
        x = 270;
        y = 110;
        LCD.DrawRectangle(x,y,20,5);
    }
    //If 3 is generated
    else if (r == 3)
    {
        //Assign coordinates to bottom position and draw the rectangle.
        x = 270;
        y = 175;
        LCD.DrawRectangle(x,y,20,5);
    }
}

/*
Function to move the enemy
This function 'erases' the current rectangle by drawing a new one over it in black
and then redraws another one in white 2 pixels to the left.

-Made by Landon and Ashton
*/
void Enemy::move()
{
    //Erase old rectangle
    LCD.SetFontColor(BLACK);
    LCD.DrawRectangle(x,y,20,5);

    //Decrease X
    x = x - 2;

    //Draw new rectangle in new position
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(x,y,20,5);
    LCD.WriteAt("X", 78, 50);
    LCD.WriteAt("X", 78, 105);
    LCD.WriteAt("X", 78, 170);
}

//Returns the x value of the enemy (so it can be accessed outside of the enemy class)
//Made by Landon
int Enemy::getX()
{
    return x;
}

//Returns the y value of the enemy (so it can be accessed outside of the enemy class)
//Made by Landon
int Enemy::getY()
{
    return y;
}

