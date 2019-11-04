#pragma once
#include "main.h"
#include "drive.hpp"
#include "brainDriver.hpp"
using namespace okapi;

#define DRIVE_LEFT_FRONT 4
#define DRIVE_LEFT_MID_FRONT 2
#define DRIVE_LEFT_MID_BACK 3
#define DRIVE_LEFT_BACK 1
#define DRIVE_RIGHT_FRONT 9
#define DRIVE_RIGHT_MID_FRONT 7
#define DRIVE_RIGHT_MID_BACK 8
#define DRIVE_RIGHT_BACK 6

#define INTAKE_LEFT 20
#define INTAKE_RIGHT 19

#define FOURBAR 18


class Hamburger {
	private:
		static Hamburger* robot;
		std::shared_ptr<MotorGroup> intake;
		std::shared_ptr<MotorGroup> fourbar;
		Hamburger();
	public:
		static Hamburger* getRobot();
		std::shared_ptr<Drive> drive;
		std::shared_ptr<BrainDriver> brainDriver;
		void opControlIntake(pros::Controller& joystick);
		void opControlFourbar(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
		void moveFourbar(int power);
};
