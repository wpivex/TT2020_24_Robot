#pragma once
#include "main.h"

using namespace okapi;

class Lift {
    private:
        // TODO figure these out.
        int heightSmallTower = -1;
        int heightMediumTower = -1;
        int heightTallTower = -1;
    public:
        Lift();
        void opControl(pros::Controller& joystick);
        void moveLift(int power);
        void moveSmallTower();
        void moveMediumTower();
        void moveTallTower();

        std::shared_ptr<MotorGroup> armMotors;
};