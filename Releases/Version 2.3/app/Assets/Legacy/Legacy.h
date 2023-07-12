// ---------- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <typeinfo>
#include <vector>
/* ----- ----- ----- ----- ----- ----- ----- Steps to playing blackjack ----- ----- ----- ----- ----- ----- ----- -----
1 - Initialize the deck of cards.
2 - Shuffle the deck of cards.
3 - Create a player and a dealer.
4 - Prompt the player to enter their name.
5 - Prompt the player to enter the amount of money they want to start with.
6 - Prompt the player to enter the number of decks they want to play with.
7 - Start the game:
    - Deal two cards face-up to the player.
    - Deal two cards to the dealer (one face-up, one face-down).
8 - Check for immediate wins:
    - If the dealer's face-up card is an Ace, offer insurance to the player.
    - If the player has a blackjack (hand value of 21), go to step 12.
    - If the dealer has a blackjack:
        - If the player took insurance and the dealer has a blackjack, resolve the insurance bet and end the game.
        - If the player did not take insurance, reveal the dealer's face-down card and end the game.
9 - Player's turn:
    - Prompt the player to choose an action (hit, stand, double down, split).
        - Only offer options to the player that are available: e.g. If the can split or double down
    - Perform the chosen action and update the player's ha`nd.
    - If the player busts (hand value exceeds 21), go to step 11.
    - If the player chooses to stand, go to step 12.
    - If the player chooses to double down, perform the action and go to step 12.
    - If the player chooses to split, create a new hand for the player and repeat step 9 for each hand.
10 - Dealer's turn:
    - Reveal the dealer's face-down card.
    - If the dealer has a soft 17 (hand value of 17 with an Ace counted as 11), the dealer must hit.
    - If the dealer busts, go to step 12.
11 - Determine the winner:
    - Compare the hand values of the player and dealer.
    - If the player's hand value is higher, the player wins.
    - If the dealer's hand value is higher, the dealer wins.
    - If the dealer's hand value is higher, the dealer wins.
    - Repeat the above for all hands of the player
12 - End the game:
    - Update the player's bankroll based on the outcome.
    - Prompt the player to play again or quit.
*/
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- Suit and Rank Arrays ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  //
/*
 * Declaration and initialization of arrays representing the suits and ranks in a deck of cards.
 */
std::string Suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
std::string Ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
// ---- ---- ---- ---- ---- ---- ---- ---- ---- Class Independent Methods ---- ---- ---- ---- ---- ---- ---- ---- //
/*
* These methods DO NOT require a class or structs to operate
*/
// Check Card Parameter Method - check_card_parameter
/*
 * This method takes in two inputs:
 * FuncInput(1): feeding_parameter - String, This string refers to a rank or suit of a card
 * FuncInput(2): checking_parameter - String, This string refers to the specific rank or suit of a card that you are checking against
 * FuncOutput: result - This method returns a boolean value after the feeding_parameter is checked against checking_parameter
 */
bool check_card_parameter(const std::string feeding_parameter, const std::string checking_parameter)
{
    // Boolean value that is returned after checking
    bool result = false;
    if (feeding_parameter == checking_parameter)
    {
        result = true;
        return result;
    }
    else
    {
        return result;
    }
}
// Clear Terminal Method - clear_terminal
/*
 * This method clears the terminal for both Unix and Windows Systems
 * This method does not return a value, it simply clears the terminal
 */
void clear_terminal()
{
// Windows machines
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
// Unix machines
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#endif
}
// Color Text Method - color_text
/*
* This method changes the output of a text in the console of a machine
* FuncInput(1): a - Integer, this value pertains to the unicode for changing colors in consoles
* FuncInput(2): text - String, this is the text that is to be colored in the console
* Different Color Options For (a):
    - 31 = Red Text
    - 32 = Green Text
    - 33 = Yellow Text
    - 34 = Blue Text
    - 35 = Purple Text
    - 36 = Cyan Text
    - 37 = White Text
* FuncOutput: code + text + "\033[0m" - This method returns a string value that will be colored in the console
*/
std::string color_text(const int a, const std::string &text)
{
    // Beginning part of Unicode sytnax
    std::string code;
    switch (a)
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
        code = "\033[0m"; // Default Text
        break;
    }
    return code + text + "\033[0m";
}
// Float Validation Method - float_validation
/*
 * - This method checks to see if an input is floating point number
 * - FuncInput(1): entry - String value that is being checked if it is a floating point number
 * - FuncOutput: result - String that returns a checked value determining if the number was successfully converted
 *  - Here are the different possible returns from the method
 *  - FNNV - Failed non negative value, this is not a number
 *  - FNV1 - Failed negative value 1, this is not a number that has a (-) at the beginning of the string
 *  - FNV2 - Failed negative value 2, this is a negative value
 *  - Passed - This is a positive float that can be successfully converted from a string to a float
 */
