#include "Intake.hpp"
#include "HeLied.hpp"
#include "menu/Menu.hpp"

Intake::Intake(std::shared_ptr<Tray> _tray) {
    MotorGroup frontIntakeMotors({Motor(INTAKE_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
                                  Motor(INTAKE_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
    MotorGroup backIntakeMotors({ Motor(INTAKE_BACK_LEFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
                                  Motor(INTAKE_BACK_RIGHT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
    frontIntake = std::make_shared<MotorGroup>(frontIntakeMotors);
    backIntake = std::make_shared<MotorGroup>(backIntakeMotors);

    frontIntake->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    backIntake->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    tray = _tray;
}


// Runs specific set of intakes. 0 = only front, 1 = only back, anything else = false
void Intake::runIntake(int power, IntakeSet set) {
    switch(set) {
        case IS_FRONT:
            frontIntake->moveVelocity(power);
            break;
        case IS_BACK:
            backIntake->moveVelocity(power);
            break;
        default:
            frontIntake->moveVelocity(power);
            backIntake->moveVelocity(power);
            break;
    }
}

void Intake::setIntakeMode(IntakeMode intakeMode){
    switch(intakeMode) {
        case IM_IN_FOR_TOWER:
            runIntake(200, IS_FRONT);
            runIntake(200, IS_BACK);
            break;
        case IM_OUT_FOR_TOWER:
            runIntake(-150, IS_FRONT);
            runIntake(200, IS_BACK);
            break;
        case IM_IN_FOR_TRAY:
            runIntake(200);
            tray->moveTraySliderVoltage(12000, 300);
            break;
        case IM_OUT_FOR_TRAY:
            runIntake(-200);
            tray->moveTraySliderVel(-100);
            break;
        case IM_SQUISH_STACK:
            backIntake->moveVelocity(-20);
            frontIntake->moveVoltage(12000);
            tray->moveTraySliderVoltage(-12000, 700);
            break;
        default:
            runIntake(0);
            tray->moveTraySliderVoltage(-6200);
            break;
    }
}

void Intake::opControl(pros::Controller &joystick, ArmMode armMode) {
    int r1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    int r2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    int left = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

    switch(armMode) {
        case ARM:
            if (r1) {
                setIntakeMode(IM_IN_FOR_TOWER);
            }
            else if (r2) {
                setIntakeMode(IM_OUT_FOR_TOWER);
            } else {
                setIntakeMode(IM_OFF);
            }
            break;
        case TILTER:
            if (r1) {
                setIntakeMode(IM_IN_FOR_TRAY);
            }
            else if (r2) {
                setIntakeMode(IM_OUT_FOR_TRAY);
            } else {
                setIntakeMode(IM_OFF);
            }
            if(left) {
                setIntakeMode(IM_SQUISH_STACK);
            }
            break;
    }
}