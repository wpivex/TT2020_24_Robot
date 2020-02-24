#pragma once
#include "main.h"

using namespace okapi;

class Tray {
    private:

    public:
        Tray();
        void opControl(pros::Controller& joystick);
        void moveTraySliderVoltage(int voltage, int current=300);
        void moveTraySliderVel(int vel, int current=12000);

        std::shared_ptr<MotorGroup> slider;
};