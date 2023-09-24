// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef PLAYER_H
#define PLAYER_H
#include "../HPP/Hand.hpp"

/*  PlayerParameters - Struct that encapsulates the parameters of a player
*   Data Members:
*       Float Values
*           bankTotal - Float value that resembles the bank total for a player for all hands
*       Integer Values
*           blackjackHands - Integer value that represents the number of blackjack hands that a player obtains in a game
*           currentHandsPossessed - Integer value that represents the number of current hands that a player has
*           handsLost - Integer value that represents the number of hands that a player has lost in a game
*           handsPlayed - Integer value that represents the number of hands played over a course of an entire sitting of blackjack
*           handsPushed - Integer value that represents the number of hands pushed over a course of an entire sitting of blackjack
*           handsWon - Integer value that represents the number of hands won over a course of an entire sitting of blackjack
*       Lists
*           CurrentHands - Pointer to a linked list of a pointer to a hand object
*           HandBankTotals - Pointer to a linked list of floats that represents the bank totals of a player after an individual hand
*           HandCardTotals - Pointer to a linked list of integers that represents the card total for an individual hand
*           HandNets - Pointer to a linked list of floats that represents the net of an individual hand
*           HandsPlayed - Pointer to a linked list of integers that represents the total number of hands played in a sitting of blackjack
*           HandWagers - Pointer to a linked list of floats that represents the individual wager for an individual hand
*       Strings
*           displayBankTotal - String value that represents the modified bank total of a player
*           displayName - String value that represents the modified name of a player
*           name - String value that represents the name of a player
*/
struct PlayerParameters {
    // Float Values
    float bankTotal;
    // Integer values
    int blackjackHands;
    int currentHandsPossessed;
    int handsLost;
    int handsPlayed;
    int handsPushed;
    int handsWon;
    // Lists
    std::shared_ptr<LinkedList<std::shared_ptr<Hand>>> CurrentHands;
    std::shared_ptr<LinkedList<float>> HandBankTotals;
    std::shared_ptr<LinkedList<int>> HandCardTotals;
    std::shared_ptr<LinkedList<float>> HandNets;
    std::shared_ptr<LinkedList<int>> HandsPlayed;
    std::shared_ptr<LinkedList<float>> HandWagers;
    // Strings
    std::string displayBankTotal;
    std::string displayName;
    std::string name;
};

class Player {
public:
    // Constructors
    Player(); // Class constructor
    ~Player(); // Class deconstructor
    // Class Functions
    Player BankDepositPrompt();
    Player NamePrompt();
    Player ResetPlayer();
    Player ShowCurrentHand(std::shared_ptr<Hand>& inputHand, std::string option, const std::string dealerShow);
    Player UpdateBank(std::shared_ptr<Hand>& inputHand, const int choice);
    // Mutator Functions
    // Setters
    // Float Values
    void SetBankTotal(const float& input);
    // Integer values
    void SetBlackjackHands();
    void SetCurrentHandsPossessed();
    void SetHandsLost();
    void SetHandsPlayed();
    void SetHandsPushed();
    void SetHandsWon();
    // Lists
    void SetCurrentHands(const std::shared_ptr<Hand>& input);
    void SetTotalHandBankTotals(const float& input);
    void SetTotalHandCardTotals(const int& input);
    void SetTotalHandNets(const float& input);
    void SetTotalHandsPlayed(const int& input);
    void SetTotalHandWagers(const float& input);
    // Strings
    void SetDisplayBankTotal();
    void SetDisplayName();
    void SetName(const std::string& input);
    // Getters
    // Float values
    float& GetBankTotal();
    // Integer values
    int& GetBlackjackHands();
    int& GetCurrentHandsPossessed();
    int& GetHandsLost();
    int& GetHandsPlayed();
    int& GetHandsPushed();
    int& GetHandsWon();
    // Lists
    std::shared_ptr<LinkedList<std::shared_ptr<Hand>>>& GetCurrentHands();
    std::shared_ptr<LinkedList<float>>& GetTotalHandBankTotals();
    std::shared_ptr<LinkedList<int>>& GetTotalHandCardTotals();
    std::shared_ptr<LinkedList<float>>& GetTotalHandNets();
    std::shared_ptr<LinkedList<int>>& GetTotalHandsPlayed();
    std::shared_ptr<LinkedList<float>>& GetTotalHandWagers();
    // Strings
    std::string& GetDisplayBankTotal();
    std::string& GetDisplayName();
    std::string& GetName();
private:
    std::shared_ptr<PlayerParameters> playerParameters; // PlayerParameters struct initialization
};

#endif