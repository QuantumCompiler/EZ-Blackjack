// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CORE_H
#define CORE_H
#include "../HPP/Hand.hpp"

void blackjack_strategy(Hand& playerHand, Hand& dealerHand);
std::tuple<Hand, Hand, Shoe> deal_hand(Hand& playerHand, Hand& dealerHand, Shoe& shoe);
std::tuple<Hand, Hand, Shoe, bool> dealer_showing_ace(Hand& playerHand, Hand& dealerHand, Shoe& shoe);
std::vector<Hand> split_hand(Hand& input);
std::tuple<std::vector<Hand>, Hand, Hand, Shoe, int> same_rank_check(Hand& playerHand, Hand& dealerHand, Shoe& shoe);
std::tuple<Hand, Hand, Shoe> player_logic(Hand& currentPlayerHand, Hand& dealerHand, Hand& masterPlayerHand, Shoe& shoe, int& hand_counter);
std::tuple<Hand, Shoe> dealer_logic(std::vector<Hand>& playerHands, Hand& dealerHand, Shoe& shoe);
std::tuple<Hand, Hand> hand_comparison_logic(Hand& playerHand, Hand& dealerHand, int& playerHandCount, int& currentHandCounter);
std::tuple<Hand, Hand, Shoe> hand_logic(Hand& playerHand, Hand& dealerHand, Shoe& shoe);
void play_game();

void test_game();

#endif