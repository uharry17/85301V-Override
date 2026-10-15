#include "globals.h"

bool driver_start = true;

void start_calibration() {
	chassis.calibrate();
	controller.rumble(".");
}

void initialize() {
	pros::lcd::initialize();
	start_calibration();

	pros::lcd::register_btn1_cb(start_calibration);
	pros::lcd::register_btn2_cb(auton_selector);

	// print robot location to the brain screen
	pros::Task screenTask([]() {
		while (true) {
			pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
			pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
			pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading   
			pros::lcd::print(3,  "Temp:  left: %f, right: %f", leftMotors.get_temperature() ,rightMotors.get_temperature());
			
			print_selected_auton();
			
			pros::delay(20);
		}
	});
}


void disabled() {}


void competition_initialize() {}


void autonomous() {
	driver_start = false;
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	chassis.setPose(0, 0, 0);
	run_selected_auton();
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	driver_start = true;
}


void opcontrol() {
	driver_start = true;
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	bool claw_open = true;
	bool flipper_up = false;

	while (true) {
		if (driver_start == true) {
			// get joystick positions
			int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
			// move the chassis with curvature drive
			chassis.arcade(leftY, rightX);
			// delay to save resources
			pros::delay(5);

			// Intake
			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
				intake_motor.move_voltage(12000);
			} 
			else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
				intake_motor.move_voltage(-12000);
			} 
			else {
				intake_motor.move_voltage(0);
			}

			// Cascade
			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
				cascade.move_voltage(12000);
				
				if (cascade.get_position() > 67) {
					
					flipper_up = true;
					flipper.set_value(true);
					
					claw_open = true;
					claw.set_value(true);
				}
			}
			else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
				cascade.move_voltage(-12000);
			}
			else {
				cascade.move_voltage(0);
			}

			// Loading Pos Macro
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
				
				claw_open = false;
				claw.set_value(false);
				
				flipper_up = true;
				flipper.set_value(true);
				
				if (cascade.get_position() > 67) {
					cascade.move_absolute(5, 600);
				}
			}
			
			// Intake Pos Macro
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
				
				claw_open = false;
				claw.set_value(false);
				
				flipper_up = false;
				flipper.set_value(false);
				
				if (cascade.get_position() > 67) {
					cascade.move_absolute(5, 600);
				}
			}

			// Claw Toggle
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
				claw_open = !claw_open;
				claw.set_value(claw_open);
			}

			// Flipper Toggle
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
				flipper_up = !flipper_up;
				flipper.set_value(flipper_up);
			}

			// Start Auton
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
				autonomous();
			}

		}
	}
}