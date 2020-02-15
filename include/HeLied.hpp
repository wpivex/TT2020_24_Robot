#pragma once
#include "main.h"
#include "Drive.hpp"
#include "BrainDriver.hpp"
#include "Lift.hpp"
#include "Tilter.hpp"
using namespace okapi;

#define BLUE_ALLIANCE

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
#define INTAKE_BACK_LEFT 16
#define INTAKE_BACK_RIGHT 15

#define FOURBAR_LEFT 18
#define FOURBAR_RIGHT 17

#define ENCODER_LEFT_DRIVE_TOP 'g'
#define ENCODER_LEFT_DRIVE_BOT 'h'
#define ENCODER_RIGHT_DRIVE_TOP 'e'
#define ENCODER_RIGHT_DRIVE_BOT 'f'

#define ARM_LEFT 14
#define ARM_RIGHT 13


class HeLied {
	private:
		static HeLied* robot;
		HeLied();

	public:
		static HeLied* getRobot();
		std::shared_ptr<Drive> drive;
		std::shared_ptr<Lift> lift;
		std::shared_ptr<Tilter> tilter;
		std::shared_ptr<MotorGroup> frontIntake;
		std::shared_ptr<MotorGroup> backIntake;

		void opControlIntake(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
};
