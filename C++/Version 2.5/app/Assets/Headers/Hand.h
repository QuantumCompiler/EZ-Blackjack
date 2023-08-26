// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef HAND_H
#define HAND_H
#include "../HPP/Shoe.hpp"
#define HASTABLESIZE 10000
#define HASHTABLEITERATIONS 31
/*  Structure IndividualHand - Struct to resemble a playing card
*   Data Members:
*     Table Values:
*       canBuyInsurance - String value that represents if a player is eligible to buy insurance
*       canDoubleDown - String value that represents if a player is eligible to double down
*       canSplitAces - String value that represents if a player is eligible to split Aces
*       canSplitHand - String value that represents if a player is eligible to split their hand (Without Aces present)
*       choseBuyInsurance - String value that represents if a player has chosen to buy insurance
*       choseDoubleDown - String value that represents if a player has chosen to double down
*       choseHitHand - String value that represents if a player has chosen to hit their hand
*       choseSplitAces - String value that represents if a player has chosen to split Aces
*       choseSplitHand - String value that represents if a player has chosen to split their hand (Without Aces present)
*       choseStandHand - String value that represents if a player has chosen to stand their hand
*       doubleDownResponse - String value that represents if a player has decided if they would like to double down or not
*       hasBlackjack - String value that represents if a player has blackjack in their current hand
*       hasHit - String value that represents if a player has hit on current hand or not
*       paramInHand - String value that represents if a player has a specific parameter in their hand
*       sameParamInHand - String value that represents if a player has the same specific parameter in their hand
*       shouldDoubleDown - String value that represents if a player should double down for a specific hand
*       shouldHit - String value that represents if a player should hit for a specific hand
*       shouldSplit - String value that represents if a player should split for a specific hand
*       shouldStand - String value that represents if a player should stand for a specific hand
*       softSeventeen - String value that represents if a player has a soft seventeen (Hand total of 17 with at least one Ace being counted as 11)
*       splitAcesResponse - String value that represents if a player has decided on if they would like to split Aces or not
*       splitHandResponse - String value that represents if a player has decided on if they would like to split their hand or not
*     Float Values:
*       insuranceWager - Float value that represents the wager of which a player places for insurance
*       net - Float value that represents the net of a hand that has been played
*       wager - Float value that represents the wager that is placed on a hand that is being played
*     Integer Values:
*       cardsTotal - Integer value that represents the total value of a players hand of cards
*     String Values:
*       displayCardsTotal - String value that represents the modified private data member "cardsTotal"
*       displayInsuranceWager - String value that represents the modified private data member "insuranceWager"
*       displayNet - String value that represents the modified private data member "net"
*       displayWager - String value that represents the modified private data member "wager"
*     List Values:
*       PlayerCards - Linked list of Cards that represent a players cards
*/
struct IndividualHand {
    // HashTable Filters
    std::shared_ptr<HashTable> hashTable;
    // Table Values
    std::string canBuyInsurance = "CanBuyInsurance";
    std::string canDoubleDown = "CanDoubleDown";
    std::string canSplitAces = "CanSplitAces";
    std::string canSplitHand = "CanSplitHand";
    std::string choseBuyInsurance = "ChoseBuyInsurance";
    std::string choseDoubleDown = "ChoseDoubleDown"; 
    std::string choseHitHand = "ChoseHitHand";
    std::string choseStandHand = "ChoseStandHand";
    std::string choseSplitAces = "ChoseSplitAces";
    std::string choseSplitHand = "ChoseSplitHand";
    std::string doubleDownResponse = "DoubleDownResponse";
    std::string hasBlackjack = "HasBlackjack";
    std::string hitHandResponse = "HitHandResponse";
    std::string paramInHand = "ParamInHand";
    std::string sameParamInHand = "SameParamInHand";
    std::string shouldDoubleDown = "ShouldDoubleDown";
    std::string shouldHit = "ShouldHit";
    std::string shouldSplit = "ShouldSplit";
    std::string shouldStand = "ShouldStand";
    std::string softSeventeen = "SoftSevenTeen";
    std::string splitAcesResponse = "SplitAcesResponse";
    std::string splitHandResponse = "SplitHandResponse";
    // Values Matrix
    std::vector<std::vector<std::string>> valuesMatrix = {
        {canBuyInsurance, canDoubleDown, canSplitAces, canSplitHand, choseBuyInsurance},
        {choseDoubleDown, choseHitHand, choseStandHand, choseSplitAces, choseSplitHand},
        {doubleDownResponse, hasBlackjack, hitHandResponse, paramInHand, sameParamInHand},
        {shouldDoubleDown, shouldHit, shouldSplit, shouldStand, softSeventeen},
        {splitAcesResponse, splitHandResponse}
    };
    // Float Values
    float bankTotal;
    float insuranceWager;
    float net;
    float wager;
    // Integer Values
    int cardsTotal;
    // Strings
    std::string displayCardsTotal;
    std::string displayInsuranceWager;
    std::string displayNet;
    std::string displayWager;
    // Lists
    std::shared_ptr<LinkedList<Card>> PlayerCards;
};
class Hand {
public:
    // Constructors
    Hand(); // Constructor
    ~Hand(); // De-Constructor
    // Class Functions
    Hand AddCardToHand(std::shared_ptr<node<Card>>& input); // Adds card to hand
    Hand AddHandTotal(); // Adds current hand total
    Hand CheckBlackJack(); // Checks for if a player has blackjack
    Hand CheckParamInHand(const std::string referenceParameter, const std::string checkingParameter); // Checks if a player has a specific parameter in their hand
    Hand CheckSameParamInHand(const std::string referenceParameter, const std::string checkingParameter = ""); // Checks if a player has the same parameter in their hand
    Hand CopyVariables(std::shared_ptr<Hand>& input);
    Hand HitHand(std::shared_ptr<Shoe>& input); // Adds a card to a players hand from a shoe
    Hand InsurancePrompt(float& bank); // Prompts a player if they would like to place an insurance wager
    Hand InsuranceSim(float& bank, const bool& input); // Places an insurance wager for a simulate hand
    Hand ParametersCheck(std::shared_ptr<Hand>& dealerHand, const float& playerBank); // Checks for certain parameters of how a player can play their hand
    Hand PlaceWagerPrompt(float& bank); // Prompts a player for how much currency they would like to place as a wager for a hand
    Hand PlaceWagerSim(float& bank, const float& wager); // Places the wager for a players hand in a simulated game
    Hand ResetHand(); // Resets certain parameters for a players hand
    // Setter Functions
    // Float Values
    void SetInsuranceWager(const float& input); // Mutates "insuranceWager"
    void SetNet(const float& input); // Mutates "net"
    void SetWager(const float& input); // Mutates "wager"
    // Integer Values
    void SetCardsTotal(const int& input); // Mutates "cardsTotal"
    // String Values
    void SetDisplayCardsTotal(); // Mutates "displayCardsTotal"
    void SetDisplayInsuranceWager(); // Mutates "displayInsuranceWager"
    void SetDisplayNet(); // Mutates "displayNet"
    void SetDisplayWager(); // Mutates "displayWager"
    // List Values
    void SetPlayerCards(std::shared_ptr<node<Card>>& input); // Mutates "PlayerCards"
    // Getter Functions
    // Table Values
    std::shared_ptr<HashTable>& GetHashTable(); // Retrieves "hashTable"
    std::vector<std::vector<std::string>>& GetValuesMatrix(); // Retrieves "valuesMatrix"
    // Float Values
    float& GetInsuranceWager(); // Retrieves "insuranceWager"
    float& GetNet(); // Retrieves "net"
    float& GetWager(); // Retrieves "wager"
    // Integer Values
    int& GetCardsTotal(); // Retrieves "cardsTotal"
    // String Values
    std::string& GetDisplayCardsTotal(); // Retrieves "displayCardsTotal"
    std::string& GetDisplayInsuranceWager(); // Retrieves "displayInsuranceWager"
    std::string& GetDisplayNet(); // Retrieves "displayNet"
    std::string& GetDisplayWager(); // Retrieves "displayWager"
    // List Values
    std::shared_ptr<LinkedList<Card>>& GetPlayerCards(); // Retrieves "PlayerCards"
private:
    std::shared_ptr<IndividualHand> individualHand; // Private data member that encapsulates the IndividualHand structure
};

#endif