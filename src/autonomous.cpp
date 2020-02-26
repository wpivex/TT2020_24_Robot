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
    // fuck
}

void score() {
    auto robot = HeLied::getRobot();
    auto chassis = robot->drive->chassis;

    //Starting the tray, delete this when you are done.
    robot->intake->setIntakeMode(IM_IN_FOR_TRAY);
    pros::delay(1000);

    chassis->setMaxVelocity(120);
    chassis->moveDistance(12_in);
    // ram the corner
    chassis->getModel()->forward(100);
    pros::delay(400);
    chassis->getModel()->stop();

    //adjust
    robot->intake->setIntakeMode(IM_SQUISH_STACK);
    pros::delay(3000);
    robot->intake->setIntakeMode(IM_OFF);

    // tilt
    double thresh = 0;
    double tiltUpSetpoint = robot->tilter->FOURBAR_UP_VALUE;
    while(robot->tilter->fourbar->getPosition()  + thresh < tiltUpSetpoint) {
        robot->tilter->moveFourbar(200);
    }
    robot->tilter->moveFourbar(0);

    // release
    robot->tray->moveTraySliderVel(200);

    // back up
    robot->intake->runIntake(-42);
    chassis->getModel()->forward(-50);
    robot->tilter->moveFourbar(-40);
    pros::delay(200);
    robot->tilter->moveFourbar(0);
    chassis->getModel()->stop();
    robot->intake->setIntakeMode(IM_OFF);

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
    lift->moveToPos(AP_DOWN);
    intake->setIntakeMode(IM_IN_FOR_TRAY);
    drive->driveDist(37_in, 70);
    chassis->turnToAngle(20_deg);
    drive->driveDist(6_in, 80);
    drive->driveDist(-5_in, 100);
    chassis->turnToAngle(-42_deg);

    // Into pyramid
    drive->driveDist(15_in, 90);
    drive->driveDist(-7_in, 90);

    // Cross corner
    chassis->turnToAngle(95_deg);
    drive->driveDist(26_in, 70);

    // Get near center goal
    drive->driveDist(-3_in, 130);
    chassis->turnToAngle(60_deg);
    drive->driveDist(11_in, 70);
    drive->driveDist(-9_in, 70);
    chassis->turnToAngle(40_deg);
    drive->driveDist(9_in, 70);

    // Get near close goal
    drive->driveDist(-18_in, 110);
    chassis->turnToAngle(130_deg);
    drive->driveDist(9_in, 70);

    // Line up to score
    drive->driveDist(-11_in, 110);
    chassis->turnToAngle(220_deg);

    // Score
    score();
}