#pragma once
#include "main.h"
#include "Drive.hpp"
#include "BrainDriver.hpp"
#include "Lift.hpp"
#include "Tilter.hpp"
#include "Tray.hpp"
#include "Intake.hpp"
#include "ArmMode.hpp"
using namespace okapi;

#define BLUE_ALLIANCE

#define DRIVE_LEFT_FRONT 9
#define DRIVE_LEFT_MID_FRONT 8
#define DRIVE_LEFT_MID_BACK 7
#define DRIVE_LEFT_BACK 6
#define DRIVE_RIGHT_FRONT 4
#define DRIVE_RIGHT_MID_FRONT 3
#define DRIVE_RIGHT_MID_BACK 2
#define DRIVE_RIGHT_BACK 1

#define INTAKE_LEFT 20
#define INTAKE_RIGHT 11
#define INTAKE_BACK_LEFT 10
#define INTAKE_BACK_RIGHT 16

#define FOURBAR_LEFT 18
#define FOURBAR_RIGHT 17
#define SLIDER 15

#define ENCODER_LEFT_DRIVE_TOP 'g'
#define ENCODER_LEFT_DRIVE_BOT 'h'
#define ENCODER_RIGHT_DRIVE_TOP 'e'
#define ENCODER_RIGHT_DRIVE_BOT 'f'

#define ARM_LEFT 14
#define ARM_RIGHT 13

// BROKEN PORTS? 19, 12

class HeLied {
	private:
		static HeLied* robot;
		HeLied();
		// 0 = arm mode, 1 = tilter mode
		int lastToggleA = 0;

		void opControlCheck(pros::Controller& joystick);

	public:
		static HeLied* getRobot();
		ArmMode armMode = TILTER;
		std::shared_ptr<Drive> drive;
		std::shared_ptr<Lift> lift;
		std::shared_ptr<Tilter> tilter;
		std::shared_ptr<Intake> intake;
		std::shared_ptr<Tray> tray;

		void opControl(pros::Controller& joystick);
};
