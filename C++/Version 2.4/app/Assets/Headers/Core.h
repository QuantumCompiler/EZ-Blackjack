// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CORE_H
#define CORE_H
#include "../HPP/Hand.hpp"

void blackjack_strategy(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, bool showStrategy, bool splitOverride); // Strategy for how to play blackjack
size_t row_counter(const std::string& file, size_t columnIndex);
std::string csv_generator(std::shared_ptr<Hand>& input); // Generates a csv of the statistics for a game
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> deal_hand(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& inputShoe); // Deals a hand to a player and dealer
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> deal_hand_sim(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& inputShoe, const float& playerWager); // Deals a hand to a player and dealer in a simulated game
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Shoe>> dealer_logic(std::vector<std::shared_ptr<Hand>>& playerHands, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe); // Processes logic of dealer
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Shoe>> dealer_logic_sim(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe); // Processes logic of dealer for simulated hand
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>, bool> dealer_showing_ace(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& inputShoe); // Checks if a dealer is showing an Ace
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>, bool> dealer_showing_ace_sim(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& inputShoe, const float playerWager, const bool buyInsurance); // Checks if a dealer is showing an Ace
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> game_logic(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe); // Processes the overall logic of a hand played
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> game_logic_sim(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe, float handWager); // Processes the overall logic for a simulated game
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>> hand_comparison_logic(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, int& playerHandCount, int& currentHandCounter); // Compares the hand of a player and dealer
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>> hand_comparison_logic_sim(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand); // Compares the hand of a player and dealer for a simulated game
void play_game(); // Provides a game for a player to play
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> player_logic(std::shared_ptr<Hand>& currentPlayerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Hand>& masterPlayerHand, std::shared_ptr<Shoe>& shoe, int& hand_counter);
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> player_logic_sim(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe, bool splitChoice); // Processes logic of player
void plot(const std::string& file, int yColumn); // Plots a bar chart from a csv file
std::tuple<std::vector<std::shared_ptr<Hand>>, std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>, int> same_rank_check(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe); // Checks for the same rank of a player
std::tuple<std::shared_ptr<Hand>, std::shared_ptr<Hand>, std::shared_ptr<Shoe>> same_rank_check_sim(std::shared_ptr<Hand>& playerHand, std::shared_ptr<Hand>& dealerHand, std::shared_ptr<Shoe>& shoe, bool splitChoice); // Checks for the same rank of a player
void simulate_game(); // Provides a simulated game for a player
std::vector<std::shared_ptr<Hand>> split_hand(std::shared_ptr<Hand>& input); // Splits the hand of a player
void split_hand_sim(std::shared_ptr<Hand>& input); // Splits the hand of a player for a simulated hand
void stats_tracker(std::shared_ptr<Hand>& input); // Updates the statistics for a game

#endif