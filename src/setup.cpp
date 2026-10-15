#include "globals.h"

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain
pros::MotorGroup left_blue_motors({8, 9}, pros::MotorGearset::blue);
pros::MotorGroup right_blue_motors({2, 3}, pros::MotorGearset::blue);
pros::Motor left_green_motor(10, pros::MotorGearset::green);
pros::Motor right_green_motor(1, pros::MotorGearset::green);

pros::MotorGroup leftMotors({8, 9, 10});
pros::MotorGroup rightMotors({2, 3, 1});

// Inertial
pros::Imu imu(11);

// Pneumatics
pros::adi::DigitalOut claw('A');
pros::adi::DigitalOut flipper('B');

// Motors
pros::Motor intake_motor(1, pros::MotorGearset::blue);
pros::MotorGroup cascade({2, 3}, pros::MotorGearset::blue);

// Distance Sensor Reset
pros::Distance front_sensor(4);
pros::Distance right_sensor(16);
pros::Distance left_sensor(20);
pros::Distance back_sensor(4);

// Odom
pros::Rotation horizontalEnc(1);
pros::Rotation verticalEnc(1);

lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, 1.25);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, -2.5);

// Drivetrain Settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.75, // 13 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// Straight PID
lemlib::ControllerSettings linearController(5.5, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            31, // derivative gain (kD)
                                            0, // anti windup
                                            0, // small error range, in inches
                                            0, // small error range timeout, in milliseconds
                                            0, // large error range, in inches
                                            0, // large error range timeout, in milliseconds
                                            0 // maximum acceleration (slew)
);

// Turning PID
lemlib::ControllerSettings angularController(4.5, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             35, // derivative gain (kD)
                                             0, // anti windup
                                             0, // small error range, in degrees
                                             0, // small error range timeout, in milliseconds
                                             0, // large error range, in degrees
                                             0, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// Odom Sensors
lemlib::OdomSensors sensors(&vertical, // &vertical, vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr, // &horizontal, horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// Expo Straight
lemlib::ExpoDriveCurve throttleCurve(15, // joystick deadband out of 127
                                     20, // minimum output where drivetrain will move out of 127
                                     1.025 // expo curve gain
);

// Expo Turning
lemlib::ExpoDriveCurve steerCurve(40, // joystick deadband out of 127
                                  20, // minimum output where drivetrain will move out of 127
                                  1.055 // expo curve gain
);

// Chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);