#pragma once

#include "main.h"
#include "lemlib/api.hpp"    // LemLib

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
extern pros::Motor       intake_motor;
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

// ———————————————————————— Auton Selector Variables ————————————————————————
extern bool testing;
extern bool mid_right;
extern bool mid_left;
extern bool red_alliance;
extern bool blue_alliance;
extern bool rush_right;
extern bool rush_left;
extern bool blue_SAWP;
extern bool red_SAWP;
extern bool skill;

// ———————————————————————— Optical / Ejection / Park ————————————————————————
extern bool ejection;
extern bool optical_on;
extern bool park_start;

// ———————————————————————— Function Declarations ————————————————————————
void auton_selector();
void print_selected_auton();
void run_selected_auton();

double dist_sensor_pos(std::string sensor_direction);



// ———————————————————————— Autons ————————————————————————
void testing_auton();
void testing2();
void testing3();