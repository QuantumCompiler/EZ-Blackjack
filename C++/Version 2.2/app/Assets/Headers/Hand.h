// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
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
*       handsPlayed - Integer value that represents the number of total hands played by a player
*       individualHands - Integer value that represents the number of individual hands (Split hands included) played by a player
*     String Values:
*       displayBankTotal - String value that represents the modified private data member "bankTotal"
*       displayCardsTotal - String value that represents the modified private data member "cardsTotal"
*       displayHandsPlayed - String value that represents the modified private data member "handsPlayed"
*       displayInsuranceWager - String value that represents the modified private data member "insuranceWager"
*       displayName - String value that represents the modified private data member "name"
*       displayNet - String value that represents the modified private data member "net"
*       displayWager - String value that represents the modified private data member "wager"
*       name - String value that represents the name of a player
*     Vector Values:
*       cards - Vector of Card objects that represents the cards in a hand of a player
*       handBankTotals - Vector of floats that represents a players bank totals after each hand
*       handCardTotals - Vector of integers that represents a players card totals after each hand
*       handNets - Vector of floats that represents a players nets after a hand
*       handPlayed - Vector of integers that represents the total of hands played by a player
*       handWagers - Vector of floats that represents the original wager placed for each hand
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
    int handsPlayed;
    int individual_hands;
    // Strings
    std::string displayBankTotal;
    std::string displayCardsTotal;
    std::string displayHandsPlayed; 
    std::string displayInsuranceWager;
    std::string displayName;
    std::string displayNet;
    std::string displayWager;
    std::string name;
    // Vectors
    std::vector<Card> cards;
    std::vector<float> handBankTotals;
    std::vector<int> handCardTotals;
    std::vector<float> handNets;
    std::vector<int> handPlayed;
    std::vector<float> handWagers; 
};
class Hand {
public:
    // Constructor
    Hand();
    // Class Functions
    Hand AddCardToHand(const Card& input);
    Hand AddHandTotal();
    Hand BankDeposit();
    Hand CheckBlackJack();
    Hand CheckParamInHand(const std::string referenceParameter, const std::string checkingParameter);
    Hand CheckSameParamInHand(const std::string referenceParameter, const std::string checkingParameter = "");
    Hand CopyVariables(Hand& input);
    Hand HitHand(Shoe& input);
    Hand InsurancePrompt();
    Hand NamePrompt();
    Hand ParametersCheck(Hand& checkingHand, Hand& dealerHand);
    Hand PlaceWager();
    Hand ResetHand();
    Hand ShowHand(std::string option = "", const std::string dealerShow = "");
    Hand UpdateBank(const int choice, const float& wager);
    // Setter Functions
    // Boolean Values
    void SetCanBuyInsurance(const bool input);
    void SetCanDoubleDown(const bool input);
    void SetCanSplitAces(const bool input);
    void SetCanSplitHand(const bool input);
    void SetChoseBuyInsurance(const bool input);
    void SetChoseDoubleDown(const bool input);
    void SetChoseSplitAces(const bool input);
    void SetChoseSplitHand(const bool input);
    void SetDoubleDownResponse(const bool input);
    void SetHasBlackJack(const bool input);
    void SetHasHit(const bool input);
    void SetParamInHand(const bool input);
    void SetSameParamInHand(const bool input);
    void SetShouldDoubleDown(const bool input);
    void SetShouldHit(const bool input);
    void SetShouldSplit(const bool input);
    void SetShouldStand(const bool input);
    void SetSoftSeventeen(const bool input);
    void SetSplitAcesResponse(const bool input);
    void SetSplitHandResponse(const bool input);
    // Float Values
    void SetBankTotal(const float& input);
    void SetInsuranceWager(const float& input);
    void SetNet(const float& input);
    void SetWager(const float& input);
    // Integer Values
    void SetCardsTotal(const int& input);
    void SetHandsPlayed(const int& input);
    void SetIndividualHands(const int& input);
    // String Values
    void SetDisplayName();
    void SetDisplayBankTotal();
    void SetDisplayNet();
    void SetDisplayWager();
    void SetDisplayInsuranceWager();
    void SetDisplayCardsTotal();
    void SetDisplayHandsPlayed();
    void SetName(const std::string& input);
    // Vector Values
    void SetCards(const Card& input);
    void SetHandBankTotals(const float& input);
    void SetHandCardTotals(const int& input);
    void SetHandNets(const float& input);
    void SetHandPlayed(const int& input);
    void SetHandWagers(const float& input);
    // Getter Functions
    // Boolean Values
    bool GetCanBuyInsurance() const;
    bool GetCanDoubleDown() const;
    bool GetCanSplitAces() const;
    bool GetCanSplitHand() const;
    bool GetChoseBuyInsurance() const;
    bool GetChoseDoubleDown() const;
    bool GetChoseSplitAces() const;
    bool GetChoseSplitHand() const;
    bool GetDoubleDownResponse() const;
    bool GetHasBlackJack() const;
    bool GetHasHit() const;
    bool GetParamInHand() const;
    bool GetSameParamInHand() const;
    bool GetShouldDoubleDown() const;
    bool GetShouldHit() const;
    bool GetShouldSplit() const;
    bool GetShouldStand() const;
    bool GetSoftSeventeen() const;
    bool GetSplitAcesResponse() const;
    bool GetSplitHandResponse() const;
    // Float Values
    float GetBankTotal() const;
    float GetInsuranceWager() const;
    float GetNet() const;
    float GetWager() const;
    // Integer Values
    int GetCardsTotal() const;
    int GetHandsPlayed() const;
    int GetIndividualHands() const;
    // String Values
    std::string GetDisplayBankTotal() const;
    std::string GetDisplayCardsTotal() const;
    std::string GetDisplayHandsPlayed() const;
    std::string GetDisplayInsuranceWager() const;
    std::string GetDisplayName() const;
    std::string GetDisplayNet() const;
    std::string GetDisplayWager() const;
    std::string GetName() const;
    // Vector Values
    std::vector<Card> GetCards() const;
    std::vector<float> GetHandBankTotals() const;
    std::vector<int> GetHandCardTotals() const;
    std::vector<float> GetHandNets() const;
    std::vector<int> GetHandPlayed() const;
    std::vector<float> GetHandWagers() const;
private:
    Player currentPlayer;
};

#endif