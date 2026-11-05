#include "globals.h"
#include "liblvgl/llemu.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/rtos.h"

bool driver_start = true;

void start_calibration() {
	chassis.calibrate();
	controller.rumble(".");
	cascade.set_zero_position_all(0);
}

void initialize() {
	pros::lcd::initialize();
	start_calibration();

	pros::lcd::register_btn1_cb(auton_selector);
	pros::lcd::register_btn0_cb(start_calibration);

	print_selected_auton();
	cascade.set_brake_mode(pros::MotorBrake::brake);
	
	// print robot location to the brain screen
	pros::Task screenTask([&]() {
		while (true) {
			pros::lcd::print(0, "X: %.3f", chassis.getPose().x); // x
			pros::lcd::print(1, "Y: %.3f", chassis.getPose().y); // y
			pros::lcd::print(2, "Theta: %.3f", chassis.getPose().theta); // heading
			pros::lcd::print(3, "Temp: left: %.0f, right: %.0f", leftMotors.get_temperature(), rightMotors.get_temperature());
			
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
				auton_selector();
			}

			pros::delay(50);
		}
	});
}


void disabled() {}


void competition_initialize() {}


void autonomous() {
	driver_start = false;
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	cascade.set_zero_position_all(0);

	run_selected_auton();
	
	chassis.waitUntilDone();
	driver_start = true;
}

bool claw_closed = false;
bool flipper_up = true;

void opcontrol() {
	driver_start = true;
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

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
			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				intake.move_voltage(12000);
			} 
			else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
				intake.move_voltage(-12000);
			} 
			else {
				intake.move_voltage(0);
			}

			// Cascade
			if (!macro_running) {
				if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
					cascade.move_voltage(12000);
				}
				else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
					cascade.move_voltage(-12000);
				}
				else {
					cascade.move_voltage(0);
				}
			}

			// Loading Pos Macro
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
				loading_pos();
			}
			
			// Intake Pos Macro
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
				pin_grabbing_pos();
				//intake_pos();
			}

			// Claw Toggle
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
				claw_closed = !claw_closed;
				claw.set_value(claw_closed);
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