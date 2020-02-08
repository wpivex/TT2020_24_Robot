#include "drive.hpp"

Drive::Drive(okapi::MotorGroup leftMotors, okapi::MotorGroup rightMotors) {
    leftMotors.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotors.setBrakeMode(AbstractMotor::brakeMode::coast);
    chassis = ChassisControllerBuilder()
                .withMotors(leftMotors, rightMotors)
                // .withGearset(AbstractMotor::gearset::green)
                .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 13.5_in},imev5GreenTPR})
                .withGains(
                    {0.001, 0, 0.0001}, // Distance controller gains
                    {0.001, 0, 0.0001}, // Turn controller gains
                    {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
                )
                .withOdometry({{3.25_in, 13.5_in},imev5GreenTPR}, StateMode::CARTESIAN, 0_mm, 0_deg)
                .buildOdometry();
}

void Drive::run(pros::Controller& joystick) {
    double forward = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127;
    double turn = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127;
    this->chassis->model().arcade(forward, turn);
}
