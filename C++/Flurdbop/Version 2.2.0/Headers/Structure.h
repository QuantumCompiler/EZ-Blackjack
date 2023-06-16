// ---------- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdlib>
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
using namespace std;
// Steps to processing blackjack logic
/* ----- ----- ----- ----- ----- ----- ----- Steps to playing blackjack ----- ----- ----- ----- ----- ----- ----- -----
 * Logical steps to creating a functioning blackjack game:
 * 1 - Create Shoe object
 * 2 - Create hand object(s) (Player and dealer hands)
 * 3 - Prompt users for name
 * 4 - Prompt user for how many decks they'd like to play with
 * 5 - Create shoe of deck(s)
 * 6 - Prompt user for how much they'd like to start with (Player bank total)
 * 7 - Take wager from player
 * 8 - Deal cards to player and dealer
 * 9 - Check for ace showing from dealer
 *     If dealer is showing ace, prompt user for if they want to buy insurance, proceed to check for blackjack
 * 10 - Check for blackjack of both players
 * 11 - Check for the same rank showing in a players hand if neither player has blackjack
 *      If player is showing the same rank, prompt the player if they would like to split their hand
 *      If they choose yes, proceed to split hand, if not, go on to playing hand
 * 12 - Process game logic for player
 * 13 - Process game logic for dealer
 * 14 - Update bank for player hand(s)
 * 15 - Check to see if the player still has enough money to continue playing
 *      If they do, proceed to check if the current shoe has more than 13 cards left in it before a new hand is dealt
 * 16 - Prompt player if they would like to continue playing
 *      If no, show states of player
 *      If yes, continue to next hand
 ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
 */
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  Arrays ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  //
string Suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
string Ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
// ---- ---- ---- ---- ---- ---- ---- ---- ----  Independent Methods ---- ---- ---- ---- ---- ---- ---- ---- //
// Check parameter of card method
/*
 * feeding parameter must be a rank or a suit
 * checking parameter pertains to what rank or suit you are checking for
 * Will return either true or false for a specific card
 */
bool check_card_parameter(string feeding_parameter, string checking_parameter) {
    bool result = false;
    if (feeding_parameter == checking_parameter) {
        result = true;
        return result;
    }
    else {
        return result;
    }
}
// Clear Terminal method
/*
* This method will clear the terminal depending
*/
void clear_terminal() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__)
        system("clear");
    #endif
}
// Color Text method
/*
 * Changes color of text, must be fed a string
 */
