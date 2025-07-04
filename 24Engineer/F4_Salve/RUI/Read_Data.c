/*
 *                   ___====-_  _-====___
 *             _--^^^#####//      \\#####^^^--_
 *          _-^##########// (    ) \\##########^-_
 *         -############//  |\^^/|  \\############-
 *       _/############//   (@::@)   \############\_
 *      /#############((     \\//     ))#############\
 *     -###############\\    (oo)    //###############-
 *    -#################\\  / VV \  //#################-
 *   -###################\\/      \//###################-
 *  _#/|##########/\######(   /\   )######/\##########|\#_
 *  |/ |#/\#/\#/\/  \#/\##\  |  |  /##/\#/  \/\#/\#/\#| \|
 *  `  |/  V  V  `   V  \#\| |  | |/#/  V   '  V  V  \|  '
 *     `   `  `      `   / | |  | | \   '      '  '   '
 *                      (  | |  | |  )
 *                     __\ | |  | | /__
 *                    (vvv(VVV)(VVV)vvv)
 * 
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *                神兽保佑            永无BUG
 */

/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-01-23 11:39:08
 * @LastEditors: Andy
 * @LastEditTime: 2024-01-24 17:24:20
 */

#include "Read_Data.h"
#include "Write_Data.h"
#include "stdint.h"
#include "string.h"


ALL_RX_Data_T ALL_RX_Data;
User_Data_T user_data;

/**
 * @name: WHW
 * @param {uint8_t} *RX_Data
 * @param {ALL_RX_Data_T} *ALL_RX_Data
 * @performance: 
 * @enter: 
 * @return {0，1，2}
 */
