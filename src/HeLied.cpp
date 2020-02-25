#include "HeLied.hpp"

HeLied *HeLied::robot = NULL;
HeLied *HeLied::getRobot() {
	if (robot == NULL) {
		robot = new HeLied();
	}
	return robot;
}

HeLied::HeLied() {
	drive = std::make_shared<Drive>();
	lift = std::make_shared<Lift>();
	tray = std::make_shared<Tray>();
	tilter = std::make_shared<Tilter>(tray);
	intake = std::make_shared<Intake>(tray);
}

void HeLied::opControl(pros::Controller &joystick) {
	opControlCheck(joystick);
	drive->opControlDrive(joystick);
    bool armUp = lift->opControl(joystick, armMode);
	intake->opControl(joystick, armMode, armUp);
	if (armMode == TILTER){
	    tilter->opControl(joystick);
	}
	tray->opControl(joystick);
}


void HeLied::opControlCheck(pros::Controller& joystick) {
	int a = joystick.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
	if(a && a != lastToggleA) {
		armMode = (ArmMode)((armMode + 1) % 2);
		joystick.rumble("-");
	}
	lastToggleA = a;
}
