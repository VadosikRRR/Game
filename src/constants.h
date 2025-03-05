#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace Constant{
    constexpr int player_attack_probability = 75;
    constexpr int player_visible_distance = 6;
    constexpr char player_char = '@';
    constexpr int med_kit_heal = 50;

    constexpr int attack_power_1 = 5;
    constexpr int attack_power_2 = 10;
    constexpr int attack_power_3 = 15;

    constexpr int max_health_1 = 30;
    constexpr int max_health_2 = 45;
    constexpr int max_health_3 = 60;

    constexpr int max_energy_1 = 50;
    constexpr int max_energy_2 = 100;
    constexpr int max_energy_3 = 150;

    constexpr int attack_probability_1 = 25;
    constexpr int attack_probability_2 = 50;
    constexpr int attack_probability_3 = 50;

    constexpr const char * enemy_name_1 = "Barbarian";
    constexpr const char * enemy_name_2 = "Pekka";
    constexpr const char * enemy_name_3 = "Godzilla";

    constexpr char enemy_symbol_1 = 'E';
    constexpr char enemy_symbol_2 = 'N';
    constexpr char enemy_symbol_3 = 'H';

    constexpr int energy_for_step = 10;
    constexpr int energy_rest = 10;
    constexpr int energy_for_hit = 15;

    constexpr int map_width = 80;
    constexpr int map_height = 60;
}
#endif // CONSTANTS_H