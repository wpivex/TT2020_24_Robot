#include "drive.hpp"
#include "hamburger.hpp"

Drive::Drive() {
  MotorGroup left({Motor(DRIVE_LEFT_FRONT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_MID_FRONT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_MID_BACK, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_BACK, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
  MotorGroup right({Motor(DRIVE_RIGHT_FRONT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_MID_FRONT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_MID_BACK, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_BACK, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
  leftMotors = std::make_shared<MotorGroup>(left);
  rightMotors = std::make_shared<MotorGroup>(right);
  leftMotors->setBrakeMode(AbstractMotor::brakeMode::coast);
  rightMotors->setBrakeMode(AbstractMotor::brakeMode::coast);

  ADIEncoder leftEncoder = ADIEncoder(ENCODER_LEFT_DRIVE_TOP, ENCODER_LEFT_DRIVE_BOT, false);
  ADIEncoder rightEncoder = ADIEncoder(ENCODER_RIGHT_DRIVE_TOP, ENCODER_RIGHT_DRIVE_BOT, true);

  chassis = ChassisControllerBuilder()
                .withMotors(leftMotors, rightMotors)
                .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 13.5_in},1024})
                .withGains(
                    {0.001, 0, 0.0001}, // Distance controller gains
                    {0.001, 0, 0.0001}, // Turn controller gains
                    {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
                )
                .withSensors(leftEncoder, rightEncoder)
                .withClosedLoopControllerTimeUtil(50, 5, 250_ms)
                .withOdometry({{3.25_in, 13.5_in},1024}, StateMode::CARTESIAN, 0_mm, 0_deg)
                .buildOdometry();
}

void Drive::opControlDrive(pros::Controller& joystick) {
    double forward = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127;
    double turn = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127;
    double forward2 = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) / 127;
    // Double stick
    this->chassis->model().arcade(forward, turn);
}
