#include "globals.h"

// ----------Auton Selector----------

int selected_auton = 0;

void auton_selector() {
    if (selected_auton < 3) {
        selected_auton += 1;
    } 
    else {
        selected_auton = 0;
    }
    print_selected_auton();
    controller.rumble(".");
}

void print_selected_auton() {
    switch (selected_auton) {
        default:
            pros::lcd::print(5, "Auton: testing_auton");
            controller.print(1, 0, "Auton: Testing");
            break;
        case 1:
            pros::lcd::print(5, "Auton: close");
            controller.print(1, 0, "Auton: Close  ");
            break;
        case 2:
            pros::lcd::print(5, "Auton: far");
            controller.print(1, 0, "Auton: Far    ");
            break;
        case 3:
            pros::lcd::print(5, "Auton: skills");
            controller.print(1, 0, "Auton: skills ");
            break;
    }
}

void run_selected_auton() {
    switch (selected_auton) {
        default:
            testing_auton();
            break;
        case 1:
            close_auton();
            break;
        case 2:
            far_auton();
            break;
        case 3:
            skills_auton();
            break;
    }
}

//--------- Macros ----------

std::atomic<bool> macro_running{false};

int starting_height = 0;
int intake_height = 1500;
int pin_grabbing_height = 1000;

void loading_pos() {
    if (macro_running) return;
    macro_running = true;

    pros::Task([]() {
        claw_closed = false;
        claw.set_value(false);

        flipper_up = true;
        flipper.set_value(true);

        cascade.move_absolute(starting_height, 600);

        while (cascade.get_position() < starting_height - 50 ||
               cascade.get_position() > starting_height + 50) {
            pros::delay(10);
        }

        macro_running = false;

    });
}

void intake_pos() {
    if (macro_running) return;
    macro_running = true;

    pros::Task([]() {
        claw_closed = false;
        claw.set_value(false);

        flipper_up = false;
        flipper.set_value(false);

        cascade.move_absolute(intake_height, 600);

        while (cascade.get_position() < intake_height - 50 ||
               cascade.get_position() > intake_height + 50) {
            pros::delay(10);
        }

        macro_running = false;

    });
}

void pin_grabbing_pos() {
    if (macro_running) return;
    macro_running = true;

    pros::Task([](){
        claw_closed = false;
        claw.set_value(false);

        flipper_up = true;
        flipper.set_value(true);

        cascade.move_absolute(1000, 600);

        while (cascade.get_position() < pin_grabbing_height - 25 ||
               cascade.get_position() > pin_grabbing_height + 25) {
            pros::delay(10);
        }

        macro_running = false;

    });
}
