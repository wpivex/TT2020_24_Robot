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
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::hold);
	intake = std::make_shared<MotorGroup>(intakeMotors);

	MotorGroup fourbarMotors({Motor(FOURBAR, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
							Motor(FOURBAR2, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
	});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);

	MotorGroup brakeMotors({Motor(TRAY_BRAKE, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
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
	opControlTrayBrake(joystick);
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

void Hamburger::opControlTrayBrake(pros::Controller& joystick) {
	#ifndef DISABLE_PASSIVE_TRAY

  // Use passive brake contorl, enabling brake when tray reaches a specified position

	// Toggle brake if the upward position is reached and the brake is off
	if (abs(fourbar->getPosition() - FOURBAR_BRAKE_ENABLE_VALUE) < FOURBAR_MARGIN_VALUE
		  && !trayBrakeOn) {
		trayBrakeOn = true;
		trayBrakeSetpoint = BRAKE_ENABLE_VALUE;
	}
	// Toggle brake if the disable position is reached and the brake is on
	else if (abs(fourbar->getPosition() - FOURBAR_BRAKE_DISABLE_VALUE) < FOURBAR_MARGIN_VALUE
					 && trayBrakeOn) {
		trayBrakeOn = false;
		trayBrakeSetpoint = BRAKE_DISABLE_VALUE;
	}

	if(trayBrake->getCurrentDraw() >= BRAKE_STALL_CURRENT) {
		trayBrakeSetpoint = trayBrake->getPosition();
	}

	trayBrake->moveAbsolute(trayBrakeSetpoint, BRAKE_MAX_SPEED);

	#else

  // Use manual brake control

	if(trayBrake->getCurrentDraw() >= BRAKE_STALL_CURRENT) {
		trayBrakeSetpoint = trayBrake->getPosition();
	}
	else if(joystick.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
		trayBrakeSetpoint = BRAKE_ENABLE_VALUE;
	}
	else if(joystick.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		trayBrakeSetpoint = BRAKE_DISABLE_VALUE;
	}

	trayBrake->moveAbsolute(trayBrakeSetpoint, BRAKE_MAX_SPEED);

	#endif
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

void Hamburger::tiltFourbarScore() {
	fourbar->tarePosition();

	for(int i = 0; i < 50; i++) {
		double numerator = (FOURBAR_UP_VALUE - fourbar->getPosition()) * FOURBAR_GAIN;
		double ratio = (double)(abs(numerator)) / FOURBAR_UP_VALUE;
		int velocity = 100 * ratio;

		if(velocity < FOURBAR_UP_MIN_VEL) {
			velocity = FOURBAR_UP_MIN_VEL;
		}
		fourbar->moveVelocity(velocity);

		pros::delay(100);
	}

	pros::delay(500);
}

void Hamburger::tiltFourbarRetract() {
	// fourbar->tarePosition();
	fourbar->moveAbsolute(0,100);
}

void Hamburger::brakeEnable() {
	trayBrake->moveAbsolute(BRAKE_ENABLE_VALUE, BRAKE_MAX_SPEED);
}

void Hamburger::brakeDisable() {
	trayBrake->moveAbsolute(BRAKE_DISABLE_VALUE, BRAKE_MAX_SPEED);
}
