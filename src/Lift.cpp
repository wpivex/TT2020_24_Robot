#include "Lift.hpp"
#include "HeLied.hpp"
#include "menu/Menu.hpp"

Lift::Lift() {
    MotorGroup arm({Motor(ARM_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
		Motor(ARM_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	arm.setBrakeMode(AbstractMotor::brakeMode::brake);
    armMotors = std::make_shared<MotorGroup>(arm);
    armMotors->tarePosition();
}

// Returns true if lift is up
bool Lift::opControl(pros::Controller& joystick, ArmMode armMode) {
    int up = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    int down = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    if (armMode == ARM){
        up |= joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
        down |= joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    }

    bool isUp = armMotors->getPosition() > (int) AP_THRESH;

    if(up) {
        moveLift(100);
    } else if(down) {
        moveLift(-100);
    } else {
        moveLift(-500 * (!isUp));
    }
    Menu::getMenu()->addDebugPrint(6, "Arm Pos:" + std::to_string(armMotors->getPosition()));

    return isUp;
}

void Lift::moveLift(int power) {
//    if (power == 0 and armMotors->getPosition() < (int) AP_THRESH){
//        armMotors->moveVoltage(-500);
//    }
    armMotors->moveVelocity(power);
}

void Lift::moveToPos(int pos, int speed) {
    armMotors->moveAbsolute(pos, speed);
}

void Lift::moveToArmPos(ArmPosition armPosition, int speed) {
    setPosition = armPosition;
    moveToPos((int) armPosition, speed);
}

void Lift::goToPos(ArmPosition armPosition, int speed) {
    moveToArmPos(armPosition, speed);
    while (abs(armMotors->getPosition() - (int) armPosition) > err_thresh){
        pros::delay(10);
    }
}

void Lift::homeArm(int power) {
    armMotors->moveVoltage(-power);
    int count = 10;
    while (count > 0) {
        if (armMotors->getCurrentDraw() > 1500) {
            count --;
        }
        else {
            count = 10;
        }
        pros::delay(10);
    }
    armMotors->tarePosition();
    armMotors->moveVoltage(-100);
}