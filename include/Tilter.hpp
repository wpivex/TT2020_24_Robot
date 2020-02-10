#pragma once
#include "main.h"

using namespace okapi;

class Tilter {
    private:
		const double FOURBAR_UP_VALUE = 950;
		const int FOURBAR_UP_MIN_VEL = 25;
		const double FOURBAR_GAIN = 0.3;

    public:
        Tilter();
        void opControl(pros::Controller& joystick);
        void moveFourbar(int power);
        void tiltScore();
        void tiltRetract();

        std::shared_ptr<MotorGroup> fourbar;
};