#include "main.h"
#include "hamburger.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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

	// get four at start
	robot->drive->chassis->getModel()->setMaxVelocity(100);
	robot->runIntake(140);
	robot->drive->chassis->moveDistance(43_in);
	// get stray cube
	robot->drive->chassis->turnAngle(20_deg);
	robot->drive->chassis->moveDistance(5_in);
	pros::delay(200);
	robot->drive->chassis->moveDistance(-5_in);
	robot->drive->chassis->turnAngle(-20_deg);
	// go to next stack
	robot->drive->chassis->getModel()->setMaxVelocity(130);
	robot->runIntake(40);
	robot->drive->chassis->moveDistance(-30_in);
	robot->drive->chassis->turnAngle(100_deg);
	robot->drive->chassis->getModel()->setMaxVelocity(100);
	robot->runIntake(200);
	robot->drive->chassis->moveDistance(21_in);
	robot->drive->chassis->turnAngle(-30_deg);
	robot->drive->chassis->moveDistance(2_in);
	robot->drive->chassis->turnAngle(-70_deg);
	// get stack of 3
	robot->drive->chassis->getModel()->setMaxVelocity(80);
	robot->runIntake(200);
	robot->drive->chassis->moveDistance(34_in);
	pros::delay(1000);
	robot->drive->chassis->moveDistance(-5_in);
	// go to goal
	robot->drive->chassis->getModel()->setMaxVelocity(100);
	robot->runIntake(40);
	robot->drive->chassis->turnAngle(-151_deg);
	robot->drive->chassis->moveDistance(34_in);
	robot->runIntake(0);
	robot->drive->chassis->getModel()->forward(30);
	pros::delay(1000);
	robot->drive->chassis->getModel()->stop();
	// score
	robot->runIntake(-100);
	pros::delay(500);
	robot->runIntake(0);
	pros::delay(500);
	robot->tiltFourbarScore();
	pros::delay(5000);
	robot->runIntake(-50);
	robot->drive->chassis->getModel()->forward(-50);
	pros::delay(1000);
	robot->tiltFourbarRetract();
	robot->drive->chassis->getModel()->stop();


	// TODO Write this with actual Odom methods
	// drive to 4 stack
	// robot->drive->chassis->getModel()->setMaxVelocity(100);
	// robot->runIntake(140);
	// robot->drive->chassis->driveToPoint({0_in, 40_in});
	// robot->runIntake(50);
	// // drive back and go to next group of 4
	// robot->drive->chassis->getModel()->setMaxVelocity(200);
	// robot->drive->chassis->turnToAngle(-30_deg);
	// robot->drive->chassis->driveToPoint({0_in, 10_in},true);

	
	// robot->drive->chassis->turnToPoint({24_in, 10_in});
	// robot->drive->chassis->driveToPoint({24_in, 10_in});
	// robot->drive->chassis->turnToPoint({24_in, 38_in});
	// // drive and pick up next group of 4
	// robot->drive->chassis->getModel()->setMaxVelocity(140);
	// robot->runIntake(200);
	// robot->drive->chassis->driveToPoint({24_in, 42_in});
	
	// // drive to goal
	// robot->runIntake(50);
	// robot->drive->chassis->getModel()->setMaxVelocity(140);
	// robot->drive->chassis->turnToPoint({-5_in, 10_in});
	// robot->drive->chassis->driveToPoint({-5_in, 10_in});
	// robot->drive->chassis->getModel()->forward(80);
	// pros::delay(1000);

	// // score
	// robot->runIntake(0);
	// robot->tiltFourbarScore();
	// pros::delay(300);
	// robot->runIntake(-40);
	// robot->drive->chassis->moveDistance(-10_in);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	auto robot = Hamburger::getRobot();
	// ADIEncoder encL(ENCODER_LEFT_DRIVE_TOP,ENCODER_LEFT_DRIVE_BOT,false);
	// ADIEncoder encR(ENCODER_RIGHT_DRIVE_TOP,ENCODER_RIGHT_DRIVE_BOT,true);
	// encL.reset();
	// encR.reset();

	while (true) {
		robot->opControl(master);
		std::valarray<std::int32_t> vals = robot->drive->chassis->getModel()->getSensorVals();
		pros::lcd::set_text(1, "Left Enc: " + std::to_string(vals[0]));
		pros::lcd::set_text(2, "Right Enc: " + std::to_string(vals[1]));
		pros::delay(20);
	}
}
