// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CORE_H
#define CORE_H
#include "../HPP/Hand.hpp"

Hand update_stats(Hand& input); // 10
Hand csv_stats(Hand& input); // 11
std::tuple<Hand, Hand, Shoe> deal_hand(Hand& playerHand, Hand& dealerHand, Shoe& shoe); // 1 - Finished
void blackjack_strategy(Hand& playerHand, Hand& dealerHand); // 12
std::tuple<Hand, Hand, Shoe, bool> dealer_showing_ace(Hand& playerHand, Hand& dealerHand, Shoe& shoe); // 2 - Finished
std::vector<Hand> split_hand(Hand& input); // 3 - Finished
std::tuple<std::vector<Hand>, Hand, Hand, Shoe, int> same_rank_check(Hand& playerHand, Hand& dealerHand, Shoe& shoe); // 4 - Finished
std::tuple<Hand, Hand, Shoe> player_hand_logic(Hand& playerHand, Hand& dealerHand, Hand& referenceHand, Shoe& shoe, int& hand_counter); // 5
std::tuple<Hand, Shoe> dealer_hand_logic(std::vector<Hand>& playerHands, Hand& dealerHand, Shoe& shoe); // 6
std::tuple<Hand, Hand, Shoe> hand_comparison_logic(Hand& playerHand, Hand& dealerHand, Shoe& shoe, int& playerHandCount, int& currentHandCounter); // 7
std::tuple<Hand, Hand, Shoe> game_logic(Hand& playerHand, Hand& dealerHand, Shoe& shoe); // 8
void play_game(); // 9

void test_game();

#endif