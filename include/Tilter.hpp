#pragma once
#include "main.h"
#include "Tray.hpp"

using namespace okapi;

class Tilter {
    private:
		const double FOURBAR_UP_VALUE = 950;
		const int FOURBAR_UP_MIN_VEL = 5;
		const double FOURBAR_GAIN = 0.3;

    public:
        Tilter(std::shared_ptr<Tray> tray);
        void opControl(pros::Controller& joystick);
        void moveFourbar(int power);
        void tiltScore();
        void tiltRetract();

        std::shared_ptr<Tray> tray;
        std::shared_ptr<MotorGroup> fourbar;
        std::shared_ptr<MotorGroup> slider;
};
