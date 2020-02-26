#include "Drive.hpp"
#include "HeLied.hpp"
#include "menu/Menu.hpp"
#include <cmath>

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

    std::shared_ptr<okapi::OdomChassisController> c = ChassisControllerBuilder()
                .withMotors(leftMotors, rightMotors)
                .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 13.5_in},1024})
                .withGains(
                    {0.0021, 0, 0.00003}, // Distance controller gains
                    {0.002, 0, 0.00003}, // Turn controller gains
                    {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
                )
                .withSensors(leftEncoder, rightEncoder)
                .withClosedLoopControllerTimeUtil(80, 8, 120_ms)
                .withOdometry({{3.25_in, 15_in},1024}, StateMode::CARTESIAN, 0_mm, 0_deg)
                .buildOdometry();
    chassis = std::dynamic_pointer_cast<okapi::DefaultOdomChassisController>(c);
    chassisPID = std::dynamic_pointer_cast<okapi::ChassisControllerPID>(chassis->getChassisController());

    x_d = 0_in;
    y_d = 0_in;
    t_d = 0_deg;
}

void Drive::opControlDrive(pros::Controller& joystick) {
    double forward = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127;
    double turn = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127;
    double forward2 = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) / 127;
    // Double stick
    this->chassis->model().arcade(forward, turn);
    // this->chassis->model().tank(forward, forward2);
}

void Drive::turnToAngle(QAngle angle, int vel, DrivePrecision precision){
    // Update desired
    t_d = angle;

    this->chassis->getModel()->setMaxVelocity(vel);

    QAngle t_e;

    if (precision == NO_PRECISION){
        this->chassis->turnToAngle(t_d);
        do {
            OdomState cur_state = chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
            t_e = t_d - cur_state.theta;
            pros::delay(10);
        } while (abs(t_e.convert(degree)) > 2 and !chassisPID->isSettled());
    }
    else{
        this->chassis->turnToAngle(t_d);
    }
}

QLength Drive::getOrientedError(){
    // Get orientation error
    OdomState cur_state = chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
    QLength x_e = x_d - cur_state.x; // x error
    QLength y_e = y_d - cur_state.y; // y error
    QAngle t_e = t_d - cur_state.theta; // theta error
    float x_o = sin(cur_state.theta.convert(radian)); // x orientation
    float y_o = cos(cur_state.theta.convert(radian)); // y orientation

    QLength e_o = (x_o * x_e) + (y_o * y_e); // calc oriented error
    return e_o;
}

void Drive::driveDist(QLength len, int vel, DrivePrecision precision){
    // Update desired position
    float x_od = sin(t_d.convert(radian)); // x orientation
    float y_od = cos(t_d.convert(radian)); // y orientation
    x_d = x_d + (len * x_od); // Update desired x
    y_d = y_d + (len * y_od); // Update desired y

    Menu::getMenu()->addDebugPrint(3, "x_d:" + std::to_string(x_d.convert(inch))+ " y_d:" + std::to_string(y_d.convert(inch)));

    QLength e_o = getOrientedError();

    this->chassis->getModel()->setMaxVelocity(vel);

    if (precision == NO_PRECISION){
        this->chassis->moveDistanceAsync(e_o);
        while (abs(e_o.convert(inch)) > .5 and !chassisPID->isSettled()) {
            e_o = getOrientedError();
            pros::delay(10);
        }
    }
    else{
        this->chassis->moveDistance(e_o);
    }
}