#include "Lift.hpp"
#include "HeLied.hpp"
#include "menu/Menu.hpp"

Tray::Tray() {
    MotorGroup sliderMotors({Motor(SLIDER, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
    slider = std::make_shared<MotorGroup>(sliderMotors);
    slider->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    slider->setCurrentLimit(300);
}

void Tray::opControl(pros::Controller& joystick) {
    int y = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
    int x = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_X);
    // release tray
    // printf("Current: %d\n", slider->getCurrentDraw());
    Menu::getMenu()->addDebugPrint(4, "Current:" + std::to_string(slider->getCurrentDraw()));
    Menu::getMenu()->addDebugPrint(5, "Tray Pos:" + std::to_string(slider->getPosition()));
    if(y) {
        moveTraySliderVel(200);
    } else if (x) {
        moveTraySliderVel(-200);
    }
}

void Tray::moveTraySliderVoltage(int voltage, int cur) {
    slider->setCurrentLimit(cur);
    slider->moveVoltage(voltage);
}

void Tray::moveTraySliderVel(int vel, int cur) {
    slider->setCurrentLimit(cur);
    slider->moveVelocity(vel);
}