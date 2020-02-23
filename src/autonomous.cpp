#include "main.h"
#include "HeLied.hpp"

using namespace okapi;

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	auto robot = HeLied::getRobot();

	////////// Gains for n cubes:
	// robot->drive->chassisPID->setGains(
	// 	{0.0021, 0, 0.000042}, // Distance controller gains
    //     {0.005, 0, 0.000}, // Turn controller gains
    //     {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
	// );

	#ifdef BLUE
	robot->drive->chassis->setTurnsMirrored(false);
	#endif

	#ifdef RED
	robot->drive->chassis->setTurnsMirrored(true);
	#endif

	// Deploy tray
	// TODO fuck

	// drive to in L
	robot->drive->chassis->moveDistance(10_in);
	// robot->lift->

}