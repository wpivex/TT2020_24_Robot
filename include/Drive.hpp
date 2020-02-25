#pragma once
#include "main.h"


using namespace okapi;

class Drive {
	public:
		Drive();
		std::shared_ptr<okapi::DefaultOdomChassisController> chassis;
		std::shared_ptr<okapi::ChassisControllerPID> chassisPID;
		void opControlDrive(pros::Controller& joystick);
		void driveDist(QLength len, int vel=150);

	private:
		std::shared_ptr<MotorGroup> leftMotors;
		std::shared_ptr<MotorGroup> rightMotors;
};
