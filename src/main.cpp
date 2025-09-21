#include "robot.hpp"
#include "task.hpp"
#include "lemlib/api.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        pros::lcd::set_text(2, "I was pressed!");
    } else {
        pros::lcd::clear_line(2);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Hello PROS User!");

    chassis.calibrate(); // 校準感測器

    pros::lcd::register_btn1_cb(on_center_button);
    pros::screen::set_pen(pros::Color::red);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    imu.reset();
    while (imu.is_calibrating()) {
        pros::delay(20); // 等待校準完成
    }
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
ASSET(example_txt);
void autonomous() {
   // pros::Task displayTask(display_position_task);
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    //chassis.follow(example_txt, 10, 4000, true);
    // move 48" forwards
    chassis.moveToPoint(0, 24.5, 10000);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
    chassis.setPose(0, 0, 0);
    // 創建輸送帶控制任務
    pros::Task conveyorTask(conveyor_control);
    // 創建顯示位置資訊的任務
    //pros::Task displayTask(display_position_task);
    //pros::Task airTask(air_control);

    pros::Task chassisTask(chassis_control); // 底盤控制
    pros::Task backintake(intake_control); // 使用後方 intake 控制
    while (true) {
        // Arcade control scheme
        pros::c::optical_raw_s_t raw = Op.get_raw();

        pros::screen::print(TEXT_LARGE, 0, "X=%.2f", chassis.getPose().x);
        pros::screen::print(TEXT_LARGE, 2, "Y=%.2f", chassis.getPose().y);
        pros::screen::print(TEXT_LARGE, 4, "Theta=%.2f", chassis.getPose().theta);
        pros::screen::print(TEXT_LARGE, 6, "imu=%.2f", imu.get_rotation());

        lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
        pros::delay(20); // Run for 20 ms then update
    }
}