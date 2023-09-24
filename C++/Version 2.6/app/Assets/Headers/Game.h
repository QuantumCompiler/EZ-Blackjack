// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef GAME_H
#define GAME_H
#include "../HPP/Core.hpp"

void blackjack(); // Incorporates game modes, an introduction to the program
void game_rules(); // Displays the rules for blackjack
void game_options(); // Gives the user options for what type of game they would like to play
void simulate_options(); // Gives the user options for what type of simulation they would like to perform
void simulate_choices(int input); // Displays the strategy of a blackjack simulation 
void single_player_versus_dealer(); // Provides a game for a player to play
void spv_all_options(); // Runs a simulation until a player reaches a set of parameters
void spv_hands_played(); // Runs a simulation until a player reaches a desired hands played total
void spv_max_bank(); // Runs a simulation until a player reaches a maximum bank total
void spv_min_bank(); // Runs a simulation until a player reaches a minimum bank total
void spv_out_of_bank(); // Runs a simulation until a player runs out of currency

#endif