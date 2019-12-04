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
							 Motor(INTAKE_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	intake = std::make_shared<MotorGroup>(intakeMotors);

	MotorGroup fourbarMotors({Motor(FOURBAR, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
							Motor(FOURBAR2, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
	});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);

	MotorGroup brakeMotors({Motor(TRAY_BRAKE, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	trayBrake = std::make_shared<MotorGroup>(brakeMotors);

	// brainDriver = std::make_shared<BrainDriver>(BrainDriver());
}

void Hamburger::opControl(pros::Controller &joystick) {
	drive->opControlDrive(joystick);
	opControlFourbar(joystick);
	opControlIntake(joystick);

	/*
	 * Enable brake when angle of tray reaches 90 degrees
	 * Disable brake when angle of tray reaches below 80ish degrees
	 */
	handleTrayBrake();
}


void Hamburger::runIntake(int power) {
	intake->moveVelocity(power);
}

void Hamburger::opControlIntake(pros::Controller &joystick) {
	int r1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
	int r2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
	int l1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
	int l2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

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
		moveFourbar(100);
	} else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		moveFourbar(-100);
	} else {
		moveFourbar(0);
	}
	// moveFourbar(joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
}

void Hamburger::handleTrayBrake() {
	bool toggleBrake = false;

	// Toggle brake if the upward position is reached and the brake is off
	if (abs(fourbar->getPosition() - FOURBAR_UP_VALUE) < FOURBAR_MARGIN_VALUE
		  && !trayBrakeOn) {
		toggleBrake = true;
	}
	// Toggle brake if the disable position is reached and the brake is on
	else if (abs(fourbar->getPosition() - FOURBAR_BRAKE_DISABLE_VALUE) < FOURBAR_MARGIN_VALUE
					 && trayBrakeOn) {
		toggleBrake = true;
	}

	if(toggleBrake) {
		if(trayBrakeOn) {
			// Brake is disabled once it reaches the disabled position within a margin
			if(abs(trayBrake->getPosition() - BRAKE_DISABLE_VALUE) < BRAKE_MARGIN_VALUE) {
				trayBrakeOn = false;
				trayBrake->moveVelocity(0);
			} else {
				trayBrake->moveVelocity(-20);
			}
		}
		else {
			// Brake is enabled once it reaches the enabled position within a margin
			if(abs(trayBrake->getPosition() - BRAKE_ENABLE_VALUE) < BRAKE_MARGIN_VALUE) {
				trayBrakeOn = true;
				trayBrake->moveVelocity(0);
			} else {
				trayBrake->moveVelocity(20);
			}
		}
	} else {
		trayBrake->moveVelocity(0);
	}
}

void Hamburger::moveFourbar(int power) {
	// if going up, throttle the value
	if(power > 0) {
		double numerator = (FOURBAR_UP_VALUE - fourbar->getPosition()) * FOURBAR_GAIN;
		double ratio = (double)(abs(numerator)) / FOURBAR_UP_VALUE;
		int16_t velocity = power * ratio;

		if(velocity < FOURBAR_UP_MIN_VEL) {
			velocity = FOURBAR_UP_MIN_VEL;
		}
		fourbar->moveVelocity(velocity);
	} else {
		// full speed down
		fourbar->moveVelocity(power);
	}
}

void Hamburger::tiltFourbarScore() {
	fourbar->tarePosition();
	fourbar->moveRelative(FOURBAR_UP_VALUE,50);
}

void Hamburger::tiltFourbarRetract() {
	// fourbar->tarePosition();
	fourbar->moveRelative(0,100);
}
