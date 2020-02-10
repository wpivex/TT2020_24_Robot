#include "Tilter.hpp"
#include "HeLied.hpp"

Tilter::Tilter() {
    MotorGroup fourbarMotors({Motor(FOURBAR_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
							Motor(FOURBAR_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
	});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);
    fourbar->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}

void Tilter::opControl(pros::Controller& joystick) {
    int up = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    int down = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

    if (up) {
		moveFourbar(100);
	} else if (down) {
		moveFourbar(-100);
	} else {
		moveFourbar(0);
	}
}

void Tilter::moveFourbar(int power) {
    if(power > 0) {
        double curr = fourbar->getPosition();
        double diff = FOURBAR_UP_VALUE - curr;
        int velocity = FOURBAR_GAIN * diff;
        // Add constraints
        velocity = velocity < FOURBAR_UP_MIN_VEL ? FOURBAR_UP_MIN_VEL : velocity;
        velocity = velocity >= power ? power : velocity;
        fourbar->moveVelocity(velocity);
    } else {
        fourbar->moveVelocity(power);
    }
}