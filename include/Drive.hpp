#pragma once
#include "main.h"


using namespace okapi;

enum DrivePrecision{
    HIGH_PRECISION,
    MEDIUM_PRECISION,
    WHAT_PRECISION
};

class Drive {
	public:
		Drive();
		std::shared_ptr<okapi::DefaultOdomChassisController> chassis;
		std::shared_ptr<okapi::ChassisControllerPID> chassisPID;
		void opControlDrive(pros::Controller& joystick);
    void driveDist(QLength len, int vel=130, DrivePrecision precision = MEDIUM_PRECISION);
    void turnToAngle(QAngle angle, int vel=150, DrivePrecision precision = MEDIUM_PRECISION);

        QLength x_d;
        QLength y_d;
        QAngle t_d;

	private:
		std::shared_ptr<MotorGroup> leftMotors;
		std::shared_ptr<MotorGroup> rightMotors;
};
