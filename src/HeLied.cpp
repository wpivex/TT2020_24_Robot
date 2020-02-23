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
	tilter = std::make_shared<Tilter>();

	MotorGroup frontIntakeMotors({Motor(INTAKE_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 Motor(INTAKE_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	MotorGroup backIntakeMotors({ Motor(INTAKE_BACK_LEFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
						 	 Motor(INTAKE_BACK_RIGHT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	frontIntake = std::make_shared<MotorGroup>(frontIntakeMotors);
	backIntake = std::make_shared<MotorGroup>(backIntakeMotors);

	frontIntake->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
	backIntake->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}

void HeLied::opControl(pros::Controller &joystick) {
	opControlCheck(joystick);
	drive->opControlDrive(joystick);
	opControlIntake(joystick);
	switch(armMode) {
		case ARM:
			lift->opControl(joystick);
			break;
		case TILTER:
			tilter->opControl(joystick);
			break;
	}
}


void HeLied::opControlCheck(pros::Controller& joystick) {
	int a = joystick.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
	if(a && a != lastToggleA) {
		armMode = (ArmMode)((armMode + 1) % 2);
		joystick.rumble("-");
	}
	lastToggleA = a;
}

// Runs specific set of intakes. 0 = only front, 1 = only back, anything else = false
void HeLied::runIntake(int power, int set) {
	switch(set) {
		case 0:
			frontIntake->moveVelocity(power);
			break;
		case 1:
			backIntake->moveVelocity(power);
			break;
		default:
			frontIntake->moveVelocity(power);
			backIntake->moveVelocity(power);
			break;
	}
}

void HeLied::opControlIntake(pros::Controller &joystick) {
	int r1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
	int r2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
	int left = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

	switch(armMode) {
		case ARM:
			if (r1) {
				runIntake(200, 0);
				runIntake(0, 1);
			}
			else if (r2) {
				runIntake(-200, 0);
				runIntake(0, 1);
			} else {
				runIntake(0);
			}
			break;
		case TILTER:
			if (r1) {
				runIntake(200);
				tilter->moveTraySliderVoltage(12000);
			}
			else if (r2) {
				runIntake(-200);
				tilter->moveTraySliderVel(-100);
			} else {
				runIntake(0);
				tilter->moveTraySliderVoltage(-6200);
			}
			if(left) {
				backIntake->moveVoltage(-1000);
			}
			break;
	}
}

