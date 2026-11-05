#include "globals.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

void toggle_start() {
    leftMotors.move_voltage(12000);
    rightMotors.move_voltage(12000);
    pros::delay(600);
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
    pros::delay(10);
}

void testing_auton() {
    
    close_auton();

}

void close_auton() {
    
    // Score First Preload
    flipper.set_value(true);
    cascade.move_absolute(900, 600);
    toggle_start();
    pros::delay(20);
    chassis.setPose(0, 0, 180);
    chassis.moveToPoint(0, 17.3, 600, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 450);
    chassis.waitUntilDone();
    pros::delay(20);
    chassis.setPose(0, 0, chassis.getPose().theta);
    chassis.moveToPoint(21, chassis.getPose().y + 0.9, 650, {.forwards = false, .minSpeed = 20});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(250);
    flipper.set_value(false);
    pros::delay(50);
    claw.set_value(false);
    pros::delay(100);
    
    

    // Grab First Stack
    chassis.setPose(0 , 0, chassis.getPose().theta);
    chassis.moveToPoint(-10, 0, 400, {.maxSpeed = 60});
    chassis.turnToPoint(11, 24.5, 450, {.forwards = false});
    flipper.set_value(true);
    chassis.moveToPoint(11.3, 24.2, 420, {.forwards = false, .minSpeed = 65});
    chassis.moveToPoint(11.3, 24.2,  370, {.forwards = false, .maxSpeed = 30, .minSpeed = 20});
    chassis.waitUntilDone();
    claw.set_value(true);
    pros::delay(80);
    cascade.move_absolute(2400, 600);
    pros::delay(100);
    chassis.moveToPoint(11.3, 24.2, 360, {.forwards = false, .minSpeed = 40});

    
    // Score First Stack
    chassis.turnToHeading(0, 550);
    chassis.waitUntilDone();
    chassis.setPose(0, 0 , chassis.getPose().theta);
    chassis.moveToPoint(1.2, -25, 637, {.forwards = false});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(200);
    claw.set_value(false);
    pros::delay(100);

    // Grab Second Stack
    chassis.setPose(0 , 0, chassis.getPose().theta - 90);
    chassis.moveToPoint(-10, 0, 400, {.maxSpeed = 60});
    chassis.turnToPoint(10.3, 24.5, 450, {.forwards = false});
    flipper.set_value(true);
    chassis.moveToPoint(10.6, 24.2, 420, {.forwards = false, .minSpeed = 65});
    chassis.moveToPoint(10.6, 24.2,  375, {.forwards = false, .maxSpeed = 30, .minSpeed = 20});
    chassis.waitUntilDone();
    claw.set_value(true);
    pros::delay(80);
    cascade.move_absolute(3700, 600);
    pros::delay(100);
    chassis.moveToPoint(10.6, 24.2, 360, {.forwards = false, .minSpeed = 40});

    
    // Score Second Stack
    chassis.turnToHeading(-2, 550);
    chassis.waitUntilDone();
    chassis.setPose(0, 0 , chassis.getPose().theta);
    chassis.moveToPoint(1, -25, 637, {.forwards = false});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(200);
    claw.set_value(false);
    pros::delay(150);

    // Grab Third Stack
    chassis.setPose(0 , 0, chassis.getPose().theta + 90);
    chassis.moveToPoint(12, 0, 400);
    chassis.turnToHeading(32, 300, {.maxSpeed = 100});
    flipper.set_value(true);
    chassis.moveToPoint(-8.5, -13, 450, {.forwards = false, .minSpeed = 65});
    chassis.turnToHeading(23, 350);
    chassis.waitUntilDone();

    leftMotors.move_voltage(-4000);
    rightMotors.move_voltage(-4000);
    pros::delay(350);
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
    pros::delay(10);
    claw.set_value(true);

    cascade.move_absolute(6100, 600);
    pros::delay(50);

    // Score Third Stack
    chassis.turnToHeading(50, 300);
    chassis.moveToPoint(6, 1, 600);
    chassis.turnToHeading(93, 300);
    chassis.waitUntilDone();
    pros::delay(550);
    chassis.moveToPoint(-1, chassis.getPose().y, 500, {.forwards = false, .minSpeed = 40});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(300);
    flipper_up = true;
    claw_closed = false;
    claw.set_value(false);
    pros::delay(10);
    cascade.move_absolute(0, 600);

    /*
    // Grab Second Stack
    chassis.setPose(0 , 0, chassis.getPose().theta - 90);
    chassis.moveToPoint(-10, 0, 400);
    chassis.turnToHeading(213.5, 500);
    chassis.moveToPose(5.05, 16.2, 215, 600, {.forwards = false, .minSpeed = 60});
    chassis.moveToPose(5.05, 16.2, 215, 450, {.forwards = false, .maxSpeed = 30, .minSpeed = 15});
    pros::delay(330);
    claw.set_value(true);
    cascade.move_absolute(3700, 600);
    pros::delay(125);

    // Score Second Stack
    chassis.moveToPoint(7.5, 20, 380, {.forwards = false, .minSpeed = 40});
    chassis.turnToHeading(-3, 550);
    chassis.moveToPoint(chassis.getPose().x + 1, -2, 800, {.forwards = false});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(150);
    claw.set_value(false);
    pros::delay(50);

    // Grab Third Stack
    chassis.setPose(0 , 0, chassis.getPose().theta + 90);
    chassis.moveToPoint(12, 0, 400);
    chassis.turnToHeading(32, 300, {.maxSpeed = 100});
    flipper.set_value(true);
    chassis.moveToPoint(-8.5, -13, 450, {.forwards = false, .minSpeed = 65});
    chassis.turnToHeading(23, 350);
    chassis.waitUntilDone();

    leftMotors.move_voltage(-4000);
    rightMotors.move_voltage(-4000);
    pros::delay(350);
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
    pros::delay(10);
    claw.set_value(true);

    cascade.move_absolute(6000, 600);
    pros::delay(50);

    // Score Third Stack
    chassis.turnToHeading(50, 300);
    chassis.moveToPoint(6, 1, 500);
    chassis.turnToHeading(93, 300);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPoint(-1, chassis.getPose().y, 500, {.forwards = false, .minSpeed = 40});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(300);
    claw.set_value(false);
    
    flipper_up = true;
    claw_closed = false;
    */
    
    



} 

