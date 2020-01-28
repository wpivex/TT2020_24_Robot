#include "main.h"
#include "hamburger.hpp"

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
	auto robot = Hamburger::getRobot();

	#ifdef BLUE
	robot->drive->chassis->setTurnsMirrored(false);
	#endif

	#ifdef RED
	robot->drive->chassis->setTurnsMirrored(true);
	#endif

	// deploy tray
	robot->deployTray();
	// get four at start
	robot->drive->chassis->getModel()->setMaxVelocity(100);
	robot->runIntake(140);
	robot->drive->chassis->moveDistance(40_in);
	// get stray cube
	robot->drive->chassis->turnAngle(20_deg);
	robot->drive->chassis->moveDistance(5_in);
	// pros::delay(100);
	robot->drive->chassis->moveDistance(-5_in);
	robot->drive->chassis->turnAngle(-20_deg);
	// go to next stack
	robot->drive->chassis->getModel()->setMaxVelocity(130);
	robot->runIntake(40);
	robot->drive->chassis->moveDistance(-27.5_in);
	robot->drive->chassis->turnAngle(100_deg);
	robot->drive->chassis->getModel()->setMaxVelocity(100);
	robot->runIntake(200);
	robot->drive->chassis->moveDistance(21_in);
	robot->drive->chassis->turnAngle(-30_deg);
	// robot->drive->chassis->moveDistance(2_in);
	robot->drive->chassis->turnAngle(-67_deg);
	// get stack of 3
	robot->drive->chassis->getModel()->setMaxVelocity(50);
	robot->runIntake(200);
	robot->drive->chassis->moveDistance(30_in);
	// robot->drive->chassis->moveDistance(-5_in);
	// jiggle
	// robot->runIntake(0);
	// robot->drive->chassis->getModel()->setMaxVelocity(150);
	// robot->drive->chassis->moveDistance(-3_in);
	// robot->runIntake(200);
	// pros::delay(500);
	// robot->drive->chassis->getModel()->setMaxVelocity(100);
	// robot->drive->chassis->moveDistance(9_in);
	// pros::delay(600);
	// robot->drive->chassis->moveDistance(-5_in);
	// go to goal
	// robot->drive->chassis->getModel()->setMaxVelocity(50);
	// robot->drive->chassis->moveDistance(-10_in);
	robot->drive->chassis->getModel()->setMaxVelocity(50);
	robot->runIntake(200);
	robot->drive->chassis->turnAngle(-156_deg);
	robot->drive->chassis->getModel()->setMaxVelocity(100);
	robot->drive->chassis->moveDistance(32_in);
	robot->drive->chassis->getModel()->setMaxVelocity(100);
	robot->runIntake(0);
	robot->drive->chassis->getModel()->forward(50);
	// std::valarray<std::int32_t> initVals = robot->drive->chassis->getModel()->getSensorVals();
	robot->brakeEnable();
	pros::delay(1000);
	robot->drive->chassis->getModel()->stop();
	// std::valarray<std::int32_t> endVals = robot->drive->chassis->getModel()->getSensorVals();

	// if(init)

	// score
	robot->tiltFourbarScore(); // Contains a delay of 5000 millsecs
	robot->drive->chassis->getModel()->forward(-40);
	pros::delay(300);
	robot->drive->chassis->getModel()->stop();
	robot->tiltFourbarRetract();
	// robot->runIntake(-40);
	pros::delay(1000);
	robot->drive->chassis->getModel()->forward(-20);
	pros::delay(1000);
	robot->brakeDisable();
	pros::delay(100);
	robot->drive->chassis->getModel()->stop();
}