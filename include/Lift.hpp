#pragma once
#include "main.h"
#include "ArmMode.hpp"

using namespace okapi;

enum ArmPosition{
    AP_DOWN = 0,
    AP_THRESH = 100,
    AP_LOW_HOVER = 140,
    AP_HIGH_HOVER = 220,
    AP_LOW_TOWER = 380,
    AP_MEDIUM_TOWER = 480,
    AP_HIGH_TOWER = 790
};


class Lift {
    private:
        // TODO figure these out.
        ArmPosition setPosition;
        int err_thresh = 20;
        int curr_thresh = 2000;
    public:
        Lift();
        bool opControl(pros::Controller& joystick, ArmMode armMode);
        void moveLift(int power);
        void moveToArmPos(ArmPosition armPosition, int speed=100);
        void moveToPos(int pos, int speed=100);
        void goToPos(ArmPosition armPosition, int speed=100);
        void homeArm(int power=12000);

        std::shared_ptr<MotorGroup> armMotors;
};