void far_auton() {

    // Score First Preload
    flipper.set_value(true);
    cascade.move_absolute(900, 600);
    toggle_start();
    chassis.setPose(0, 0, 180);
    chassis.moveToPoint(0, 18.7, 550, {.forwards = false});
    chassis.turnToHeading(90, 550);
    chassis.moveToPoint(-21, chassis.getPose().y + 2.6, 650, {.forwards = false});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(200);
    flipper.set_value(false);
    pros::delay(50);
    claw.set_value(false);
    pros::delay(50);

    // Grab First Stack
    chassis.setPose(0 , 0, chassis.getPose().theta);
    chassis.moveToPoint(10, 0, 400);
    chassis.turnToHeading(43, 600, {.maxSpeed = 100});
    flipper.set_value(true);
    chassis.moveToPose(-8.5, -13.6, 45.41, 900, {.forwards = false, .minSpeed = 55});
    chassis.turnToHeading(20, 350);
    chassis.moveToPoint(-10, -15, 300, {.forwards = false, .minSpeed = 50});
    chassis.waitUntilDone();
    claw.set_value(true);
    pros::delay(100);
    cascade.move_absolute(2700, 600);
    pros::delay(100);

    // Score First Stack
    chassis.turnToHeading(46, 300);
    chassis.moveToPoint(3.7, 1, 800);
    chassis.turnToHeading(93, 400);
    chassis.moveToPoint(-1, chassis.getPose().y, 500, {.forwards = false, .minSpeed = 40});
    chassis.waitUntilDone();
    cascade.move_absolute(0, 600);
    pros::delay(300);
    claw.set_value(false);
    
    flipper_up = true;
    claw_closed = false;

}

void skills_auton() {

    close_auton();

    // Park
    chassis.moveToPoint(12, 0, 400);
    chassis.turnToHeading(-50, 80);
    chassis.waitUntilDone();
    chassis.setPose(0 , 0, chassis.getPose().theta);
    chassis.moveToPoint(-40, 40, 1500);
    



}