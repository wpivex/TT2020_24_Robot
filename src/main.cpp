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
	robot->drive->chassis->getModel()->setMaxVelocity(140);
	robot->drive->chassis->moveDistance(24_in);
	// robot->drive->chassis->turnAngle(90_deg);
	// pros::lcd::set_text(1, "I am going to drive to 12, 12");
	// robot->drive->chassis->driveToPoint({12_in,12_in});
	// pros::lcd::set_text(1, "I am going to drive to 24, 24");
	// robot->drive->chassis->driveToPoint({24_in,24_in});
	// robot->drive->chassis->stop();

	// robot->runIntake(100);
	// robot->drive->chassis->getModel()->setMaxVelocity(55);

	// robot->drive->chassis->moveDistance(38_in);
	// pros::delay(100);

	// robot->drive->chassis->getModel()->setMaxVelocity(110);
	// robot->drive->chassis->turnAngle(45_deg);
	// robot->runIntake(200);
	// robot->drive->chassis->getModel()->setMaxVelocity(60);
	// robot->drive->chassis->moveDistance(20_in);
	// pros::delay(2000);

	// robot->drive->chassis->getModel()->setMaxVelocity(110);
	// robot->drive->chassis->moveDistance(-30_in);
	// robot->runIntake(0);

	// robot->drive->chassis->turnAngle(125_deg);

	// pros::delay(500);

	// robot->drive->chassis->moveDistance(17_in);
	// pros::delay(500);

	// robot->tiltFourbarScore();

	// pros::delay(5000);

	// robot->runIntake(-50);
	// pros::delay(250);
	// robot->drive->chassis->moveDistance(-15_in);

	// robot->tiltFourbarRetract();

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