string color_text(int a, string text) {
    string code;
    switch (a) {
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
// String to float conversion method
/*
 * Checks to see if a string fits the criteria for a float
 * FNNV - Failed non negative value, this is not a number
 * FNV1 - Failed negative value 1, this is not a number that has a (-) at the beginning of the string
 * FNV2 - Failed negative value 2, this is a negative value
 * Passed - This is a positive float that can be successfully converted from a string to a float
 */
string float_validation(string entry) {
    string result;
    bool has_decimal = false;
    if (entry.front() != '-') {
        for (int i = 0; i < entry.length(); i++) {
            if (!isdigit(entry[i])) {
                if (entry[i] == '.' && !has_decimal) {
                    has_decimal = true;
                }
                else {
                    // Failed Non-Negative Value
                    result = "FNNV";
                    return result;
                }
            }
            else if (isdigit(entry[i])) {
                continue;
            }
            else {}
        }
    }
    else if (entry.front() == '-') {
        for (int i = 1; i < entry.length(); i++) {
            if (!isdigit(entry[i])) {
                if (entry[i] == '.' && !has_decimal) {
                    has_decimal = true;
                }
                else {
                    // Failed Negative Value 1
                    result = "FNV1";
                    return result;
                }
            }
            else if (isdigit(entry[i])) {
                continue;
            }
            else {}
        }
        // Failed Negative Value 2
        result = "FNV2";
        return result;
    }
    else {}
    result = "Passed";
    return result;
}
// Round values to string method
/*
 * Rounds a float value to 2 decimal places and converts that float to a string afterwords
 */
string round_to_string(float entry_value) {
    ostringstream oss;
    oss << fixed << setprecision(2) << entry_value;
    string return_string = oss.str();
    return return_string;
}
// Round wager / bank method
/*
 * Rounds a float value, designed to be either be a player bank or player wager, to two decimal places
 */
float round_wager_bank(float entry_value) {
    entry_value = round(entry_value * 100) / 100;
    return entry_value;
}
// Sleep method
/*
 * Causes the console to sleep for a given time
 */
void time_sleep(long sleep_time) {
    this_thread::sleep_for(chrono::milliseconds(sleep_time));
}
// Measure time of method
/*
 * Measures the time taken for a method to run
 * measure_time([&Class_Name]() {Class_Name.Method();}); --> measure time of member function (Belongs to a class)
 * measure_time(&Some_Function); --> measure time of global function (Global function defined outside a class)
 */
template<typename Func>
void measure_time(Func function) {
    auto start = chrono::high_resolution_clock::now();
    function();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    float duration_time = duration.count();
    string rounded_time = round_to_string(duration_time);
    cout << endl << "Execution time: " << color_text(31, rounded_time) << " milliseconds." << endl;
}
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  Classes ---- ---- ---- ---- ---- ---- ---- ---- ---- ----  //
// Card class and struct
struct Playing_Card{
    string rank;
    string suit;
    int card_value;
};
class Card {
public:
    // Public variables
    Playing_Card card;
    string display_rank;
    string display_suit;
    string display_value;
    // Constructor
    Card(string rank, string suit) {
        card.rank = rank;
        card.suit = suit;
        for (int i = 0; i <= 12; i++) {
            if (check_card_parameter(card.rank, Ranks[i])) {
                card.rank = Ranks[i];
                this->display_rank = color_text(32, card.rank);
                switch (i) {
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
                this->display_value = color_text(33, to_string(card.card_value));
            }
            else {}
        }
        this->display_suit = color_text(37, card.suit);
        for (int i = 0; i <= 3; i++) {
            if (check_card_parameter(card.suit, Suits[i])) {
                card.suit = Suits[i];
                switch (i) {
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
    // Change value of card method
    void Set_New_Value(int new_value) {
        card.card_value = new_value;
    }
    // Representation method
    friend ostream & operator << (ostream & os, const Card & currentCard) {
        os << currentCard.display_rank << " of " << currentCard.display_suit;
        return os;
    }
};
// Shoe Class and Struct
struct Deck{
    vector<Card> cards;
    vector<Card> returned_cards;
    vector<Card> rigged_cards;
    int num_of_decks;
};
class Shoe {
public:
    // Public variables
    Deck deck;
    // Constructor
    Shoe() {
        deck.num_of_decks = 0;
        deck.rigged_cards = {};
    }
    // Create shoe method
    vector<Card> Create_Shoe() {
        for (int i = 1; i <= deck.num_of_decks; i++) {
            for (const auto & rank : Ranks) {
                for (const auto & suit : Suits) {
                    deck.cards.push_back(Card(rank, suit));
                }
            }
        }
        return deck.cards;
    }
    int Deck_Count() {
        time_sleep(1000);
        bool loop_passed = false;
        while (!loop_passed) {
            string input;
            cout << "Please enter the number of decks you'd like to play with: ";
            cin >> input;
            for (int i = 0; i < input.size(); i++) {
                if (isdigit(input[i]) && input[0] != '0') {
                    loop_passed = true;
                    continue;
                }
                else if (!isdigit(input[i]) || input[i] == '0') {
                    loop_passed = false;
                    cout << "\n" + color_text(31, "Invalid Response") + " of " + color_text(31, input)
                    + ". Please enter a positive integer for a deck count." "\n" << endl;
                    break;
                }
                else {}
            }
            if (loop_passed) {
                deck.num_of_decks = stoi(input);
                break;
            }
            else {}
        }
        time_sleep(1000);
        cout << endl << "This shoe will be comprised of " + color_text(33, to_string(deck.num_of_decks))
        + " deck(s)." << endl;
        return deck.num_of_decks;
    }
    // Draw method
    Card Draw() {
        if (deck.rigged_cards.empty()) {
            Card card_drawn = deck.cards.back();
            deck.cards.pop_back();
            return card_drawn;
        }
        else if (deck.rigged_cards.size() > 0) {
            Card card_drawn = deck.rigged_cards.back();
            deck.rigged_cards.pop_back();
            return card_drawn;
        }
        else {}
    }
    // Deal cards method
    void Deal_Cards() {
        cout << "\n" "Here are the cards in the shoe:" << endl;
        bool rigged_deck = false;
        int deck_counter = 0;
        int card_dealt_number = 1;
        if (deck.rigged_cards.size() > 0) {
            rigged_deck = true;
        }
        else if (deck.cards.size() > 0) {
            rigged_deck = false;
        }
        else {}
        if (!rigged_deck) {
            int num_of_cards = deck.cards.size();
            deck.returned_cards.clear();
            for (int i = 1; i <= num_of_cards; i++) {
                if (i == 1) {
                    cout << endl << "Dealing the deck(s):" << endl << "\n";
                }
                else {}
                Card drawn_card = Draw();
                deck.returned_cards.push_back(drawn_card);
                cout << "Card dealt number: " << color_text(33, to_string(card_dealt_number)) <<
                 " - " << drawn_card << endl;
                if (card_dealt_number % 52 == 0) {
                    deck_counter++;
                    if (deck.cards.size() > 0) {
                        cout << endl << "End of remaining deck " << to_string(deck_counter) << ". " << to_string(card_dealt_number) << " cards dealt, "
                        << to_string(deck.cards.size()) << " cards remaining in shoe." "\n" << endl;
                    }
                    else if (deck.cards.empty()) {
                        cout << endl << "End of shoe." "\n" << endl;
                    }
                    else {}
                }
                else if (card_dealt_number % 52 != 0) {
                    if (deck.cards.empty()) {
                        cout << endl << "End of shoe." "\n" << endl;
                    }
                    else {}
                }
                else {}
                card_dealt_number += 1;
            }
            deck.cards = deck.returned_cards;
            reverse(deck.cards.begin(), deck.cards.end());
            cout << color_text(33, to_string(deck.cards.size())) << " cards left in shoe." << endl;
        }
        else if (rigged_deck) {
            int num_of_rigged_cards = deck.rigged_cards.size();
            deck.returned_cards.clear();
            for (int i = 1; i <= num_of_rigged_cards; i++) {
                if (i == 1) {
                    cout << endl << "Dealing rigged shoe:" "\n" << endl;
                }
                else {}
                Card drawn_card = Draw();
                deck.returned_cards.push_back(drawn_card);
                cout << "Card dealt number: " << color_text(33, to_string(card_dealt_number))
                << " - " << drawn_card << endl;
                card_dealt_number += 1;
            }
            deck.rigged_cards = deck.returned_cards;
            reverse(deck.rigged_cards.begin(), deck.rigged_cards.end());
            cout << endl << color_text(33, to_string(deck.rigged_cards.size())) << " cards left in rigged shoe." << endl;
        }
        else {}
    }
    // Shuffle method
    void Shuffle() {
        random_device rd;
        std::mt19937 g(rd());
        shuffle(deck.cards.begin(), deck.cards.end(), g);
    }
    // Representation method
    friend ostream & operator << (ostream & os, const Shoe & shoe) {
        os << "\n" "Deck of " << color_text(33, to_string(shoe.deck.cards.size())) << " cards and "
        << color_text(33, to_string(shoe.deck.num_of_decks)) << " deck(s)." << endl;
        return os;
    }
};
// Hand Class and struct
struct Player {
    string name;
    float bank_total;
    int cards_total;
    float hand_wager;
    vector<Card> cards;
};
class Hand{
public:
    // Public variables
    Player player;
    // Constructor
    Hand() {
        player.name = "";
        player.bank_total = 0;
        player.cards_total = 0;
        player.hand_wager = 0;
        player.cards = {};
    }
    // Add cards to hand method
    void Add_Card_To_Hand(Card card) {
        player.cards.push_back(card);
    }
    // Add hand total method
    int Add_Hand_Total() {
        int ace_count = 0;
        int running_hand_value = 0;
        for (const Card & current_card : player.cards) {
            if (check_card_parameter(current_card.card.rank, "Ace")) {
                ace_count += 1;
            }
            else {}
        }
        for (Card & current_card : player.cards) {
            if (ace_count == 1) {
                if (check_card_parameter(current_card.card.rank, "Ace")) {
                    current_card.Set_New_Value(11);
                }
                else {}
            }
            else if (ace_count > 1) {
                if (check_card_parameter(current_card.card.rank, "Ace")) {
                    current_card.Set_New_Value(1);
                }
                else {}
            }
            else {}
            running_hand_value += current_card.card.card_value;
            ace_count -= 1;
        }
        if (running_hand_value > 21) {
            running_hand_value = 0;
            for (Card & current_card : player.cards) {
                if (check_card_parameter(current_card.card.rank, "Ace")) {
                    current_card.Set_New_Value(1);
                    running_hand_value += current_card.card.card_value;
                }
                else if (!(check_card_parameter(current_card.card.rank, "Ace"))) {
                    running_hand_value += current_card.card.card_value;
                }
                else {}
            }
        }
        else {}
        player.cards_total = running_hand_value;
        return player.cards_total;
    }
    // Hand name method
    string Name() {
        string hand_name = "";
        cout << "Enter a name for this player: ";
        cin >> hand_name;
        player.name = color_text(34, hand_name);
        time_sleep(1000);
        return player.name;
    }
    // Deposit method
    float Deposit() {
        player.bank_total = 0;
        while (player.bank_total == 0) {
            while (true) {
                try {
                    string deposit;
                    string try_result;
                    cout << "\n" "Please enter an amount you'd like to deposit into your bank: ";
                    cin >> deposit;
                    try_result = float_validation(deposit);
                    if (try_result == "FNNV") {
                        throw invalid_argument("\n" + color_text(31, "Invalid entry") + " of " + color_text(31, deposit)
                        + ". Please re-enter your bank total.");
                    }
                    else if (try_result == "FNV1") {
                        throw invalid_argument("\n" + color_text(31, "Invalid entry") + " of " + color_text(31, deposit)
                        + ". Please re-enter your bank total.");
                    }
                    else if (try_result == "FNV2") {
                        throw invalid_argument("\n" + color_text(31, "Negative entry") + " of " + color_text(31, deposit)
                        + ". Please enter a positive value for a bank total.");
                    }
                    else if (try_result == "Passed") {
                        player.bank_total = round_wager_bank(stof(deposit));
                        break;
                    }
                    else {}
                }
                catch (const invalid_argument & e) {
                    cout << e.what() << endl;
                }
                if (player.bank_total > 0) {
                    break;
                }
                else if (player.bank_total < 0) {
                    continue;
                }
            }
        }
        time_sleep(1000);
        string Bank_of_Player = round_to_string(player.bank_total);
        cout << "\n" << player.name << " has decided to start with: "
        << color_text(33, Bank_of_Player) << "\n" << endl;
        return player.bank_total;
    }
    // Hit hand method
    Hand Hit(Shoe& shoe) {
        Add_Card_To_Hand(shoe.Draw());
        Add_Hand_Total();
        return Hand();
    }
    // Insurance method
    tuple<float, float, bool> Insurance(Hand& hand) {
        string insurance_choice;
        bool insurance_decision = false;
        while (insurance_choice.empty()) {
            cout << "Would you like to buy insurance? Insurance pays 2 : 1. (y/n): ";
            cin >> insurance_choice;
            if (insurance_choice == "y") {
                insurance_decision = true;
            }
            else if (insurance_choice == "n") {
                break;
            }
            else {
                cout << color_text(31, "Invalid choice") + " of "
                + color_text(31, insurance_choice) + ". Plese re-enter your insurance decision." "\n" << endl;
                insurance_choice.clear();
            }
        }
        if (insurance_decision) {
            float insurance_wager = round_wager_bank(0.5*hand.player.hand_wager);
            hand.player.bank_total -= insurance_wager;
            return make_tuple(insurance_wager, hand.player.bank_total, insurance_decision);
        }
        else if (!insurance_decision) {
            hand.player.bank_total = hand.player.bank_total;
            return make_tuple(hand.player.hand_wager, hand.player.bank_total, insurance_decision);
        }
        else {}
    }
    // Place wager method
    float Place_Wager(Hand& hand) {
        float wager = 0;
        while (wager == 0) {
            while (true) {
                try {
                    string input_wager;
                    string try_result;
                    time_sleep(1000);
                    cout << endl << "Please place a wager for this hand. Current bank total: " << color_text(33, round_to_string(hand.player.bank_total)) << ": ";
                    cin >> input_wager;
                    cout << endl;
                    try_result = float_validation(input_wager);
                    if (try_result != "Passed") {
                        if (try_result == "FNNV" || try_result == "FNV1") {
                            throw invalid_argument(color_text(31, "Invalid Wager") + " of " + color_text(31, input_wager)
                            + ". Please enter a number for your wager.");
                        }
                        else if (try_result == "FNV2") {
                            string string_wager = round_to_string(round_wager_bank(stof(input_wager)));                        
                            throw invalid_argument("\n"
                            + color_text(31, "Negative wager") + " of " + color_text(31, string_wager)
                            + ". Please enter a positive number for your wager.");
                        }
                        else {}
                    }
                    else if ((try_result == "Passed") && (stof(input_wager) > player.bank_total)) {
                        string string_wager = round_to_string(round_wager_bank(stof(input_wager)));
                        string string_PB = round_to_string(player.bank_total);                        
                        throw invalid_argument(color_text(31, "Invalid wager") + " of " + color_text(31, string_wager)
                        + " due to wager being larger than bank total of "
                        + color_text(31, string_PB) + ". Please re-enter your wager.");
                    }
                    else {
                        wager = round_wager_bank(stof(input_wager));
                        break;
                    }
                }
                catch (const invalid_argument & e) {
                    cout << e.what() << endl;
                }
            }
        }
        time_sleep(1000);
        hand.player.hand_wager = round_wager_bank(wager);
        hand.player.bank_total -= hand.player.hand_wager;
        string player_wager = round_to_string(round_wager_bank(hand.player.hand_wager));
        string player_bank = round_to_string(round_wager_bank(hand.player.bank_total));
        cout << hand.player.name << " has wagered: " << color_text(31, player_wager)
        << " with a current bank total of " << color_text(33, player_bank) << endl;
        return hand.player.hand_wager;
    }
    // Show hand method
    void Show_Hand(string option = "", string dealer_show = "") {
        string display_name = color_text(34, player.name);
        if (player.name != "Dealer") {
            if (option.empty()) {
                option = "current";
                cout << display_name << "'s " << color_text(31, option) << " hand: [";
                for (int i = 0; i < player.cards.size(); i++) {
                    if (i == player.cards.size() - 1) {
                        cout << player.cards[i] << "]";
                    }
                    else {
                        cout << player.cards[i] << " , ";
                    }
                }
                Add_Hand_Total();
                string Rounded_Wager = round_to_string(player.hand_wager);
                string Bank_of_Player = round_to_string(player.bank_total);
                cout << color_text(36, " Hand Total") << ": "
                << color_text(36, to_string(player.cards_total)) << " , "
                << color_text(31, "Hand Wager") << ": " << color_text(31, Rounded_Wager)
                << " , " << color_text(33, "Bank Total") << ": " << color_text(33, Bank_of_Player)
                << endl;
            }
            else if (!option.empty()) {
                cout << display_name << "'s " << color_text(31, option) << " hand: [";
                for (int i = 0; i < player.cards.size(); i++) {
                    if (i == player.cards.size() - 1) {
                        cout << player.cards[i] << "]";
                    }
                    else {
                        cout << player.cards[i] << " , ";
                    }
                }
                Add_Hand_Total();
                string Rounded_Wager = round_to_string(player.hand_wager);
                string Bank_of_Player = round_to_string(player.bank_total);
                cout << color_text(36, " Hand Total") << ": "
                << color_text(36, to_string(player.cards_total)) << " , " <<
                color_text(31, "Hand Wager") << ": " << color_text(31, Rounded_Wager) << " , "
                << color_text(33, "Bank Total") << ": " << color_text(33, Bank_of_Player)
                << endl;
            }
            else {}
        }
        else if (player.name == "Dealer") {
            if (option.empty()) {
                if (dealer_show.empty()) {
                    option = "current";
                    cout << display_name << "'s " << color_text(31, option)
                    << " hand: [Hidden, " << player.cards.back() << "]"
                    << color_text(36, " Hand Total") << ": "
                    << color_text(36, to_string(player.cards.back().card.card_value))
                    << endl;
                }
                else if (!dealer_show.empty()) {
                    option = "current";
                    if (dealer_show != "cards") {
                        cout << display_name << "'s " << color_text(31, option) << " hand: [";
                    }
                    else if (dealer_show == "cards") {
                        cout << "[";
                    }
                    else {}
                    for (int i = 0; i < player.cards.size(); i++) {
                        if (i == player.cards.size() - 1) {
                            cout << player.cards[i] << "]";
                        }
                        else {
                            cout << player.cards[i] << " , ";
                        }
                    }
                    Add_Hand_Total();
                    cout << color_text(36, " Hand Total") << ": "
                         << color_text(36, to_string(player.cards_total)) << endl;
                }
                else {}
            }
            else if (!option.empty()) {
                if (dealer_show.empty()) {
                    cout << display_name << "'s " << color_text(31, option)
                         << " hand: [Hidden, " << player.cards.back() << "]"
                         << color_text(36, " Hand Total") << ": "
                         << color_text(36, to_string(player.cards.back().card.card_value))
                         << endl;
                }
                else if (!dealer_show.empty()) {
                    if (dealer_show != "cards") {
                        cout << display_name << "'s " << color_text(31, option) << " hand: [";
                    }
                    else if (dealer_show == "cards") {
                        cout << "[";
                    }
                    else {}
                    for (int i = 0; i < player.cards.size(); i++) {
                        if (i == player.cards.size() - 1) {
                            cout << player.cards[i] << "]";
                        }
                        else {
                            cout << player.cards[i] << " , ";
                        }
                    }
                    Add_Hand_Total();
                    cout << color_text(36, " Hand Total") << ": "
                         << color_text(36, to_string(player.cards_total)) << endl;
                }
                else {}
            }
            else {}
        }
        else {}
    }
    // Update bank method
    float Update_Bank(string choice, Hand& hand, float wager) {
        switch (choice[0]) {
            case 'W':
                hand.player.bank_total += 2.0*wager;
                return hand.player.bank_total;
            case 'L':
                return hand.player.bank_total;
            case 'P':
                hand.player.bank_total += wager;
                return hand.player.bank_total;
            case 'B':
                hand.player.bank_total += wager + 1.5*wager;
                return hand.player.bank_total;
            case 'I':
                hand.player.bank_total += 3.0*wager;
                return hand.player.bank_total;
            default:
                hand.player.bank_total += wager;
                return hand.player.bank_total;
        }
    }
};
// ---- ---- ---- ---- ---- ---- ---- ---- ---- Class Dependent Methods ---- ---- ---- ---- ---- ---- ---- ---- //
// Check for rank / suit in hand method
/*
 * Will check if a specific parameter is in a hand, e.g. Rank or Suit of card
 * parameter must be R - Rank or S - Suit, othewrise an error will be thrown
 * checking_parameter is the rank or suit of a card you are checking for
 * Function will return true or false depending on what happens in the funciton
 */
bool check_parameter_in_hand(Hand& hand, string parameter, string checking_parameter) {
    bool result = false;
    for (Card card : hand.player.cards) {
        if (parameter == "R") {
            if (check_card_parameter(card.card.rank, checking_parameter)) {
                result = true;
                break;
            }
            else {continue;}
        }
        else if (parameter == "S") {
            if (check_card_parameter(card.card.suit, checking_parameter)) {
                result = true;
                break;
            }
            else {continue;}
        }
        else {
            throw invalid_argument("\n"
            + color_text(31, "Invalid parameter") + ". Please select either rank or suit to check." "\n");
        }
    }
    return result;
}
// Check for same rank / suit in hand method
/*
 * Checks for if a parameter is repeated in a hand, e.g. Rank or Suit
 * parameter must be R - Rank or S - Suit, otherwise an error will be thrown
 * checking_parameter is optional, but if chosen, it must be set for if a specific parameter is repeated
 * Function will return true or false depending on what is discovered in hand
 */
bool check_same_parameter_in_hand(Hand& hand, string parameter, string checking_parameter = "") {
    bool result = true;
    vector<Card> one_onward(hand.player.cards.begin() + 1, hand.player.cards.end());
    for (Card card : one_onward) {
        if (parameter == "R") {
            if (!check_card_parameter(card.card.rank, hand.player.cards.at(0).card.rank)
            || (!checking_parameter.empty() && !check_card_parameter(card.card.rank, checking_parameter))) {
                result = false;
                break;
            }
            else {continue;}
        }
        else if (parameter == "S") {
            if (!check_card_parameter(card.card.suit, hand.player.cards.at(0).card.suit)
            || (!checking_parameter.empty()) && !check_card_parameter(card.card.suit, checking_parameter)) {
                result = false;
                break;
            }
            else {continue;}
        }
        else {
            throw invalid_argument("\n"
            + color_text(31, "Invalid parameter") + ". Please select either rank or suit to check." "\n");
        }
    }
    return result;
}
// Check for Blackjack in hand method
/*
 * Checks if a blackjack is present in a hand
 * Function will return true or false depending on if there is a blackjack in a players hand
 */
bool check_blackjack(Hand& hand) {
    bool result = false;
    for (Card card : hand.player.cards) {
        if (card.card.card_value == 10) {
            if (check_parameter_in_hand(hand, "R", "Ace")) {
                result = true;
            }
            else {continue;}
        }
        else {continue;}
    }
    return result;
}
// Deal shoe method
/*
 * Prompts player to enter a wager for hand
 * Deals cards to a player and a dealer. Player gets first and third card of deal, dealer gets second and fourth
 * After cards are dealt, hands will be shown of each player
 * Function returns a pair of hands
 * pair<Hand, Hand> examplePair = deal_hand(Shoe shoe, Hand playerHand, Hand dealerHand);
 * Hand firstHand = examplePair.first; --> Accesses the first hand (playerHand) that is returned
 * Hand secondHand = examplePair.second; --> Accesses the second hand (dealerHand) that is returned
 */
pair<Hand, Hand> deal_hand(Shoe& shoe, Hand& playerHand, Hand& dealerHand) {
    if (!(playerHand.player.cards.empty()) && !(dealerHand.player.cards.empty())) {
        playerHand.player.cards.clear();
        dealerHand.player.cards.clear();
    }
    else {}
    if (playerHand.player.hand_wager >= 0) {
        playerHand.player.hand_wager = 0;
    }
    else {}
    playerHand.Place_Wager(playerHand);
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            playerHand.Hit(shoe);
        }
        else if (i % 2 == 1) {
            dealerHand.Hit(shoe);
        }
        else {}
    }
    cout << endl;
    time_sleep(1000);
    cout << "Here are the initial hands of each player: " << endl;
    time_sleep(1000);
    playerHand.Show_Hand("initial");
    time_sleep(1000);
    dealerHand.Show_Hand("initial");
    return make_pair(playerHand, dealerHand);
}
// Black logic method
/*
* This method processes logic to tell the user the best strategy for playing blackjack
* This method takes in a player hand, dealer hand, a boolean that keeps track if a player has hit their hand already
* This method does not return any values, but it outputs to console what players should do
*/
void blackjack_logic(Hand& playerHand, Hand& dealerHand, bool has_hit_or_split) {
    int player_card_total = playerHand.player.cards_total;
    double player_wager = playerHand.player.hand_wager;
    double player_bank = playerHand.player.bank_total;
    int num_of_player_cards = playerHand.player.cards.size();
    int dealer_face_up_card = dealerHand.player.cards[1].card.card_value;
    bool can_double_down = false;
    bool can_split = false;
    if (player_bank >= player_wager) {
        can_double_down = true;
        can_split = true;
    }
    else {}
    time_sleep(1000);
    if (num_of_player_cards == 2 && (check_parameter_in_hand(playerHand,"R","Ace") || check_same_parameter_in_hand(playerHand,"R")) && !check_blackjack(playerHand)) {
        if (check_parameter_in_hand(playerHand,"R","Ace") && (check_parameter_in_hand(playerHand,"R","2") || check_parameter_in_hand(playerHand,"R","3"))) {
            switch (dealer_face_up_card)
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
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            case 5:
            case 6:
                if (can_double_down && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                    << " or " << color_text(31, "hit") << "." << endl;
                }
                else if (!can_double_down || has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggess " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                }
                else {}
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand,"R","Ace") && (check_parameter_in_hand(playerHand,"R","4") || check_parameter_in_hand(playerHand,"R","5"))) {
            switch (dealer_face_up_card)
            {
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            case 4:
            case 5:
            case 6:
                if (can_double_down && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                    << " or " << color_text(31, "hit") << "." << endl;
                }
                else if (!can_double_down || has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                }
                else {}
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand,"R","Ace") && check_parameter_in_hand(playerHand,"R","6")) {
            switch (dealer_face_up_card)
            {
            case 2:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                if (can_double_down && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                    << " or " << color_text(31, "hit") << "." << endl;
                }
                else if (!can_double_down || has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                }
                else {}
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand,"R","Ace") && check_parameter_in_hand(playerHand,"R","7")) {
            switch (dealer_face_up_card)
            {
            case 2:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                if (can_double_down && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                    << " or " << color_text(31, "stand") << "." << endl;
                }
                else if (!can_double_down || has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                }
                else {}
                break;
            case 7:
            case 8:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                break;
            case 9:
            case 10:
            case 11:
            case 1:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            default:
                break;
            }
        }
        else if (check_parameter_in_hand(playerHand,"R","Ace") && (check_parameter_in_hand(playerHand,"R","8") || check_parameter_in_hand(playerHand,"R","9"))) {
            cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
        }
        else {}
        if (check_same_parameter_in_hand(playerHand,"R")) {
            if (check_parameter_in_hand(playerHand,"R","2") || check_parameter_in_hand(playerHand,"R","3")) {
                switch (dealer_face_up_card)
                {
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    if (can_split && !has_hit_or_split) {
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split")
                        << " or " << color_text(31, "hit") << "." << endl;
                    }
                    else if (!can_split || has_hit_or_split) {
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                    }
                    else {}
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                case 1:
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                    break;
                default:
                    break;
                }
            }
            else if (check_parameter_in_hand(playerHand,"R","4")) {
                switch (dealer_face_up_card)
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
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                    break;
                case 5:
                case 6:
                    if (can_split && !has_hit_or_split) {
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split")
                        << " or " << color_text(31, "hit") << "." << endl;
                    }
                    else if (!can_split || has_hit_or_split) {
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                    }
                    else {}
                    break;                
                default:
                    break;
                }
            }
            else if (check_parameter_in_hand(playerHand,"R","5")) {
                switch (dealer_face_up_card)
                {
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    if (can_double_down && !has_hit_or_split) {
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                        << " or " << color_text(31, "hit") << "." << endl;
                    }
                    else if (!can_double_down || has_hit_or_split) {
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                    }
                    break;
                    break;
                case 10:
                case 11:
                case 1:
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                    break;
                default:
                    break;
                }
            }
            else if (check_parameter_in_hand(playerHand,"R","6")) {
                if (can_split && !has_hit_or_split) {
                    switch (dealer_face_up_card)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split") << "." << endl;
                        break;
                    case 7:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split")
                        << " or " << color_text(31, "stand") << "." << endl;
                        break;
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                        break;
                    default:
                        break;
                    }
                }
                else if (!can_split || has_hit_or_split) {
                    switch (dealer_face_up_card)
                    {
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;                        
                        break;
                    case 4:
                    case 5:
                    case 6:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                        break;
                    default:
                        break;
                    }
                }
                else {}
            }
            else if (check_parameter_in_hand(playerHand,"R","7")) {
                if (can_split && !has_hit_or_split) {
                    switch (dealer_face_up_card)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split") << "." << endl;                        
                        break;
                    case 8:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split")
                        << " or " << color_text(31, "hit") << "." << endl;
                        break;
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                        break;
                    default:
                        break;
                    }
                }
                else if (!can_split || has_hit_or_split) {
                    switch (dealer_face_up_card)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;                        
                        break;
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                        break;
                    default:
                        break;
                    }
                }
                else {}
            }
            else if (check_parameter_in_hand(playerHand,"R","8")) {
                if (can_split && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split") << "." << endl;
                }
                else if (!can_split || has_hit_or_split) {
                    switch (dealer_face_up_card)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;                        
                        break;
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                        break;
                    default:
                        break;
                    }
                }
                else {}
            }
            else if (check_parameter_in_hand(playerHand,"R","9")) {
                if (can_split && !has_hit_or_split) {
                    switch (dealer_face_up_card)
                    {
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 8:
                    case 9:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split") << "." << endl;                        
                        break;
                    case 7:
                    case 10:
                    case 11:
                    case 1:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                        break;
                    default:
                        break;
                    }
                }
                else if (!can_split || has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                }
                else {}
            }
            else if (playerHand.player.cards_total == 20) {
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
            }
            else if (check_parameter_in_hand(playerHand,"R","Ace")) {
                if (can_split && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "split") << "." << endl;
                }
                else if (!can_split || has_hit_or_split) {
                    switch (dealer_face_up_card)
                    {
                    case 2:
                    case 3:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 1:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;                        
                        break;
                    case 4:
                    case 5:
                    case 6:
                        cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
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
    else if (num_of_player_cards >=2) {
        if (player_card_total >= 4 && player_card_total <= 8) {
            cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
        }
        else if (player_card_total == 9) {
            switch (dealer_face_up_card)
            {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                if (num_of_player_cards == 2 && can_double_down && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                    << " or " << color_text(31, "hit") << "." << endl;
                }
                else if (num_of_player_cards > 2 || !can_double_down || has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                }
                else {}
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            default:
                break;
            }
        }
        else if (player_card_total == 10) {
            switch (dealer_face_up_card)
            {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                if (num_of_player_cards == 2 && can_double_down && !has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                    << " or " << color_text(31, "hit") << "." << endl;
                }
                else if (num_of_player_cards > 2 || !can_double_down || has_hit_or_split) {
                    cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                }
                else {}
                break;
            case 10:
            case (11):
            case (1):
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            default:
                break;
            }
        }
        else if (player_card_total == 11) {
            if (num_of_player_cards == 2 && can_double_down && !has_hit_or_split) {
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "double down")
                << " or " << color_text(31, "hit") << "." << endl;
            }
            else if (num_of_player_cards >= 2 || !can_double_down || has_hit_or_split) {
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
            }
            else {}
        }
        else if (player_card_total == 12) {
            switch (dealer_face_up_card)
            {
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            case 4:
            case 5:
            case 6:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                break;
            default:
                break;
            }
        }
        else if (player_card_total == 13 || player_card_total == 14 || player_card_total == 15 || player_card_total == 16) {
            switch (dealer_face_up_card)
            {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 1:
                cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "hit") << "." << endl;
                break;
            default:
                break;
            }
        }
        else if (player_card_total == 17 || player_card_total == 18 || player_card_total == 19 || player_card_total == 20) {
            cout << endl << color_text(32, "Blackjack") << " strategy suggests " << color_text(34, playerHand.player.name) << " should " << color_text(31, "stand") << "." << endl;
        }
        else {}
    }
    else {}
    time_sleep(1000);
}
// Dealer showing ace method
/*
 * Checks to see if the dealer is showing an ace for their face up card.
 * Prompts player if they would like to purchase insurance
 * If the player chooses to buy insurance, it will check if either player has blackjack
 * If either the player or dealer has blackjack, the function will return a false value for hand_continue
 * Access this boolean value to process logic later on in the hand
 * Function returns the player hand and dealer hand, a boolean for if the hand is to continue or not, and the game shoe that was fed
 */
tuple<Hand, Hand, bool, Shoe> dealer_showing_ace(Hand& playerHand, Hand& dealerHand, Shoe& shoe) {
    float prior_bank_total = playerHand.player.bank_total;
    deal_hand(shoe, playerHand, dealerHand);
    bool hand_continue = true;
    if (check_card_parameter(dealerHand.player.cards.at(1).card.rank, "Ace")) {
        if (playerHand.player.bank_total >= 0.5*playerHand.player.hand_wager) {
            time_sleep(1000);
            cout << endl << "The " << dealerHand.player.name << " is showing an " << dealerHand.player.cards.at(1).display_rank << ". ";
            auto insurance_result = playerHand.Insurance(playerHand);
            float insurance_wager = get<0>(insurance_result);
            bool chose_to_buy = get<2>(insurance_result);
            if (chose_to_buy) {
                time_sleep(1000);
                cout << endl << playerHand.player.name << " has chosen to buy insurance. Your insurance wager"
                << " is " << color_text(34, round_to_string(insurance_wager)) << "." << endl;
                time_sleep(1000);
                if (check_blackjack(dealerHand) && check_blackjack(playerHand)) {
                    hand_continue = false;
                    cout << endl << "Both players have blackjack. " << playerHand.player.name << " wins insurance of "
                         << color_text(33, round_to_string(2*insurance_wager)) << " and pushes their "
                         << "original wager of "
                         << color_text(33, round_to_string(playerHand.player.hand_wager));
                    time_sleep(1000);
                    playerHand.Update_Bank("P", playerHand, playerHand.player.hand_wager);
                    playerHand.Update_Bank("I", playerHand, insurance_wager);
                    float final_net = playerHand.player.bank_total - prior_bank_total;
                    cout << ". " << playerHand.player.name << " nets "
                         << color_text(33, round_to_string(final_net)) << " this hand." << endl
                         << "\n" "Here are the final hands of the players:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("final", "Show");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand))) {
                    hand_continue = false;
                    cout << endl << dealerHand.player.name << " has blackjack but " << playerHand.player.name
                         << " does not. " << playerHand.player.name << " wins insurance of "
                         << color_text(33, round_to_string(2*insurance_wager)) << " and loses their "
                         << "original wager of "
                         << color_text(33, round_to_string(playerHand.player.hand_wager));
                    time_sleep(1000);
                    playerHand.Update_Bank("L", playerHand, playerHand.player.hand_wager);
                    playerHand.Update_Bank("I", playerHand, insurance_wager);
                    float final_net = playerHand.player.bank_total - prior_bank_total;
                    cout << ". " << playerHand.player.name << " nets "
                         << color_text(33, round_to_string(final_net)) << " this hand." << endl
                         << "\n" "Here are the final hands of the players:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("final", "Show");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand))) {
                    hand_continue = false;
                    cout << endl << playerHand.player.name << " has blackjack and " << dealerHand.player.name
                         << " does not. " << playerHand.player.name << " loses insurance of "
                         << color_text(33, round_to_string(insurance_wager)) << " but wins their "
                         << "original wager of "
                         << color_text(33, round_to_string(1.5*playerHand.player.hand_wager));
                    time_sleep(1000);
                    playerHand.Update_Bank("B", playerHand, playerHand.player.hand_wager);
                    playerHand.Update_Bank("L", playerHand, insurance_wager);
                    float final_net = playerHand.player.bank_total - prior_bank_total;
                    cout << ". " << playerHand.player.name << " nets "
                         << color_text(33, round_to_string(final_net)) << " this hand." << endl
                         << "\n" "Here are the final hands of the players:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("final", "Show");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand))) {
                    hand_continue = true;
                    playerHand.Update_Bank("L", playerHand, insurance_wager);
                    cout << endl << dealerHand.player.name << " does not have blackjack. " << playerHand.player.name
                         << " loses their insurance wager of "
                         << color_text(33, round_to_string(insurance_wager))
                         << ". The hand will continue." "\n" << endl;
                    time_sleep(1000);
                    cout << "Here are the current hands of each player:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("initial");
                    time_sleep(1000);
                    dealerHand.Show_Hand("initial");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else {}
            }
            else if (!chose_to_buy) {
                time_sleep(1000);
                cout << endl << playerHand.player.name << " has chosen to not buy insurance." << endl;
                time_sleep(1000);
                if (check_blackjack(dealerHand) && check_blackjack(playerHand)) {
                    hand_continue = false;
                    cout << endl << "Both players have blackjack. " << playerHand.player.name << " pushes their "
                         << "original wager of "
                         << color_text(33, round_to_string(playerHand.player.hand_wager));
                    time_sleep(1000);
                    playerHand.Update_Bank("P", playerHand, playerHand.player.hand_wager);
                    float final_net = playerHand.player.bank_total - prior_bank_total;
                    cout << ". " << playerHand.player.name << " nets "
                         << color_text(33, round_to_string(final_net)) << " this hand." << endl
                         << "\n" "Here are the final hands of the players:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("final", "Show");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand))) {
                    hand_continue = false;
                    cout << endl << dealerHand.player.name << " has blackjack but " << playerHand.player.name
                         << " does not. " << playerHand.player.name << " loses their original wager of "
                         << color_text(33, round_to_string(playerHand.player.hand_wager));
                    time_sleep(1000);
                    playerHand.Update_Bank("L", playerHand, playerHand.player.hand_wager);
                    float final_net = playerHand.player.bank_total - prior_bank_total;
                    cout << ". " << playerHand.player.name << " nets "
                         << color_text(33, round_to_string(final_net)) << " this hand." << endl
                         << "\n" "Here are the final hands of the players:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("final", "Show");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand))) {
                    hand_continue = false;
                    cout << endl << playerHand.player.name << " has blackjack and " << dealerHand.player.name
                         << " does not. " << playerHand.player.name << " wins their original wager of "
                         << color_text(33, round_to_string(1.5*playerHand.player.hand_wager));
                    time_sleep(1000);
                    playerHand.Update_Bank("B", playerHand, playerHand.player.hand_wager);
                    float final_net = playerHand.player.bank_total - prior_bank_total;
                    cout << ". " << playerHand.player.name << " nets "
                         << color_text(33, round_to_string(final_net)) << " this hand." << endl
                         << "\n" "Here are the final hands of the players:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("final", "Show");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand))) {
                    hand_continue = true;
                    cout << endl << dealerHand.player.name << " does not have blackjack. "
                         << "The hand will continue." "\n" << endl;
                    time_sleep(1000);
                    cout << "Here are the current hands of each player:" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("initial");
                    time_sleep(1000);
                    dealerHand.Show_Hand("initial");
                    return make_tuple(playerHand, dealerHand, hand_continue, shoe);
                }
                else {}
            }
        }
        else if (playerHand.player.bank_total < 0.5*playerHand.player.hand_wager) {
            time_sleep(1000);
            if (check_blackjack(dealerHand) && check_blackjack(playerHand)) {
                hand_continue = false;
                cout << endl << "Both players have blackjack. " << playerHand.player.name << " pushes their "
                     << "original wager of "
                     << color_text(33, round_to_string(playerHand.player.hand_wager));
                time_sleep(1000);
                playerHand.Update_Bank("P", playerHand, playerHand.player.hand_wager);
                float final_net = playerHand.player.bank_total - prior_bank_total;
                cout << ". " << playerHand.player.name << " nets "
                     << color_text(33, round_to_string(final_net)) << " this hand." << endl
                     << "\n" "Here are the final hands of the players:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
                time_sleep(1000);
                dealerHand.Show_Hand("final", "Show");
                return make_tuple(playerHand, dealerHand, hand_continue, shoe);
            }
            else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand))) {
                hand_continue = false;
                cout << endl << dealerHand.player.name << " has blackjack but " << playerHand.player.name
                     << " does not. " << playerHand.player.name << " loses their original wager of "
                     << color_text(33, round_to_string(playerHand.player.hand_wager));
                time_sleep(1000);
                playerHand.Update_Bank("L", playerHand, playerHand.player.hand_wager);
                float final_net = playerHand.player.bank_total - prior_bank_total;
                cout << ". " << playerHand.player.name << " nets "
                     << color_text(33, round_to_string(final_net)) << " this hand." << endl
                     << "\n" "Here are the final hands of the players:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
                time_sleep(1000);
                dealerHand.Show_Hand("final", "Show");
                return make_tuple(playerHand, dealerHand, hand_continue, shoe);
            }
            else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand))) {
                hand_continue = false;
                cout << endl << playerHand.player.name << " has blackjack and " << dealerHand.player.name
                     << " does not. " << playerHand.player.name << " wins their original wager of "
                     << color_text(33, round_to_string(1.5*playerHand.player.hand_wager));
                time_sleep(1000);
                playerHand.Update_Bank("B", playerHand, playerHand.player.hand_wager);
                float final_net = playerHand.player.bank_total - prior_bank_total;
                cout << ". " << playerHand.player.name << " nets "
                     << color_text(33, round_to_string(final_net)) << " this hand." << endl
                     << "\n" "Here are the final hands of the players:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
                time_sleep(1000);
                dealerHand.Show_Hand("final", "Show");
                return make_tuple(playerHand, dealerHand, hand_continue, shoe);
            }
            else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand))) {
                hand_continue = true;
                return make_tuple(playerHand, dealerHand, hand_continue, shoe);
            }
            else {}
        }
    }
    else if (!check_card_parameter(dealerHand.player.cards.at(1).card.rank, "Ace")) {
        time_sleep(1000);
        if (check_blackjack(dealerHand) && check_blackjack(playerHand)) {
            hand_continue = false;
            cout << endl << "Both players have blackjack. " << playerHand.player.name << " pushes their "
                 << "original wager of "
                 << color_text(33, round_to_string(playerHand.player.hand_wager));
            time_sleep(1000);
            playerHand.Update_Bank("P", playerHand, playerHand.player.hand_wager);
            float final_net = playerHand.player.bank_total - prior_bank_total;
            cout << ". " << playerHand.player.name << " nets "
                 << color_text(33, round_to_string(final_net)) << " this hand." << endl
                 << "\n" "Here are the final hands of the players:" << endl;
            time_sleep(1000);
            playerHand.Show_Hand("final");
            time_sleep(1000);
            dealerHand.Show_Hand("final", "Show");
            return make_tuple(playerHand, dealerHand, hand_continue, shoe);
        }
        else if (check_blackjack(dealerHand) && !(check_blackjack(playerHand))) {
            hand_continue = false;
            cout << endl << dealerHand.player.name << " has blackjack but " << playerHand.player.name
                 << " does not. " << playerHand.player.name << " loses their original wager of "
                 << color_text(33, round_to_string(playerHand.player.hand_wager));
            time_sleep(1000);
            playerHand.Update_Bank("L", playerHand, playerHand.player.hand_wager);
            float final_net = playerHand.player.bank_total - prior_bank_total;
            cout << ". " << playerHand.player.name << " nets "
                 << color_text(33, round_to_string(final_net)) << " this hand." << endl
                 << "\n" "Here are the final hands of the players:" << endl;
            time_sleep(1000);
            playerHand.Show_Hand("final");
            time_sleep(1000);
            dealerHand.Show_Hand("final", "Show");
            return make_tuple(playerHand, dealerHand, hand_continue, shoe);
        }
        else if (!check_blackjack(dealerHand) && (check_blackjack(playerHand))) {
            hand_continue = false;
            cout << endl << playerHand.player.name << " has blackjack and " << dealerHand.player.name
                 << " does not. " << playerHand.player.name << " wins their original wager of "
                 << color_text(33, round_to_string(1.5*playerHand.player.hand_wager));
            time_sleep(1000);
            playerHand.Update_Bank("B", playerHand, playerHand.player.hand_wager);
            float final_net = playerHand.player.bank_total - prior_bank_total;
            cout << ". " << playerHand.player.name << " nets "
                 << color_text(33, round_to_string(final_net)) << " this hand." << endl
                 << "\n" "Here are the final hands of the players:" << endl;
            time_sleep(1000);
            playerHand.Show_Hand("final");
            time_sleep(1000);
            dealerHand.Show_Hand("final", "Show");
            return make_tuple(playerHand, dealerHand, hand_continue, shoe);
        }
        else if (!(check_blackjack(dealerHand)) && !(check_blackjack(playerHand))) {
            hand_continue = true;
            return make_tuple(playerHand, dealerHand, hand_continue, shoe);
        }
        else {}
    }
    else {}
}
// Split hand method
/*
 * This method takes a hand from a player and splits it, creating new hands
 * It copies the name of the original player, as well as the wager placed, and subtracts the total from the bank
 * This method will work even if the card is not of the same rank
 * This method will return a boolean value that determines if the hand has been split as well as
 * returning a vector of Hand objects if a player chooses to split
 */
