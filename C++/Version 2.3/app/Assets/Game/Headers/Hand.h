// // ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef HAND_H
#define HAND_H
#include "../HPP/Shoe.hpp"
/*  Structure Player - Struct to resemble a playing card
*   Data Members:
*     Boolean Values:
*       canBuyInsurance - Boolean value that represents if a player is able to buy insurance on a hand
*       canDoubleDown - Boolean value that represents if a player is able to double down on a hand
*       canSplitHand - Boolean value that represents if a player is able to split on a hand
*       canSplitAces - Boolean value that represents if a player is able to split aces on a hand
*       choseBuyInsurance - Boolean value that represents if a player has chosen to buy insurance on a hand
*       choseDoubleDown - Boolean value that represents if a player has chosen to double down on a hand
*       choseSplitAces - Boolean value that represents if a player has chosen to split aces on a hand
*       choseSplitHand - Boolean value that represents if a player has chosen to split on a hand
*       doubleDownResponse - Boolean value that represents if a player has chosen to double down on a hand
*       hasBlackJack - Boolean value that represents if a player has blackjack
*       hasHit - Boolean value that represents if a player has chosen to hit on their hand
*       paramInHand - Boolean value that represents if a player has a select parameter in their hand
*       shouldDoubleDown - Boolean value that represents if a player should double down according to blackjack strategy
*       shouldHit - Boolean value that represents if a player should hit according to blackjack strategy
*       shouldSplit - Boolean value that represents if a player should split according to blackjack strategy
*       shouldStand - Boolean value that represents if a player should stand according to blackjack strategy
*       softSeventeen - Boolean value that represents if a player has a soft 17 or not
*       splitAcesResponse - Boolean value that represents if a player has chosen to split their aces or not
*       splitHandResponse - Boolean value that represents if a player has chosen to split their hand or not
*     Float Values:
*       bankTotal - Float value that represents the total value of a players currency they can play with
*       insuranceWager - Float value that represents the wager of which a player places for insurance
*       net - Float value that represents the net of a hand that has been played
*       wager - Float value that represents the wager that is placed on a hand that is being played
*     Integer Values:
*       cardsTotal - Integer value that represents the total value of a players hand of cards
*       handsBlackjack - Integer value that represents how many blackjack hands a player has had
*       handsLost - Integer value that represents how many hands a player has lost
*       handsPlayed - Integer value that represents the number of total hands played by a player
*       handsPushed - Integer value that represents the number of total hands a player has pushed
*       handsWon - Integer value that represents the number of total hands a player has won
*     String Values:
*       displayBankTotal - String value that represents the modified private data member "bankTotal"
*       displayCardsTotal - String value that represents the modified private data member "cardsTotal"
*       displayInsuranceWager - String value that represents the modified private data member "insuranceWager"
*       displayName - String value that represents the modified private data member "name"
*       displayNet - String value that represents the modified private data member "net"
*       displayWager - String value that represents the modified private data member "wager"
*       name - String value that represents the name of a player
*     List Values:
*       handBankTotals - Linked list of float values that represent a players bank totals after each hand
*       handCardTotals - Linked list of integers that represent a players hand totals
*       handNets - Linked list of float values that represent a players nets after each hand
*       handPlayed - Linked list of integer values that represents the hand played in a game
*       handWagers - Linked list of float values that represent a players wager for each hand
*       playerCards - Linked list of Cards that represent a players cards
*       
*/
struct Player {
    // Boolean Value
    bool canBuyInsurance;
    bool canDoubleDown;
    bool canSplitAces;
    bool canSplitHand;
    bool choseBuyInsurance;
    bool choseDoubleDown;
    bool choseSplitAces;
    bool choseSplitHand;
    bool doubleDownResponse;
    bool hasBlackJack;
    bool hasHit;
    bool paramInHand;
    bool sameParamInHand;
    bool shouldDoubleDown;
    bool shouldHit;
    bool shouldSplit;
    bool shouldStand;
    bool softSeventeen;
    bool splitAcesResponse;
    bool splitHandResponse;
    // Float Values
    float bankTotal;
    float insuranceWager;
    float net;
    float wager;
    // Integer Values
    int cardsTotal;
    int handsBlackjack;
    int handsLost;
    int handsPlayed;
    int handsPushed;
    int handsWon;
    // Strings
    std::string displayBankTotal;
    std::string displayCardsTotal;
    std::string displayInsuranceWager;
    std::string displayName;
    std::string displayNet;
    std::string displayWager;
    std::string name;
    // Lists
    std::shared_ptr<LinkedList<float>> handBankTotals;
    std::shared_ptr<LinkedList<int>> handCardTotals;
    std::shared_ptr<LinkedList<float>> handNets;
    std::shared_ptr<LinkedList<int>> handPlayed;
    std::shared_ptr<LinkedList<float>> handWagers;
    std::shared_ptr<LinkedList<Card>> playerCards;
};
class Hand {
public:
    // Constructors
    Hand(); // Constructor
    ~Hand(); // De-Constructor
    // Class Functions
    Hand AddCardToHand(std::shared_ptr<node<Card>>& input); // Adds card to hand
    Hand AddHandTotal(); // Adds current hand total
    Hand BankDeposit(); // Deposits currency into a players bank
    Hand CheckBlackJack(); // Checks for if a player has blackjack
    Hand CheckParamInHand(const std::string referenceParameter, const std::string checkingParameter); // Checks if a player has a specific parameter in their hand
    Hand CheckSameParamInHand(const std::string referenceParameter, const std::string checkingParameter = ""); // Checks if a player has the same parameter in their hand
    Hand CopyVariables(std::shared_ptr<Hand>& input);
    Hand HitHand(std::shared_ptr<Shoe>& input); // Adds a card to a players hand from a shoe
    Hand InsurancePrompt(); // Prompts a player if they would like to place an insurance wager
    Hand NamePrompt(); // Prompts the player for a name that they would like to be called
    Hand ParametersCheck(std::shared_ptr<Hand>& dealerHand); // Checks for certain parameters of how a player can play their hand
    Hand PlaceWager(); // Prompts a player for how much currency they would like to place as a wager for a hand
    Hand ResetHand(); // Resets certain parameters for a players hand
    Hand ShowHand(std::string option = "", const std::string dealerShow = ""); 
    Hand UpdateBank(const int choice, const float& wager); // Updates the bank total of a player
    // Setter Functions
    // Boolean Values
    void SetCanBuyInsurance(const bool input); // Mutates "canBuyInsurance"
    void SetCanDoubleDown(const bool input); // Mutates "canDoubleDown"
    void SetCanSplitAces(const bool input); // Mutates "canSplitAces"
    void SetCanSplitHand(const bool input); // Mutates "canSplitHand"
    void SetChoseBuyInsurance(const bool input); // Mutates "choseBuyInsurance"
    void SetChoseDoubleDown(const bool input); // Mutates "choseDoubleDown"
    void SetChoseSplitAces(const bool input); // Mutates "choseSplitAces"
    void SetChoseSplitHand(const bool input); // Mutates "choseSplitHand"
    void SetDoubleDownResponse(const bool input); // Mutates "doubleDownResponse"
    void SetHasBlackJack(const bool input); // Mutates "hasBlackJack"
    void SetHasHit(const bool input); // Mutates "hasHit"
    void SetParamInHand(const bool input); // Mutates "paramInHand"
    void SetSameParamInHand(const bool input); // Mutates "sameParamInHand"
    void SetShouldDoubleDown(const bool input); // Mutates "shouldDoubleDowns"
    void SetShouldHit(const bool input); // Mutates "shouldHit"
    void SetShouldSplit(const bool input); // Mutates "shouldSplit"
    void SetShouldStand(const bool input); // Mutates "shouldStand"
    void SetSoftSeventeen(const bool input); // Mutates "softSeventeen"
    void SetSplitAcesResponse(const bool input); // Mutates "splitAcesResponse"
    void SetSplitHandResponse(const bool input); // Mutates "splitHandResponse"
    // Float Values
    void SetBankTotal(const float& input); // Mutates "bankTotal"
    void SetInsuranceWager(const float& input); // Mutates "insuranceWager"
    void SetNet(const float& input); // Mutates "net"
    void SetWager(const float& input); // Mutates "wager"
    // Integer Values
    void SetCardsTotal(const int& input); // Mutates "cardsTotal"
    void SetHandsBlackjack(const int& input); // Mutates "handsBlackjack"
    void SetHandsLost(const int& input); // Mutates "handsLost"
    void SetHandsPlayed(const int& input); // Mutates "handsPlayed"
    void SetHandsPushed(const int& input); // Mutates "handsPushed"
    void SetHandsWon(const int& input); // Mutates "handsWon"
    // String Values
    void SetDisplayBankTotal(); // Mutates "displayBankTotal"
    void SetDisplayCardsTotal(); // Mutates "displayCardsTotal"
    void SetDisplayInsuranceWager(); // Mutates "displayInsuranceWager"
    void SetDisplayName(); // Mutates "displayName"
    void SetDisplayNet(); // Mutates "displayNet"
    void SetDisplayWager(); // Mutates "displayWager"
    void SetName(const std::string& input); // Mutates "name"
    // List Values
    void SetHandBankTotals(std::shared_ptr<node<float>>& input); // Mutates "handBankTotals"
    void SetHandCardTotals(std::shared_ptr<node<int>>& input); // Mutates "handCardTotals"
    void SetHandNets(std::shared_ptr<node<float>>& input); // Mutates "handNets"
    void SetHandPlayed(std::shared_ptr<node<int>>& input); // Mutates "handPlayed"
    void SetHandWagers(std::shared_ptr<node<float>>& input); // Mutates "handWagers"
    void SetPlayerCards(std::shared_ptr<node<Card>>& input); // Mutates "playerCards"
    // Getter Functions
    // Boolean Values
    bool& GetCanBuyInsurance(); // Retrieves "canBuyInsurance"
    bool& GetCanDoubleDown(); // Retrieves "canDoubleDown"
    bool& GetCanSplitAces(); // Retrieves "canSplitAces"
    bool& GetCanSplitHand(); // Retrieves "canSplitHand"
    bool& GetChoseBuyInsurance(); // Retrieves "choseBuyInsurance"
    bool& GetChoseDoubleDown(); // Retrieves "choseDoubleDown"
    bool& GetChoseSplitAces(); // Retrieves "choseSplitAces"
    bool& GetChoseSplitHand(); // Retrieves "choseSplitHand"
    bool& GetDoubleDownResponse(); // Retrieves "doubleDownResponse"
    bool& GetHasBlackJack(); // Retrieves "hasBlackJack"
    bool& GetHasHit(); // Retrieves "hasHit"
    bool& GetParamInHand(); // Retrieves "paramInHand"
    bool& GetSameParamInHand(); // Retrieves "sameParamInHand"
    bool& GetShouldDoubleDown(); // Retrieves "shouldDoubleDown"
    bool& GetShouldHit(); // Retrieves "shouldHit"
    bool& GetShouldSplit(); // Retrieves "shouldSplit"
    bool& GetShouldStand(); // Retrieves "shouldStand"
    bool& GetSoftSeventeen(); // Retrieves "softSeventeen"
    bool& GetSplitAcesResponse(); // Retrieves "splitAcesResponse"
    bool& GetSplitHandResponse(); // Retrieves "splitHandResponse"
    // Float Values
    float& GetBankTotal(); // Retrieves "bankTotal"
    float& GetInsuranceWager(); // Retrieves "insuranceWager"
    float& GetNet(); // Retrieves "net"
    float& GetWager(); // Retrieves "wager"
    // Integer Values
    int& GetCardsTotal(); // Retrieves "cardsTotal"
    int& GetHandsBlackjack(); // Retrieves "handsBlackjack"
    int& GetHandsLost(); // Retrieves "handsLost"
    int& GetHandsPlayed(); // Retrieves "handsPlayed"
    int& GetHandsPushed(); // Retrieves "handsPushed"
    int& GetHandsWon(); // Retrieves "handsWon"
    // String Values
    std::string& GetDisplayBankTotal(); // Retrieves "displayBankTotal"
    std::string& GetDisplayCardsTotal(); // Retrieves "displayCardsTotal"
    std::string& GetDisplayInsuranceWager(); // Retrieves "displayInsuranceWager"
    std::string& GetDisplayName(); // Retrieves "displayName"
    std::string& GetDisplayNet(); // Retrieves "displayNet"
    std::string& GetDisplayWager(); // Retrieves "displayWager"
    std::string& GetName(); // Retrieves "name"
    // List Values
    std::shared_ptr<LinkedList<float>>& GetHandBankTotals(); // Retrieves "handBankTotals"
    std::shared_ptr<LinkedList<int>>& GetHandCardTotals(); // Retrieves "handCardTotals"
    std::shared_ptr<LinkedList<float>>& GetHandNets(); // Retrieves "handNets"
    std::shared_ptr<LinkedList<int>>& GetHandPlayed(); // Retrieves "handPlayed"
    std::shared_ptr<LinkedList<float>>& GetHandWagers(); // Retrieves "handWagers"
    std::shared_ptr<LinkedList<Card>>& GetPlayerCards(); // Retrieves "playerCards"
private:
    std::shared_ptr<Player> player; // Private data member that encapsulates the Player structure
};

#endif