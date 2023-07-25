// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../../Structure/Headers/Includes.h"
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- Suit and Rank Arrays ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  //
std::string Suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
std::string Ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
// ---- ---- ---- ---- ---- ---- ---- ---- ---- Class Independent Methods ---- ---- ---- ---- ---- ---- ---- ---- //
/*  clear_terminal - Clears the terminal of a machine
*   Algorithm:
*       If the machine is a Windows machine, then "cls" is passed as a system command
*       If the machine is a Unix machine, then "clear" is passed as a system command
*/
void clear_terminal() {
// Windows machines
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
// Unix machines
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#endif
}

/*  color_text - Styles the console text of an entry
*   Input:
*       codeInput - Constant integer value that corresponds to the desired color to be outputted to console
*           codeInput = 31 - Red Text
*           codeInput = 32 - Green Text
*           codeInput = 33 - Yellow Text
*           codeInput = 34 - Blue Text
*           codeInput = 35 - Purple Text
*           codeInput = 36 - Cyan Text
*           codeInput = 37 - White Text
*       textInput - Constant string value that is passed to be changed to a different color
*   Algorithm:
*       codeInput is ran through a switch statement to check if it matches one of codes to style one of text
*       If codeInput matches one of the above input codes, then the parameter "textInput" is changed to the color
*       of the parameter "codeInput"
*   Output:
*       The function returns the string combination of "code + textInput + "\033[0m""
*           code is what is changed to according to codeInput
*           textInput is the string parameter that is fed into the function to be colored
*           \033[0m" is the ending of the unicode phrase to change the output in console
*/
std::string color_text(const int codeInput, const std::string textInput) {
    std::string code;
    switch (codeInput)
    {
    case 31:
        code = "\033[31m"; // Red Text
        break;
    case 32:
        code = "\033[32m"; // Green Text
        break;
    case 33:
        code = "\033[33m"; // Yellow Text
        break;
    case 34:
        code = "\033[34m"; // Blue Text
        break;
    case 35:
        code = "\033[35m"; // Purple Text
        break;
    case 36:
        code = "\033[36m"; // Cyan Text
        break;
    case 37:
        code = "\033[37m"; // White Text
        break;
    default:
        code = "\033[37m"; // Default Text
        break;
    }
    return code + textInput + "\033[0m";
}

/*  round_to_string - This function rounds a float value to two digits and returns it as a string
*   Input:
*       input - Constant float value that is fed into the function that is to be rounded
*   Algorithm:
*       This function uses ostringstream to cast a float to a string and round it two decimal values
*   Output:
*       return_string - Rounded string value to resemble a currency value
*/
std::string round_to_string(const float input) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << input;
    std::string return_string = oss.str();
    return return_string;
}

/*  round_input - This function rounds a float value to two digits to resemble a currency value
*   Input:
*       input - Float value that is to be rounded to a currency value
*   Algorithm:
*       This function utilizes the built in "round" function to round a value to two digits
*   Output:
*       input - Float value that is returned after being rounded to a currency value
*/
float round_input(float input) {
    input = round(input * 100) / 100;
    return input;
}

/*  time_sleep - This function causes the console to sleep for a given amount of time
*   Input:
*       input - Constant long value that resembles the time in milliseconds to have the console sleep
*   Algorithm:
*       This function utilizes the "sleep_for" built in function to cause the console to sleep
*/
void time_sleep(const long input) {
    long time = input;
    if (input == 1000) {
        time = 0;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

/* measure_time - This function measures the time that a function runs for
*   Input:
*       function - This is a constant function that is to be measured for how long it runs
*   Algorithm:
*       This function utilizes the built in function "high_resolution_clock" to time how long a function runs for
*/
template <typename Func> void measure_time(const Func function) {
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    float duration_time = duration.count();
    std::string rounded_time = round_to_string(duration_time);
    std::cout << std::endl << "Execution time: " << color_text(31, rounded_time) << " milliseconds." << std::endl;
}