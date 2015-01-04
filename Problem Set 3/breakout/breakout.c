//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // variable to track bricks destroyed
    char bds[3];
    
    // set initial velocity
    double xvelocity = 2*drand48()+2;
    double yvelocity = xvelocity;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        //if we heard one
        if (event != NULL)
        {   
            if (getEventType(event) == MOUSE_MOVED)
            {
            double x = getX(event) - getWidth(paddle)/2;  
            
            // set up lower and up per bounds so paddle doesn't go off the  board         
            if (x < 0)
                setLocation(paddle, 0, 500);
            else if (x > (WIDTH-getWidth(paddle)))
                setLocation(paddle, WIDTH-getWidth(paddle), 500);
            else
                setLocation(paddle, x, 500);
            }
        }  
        
        // sets the ball in motion
        move(ball, xvelocity, -yvelocity);
        
        // sets rules for bouncing off walls
        if (getX(ball)+getWidth(ball) >= WIDTH)
        {
            xvelocity = -xvelocity;
        }
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }
        else if(getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }
        // if ball exceeds bottom, pause game until click, then break
        else if (getY(ball)+getWidth(ball) >= HEIGHT)
        {
            lives--;
            setLocation(ball, WIDTH/2-10, 200);
            while (true)
            {   
                pause(1);
                GEvent event1 = getNextEvent(MOUSE_EVENT);
                if (event1 != NULL)
                {
                    if (getEventType(event1) == MOUSE_CLICKED) 
                        break;     
                }
            }
        }

        pause(10);
        
        // get information about collision. If collision is block, remove
        // if paddle, bounce.
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0)
                {
                if (object == paddle)
                {
                    yvelocity = -yvelocity;  
                }
                else
                    {
                    bricks--;
                    sprintf(bds, "%i", 50-bricks);
                    setLabel(label, bds);
                    removeGWindow(window, object);
                    yvelocity = -yvelocity;
                    }                
                }
        }
    }
    
    if (lives == 0)
        setLabel(label, "Game over!");
    else
        setLabel(label, "Victory!");
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    string colors[ROWS] = {"CYAN", "GREEN", "ORANGE", "MAGENTA", "YELLOW"}; 
    // rows is 5, cols is 10
    for (int i = 0; i < ROWS; i++)
        {
        for (int j = 0; j < COLS; j++)
            {
                GRect paddle = newGRect(2+40*j,20*i+30, 35, 10);
                setFilled(paddle, true);
                setColor(paddle, colors[i]); 
                add(window, paddle);
            }
        }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2-10, 200, 20, 20);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH/2-25, 500, 50, 8);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // only need 2 b/c 1 character (digit) and null.    
    GLabel score = newGLabel("");
    setFont(score, "SansSerif-24");
    setColor(score, "GRAY");
    sendToBack(score);
    setLocation(score, WIDTH/2, HEIGHT/2);
    add(window, score);
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
