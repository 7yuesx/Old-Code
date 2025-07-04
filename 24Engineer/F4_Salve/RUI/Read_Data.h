/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 * 
 * 
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *            佛祖保佑     永不宕机     永无BUG
 * 
 *        佛曰:  
 *                写字楼里写字间，写字间里程序员；  
 *                程序人员写程序，又拿程序换酒钱。  
 *                酒醒只在网上坐，酒醉还来网下眠；  
 *                酒醉酒醒日复日，网上网下年复年。  
 *                但愿老死电脑间，不愿鞠躬老板前；  
 *                奔驰宝马贵者趣，公交自行程序员。  
 *                别人笑我忒疯癫，我笑自己命太贱；  
 *                不见满街漂亮妹，哪个归得程序员？
 */

/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-01-23 11:39:25
 * @LastEditors: Andy
 * @LastEditTime: 2024-01-24 13:29:17
 */

#ifndef __READ_DATA_H
#define __READ_DATA_H

#include "usart.h" 
#include "Write_Data.h"

enum Read_Cmd_ID_Typdef
{
    game_state      = 0x0001 ,  //比赛状态数据，固定 1Hz 频率发送
    Match_results   = 0x0002 ,  //比赛结果数据，比赛结束触发发送
    Robot_HP        = 0x0003 ,  //机器人血量数据，固定 3Hz 频率
    Venue_Events    = 0x0101 ,  //场地事件数据，固定 1Hz 频率
    Supply_action   = 0x0102 ,  //补给站动作标识数据，补给站弹丸释放时触发发送
    Referee_warning = 0x0104 ,  //裁判警告数据，己方判罚/判负时触发发送，其余时间以 1Hz 频率发送
    Dart_fire       = 0x0105 ,  //飞镖发射相关数据，固定 1Hz 频率发送
    Robot_performan = 0x0201 ,  //机器人性能体系数据，固定10Hz 频率发送  
    time_power      = 0x0202 ,  //实时功率热量数据，固定 50Hz频率发送
    Robot_location  = 0x0203 ,  //机器人位置数据，哨兵机器人的发送频率为 10Hz，其余机器人的发送频率为 1Hz
    Robot_buff      = 0x0204 ,  //机器人增益数据，固定 3Hz 频率发送
    Air_support     = 0x0205 ,  //空中支援时间数据，固定 1Hz 频率发送
    Damage_status   = 0x0206 ,  //伤害状态数据，伤害发生后发送
    time_shooting   = 0x0207 ,  //实时射击数据，弹丸发射后发送
    Allowable_ammo  = 0x0208 ,  //允许发弹量，固定 10Hz 频率发送
    RFID            = 0x0209 ,  //机器人 RFID 状态，固定 3Hz 频率发送
    Dart_directives = 0x020A ,  //飞镖选手端指令数据，飞镖闸门上线后固定 3Hz 频率发送
    Ground_location = 0x020B ,  //地面机器人位置数据，固定 1Hz频率发送
    Radar_Marking   = 0x020C ,  //雷达标记进度数据，固定 1Hz 频率发送
    Route_Informat  = 0x020D ,  //哨兵自主决策相关信息同步，固定 1Hz 频率发送
    Radar_Informat  = 0x020E ,  //雷达自主决策信息同步，固定1Hz 频率发送
    Minimap         = 0x0303 ,  //选手端小地图交互数据，选手端触发发送
    remote          = 0x0304 ,  //键鼠遥控数据，固定 30Hz 频率发送
};

/*0x0001*/
typedef struct __packed
{
    uint8_t game_type : 4;
    uint8_t game_progress : 4;
    uint16_t stage_remain_time;
    uint64_t SyncTimeStamp;

}game_status_t;

/*0x0002*/
typedef struct __packed
{
    uint8_t winner;

}game_result_t;

/*0x0003*/
typedef struct __packed
{
    uint16_t red_1_robot_HP;
    uint16_t red_2_robot_HP;
    uint16_t red_3_robot_HP;
    uint16_t red_4_robot_HP;
    uint16_t red_5_robot_HP;
    uint16_t red_7_robot_HP;
    uint16_t red_outpost_HP;
    uint16_t red_base_HP;
    uint16_t blue_1_robot_HP;
    uint16_t blue_2_robot_HP;
    uint16_t blue_3_robot_HP;
    uint16_t blue_4_robot_HP;
    uint16_t blue_5_robot_HP;
    uint16_t blue_7_robot_HP;
    uint16_t blue_outpost_HP;
    uint16_t blue_base_HP;

}game_robot_HP_t;

