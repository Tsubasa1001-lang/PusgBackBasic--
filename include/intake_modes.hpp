#ifndef INTAKE_MODES_HPP
#define INTAKE_MODES_HPP

// Intake 模式函式宣告

/**
 * @brief L1模式：吸入儲存槽
 * 前方intake低速正轉，中間上層反轉，其他停止
 */
void intake_mode_storage();

/**
 * @brief R1模式：上方 output
 * 所有intake和輸送帶都正轉
 */
void intake_mode_upper_output();

/**
 * @brief R2模式：中間 output  
 * 前方上層反轉，前方下層正轉，中間上層停止，中間下層正轉，輸送帶正轉
 */
void intake_mode_middle_output();

/**
 * @brief L2模式：下方 output
 * 輸送帶正轉，中間下層正轉，前方下層反轉，其他停止
 */
void intake_mode_lower_output();

/**
 * @brief 停止所有 intake 馬達
 */
void intake_stop_all();

#endif // INTAKE_MODES_HPP