tuple<vector<Hand>, bool> split_hand(Hand& inputHand, Hand& referenceHand) {
    vector<Hand> hands;
    bool split_result = true;
    referenceHand.player.bank_total -= referenceHand.player.hand_wager;
    for (Card card : inputHand.player.cards) {
        Hand current_hand;
        current_hand.player.cards.push_back(card);
        current_hand.player.name = referenceHand.player.name;
        current_hand.player.hand_wager = referenceHand.player.hand_wager;
        current_hand.player.bank_total = referenceHand.player.bank_total;
        hands.push_back(current_hand);
    }
    return make_tuple(hands, split_result);
}
// Check for if a player has the same rank in their dealt hand method
/*
* This method checks if a player has the same rank in their hand
* If a player does have the same rank, it then checks if the player has enough money left in their bank to split
* If the last two conditions are met, then the player is prompted to whether or not they would like to split their hand
* It then processes logic as to whether or not the player can continue to split their hand
* The player can split their hand up to 4 times and can only continue splitting their hand if they are given another card of the same rank
* The method will then return a vector of hands, dealer hand, a boolean for if the player split aces, if the player split a hand in general, the game shoe,
* And the number of hands that the player now has
* The boolean for splitting aces can only be true if the player splits aces
* The boolean for splitting a hand can be true if the player splits their aces or another hand of a different rank
*/
tuple<vector<Hand>, Hand, bool, bool, Shoe, int> player_same_rank(Hand& playerHand, Hand& dealerHand, Shoe& shoe) {
    bool player_split_aces = false;
    bool player_split_hand = false;
    int hand_count = 1;
    vector<Hand> new_hand;
    if (playerHand.player.bank_total >= playerHand.player.hand_wager) {
        if (check_same_parameter_in_hand(playerHand, "R", "Ace")) {
            string aces_response;
            while (aces_response.empty()) {
                cout << "\n" "You have the same rank of " << playerHand.player.cards[0].display_rank << " in your hand." << endl;
                blackjack_logic(playerHand,dealerHand,false);
                cout << endl << "Would you like to split your hand? You may only split your hand once (y/n): ";
                cin >> aces_response;
                cout << endl;
                if (aces_response == "y") {
                    auto split_aces = split_hand(playerHand, playerHand);
                    Hand player_hand_1 = get<0>(split_aces).at(0);
                    Hand player_hand_2 = get<0>(split_aces).at(1);
                    player_split_aces = get<1>(split_aces);
                    player_split_hand = get<1>(split_aces);
                    player_hand_1.Hit(shoe);
                    player_hand_2.Hit(shoe);
                    new_hand.push_back(player_hand_1);
                    new_hand.push_back(player_hand_2);
                    hand_count = 2;
                    time_sleep(1000);
                    cout << playerHand.player.name << " has chosen to split their " << playerHand.player.cards[0].display_rank << "'s." << endl;
                    time_sleep(1000);
                    cout << endl << "Here are the current hands of both players: " << endl;
                    int loop_counter = 1;
                    string hand_tracker;
                    for (Hand& current_hand : new_hand) {
                        time_sleep(1000);
                        if (loop_counter == 1) {
                            hand_tracker = "first";
                        }
                        else if (loop_counter == 2) {
                            hand_tracker = "second";
                        }
                        else {}
                        current_hand.Show_Hand(hand_tracker);
                        loop_counter ++;
                    }
                    time_sleep(1000);
                    dealerHand.Show_Hand();
                    return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
                }
                else if (aces_response == "n") {
                    new_hand.push_back(playerHand);
                    time_sleep(1000);
                    cout << playerHand.player.name << " has chosen not to split their " << playerHand.player.cards[0].display_rank << "'s." << endl;
                    time_sleep(1000);
                    return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
                }
                else {
                    cout << color_text(31, "Invalid choice") + " of "
                    + color_text(31, aces_response) + ". Plese re-enter your decision." "\n" << endl;
                    aces_response.clear();
                }
            }
        }
        else if (check_same_parameter_in_hand(playerHand, "R") && !check_card_parameter(playerHand.player.cards[0].card.rank, "Ace")) {
            string same_rank_response;
            while (same_rank_response.empty()) {
                cout << "\n" "You have the same rank of " << playerHand.player.cards[0].display_rank << " in your hand." << endl;
                blackjack_logic(playerHand,dealerHand,false);
                cout << endl << "Would you like to split your hand? You may split up to a total of four times. (y/n): ";
                cin >> same_rank_response;
                if (same_rank_response == "y") {
                    time_sleep(1000);
                    cout << endl << playerHand.player.name << " has chosen to split their hand." << endl;
                    time_sleep(1000);
                    int split_counter = 1;
                    hand_count++;
                    auto initial_split = split_hand(playerHand, playerHand);
                    vector<Hand> split_hands;
                    vector<Hand> temp_hands;
                    Hand player_hand_1 = get<0>(initial_split).at(0);
                    Hand player_hand_2 = get<0>(initial_split).at(1);
                    Hand checking_hand;
                    player_split_hand = get<1>(initial_split);
                    player_hand_2.Hit(shoe);
                    temp_hands.push_back(player_hand_2);
                    temp_hands.push_back(player_hand_1);
                    checking_hand = player_hand_2;
                    if (check_same_parameter_in_hand(checking_hand, "R")) {
                        if (playerHand.player.bank_total >= playerHand.player.hand_wager) {
                            cout << endl << "Total times split: " << color_text(31, to_string(split_counter)) << ". Your current hand(s) are:" << endl;
                            int loop_counter = 1;
                            string hand_tracker;
                            for (Hand& current_hand : temp_hands) {
                                if (loop_counter == 1) {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2) {
                                    hand_tracker = "second";
                                }
                                else {}
                                time_sleep(1000);
                                current_hand.Show_Hand(hand_tracker);
                                loop_counter++;
                            }
                            temp_hands.clear();
                            while (split_counter < 4 && check_same_parameter_in_hand(checking_hand, "R")) {
                                string split_again;                                
                                while (split_again != "y" || split_again != "n") {
                                    time_sleep(1000);
                                    cout << endl << "You have pulled the same rank of " << checking_hand.player.cards[0].display_rank << " again." << endl;
                                    blackjack_logic(checking_hand,dealerHand,false);
                                    cout << endl << "Would you like to split your current hand again? (y/n): ";
                                    cin >> split_again;
                                    cout << endl;
                                    if (split_again == "y") {
                                        split_counter++;
                                        hand_count++;
                                        auto new_split = split_hand(checking_hand, playerHand);
                                        Hand new_player_hand_1 = get<0>(new_split).at(0);
                                        Hand new_player_hand_2 = get<0>(new_split).at(1);
                                        new_player_hand_2.Hit(shoe);
                                        split_hands.insert(split_hands.begin(), new_player_hand_1);
                                        checking_hand = new_player_hand_2;
                                        break;
                                    }
                                    else if (split_again == "n") {
                                        break;
                                    }
                                    else {
                                        cout << color_text(31, "Invalid entry") << ". Please enter a valid choice." << endl;
                                        split_again.clear();
                                    }
                                }
                                split_hands.insert(split_hands.begin(), checking_hand);
                                split_hands.insert(split_hands.end(), player_hand_1);
                                for (int i = 0; i < split_hands.size(); i++) {
                                    split_hands.at(i).player.bank_total = playerHand.player.bank_total;
                                }
                                if (check_same_parameter_in_hand(checking_hand, "R") && split_again == "y") {
                                    if (split_counter < 4 && playerHand.player.bank_total >= playerHand.player.hand_wager) {
                                        time_sleep(1000);
                                        cout << playerHand.player.name << " has chosen to split their hand again." << endl;
                                        time_sleep(1000);
                                        cout << endl << "Total times split: " << color_text(31, to_string(split_counter)) << ". Your current hand(s) are:" << endl;
                                        int loop_counter = 1;
                                        string hand_tracker;
                                        for (Hand& current_hand : split_hands) {
                                            if (loop_counter == 1) {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2) {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3) {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4) {
                                                hand_tracker = "fourth";
                                            }
                                            else {
                                                hand_tracker = "current";
                                            }
                                            time_sleep(1000);
                                            current_hand.Show_Hand(hand_tracker);
                                            loop_counter++;
                                        }
                                        split_hands.erase(split_hands.begin());
                                        split_hands.pop_back();
                                        continue;
                                    }
                                    else if (split_counter == 4 || playerHand.player.bank_total < playerHand.player.hand_wager) {
                                        if (split_counter == 4) {
                                            time_sleep(1000);
                                            cout << playerHand.player.name << " has reached the max amount of times to split." << endl;
                                            time_sleep(1000);
                                            cout << endl << "Total times split: " << color_text(31, to_string(split_counter)) << ". Your current hand(s) are:" << endl;
                                            int loop_counter = 1;
                                            string hand_tracker;
                                            for (Hand& current_hand : split_hands) {
                                                if (loop_counter == 1) {
                                                    hand_tracker = "first";
                                                }
                                                else if (loop_counter == 2) {
                                                    hand_tracker = "second";
                                                }
                                                else if (loop_counter == 3) {
                                                    hand_tracker = "third";
                                                }
                                                else if (loop_counter == 4) {
                                                    hand_tracker = "fourth";
                                                }
                                                else if (loop_counter == 5) {
                                                    hand_tracker = "fifth";
                                                }
                                                else {
                                                    hand_tracker = "current";
                                                }
                                                time_sleep(1000);
                                                current_hand.Show_Hand(hand_tracker);
                                                loop_counter++;
                                            }
                                            cout << endl;
                                        }
                                        else if (playerHand.player.bank_total < playerHand.player.hand_wager) {
                                            cout << "Your current bank balance of " << color_text(31, round_to_string(playerHand.player.bank_total)) << " is not greater than"
                                            << " your wager of " << color_text(31, round_to_string(playerHand.player.hand_wager))
                                            << ". You can no longer split your hands. Total times split: " << color_text(31, to_string(split_counter))
                                            << ". Your current hand(s) are:" << endl;
                                            int loop_counter = 1;
                                            string hand_tracker;
                                            for (Hand& current_hand : split_hands) {
                                                if (loop_counter == 1) {
                                                    hand_tracker = "first";
                                                }
                                                else if (loop_counter == 2) {
                                                    hand_tracker = "second";
                                                }
                                                else if (loop_counter == 3) {
                                                    hand_tracker = "third";
                                                }
                                                else if (loop_counter == 4) {
                                                    hand_tracker = "fourth";
                                                }
                                                else {
                                                    hand_tracker = "current";
                                                }
                                                time_sleep(1000);
                                                current_hand.Show_Hand(hand_tracker);
                                                loop_counter++;
                                            }
                                            cout << endl;
                                        }
                                        break;
                                    }
                                    else {}
                                }
                                else if (!check_same_parameter_in_hand(checking_hand, "R") || split_again == "n") {
                                    if (!check_same_parameter_in_hand(checking_hand, "R")) {
                                        cout << "You did not pull the same rank of " << checking_hand.player.cards[0].display_rank << " again. "
                                        << "You can no longer split your hands. Total times split: " << color_text(31, to_string(split_counter))
                                        << ". Your current hand(s) are: " << endl;
                                        int loop_counter = 1;
                                        string hand_tracker;
                                        for (Hand& current_hand : split_hands) {
                                            if (loop_counter == 1) {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2) {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3) {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4) {
                                                hand_tracker = "fourth";
                                            }
                                            else {
                                                hand_tracker = "current";
                                            }                                                
                                            time_sleep(1000);
                                            current_hand.Show_Hand(hand_tracker);
                                            loop_counter++;
                                        }
                                        cout << endl;
                                    }
                                    else if (split_again == "n") {
                                        cout << playerHand.player.name << " has chosen not to split their hand again." << endl;
                                        cout << endl << "Total times split: " << color_text(31, to_string(split_counter))
                                        << ". Your current hand(s) are:" << endl;
                                        int loop_counter = 1;
                                        string hand_tracker;                                            
                                        for (Hand& current_hand : split_hands) {
                                            if (loop_counter == 1) {
                                                hand_tracker = "first";
                                            }
                                            else if (loop_counter == 2) {
                                                hand_tracker = "second";
                                            }
                                            else if (loop_counter == 3) {
                                                hand_tracker = "third";
                                            }
                                            else if (loop_counter == 4) {
                                                hand_tracker = "fourth";
                                            }
                                            else {
                                                hand_tracker = "current";
                                            }                                                  
                                            time_sleep(1000);
                                            current_hand.Show_Hand(hand_tracker);
                                            loop_counter++;
                                        }
                                        cout << endl;
                                    }
                                    else {}
                                    break;
                                }
                            }
                            new_hand = split_hands;
                            return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
                        }
                        else if (playerHand.player.bank_total < playerHand.player.hand_wager) {
                            time_sleep(1000);
                            cout << endl << "You have pulled the same rank of " << checking_hand.player.cards[0].display_rank << " again." << endl;
                            int loop_counter = 1;
                            string hand_tracker;
                            for (Hand& current_hand : temp_hands) {
                                if (loop_counter == 1) {
                                    hand_tracker = "first";
                                }
                                else if (loop_counter == 2) {
                                    hand_tracker = "second";
                                }
                                else {
                                    hand_tracker = "current";
                                }
                                time_sleep(1000);
                                current_hand.Show_Hand(hand_tracker);
                                loop_counter++;
                            }
                            time_sleep(1000);
                            cout << endl << "Your current bank balance of " << color_text(31, round_to_string(playerHand.player.bank_total)) << " is not"
                            << " greater than your wager of " << color_text(31, round_to_string(playerHand.player.hand_wager))
                            << ". You can no longer split your hands. Total times split: " << color_text(31, to_string(split_counter)) << endl;
                            new_hand = temp_hands;
                            return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
                        }
                        else {}
                    }
                    else if (!check_same_parameter_in_hand(checking_hand, "R")) {
                        new_hand.insert(new_hand.begin(), checking_hand);
                        new_hand.push_back(player_hand_1);
                        time_sleep(1000);
                        cout << endl << "Total times split: " << color_text(31, to_string(split_counter)) << ". Your current hand(s) are:" << endl;
                        int loop_counter = 1;
                        string hand_tracker;
                        for (Hand& current_hand : new_hand) {
                            if (loop_counter == 1) {
                                hand_tracker = "first";
                            }
                            else if (loop_counter == 2) {
                                hand_tracker = "second";
                            }
                            else {}
                            time_sleep(1000);
                            current_hand.Show_Hand(hand_tracker);
                            loop_counter++;
                        }
                        cout << endl;
                        return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
                    }
                    else {}
                }
                else if (same_rank_response == "n") {
                    new_hand.push_back(playerHand);
                    time_sleep(1000);
                    cout << endl << playerHand.player.name << " has chosen not to split their hand." << endl;
                    time_sleep(1000);
                    return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
                }
                else {
                    cout << endl << color_text(31, "Invalid choice") + " of "
                    + color_text(31, same_rank_response) + ". Plese re-enter your decision." << endl;
                    same_rank_response.clear();
                }
            }
        }
        else if (!check_same_parameter_in_hand(playerHand, "R")) {
            new_hand.push_back(playerHand);
            return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
        }
        else {}
    }
    else if (playerHand.player.bank_total < playerHand.player.hand_wager) {
        if (check_same_parameter_in_hand(playerHand, "R")) {
            cout << endl << "You have pulled the same rank of " << playerHand.player.cards[0].display_rank << " but your current bank balance of "
            << color_text(33, round_to_string(playerHand.player.bank_total)) << " is not greater than your wager of "
            << color_text(31, round_to_string(playerHand.player.hand_wager)) << ". You cannot split your hand." << endl;
            time_sleep(1000);
        }
        else {}
        new_hand.push_back(playerHand);
        return make_tuple(new_hand, dealerHand, player_split_aces, player_split_hand, shoe, hand_count);
    }
    else {}
}
// Hand logic method
/*
* This method processes the logic for if a player wants to hit, stand, or double down on a current hand
* The method takes in a player hand, dealer hand, shoe, and boolean value as an input
* The boolean value is used to determine how a dealer hand should be displayed under certain conditions
* The hands of the player are modified along with the shoe that is being used in game
* The method will return a modified player hand, dealer hand, and a modified shoe
* Depending on certain conditions, a player will have the option to hit, stand, or double down on the current hand that
* is fed into the method
*/
tuple<Hand, Hand, Shoe> player_hand_logic(Hand& playerHand, Hand& dealerHand, bool split_hand, Shoe& shoe, int& hand_counter) {
    bool has_hit = false;
    string response;
    string hand_tracker;
    if (hand_counter == 1) {
        hand_tracker = "first";
    }
    else if (hand_counter == 2) {
        hand_tracker = "second";
    }
    else if (hand_counter == 3) {
        hand_tracker = "third";
    }
    else if (hand_counter == 4) {
        hand_tracker = "fourth";
    }
    else if (hand_counter == 5) {
        hand_tracker = "fifth";
    }
    else {
        hand_tracker = "current";
    }
    if (hand_counter > 1) {
        playerHand.Hit(shoe);
    }
    else {}
    while ((response != "h" && response != "s" && response != "d") && playerHand.player.cards_total < 21) {
        if (!has_hit) {
            if (split_hand) {
                cout << "Here are the initial hands of each player for hand " << to_string(hand_counter) << ":" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("initial " + hand_tracker);
                time_sleep(1000);
                dealerHand.Show_Hand("initial");
                time_sleep(1000);
                cout << endl << "Would you like to hit, stand, or double down for hand " << to_string(hand_counter) << "?" << endl;
                blackjack_logic(playerHand,dealerHand,true);
                cout << endl << "Enter (h) to hit, (s) to stand, and (d) to double down for " << to_string(hand_counter) << ": ";
                cin >> response;
                cout << endl;
            }
            else if (!split_hand) {
                cout << endl << "Would you like to hit, stand, or double down?" << endl;
                blackjack_logic(playerHand,dealerHand,false);
                cout << endl << "Enter (h) to hit, (s) to stand, and (d) to double down: ";
                cin >> response;
                cout << endl;
            }
            else {}
        }
        else if (has_hit) {
            time_sleep(1000);
            if (split_hand) {
                playerHand.Show_Hand("current " + hand_tracker);
            }
            else if (!split_hand) {
                playerHand.Show_Hand("current");
            }
            else {}
            time_sleep(1000);
            dealerHand.Show_Hand("initial");
            time_sleep(1000);
            cout << endl << "Would you like to hit (h) or stand (s)?" << endl;
            blackjack_logic(playerHand,dealerHand,has_hit);
            cout << endl << "Enter (h) to hit and (s) to stand: ";
            cin >> response;
            cout << endl;
        }
        else {}
        if (response == "h") {
            has_hit = true;
            playerHand.Hit(shoe);
            if (playerHand.player.cards_total > 21) {
                time_sleep(1000);
                cout << playerHand.player.name << " has chosen to hit and busted. Final hand total: " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                if (split_hand) {
                    cout << endl << "Here is " << playerHand.player.name << "'s final hand for hand " << to_string(hand_counter) 
                    << " and the " << dealerHand.player.name << "'s current hand:" << endl; 
                    time_sleep(1000);
                    playerHand.Show_Hand("final " + hand_tracker);
                    time_sleep(1000);
                    dealerHand.Show_Hand("current");
                }
                else if (!split_hand) {
                    cout << endl << "Here is the final hand for " << playerHand.player.name << " and the final hand of the " << dealerHand.player.name << ":" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("final", "show");
                }
                else {}
                time_sleep(1000);
                cout << endl;
                break;
            }
            else if (playerHand.player.cards_total < 21) {
                time_sleep(1000);
                cout << playerHand.player.name << " has chosen to hit. Current hand total: " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                if (split_hand) {
                    cout << endl << "Here are the current hands of each player for hand " << to_string(hand_counter) << ":" << endl;
                }
                else if (!split_hand) {
                    cout << endl << "Here are the current hands of each player:" << endl;
                }
                else {}
            }
            else if (playerHand.player.cards_total == 21) {
                time_sleep(1000);
                cout << playerHand.player.name << " has chosen to hit. Final hand total: " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                if (split_hand) {
                    cout << endl << "Here is " << playerHand.player.name << "'s final hand for hand " << to_string(hand_counter) 
                    << " and the " << dealerHand.player.name << "'s current hand:" << endl; 
                    time_sleep(1000);
                    playerHand.Show_Hand("final " + hand_tracker);
                    time_sleep(1000);
                    dealerHand.Show_Hand("current", "");
                }
                else if (!split_hand) {
                    cout << endl << "Here is the final hand for " << playerHand.player.name << " and the initial hand of the " << dealerHand.player.name << ":" << endl;
                    time_sleep(1000);
                    playerHand.Show_Hand("final");
                    time_sleep(1000);
                    dealerHand.Show_Hand("initial", "show");
                }
                else {}
                cout << endl;
            }
            else {}
            response.clear();
        }
        else if (response == "s") {
            time_sleep(1000);
            cout << playerHand.player.name << " has chosen to stand. Final hand total: " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
            time_sleep(1000);
            if (split_hand) {
                cout << endl << "Here is " << playerHand.player.name << "'s final hand for hand " << to_string(hand_counter) 
                << " and the " << dealerHand.player.name << "'s current hand:" << endl; 
                time_sleep(1000);
                playerHand.Show_Hand("final " + hand_tracker);
                time_sleep(1000);
                dealerHand.Show_Hand("current", "");
            }
            else if (!split_hand) {
                cout << endl << "Here is the final hand for " << playerHand.player.name << " and the initial hand of the " << dealerHand.player.name << ":" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
                time_sleep(1000);
                dealerHand.Show_Hand("initial", "show");
            }
            else {}
            cout << endl;
            time_sleep(1000);
            break;
        }
        else if (response == "d" && !has_hit) {
            if (playerHand.player.bank_total >= playerHand.player.hand_wager) {
                playerHand.player.bank_total -= playerHand.player.hand_wager;
                playerHand.player.hand_wager *= 2;
                playerHand.Hit(shoe);
                if (playerHand.player.cards_total > 21) {
                    playerHand.Update_Bank("L", playerHand, playerHand.player.hand_wager);
                    time_sleep(1000);
                    cout << playerHand.player.name << " has doubled down and busted. Final hand total: " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                    time_sleep(1000);
                    if (split_hand) {
                        cout << endl << "Here is " << playerHand.player.name << "'s final hand for hand " << to_string(hand_counter) 
                        << " and the " << dealerHand.player.name << "'s current hand:" << endl; 
                        time_sleep(1000);
                        playerHand.Show_Hand("final " + hand_tracker);
                        time_sleep(1000);
                        dealerHand.Show_Hand("current");
                    }
                    else if (!split_hand) {
                        cout << endl << "Here is the final hand for " << playerHand.player.name << " and the final hand of the " << dealerHand.player.name << ":" << endl;
                        time_sleep(1000);
                        playerHand.Show_Hand("final");
                        time_sleep(1000);
                        dealerHand.Show_Hand("final", "show");
                    }
                    else {}
                    cout << endl;
                    break;
                }
                else if (playerHand.player.cards_total <= 21) {
                    time_sleep(1000);
                    cout << playerHand.player.name << " has doubled down. Final hand total: " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                    time_sleep(1000);
                    if (split_hand) {
                        cout << endl << "Here is " << playerHand.player.name << "'s final hand for hand " << to_string(hand_counter) 
                        << " and the " << dealerHand.player.name << "'s current hand:" << endl; 
                        time_sleep(1000);
                        playerHand.Show_Hand("final " + hand_tracker);
                        time_sleep(1000);
                        dealerHand.Show_Hand("current");
                    }
                    else if (!split_hand) {
                        cout << endl << "Here is the final hand for " << playerHand.player.name << " and the initial hand of the " << dealerHand.player.name << ":" << endl;
                        time_sleep(1000);
                        playerHand.Show_Hand("final");
                        time_sleep(1000);
                        dealerHand.Show_Hand("initial", "show");
                    }
                    else {}
                    cout << endl;
                    time_sleep(1000);
                    break;
                }
                else {}
            }
            else if (playerHand.player.bank_total < playerHand.player.hand_wager) {
                time_sleep(1000);
                cout << "Your current bank total of " << color_text(33, round_to_string(playerHand.player.bank_total)) << " is not greater than your wager of "
                << color_text(31, round_to_string(playerHand.player.hand_wager)) << ". You cannot double down." << endl;
                response.clear();
                continue;
            }
            else {}
        }
        else if (response != "h" && response != "s" && response != "d") {
            if (!split_hand) {
                cout << color_text(31, "Invalid choice") << "." << endl;
            }
            else if (split_hand) {
                cout << color_text(31, "Invalid choice") << "." "\n" << endl;
            }
            else {}
            response.clear();
            continue;
        }
        else {}
    }
    return make_tuple(playerHand, dealerHand, shoe);
}
// Dealer hand logic method
/*
* This method processes the logic of when and how a dealer plays their hand
* The method then returns a modified dealer hand as well as a modificed game shoe
*/
tuple<Hand, Shoe> dealer_hand_logic(vector<Hand>& playerHands, Hand& dealerHand, Shoe& shoe) {
    bool all_over_21 = true;
    for (Hand current_hand : playerHands) {
        if (current_hand.player.cards_total <= 21) {
            all_over_21 = false;
            break;
        }
        else if (current_hand.player.cards_total > 21) {
            all_over_21 = true;
            continue;
        }
        else {}
    }
    if (!all_over_21) {
        if ((dealerHand.player.cards_total >= 17 && !check_parameter_in_hand(dealerHand, "R", "Ace")) || (dealerHand.player.cards_total > 17 && check_parameter_in_hand(dealerHand, "R", "Ace"))) {
            int total_hands = playerHands.size();
            if (total_hands > 1) {
                time_sleep(1000);
                int hand_counter = 0;
                string hand_tracker;
                cout << "Here are the final hand(s) of " << playerHands.at(0).player.name << " and the " << dealerHand.player.name << ":" << endl;
                for (Hand current_hand : playerHands) {
                    hand_counter++;
                    if (hand_counter == 1) {
                        hand_tracker = " first";
                    }
                    else if (hand_counter == 2) {
                        hand_tracker = " second";
                    }
                    else if (hand_counter == 3) {
                        hand_tracker = " third";
                    }
                    else if (hand_counter == 4) {
                        hand_tracker = " fourth";
                    }
                    else if (hand_counter == 5) {
                        hand_tracker = " fifth";
                    }
                    else {}
                    time_sleep(1000);
                    current_hand.Show_Hand("final" + hand_tracker);
                }
                time_sleep(1000);
                dealerHand.Show_Hand("final", "show");
                time_sleep(1000);
                cout << endl << "The " << dealerHand.player.name << " does not need to play their hand with a final total of " << color_text(36, to_string(dealerHand.player.cards_total)) << "." "\n" << endl;
            }
            else {
                cout << "The " << dealerHand.player.name << " does not need to play their hand with a final total of " << color_text(36, to_string(dealerHand.player.cards_total)) << "." "\n" << endl;
            }
        }
        else if (dealerHand.player.cards_total < 17 || (dealerHand.player.cards_total == 17 && check_parameter_in_hand(dealerHand, "R", "Ace"))) {
            int total_hands = playerHands.size();
            if (total_hands > 1) {
                time_sleep(1000);
                int hand_counter = 0;
                string hand_tracker;
                cout << "Here are the final hand(s) of " << playerHands.at(0).player.name << " and the initial hand of the " << dealerHand.player.name << ":" << endl;
                for (Hand current_hand : playerHands) {
                    hand_counter++;
                    if (hand_counter == 1) {
                        hand_tracker = " first";
                    }
                    else if (hand_counter == 2) {
                        hand_tracker = " second";
                    }
                    else if (hand_counter == 3) {
                        hand_tracker = " third";
                    }
                    else if (hand_counter == 4) {
                        hand_tracker = " fourth";
                    }
                    else if (hand_counter == 5) {
                        hand_tracker = " fifth";
                    }
                    else {}
                    time_sleep(1000);
                    current_hand.Show_Hand("final" + hand_tracker);
                }
                time_sleep(1000);
                dealerHand.Show_Hand("initial", "show");
                time_sleep(1000);
                cout << endl << "The " << dealerHand.player.name << " will now play their hand." "\n" << endl;
            }
            else {
                cout << "The " << dealerHand.player.name << " will now play their hand." "\n" << endl;
            }
            while ((dealerHand.player.cards_total < 17 || (dealerHand.player.cards_total <= 17 && check_parameter_in_hand(dealerHand, "R", "Ace")))) {
                bool aces_all_ones = true;
                for (Card current_card : dealerHand.player.cards) {
                    if (check_card_parameter(current_card.card.rank, "Ace")) {
                        current_card.card.card_value = 11;
                        aces_all_ones = false;
                        break;
                    }
                    else if (check_card_parameter(current_card.card.rank, "Ace")) {
                        current_card.card.card_value = 1;
                        aces_all_ones = true;
                        continue;
                    }
                    else {}                   
                }
                if (!aces_all_ones || !check_parameter_in_hand(dealerHand, "R", "Ace")) {
                    dealerHand.Hit(shoe);
                    time_sleep(1000);
                    cout << dealerHand.player.name << " hits hand: "; 
                    dealerHand.Show_Hand("", "cards");
                }
                else if (aces_all_ones) {
                    cout << dealerHand.player.name << " final hand ";
                    dealerHand.Show_Hand("", "cards");
                    break;
                }
            }
            cout << endl;
        }
        else {}
    }
    else if (all_over_21) {
        time_sleep(1000);
        cout << playerHands.at(0).player.name << " has busted on all of their hands. " << dealerHand.player.name << " does not need to play their hand." "\n" << endl;
        int total_hands = playerHands.size();
        if (total_hands > 1) {
            time_sleep(1000);
            int hand_counter = 0;
            string hand_tracker;
            cout << endl << "The final hands of " << playerHands.at(0).player.name << " and the " << dealerHand.player.name << " are:" << endl;
            for (Hand current_hand : playerHands) {
                hand_counter++;
                if (hand_counter == 1) {
                    hand_tracker = " first";
                }
                else if (hand_counter == 2) {
                    hand_tracker = " second";
                }
                else if (hand_counter == 3) {
                    hand_tracker = " third";
                }
                else if (hand_counter == 4) {
                    hand_tracker = " fourth";
                }
                else if (hand_counter == 5) {
                    hand_tracker = " fifth";
                }
                else {}
                time_sleep(1000);
                current_hand.Show_Hand("final" + hand_tracker);
            }
            time_sleep(1000);
            dealerHand.Show_Hand("final", "show");
            time_sleep(1000);
        }
        else {}
    }
    else {}
    return make_tuple(dealerHand, shoe);
}
// Hand comparison method
/*
* This method determines the result of a hand against the dealers hand
* It returns a modified player and dealer hand as well as modified shoe
* The player and dealer hand must be fed into this method as well as the shoe in the game
*/
tuple<Hand, Hand, Shoe> hand_comparison(Hand& playerHand, Hand& dealerHand, Shoe& shoe, int& playerHandCount, int& currentHandCounter) {
    float prior_bank = playerHand.player.bank_total + playerHand.player.hand_wager;
    float net = 0;
    string hand_tracker;
    bool multiple_hands = false;
    if (playerHandCount > 1) {
        multiple_hands = true;
        if (currentHandCounter == 1) {
            hand_tracker = " first";
        }
        else if (currentHandCounter == 2) {
            hand_tracker = " second";
        }
        else if (currentHandCounter == 3) {
            hand_tracker = " third";
        }
        else if (currentHandCounter == 4) {
            hand_tracker = " fourth";
        }
        else if (currentHandCounter == 5) {
            hand_tracker = " fifth";
        }
        else {
            hand_tracker.clear();
        }
    }
    else {}
    if (playerHand.player.cards_total <= 21) {
        if (playerHand.player.cards_total == dealerHand.player.cards_total) {
            playerHand.Update_Bank("P", playerHand, playerHand.player.hand_wager);
            net = playerHand.player.bank_total - prior_bank;
            time_sleep(1000);
            if (!multiple_hands) {
                cout << "Both players have the same final value of " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands) {
                cout << "Both players have the same final value of " << color_text(36, to_string(playerHand.player.cards_total)) << " for hand " << to_string(currentHandCounter)
                << ". " << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player for hand " << to_string(currentHandCounter) << " are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {}
            time_sleep(1000);
            dealerHand.Show_Hand("final", "show");
            time_sleep(1000);
            if (!multiple_hands) {
                cout << endl << "This hand is a push. " << playerHand.player.name << " nets " << color_text(31, round_to_string(net)) << " this hand." << endl;
            }
            else if (multiple_hands) {
                cout << endl << "Hand " << to_string(currentHandCounter) << " is a push. " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
                << " for hand " << to_string(currentHandCounter) << "." "\n" << endl;
            }
            else {}
        }
        else if (dealerHand.player.cards_total > playerHand.player.cards_total && dealerHand.player.cards_total <= 21) {
            playerHand.Update_Bank("L", playerHand, playerHand.player.hand_wager);
            net = playerHand.player.bank_total - prior_bank;
            time_sleep(1000);
            if (!multiple_hands) {
                cout << dealerHand.player.name << " has a greater final value of " << color_text(36, to_string(dealerHand.player.cards_total)) << " compared to "
                << playerHand.player.name << "'s final value of " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands) {
                cout << dealerHand.player.name << " has a greater final value of " << color_text(36, to_string(dealerHand.player.cards_total)) << " for hand " << to_string(currentHandCounter)
                << " compared to " << playerHand.player.name << "'s final value of " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player for hand " << to_string(currentHandCounter) << " are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {}
            time_sleep(1000);
            dealerHand.Show_Hand("final", "show");
            time_sleep(1000);
            if (!multiple_hands) {
                cout << endl << playerHand.player.name << " loses the current hand. " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
                << " this hand." << endl;
            }
            else if (multiple_hands) {
                cout << endl << playerHand.player.name << " loses hand " << to_string(currentHandCounter) << ". " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
                << " for hand " << to_string(currentHandCounter) << "." "\n" << endl;
            }
            else {}
        }
        else if (dealerHand.player.cards_total < playerHand.player.cards_total) {
            playerHand.Update_Bank("W", playerHand, playerHand.player.hand_wager);
            net = playerHand.player.bank_total - prior_bank;
            time_sleep(1000);
            if (!multiple_hands) {
                cout << playerHand.player.name << " has a greater final value of " << color_text(36, to_string(playerHand.player.cards_total)) << " compared to "
                << dealerHand.player.name << "'s final value of " << color_text(36, to_string(dealerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands) {
                cout << playerHand.player.name << " has a greater final value of " << color_text(36, to_string(playerHand.player.cards_total)) << " for hand " << to_string(currentHandCounter)
                << " compared to " << dealerHand.player.name << "'s final value of " << color_text(36, to_string(dealerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player for hand " << to_string(currentHandCounter) << " are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {}
            time_sleep(1000);
            dealerHand.Show_Hand("final", "show");
            time_sleep(1000);
            if (!multiple_hands) {
                cout << endl << playerHand.player.name << " wins the current hand. " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
                << " this hand." << endl;
            }
            else if (multiple_hands) {
                cout << endl << playerHand.player.name << " wins hand " << to_string(currentHandCounter) << ". " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
                << " for hand " << to_string(currentHandCounter) << "." "\n" << endl;
            }
            else {}
        }
        else if (dealerHand.player.cards_total > 21) {
            playerHand.Update_Bank("W", playerHand, playerHand.player.hand_wager);
            net = playerHand.player.bank_total - prior_bank;
            time_sleep(1000);
            if (!multiple_hands) {
                cout << dealerHand.player.name << " has busted with a final value of " << color_text(36, to_string(dealerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player for the current hand are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final");
            }
            else if (multiple_hands) {
                cout << dealerHand.player.name << " has busted with a final value of " << color_text(36, to_string(dealerHand.player.cards_total)) << "." << endl;
                time_sleep(1000);
                cout << endl << "The final hands of each player for hand " << to_string(currentHandCounter) << " are:" << endl;
                time_sleep(1000);
                playerHand.Show_Hand("final" + hand_tracker);
            }
            else {}
            time_sleep(1000);
            dealerHand.Show_Hand("final", "show");
            time_sleep(1000);
            if (!multiple_hands) {
                cout << endl << playerHand.player.name << " wins the current hand. " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
                << " this hand." << endl;
            }
            else if (multiple_hands) {
                cout << endl << playerHand.player.name << " wins hand " << to_string(currentHandCounter) << ". " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
                << " for hand " << to_string(currentHandCounter) << "." "\n" << endl;
            }
            else {}
        }
        else {}
    }
    else if (playerHand.player.cards_total > 21) {
        playerHand.Update_Bank("L", playerHand, playerHand.player.hand_wager);
        net = playerHand.player.bank_total - prior_bank;
        time_sleep(1000);
        if (!multiple_hands) {
            cout << playerHand.player.name << " has busted with a final value of " << color_text(36, to_string(playerHand.player.cards_total)) << "." << endl;
            time_sleep(1000);
            cout << endl << "The final hands of each player for the current hand are:" << endl;
            time_sleep(1000);
            playerHand.Show_Hand("final");
        }
        else if (multiple_hands) {
            cout << playerHand.player.name << " has busted with a final value of " << color_text(36, to_string(playerHand.player.cards_total)) << " for hand " << to_string(currentHandCounter) << "." << endl;
            time_sleep(1000);
            cout << endl << "The final hands of each player for hand " << to_string(currentHandCounter) << " are:" << endl;
            time_sleep(1000);
            playerHand.Show_Hand("final" + hand_tracker);
        }
        else {}
        time_sleep(1000);
        dealerHand.Show_Hand("final", "show");
        time_sleep(1000);
        if (!multiple_hands) {
            cout << endl << playerHand.player.name << " loses the current hand. " << playerHand.player.name << " nets " << color_text(31, round_to_string(net)) << " this hand." << endl;
        }
        else if (multiple_hands) {
            cout << endl << playerHand.player.name << " loses hand " << to_string(currentHandCounter) << ". " << playerHand.player.name << " nets " << color_text(31, round_to_string(net))
            << " for hand " << to_string(currentHandCounter) << "." "\n" << endl;
        }
        else {}
    }
    else {}
    return make_tuple(playerHand, dealerHand, shoe);
}
// Mini main method
/*
* This method includes all of the sub methods that are required to conduct the logic in playing blackjack
* This method takes in a player hand, dealer hand, and a shoe
* The first method that is used is the dealer_showing_ace method
* - This method checks if the dealer is showing an ace and determines if the hand should continue
* After dealer_showing_ace, player_same_rank is implemented to check if the player has the same rank in their hand
* - Players can decide if they would like to split their current hand in this method
* After player_same_rank, player_hand_logic is implemented
* - This method lets players decide if they want to hit, stand, or double down on their current hand
* Once the player is done playing in the player_hand_logic method, dealer_hand_logic is implemented
* - This method performs the necessary actions for what a dealer would do in a blackjack game
* After the dealer_hand_logic method, the hand comparison method is implemented for all player hands
* - This method determines if a player wins or loses their current hand(s)
* And finally, the player's bank and game shoe are updated to determine if the game will continue 
*/
tuple<Hand, Hand, Shoe> mini_main(Hand& playerHand, Hand& dealerHand, Shoe& shoe) {
    // Check if dealer is showing ace
    auto showing_ace_result = dealer_showing_ace(playerHand, dealerHand, shoe);
    Hand sa_player_hand = get<0>(showing_ace_result);
    Hand sa_dealer_hand = get<1>(showing_ace_result);
    bool sa_continue = get<2>(showing_ace_result);
    Shoe sa_shoe = get<3>(showing_ace_result);
    if (sa_continue) {
        // Player same rank check
        auto player_same_rank_result = player_same_rank(playerHand, dealerHand, sa_shoe);
        vector<Hand> psrr_player_hands = get<0>(player_same_rank_result);
        Hand psrr_dealer_hand = get<1>(player_same_rank_result);
        bool psrr_split_aces = get<2>(player_same_rank_result);
        bool psrr_split_hand = get<3>(player_same_rank_result);
        Shoe psrr_shoe = get<4>(player_same_rank_result);
        int hand_count = get<5>(player_same_rank_result);
        hand_count %= hand_count;
        // Player hand logic
        vector<Hand> phlr_player_hands;
        Hand phlr_dealer_hand;
        Shoe phlr_shoe;
        int loop_counter = 0;
        for (Hand current_hand : psrr_player_hands) {
            hand_count++;
            current_hand.player.bank_total = playerHand.player.bank_total;
            auto player_hand_logic_result = player_hand_logic(current_hand, psrr_dealer_hand, psrr_split_hand, psrr_shoe, hand_count);
            playerHand.player.bank_total = current_hand.player.bank_total;
            phlr_player_hands.insert(phlr_player_hands.begin(), get<0>(player_hand_logic_result));
            phlr_dealer_hand = move(get<1>(player_hand_logic_result));
            phlr_shoe = move(get<2>(player_hand_logic_result));
            loop_counter++;
        }
        reverse(phlr_player_hands.begin(), phlr_player_hands.end());
        for (int i = 0; i < phlr_player_hands.size(); i++) {
            phlr_player_hands.at(i).player.bank_total = playerHand.player.bank_total;
        }
        // Dealer hand logic
        auto dealer_hand_logic_result = dealer_hand_logic(phlr_player_hands, phlr_dealer_hand, phlr_shoe);
        Hand dhlr_dealer_hand = get<0>(dealer_hand_logic_result);
        Shoe dhlr_shoe = get<1>(dealer_hand_logic_result);
        // Hand comparison logic
        vector<Hand> hcr_player_hands;
        Hand hcr_dealer_hand;
        Shoe hcr_shoe;
        int player_hand_count = phlr_player_hands.size();
        int current_hand_counter = 1;
        for (Hand current_hand : phlr_player_hands) {
            current_hand.player.bank_total = playerHand.player.bank_total;
            auto hand_comparison_result = hand_comparison(current_hand, dhlr_dealer_hand, dhlr_shoe, player_hand_count, current_hand_counter);
            playerHand.player.bank_total = current_hand.player.bank_total;
            hcr_player_hands.insert(hcr_player_hands.begin(), get<0>(hand_comparison_result));
            hcr_dealer_hand = move(get<1>(hand_comparison_result));
            hcr_shoe = move(get<2>(hand_comparison_result));
            current_hand_counter++;
        }
        reverse(hcr_player_hands.begin(), hcr_player_hands.end());
        for (int i = 0; i < hcr_player_hands.size(); i++) {
            hcr_player_hands.at(i).player.bank_total = playerHand.player.bank_total;
        }
        // Update player and dealer hands as well as the shoe
        playerHand = hcr_player_hands.at(0);
        dealerHand = hcr_dealer_hand;
        shoe = hcr_shoe;
        }
    else if (!sa_continue) {
        // Update player and dealer hands as well as the shoe
        playerHand = sa_player_hand;
        dealerHand = sa_dealer_hand;
        shoe = sa_shoe;
    }
    else {}
    return make_tuple(playerHand, dealerHand, shoe);
}
// Game rules method
void game_rules() {
    clear_terminal();
    time_sleep(750);
    cout << "Welcome to " << color_text(32, "Blackjack") << " by " << color_text(31, "RelativiBit") << "." << endl;
    time_sleep(750);
    char info_input;
    while (true) {
        cout << endl << "To see the information about this game, please enter (i). Otherwise, (c) to continue to playing " << color_text(32, "Blackjack") << ": ";
        cin >> info_input;
        clear_terminal();
        if (info_input == 'i' || info_input == 'c') {
            false;
            break;
        }
        else {}
    }
    if (info_input == 'i') {
        cout << endl << "This game is designed to be played by a human player and an automated dealer." << endl;
        time_sleep(750);
        cout << endl << "You will first be prompted to enter a name for your player." << endl;
        time_sleep(750);
        cout << endl << "After your name has been entered, you will then be prompted to enter a bank total to be played with." << endl;
        time_sleep(750);
        cout << endl << "You will then be asked to enter the number of decks you would like to play with." << endl;
        time_sleep(750);
        cout << endl << "After this, you will be ready to play " << color_text(32, "Blackjack") << "." << endl;
        time_sleep(750);
        cout << endl << "This version of " << color_text(32, "Blackjack") << " includes hints to as to what players should do." << endl;
        time_sleep(750);
        char cont_input;
        while (true) {
            cout << endl << "Enter (c) to continue to the rules of this game: ";
            cin >> cont_input;
            clear_terminal();
            if (cont_input == 'c') {
                false;
                break;
            }
            else {}
        }
        cout << "The rules for this edition of " << color_text(32, "Blackjack") << " are as follows:" << endl;
        time_sleep(750);
        cout << endl << "The goal of this game is to get a higher final total than the dealer without going over a hand total of 21." << endl;
        time_sleep(750);
        cout << endl << "The dealer must hit on all soft 17's." << endl;
        time_sleep(750);
        cout << endl << color_text(32, "Blackjacks") << " pay 3:2." << endl;
        time_sleep(750);
        cout << endl << "Players have the option to split hands up to four times." << endl;
        time_sleep(750);
        cout << endl << "Players can continue playing until they choose to stop or until they run out of money." << endl;
        time_sleep(750);
        cout << endl << "Are you ready to play some " << color_text(32, "Blackjack") << "?" << endl;
        time_sleep(750);
        char playing_input;
        while (true) {
            cout << endl << "Enter (y) to proceed to playing " << color_text(32, "Blackjack") << ": ";
            cin >> playing_input;
            clear_terminal();
            if (playing_input == 'y') {
                false;
                break;
            }
            else {}
        }
        time_sleep(750);
        cout << endl << "Continuing to playing " << color_text(32, "Blackjack") << "." << endl;
        time_sleep(1500);
        clear_terminal();
    }
    else if (info_input == 'c') {
        time_sleep(750);
        cout << endl << "Continuing to playing " << color_text(32, "Blackjack") << "." << endl;
        time_sleep(1500);
        clear_terminal();
    }
    else {}
}
// Play game method
/*
 * Plays a game blackjack for two players, a user and a dealer
 * Creates a single hand for a human player, as well as a hand for the dealer
 * Creates a shoe of cards depending on the player's input
 * Users can determine if they would like to continue playing after each hand, or if they would like to stop
 * If users run out of currency in their bank, they are prompted if they would like to continue
 */
void play_game() {
    Shoe gameShoe;
    Hand playerHand;
    Hand dealerHand;
    // Set names and banks of players
    dealerHand.player.name = "Dealer";
    playerHand.Name();
    playerHand.Deposit();
    // Create shoe
    gameShoe.Deck_Count();
    gameShoe.Create_Shoe();
    gameShoe.Shuffle();
    // Mini main
    while (gameShoe.deck.cards.size() >= 13 && playerHand.player.bank_total > 0) {
        auto mini_main_result = mini_main(playerHand, dealerHand, gameShoe);
        playerHand = move(get<0>(mini_main_result));
        dealerHand = move(get<1>(mini_main_result));
        gameShoe = move(get<2>(mini_main_result));
        bool continue_playing = false;
        if (playerHand.player.bank_total > 0) {
            char cont_playing_input;
            while (true) {
                time_sleep(1000);
                cout << endl << "Would you like to continue playing? (y/n): ";
                cin >> cont_playing_input;
                if (cont_playing_input == 'y') {
                    if (gameShoe.deck.cards.size() >= 13) {
                        time_sleep(1000);
                        cout << endl << gameShoe.deck.cards.size() << " cards left in shoe. " << endl;
                        time_sleep(1000);
                        cout << endl << "Dealing new hands." << endl;
                        time_sleep(3000);
                        clear_terminal();
                        break;
                    }
                    else if (gameShoe.deck.cards.size() < 13) {
                        time_sleep(1000);
                        cout << endl << gameShoe.deck.cards.size() << " cards left in shoe. " << endl;
                        time_sleep(1000);
                        cout << endl << "Shuffling a new shoe." << endl;
                        gameShoe.deck.cards.clear();
                        gameShoe.Create_Shoe();
                        gameShoe.Shuffle();
                        time_sleep(5000);
                        clear_terminal();
                        break;
                    }   
                    else {
                        break;
                    }
                }
                else if (cont_playing_input == 'n') {
                    continue_playing = false;
                    time_sleep(1000);
                    cout << endl << playerHand.player.name << " has chosen to quit playing. Final bank total: " << playerHand.player.bank_total << endl;
                    time_sleep(1000);
                    cout << endl << "Thank you for playing." << endl;
                    time_sleep(3000);
                    clear_terminal();
                    break;
                }
                else {
                    continue;
                }
            }
            if (cont_playing_input == 'y') {
                continue_playing = true;
            }
            else if (cont_playing_input == 'n') {
                continue_playing = false;
            }
            else {}
        }
        else if (playerHand.player.bank_total == 0) {
            time_sleep(1000);
            cout << endl << playerHand.player.name << " has run out of currency in their bank. " << endl;
            time_sleep(1000);
            char currency_continue;
            while (true) {
                cout << endl << "Would you like to deposit more currency into your bank? (y/n): ";
                cin >> currency_continue;
                clear_terminal();
                if (currency_continue == 'y') {
                    playerHand.Deposit();
                    time_sleep(2000);
                    clear_terminal();
                    break;
                }
                else if (currency_continue == 'n') {
                    cout << endl << playerHand.player.name << " has ran out of currency and has chosen to "
                    << "not deposit more currency into their bank. Game over." << endl;
                    time_sleep(2000);
                    cout << endl << "Thank you for playing." << endl;
                    time_sleep(3000);
                    clear_terminal();
                    break;
                }
                else {
                    continue;
                }
            }
            if (currency_continue == 'y') {
                continue_playing = true;
            }
            else if (currency_continue == 'n') {
                continue_playing = false;
            }
            else {}
        }
        else {}
        if (!continue_playing) {
            break;
        }
        else if (continue_playing) {
            continue;
        }
        else {}
    }
}

// Test game method
void test_game() {}