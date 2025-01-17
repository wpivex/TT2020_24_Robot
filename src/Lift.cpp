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

void Lift::opControl(pros::Controller& joystick) {
    int x = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    int b = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    if(x) {
        moveLift(100);
    } else if(b) {
        moveLift(-100);
    } else {
        moveLift(0);
    }
    Menu::getMenu()->addDebugPrint(6, "Arm Pos:" + std::to_string(armMotors->getPosition()));
}

void Lift::moveLift(int power) {
    armMotors->moveVelocity(power);
}

void Lift::moveToPos(int pos, int speed) {
    armMotors->moveAbsolute(pos, speed);
}
