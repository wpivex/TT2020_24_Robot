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

    auto robot = HeLied::getRobot();

    // robot->intake->setIntakeMode(IM_OUT_FOR_TOWER);
    robot->lift->goToPos(AP_HIGH_TOWER);
    // robot->intake->setIntakeMode(IM_OUT_FOR_TOWER);
    robot->lift->homeArm();
}

void score() {
    auto robot = HeLied::getRobot();
    auto chassis = robot->drive->chassis;
    // ram the corner
    chassis->getModel()->forward(100);
    pros::delay(1300);
    chassis->getModel()->stop();

    //adjust
    robot->intake->setIntakeMode(IM_SQUISH_STACK);
    pros::delay(4000);
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
    robot->tilter->moveFourbar(-120);
    pros::delay(400);
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



    deploy();
    lift->moveLift(-1000);

    intake->setIntakeMode(IM_IN_FOR_TRAY);
    drive->driveDist(37_in, 70, NO_PRECISION);
    drive->turnToAngle(20_deg);
    drive->driveDist(6_in, 90, NO_PRECISION);
    pros::delay(200);

    drive->turnToAngle(30_deg, 100);
    drive->driveDist(4.5_in, 90);
    intake->setIntakeMode(IM_OFF);
    drive->turnToAngle(145_deg,60);
    intake->setIntakeMode(IM_IN_FOR_TRAY);
    drive->driveDist(26_in, 70);

    // Get isolated
    drive->turnToAngle(48_deg,90);
    drive->driveDist(17_in, 70, NO_PRECISION);
    drive->driveDist(-9_in, 110);

    // Get near center
    drive->turnToAngle(18_deg,90);
    drive->driveDist(19_in, 70, NO_PRECISION);
    drive->driveDist(-7_in, 100);
    drive->turnToAngle(6_deg,90);
    drive->driveDist(12_in, 100, NO_PRECISION);

    // Line up to score
    drive->driveDist(-8_in, 110);
    drive->turnToAngle(-146_deg, 90);
    drive->driveDist(38_in, 190, NO_PRECISION);
    lift->moveLift(-1000);

    // Score
    // score();
}