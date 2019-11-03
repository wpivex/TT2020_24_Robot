#pragma once
#include "main.h"
#include "drive.hpp"
using namespace okapi;

#define DRIVE_LEFT_FRONT 1 //Rev
#define DRIVE_LEFT_MID_FRONT 2
#define DRIVE_LEFT_MID_BACK 3
#define DRIVE_LEFT_BACK 4
#define DRIVE_RIGHT_FRONT 6 //REV
#define DRIVE_RIGHT_MID_FRONT 7
#define DRIVE_RIGHT_MID_BACK 8
#define DRIVE_RIGHT_BACK 9

#define INTAKE_LEFT 19
#define INTAKE_RIGHT 20

#define FOURBAR 


class Hamburger {
	private:
		static Hamburger* robot;
		std::shared_ptr<MotorGroup> intake;
		Hamburger();
	public:
		static Hamburger* getRobot();
		std::shared_ptr<Drive> drive;
		void opControlIntake(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
		void opControlIntake(int power);
};
