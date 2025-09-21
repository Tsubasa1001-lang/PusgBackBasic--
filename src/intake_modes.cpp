#include "intake_modes.hpp"
#include "robot.hpp"

// L1模式：吸入儲存槽
void intake_mode_storage() {
    FrontIntakeUpper.move(80);    // 前方上層正轉
    FrontIntakeLower.move(127);    // 前方下層正轉
    MiddleIntakeUpper.move(-127); // 中間上層反轉
    MiddleIntakeLower.move(0);    // 中間下層停止
    Conveyor.move(-127);             // 輸送帶停止
}

// R1模式：上方 output
void intake_mode_upper_output() {
    FrontIntakeUpper.move(127);   // 前方上層正轉
    FrontIntakeLower.move(127);   // 前方下層正轉
    MiddleIntakeUpper.move(127);  // 中間上層正轉
    MiddleIntakeLower.move(127);  // 中間下層正轉
    Conveyor.move(127);           // 輸送帶正轉
}

// R2模式：中間 output
void intake_mode_middle_output() {
    FrontIntakeUpper.move(-127);  // 前方上層反轉
    FrontIntakeLower.move(127);   // 前方下層正轉
    MiddleIntakeUpper.move(0);    // 中間上層停止
    MiddleIntakeLower.move(127);  // 中間下層正轉
    Conveyor.move(127);           // 輸送帶正轉
}

// L2模式：下方 output
void intake_mode_lower_output() {
    Conveyor.move(127);           // 輸送帶正轉
    MiddleIntakeLower.move(127);  // 中間下層正轉
    FrontIntakeLower.move(-127);  // 前方下層反轉
    FrontIntakeUpper.move(0);     // 前方上層停止
    MiddleIntakeUpper.move(0);    // 中間上層停止
}

// 停止所有 intake 馬達
void intake_stop_all() {
    FrontIntakeUpper.move(0);
    FrontIntakeLower.move(0);
    MiddleIntakeUpper.move(0);
    MiddleIntakeLower.move(0);
    Conveyor.move(0);
}