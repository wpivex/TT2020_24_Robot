#pragma once
#include "main.h"
#include "drive.hpp"
#include "brainDriver.hpp"
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

#define INTAKE_LEFT_BOT 20
#define INTAKE_LEFT_TOP 16
#define INTAKE_RIGHT_BOT 19
#define INTAKE_RIGHT_TOP 15

#define TRAY_DEPLOY 12
#define TRAY_BRAKE 11
// #define DISABLE_PASSIVE_TRAY

#define FOURBAR_LEFT 18
#define FOURBAR_RIGHT 17

#define ARM_GRIP 13
#define ARM_LIFT 14

#define ENCODER_LEFT_DRIVE_TOP 'a'
#define ENCODER_LEFT_DRIVE_BOT 'b'
#define ENCODER_RIGHT_DRIVE_TOP 'c'
#define ENCODER_RIGHT_DRIVE_BOT 'd'


class Hamburger {
	private:
		static Hamburger* robot;
		std::shared_ptr<MotorGroup> intake;
		std::shared_ptr<MotorGroup> fourbar;
		std::shared_ptr<MotorGroup> armLift;
		std::shared_ptr<MotorGroup> armGrip;

		Hamburger();

		int lastUp = 0;
		int lastDown = 0;

		double trayBrakeSetpoint = 0;

		const double fourbarThreshold = 500;
		const double FOURBAR_UP_VALUE = 1020;
		const double FOURBAR_BRAKE_DISABLE_VALUE = 500;
		const double FOURBAR_BRAKE_ENABLE_VALUE = 800;
		const double FOURBAR_MARGIN_VALUE = 100;
		const int FOURBAR_UP_MIN_VEL = 30;
		const double FOURBAR_GAIN = 0.70;

		const double BRAKE_MAX_SPEED = 75;
		const double BRAKE_ENABLE_VALUE = 250;
		const double BRAKE_DISABLE_VALUE = 0;
		const double BRAKE_STALL_CURRENT = 2450;
	public:
		static Hamburger* getRobot();
		std::shared_ptr<Drive> drive;
		std::shared_ptr<BrainDriver> brainDriver;
		void opControlIntake(pros::Controller& joystick);
		void opControlFourbar(pros::Controller& joystick);
		void opControlTrayBrake(pros::Controller& joystick);
		void opControlTrayDeploy(pros::Controller& joystick);
		void opControlArm(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
		void moveFourbar(int power);
		void tiltFourbarScore();
		void tiltFourbarRetract();
		void brakeEnable();
		void brakeDisable();
		void deployTray();
		std::shared_ptr<MotorGroup> trayBrake;
		std::shared_ptr<MotorGroup> trayDeploy;
};