std::string float_validation(const std::string entry)
{
    std::string result;
    bool has_decimal = false;
    if (entry.front() != '-')
    {
        for (int i = 0; i < entry.length(); i++)
        {
            if (!isdigit(entry[i]))
            {
                if (entry[i] == '.' && !has_decimal)
                {
                    has_decimal = true;
                }
                else
                {
                    // Failed Non-Negative Value
                    result = "FNNV";
                    return result;
                }
            }
            else if (isdigit(entry[i]))
            {
                continue;
            }
            else {}
        }
    }
    else if (entry.front() == '-')
    {
        for (int i = 1; i < entry.length(); i++)
        {
            if (!isdigit(entry[i]))
            {
                if (entry[i] == '.' && !has_decimal)
                {
                    has_decimal = true;
                }
                else
                {
                    // Failed Negative Value 1
                    result = "FNV1";
                    return result;
                }
            }
            else if (isdigit(entry[i]))
            {
                continue;
            }
            else {}
        }
        // Failed Negative Value 2
        result = "FNV2";
        return result;
    }
    else{}
    result = "Passed";
    return result;
}
// Round to String Method - round_to_string
/*
* This method takes in a floating point value and converts it to a rounded string
* FuncInput(1): entry_value - Float, Floating point number that is to be converted to a string
* FuncOutput: return_string - String, entry_value that is rounded to (2) decimal places
*/
std::string round_to_string(const float entry_value)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << entry_value;
    std::string return_string = oss.str();
    return return_string;
}
// Round Wager or Bank Method - round_wager_bank
/*
* This method takes in an entry value and rounds it to two decimal places, like a currency
* FuncInput(1): entry_value - Float, Floating point value that is to be rounded
* FuncOutput: entry_value - Float, Floating point value that is returned after being rounded
*   -> to two decimal places, like a currency
*/
float round_wager_bank(float entry_value)
{
    entry_value = round(entry_value * 100) / 100;
    return entry_value;
}
// Time Sleep Method - time_sleep
/*
* This method causes the console to sleep
* FuncInput(1): sleep_time - Long, Long point value that is supposed to resemble time in milliseconds
* This method does not return a value, it simply causes the console to sleep for a given number
* -> of milliseconds
*/
void time_sleep(const long sleep_time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
}
// Measure Time Method - measure_time
/*
* This method takes in a method and calculates the time that it takes for a given method to execute
* FuncInput(1): method - Method, Method that is to be timed for how long it takes to execute
* This method does not return any values, instead, it outputs to console how long a method took to execute
* -> in milliseconds
*/
template <typename Func> void measure_time(const Func method)
{
    auto start = std::chrono::high_resolution_clock::now();
    method();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    float duration_time = duration.count();
    std::string rounded_time = round_to_string(duration_time);
    std::cout << std::endl << "Execution time: " << color_text(31, rounded_time) << " milliseconds." << std::endl;
}
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- Structs & Classes ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  //
// Card Struct - Playing_Card
/*
* This struct contains three parameters in it
*   StructParam(1): rank - String, this is the rank of a card, e.g. Ace, King, etc.
*   StructParam(2): suit - String, this is the suit of a card, e.g. Hearts, Clubs, etc.
*   StructParam(3): card_value: Integer, this is the value of a card based off of rank
*/
struct Playing_Card
{
    std::string rank;
    std::string suit;
    int card_value;
};
// Card Class - Card
/*
* This class is the card class
* The following public variables that are accessible to all methods, in the class, as well as outside the class are:
*   - There are a total of four public variables for this class
*       - PubVar(1): card - Playing_Card, this is the public Playing_Card struct that inherits all of the parameters
*       -> from the Playing_Card struct
*       - PubVar(2): display_rank - String, this is the modified (colored) string that represents the rank of the card
*       - PubVar(3): display_suit - String, this is the modified (colored) string that represents the suit of the card
*       - PubVar(4): display_value - String, this is the modified (colored) string that represents the value of the card
* The constructor of this class is as follows
*   - Class Constructor, there are two inputs that are to be taken in for the constructor of this class
*       - ClassConst(1): rank - String, this is the rank of the card that is being set for the Card object
*       - ClassConst(2): suit - String, this is the suit of the card that is being set for the Card object
*   - This class constructor does the following
*       - Assigns the struct parameter of (rank) to the constructor input of (rank)
*       - Assigns the struct parameter of (suit) to the constructor input of (suit)
*       - Checks the rank of the constructor input (rank) to be in the Ranks array previously defined
*           - If the constructor input of (rank) exists in the Ranks array, the public variable of (display_rank) is set
*           -> to the color green
*           - It then assigns the struct parameter of (card_value) to the correct card value depending on the rank of the card
*               - The default value of an Ace is set to 11
*           - The public variable of (display_value) is then set to the color yellow 
*       - Checks the suit of the constructor input (suit) to be in the Suits array previously defined
*           - If the constructor input of (suit) exists in the Suits array, the public variable of (display_suit) is set
*           -> to the following colors depending on the suit
*               - If the suit is a Club or Spade, the public variable of (display_suit) is set to purple
*               - If the suit is a Diamond or Heart, the public variable of (display_suit) is set to red
*               - If the suit is not any of the above, the public variable of (display_suit) is set to white
* The other methods of this class include
*   - Set New Value Method - Set_New_Value
*       - This method changes the value of a card depending on what is fed into the input
*       - FuncInput(1): new_value - Integer, this is the new value of the card that it will be changed to
*       - FuncOutput: card - Playing_Card, this is the returned card after the method executes
*   - Representation Method
*       - This method ouputs the public variable (display_rank) and (display_suit) to the console
*/
class Card
{
public:
    // Public variables
    Playing_Card card;
    std::string display_rank;
    std::string display_suit;
    std::string display_value;
    // Constructor
    Card(const std::string rank, const std::string suit)
    {
        card.rank = rank;
        card.suit = suit;
        for (int i = 0; i <= 12; i++)
        {
            if (check_card_parameter(card.rank, Ranks[i]))
            {
                card.rank = Ranks[i];
                this->display_rank = color_text(32, card.rank);
                switch (i)
                {
                case 0:
                    card.card_value = 11;
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    card.card_value = stoi(Ranks[i]);
                    break;
                case 9:
                case 10:
                case 11:
                case 12:
                    card.card_value = 10;
                    break;
                default:
                    card.card_value = stoi(Ranks[i]);
                    break;
                }
                this->display_value = color_text(33, std::to_string(card.card_value));
            }
            else {}
        }
        this->display_suit = color_text(37, card.suit);
        for (int i = 0; i <= 3; i++)
        {
            if (check_card_parameter(card.suit, Suits[i]))
            {
                card.suit = Suits[i];
                switch (i)
                {
                case 0:
                case 3:
                    this->display_suit = color_text(35, card.suit);
                    break;
                case 1:
                case 2:
                    this->display_suit = color_text(31, card.suit);
                    break;
                default:
                    this->display_suit = color_text(37, card.suit);
                    break;
                }
            }
            else {}
        }
    }
    // Set New Value Method - Set_New_Value
    Card& Set_New_Value(const int new_value)
    {
        card.card_value = new_value;
        this->display_value = color_text(33, std::to_string(card.card_value));
        return *this;
    }
    // Representation method
    friend std::ostream &operator<<(std::ostream &os, const Card &currentCard)
    {
        os << currentCard.display_rank << " of " << currentCard.display_suit;
        return os;
    }
};
// Deck Struct - Deck
/*
* This struct contains three parameters in it
*   StructParam(1): cards - Vector, this is a vector that contains card objects
*   StructParam(2): returned_cards - Vector, this is a vector that contains returned cards. This vector is onl necessary for
*               -> for when the cards are being displayed to the console.
*   StructParam(3): rigged_cards - Vector, this is a vector that contains a rigged set of cards. This vector is only used for
*               -> testing certain aspects within the application
*   StructParam(4): num_of_decks - Integer, this is the number of decks that are going to be present in the shoe
*/
struct Deck
{
    std::vector<Card> cards;
    std::vector<Card> returned_cards;
    std::vector<Card> rigged_cards;
    int num_of_decks;
};
// Shoe Class - Shoe
/*
* This is the shoe class
* The following are public variables that are accessible to all methods, in the class, as well as outside the scope of the class
*   - There is only one public variable for this class
*       - PubVar(1): deck - Deck, this is the public struct Deck that inherits all of the public parameters from the Deck struct
* The contstructor for this class is as follows
*   - Class Constructor, there are no inputs that are necessary for the constructor of this class
*   - This class constructor does the following
*       - Assigns the initial number of decks that are present in the shoe to be zero
*       - Creates an empty vector for the cards, returned_cards, and rigged_cards public struct parameters
* The methods that exist inside this class are the following
*   - Create Shoe Method - Create_Shoe
*       - This method creates the shoe that the game is to use for playing Blackjack
*       - This method will iterate first through the Ranks array and assign a separate suit for each rank. It then proceeds to move
*       -> move on to the next rank and do the same. 
*       - Depending on how many decks are chosen by the user to be played, dictates how many times the above process is repeated
*       - This method must show up after the Deck_Count method, otherwise the default number of decks that will be played with is 1.
*       - This method will return a modified Shoe object by changing the public structs (cards) parameter 
*   - Deck Count Method - Deck_Count
*       - This method prompts the user to enter an integer value for the number of decks that they would like to play with
*       - This method does not require an input, instead, it modifies the struct parameter num_of_decks, so that it can be used later
*       -> on outside the scope of this method and class
*       - This method will return a modified Shoe object by changing the public structs (num_of_decks) parameter
*   - Draw Method - Draw
*       - This method will pull the last card out of the public structs (cards or rigged_cards) parameter
*       - This method does not require an input for it
*           - If the (rigged_cards) parameter is empty, then the card will be drawn from the (cards) parameter
*           - If there exists cards in the (rigged_cards) parameter, then the card will be drawn from (rigged_cards)
*       - This method will return a Card object
*   - Deal Cards Method - Deal_Cards
*       - This method prints the cards in either the public structs (cards) or (rigged_cards) parameter
*       - This method does not require an input for it, and it does not return a value
*       - Depending on whether the (rigged_cards) parameter is empty or not, the vector that the cards are pulled from may be different
*           - If the (rigged_deck) parameter is empty, then cards will be displayed from the (cards) parameter
*           - If there is a single card in the (rigged_deck) parameter, then cards will be displayed from (rigged_cards)
*       - This method will also indicate separate decks that are delt
*   - Shuffle Method - Shuffle
*       - This method will shuffle the cards that are present in a shoe
*       - This method does not require an input and it does not return anything, it simply modifies the shoe that is being used in game
*   - Representation Method
*       - This method displays the size of the public structs (cards) parameter and the number of decks that are being played with
*       - FuncInput(1): os - Ostream, this is an ostream object that is passed to the function
*       - FuncInput(2): shoe - Shoe, this is a Shoe object that is being passed so that it can correctly display the right statistics
*/
class Shoe
{
public:
    // Public variables
    Deck deck;
    // Constructor
    Shoe()
    {
        deck.num_of_decks = 0;
        deck.cards = {};
        deck.returned_cards = {};
        deck.rigged_cards = {};
    }
    // Create Shoe Method
    Shoe& Create_Shoe()
    {
        if (deck.num_of_decks == 0) {
            deck.num_of_decks = 1;
        }
        else {}
        for (int i = 1; i <= deck.num_of_decks; i++)
        {
            for (const auto &rank : Ranks)
            {
                for (const auto &suit : Suits)
                {
                    deck.cards.push_back(Card(rank, suit));
                }
            }
        }
        return *this;
    }
    Shoe& Deck_Count()
    {
        bool loop_passed = false;
        while (!loop_passed)
        {
            std::string input;
            std::cout << std::endl << "Please enter the number of decks you'd like to play with: ";
            std::cin >> input; 
            for (int i = 0; i < input.size(); i++)
            {
                if (isdigit(input[i]) && input[0] != '0')
                {
                    loop_passed = true;
                    continue;
                }
                else if (!isdigit(input[i]) || input[i] == '0')
                {
                    loop_passed = false;
                    std::cout << "\n" + color_text(31, "Invalid Response") + " of " + color_text(31, input) + ". Please enter a positive integer for a deck count." "\n" << std::endl; 
                    break;
                }
                else {}
            }
            if (loop_passed)
            {
                deck.num_of_decks = stoi(input);
                break;
            }
            else {}
        }
        std::cout << std::endl << "This shoe will be comprised of " + color_text(33, std::to_string(deck.num_of_decks)) + " deck(s)." << std::endl; 
        return *this;
    }
    // Draw Method
    Card Draw()
    {
        if (deck.rigged_cards.empty())
        {
            Card card_drawn = deck.cards.back();
            deck.cards.pop_back();
            return card_drawn;
        }
        else if (deck.rigged_cards.size() > 0)
        {
            Card card_drawn = deck.rigged_cards.back();
            deck.rigged_cards.pop_back();
            return card_drawn;
        }
        else {}
    }
    // Deal Cards Method
    void Deal_Cards()
    {
        std::cout << "\n" "Here are the cards in the shoe:" << std::endl; 
        bool rigged_deck = false;
        int deck_counter = 0;
        int card_dealt_number = 1;
        if (deck.rigged_cards.size() > 0)
        {
            rigged_deck = true;
        }
        else if (deck.cards.size() > 0)
        {
            rigged_deck = false;
        }
        else {}
        if (!rigged_deck)
        {
            int num_of_cards = deck.cards.size();
            deck.returned_cards.clear();
            for (int i = 1; i <= num_of_cards; i++)
            {
                if (i == 1)
                {
                    std::cout << std::endl << "Dealing the deck(s):" << std::endl << "\n"; 
                }
                else {}
                Card drawn_card = Draw();
                deck.returned_cards.push_back(drawn_card);
                std::cout << "Card dealt number: " << color_text(33, std::to_string(card_dealt_number)) << " - " << drawn_card << std::endl;
                if (card_dealt_number % 52 == 0)
                {
                    deck_counter++;
                    if (deck.cards.size() > 0)
                    {
                        std::cout << std::endl << "End of remaining deck " << std::to_string(deck_counter) << ". " << std::to_string(card_dealt_number) 
                        << " cards dealt, " << std::to_string(deck.cards.size()) << " cards remaining in shoe." "\n" << std::endl;
                    }
                    else if (deck.cards.empty())
                    {
                        std::cout << std::endl << "End of shoe." "\n" << std::endl; 
                    }
                    else {}
                }
                else if (card_dealt_number % 52 != 0)
                {
                    if (deck.cards.empty())
                    {
                        std::cout << std::endl << "End of shoe." "\n" << std::endl; 
                    }
                    else {}
                }
                else {}
                card_dealt_number += 1;
            }
            deck.cards = deck.returned_cards;
            reverse(deck.cards.begin(), deck.cards.end());
            std::cout << color_text(33, std::to_string(deck.cards.size())) << " cards left in shoe." << std::endl; 
        }
        else if (rigged_deck)
        {
            int num_of_rigged_cards = deck.rigged_cards.size();
            deck.returned_cards.clear();
            for (int i = 1; i <= num_of_rigged_cards; i++)
            {
                if (i == 1)
                {
                    std::cout << std::endl << "Dealing rigged shoe:" "\n" << std::endl; 
                }
                else {}
                Card drawn_card = Draw();
                deck.returned_cards.push_back(drawn_card);
                std::cout << "Card dealt number: " << color_text(33, std::to_string(card_dealt_number)) << " - " << drawn_card << std::endl;
                card_dealt_number += 1;
            }
            deck.rigged_cards = deck.returned_cards;
            reverse(deck.rigged_cards.begin(), deck.rigged_cards.end());
            std::cout << std::endl << color_text(33, std::to_string(deck.rigged_cards.size())) << " cards left in rigged shoe." << std::endl; 
        }
        else {}
    }
    // Shuffle Method
    void Shuffle()
    {
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(deck.cards.begin(), deck.cards.end(), g);
    }
    // Representation method
    friend std::ostream &operator<<(std::ostream &os, const Shoe &shoe)
    {
        os << "\n" "Deck of " << color_text(33, std::to_string(shoe.deck.cards.size())) << " cards and "
        << color_text(33, std::to_string(shoe.deck.num_of_decks)) << " deck(s)." << std::endl;
        return os;
    }
};
// Player Struct - Player
/*
* This struct contains the following parameters in it
*/
struct Player
{
    bool can_buy_insurance;
    bool can_double_down;
    bool can_split_hand;
    bool chose_buy_insurance;
    bool chose_split_aces;
    bool chose_split_hand;
    bool has_hit;
    bool split_decision;
    float bank_total;
    float net;
    float wager;
    float insurance_wager;
    int cards_total;
    int individual_hands;
    int hands_played;
    std::string name;
    std::string display_name;
    std::string display_bank_total;
    std::string display_net;
    std::string display_wager;
    std::string display_insurance_wager;
    std::string display_cards_total;
    std::string display_hands_played;
    std::vector<Card> cards;
    std::vector<float> hand_bank_totals;
    std::vector<float> hand_nets;
    std::vector<float> hand_wagers;
    std::vector<int> hand_card_totals;
    std::vector<int> hand_hands_played;
};
// Hand Class - Hand
/*
* This is the Hand class
* The following are public variables that can be accessed to all methods inside the class as well as outside the scope of this class
* The constructor for this class is as follows
*   - Class constructor, this class constructor does not take any inputs
*   - This class constructor does the following
* The methods that exist in this class are the following
*   - Add Cards to Hand Method - Add_Card_To_Hand
*       - This method adds a card to a hand object, it takes a card object as an input and will return a hand object
*       - FuncInput(1): card - Card, card object that possesses all the attributes of a regular card object
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Add Hand Total Method - Add_Hand_Total
*       - This method adds up the card totals of a players hand
*       - This method does not take any inputs, but it returns a Hand object
*       - This method first counts how many Ace's are present in a players hand
*           - If there is one Ace in the hand, the value of the Ace is set to 1
*           - If there are multiple Aces in the hand, only the first Ace in the hand will be counted as an 11, the rest will be 1's
*       - This method then checks if the user has a value greater than 21
*           - If the value is greater than 21, all Ace's in the hand are set to 1, otherwise the value of the card is kept the same
*           - The public variable of (player.cards_total) is then assigned to this value of (running_hand_value)
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Set Player Name Method - Name
*       - This method sets the player name that a player will be identified with
*       - This method does not take any inputs, but it returns a Hand object
*       - This method modifies both the public variables of (player.name) and (player.display_name)
*           - The default color for the display name is set to blue
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Bank Deposit Method - Deposit
*       - This method deposits the amount of currency that a player wishes to play with
*       - This method does not require an input, but it does return a Hand object
*       - This method goes through a float validation process, where it is checking if the input was indeed a float
*           - The four possible results are the same of the float_validation method as previously defined
*           - If the input passes the float validation method, it then is converted to a float and rounded like a currency
*           - This value is then assigned to the (player.bank_total) public variable
*       - This method will then output to console what the player input as their bank currency deposit
*       - This method then will append this bank total to the (player.hand_bank_totals) method
*           - If the previous bank total is zero, (Which can happen at the beginning of the game or when a player runs out of currency)
*           -> then (player.hand_wagers), (player.hand_nets), and (player.card_totals) have a zero value appended to them
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Hit Hand Method - Hit
*       - This method removes a card from a shoe and adds it to a players hand
*       - This method takes in a Shoe object as an input and returns a Hand object
*       - FuncInput(1): shoe - Shoe, this is a shoe object. The object is passed by reference because it is modifying the Shoe object as well
*       -> as the Hand object
*       - This method also adds the up the hand's total after the cards have been added to the Hand object
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Insurance Method - Insurance
*       - This method determines if a player wants to buy insurance or not
*       - This method first prompts the user if they would like to buy insurance
*       - This method does not take in an input but it returns a Hand object
*           - If the user inputs (y) for yes, (player.chose_buy_insurance) is changed to true and the loop is broken
*               - The public variable (player.insurance_wager) is then set to half of the player's original wager (player.wager)
*               - The public variable (player.bank_total) is then updated to incorporate the placing of the insurance wager
*           - If the user inputs (n) for no, (player.chose_buy_insurance) is changed to false and the loop is broken
*           - If the user does not input either one of the above options, an error is thrown and the user is prompted to re-enter their decision
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Place Wager Method - Place_Wager
*       - This method places a wager for a player
*       - This method does not take in any input, but it returns a Hand object as an output
*       - This method processes logic to make sure that the wager is a valid input e.g. A positive number, not more than the bank total
*       - This method outputs to console how much a player places for a wager as well as their current bank total
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Show Hand Method - Show_Hand
*       - This method shows the hand of a player
*       - This method takes in two strings as optional inputs and returns a hand object
*       - FuncInput(1): option - String, this is a string that allows users to signify the current state of a players hand
*       - FuncInput(2): dealer_show - String, this is a string that dictates if a dealer is to show their face down card
*       - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
*   - Update Bank Method - Update_Bank
*       - This method updates the bank total of a player
*       - This method takes in three separate values as input: A string, Hand object, and a float
*       - FuncInput(1): choice - String, this is the value that is passed to determine what outcome has happened
*           - 'W' - Player wins hand, does not apply to Blackjacks, currency added to (bank_total) public variable
*           - 'L' - Player loses hand, currency subtracted from (bank_total) public variable
*           - 'P' - Player pushes hand, original wager is added back to (bank_total) public variable
*           - 'B' - Player has Blackjack, player wins 3:2 of original bet to be added to (bank_total) public variable
*           - 'I' - Player wins insurance, player wins 2:1 payout of insurance bet to be added to (bank_total) public variable
*       - FuncInput(2): hand - Hand, this is the hand object that is passed to be updated
*       - FuncInput(3): wager - Float, this is the wager that is to be added or subtracted from (bank_total)
*   - Reset Player Variables Method - Reset
*       - This method resets some of the public variables in a Hand object
*       - This method takes in a single hand object as an input and returns a Hand object
*       - FuncInput(1): hand - Hand, this is the hand object where the following public variables are reset
*           - hand.player.can_buy_insurance = false
*           - hand.player.can_double_down = false
*           - hand.player.can_split_hand = false
*           - hand.player.chose_buy_insurance = false
*           - hand.player.chose_split_aces = false
*           - hand.player.chose_split_hand = false
*           - hand.player.net = 0
*           - hand.player.wager = 0
*           - hand.player.insurance_wager = 0
*           - hand.player.cards_total = 0
*           - hand.player.individual_hands = 1
*           - hand.player.display_bank_total cleared
*           - hand.player.display_net cleared
*           - hand.player.display_wager cleared
*           - hand.player.display_cards_total cleared
*           - hand.player.display_hands_played cleared
*           - hand.player.cards cleared
*/
class Hand
{
public:
    // Public variables
    Player player;
    // Constructor
    Hand()
    {
        player.can_buy_insurance = false;
        player.can_double_down = false;
        player.can_split_hand = false;
        player.chose_buy_insurance = false;
        player.chose_split_aces = false;
        player.chose_split_hand = false;
        player.has_hit = false;
        player.split_decision = false;
        player.bank_total = 0;
        player.net = 0;
        player.wager = 0;
        player.insurance_wager = 0;
        player.cards_total = 0;
        player.hands_played = 0;
        player.individual_hands = 1;
        player.name.clear();
        player.display_name = color_text(34, player.name);
        player.display_bank_total = color_text(33, round_to_string(round_wager_bank(player.bank_total)));
        player.display_net = color_text(31, round_to_string(round_wager_bank(player.net)));
        player.display_wager = color_text(31, round_to_string(round_wager_bank(player.wager)));
        player.display_insurance_wager = color_text(31, round_to_string(round_wager_bank(player.insurance_wager)));
        player.display_cards_total = color_text(36, round_to_string(round_wager_bank(player.cards_total)));
        player.display_hands_played = color_text(36, round_to_string(round_wager_bank(player.hands_played)));
        player.cards.clear();
        player.hand_bank_totals.clear();
        player.hand_nets.clear();
        player.hand_wagers.clear();
        player.hand_card_totals.clear();
        player.hand_hands_played.clear();
    }
    // Add Cards to Hand Method
    Hand Add_Card_To_Hand(const Card card)
    {
        player.cards.push_back(card);
        return *this;
    }
    // Add Hand Total Method 
    Hand Add_Hand_Total()
    {
        int ace_count = 0;
        int running_hand_value = 0;
        for (const Card &current_card : player.cards)
        {
            if (check_card_parameter(current_card.card.rank, "Ace"))
            {
                ace_count += 1;
            }
            else {}
        }
        for (Card &current_card : player.cards)
        {
            if (ace_count == 1)
            {
                if (check_card_parameter(current_card.card.rank, "Ace"))
                {
                    current_card.Set_New_Value(11);
                }
                else {}
            }
            else if (ace_count > 1)
            {
                if (check_card_parameter(current_card.card.rank, "Ace"))
                {
                    current_card.Set_New_Value(1);
                }
                else {}
            }
            else {}
            running_hand_value += current_card.card.card_value;
            ace_count -= 1;
        }
        if (running_hand_value > 21)
        {
            running_hand_value = 0;
            for (Card &current_card : player.cards)
            {
                if (check_card_parameter(current_card.card.rank, "Ace"))
                {
                    current_card.Set_New_Value(1);
                    running_hand_value += current_card.card.card_value;
                }
                else if (!(check_card_parameter(current_card.card.rank, "Ace")))
                {
                    running_hand_value += current_card.card.card_value;
                }
                else {}
            }
        }
        else {}
        player.cards_total = running_hand_value;
        player.display_cards_total = color_text(36, std::to_string(player.cards_total));
        return *this;
    }
    // Set Player Name Method
    Hand Name()
    {
        std::cout << "Enter a name for this player: ";
        std::getline(std::cin, player.name); 
        player.display_name = color_text(34, player.name);
        return *this;
    }
    // Bank Deposit Method
    Hand Deposit()
    {
        float prior_bank = player.bank_total;
        while (true)
        {
            try
            {
                std::string deposit;
                std::string try_result;
                std::cout << "\n" "Please enter an amount you'd like to deposit into your bank: ";
                std::cin >> deposit; 
                try_result = float_validation(deposit);
                if (try_result == "FNNV")
                {
                    throw std::invalid_argument("\n" + color_text(31, "Invalid entry") + " of " + color_text(31, deposit) + ". Please re-enter your bank total."); 
                }
                else if (try_result == "FNV1")
                {
                    throw std::invalid_argument("\n" + color_text(31, "Invalid entry") + " of " + color_text(31, deposit) + ". Please re-enter your bank total."); 
                }
                else if (try_result == "FNV2")
                {
                    throw std::invalid_argument("\n" + color_text(31, "Negative entry") + " of " + color_text(31, deposit) + ". Please enter a positive value for a bank total."); 
                }
                else if (try_result == "Passed")
                {
                    player.bank_total = round_wager_bank(stof(deposit));
                    break;
                }
                else {}
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << e.what() << std::endl; 
            }
            if (player.bank_total > 0)
            {
                break;
            }
            else if (player.bank_total < 0)
            {
                continue;
            }
            else {}
        }
        player.display_bank_total = color_text(33, round_to_string(round_wager_bank(player.bank_total)));
        std::cout << std::endl << player.display_name << " has decided to start with: " << color_text(33, player.display_bank_total) << std::endl; 
        if (prior_bank == 0)
        {
            if (player.hands_played == 0)
            {
                player.hand_hands_played.push_back(player.hands_played);
                player.hand_wagers.push_back(player.wager);
                player.hand_nets.push_back(player.net);
                player.hand_card_totals.push_back(player.cards_total);
                player.hand_bank_totals.push_back(player.bank_total);
            }
            else if (player.hands_played > 0)
            {
                player.hands_played++;
                player.hand_hands_played.push_back(player.hands_played);
                player.hand_wagers.push_back(player.wager);
                player.hand_nets.push_back(player.net);
                player.hand_card_totals.push_back(player.cards_total);
                player.hand_bank_totals.push_back(player.bank_total);
            }
            else {}
        }
        else {}
        return *this;
    }
    // Hit Hand Method
    Hand Hit(Shoe& shoe)
    {
        Add_Card_To_Hand(shoe.Draw());
        Add_Hand_Total();
        return *this;
    }
    // Insurance Method
    Hand Insurance()
    {
        std::string insurance_choice;
        while (true)
        {
            std::cout << "Would you like to buy insurance? Insurance pays 2 : 1. (y/n): ";
            std::cin >> insurance_choice; 
            if (insurance_choice == "y")
            {
                player.chose_buy_insurance = true;
                break;
            }
            else if (insurance_choice == "n")
            {
                player.chose_buy_insurance = false;
                break;
            }
            else
            {
                std::cout << std::endl << color_text(31, "Invalid choice") + " of " + color_text(31, insurance_choice) 
                + ". Plese re-enter your insurance decision." "\n" << std::endl; 
                insurance_choice.clear();
                continue;
            }
        }
        if (player.chose_buy_insurance)
        {
            player.insurance_wager = round_wager_bank(0.5 * player.wager);
            player.display_insurance_wager = color_text(31, round_to_string(round_wager_bank(player.insurance_wager)));
            player.bank_total -= player.insurance_wager;
            player.display_bank_total = color_text(33, round_to_string(player.bank_total));
            return *this;
        }
        else if (!player.chose_buy_insurance)
        {
            return *this;
        }
        else {}
    }
    // Place Wager Method
    Hand Place_Wager()
    {
        float wager = 0;
        while (wager == 0)
        {
            while (true)
            {
                try
                {
                    std::string input_wager;
                    std::string try_result;
                    std::cout << std::endl << "Please place a wager for this hand. Current bank total: " << color_text(33, round_to_string(player.bank_total)) << ": ";
                    std::cin >> input_wager; 
                    std::cout << std::endl;
                    try_result = float_validation(input_wager);
                    if (try_result != "Passed")
                    {
                        if (try_result == "FNNV" || try_result == "FNV1")
                        {
                            std::cout << color_text(31, "Invalid Wager") + " of " + color_text(31, input_wager) + ". Please enter a number for your wager." << std::endl; 
                        }
                        else if (try_result == "FNV2")
                        {
                            std::string string_wager = round_to_string(round_wager_bank(stof(input_wager)));
                            std::cout << color_text(31, "Negative Wager") + " of " + color_text(31, string_wager) + ". Please enter a positive number for your wager." << std::endl; 
                        }
                        else {}
                    }
                    else if ((try_result == "Passed") && (stof(input_wager) > player.bank_total))
                    {
                        std::string string_wager = round_to_string(round_wager_bank(stof(input_wager)));
                        std::string string_PB = round_to_string(player.bank_total);
                        std::cout << color_text(31, "Invalid Wager") + " of " + color_text(31, string_wager) + " due to wager being larger than bank total of " + color_text(31, string_PB) + "." << std::endl; 
                    }
                    else
                    {
                        wager = round_wager_bank(stof(input_wager));
                        break;
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        player.wager = round_wager_bank(wager);
        player.display_wager = color_text(31, round_to_string(round_wager_bank(player.wager)));
        player.bank_total -= player.wager;
        player.display_bank_total = color_text(33, round_to_string(round_wager_bank(player.bank_total)));
        std::cout << player.display_name << " has wagered: " << player.display_wager << " with a current bank total of " << player.display_bank_total << std::endl; 
        return *this;
    }
    // Show Hand Method
    Hand Show_Hand(std::string option = "", const std::string dealer_show = "")
    {
        if (player.name != "Dealer")
        {
            if (option.empty())
            {
                option = "current";
                std::cout << std::endl << player.display_name << "'s " << color_text(34, option) << " hand: [";
                for (int i = 0; i < player.cards.size(); i++)
                {
                    if (i == player.cards.size() - 1)
                    {
                        std::cout << player.cards[i] << "]";
                    }
                    else
                    {
                        std::cout << player.cards[i] << " , ";
                    }
                }
                Add_Hand_Total();
                std::cout << color_text(36, " Hand Total") << ": " << player.display_cards_total << " , " << color_text(31, "Hand Wager") << ": " << player.display_wager
                << " , " << color_text(33, "Bank Total") << ": " << player.display_bank_total;
            }
            else if (!option.empty())
            {
                std::cout << std::endl << player.display_name << "'s " << color_text(34, option) << " hand: [";
                for (int i = 0; i < player.cards.size(); i++)
                {
                    if (i == player.cards.size() - 1)
                    {
                        std::cout << player.cards[i] << "]";
                    }
                    else
                    {
                        std::cout << player.cards[i] << " , ";
                    }
                }
                Add_Hand_Total();
                std::cout << color_text(36, " Hand Total") << ": " << player.display_cards_total << " , " << color_text(31, "Hand Wager") << ": " << player.display_wager 
                << " , " << color_text(33, "Bank Total") << ": " << player.display_bank_total;
            }
            else {}
        }
        else if (player.name == "Dealer")
        {
            player.display_name = color_text(31, player.name);
            player.display_cards_total = color_text(36, std::to_string(player.cards_total));
            if (option.empty())
            {
                if (dealer_show.empty())
                {
                    option = "current";
                    std::cout << std::endl << player.display_name << "'s " << color_text(31, option) << " hand: [Hidden, " << player.cards.back() << "]" << color_text(36, " Hand Total") << ": "
                    << color_text(36, std::to_string(player.cards.back().card.card_value)) << std::endl;
                }
                else if (!dealer_show.empty())
                {
                    option = "current";
                    if (dealer_show != "cards")
                    {
                        std::cout << std::endl << player.display_name << "'s " << color_text(31, option) << " hand: [";
                    }
                    else if (dealer_show == "cards")
                    {
                        std::cout << "[";
                    }
                    else {}
                    for (int i = 0; i < player.cards.size(); i++)
                    {
                        if (i == player.cards.size() - 1)
                        {
                            std::cout << player.cards[i] << "]";
                        }
                        else
                        {
                            std::cout << player.cards[i] << " , ";
                        }
                    }
                    Add_Hand_Total();
                    std::cout << color_text(36, " Hand Total") << ": " << player.display_cards_total << std::endl;
                }
                else {}
            }
            else if (!option.empty())
            {
                if (dealer_show.empty())
                {
                    std::cout << std::endl << player.display_name << "'s " << color_text(31, option) << " hand: [Hidden, " << player.cards.back() << "]" << color_text(36, " Hand Total") << ": "
                    << color_text(36, std::to_string(player.cards.back().card.card_value)) << std::endl;
                }
                else if (!dealer_show.empty())
                {
                    if (dealer_show != "cards")
                    {
                        std::cout << std::endl << player.display_name << "'s " << color_text(31, option) << " hand: [";
                    }
                    else if (dealer_show == "cards")
                    {
                        std::cout << "[";
                    }
                    else {}
                    for (int i = 0; i < player.cards.size(); i++)
                    {
                        if (i == player.cards.size() - 1)
                        {
                            std::cout << player.cards[i] << "]";
                        }
                        else
                        {
                            std::cout << player.cards[i] << " , ";
                        }
                    }
                    Add_Hand_Total();
                    std::cout << color_text(36, " Hand Total") << ": " << player.display_cards_total << std::endl;
                }
                else {}
            }
            else {}
        }
        else {}
        return *this;
    }
    // Update Bank Method
    Hand Update_Bank(const std::string choice, Hand& hand, const float wager)
    {
        float prior_bank = hand.player.bank_total;
        switch (choice[0])
        {
        case 'W':
            hand.player.bank_total += 2.0 * wager;
            hand.player.display_bank_total = color_text(33, round_to_string(hand.player.bank_total));
            hand.player.net = hand.player.bank_total - (prior_bank + hand.player.wager);
            hand.player.display_net = color_text(31, round_to_string(hand.player.net));
            return *this;
        case 'L':
            hand.player.display_bank_total = color_text(33, round_to_string(hand.player.bank_total));
            hand.player.net = hand.player.bank_total - (prior_bank + hand.player.wager);
            hand.player.display_net = color_text(31, round_to_string(hand.player.net));
            return *this;
        case 'P':
            hand.player.bank_total += wager;
            hand.player.display_bank_total = color_text(33, round_to_string(hand.player.bank_total));
            hand.player.net = hand.player.bank_total - (prior_bank + hand.player.wager);
            hand.player.display_net = color_text(31, round_to_string(hand.player.net));
            return *this;
        case 'B':
            hand.player.bank_total += wager + 1.5 * wager;
            hand.player.display_bank_total = color_text(33, round_to_string(hand.player.bank_total));
            hand.player.net = hand.player.bank_total - (prior_bank + hand.player.wager);
            hand.player.display_net = color_text(31, round_to_string(hand.player.net));
            return *this;
        case 'I':
            hand.player.bank_total += 3.0 * wager;
            hand.player.display_bank_total = color_text(33, round_to_string(hand.player.bank_total));
            hand.player.net = hand.player.bank_total - (prior_bank + hand.player.wager);
            hand.player.display_net = color_text(31, round_to_string(hand.player.net));
            return *this;
        default:
            hand.player.bank_total += wager;
            hand.player.display_bank_total = color_text(33, round_to_string(hand.player.bank_total));
            hand.player.net = hand.player.bank_total - (prior_bank + hand.player.wager);
            hand.player.display_net = color_text(31, round_to_string(hand.player.net));
            return *this;
        }
    }
    // Copy Variables Method 
    Hand Copy_Variables(Hand& hand)
    {
        player.has_hit = hand.player.has_hit;
        player.name = hand.player.name;
        player.display_name = hand.player.display_name;
        player.bank_total = hand.player.bank_total;
        player.display_bank_total = hand.player.display_bank_total;
        player.wager = hand.player.wager;
        player.display_wager = hand.player.display_wager;
        player.hands_played = hand.player.hands_played;
        return *this;
    }
    // Reset Public Variables Method
    Hand Reset(std::string choice) 
    {
        if (choice == "HandOver") 
        {
            this->player.can_buy_insurance = false;
            this->player.can_buy_insurance = false;
            this->player.can_double_down = false;
            this->player.can_split_hand = false;
            this->player.chose_buy_insurance = false;
            this->player.chose_split_aces = false;
            this->player.chose_split_hand = false;
            this->player.has_hit = false;
            this->player.split_decision = false;
            this->player.net = 0;
            this->player.wager = 0;
            this->player.insurance_wager = 0;
            this->player.cards_total = 0;
            this->player.individual_hands = 1;
            this->player.display_bank_total.clear();
            this->player.display_net.clear();
            this->player.display_wager.clear();
            this->player.display_cards_total.clear();
            this->player.display_hands_played.clear();
            this->player.cards.clear();
        }
        else {}
        return *this;
    }
};
// ---- ---- ---- ---- ---- ---- ---- ---- ---- Class Dependent Methods ---- ---- ---- ---- ---- ---- ---- ---- //
/*
* These methods require classes, structs, and their public variables in order to operate
*/
// Check Parameter In Hand Method - check_parameter_in_hand
/*
* This method checks for if a parameter is present in a players hand
* This method takes in three input parameters, A Hand object hand, a string object parameter, and another string object checking_parameter
* This method returns a boolean value for if the parameter that is being checked for is present or not
*   - FuncInput(1): hand - Hand, this is the hand object that is being checked for a specific parameter
*   - FuncInput(2): parameter - String, this is the parameter that is being sought out e.g. A Rank or Suit
*       - 'R': The user is checking for a specific rank of a card
*       - 'S': The user is checking for a specific suit of a card
*   - FuncInput(3): checking_parameter - String, this is the specific rank or suit that a user is checking for
*   - FuncOutput: result - Boolean, this is the boolean value that represents if there is a specific parameter present in a hand
*/
bool check_parameter_in_hand(Hand& hand, const std::string parameter, const std::string checking_parameter)
{
    bool result = false;
    for (Card card : hand.player.cards)
    {
        if (parameter == "R")
        {
            if (check_card_parameter(card.card.rank, checking_parameter))
            {
                result = true;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (parameter == "S")
        {
            if (check_card_parameter(card.card.suit, checking_parameter))
            {
                result = true;
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {   
            std::cout << std::endl << color_text(31, "Invalid Parameter") + ". Please select either rank or suit to check." << std::endl; 
        }
    }
    return result;
}
// Check Same Parameter In Hand Method - check_same_parameter_in_hand
/*
* This method determines if there is the same parameter present in a hand (Rank or Suit)
* This method takes in three parameters as input, A Hand object, a string, and an optional string
* This method returns a boolean value for if the check is true or false
*   - FuncInput(1): hand - Hand, this is the hand object that is fed into the function to check for a parameter type
*   - FuncInput(2): parameter - String, this is the string that is fed into the function to determine what is to be checked
*       - 'R' - When set to R, this function will check for there being the same rank in a hand
*       - 'S' - When set to S, this function will check for there being the same suit in a hand
*   - FuncInput(3): checking_parameter - String, optional parameter that may be checked for e.g. An Ace rank or a Clubs suit
*   - FuncOutput: result - Boolean, this boolean value tells the computer if the check is true or false
*/
bool check_same_parameter_in_hand(Hand& hand, const std::string parameter, const std::string checking_parameter = "")
{
    bool result = true;
    std::vector<Card> one_onward(hand.player.cards.begin() + 1, hand.player.cards.end());
    for (Card card : one_onward)
    {
        if (parameter == "R")
        {
            if (!check_card_parameter(card.card.rank, hand.player.cards.at(0).card.rank) || (!checking_parameter.empty() && !check_card_parameter(card.card.rank, checking_parameter)))
            {
                result = false;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (parameter == "S")
        {
            if (!check_card_parameter(card.card.suit, hand.player.cards.at(0).card.suit) || (!checking_parameter.empty()) && !check_card_parameter(card.card.suit, checking_parameter))
            {
                result = false;
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            std::cout << std::endl << color_text(31, "Invalid Parameter") + ". Please select either rank or suit to check." << std::endl; 
        }
    }
    return result;
}
// Check For Blackjack Method - check_blackjack
/*
* This method checks for if there is a Blackjack present in a players hand
* This method takes in a Hand object as an input and returns a boolean value in return
*   - FuncInput(1): hand - Hand, the hand that is being checked for if there is a Blackjack
*   - FuncOutput: result - Boolean, the boolean value that tells the user if a Blackjack is present
*/
bool check_blackjack(Hand& hand)
{
    bool result = false;
    for (Card card : hand.player.cards)
    {
        if (card.card.card_value == 10)
        {
            if (check_parameter_in_hand(hand, "R", "Ace"))
            {
                result = true;
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }
    return result;
}
// Update Game Statistics Method - update_stats
/*
* This method updates the game statistics for a player
* This method takes in a Hand object as an input and returns a hand object
*   - FuncInput(1): hand - Hand, this is the hand object that is being modified
*       - The following vectors are having values appended to them
*           - player.hand_bank_totals
*           - player.hand_wagers
*           - player.hand_nets
*           - player.hand_card_totals
*           - player.hand_hands_played
*   - FuncOutput: Hand - Hand, hand object that possesses all the attributes of a regular hand object
* This method should be implemented in the hand_comparison method
*/
Hand update_stats(Hand& hand)
{
    hand.player.hands_played += 1;
    hand.player.hand_hands_played.push_back(hand.player.hands_played);
    hand.player.hand_wagers.push_back(hand.player.wager);
    hand.player.hand_nets.push_back(hand.player.net);
    hand.player.hand_card_totals.push_back(hand.player.cards_total);
    hand.player.hand_bank_totals.push_back(hand.player.bank_total);
    return hand;
}
// Create CSV Statistics File Method - csv_stats
/*
* This method is designed to create a csv file that contains all of the trackable statistics in a Blackjack game
* This method creates a CSV File for the following statistics 
*   - Hand Number: This is the hand number that a player played
*   - Wager: This is the wager that is placed on a specific hand
*   - Net: This is the net profit / loss for a hand of a player
*   - Cards Total: This is the final hand value for a hand of a player
*   - Updated Bank: This is the updated bank total after a hand has finished for a player
* This method takes in a hand object and returns no value, but creates a CSV file
*   FuncInput(1): hand - Hand, this is the hand object that will have the statistics of the game tracked an made into a csv file
*/
void csv_stats(Hand& hand)
{
    std::string csvFileName = hand.player.name + " Results.csv";
    std::ofstream file(csvFileName);
    if (file)
    {
        file << "Hand Number, Wager, Net, Cards Total, Updated Bank" << std::endl;
        for (int i = 0; i < hand.player.hand_hands_played.size(); i++)
        {
            file << hand.player.hand_hands_played.at(i) << "," << hand.player.hand_wagers.at(i) << "," << hand.player.hand_nets.at(i)
            << "," << hand.player.hand_card_totals.at(i) << "," << hand.player.hand_bank_totals.at(i) << std::endl;
        }
        file.close();
        std::cout << "CSV File Created: " << csvFileName << std::endl; 
    }
    else if (!file)
    {
        std::cout << "Error creating CSV File: " << csvFileName << std::endl; 
    }
    else {}
}
// Special Options Method - special_options
Hand special_options(Hand& playerHand, Hand& dealerHand, bool override)
{
    override = false;
    if (playerHand.player.bank_total >= 0.5 * playerHand.player.wager) 
    {
        if (check_card_parameter(dealerHand.player.cards.back().card.rank, "Ace")) 
        {
            playerHand.player.can_buy_insurance = true;
        }
        else if (!check_card_parameter(dealerHand.player.cards.back().card.rank, "Ace"))
        {
            playerHand.player.can_buy_insurance = false;
        }
        else {}
        if (playerHand.player.bank_total >= playerHand.player.wager) 
        {
            playerHand.player.can_double_down = true;
            if (check_same_parameter_in_hand(playerHand,"R")) {
                if (!override)
                {
                    playerHand.player.can_split_hand = true;
                }
                else if (override) {
                    playerHand.player.can_split_hand = false;
                }
                else {}
            }
            else if (!check_same_parameter_in_hand(playerHand,"R")) {
                playerHand.player.can_split_hand = false;
            }
            else {}
        }
        else if (playerHand.player.bank_total < playerHand.player.wager) 
        {
            playerHand.player.can_double_down = false;
            playerHand.player.can_split_hand = false;
        }
        else {}
    }
    else if (playerHand.player.bank_total < 0.5 * playerHand.player.wager) {
        playerHand.player.can_buy_insurance = false;
        playerHand.player.can_double_down = false;
        playerHand.player.can_split_hand = false;
    }
    else {}
    return playerHand;
}
// Deal Hand To Players Method - deal_hand
/*
* This method deals the hands to players
* This method also checks if a player can double down, split their hand, and buy insurance
* This method takes in three separate parameters for inputs and returns the modified objects
*   - FuncInput(1): playerHand - Hand, this is the hand object for a user
*   - FuncInput(2): dealerHand - Hand, this is the hand object for a dealer
*   - FuncInput(3): shoe - Shoe, this is the shoe object that is being used for the game
*   - FuncOutput(1): playerHand - Hand, modified user hand object
*   - FuncOutput(2): dealerHand - Hand, modified dealer hand object
*   - FuncOutput(3): shoe - Shoe, modified shoe object being used in game
*/
std::tuple<Hand, Hand, Shoe> deal_hand(Hand& playerHand, Hand& dealerHand, Shoe& shoe)
{
    playerHand.Place_Wager();
    for (int i = 0; i < 4; i++)
    {
        if (i % 2 == 0)
        {
            playerHand.Hit(shoe);
        }
        else if (i % 2 == 1)
        {
            dealerHand.Hit(shoe);
        }
        else {}
    }
    std::cout << std::endl << "Here are the initial hands of each player: " << std::endl; 
    playerHand.Show_Hand("initial");
    dealerHand.Show_Hand("initial","");
    special_options(playerHand, dealerHand, false);
    return std::make_tuple(playerHand, dealerHand, shoe);
}
// Blackjack Strategy Method - blackjack_strategy
/*
* This method tells the user what they should do depending on Blackjack strategy
* This method uses the strategy outlined in the Assets folder of this projects version home directory
* This method takes in two Hand objects for input parameters and a boolean value for an over ride, it does not return a value
*   - FuncInput(1): playerHand - Hand, hand object for the user
*   - FuncInput(2): dealerHand - Hand, hand object that represents the dealer
*   - FuncInput(3): override - Boolean, this is a boolean value that will over ride a players ability to be recommended to split a hand
*       - This is only set to true if we are examining a hand that has already been split
*/
void blackjack_strategy(Hand& playerHand, Hand& dealerHand, bool override)
{
    std::string BlackJack = color_text(32, "Blackjack");
    std::string ShouldDD = color_text(31, "double down");
    std::string ShouldHit = color_text(31, "hit");
    std::string ShouldStand = color_text(31, "stand");
    std::string ShouldSplit = color_text(31, "split");
    special_options(playerHand, dealerHand, override);
    if (playerHand.player.cards.size() == 2 && (check_parameter_in_hand(playerHand, "R", "Ace") || check_same_parameter_in_hand(playerHand, "R")) && !check_blackjack(playerHand))
    {
        if (check_parameter_in_hand(playerHand, "R", "Ace") && (check_parameter_in_hand(playerHand, "R", "2") || check_parameter_in_hand(playerHand, "R", "3")))
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
            case 3:
            case 4:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            case 5:
            case 6:
                if (playerHand.player.can_double_down && !playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldHit << "." << std::endl;
                }
                else if (!playerHand.player.can_double_down || playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggess " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                }
                else {}
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand, "R", "Ace") && (check_parameter_in_hand(playerHand, "R", "4") || check_parameter_in_hand(playerHand, "R", "5")))
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            case 4:
            case 5:
            case 6:
                if (playerHand.player.can_double_down && !playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldHit << "." << std::endl;
                }
                else if (!playerHand.player.can_double_down || playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                }
                else {}
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand, "R", "Ace") && check_parameter_in_hand(playerHand, "R", "6"))
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                if (playerHand.player.can_double_down && !playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldHit << "." << std::endl;
                }
                else if (!playerHand.player.can_double_down || playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                }
                else {}
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand, "R", "Ace") && check_parameter_in_hand(playerHand, "R", "7"))
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                if (playerHand.player.can_double_down && !playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldStand << "." << std::endl;
                }
                else if (!playerHand.player.can_double_down || playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                }
                else {}
                break;
            case 7:
            case 8:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                break;
            case 9:
            case 10:
            case 11:
            case 1:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand, "R", "Ace") && (check_parameter_in_hand(playerHand, "R", "8") || check_parameter_in_hand(playerHand, "R", "9")))
        {
            std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
        }
        else {}
        if (check_same_parameter_in_hand(playerHand, "R"))
        {
            if (check_parameter_in_hand(playerHand, "R", "2") || check_parameter_in_hand(playerHand, "R", "3"))
            {
                switch (dealerHand.player.cards[1].card.card_value)
                {
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    if (playerHand.player.can_split_hand && (!playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                    {
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << " or " << ShouldHit << "." << std::endl;
                    }
                    else if (!playerHand.player.can_split_hand || (playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                    {
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                    }
                    else {}
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                case 1:
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                    break;
                default:
                    break;
                }
            }
            else if (check_parameter_in_hand(playerHand, "R", "4"))
            {
                switch (dealerHand.player.cards[1].card.card_value)
                {
                case 2:
                case 3:
                case 4:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 1:
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                    break;
                case 5:
                case 6:
                    if (playerHand.player.can_split_hand && (!playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                    {
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << " or " << ShouldHit << "." << std::endl;
                    }
                    else if (!playerHand.player.can_split_hand || (playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                    {
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                    }
                    else {}
                    break;
                default:
                    break;
                }
            }
            else if (check_parameter_in_hand(playerHand, "R", "5"))
            {
                switch (dealerHand.player.cards[1].card.card_value)
                {
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    if (playerHand.player.can_double_down && !playerHand.player.has_hit)
                    {
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldHit << "." << std::endl;
                    }
                    else if (!playerHand.player.can_double_down) 
                    {
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                    }
                    break;
                case 10:
                case 11:
                case 1:
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                    break;
                default:
                    break;
                }
            }
            else if (check_parameter_in_hand(playerHand, "R", "6"))
            {
                if (playerHand.player.can_split_hand && (!playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    switch (dealerHand.player.cards[1].card.card_value)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << "." << std::endl;
                        break;
                    case 7:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << " or " << ShouldStand << "." << std::endl;
                        break;
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                        break;
                    default:
                        break;
                    }
                }
                else if (!playerHand.player.can_split_hand || (playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    switch (dealerHand.player.cards[1].card.card_value)
                    {
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                        break;
                    case 4:
                    case 5:
                    case 6:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                        break;
                    default:
                        break;
                    }
                }
                else {}
            }
            else if (check_parameter_in_hand(playerHand, "R", "7"))
            {
                if (playerHand.player.can_split_hand && (!playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    switch (dealerHand.player.cards[1].card.card_value)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << "." << std::endl;
                        break;
                    case 8:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << " or " << ShouldHit << "." << std::endl;
                        break;
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                        break;
                    default:
                        break;
                    }
                }
                else if (!playerHand.player.can_split_hand || (playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    switch (dealerHand.player.cards[1].card.card_value)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                        break;
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                        break;
                    default:
                        break;
                    }
                }
                else {}
            }
            else if (check_parameter_in_hand(playerHand, "R", "8"))
            {
                if (playerHand.player.can_split_hand && (!playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << "." << std::endl;
                }
                else if (!playerHand.player.can_split_hand || (playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    switch (dealerHand.player.cards[1].card.card_value)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                        break;
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                        break;
                    default:
                        break;
                    }
                }
                else {}
            }
            else if (check_parameter_in_hand(playerHand, "R", "9"))
            {
                if (playerHand.player.can_split_hand && (!playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    switch (dealerHand.player.cards[1].card.card_value)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 8:
                    case 9:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << "." << std::endl;
                        break;
                    case 7:
                    case 10:
                    case 11:
                    case 1:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                        break;
                    default:
                        break;
                    }
                }
                else if (!playerHand.player.can_split_hand || (playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                }
                else {}
            }
            else if (playerHand.player.cards_total == 20)
            {
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
            }
            else if (check_parameter_in_hand(playerHand, "R", "Ace"))
            {
                if (playerHand.player.can_split_hand && (!playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldSplit << "." << std::endl;
                }
                else if (!playerHand.player.can_split_hand || (playerHand.player.split_decision && !playerHand.player.chose_split_hand))
                {
                    switch (dealerHand.player.cards[1].card.card_value)
                    {
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                        break;
                    case 4:
                    case 5:
                    case 6:
                        std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                        break;
                    default:
                        break;
                    }
                }
                else {}
            }
            else {}
        }
        else {}
    }
    else if (playerHand.player.cards.size() >= 2)
    {
        if (playerHand.player.cards_total >= 4 && playerHand.player.cards_total <= 8)
        {
            std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
        }
        else if (playerHand.player.cards_total == 9)
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                if (playerHand.player.cards.size() == 2 && playerHand.player.can_double_down && !playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldHit << "." << std::endl;
                }
                else if (playerHand.player.cards.size() > 2 || !playerHand.player.can_double_down || playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                }
                else {}
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            default:
                break;
            }
        }
        else if (playerHand.player.cards_total == 10)
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                if (playerHand.player.cards.size() == 2 && playerHand.player.can_double_down && !playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldHit << "." << std::endl;
                }
                else if (playerHand.player.cards.size() > 2 || !playerHand.player.can_double_down || playerHand.player.has_hit)
                {
                    std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                }
                else {}
                break;
            case 10:
            case (11):
            case (1):
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            default:
                break;
            }
        }
        else if (playerHand.player.cards_total == 11)
        {
            if (playerHand.player.cards.size() == 2 && playerHand.player.can_double_down && !playerHand.player.has_hit)
            {
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldDD << " or " << ShouldHit << "." << std::endl;
            }
            else if (playerHand.player.cards.size() >= 2 || !playerHand.player.can_double_down || playerHand.player.has_hit)
            {
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
            }
            else {}
        }
        else if (playerHand.player.cards_total == 12)
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            case 4:
            case 5:
            case 6:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                break;
            default:
                break;
            }
        }
        else if (playerHand.player.cards_total == 13 || playerHand.player.cards_total == 14 || playerHand.player.cards_total == 15 || playerHand.player.cards_total == 16)
        {
            switch (dealerHand.player.cards[1].card.card_value)
            {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldHit << "." << std::endl;
                break;
            default:
                break;
            }
        }
        else if (playerHand.player.cards_total == 17 || playerHand.player.cards_total == 18 || playerHand.player.cards_total == 19 || playerHand.player.cards_total == 20)
        {
            std::cout << std::endl << BlackJack << " strategy suggests " << playerHand.player.display_name << " should " << ShouldStand << "." << std::endl;
        }
        else {}
    }
    else {
        std::cout << std::endl << "Fuck" << std::endl;
    }
    
}
// Check For Face Up Ace of Dealer Method - dealer_showing_ace
/*
* This method checks if the dealer has an Ace as a face up card
* This method takes in three parameters for input and returns four parameters as an output
*   - FuncInput(1): playerHand - Hand, this is a Hand object that represents the user
*   - FuncInput(2): dealerHand - Hand, this is a Hand object that represents the dealer
*   - FuncInput(3): shoe - Shoe, this is a Shoe object that represents the game shoe
*   - FuncOutput(1): playerHand - Hand, this is the modified Hand object for the user
*   - FuncOutput(2): dealerhand - Hand, this is the modified Hand object for the dealer
*   - FuncOutput(3): shoe - Hand, this is the modified Shoe object that represents the game shoe
*   - FuncOutput(4): hand_continue - Boolean, this is the boolean value that dictates if the hand is supposed to continue after this method
*/
std::tuple<Hand, Hand, Shoe, bool> dealer_showing_ace(Hand& playerHand, Hand& dealerHand, Shoe& shoe)
{
    float prior_bank_total = playerHand.player.bank_total;
    deal_hand(playerHand, dealerHand, shoe);
    bool hand_continue = true;
    if (check_card_parameter(dealerHand.player.cards.at(1).card.rank, "Ace"))
    {
        if (playerHand.player.can_buy_insurance)
        {
            std::cout << std::endl << "The " << dealerHand.player.display_name << " is showing an " << dealerHand.player.cards.at(1).display_rank << ". "; 
            playerHand.Insurance();
            if (playerHand.player.chose_buy_insurance)
            {
                std::cout << std::endl << playerHand.player.display_name << " has chosen to buy insurance. Your insurance wager" << " is " << playerHand.player.display_insurance_wager << "." << std::endl; 
                if (check_blackjack(dealerHand) && check_blackjack(playerHand))
                {
                    hand_continue = false;
                    std::cout << std::endl << "Both players have blackjack. " << playerHand.player.display_name << " wins insurance and pushes their original wager. ";
                    playerHand.Update_Bank("P", playerHand, playerHand.player.wager);
                    playerHand.Update_Bank("I", playerHand, playerHand.player.insurance_wager);
                    std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                    std::cout << "Here are the final hands of the players:" << std::endl; 
                    playerHand.Show_Hand("final");
                    dealerHand.Show_Hand("final", "Show");
                    update_stats(playerHand);
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand)))
                {
                    hand_continue = false;
                    std::cout << std::endl << dealerHand.player.display_name << " has blackjack but " << playerHand.player.display_name << " does not. " << playerHand.player.display_name 
                    << " wins insurance but loses their original wager. ";
                    playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
                    playerHand.Update_Bank("I", playerHand, playerHand.player.insurance_wager);
                    std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                    std::cout << "Here are the final hands of the players:" << std::endl; 
                    playerHand.Show_Hand("final");
                    dealerHand.Show_Hand("final", "Show");
                    update_stats(playerHand);
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand)))
                {
                    hand_continue = false;
                    std::cout << std::endl << playerHand.player.display_name << " has blackjack and " << dealerHand.player.display_name << " does not. " << playerHand.player.display_name 
                    << " loses insurance but wins their original wager. ";
                    playerHand.Update_Bank("B", playerHand, playerHand.player.wager);
                    playerHand.Update_Bank("L", playerHand, playerHand.player.insurance_wager);
                    std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl ; 
                    std::cout << "Here are the final hands of the players:" << std::endl; 
                    playerHand.Show_Hand("final");
                    dealerHand.Show_Hand("final", "Show");
                    update_stats(playerHand);
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand)))
                {
                    hand_continue = true;
                    playerHand.Update_Bank("L", playerHand, playerHand.player.insurance_wager);
                    std::cout << std::endl << "Neither player has blackjack. " << playerHand.player.display_name << " loses their insurance wager. The hand will continue." << std::endl << std::endl; ; 
                    std::cout << "Here are the current hands of each player:" << std::endl; 
                    playerHand.Show_Hand("initial");
                    dealerHand.Show_Hand("initial");
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else {}
            }
            else if (!playerHand.player.chose_buy_insurance)
            {
                std::cout << std::endl << playerHand.player.display_name << " has chosen to not buy insurance." << std::endl; 
                if (check_blackjack(dealerHand) && check_blackjack(playerHand))
                {
                    hand_continue = false;
                    std::cout << std::endl << "Both players have blackjack. " << playerHand.player.display_name << " pushes their original wager. ";
                    playerHand.Update_Bank("P", playerHand, playerHand.player.wager);
                    std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                    std::cout << "Here are the final hands of the players:" << std::endl; 
                    playerHand.Show_Hand("final");
                    dealerHand.Show_Hand("final", "Show");
                    update_stats(playerHand);
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand)))
                {
                    hand_continue = false;
                    std::cout << std::endl << dealerHand.player.display_name << " has blackjack but " << playerHand.player.display_name << " does not. " 
                    << playerHand.player.display_name << " loses their original wager. ";
                    playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
                    std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                    std::cout << "Here are the final hands of the players:" << std::endl; 
                    playerHand.Show_Hand("final");
                    dealerHand.Show_Hand("final", "Show");
                    update_stats(playerHand);
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand)))
                {
                    hand_continue = false;
                    std::cout << std::endl << playerHand.player.display_name << " has blackjack and " << dealerHand.player.display_name << " does not. " << playerHand.player.display_name 
                    << " wins their original wager. ";
                    playerHand.Update_Bank("B", playerHand, playerHand.player.wager);
                    std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                    std::cout << "Here are the final hands of the players:" << std::endl; 
                    playerHand.Show_Hand("final");
                    dealerHand.Show_Hand("final", "Show");
                    update_stats(playerHand);
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand)))
                {
                    hand_continue = true;
                    std::cout << std::endl << "Neither player has blackjack. The hand will continue." << std::endl << std::endl; 
                    std::cout << "Here are the current hands of each player:" << std::endl; 
                    playerHand.Show_Hand("initial");
                    dealerHand.Show_Hand("initial");
                    return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
                }
                else {}
            }
        }
        else if (!playerHand.player.can_buy_insurance)
        {
            std::cout << std::endl << "The " << dealerHand.player.display_name << " is showing an " << dealerHand.player.cards.at(1).display_rank << ". But " << playerHand.player.display_name
            << " does not have enough currency in their bank to purchase insurance." << std::endl; 
            if (check_blackjack(dealerHand) && check_blackjack(playerHand))
            {
                hand_continue = false;
                std::cout << std::endl << "Both players have blackjack. " << playerHand.player.display_name << " pushes their original wager."; 
                playerHand.Update_Bank("P", playerHand, playerHand.player.wager);
                std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                std::cout << "Here are the final hands of the players:" << std::endl; 
                playerHand.Show_Hand("final");
                dealerHand.Show_Hand("final", "Show");
                update_stats(playerHand);
                return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
            }
            else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand)))
            {
                hand_continue = false;
                std::cout << std::endl << dealerHand.player.display_name << " has blackjack but " << playerHand.player.display_name << " does not. " 
                << playerHand.player.display_name << " loses their original wager.";
                playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
                std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                std::cout << "Here are the final hands of the players:" << std::endl; 
                playerHand.Show_Hand("final");
                dealerHand.Show_Hand("final", "Show");
                update_stats(playerHand);
                return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
            }
            else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand)))
            {
                hand_continue = false;
                std::cout << std::endl << playerHand.player.display_name << " has blackjack and " << dealerHand.player.display_name << " does not. " 
                << playerHand.player.display_name << " wins their original wager. ";
                playerHand.Update_Bank("B", playerHand, playerHand.player.wager);
                std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
                std::cout << "Here are the final hands of the players:" << std::endl; 
                playerHand.Show_Hand("final");
                dealerHand.Show_Hand("final", "Show");
                update_stats(playerHand);
                return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
            }
            else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand)))
            {
                hand_continue = true;
                return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
            }
            else {}
        }
    }
    else if (!check_card_parameter(dealerHand.player.cards.at(1).card.rank, "Ace"))
    {
        if (check_blackjack(dealerHand) && check_blackjack(playerHand))
        {
            hand_continue = false;
            std::cout << std::endl << "Both players have blackjack. " << playerHand.player.display_name << " pushes their original wager. ";
            playerHand.Update_Bank("P", playerHand, playerHand.player.wager);
            std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
            std::cout << "Here are the final hands of the players:" << std::endl; 
            playerHand.Show_Hand("final");
            dealerHand.Show_Hand("final", "Show");
            update_stats(playerHand);
            return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
        }
        else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand)))
        {
            hand_continue = false;
            std::cout << std::endl << dealerHand.player.display_name << " has blackjack but " << playerHand.player.display_name << " does not. " 
            << playerHand.player.display_name << " loses their original wager. ";
            playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
            std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
            std::cout << "Here are the final hands of the players:" << std::endl; 
            playerHand.Show_Hand("final");
            dealerHand.Show_Hand("final", "Show");
            update_stats(playerHand);
            return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
        }
        else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand)))
        {
            hand_continue = false;
            std::cout << std::endl << playerHand.player.display_name << " has blackjack and " << dealerHand.player.display_name << " does not. " 
            << playerHand.player.display_name << " wins their original wager. ";
            playerHand.Update_Bank("B", playerHand, playerHand.player.wager);
            std::cout << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl << std::endl; 
            std::cout << "Here are the final hands of the players:" << std::endl; 
            playerHand.Show_Hand("final");
            dealerHand.Show_Hand("final", "Show");
            update_stats(playerHand);
            return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
        }
        else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand)))
        {
            hand_continue = true;
            return std::make_tuple(playerHand, dealerHand, shoe, hand_continue);
        }
        else {}
    }
    else {}
}
// Split Hand Method - split_hand
/*
* This method splits the hand of a user
* This method takes in one input, a Hand object, and returns a vector of hands
*   - FuncInput(1): inputHand - Hand, this is the hand object that is fed into the method to be split
*   - FuncOutput(1): hands - Vector, this is the vector of hands that is created after the original hand is split
*/
std::vector<Hand> split_hand(Hand& inputHand)
{
    std::vector<Hand> hands;
    inputHand.player.bank_total -= inputHand.player.wager;
    inputHand.player.display_bank_total = color_text(33, round_to_string(inputHand.player.bank_total));
    for (Card card : inputHand.player.cards)
    {
        Hand current_hand;
        current_hand.player.cards.push_back(card);
        hands.push_back(current_hand);
    }
    for (Hand& current_hand : hands) {
        current_hand.Copy_Variables(inputHand);
    }
    return hands;
}
// Player Same Rank Method - player_same_rank
/*
* This method determines if a player has the same rank of a card in their hand
* This method takes in two hands and a shoe as an input and returns a vector of hands, two modified hands, a modified shoe, and an integer
*   - FuncInput(1): playerHand - Hand, this is the original player hand that is fed into the method to check if a player has duplicate ranks
*   - FuncInput(2): dealerHand - Hand, this is the original dealer hand that is fed into the method
*   - FuncInput(3): shoe - Shoe, this is shoe that is being played with
*   - FuncOutput(1): new_hand - Vector, this is a vector of hands that is returned after the logical process of this method
*   - FuncOutput(2): playerHand - Hand, this is the modified hand object of the original players hand
*   - FuncOutput(3): dealerHand - Hand, this is the modified hand object of the original dealer hand
*   - FuncOutput(4): shoe - Shoe, this is the modified shoe object of the shoe that is being played with
*   - FuncOutput(5): hand_count - Integer, this is an integer value that tells the computer how many hands a player ends up with after this method
*/
std::tuple<std::vector<Hand>, Hand, Hand, Shoe, int> player_same_rank(Hand& playerHand, Hand& dealerHand, Shoe& shoe)
{
    int hand_count = 1;
    std::vector<Hand> new_hand;
    if (playerHand.player.can_split_hand)
    {
        if (check_same_parameter_in_hand(playerHand, "R", "Ace"))
        {
            std::string aces_response;
            while (aces_response.empty())
            {
                std::cout << std::endl << "You have the same rank of " << playerHand.player.cards[0].display_rank << " in your hand." << std::endl; 
                std::cout << std::endl << "Would you like to split your hand? You may only split your hand once." << std::endl; 
                blackjack_strategy(playerHand, dealerHand, false);
                std::cout << std::endl << "Enter (y) for yes and (n) for no: ";
                std::cin >> aces_response;
                std::cout << std::endl; 
                if (aces_response == "y")
                {
                    playerHand.player.chose_split_aces = true;
                    playerHand.player.split_decision = true;
                    std::cout << playerHand.player.display_name << " has chosen to split their " << playerHand.player.cards[0].display_rank << "'s." << std::endl; 
                    std::cout << std::endl << "Here are the current hands of both players: " << std::endl; 
                    std::vector<Hand> split_aces = split_hand(playerHand);
                    Hand player_hand_1 = split_aces.at(0);
                    Hand player_hand_2 = split_aces.at(1);
                    player_hand_1.Hit(shoe);
                    player_hand_2.Hit(shoe);
                    new_hand.push_back(player_hand_1);
                    new_hand.push_back(player_hand_2);
                    hand_count = 2;
                    int loop_counter = 1;
                    std::string hand_tracker;
                    for (Hand& current_hand : new_hand)
                    {
                        if (loop_counter == 1)
                        {
                            hand_tracker = "first";
                        }
                        else if (loop_counter == 2)
                        {
                            hand_tracker = "second";
                        }
                        else {}
                        current_hand.Show_Hand(hand_tracker);
                        loop_counter++;
                    }
                    dealerHand.Show_Hand();
                    playerHand.Copy_Variables(new_hand.back());
                    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                }
                else if (aces_response == "n")
                {
                    playerHand.player.chose_split_aces = false;
                    playerHand.player.split_decision = true;
                    std::cout << playerHand.player.display_name << " has chosen not to split their " << playerHand.player.cards[0].display_rank << "'s." << std::endl; 
                    new_hand.push_back(playerHand);
                    playerHand.Copy_Variables(new_hand.back());
                    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                }
                else
                {
                    std::cout << color_text(31, "Invalid choice") + " of " + color_text(31, aces_response) + ". Plese re-enter your decision." << std::endl << std::endl; 
                    aces_response.clear();
                }
            }
        }
        else if (check_same_parameter_in_hand(playerHand, "R") && !check_card_parameter(playerHand.player.cards[0].card.rank, "Ace"))
        {
            std::string same_rank_response;
            while (same_rank_response.empty())
            {
                std::cout << std::endl << "You have the same rank of " << playerHand.player.cards[0].display_rank << " in your hand." << std::endl; 
                std::cout << std::endl << "Would you like to split your hand? You may split up to a total of four times." << std::endl; 
                blackjack_strategy(playerHand, dealerHand, false);
                std::cout << std::endl << "Enter (y) for yes and (n) for no: ";
                std::cin >> same_rank_response;
                if (same_rank_response == "y")
                {
                    playerHand.player.chose_split_hand = true;
                    playerHand.player.split_decision = true;
                    std::cout << std::endl << playerHand.player.display_name << " has chosen to split their hand." << std::endl; 
                    int split_counter = 1;
                    hand_count++;
                    std::vector<Hand> initial_split = split_hand(playerHand);
                    std::vector<Hand> split_hands;
                    std::vector<Hand> temp_hands;
                    Hand player_hand_1 = initial_split.at(0);
                    Hand player_hand_2 = initial_split.at(1);
                    player_hand_2.Hit(shoe);
                    temp_hands.push_back(player_hand_2);
                    temp_hands.push_back(player_hand_1);
                    Hand checking_hand;
                    checking_hand = player_hand_2;
                    checking_hand.Copy_Variables(player_hand_2);
                    special_options(checking_hand, dealerHand, false);
                    if (check_same_parameter_in_hand(checking_hand, "R"))
                    {
                        if (checking_hand.player.can_split_hand)
                        {
                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
                            int loop_counter = 1;
                            std::string hand_tracker;
                            for (Hand& current_hand : temp_hands)
                            {
                                if (loop_counter == 1)
                                {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2)
                                {
                                    hand_tracker = "second";
                                }
                                else {}
                                current_hand.Show_Hand(hand_tracker);
                                loop_counter++;
                            }
                            temp_hands.clear();
                            while (split_counter < 4 && checking_hand.player.can_split_hand)
                            {
                                std::string split_again;
                                while (split_again != "y" || split_again != "n")
                                {
                                    std::cout << std::endl << std::endl << "You have pulled the same rank of " << checking_hand.player.cards[0].display_rank 
                                    << " again." << std::endl; 
                                    std::cout << std::endl << "Would you like to split your current hand again?" << std::endl; 
                                    blackjack_strategy(checking_hand, dealerHand, false);
                                    std::cout << std::endl << "Enter (y) for yes and (n) for no: ";
                                    std::cin >> split_again;
                                    std::cout << std::endl;
                                    if (split_again == "y")
                                    {
                                        split_counter++;
                                        hand_count++;
                                        std::vector<Hand> new_split = split_hand(checking_hand);
                                        Hand new_player_hand_1 = new_split.at(0);
                                        Hand new_player_hand_2 = new_split.at(1);
                                        new_player_hand_2.Hit(shoe);
                                        split_hands.insert(split_hands.begin(), new_player_hand_1);
                                        checking_hand = new_player_hand_2;
                                        checking_hand.Copy_Variables(new_player_hand_2);
                                        special_options(checking_hand, dealerHand, false);
                                        break;
                                    }
                                    else if (split_again == "n")
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        std::cout << color_text(31, "Invalid Entry") << ". Please enter a valid choice." << std::endl; 
                                        split_again.clear();
                                    }
                                }
                                split_hands.insert(split_hands.begin(), checking_hand);
                                split_hands.insert(split_hands.end(), player_hand_1);
                                for (int i = 0; i < split_hands.size(); i++)
                                {
                                    split_hands.at(i).Copy_Variables(checking_hand);
                                }
                                if (checking_hand.player.can_split_hand && split_again == "y")
                                {
                                    if (split_counter < 4 && checking_hand.player.can_split_hand)
                                    {
                                        std::cout << playerHand.player.display_name << " has chosen to split their hand again." << std::endl; 
                                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
                                        int loop_counter = 1;
                                        std::string hand_tracker;
                                        for (Hand& current_hand : split_hands)
                                        {
                                            if (loop_counter == 1)
                                            {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2)
                                            {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3)
                                            {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4)
                                            {
                                                hand_tracker = "fourth";
                                            }
                                            else
                                            {
                                                hand_tracker = "current";
                                            }
                                            current_hand.Show_Hand(hand_tracker);
                                            loop_counter++;
                                        }
                                        split_hands.erase(split_hands.begin());
                                        split_hands.pop_back();
                                        continue;
                                    }
                                    else if (split_counter == 4 || !checking_hand.player.can_split_hand)
                                    {
                                        if (split_counter == 4)
                                        {
                                            std::cout << playerHand.player.display_name << " has reached the max amount of times to split." << std::endl; 
                                            std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
                                            int loop_counter = 1;
                                            std::string hand_tracker;
                                            for (Hand& current_hand : split_hands)
                                            {
                                                if (loop_counter == 1)
                                                {
                                                    hand_tracker = "first";
                                                }
                                                else if (loop_counter == 2)
                                                {
                                                    hand_tracker = "second";
                                                }
                                                else if (loop_counter == 3)
                                                {
                                                    hand_tracker = "third";
                                                }
                                                else if (loop_counter == 4)
                                                {
                                                    hand_tracker = "fourth";
                                                }
                                                else if (loop_counter == 5)
                                                {
                                                    hand_tracker = "fifth";
                                                }
                                                else
                                                {
                                                    hand_tracker = "current";
                                                }
                                                current_hand.Show_Hand(hand_tracker);
                                                loop_counter++;
                                            }
                                            std::cout << std::endl << std::endl;
                                        }
                                        else if (!checking_hand.player.can_split_hand)
                                        {
                                            if (checking_hand.player.bank_total < checking_hand.player.wager) 
                                            {
                                                std::cout << "Your current bank balance of " << checking_hand.player.display_bank_total << " is not greater than"
                                                << " your wager of " << checking_hand.player.display_wager << ". You can no longer split your hands. Total times split: " 
                                                << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
                                            }
                                            else {}
                                            int loop_counter = 1;
                                            std::string hand_tracker;
                                            for (Hand& current_hand : split_hands)
                                            {
                                                if (loop_counter == 1)
                                                {
                                                    hand_tracker = "first";
                                                }
                                                else if (loop_counter == 2)
                                                {
                                                    hand_tracker = "second";
                                                }
                                                else if (loop_counter == 3)
                                                {
                                                    hand_tracker = "third";
                                                }
                                                else if (loop_counter == 4)
                                                {
                                                    hand_tracker = "fourth";
                                                }
                                                else
                                                {
                                                    hand_tracker = "current";
                                                }
                                                current_hand.Show_Hand(hand_tracker);
                                                loop_counter++;
                                            }
                                            std::cout << std::endl << std::endl;
                                        }
                                        break;
                                    }
                                    else {}
                                }
                                else if (!checking_hand.player.can_split_hand || split_again == "n")
                                {
                                    if (!checking_hand.player.can_split_hand)
                                    {
                                        if (checking_hand.player.bank_total < checking_hand.player.wager) {
                                            std::cout << "You pulled the same rank of " << checking_hand.player.cards[0].display_rank << " again but you do not have enough currency to continue splitting. ";
                                            std::cout << std::endl << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are: " << std::endl; 
                                        }
                                        else if (checking_hand.player.bank_total >= checking_hand.player.wager) {
                                            std::cout << "You did not pull the same rank of " << checking_hand.player.cards[0].display_rank << " again. You can no longer split your hands."; 
                                            std::cout << std::endl << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are: " << std::endl; 
                                        }
                                        else {}
                                        int loop_counter = 1;
                                        std::string hand_tracker;
                                        for (Hand& current_hand : split_hands)
                                        {
                                            if (loop_counter == 1)
                                            {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2)
                                            {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3)
                                            {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4)
                                            {
                                                hand_tracker = "fourth";
                                            }
                                            else
                                            {
                                                hand_tracker = "current";
                                            }
                                            current_hand.Show_Hand(hand_tracker);
                                            loop_counter++;
                                        }
                                        std::cout << std::endl << std::endl;
                                    }
                                    else if (split_again == "n")
                                    {
                                        std::cout << playerHand.player.display_name << " has chosen not to split their hand again." << std::endl << std::endl << "Total times split: " 
                                        << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
                                        int loop_counter = 1;
                                        std::string hand_tracker;
                                        for (Hand &current_hand : split_hands)
                                        {
                                            if (loop_counter == 1)
                                            {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2)
                                            {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3)
                                            {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4)
                                            {
                                                hand_tracker = "fourth";
                                            }
                                            else
                                            {
                                                hand_tracker = "current";
                                            }
                                            current_hand.Show_Hand(hand_tracker);
                                            loop_counter++;
                                        }
                                        std::cout << std::endl << std::endl;
                                    }
                                    else {}
                                    break;
                                }
                            }
                            new_hand = split_hands;
                            playerHand.Copy_Variables(new_hand.back());
                            return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                        }
                        else if (!checking_hand.player.can_split_hand)
                        {
                            std::cout << std::endl << "You have pulled the same rank of " << checking_hand.player.cards[0].display_rank << " again." << std::endl;
                            int loop_counter = 1;
                            std::string hand_tracker;
                            for (Hand& current_hand : temp_hands)
                            {
                                if (loop_counter == 1)
                                {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2)
                                {
                                    hand_tracker = "second";
                                }
                                else
                                {
                                    hand_tracker = "current";
                                }
                                current_hand.Show_Hand(hand_tracker);
                                loop_counter++; 
                            }
                            std::cout << std::endl << "Your current bank balance of " << checking_hand.player.display_bank_total << " is not  greater than your wager of " 
                            << checking_hand.player.display_wager << ". You can no longer split your hands. Total times split: " << color_text(31, std::to_string(split_counter)) << std::endl;
                            new_hand = temp_hands;
                            playerHand.Copy_Variables(new_hand.back());
                            return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                        }
                        else {}
                    }
                    else if (!check_same_parameter_in_hand(checking_hand, "R"))
                    {
                        new_hand.insert(new_hand.begin(), checking_hand);
                        new_hand.push_back(player_hand_1);
                        std::cout << std::endl << "Total times split: " << color_text(31, std::to_string(split_counter)) << ". Your current hand(s) are:" << std::endl; 
                        int loop_counter = 1;
                        std::string hand_tracker;
                        for (Hand &current_hand : new_hand)
                        {
                            if (loop_counter == 1)
                            {
                                hand_tracker = "first";
                            }
                            else if (loop_counter == 2)
                            {
                                hand_tracker = "second";
                            }
                            else {}
                            current_hand.Show_Hand(hand_tracker);
                            loop_counter++;
                        }
                        std::cout << std::endl;
                        playerHand.Copy_Variables(new_hand.back());
                        return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                    }
                    else {}
                }
                else if (same_rank_response == "n")
                {
                    playerHand.player.chose_split_hand = false;
                    playerHand.player.split_decision = true;
                    new_hand.push_back(playerHand);
                    std::cout << std::endl << playerHand.player.display_name << " has chosen not to split their hand." << std::endl; 
                    playerHand.Copy_Variables(new_hand.back());
                    return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
                }
                else
                {
                    std::cout << std::endl << color_text(31, "Invalid choice") + " of " + color_text(31, same_rank_response) + ". Plese re-enter your decision." << std::endl; 
                    same_rank_response.clear();
                }
            }
        }
        else if (!check_same_parameter_in_hand(playerHand, "R"))
        {
            new_hand.push_back(playerHand);
            playerHand.Copy_Variables(new_hand.back());
            return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
        }
        else {}
    }
    else if (!playerHand.player.can_split_hand)
    {
        new_hand.push_back(playerHand);
        playerHand.Copy_Variables(new_hand.back());
        return std::make_tuple(new_hand, playerHand, dealerHand, shoe, hand_count);
    }
    else {}
}
// Player Hand Logic - player_hand_logic
std::tuple<Hand, Hand, Hand, Shoe> player_hand_logic(Hand& playerHand, Hand& dealerHand, Hand& referenceHand, Shoe& shoe, int& hand_counter)
{
    if (!referenceHand.player.chose_split_aces) 
    {
        std::string response;
        std::string hand_tracker;
        if (hand_counter == 1)
        {
            hand_tracker = "first";
        }
        else if (hand_counter == 2)
        {
            hand_tracker = "second";
        }
        else if (hand_counter == 3)
        {
            hand_tracker = "third";
        }
        else if (hand_counter == 4)
        {
            hand_tracker = "fourth";
        }
        else if (hand_counter == 5)
        {
            hand_tracker = "fifth";
        }
        else
        {
            hand_tracker = "current";
        }
        if (hand_counter > 1)
        {
            playerHand.Hit(shoe);
        }
        else {}
        while ((response != "h" && response != "s" && response != "d") && playerHand.player.cards_total < 21)
        {
            if (!playerHand.player.has_hit)
            {
                if (referenceHand.player.chose_split_hand)
                {
                    std::cout << std::endl << "Here are the initial hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl; 
                    playerHand.Show_Hand("initial " + hand_tracker);
                    dealerHand.Show_Hand("initial");
                    std::cout << std::endl << "Would you like to hit, stand, or double down for hand " << std::to_string(hand_counter) << "?" << std::endl; 
                    blackjack_strategy(playerHand, dealerHand, true);
                    std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down for " << std::to_string(hand_counter) << ": ";
                    std::cin >> response;
                    std::cout << std::endl;
                }
                else if (!referenceHand.player.chose_split_hand)
                {
                    std::cout << std::endl << "Would you like to hit, stand, or double down?" << std::endl; 
                    blackjack_strategy(playerHand, dealerHand, true);
                    std::cout << std::endl << "Enter (h) to hit, (s) to stand, and (d) to double down: ";
                    std::cin >> response;
                    std::cout << std::endl;
                }
                else {}            
            }
            else if (playerHand.player.has_hit)
            {
                
                if (referenceHand.player.chose_split_hand)
                {
                    playerHand.Show_Hand("current " + hand_tracker);
                }
                else if (!referenceHand.player.chose_split_hand)
                {
                    playerHand.Show_Hand("current");
                }
                else {}
                dealerHand.Show_Hand("initial");
                std::cout << std::endl << "Would you like to hit (h) or stand (s)?" << std::endl; 
                blackjack_strategy(playerHand, dealerHand, true);
                std::cout << std::endl << "Enter (h) to hit and (s) to stand: ";
                std::cin >> response;
                std::cout << std::endl;
            }
            else {}
            if (response == "h")
            {
                playerHand.player.has_hit = true;
                playerHand.Hit(shoe);
                if (playerHand.player.cards_total > 21)
                {
                    std::cout << playerHand.player.display_name << " has chosen to hit and busted. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
                    if (referenceHand.player.chose_split_hand)
                    {
                        std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter)
                        << " and the " << dealerHand.player.display_name << "'s current hand:" << std::endl; 
                        playerHand.Show_Hand("final " + hand_tracker);
                        dealerHand.Show_Hand("current");
                    }
                    else if (!referenceHand.player.chose_split_hand)
                    {
                        std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the final hand of the " << dealerHand.player.display_name << ":" << std::endl; 
                        playerHand.Show_Hand("final");
                        dealerHand.Show_Hand("final", "show");
                    }
                    else {}
                    std::cout << std::endl;
                    
                    break;
                }
                else if (playerHand.player.cards_total < 21)
                {
                    std::cout << playerHand.player.display_name << " has chosen to hit. Current hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
                    if (referenceHand.player.chose_split_hand)
                    {
                        std::cout << std::endl << "Here are the current hands of each player for hand " << std::to_string(hand_counter) << ":" << std::endl;
                    }
                    else if (!referenceHand.player.chose_split_hand)
                    {
                        std::cout << std::endl << "Here are the current hands of each player:" << std::endl;
                    }
                    else {}
                }
                else if (playerHand.player.cards_total == 21)
                {
                    std::cout << playerHand.player.display_name << " has chosen to hit. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
                    if (referenceHand.player.chose_split_hand)
                    {
                        std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
                        << dealerHand.player.display_name << "'s current hand:" << std::endl; 
                        playerHand.Show_Hand("final " + hand_tracker);
                        dealerHand.Show_Hand("current", "");
                    }
                    else if (!referenceHand.player.chose_split_hand)
                    {
                        std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the initial hand of the " 
                        << dealerHand.player.display_name << ":" << std::endl; 
                        playerHand.Show_Hand("final");
                        dealerHand.Show_Hand("initial", "show");
                    }
                    else
                    std::cout << std::endl;
                    
                }
                else {}
                response.clear();
            }
            else if (response == "s")
            {
                std::cout << playerHand.player.display_name << " has chosen to stand. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
                if (referenceHand.player.chose_split_hand)
                {
                    std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter)
                    << " and the " << dealerHand.player.display_name << "'s current hand:" << std::endl; 
                    playerHand.Show_Hand("final " + hand_tracker);
                    dealerHand.Show_Hand("current", "");
                }
                else if (!referenceHand.player.chose_split_hand)
                {
                    std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the initial hand of the " 
                    << dealerHand.player.display_name << ":" << std::endl; 
                    playerHand.Show_Hand("final");
                    dealerHand.Show_Hand("initial", "show");
                }
                else
                std::cout << std::endl;
                
                break;
            }
            else if (response == "d" && !playerHand.player.has_hit)
            {
                if (playerHand.player.bank_total >= playerHand.player.wager)
                {
                    playerHand.player.bank_total -= playerHand.player.wager;
                    playerHand.player.wager *= 2;
                    playerHand.Hit(shoe);
                    if (playerHand.player.cards_total > 21)
                    {
                        playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
                        std::cout << playerHand.player.display_name << " has doubled down and busted. Final hand total: " 
                        << playerHand.player.display_cards_total << "." << std::endl; 
                        if (referenceHand.player.chose_split_hand)
                        {
                            std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter)
                            << " and the " << dealerHand.player.display_name << "'s current hand:" << std::endl; 
                            playerHand.Show_Hand("final " + hand_tracker);
                            dealerHand.Show_Hand("current");
                        }
                        else if (!referenceHand.player.chose_split_hand)
                        {
                            std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the final hand of the " 
                            << dealerHand.player.display_name << ":" << std::endl; 
                            playerHand.Show_Hand("final");
                            dealerHand.Show_Hand("final", "show");
                        }
                        else
                        std::cout << std::endl;
                        
                        break;
                    }
                    else if (playerHand.player.cards_total <= 21)
                    {
                        std::cout << playerHand.player.display_name << " has doubled down. Final hand total: " << playerHand.player.display_cards_total << "." << std::endl; 
                        if (referenceHand.player.chose_split_hand)
                        {
                            std::cout << std::endl << "Here is " << playerHand.player.display_name << "'s final hand for hand " << std::to_string(hand_counter) << " and the " 
                            << dealerHand.player.display_name << "'s current hand:" << std::endl; 
                            playerHand.Show_Hand("final " + hand_tracker);
                            dealerHand.Show_Hand("current");
                        }
                        else if (!referenceHand.player.chose_split_hand)
                        {
                            std::cout << std::endl << "Here is the final hand for " << playerHand.player.display_name << " and the initial hand of the " 
                            << dealerHand.player.display_name << ":" << std::endl; 
                            playerHand.Show_Hand("final");
                            dealerHand.Show_Hand("initial", "show");
                        }
                        else {}
                        std::cout << std::endl;
                        
                        break;
                    }
                    else {}
                }
                else if (playerHand.player.bank_total < playerHand.player.wager)
                {
                    std::cout << "Your current bank total of " << playerHand.player.display_bank_total << " is not greater than your wager of "
                    << playerHand.player.display_wager << ". You cannot double down." << std::endl;
                    response.clear();
                    continue;
                }
                else {}
            }
            else if (response != "h" && response != "s" && response != "d")
            {
                if (!referenceHand.player.chose_split_hand)
                {
                    std::cout << color_text(31, "Invalid choice") << "." << std::endl; 
                }
                else if (referenceHand.player.chose_split_hand)
                {
                    std::cout << color_text(31, "Invalid choice") << "." << std::endl << std::endl; 
                }
                else {}            
                response.clear();
                continue;
            }
            else {}
        }
        referenceHand.Copy_Variables(playerHand);
        return std::make_tuple(playerHand, dealerHand, referenceHand, shoe);
    }
    else if (referenceHand.player.chose_split_aces) {
        referenceHand.Copy_Variables(playerHand);
        return std::make_tuple(playerHand, dealerHand, referenceHand, shoe);
    }
    else {}
}
// Dealer Hand Logic
std::tuple<Hand, Shoe> dealer_hand_logic(std::vector<Hand>& playerHands, Hand& dealerHand, Shoe& shoe)
{
    bool all_over_21 = true;
    for (Hand current_hand : playerHands)
    {
        if (current_hand.player.cards_total <= 21)
        {
            all_over_21 = false;
            break;
        }
        else if (current_hand.player.cards_total > 21)
        {
            all_over_21 = true;
            continue;
        }
        else {}
    }
    if (!all_over_21)
    {
        if ((dealerHand.player.cards_total >= 17 && !check_parameter_in_hand(dealerHand, "R", "Ace")) || (dealerHand.player.cards_total > 17 && check_parameter_in_hand(dealerHand, "R", "Ace")))
        {
            int total_hands = playerHands.size();
            if (total_hands > 1)
            {
                int hand_counter = 0;
                std::string hand_tracker;
                std::cout << std::endl << "Here are the final hand(s) of " << playerHands.at(0).player.display_name << " and the " << dealerHand.player.display_name << ":" << std::endl;
                for (Hand current_hand : playerHands)
                {
                    hand_counter++;
                    if (hand_counter == 1)
                    {
                        hand_tracker = " first";
                    }
                    else if (hand_counter == 2)
                    {
                        hand_tracker = " second";
                    }
                    else if (hand_counter == 3)
                    {
                        hand_tracker = " third";
                    }
                    else if (hand_counter == 4)
                    {
                        hand_tracker = " fourth";
                    }
                    else if (hand_counter == 5)
                    {
                        hand_tracker = " fifth";
                    }
                    else {}
                    current_hand.Show_Hand("final" + hand_tracker);
                }
                dealerHand.Show_Hand("final", "show");
                std::cout << std::endl << "The " << dealerHand.player.display_name << " does not need to play their hand with a final total of " 
                << dealerHand.player.display_cards_total << "." << std::endl << std::endl;
            }
            else
            {
                std::cout << std::endl << "The " << dealerHand.player.display_name << " does not need to play their hand with a final total of " << dealerHand.player.display_cards_total << "." << std::endl << std::endl;
            }
        }
        else if (dealerHand.player.cards_total < 17 || (dealerHand.player.cards_total == 17 && check_parameter_in_hand(dealerHand, "R", "Ace")))
        {
            int total_hands = playerHands.size();
            if (total_hands > 1)
            {
                int hand_counter = 0;
                std::string hand_tracker;
                std::cout << std::endl << "Here are the final hand(s) of " << playerHands.at(0).player.display_name << " and the initial hand of the " << dealerHand.player.display_name << ":" << std::endl;
                for (Hand current_hand : playerHands)
                {
                    hand_counter++;
                    if (hand_counter == 1)
                    {
                        hand_tracker = " first";
                    }
                    else if (hand_counter == 2)
                    {
                        hand_tracker = " second";
                    }
                    else if (hand_counter == 3)
                    {
                        hand_tracker = " third";
                    }
                    else if (hand_counter == 4)
                    {
                        hand_tracker = " fourth";
                    }
                    else if (hand_counter == 5)
                    {
                        hand_tracker = " fifth";
                    }
                    else {}
                    current_hand.Show_Hand("final" + hand_tracker);
                }
                dealerHand.Show_Hand("initial", "show");
                std::cout << std::endl << "The " << dealerHand.player.display_name << " will now play their hand." << std::endl << std::endl;
            }
            else
            {
                std::cout << std::endl << "The " << dealerHand.player.display_name << " will now play their hand." << std::endl << std::endl;
            }
            while ((dealerHand.player.cards_total < 17 || (dealerHand.player.cards_total <= 17 && check_parameter_in_hand(dealerHand, "R", "Ace"))))
            {
                bool aces_all_ones = true;
                for (Card current_card : dealerHand.player.cards)
                {
                    if (check_card_parameter(current_card.card.rank, "Ace"))
                    {
                        current_card.card.card_value = 11;
                        aces_all_ones = false;
                        break;
                    }
                    else if (check_card_parameter(current_card.card.rank, "Ace"))
                    {
                        current_card.card.card_value = 1;
                        aces_all_ones = true;
                        continue;
                    }
                    else {}
                }
                if (!aces_all_ones || !check_parameter_in_hand(dealerHand, "R", "Ace"))
                {
                    dealerHand.Hit(shoe);
                    std::cout << dealerHand.player.display_name << " hits hand: ";
                    dealerHand.Show_Hand("", "cards");
                }
                else if (aces_all_ones)
                {
                    std::cout << dealerHand.player.display_name << " final hand ";
                    dealerHand.Show_Hand("", "cards");
                    break;
                }
            }
            std::cout << std::endl;
        }
        else {}
    }
    else if (all_over_21)
    {
        std::cout << playerHands.at(0).player.display_name << " has busted on all of their hands. " << dealerHand.player.display_name << " does not need to play their hand." << std::endl << std::endl;
        int total_hands = playerHands.size();
        if (total_hands > 1)
        {
            int hand_counter = 0;
            std::string hand_tracker;
            std::cout << "The final hands of " << playerHands.at(0).player.display_name << " and the " << dealerHand.player.display_name << " are:" << std::endl;
            for (Hand current_hand : playerHands)
            {
                hand_counter++;
                if (hand_counter == 1)
                {
                    hand_tracker = " first";
                }
                else if (hand_counter == 2)
                {
                    hand_tracker = " second";
                }
                else if (hand_counter == 3)
                {
                    hand_tracker = " third";
                }
                else if (hand_counter == 4)
                {
                    hand_tracker = " fourth";
                }
                else if (hand_counter == 5)
                {
                    hand_tracker = " fifth";
                }
                else {}
                current_hand.Show_Hand("final" + hand_tracker);
            }
            dealerHand.Show_Hand("final", "show");
        }
        else {}
    }
    else {}
    return std::make_tuple(dealerHand, shoe);
}
// Hand Comparison Logic Method
std::tuple<Hand, Hand, Shoe> hand_comparison(Hand& playerHand, Hand& dealerHand, Shoe& shoe, int& playerHandCount, int& currentHandCounter)
{
    std::string hand_tracker;
    bool multiple_hands = false;
    if (playerHandCount > 1)
    {
        multiple_hands = true;
        if (currentHandCounter == 1)
        {
            hand_tracker = " first";
        }
        else if (currentHandCounter == 2)
        {
            hand_tracker = " second";
        }
        else if (currentHandCounter == 3)
        {
            hand_tracker = " third";
        }
        else if (currentHandCounter == 4)
        {
            hand_tracker = " fourth";
        }
        else if (currentHandCounter == 5)
        {
            hand_tracker = " fifth";
        }
        else
        {
            hand_tracker.clear();
        }
    }
    else {}
    if (playerHand.player.cards_total <= 21)
    {
        if (playerHand.player.cards_total == dealerHand.player.cards_total)
        {
            playerHand.Update_Bank("P", playerHand, playerHand.player.wager);
            
            if (!multiple_hands)
            {
                std::cout << "Both players have the same final value of " << playerHand.player.display_cards_total << "." << std::endl; 
                std::cout << std::endl << "The final hands of each player are:" << std::endl; 
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands)
            {
                std::cout << "Both players have the same final value of " << playerHand.player.display_cards_total << " for hand " << std::to_string(currentHandCounter) << ". " << std::endl; 
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; 
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {} 
            dealerHand.Show_Hand("final", "show");
            if (!multiple_hands)
            {
                std::cout << std::endl << "This hand is a push. " << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl;
            }
            else if (multiple_hands)
            {
                std::cout << std::endl << "Hand " << std::to_string(currentHandCounter) << " is a push. " << playerHand.player.display_name << " nets " << playerHand.player.display_net
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl << std::endl;
            }
            else {}
        }
        else if (dealerHand.player.cards_total > playerHand.player.cards_total && dealerHand.player.cards_total <= 21)
        {
            playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
            
            if (!multiple_hands)
            {
                std::cout << dealerHand.player.display_name << " has a greater final value of " << dealerHand.player.display_cards_total << " compared to "
                << playerHand.player.display_name << "'s final value of " << playerHand.player.display_cards_total << "." << std::endl; 
                std::cout << std::endl << "The final hands of each player are:" << std::endl; 
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands)
            {
                std::cout << dealerHand.player.display_name << " has a greater final value of " << dealerHand.player.display_cards_total << " for hand " << std::to_string(currentHandCounter)
                << " compared to " << playerHand.player.display_name << "'s final value of " << playerHand.player.display_cards_total << "." << std::endl; 
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; 
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {}
            dealerHand.Show_Hand("final", "show");
            if (!multiple_hands)
            {
                std::cout << std::endl << playerHand.player.display_name << " loses the current hand. " << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl;
            }
            else if (multiple_hands)
            {
                std::cout << std::endl << playerHand.player.display_name << " loses hand " << std::to_string(currentHandCounter) << ". " << playerHand.player.display_name << " nets " << playerHand.player.display_net
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl << std::endl;
            }
            else {}
        }
        else if (dealerHand.player.cards_total < playerHand.player.cards_total)
        {
            playerHand.Update_Bank("W", playerHand, playerHand.player.wager);
            
            if (!multiple_hands)
            {
                std::cout << playerHand.player.display_name << " has a greater final value of " << playerHand.player.display_cards_total << " compared to "
                << dealerHand.player.display_name << "'s final value of " << dealerHand.player.display_cards_total << "." << std::endl; 
                std::cout << std::endl << "The final hands of each player are:" << std::endl; 
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands)
            {
                std::cout << playerHand.player.display_name << " has a greater final value of " << playerHand.player.display_cards_total << " for hand " << std::to_string(currentHandCounter)
                << " compared to " << dealerHand.player.display_name << "'s final value of " << dealerHand.player.display_cards_total << "." << std::endl; 
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; 
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {}
            dealerHand.Show_Hand("final", "show");
            if (!multiple_hands)
            {
                std::cout << std::endl << playerHand.player.display_name << " wins the current hand. " << playerHand.player.display_name << " nets " << playerHand.player.display_net
                << " this hand." << std::endl;
            }
            else if (multiple_hands)
            {
                std::cout << std::endl << playerHand.player.display_name << " wins hand " << std::to_string(currentHandCounter) << ". " << playerHand.player.display_name << " nets " << playerHand.player.display_net
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl << std::endl;
            }
            else {}
        }
        else if (dealerHand.player.cards_total > 21)
        {
            playerHand.Update_Bank("W", playerHand, playerHand.player.wager);
            
            if (!multiple_hands)
            {
                std::cout << dealerHand.player.display_name << " has busted with a final value of " << dealerHand.player.display_cards_total << "." << std::endl; 
                std::cout << std::endl << "The final hands of each player for the current hand are:" << std::endl; 
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands)
            {
                std::cout << dealerHand.player.display_name << " has busted with a final value of " << dealerHand.player.display_cards_total << "." << std::endl; 
                std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; 
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {}
            dealerHand.Show_Hand("final", "show");
            if (!multiple_hands)
            {
                std::cout << std::endl << playerHand.player.display_name << " wins the current hand. " << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl;
            }
            else if (multiple_hands)
            {
                std::cout << std::endl << playerHand.player.display_name << " wins hand " << std::to_string(currentHandCounter) << ". " << playerHand.player.display_name << " nets " << playerHand.player.display_net
                << " for hand " << std::to_string(currentHandCounter) << "." << std::endl << std::endl;
            }
            else {}
        }
        else {}
    }
    else if (playerHand.player.cards_total > 21)
    {
        playerHand.Update_Bank("L", playerHand, playerHand.player.wager);
        
        if (!multiple_hands)
        {
            std::cout << playerHand.player.display_name << " has busted with a final value of " << playerHand.player.display_cards_total << "." << std::endl; 
            std::cout << std::endl << "The final hands of each player for the current hand are:" << std::endl; 
            playerHand.Show_Hand("final");
        }
        else if (multiple_hands)
        {
            std::cout << playerHand.player.display_name << " has busted with a final value of " << playerHand.player.display_cards_total << " for hand " << std::to_string(currentHandCounter) << "." << std::endl; 
            std::cout << std::endl << "The final hands of each player for hand " << std::to_string(currentHandCounter) << " are:" << std::endl; 
            playerHand.Show_Hand("final" + hand_tracker);
        }
        else {}
        dealerHand.Show_Hand("final", "show");
        if (!multiple_hands)
        {
            std::cout << std::endl << playerHand.player.display_name << " loses the current hand. " << playerHand.player.display_name << " nets " << playerHand.player.display_net << " this hand." << std::endl;
        }
        else if (multiple_hands)
        {
            std::cout << std::endl << playerHand.player.display_name << " loses hand " << std::to_string(currentHandCounter) << ". " << playerHand.player.display_name << " nets " << playerHand.player.display_net
            << " for hand " << std::to_string(currentHandCounter) << "." << std::endl << std::endl;
        }
        else {}
    }
    else {}
    update_stats(playerHand);
    return std::make_tuple(playerHand, dealerHand, shoe);
}
// Game Logic Method
std::tuple<Hand, Hand, Shoe> game_logic(Hand& playerHand, Hand& dealerHand, Shoe& shoe) {
    auto showing_ace = dealer_showing_ace(playerHand, dealerHand, shoe);
    playerHand = std::get<0>(showing_ace);
    dealerHand = std::get<1>(showing_ace);
    shoe = std::get<2>(showing_ace);
    bool showing_ace_cont = std::get<3>(showing_ace);
    if (showing_ace_cont) 
    {
        // Player same rank check
        auto same_rank = player_same_rank(playerHand, dealerHand, shoe);
        std::vector<Hand> sr_hands = std::get<0>(same_rank);
        playerHand = std::get<1>(same_rank);
        dealerHand = std::get<2>(same_rank);
        shoe = std::get<3>(same_rank);
        int sr_hand_count = std::get<4>(same_rank);
        sr_hand_count %= sr_hand_count;
        // Player hand logic check
        std::vector<Hand> phl_hands;
        for (Hand& current_hand : sr_hands) 
        {
            sr_hand_count++;
            auto hand_logic = player_hand_logic(current_hand, dealerHand, playerHand, shoe, sr_hand_count);
            phl_hands.insert(phl_hands.begin(), std::get<0>(hand_logic));
            dealerHand = std::get<1>(hand_logic);
            playerHand = std::get<2>(hand_logic);
            shoe = std::get<3>(hand_logic);
        }
        std::reverse(phl_hands.begin(), phl_hands.end());
        // Dealer hand logic
        auto dealerHand_logic = dealer_hand_logic(phl_hands, dealerHand, shoe);
        dealerHand = std::get<0>(dealerHand_logic);
        shoe = std::get<1>(dealerHand_logic);
        // Hand comparison logic
        std::vector<Hand> hcl_hands;
        int playerHand_count = phl_hands.size();
        int currentHand_counter = 1;
        for (Hand& current_hand : phl_hands)
        {
            current_hand.Copy_Variables(playerHand);
            auto comparison_logic = hand_comparison(current_hand, dealerHand, shoe, playerHand_count, currentHand_counter);
            playerHand = std::get<0>(comparison_logic);
            dealerHand = std::get<1>(comparison_logic);
            shoe = std::get<2>(comparison_logic);
            hcl_hands.insert(hcl_hands.begin(), std::get<0>(comparison_logic));
            currentHand_counter++;
        }
        std::reverse(hcl_hands.begin(), hcl_hands.end());
        for (Hand& current_hand : hcl_hands) {
            current_hand.Reset("HandOver");
        }
    }
    else if (!showing_ace_cont) {}
    else {}
    return std::make_tuple(playerHand, dealerHand, shoe);
}
// Play game
void play_game()
{
    // Create Objects
    Shoe gameShoe;
    Hand playerHand;
    Hand dealerHand;
    // Set names of players
    dealerHand.player.name = "Dealer";
    playerHand.Name();
    // Take in Bank deposit of users
    playerHand.Deposit();
    // Create Shoe
    gameShoe.Deck_Count();
    gameShoe.Create_Shoe();
    gameShoe.Shuffle();
    while (gameShoe.deck.cards.size() >= 13 && playerHand.player.bank_total > 0)
    {
        auto gameLogic_result = game_logic(playerHand, dealerHand, gameShoe);
        playerHand = std::get<0>(gameLogic_result);
        dealerHand = std::get<1>(gameLogic_result);
        gameShoe = std::get<2>(gameLogic_result);
        bool continue_playing = false;
        playerHand.Reset("HandOver");
        dealerHand.Reset("HandOver");
        if (playerHand.player.bank_total > 0)
        {
            char cont_playing_input;
            while (true)
            {
                std::cout << std::endl << "Would you like to continue playing? (y/n): ";
                std::cin >> cont_playing_input;
                if (cont_playing_input == 'y')
                {
                    if (gameShoe.deck.cards.size() >= 13)
                    {
                        std::cout << std::endl << gameShoe.deck.cards.size() << " cards left in shoe. " << std::endl;
                        std::cout << std::endl << "Dealing new hands." << std::endl; time_sleep(5000);
                        clear_terminal();
                        break;
                    }
                    else if (gameShoe.deck.cards.size() < 13)
                    {
                        std::cout << std::endl << gameShoe.deck.cards.size() << " cards left in shoe. " << std::endl;
                        std::cout << std::endl << "Shuffling a new shoe." << std::endl;
                        gameShoe.deck.cards.clear();
                        gameShoe.Create_Shoe();
                        gameShoe.Shuffle(); time_sleep(5000);
                        clear_terminal();
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
                else if (cont_playing_input == 'n')
                {
                    continue_playing = false;
                    std::cout << std::endl << playerHand.player.display_name << " has chosen to quit playing. Final bank total: " << playerHand.player.display_bank_total << std::endl;
                    std::cout << std::endl << "Thank you for playing." << std::endl; time_sleep(5000);
                    clear_terminal();
                    break;
                }
                else
                {
                    continue;
                }
            }
            if (cont_playing_input == 'y')
            {
                continue_playing = true;
            }
            else if (cont_playing_input == 'n')
            {
                continue_playing = false;
            }
            else {}
        }
        else if (playerHand.player.bank_total == 0)
        {
            std::cout << std::endl << playerHand.player.name << " has run out of currency in their bank. " << std::endl;
            char currency_continue;
            while (true)
            {
                std::cout << std::endl << "Would you like to deposit more currency into your bank? (y/n): ";
                std::cin >> currency_continue;
                if (currency_continue == 'y')
                {
                    playerHand.Deposit(); time_sleep(5000);
                    clear_terminal();
                    break;
                }
                else if (currency_continue == 'n')
                {
                    std::cout << std::endl << playerHand.player.name << " has ran out of currency and has chosen to " << "not deposit more currency into their bank. Game over." << std::endl;
                    std::cout << std::endl << "Thank you for playing." << std::endl; time_sleep(5000);
                    clear_terminal();
                    break;
                }
                else
                {
                    continue;
                }
            }
            if (currency_continue == 'y')
            {
                continue_playing = true;
            }
            else if (currency_continue == 'n')
            {
                continue_playing = false;
            }
            else {}
        }
        else {}
        if (!continue_playing)
        {
            break;
        }
        else if (continue_playing)
        {
            continue;
        }
        else {}
    }
    csv_stats(playerHand);
}