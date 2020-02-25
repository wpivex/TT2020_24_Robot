#include "Tilter.hpp"
#include "HeLied.hpp"
#include "menu/Menu.hpp"

Tilter::Tilter(std::shared_ptr<Tray> _tray) {
    MotorGroup fourbarMotors({Motor(FOURBAR_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
                            Motor(FOURBAR_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
    });
    fourbar = std::make_shared<MotorGroup>(fourbarMotors);
    fourbar->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

    tray = _tray;
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
        float gain = FOURBAR_GAIN;
        if (tray->slider->getPosition() < 150){
            gain = gain * .4;
        }
        int velocity = gain * diff;
        // Add constraints
        velocity = velocity < FOURBAR_UP_MIN_VEL ? FOURBAR_UP_MIN_VEL : velocity;
        velocity = velocity >= power ? power : velocity;
        fourbar->moveVelocity(velocity);
        Menu::getMenu()->addDebugPrint(7, "Diff:" + std::to_string(diff));
        if (diff < 200){
            tray->moveTraySliderVoltage(5000, 100);
        }
        else if (diff < 600){
            tray->moveTraySliderVoltage(-12000, 900);
        }
        else {
            tray->moveTraySliderVoltage(5000, 100);
        }
    } else if (power == 0){
        fourbar->moveVoltage(0);
    } else {
        fourbar->moveVelocity(power);
    }
}
