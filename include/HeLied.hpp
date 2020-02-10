#pragma once
#include "main.h"
#include "Drive.hpp"
#include "BrainDriver.hpp"
#include "Lift.hpp"
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

#define ENCODER_LEFT_DRIVE_TOP 'a'
#define ENCODER_LEFT_DRIVE_BOT 'b'
#define ENCODER_RIGHT_DRIVE_TOP 'c'
#define ENCODER_RIGHT_DRIVE_BOT 'd'

#define ARM_LEFT 14
#define ARM_RIGHT 13


class HeLied {
	private:
		static HeLied* robot;
		std::shared_ptr<MotorGroup> intake;
		std::shared_ptr<MotorGroup> fourbar;
		HeLied();

		int lastUp = 0;
		int lastDown = 0;

		const double fourbarThreshold = 500;
		const double FOURBAR_UP_VALUE = 950;
		const double FOURBAR_BRAKE_DISABLE_VALUE = 420;
		const double FOURBAR_BRAKE_ENABLE_VALUE = 600;
		const double FOURBAR_MARGIN_VALUE = 100;
		const int FOURBAR_UP_MIN_VEL = 30;
		const double FOURBAR_GAIN = 0.40;
		
	public:
		static HeLied* getRobot();
		std::shared_ptr<Drive> drive;
		std::shared_ptr<Lift> lift;
		std::shared_ptr<BrainDriver> brainDriver;
		void opControlIntake(pros::Controller& joystick);
		void opControlFourbar(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
		void moveFourbar(int power);
		void moveFourbar2(int power);
		void tiltFourbarScore();
		void tiltFourbarRetract();
};