/*0x0101*/
typedef struct __packed
{
    uint32_t refueling_Blood : 1;
    uint32_t supply_Blood : 1;
    uint32_t Reserved_bits_1 : 1;
    uint32_t buff_activated : 1;
    uint32_t buff_small : 1;
    uint32_t buff_big : 1;
    uint32_t Circular_Heights : 2;
    uint32_t Trapezoidal_heights_3 : 2;
    uint32_t Trapezoidal_heights_4 : 2;
    uint32_t Virtual_Shield : 7;
    uint32_t Dart_hit_time : 9;
    uint32_t Dart_hit_aim : 2;
    uint32_t Reserved_bits_2 : 2;

}event_data_t;

/*0x0102*/
typedef struct __packed
{
    uint8_t reserved;
    uint8_t supply_robot_id;
    uint8_t supply_projectile_step;
    uint8_t supply_projectile_num;

} ext_supply_projectile_action_t;

/*0x0104*/
typedef struct __packed
{
    uint8_t level;
    uint8_t offending_robot_id;
    uint8_t count;

}referee_warning_t;

/*0x0105*/
typedef struct __packed
{
    uint8_t dart_remaining_time;
    uint8_t Dart_aimed : 2;
    uint8_t Dart_success : 3;
    uint8_t Dart_aiming : 2;
    uint8_t Reserved_bits : 1;

}dart_info_t;

/*0x0201*/
typedef struct __packed
{
    uint8_t robot_id;
    uint8_t robot_level;
    uint16_t current_HP; 
    uint16_t maximum_HP;
    uint16_t shooter_barrel_cooling_value;
    uint16_t shooter_barrel_heat_limit;
    uint16_t chassis_power_limit; 
    uint8_t power_management_gimbal_output : 1;
    uint8_t power_management_chassis_output : 1; 
    uint8_t power_management_shooter_output : 1;

}robot_status_t;

/*0x0202*/
typedef struct __packed
{
    uint16_t chassis_voltage;
    uint16_t chassis_current;
    float chassis_power;
    uint16_t buffer_energy;
    uint16_t shooter_17mm_1_barrel_heat;
    uint16_t shooter_17mm_2_barrel_heat;
    uint16_t shooter_42mm_barrel_heat;

}power_heat_data_t;

/*0x0203*/
typedef struct __packed
{
    float x;
    float y;
    float angle;

}robot_pos_t;

/*0x0204*/
typedef struct __packed
{
    uint8_t recovery_buff;
    uint8_t cooling_buff;
    uint8_t defence_buff;
    uint16_t attack_buff;

}buff_t;

/*0x0205*/
typedef struct __packed
{
    uint8_t airforce_status;
    uint8_t time_remain;

}air_support_data_t;

/*0x0206*/
typedef struct __packed
{
    uint8_t armor_id : 4;
    uint8_t HP_deduction_reason : 4;

}hurt_data_t;

/*0x0207*/
typedef struct __packed
{
    uint8_t bullet_type;
    uint8_t shooter_number;
    uint8_t launching_frequency;
    float initial_speed;

}shoot_data_t;

/*0x0208*/
typedef struct __packed
{
    uint16_t projectile_allowance_17mm;
    uint16_t projectile_allowance_42mm;
    uint16_t remaining_gold_coin;

}projectile_allowance_t;

/*0x0209*/
typedef struct __packed
{
    uint32_t bit0 : 1;
    uint32_t bit1 : 1;
    uint32_t bit2 : 1;
    uint32_t bit3 : 1;
    uint32_t bit4 : 1;
    uint32_t bit5 : 1;
    uint32_t bit6 : 1;
    uint32_t bit7 : 1;
    uint32_t bit8 : 1;
    uint32_t bit9 : 1;
    uint32_t bit10 : 1;
    uint32_t bit11 : 1;
    uint32_t bit12 : 1;
    uint32_t bit13 : 1;
    uint32_t bit14 : 1;
    uint32_t bit15 : 1;
    uint32_t bit16 : 1;
    uint32_t bit17 : 1;
    uint32_t bit18 : 1;
    uint32_t bit19 : 1;
    uint32_t bit20_31 : 13;

}rfid_status_t;

/*0x020A*/
typedef struct __packed
{
    uint8_t dart_launch_opening_status;
    uint8_t reserved;
    uint16_t target_change_time;
    uint16_t latest_launch_cmd_time;

}dart_client_cmd_t;

/*0x020B*/
typedef struct __packed
{
    float hero_x;
    float hero_y;
    float engineer_x;
    float engineer_y;
    float standard_3_x;
    float standard_3_y;
    float standard_4_x;
    float standard_4_y;
    float standard_5_x;
    float standard_5_y;

}ground_robot_position_t;

