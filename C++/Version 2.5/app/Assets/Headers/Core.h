// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CORE_H
#define CORE_H
#include "../HPP/Player.hpp"

/*  Logical order of implementation of functions
*   deal_hand / deal_hand_sim
*   blackjack_check / blackjack_check_sim
*   blackjack_strategy / blackjack_strategy_sim
*   split_hand / split_hand_sim
*   same_rank_check / same_rank_check_sim
*   player_logic / player_logic_sim
*   dealer_logic / dealer_logic_sim
*   hand_comparison_logic / hand_comparison_logic_sim
*   game_logic / simulate_logic
*/

void blackjack_strategy(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Hand>& playerHand, std::shared_ptr<Player>& dealer, bool showStrategy, bool splitOverride); // Strategy for how to play blackjack
std::string csv_generator(std::shared_ptr<Player>& input); // Generates a csv of the statistics for a game
void deal_hand(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& inputShoe); // Deals a hand to a player and dealer
void deal_hand_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& inputShoe, const float& playerWager); // Deals a hand to a player and dealer in a simulated game
// std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Shoe>> dealer_logic(std::vector<std::shared_ptr<Hand>>& playerHands, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe); // Processes logic of dealer
void dealer_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe); // Processes logic of dealer for simulated hand
// std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>, bool> blackjack_check(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& inputShoe); // Checks if a dealer is showing an Ace
bool blackjack_check_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& inputShoe, const float playerWager, const bool buyInsurance); // Checks if a dealer is showing an Ace
// std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> game_logic(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe); // Processes the overall logic of a hand played
void game_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe, float handWager); // Processes the overall logic for a simulated game
// std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>> hand_comparison_logic(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, int& playerHandCount, int& currentHandCounter); // Compares the hand of a player and dealer
void hand_comparison_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer); // Compares the hand of a player and dealer for a simulated game
// std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> player_logic(std::shared_ptr<Hand>& currentPlayerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Hand>& masterPlayerHand, std::shared_ptr<Shoe>& shoe, int& hand_counter);
void player_logic_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe, bool splitChoice); // Processes logic of player
void plot(const std::string& file, int yColumn); // Plots a bar chart from a csv file
size_t row_counter(const std::string& file);
// std::tuple<std::vector<std::shared_ptr<Hand>>, std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>, int> same_rank_check(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe); // Checks for the same rank of a player
void same_rank_check_sim(std::shared_ptr<Player>& humanPlayer, std::shared_ptr<Player>& dealer, std::shared_ptr<Shoe>& shoe, bool splitChoice); // Checks for the same rank of a player
void split_hand(std::shared_ptr<Player>& humanPlayer); // Splits the hand of a player for a simulated hand

#endif