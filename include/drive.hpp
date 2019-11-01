#pragma once
#include "main.h"

using namespace okapi;

class Drive {
	public:
		Drive(okapi::MotorGroup leftMotors, okapi::MotorGroup rightMotors);
		std::shared_ptr<okapi::OdomChassisController> chassis;
		void run(pros::Controller& joystick);
};
