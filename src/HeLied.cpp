#include "HeLied.hpp"

HeLied *HeLied::robot = NULL;
HeLied *HeLied::getRobot() {
	if (robot == NULL) {
		robot = new HeLied();
	}
	return robot;
}

HeLied::HeLied() {
	drive = std::make_shared<Drive>();
	lift = std::make_shared<Lift>();

	MotorGroup frontIntakeMotors({Motor(INTAKE_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 Motor(INTAKE_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	MotorGroup backIntakeMotors({ Motor(INTAKE_BACK_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
						 	 Motor(INTAKE_BACK_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	frontIntake = std::make_shared<MotorGroup>(frontIntakeMotors);
	backIntake = std::make_shared<MotorGroup>(backIntakeMotors);

	frontIntake->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
	backIntake->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}

void HeLied::opControl(pros::Controller &joystick) {
	drive->opControlDrive(joystick);
	lift->opControl(joystick);
	tilter->opControl(joystick);
	opControlIntake(joystick);
}


void HeLied::runIntake(int power) {
	if(power != 0) {
		frontIntake->moveVelocity(power);
		backIntake->moveVelocity(power);
	} else {
		frontIntake->moveVelocity(power);
		backIntake->moveVelocity(10);
	}
}

void HeLied::opControlIntake(pros::Controller &joystick) {
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

