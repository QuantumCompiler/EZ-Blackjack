// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef CORE_H
#define CORE_H
#include "../HPP/Hand.hpp"

bool check_parameter_in_hand(const Hand& input, const std::string referenceParameter, const std::string checkingParameter);
bool check_same_parameter_in_hand(Hand& input, const std::string referenceParameter, const std::string checkingParameter = "");

void test_game();

#endif