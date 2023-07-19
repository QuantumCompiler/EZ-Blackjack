// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef PREFUNC_H
#define PREFUNC_H
#include "Includes.h"

void clear_terminal();
std::string color_text(const int codeInput, const std::string textInput);
std::string round_to_string(const float input);
float round_input(float input);
void time_sleep(const long input);
template <typename Func> void measure_time(const Func function);

#endif