uint8_t Read_Data_system(ALL_RX_Data_T *ALL_RX_Data , User_Data_T *user_data)
{
    if((ALL_RX_Data->RX_Data.frame_header.SOF == (uint16_t)0xA5) \
        && (1 == Verify_CRC8_Check_Sum(ALL_RX_Data->Data , 5)) \
        && (1 == Verify_CRC16_Check_Sum(ALL_RX_Data->Data , ALL_RX_Data->RX_Data.frame_header.DataLenth + 9)))
    {
        ALL_RX_Data->Data[0]++;
        switch (ALL_RX_Data->RX_Data.read_cmd_id)
        {
            case game_state:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.game_status) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->game_status.game_progress = ALL_RX_Data->RX_Data.read_data.game_status.game_progress;
                    user_data->game_status.game_type = ALL_RX_Data->RX_Data.read_data.game_status.game_type;
                    user_data->game_status.stage_remain_time = ALL_RX_Data->RX_Data.read_data.game_status.stage_remain_time;
                    user_data->game_status.SyncTimeStamp = ALL_RX_Data->RX_Data.read_data.game_status.SyncTimeStamp;
                }               
            }break;

            case Match_results:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.game_result) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->game_result.winner = ALL_RX_Data->RX_Data.read_data.game_result.winner;
                }
            }break;

            case Robot_HP:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.game_robot_HP) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->game_robot_HP.blue_1_robot_HP    = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_1_robot_HP;
                    user_data->game_robot_HP.blue_2_robot_HP    = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_2_robot_HP;
                    user_data->game_robot_HP.blue_3_robot_HP    = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_3_robot_HP;
                    user_data->game_robot_HP.blue_4_robot_HP    = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_4_robot_HP;
                    user_data->game_robot_HP.blue_5_robot_HP    = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_5_robot_HP;
                    user_data->game_robot_HP.blue_7_robot_HP    = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_7_robot_HP;
                    user_data->game_robot_HP.blue_base_HP       = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_base_HP;
                    user_data->game_robot_HP.blue_outpost_HP    = ALL_RX_Data->RX_Data.read_data.game_robot_HP.blue_outpost_HP;
                    user_data->game_robot_HP.red_1_robot_HP     = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_1_robot_HP;
                    user_data->game_robot_HP.red_2_robot_HP     = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_2_robot_HP;
                    user_data->game_robot_HP.red_3_robot_HP     = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_3_robot_HP;
                    user_data->game_robot_HP.red_4_robot_HP     = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_4_robot_HP;
                    user_data->game_robot_HP.red_5_robot_HP     = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_5_robot_HP;
                    user_data->game_robot_HP.red_7_robot_HP     = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_7_robot_HP;
                    user_data->game_robot_HP.red_base_HP        = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_base_HP;
                    user_data->game_robot_HP.red_outpost_HP     = ALL_RX_Data->RX_Data.read_data.game_robot_HP.red_outpost_HP;
                }
            }break;

            case Venue_Events:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.event_data) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->event_data.buff_activated        = ALL_RX_Data->RX_Data.read_data.event_data.buff_activated;
                    user_data->event_data.buff_big              = ALL_RX_Data->RX_Data.read_data.event_data.buff_big;
                    user_data->event_data.buff_small            = ALL_RX_Data->RX_Data.read_data.event_data.buff_small;
                    user_data->event_data.Circular_Heights      = ALL_RX_Data->RX_Data.read_data.event_data.Circular_Heights;
                    user_data->event_data.Dart_hit_aim          = ALL_RX_Data->RX_Data.read_data.event_data.Dart_hit_aim;
                    user_data->event_data.Dart_hit_time         = ALL_RX_Data->RX_Data.read_data.event_data.Dart_hit_time;
                    user_data->event_data.refueling_Blood       = ALL_RX_Data->RX_Data.read_data.event_data.refueling_Blood;
                    user_data->event_data.Reserved_bits_1       = ALL_RX_Data->RX_Data.read_data.event_data.Reserved_bits_1;
                    user_data->event_data.Reserved_bits_2       = ALL_RX_Data->RX_Data.read_data.event_data.Reserved_bits_2;
                    user_data->event_data.supply_Blood          = ALL_RX_Data->RX_Data.read_data.event_data.supply_Blood;
                    user_data->event_data.Trapezoidal_heights_3 = ALL_RX_Data->RX_Data.read_data.event_data.Trapezoidal_heights_3;
                    user_data->event_data.Trapezoidal_heights_4 = ALL_RX_Data->RX_Data.read_data.event_data.Trapezoidal_heights_4;
                    user_data->event_data.Virtual_Shield        = ALL_RX_Data->RX_Data.read_data.event_data.Virtual_Shield;
                }
            }break;

            case Supply_action:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.ext_supply_projectile_action) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->ext_supply_projectile_action.reserved                = ALL_RX_Data->RX_Data.read_data.ext_supply_projectile_action.reserved;
                    user_data->ext_supply_projectile_action.supply_projectile_num   = ALL_RX_Data->RX_Data.read_data.ext_supply_projectile_action.supply_projectile_num;
                    user_data->ext_supply_projectile_action.supply_projectile_step  = ALL_RX_Data->RX_Data.read_data.ext_supply_projectile_action.supply_projectile_step;
                    user_data->ext_supply_projectile_action.supply_robot_id         = ALL_RX_Data->RX_Data.read_data.ext_supply_projectile_action.supply_robot_id;
                }
            }break;

            case Referee_warning:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.referee_warning) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->referee_warning.count                = ALL_RX_Data->RX_Data.read_data.referee_warning.count;
                    user_data->referee_warning.level                = ALL_RX_Data->RX_Data.read_data.referee_warning.level;
                    user_data->referee_warning.offending_robot_id   = ALL_RX_Data->RX_Data.read_data.referee_warning.offending_robot_id;
                }
            }break;

            case Dart_fire:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.dart_info) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->dart_info.Dart_aimed             = ALL_RX_Data->RX_Data.read_data.dart_info.Dart_aimed;
                    user_data->dart_info.Dart_aiming            = ALL_RX_Data->RX_Data.read_data.dart_info.Dart_aiming;
                    user_data->dart_info.dart_remaining_time    = ALL_RX_Data->RX_Data.read_data.dart_info.dart_remaining_time;
                    user_data->dart_info.Dart_success           = ALL_RX_Data->RX_Data.read_data.dart_info.Dart_success;
                    user_data->dart_info.Reserved_bits          = ALL_RX_Data->RX_Data.read_data.dart_info.Reserved_bits;
                }
            }break;

            case Robot_performan:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.robot_status) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->robot_status.maximum_HP                          = ALL_RX_Data->RX_Data.read_data.robot_status.maximum_HP;
                    user_data->robot_status.current_HP                          = ALL_RX_Data->RX_Data.read_data.robot_status.current_HP;
                    user_data->robot_status.power_management_chassis_output     = ALL_RX_Data->RX_Data.read_data.robot_status.power_management_chassis_output;
                    user_data->robot_status.power_management_gimbal_output      = ALL_RX_Data->RX_Data.read_data.robot_status.power_management_gimbal_output;
                    user_data->robot_status.power_management_shooter_output     = ALL_RX_Data->RX_Data.read_data.robot_status.power_management_shooter_output;
                    user_data->robot_status.robot_id                            = ALL_RX_Data->RX_Data.read_data.robot_status.robot_id;
                    user_data->robot_status.robot_level                         = ALL_RX_Data->RX_Data.read_data.robot_status.robot_level;
                    user_data->robot_status.shooter_barrel_heat_limit           = ALL_RX_Data->RX_Data.read_data.robot_status.robot_level;
                    user_data->robot_status.shooter_barrel_cooling_value        = ALL_RX_Data->RX_Data.read_data.robot_status.robot_level;
                    user_data->robot_status.chassis_power_limit                 = ALL_RX_Data->RX_Data.read_data.robot_status.chassis_power_limit;
                }
            }break;

            case time_power:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.power_heat_data) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->power_heat_data.buffer_energy                = ALL_RX_Data->RX_Data.read_data.power_heat_data.buffer_energy;
                    user_data->power_heat_data.chassis_current              = ALL_RX_Data->RX_Data.read_data.power_heat_data.chassis_current;
                    user_data->power_heat_data.chassis_power                = ALL_RX_Data->RX_Data.read_data.power_heat_data.chassis_power;
                    user_data->power_heat_data.chassis_voltage              = ALL_RX_Data->RX_Data.read_data.power_heat_data.chassis_voltage;
                    user_data->power_heat_data.shooter_17mm_1_barrel_heat   = ALL_RX_Data->RX_Data.read_data.power_heat_data.shooter_17mm_1_barrel_heat;
                    user_data->power_heat_data.shooter_17mm_2_barrel_heat   = ALL_RX_Data->RX_Data.read_data.power_heat_data.shooter_17mm_2_barrel_heat;
                    user_data->power_heat_data.shooter_42mm_barrel_heat     = ALL_RX_Data->RX_Data.read_data.power_heat_data.shooter_42mm_barrel_heat;
                }
            }break;

            case Robot_location:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.robot_pos) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->robot_pos.angle  = ALL_RX_Data->RX_Data.read_data.robot_pos.angle;
                    user_data->robot_pos.x      = ALL_RX_Data->RX_Data.read_data.robot_pos.x;
                    user_data->robot_pos.y      = ALL_RX_Data->RX_Data.read_data.robot_pos.y;
                }
            }break;

            case Robot_buff:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.buff) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->buff.attack_buff     = ALL_RX_Data->RX_Data.read_data.buff.attack_buff;
                    user_data->buff.cooling_buff    = ALL_RX_Data->RX_Data.read_data.buff.cooling_buff;
                    user_data->buff.defence_buff    = ALL_RX_Data->RX_Data.read_data.buff.defence_buff;
                    user_data->buff.recovery_buff   = ALL_RX_Data->RX_Data.read_data.buff.recovery_buff;
                }
            }break;

            case Air_support:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.air_support_data) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->air_support_data.airforce_status = ALL_RX_Data->RX_Data.read_data.air_support_data.airforce_status;
                    user_data->air_support_data.time_remain     = ALL_RX_Data->RX_Data.read_data.air_support_data.time_remain;
                }
            }break;

            case Damage_status:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.hurt_data) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->hurt_data.armor_id               = ALL_RX_Data->RX_Data.read_data.hurt_data.armor_id;
                    user_data->hurt_data.HP_deduction_reason    = ALL_RX_Data->RX_Data.read_data.hurt_data.HP_deduction_reason;
                }
            }break;

            case time_shooting:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.shoot_data) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->shoot_data.bullet_type           = ALL_RX_Data->RX_Data.read_data.shoot_data.bullet_type;
                    user_data->shoot_data.initial_speed         = ALL_RX_Data->RX_Data.read_data.shoot_data.initial_speed;
                    user_data->shoot_data.launching_frequency   = ALL_RX_Data->RX_Data.read_data.shoot_data.launching_frequency;
                    user_data->shoot_data.shooter_number        = ALL_RX_Data->RX_Data.read_data.shoot_data.shooter_number;
                }
            }break;

            case Allowable_ammo:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.projectile_allowance) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->projectile_allowance.projectile_allowance_17mm   = ALL_RX_Data->RX_Data.read_data.projectile_allowance.projectile_allowance_17mm;
                    user_data->projectile_allowance.projectile_allowance_42mm   = ALL_RX_Data->RX_Data.read_data.projectile_allowance.projectile_allowance_42mm;
                    user_data->projectile_allowance.remaining_gold_coin         = ALL_RX_Data->RX_Data.read_data.projectile_allowance.remaining_gold_coin;
                }
            }break;

            case RFID:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.rfid_status) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->rfid_status.bit0     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit0;
                    user_data->rfid_status.bit1     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit1;
                    user_data->rfid_status.bit2     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit2;
                    user_data->rfid_status.bit3     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit3;
                    user_data->rfid_status.bit4     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit4;
                    user_data->rfid_status.bit5     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit5;
                    user_data->rfid_status.bit6     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit6;
                    user_data->rfid_status.bit7     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit7;
                    user_data->rfid_status.bit8     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit8;
                    user_data->rfid_status.bit9     = ALL_RX_Data->RX_Data.read_data.rfid_status.bit9;
                    user_data->rfid_status.bit10    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit10;
                    user_data->rfid_status.bit11    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit11;
                    user_data->rfid_status.bit12    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit12;
                    user_data->rfid_status.bit13    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit13;
                    user_data->rfid_status.bit14    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit14;
                    user_data->rfid_status.bit15    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit15;
                    user_data->rfid_status.bit16    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit16;
                    user_data->rfid_status.bit17    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit17;
                    user_data->rfid_status.bit18    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit18;
                    user_data->rfid_status.bit19    = ALL_RX_Data->RX_Data.read_data.rfid_status.bit19;
                    user_data->rfid_status.bit20_31 = ALL_RX_Data->RX_Data.read_data.rfid_status.bit20_31;
                }
            }break;

            case Dart_directives:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.dart_client_cmd) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->dart_client_cmd.reserved                     = ALL_RX_Data->RX_Data.read_data.dart_client_cmd.reserved;
                    user_data->dart_client_cmd.dart_launch_opening_status   = ALL_RX_Data->RX_Data.read_data.dart_client_cmd.dart_launch_opening_status;                   
                    user_data->dart_client_cmd.latest_launch_cmd_time       = ALL_RX_Data->RX_Data.read_data.dart_client_cmd.latest_launch_cmd_time;
                    user_data->dart_client_cmd.target_change_time           = ALL_RX_Data->RX_Data.read_data.dart_client_cmd.target_change_time;
                }
            }break;

            case Ground_location:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.ground_robot_position) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->ground_robot_position.engineer_x     = ALL_RX_Data->RX_Data.read_data.ground_robot_position.engineer_x;
                    user_data->ground_robot_position.engineer_y     = ALL_RX_Data->RX_Data.read_data.ground_robot_position.engineer_y;
                    user_data->ground_robot_position.hero_x         = ALL_RX_Data->RX_Data.read_data.ground_robot_position.hero_x;
                    user_data->ground_robot_position.hero_y         = ALL_RX_Data->RX_Data.read_data.ground_robot_position.hero_y;
                    user_data->ground_robot_position.standard_3_x   = ALL_RX_Data->RX_Data.read_data.ground_robot_position.standard_3_x;
                    user_data->ground_robot_position.standard_3_y   = ALL_RX_Data->RX_Data.read_data.ground_robot_position.standard_3_y;
                    user_data->ground_robot_position.standard_4_x   = ALL_RX_Data->RX_Data.read_data.ground_robot_position.standard_4_x;
                    user_data->ground_robot_position.standard_4_y   = ALL_RX_Data->RX_Data.read_data.ground_robot_position.standard_4_y;
                    user_data->ground_robot_position.standard_5_x   = ALL_RX_Data->RX_Data.read_data.ground_robot_position.standard_5_x;
                    user_data->ground_robot_position.standard_5_y   = ALL_RX_Data->RX_Data.read_data.ground_robot_position.standard_5_y;
                }
            }break;

            case Radar_Marking:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.radar_mark_data) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->radar_mark_data.mark_engineer_progress   = ALL_RX_Data->RX_Data.read_data.radar_mark_data.mark_engineer_progress;
                    user_data->radar_mark_data.mark_hero_progress       = ALL_RX_Data->RX_Data.read_data.radar_mark_data.mark_hero_progress;
                    user_data->radar_mark_data.mark_sentry_progress     = ALL_RX_Data->RX_Data.read_data.radar_mark_data.mark_sentry_progress;                    
                    user_data->radar_mark_data.mark_standard_3_progress = ALL_RX_Data->RX_Data.read_data.radar_mark_data.mark_standard_3_progress;
                    user_data->radar_mark_data.mark_standard_4_progress = ALL_RX_Data->RX_Data.read_data.radar_mark_data.mark_standard_4_progress;
                    user_data->radar_mark_data.mark_standard_5_progress = ALL_RX_Data->RX_Data.read_data.radar_mark_data.mark_standard_5_progress;
                }
            }break;

            case Route_Informat:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.sentry_info) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->sentry_info.remote_HP                    = ALL_RX_Data->RX_Data.read_data.sentry_info.remote_HP;
                    user_data->sentry_info.remote_successfully_redeemed = ALL_RX_Data->RX_Data.read_data.sentry_info.remote_successfully_redeemed;
                    user_data->sentry_info.Reserved_bits                = ALL_RX_Data->RX_Data.read_data.sentry_info.Reserved_bits;
                    user_data->sentry_info.successfully_redeemed        = ALL_RX_Data->RX_Data.read_data.sentry_info.successfully_redeemed;
                }
            }break;

            case Radar_Informat:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.radar_info) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->radar_info.vulnerable_begin  = ALL_RX_Data->RX_Data.read_data.radar_info.vulnerable_begin;
                    user_data->radar_info.vulnerable_now    = ALL_RX_Data->RX_Data.read_data.radar_info.vulnerable_now;
                }               
            }break;

            case Minimap:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.map_command) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->map_command.cmd_keyboard         = ALL_RX_Data->RX_Data.read_data.map_command.cmd_keyboard;
                    user_data->map_command.cmd_source           = ALL_RX_Data->RX_Data.read_data.map_command.cmd_source;
                    user_data->map_command.target_position_x    = ALL_RX_Data->RX_Data.read_data.map_command.target_position_x;
                    user_data->map_command.target_position_y    = ALL_RX_Data->RX_Data.read_data.map_command.target_position_y;
                    user_data->map_command.target_robot_id      = ALL_RX_Data->RX_Data.read_data.map_command.target_robot_id;
                }
            }break;

            case remote:
            {
                if (sizeof(ALL_RX_Data->RX_Data.read_data.remote_control) == ALL_RX_Data->RX_Data.frame_header.DataLenth)
                {
                    user_data->remote_control.keyboard_value_A      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_A;
                    user_data->remote_control.keyboard_value_B      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_B;
                    user_data->remote_control.keyboard_value_C      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_C;
                    user_data->remote_control.keyboard_value_Ctrl   = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_Ctrl;
                    user_data->remote_control.keyboard_value_D      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_D;
                    user_data->remote_control.keyboard_value_E      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_E;
                    user_data->remote_control.keyboard_value_F      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_F;
                    user_data->remote_control.keyboard_value_G      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_G;
                    user_data->remote_control.keyboard_value_Q      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_Q;
                    user_data->remote_control.keyboard_value_R      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_R;
                    user_data->remote_control.keyboard_value_S      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_S;
                    user_data->remote_control.keyboard_value_Shift  = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_Shift;
                    user_data->remote_control.keyboard_value_V      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_V;
                    user_data->remote_control.keyboard_value_W      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_W;
                    user_data->remote_control.keyboard_value_X      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_X;
                    user_data->remote_control.keyboard_value_Z      = ALL_RX_Data->RX_Data.read_data.remote_control.keyboard_value_Z;
                    user_data->remote_control.left_button_down      = ALL_RX_Data->RX_Data.read_data.remote_control.left_button_down;
                    user_data->remote_control.mouse_x               = ALL_RX_Data->RX_Data.read_data.remote_control.mouse_x;
                    user_data->remote_control.mouse_y               = ALL_RX_Data->RX_Data.read_data.remote_control.mouse_y;
                    user_data->remote_control.mouse_z               = ALL_RX_Data->RX_Data.read_data.remote_control.mouse_z;
                    user_data->remote_control.reserved              = ALL_RX_Data->RX_Data.read_data.remote_control.reserved;
                    user_data->remote_control.right_button_down     = ALL_RX_Data->RX_Data.read_data.remote_control.right_button_down;
                }
            }break;
            
            default:
                return 2;   //没有对应的ID
        }
    }
    else
    {
        return 1;   //校验不通过
    }
    return 0;
    
}

