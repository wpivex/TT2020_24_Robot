#include "drive.hpp"

Drive::Drive(okapi::MotorGroup leftMotors, okapi::MotorGroup rightMotors) {
    leftMotors.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotors.setBrakeMode(AbstractMotor::brakeMode::coast);
    // chassis = ChassisControllerFactory::createPtr(leftMotors, 
    // rightMotors, 
    // IterativePosPIDController::Gains{0.001, 0, 0.0001},
    // IterativePosPIDController::Gains{0.001, 0, 0.0001},
    // IterativePosPIDController::Gains{0.001, 0, 0.0001},
    // AbstractMotor::gearset::green, 
    // {3.25_in, 13.5_in});
}

void Drive::run(pros::Controller& joystick) {
    double forward = joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127;
    double turn = joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127;
    // this->chassis->arcade(forward, turn);
}
