#include "hamburger.hpp"

Hamburger* Hamburger::robot = NULL;
Hamburger* Hamburger::getRobot() {
	if(robot == NULL) {
		robot = new Hamburger();
	}
	return robot;
}

Hamburger::Hamburger():
	drive({ Motor(DRIVE_LEFT_FRONT, false,AbstractMotor::gearset::green), 
			Motor(DRIVE_LEFT_MID_FRONT, false,AbstractMotor::gearset::green),
			Motor(DRIVE_LEFT_MID_BACK, false,AbstractMotor::gearset::green),
			Motor(DRIVE_LEFT_BACK, true,AbstractMotor::gearset::green)}, 
			{ Motor(DRIVE_RIGHT_FRONT, false,AbstractMotor::gearset::green), 
			Motor(DRIVE_RIGHT_MID_FRONT, false,AbstractMotor::gearset::green),
			Motor(DRIVE_RIGHT_MID_BACK, false,AbstractMotor::gearset::green),
			Motor(DRIVE_RIGHT_BACK, true,AbstractMotor::gearset::green)})
{
	// ChassisControllerFactory::createPtr()
}
