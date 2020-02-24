#pragma once
#include "main.h"
#include "Tray.hpp"
#include "ArmMode.hpp"

using namespace okapi;

enum IntakeSet {
    IS_FRONT,
    IS_BACK,
    IS_BOTH
};

enum IntakeMode {
    IM_OFF,
    IM_IN_FOR_TOWER,
    IM_IN_FOR_TRAY,
    IM_OUT_FOR_TOWER,
    IM_OUT_FOR_TRAY,
    IM_SQUISH_STACK
};

class Intake {
    private:

    public:
        Intake(std::shared_ptr<Tray> tray);
        void opControl(pros::Controller& joystick, ArmMode armMode);
        void runIntake(int power, IntakeSet set=IS_BOTH);
        void setIntakeMode(IntakeMode intakeMode);

        std::shared_ptr<Tray> tray;
        std::shared_ptr<MotorGroup> frontIntake;
        std::shared_ptr<MotorGroup> backIntake;
};