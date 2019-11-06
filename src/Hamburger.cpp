#include "hamburger.hpp"

Hamburger *Hamburger::robot = NULL;
Hamburger *Hamburger::getRobot() {
	if (robot == NULL) {
		robot = new Hamburger();
	}
	return robot;
}

Hamburger::Hamburger() {
	MotorGroup left({Motor(DRIVE_LEFT_FRONT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_MID_FRONT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_MID_BACK, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_BACK, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	MotorGroup right({Motor(DRIVE_RIGHT_FRONT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_MID_FRONT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_MID_BACK, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_BACK, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	drive = std::make_shared<Drive>(left, right);

	MotorGroup intakeMotors({Motor(INTAKE_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 Motor(INTAKE_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	intake = std::make_shared<MotorGroup>(intakeMotors);
	
	MotorGroup fourbarMotors({Motor(FOURBAR, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);

	// brainDriver = std::make_shared<BrainDriver>(BrainDriver());
}

void Hamburger::opControl(pros::Controller &joystick) {
	drive->run(joystick);
	opControlFourbar(joystick);
	opControlIntake(joystick);
}


void Hamburger::runIntake(int power) {
	intake->moveVelocity(power);
}

void Hamburger::opControlIntake(pros::Controller &joystick) {
	if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		runIntake(200);
	}
	else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		runIntake(-200);
	}
	else {
		runIntake(0);
	}
}

void Hamburger::opControlFourbar(pros::Controller& joystick) {
	if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		moveFourbar(100);
	} else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		moveFourbar(-100);
	} else {
		moveFourbar(0);
	}
}

void Hamburger::moveFourbar(int power) {
	fourbar->moveVelocity(power);
}

void Hamburger::tiltFourbarScore() {
	fourbar->tarePosition();
	fourbar->moveRelative(1840,100);
}

void Hamburger::tiltFourbarRetract() {
	fourbar->tarePosition();
	fourbar->moveRelative(-1840,100);
}
