/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 * Amelia Tuttle
 **********************************************************************/

#include "acceleration.h"
#include "position.h"    // for Position class
#include "lander.h"      // for Lander class (if needed)
#include "star.h"        // for Star class
#include "uiInteract.h"  // for Interface class
#include "uiDraw.h"      // for draw functions and ogstream
#include "ground.h"      // for Ground class
#include <vector>        // for vector
#include <cstdlib>       // for srand and rand
#include <ctime>         // for time
#include <iostream>

using namespace std;

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator {
public:
    // Constructor
    Simulator(const Position& posUpperRight)
        : ground(posUpperRight), width(posUpperRight.getX()), height(posUpperRight.getY()),
          posLander(posUpperRight), lander(posUpperRight)
    {
        // Initialize stars
        stars.resize(50);
        for (Star &star : stars)
            star.reset(width, height);
    }
    
    // Update simulator
    void update(const Interface* pUI) {
        // Apply gravity to the lander
        const double gravity = -1.625;
        
        // Handle user input and get acceleration
        Acceleration acceleration = lander.input(thrust, gravity);
        
        if (!ground.onPlatform(lander.getPosition(), lander.getWidth()) && !ground.hitGround(lander.getPosition(), lander.getWidth()))
            // Update the lander's position every 0.1 seconds if it hasn't landed anywhere
            lander.coast(acceleration, 0.1);
        
        // Check if conditions for landing or crashing are met
        if ((ground.hitGround(lander.getPosition(), lander.getWidth())) || (ground.onPlatform(lander.getPosition(), lander.getWidth()) && lander.getMaxSpeed() < lander.getSpeed() )) 
        {
            lander.crash(); // Fail, crash!!!
        }
        else if (ground.onPlatform(lander.getPosition(), lander.getWidth()) && lander.getMaxSpeed() >= lander.getSpeed())
        {
            lander.land(); // Success, landed!!!!
        }
    }
    
    // Set the thrust according to user input
    void setThrust(const Interface* pUI) {
        thrust.set(pUI);
    }

    // Draw everything on the screen
    void draw(ogstream &gout) {
        // Draw each star
        for (Star &star : stars) {
            star.draw(gout);
        }

        // Draw the ground
        ground.draw(gout);

        // Draw the lander
        lander.draw(thrust, gout);
        
        // Output speed and fuel level to the screen
        gout.drawText(Position(10, height - 20), ("Speed: " + to_string(lander.getSpeed()) + "m/s").c_str());
        gout.drawText(Position(10, height - 40), ("Fuel: " + to_string(lander.getFuel()) + "lbs").c_str());
        gout.drawText(Position(10, height - 60), ("Mission: " + to_string(missions)).c_str());
        
        if (lander.isDead())
        {
            gout.drawText(Position(475, height - 200), ("CRASH!"));
            gout.drawText(Position(400, height - 220), ("(press spacebar to play again or 'q' to quit)"));
        }
        else if (lander.isLanded())
        {
            gout.drawText(Position(475, height - 200), ("SUCCESS!!"));
            gout.drawText(Position(400, height - 220), ("(press spacebar to play again or 'q' to quit)"));
        }
    }
    
    // Reset the program if the spacebar is pressed
    void reset(const Interface* pUI)
    {
        // Reset game if you are no longer flying and the user presses the space bar
        if (pUI->isSpace() && !lander.isFlying())
        {
            missions += 1;
            lander.reset(posLander);
            ground.reset();
        }
    }
    
    // Exit the program if q is pressed
    void exitProgram(const Interface* pUI)
    {
        if (pUI->isQ() && !lander.isFlying())
            exit(0);
    }

private:
    Ground ground;
    Lander lander;
    Thrust thrust;
    double width;  // Width of the simulation area
    double height; // Height of the simulation area
    Position posLander; // Position of the lander
    vector<Star> stars; // Vector to store stars
    int missions = 1; // Initiate the amount of simulator plays
};

/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    // Cast the void pointer into a simulator object
    Simulator* pSimulator = (Simulator*)p;

    // Update the thrusters based on user input
    pSimulator->setThrust(pUI);

    // Update the simulator (apply physics, handle input, etc.)
    pSimulator->update(pUI);

    // Draw the simulator (including ground, stars, and lander)
    ogstream gout;
    pSimulator->draw(gout);
    
    // Call reset
    pSimulator->reset(pUI);
    
    // Call exit
    pSimulator->exitProgram(pUI);
}


/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Initialize OpenGL
    Position posUpperRight(1000, 1000);
    Interface ui("Lunar Lander", posUpperRight);

    // Initialize the game class
    Simulator simulator(posUpperRight);

    // Set everything into action
    ui.run(callBack, (void*)&simulator);

    return 0;
}
