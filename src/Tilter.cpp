#include "Tilter.hpp"
#include "HeLied.hpp"
#include "menu/Menu.hpp"

Tilter::Tilter() {
    MotorGroup fourbarMotors({Motor(FOURBAR_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
							Motor(FOURBAR_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
	});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);
    fourbar->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

    MotorGroup sliderMotors({Motor(SLIDER, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
    slider = std::make_shared<MotorGroup>(sliderMotors);
    slider->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    slider->setCurrentLimit(300);
}

void Tilter::opControl(pros::Controller& joystick) {
    int up = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    int down = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    int y = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
    int x = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_X);

    if (up) {
		moveFourbar(100);
	} else if (down) {
		moveFourbar(-100);
	} else {
		moveFourbar(0);
	}

    // release tray
    // printf("Current: %d\n", slider->getCurrentDraw());
    Menu::getMenu()->addDebugPrint(4, "Current:" + std::to_string(slider->getCurrentDraw()));
    if(y) {
        moveTraySliderVel(200);
    } else if (x) {
        moveTraySliderVel(-200);
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

void Tilter::moveTraySliderVoltage(int voltage) {
    slider->setCurrentLimit(300);
    slider->moveVoltage(voltage);
}

void Tilter::moveTraySliderVel(int vel) {
    slider->setCurrentLimit(12000);
    slider->moveVelocity(vel);
}