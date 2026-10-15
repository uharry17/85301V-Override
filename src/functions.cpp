#include "globals.h"

// ----------Auton Selector----------

int selected_auton = 0;

void auton_selector() {
    if (selected_auton < 2) {
        selected_auton += 1;
    } 
    else {
        selected_auton = 0;
    }
}

void print_selected_auton() {
    switch (selected_auton) {
        default:
            pros::lcd::print(5, "Auton: testing_auton");
            break;
        case 1:
            pros::lcd::print(5, "Auton: testing2");
            break;
        case 2:
            pros::lcd::print(5, "Auton: testing3");
            break;
    }
}

void run_selected_auton() {
    switch (selected_auton) {
        default:
            testing_auton();
            break;
        case 1:
            testing2();
            break;
        case 2:
            testing3();
            break;
    }
}