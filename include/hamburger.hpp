#pragma once
#include "main.h"
#include "drive.hpp"
using namespace okapi;

#define DRIVE_LEFT_FRONT 1
#define DRIVE_LEFT_MID_FRONT 2
#define DRIVE_LEFT_MID_BACK 3
#define DRIVE_LEFT_BACK 4
#define DRIVE_RIGHT_FRONT 5
#define DRIVE_RIGHT_MID_FRONT 6
#define DRIVE_RIGHT_MID_BACK 7
#define DRIVE_RIGHT_BACK 8


class Hamburger {
	private:
		static Hamburger* robot;
		Hamburger();
	public:
		static Hamburger* getRobot();
		Drive drive;
};
