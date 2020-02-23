#pragma once
#include "main.h"

using namespace okapi;

class Tilter {
    private:
		const double FOURBAR_UP_VALUE = 950;
		const int FOURBAR_UP_MIN_VEL = 5;
		const double FOURBAR_GAIN = 0.3;
    const double FOURBAR_TRAY_SLIDE_THRESH = 50;

    public:
        Tilter();
        void opControl(pros::Controller& joystick);
        void moveFourbar(int power);
        void tiltScore();
        void tiltRetract();
        void moveTraySliderVoltage(int voltage);
        void moveTraySliderVel(int vel);


        std::shared_ptr<MotorGroup> fourbar;
        std::shared_ptr<MotorGroup> slider;
};