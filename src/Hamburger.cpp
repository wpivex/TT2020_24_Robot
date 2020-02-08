#include "hamburger.hpp"

Hamburger *Hamburger::robot = NULL;
Hamburger *Hamburger::getRobot() {
	if (robot == NULL) {
		robot = new Hamburger();
	}
	return robot;
}

Hamburger::Hamburger() {
	drive = std::make_shared<Drive>();
	MotorGroup intakeMotors({Motor(INTAKE_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 Motor(INTAKE_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 Motor(INTAKE_BACK_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
						 	 Motor(INTAKE_BACK_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	intake = std::make_shared<MotorGroup>(intakeMotors);

	MotorGroup fourbarMotors({Motor(FOURBAR_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
							Motor(FOURBAR_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
	});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);

	MotorGroup armMotors({Motor(ARM_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
		Motor(ARM_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	armMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	arm = std::make_shared<MotorGroup>(armMotors);

}

void Hamburger::opControl(pros::Controller &joystick) {
	drive->opControlDrive(joystick);
	opControlFourbar(joystick);
	opControlIntake(joystick);
	opControlArm(joystick);
}


void Hamburger::runIntake(int power) {
	intake->moveVelocity(power);
}

void Hamburger::opControlIntake(pros::Controller &joystick) {
	int r1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
	int r2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

	if (r1) {
		runIntake(200);
	}
	else if (r2) {
		runIntake(-200);
	}
	else {
		runIntake(0);
	}
}

void Hamburger::opControlFourbar(pros::Controller& joystick) {
	if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		moveFourbar2(100);
	} else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		moveFourbar2(-100);
	} else {
		moveFourbar2(0);
	}
}

void Hamburger::opControlArm(pros::Controller& joystick) {
	if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
		moveArm(100);
	} else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
		moveArm(-100);
	} else {
		moveArm(0);
	}
}

void Hamburger::moveFourbar(int power) {
	// if going up, throttle the value
	if(power > 0) {
		double fourbarPos = fourbar->getPosition();
		double numerator = (FOURBAR_UP_VALUE - fourbarPos) * FOURBAR_GAIN;
		double ratio = (double)(abs(numerator)) / FOURBAR_UP_VALUE;
		int velocity = power * ratio;

		if(fourbarPos >= FOURBAR_UP_VALUE) {
			velocity = 0.0;
		}
		else if(velocity < FOURBAR_UP_MIN_VEL) {
			velocity = FOURBAR_UP_MIN_VEL;
		}

		fourbar->moveVelocity(velocity);

	} else {
		// full speed down
		fourbar->moveVelocity(power);
	}
}

void Hamburger::moveFourbar2(int power) {
	if(power > 0) {
		double numerator = FOURBAR_UP_VALUE - fourbar->getPosition() * 9 / 10;
		double ratio = (double)(abs(numerator)) / FOURBAR_UP_VALUE;
		fourbar->moveVelocity(power * ratio);

	} else {
		// full speed down
		fourbar->moveVelocity(power);
	}
}

void Hamburger::tiltFourbarScore() {
	fourbar->tarePosition();

	for(int i = 0; i < 56; i++) {
		// double numerator = (FOURBAR_UP_VALUE - fourbar->getPosition()) * FOURBAR_GAIN;
		// double ratio = (double)(abs(numerator)) / FOURBAR_UP_VALUE;
		// int velocity = 100 * ratio;
		

		// if(velocity < FOURBAR_UP_MIN_VEL) {
		// 	velocity = FOURBAR_UP_MIN_VEL;
		// }
		// fourbar->moveVelocity(velocity);

		double numerator = FOURBAR_UP_VALUE - fourbar->getPosition() * 9 / 10;
		double ratio = (double)(abs(numerator)) / FOURBAR_UP_VALUE;
		fourbar->moveVelocity(100 * ratio);

		pros::delay(100);
	}

	pros::delay(500);
}

void Hamburger::tiltFourbarRetract() {
	// fourbar->tarePosition();
	fourbar->moveAbsolute(0,100);
}

void Hamburger::moveArm(int power) {
	arm->moveVelocity(power);
}
