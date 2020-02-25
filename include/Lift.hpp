#pragma once
#include "main.h"
#include "ArmMode.hpp"

using namespace okapi;

class Lift {
    private:
        // TODO figure these out.
        int heightSmallTower = -1;
        int heightMediumTower = -1;
        int heightTallTower = -1;
    public:
        Lift();
        void opControl(pros::Controller& joystick, ArmMode armMode);
        void moveLift(int power);
        void moveSmallTower();
        void moveMediumTower();
        void moveTallTower();
        void moveToPos(int pos, int speed=100);

        std::shared_ptr<MotorGroup> armMotors;
};