/*0x020C*/
typedef struct __packed
{
    uint8_t mark_hero_progress;
    uint8_t mark_engineer_progress;
    uint8_t mark_standard_3_progress;
    uint8_t mark_standard_4_progress;
    uint8_t mark_standard_5_progress;
    uint8_t mark_sentry_progress;

}radar_mark_data_t;

/*0x020D*/
typedef struct __packed
{
    uint32_t successfully_redeemed : 11;
    uint32_t remote_successfully_redeemed : 4;
    uint32_t remote_HP : 4;
    uint32_t Reserved_bits : 13;

}sentry_info_t;

/*0x020E*/
typedef struct __packed
{
    uint8_t vulnerable_begin : 2;
    uint8_t vulnerable_now : 1;

}radar_info_t;

/*0x0303*/
typedef struct __packed
{
    float target_position_x;
    float target_position_y;
    uint8_t cmd_keyboard;
    uint8_t target_robot_id;
    uint8_t cmd_source;

}map_command_t;

/*0x0304*/
typedef struct __packed
{
    int16_t mouse_x;
    int16_t mouse_y;
    int16_t mouse_z;
    int8_t left_button_down;
    int8_t right_button_down;
    uint16_t keyboard_value_W : 1;
    uint16_t keyboard_value_S : 1;
    uint16_t keyboard_value_A : 1;
    uint16_t keyboard_value_D : 1;
    uint16_t keyboard_value_Shift : 1;
    uint16_t keyboard_value_Ctrl : 1;
    uint16_t keyboard_value_Q : 1;
    uint16_t keyboard_value_E : 1;
    uint16_t keyboard_value_R : 1;
    uint16_t keyboard_value_F : 1;
    uint16_t keyboard_value_G : 1;
    uint16_t keyboard_value_Z : 1;
    uint16_t keyboard_value_X : 1;
    uint16_t keyboard_value_C : 1;
    uint16_t keyboard_value_V : 1;
    uint16_t keyboard_value_B : 1;
    uint16_t reserved;

}remote_control_t;



typedef union __packed
{
    /* data */
    game_status_t game_status;
    game_result_t game_result;
    game_robot_HP_t game_robot_HP;
    event_data_t event_data;
    ext_supply_projectile_action_t ext_supply_projectile_action;
    referee_warning_t referee_warning;
    dart_info_t dart_info;
    robot_status_t robot_status;
    power_heat_data_t power_heat_data;
    robot_pos_t robot_pos;
    buff_t buff;
    air_support_data_t air_support_data;
    hurt_data_t hurt_data;
    shoot_data_t shoot_data;
    projectile_allowance_t projectile_allowance;
    rfid_status_t rfid_status;
    dart_client_cmd_t dart_client_cmd;
    ground_robot_position_t ground_robot_position;
    radar_mark_data_t radar_mark_data;
    sentry_info_t sentry_info;
    radar_info_t radar_info;
    map_command_t map_command;
    remote_control_t remote_control;
    uint8_t Data_RX[255];

}Read_Data_T;

typedef struct __packed
{
    /* data */
    game_status_t game_status;
    game_result_t game_result;
    game_robot_HP_t game_robot_HP;
    event_data_t event_data;
    ext_supply_projectile_action_t ext_supply_projectile_action;
    referee_warning_t referee_warning;
    dart_info_t dart_info;
    robot_status_t robot_status;
    power_heat_data_t power_heat_data;
    robot_pos_t robot_pos;
    buff_t buff;
    air_support_data_t air_support_data;
    hurt_data_t hurt_data;
    shoot_data_t shoot_data;
    projectile_allowance_t projectile_allowance;
    rfid_status_t rfid_status;
    dart_client_cmd_t dart_client_cmd;
    ground_robot_position_t ground_robot_position;
    radar_mark_data_t radar_mark_data;
    sentry_info_t sentry_info;
    radar_info_t radar_info;
    map_command_t map_command;
    remote_control_t remote_control;

}User_Data_T;

typedef union 
{
    struct __packed
    {
        /* data */
        frame_header_Typdef frame_header;
        enum Read_Cmd_ID_Typdef read_cmd_id;
        Read_Data_T read_data;
        uint16_t frame_tail;    
    }RX_Data;

    uint8_t Data[255];
    
}ALL_RX_Data_T;

uint8_t Read_Data_system(ALL_RX_Data_T *ALL_RX_Data , User_Data_T *user_data);

extern ALL_RX_Data_T ALL_RX_Data;
extern User_Data_T user_data;

#endif
