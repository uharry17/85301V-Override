#pragma once

#include "main.h"
#include "lemlib/api.hpp"    // LemLib

#include <atomic>
#include <string>

// ———————————————————————— Controller ————————————————————————
extern pros::Controller controller;

// ———————————————————————— Drivetrain Motors ————————————————————————
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// ———————————————————————— Pneumatics ————————————————————————
extern pros::adi::DigitalOut claw;
extern pros::adi::DigitalOut flipper;

// ———————————————————————— Intake / Cascade ————————————————————————
extern pros::Motor       intake;
extern pros::MotorGroup  cascade;

// ———————————————————————— Sensors ————————————————————————
extern pros::Imu         imu;
//extern pros::Optical     optical_sensor;
extern pros::Rotation    horizontalEnc;
extern pros::Rotation    verticalEnc;
extern pros::Distance    front_sensor;
extern pros::Distance   right_sensor;
extern pros::Distance    left_sensor;
extern pros::Distance    back_sensor;
extern pros::Rotation    cascadeEnc;

// ———————————————————————— LemLib Odometry & Tracking Wheels ————————————————————————
extern lemlib::TrackingWheel horizontal;
extern lemlib::TrackingWheel vertical;

extern lemlib::Drivetrain            drivetrain;
extern lemlib::ControllerSettings    linearController;
extern lemlib::ControllerSettings    angularController;
extern lemlib::OdomSensors           sensors;
extern lemlib::ExpoDriveCurve        throttleCurve;
extern lemlib::ExpoDriveCurve        steerCurve;

extern lemlib::Chassis               chassis;

// ———————————————————————— Function Declarations ————————————————————————
void auton_selector();
void print_selected_auton();
void run_selected_auton();

/// ———————————————————————— Macros ————————————————————————
void loading_pos();
void intake_pos();
void pin_grabbing_pos();

// ———————————————————————— Autons ————————————————————————
void testing_auton();
void close_auton();
void far_auton();
void skills_auton();

// ———————————————————————— Variables ————————————————————————
extern bool claw_closed;
extern bool flipper_up;
extern std::atomic<bool> macro_running;