#include "task.hpp"
#include "robot.hpp" // 引入電子元件宣告
#include "intake_modes.hpp" // 引入 intake 模式函式

// 底盤控制 Task
void chassis_control(void* param) {
    while (true) {
        int dir = Player1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);   // 前後控制
        int turn = Player1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // 左右轉向

        LeftGroup.move(dir + turn);  // 左側馬達組
        RightGroup.move(dir - turn); // 右側馬達組

        pros::delay(20); // 延遲避免過度消耗資源
    }
}

// Intake 控制 Task
void intake_control(void* param) {
    while (true) {
        // L1按鈕：吸入儲存槽
        if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake_mode_storage();
        }
        // R1按鈕：上方output
        else if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intake_mode_upper_output();
        }
        // R2按鈕：中間output
        else if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intake_mode_middle_output();
        }
        // L2按鈕：下面output
        else if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake_mode_lower_output();
        }
        // 沒有按鈕時全部停止
        else {
            intake_stop_all();
        }
        pros::delay(20);
    }
}

void air_control(void* param) {
    while (true) {
        if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            Arm1stg.set_value(false);
        }
        else if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
            Arm1stg.set_value(true);
        }
        pros::delay(20);
    }
}

// Conveyor 控制 Task
void conveyor_control(void* param) {
    while (true) {
        if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            Conveyor.move(127); // 正向運轉
        } else if (Player1.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            Conveyor.move(-127); // 反向運轉
        } else {
            Conveyor.move(0); // 停止
        }
        pros::delay(20);
    }
}

void display_position_task() {
    while (true) {
        // 獲取機器人的當前位置資訊
        lemlib::Pose currentPose = chassis.getPose(); // 假設 chassis 有 getPose() 方法
        float x = currentPose.x;
        float y = currentPose.y;
        float theta = currentPose.theta;

        // 在 LCD 上顯示位置資訊
        pros::screen::print(TEXT_LARGE, 0, "X=%.2f", x);
        pros::screen::print(TEXT_LARGE, 2, "Y=%.2f", y);
        pros::screen::print(TEXT_LARGE, 4, "Theta=%.2f", theta);
        
        pros::delay(100); // 每 100 毫秒更新一次
    }
}