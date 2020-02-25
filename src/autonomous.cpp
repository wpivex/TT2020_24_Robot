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
void deploy() {

}

void score() {

}

void autonomous() {
	auto robot = HeLied::getRobot();

	////////// Gains for n cubes:
	// robot->drive->chassisPID->setGains(
	// 	{0.0021, 0, 0.000042}, // Distance controller gains
    //     {0.005, 0, 0.000}, // Turn controller gains
    //     {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
	// );
    std::shared_ptr<Drive> drive = robot->drive;
    std::shared_ptr<okapi::DefaultOdomChassisController> chassis = drive->chassis;
    std::shared_ptr<Lift> lift = robot->lift;
    std::shared_ptr<Intake> intake = robot->intake;

	#ifdef BLUE
	chassis->setTurnsMirrored(false);
	#endif

	#ifdef RED
	chassis->setTurnsMirrored(true);
    #endif

	chassis->getModel()->setMaxVelocity(150);

	// Deploy tray
	// TODO fuck

	// drive to in L
//	intake->setIntakeMode(IM_IN_FOR_TRAY);
//	drive->driveDist(24_in, 90);
//	pros::delay(500);
//    lift->moveToPos(AP_LOW_HOVER);
//    drive->driveDist(-5_in, 90);
//    chassis->turnAngle(-8_deg);
//    lift->goToPos(AP_LOW_HOVER);
////    intake->setIntakeMode(IM_OFF);
//    drive->driveDist(10_in);
//    lift->goToPos(AP_LOW_HOVER);
//    drive->driveDist(-15_in);
//    lift->goToPos(AP_DOWN);
//    intake->setIntakeMode(IM_IN_FOR_TRAY);
//    drive->driveDist(20_in, 90);
//    chassis->turnToAngle(-40_deg);
//    chassis->getModel()->setMaxVelocity(150);
//    drive->driveDist(11_in, 90);
//    pros::delay(400);
////    drive->driveDist(-10_in);
//    chassis->turnToAngle(0_deg);
//    drive->driveDist(8_in, 90);
//    pros::delay(600);
//    drive->driveDist(-10_in);
//    chassis->turnToAngle(40_deg);
//    drive->driveDist(16_in, 90);
//    drive->driveDist(-5_in, 90);
//    chassis->turnToAngle(60_deg);
//    drive->driveDist(6_in, 60);
//    drive->driveDist(-2_in, 90);
//    chassis->turnToAngle(-120_deg);
//    drive->driveDist(8_in, 90);

    intake->setIntakeMode(IM_IN_FOR_TRAY);
    drive->driveDist(44_in, 70);
    chassis->turnToAngle(90_deg);
    drive->driveDist(52_in, 70);
}