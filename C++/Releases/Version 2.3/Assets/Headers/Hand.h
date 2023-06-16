// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef HAND_H
#define HAND_H
#include "../HPP/Shoe.hpp"

struct Player {
    // Boolean Value
    bool can_buy_insurance;
    bool can_double_down;
    bool can_split_hand;
    bool can_split_aces;
    bool chose_buy_insurance;
    bool chose_double_down;
    bool chose_split_aces;
    bool chose_split_hand;
    bool has_hit;
    // Float Values
    float bank_total;
    float net;
    float wager;
    float insurance_wager;
    // Integer Values
    int cards_total;
    int individual_hands;
    int hands_played;
    // Strings
    std::string name;
    std::string display_name;
    std::string display_bank_total;
    std::string display_net;
    std::string display_wager;
    std::string display_insurance_wager;
    std::string display_cards_total;
    std::string display_hands_played;
    // Vectors
    std::vector<Card> cards;
    std::vector<float> hand_bank_totals;
    std::vector<float> hand_nets;
    std::vector<float> hand_wagers;
    std::vector<int> hand_card_totals;
    std::vector<int> hand_played;
};

class Hand {
public:
    // Constructor
    Hand();
    // Class Functions
    Hand AddCardToHand(const Card card);
    Hand AddHandTotal();
    Hand BankDeposit();
    Hand CopyVariables(Hand& inputHand);
    Hand Hit(Shoe& inputShoe);
    Hand Insurance();
    Hand Name();
    Hand PlaceWager();
    Hand ResetHand();
    Hand ShowHand(const std::string option = "", const std::string dealer_show = "");
    Hand UpdateBank(const std::string choice, Hand& inputHand, const float& wager);
    // Setter Functions
    // Boolean Values
    void SetCanBuyInsurance(const bool input);
    void SetCanDoubleDown(const bool input);
    void SetCanSplitAces(const bool input);
    void SetCanSplitHand(const bool input);
    void SetChoseBuyInsurace(const bool input);
    void SetChoseDoubleDown(const bool input);
    void SetChoseSplitAces(const bool input);
    void SetChoseSplitHand(const bool input);
    void SetHasHit(const bool input);
    // Float Values
    void SetBankTotal(const float& input);
    void SetNet(const float& input);
    void SetWager(const float& input);
    void SetInsuranceWager(const float& input);
    // Integer Values
    void SetCardsTotal(const int& input);
    void SetIndividualHands(const int& input);
    void SetHandsPlayed(const int& input);
    // String Values
    void SetName(const std::string& input);
    void SetDisplayName();
    void SetDisplayBankTotal();
    void SetDisplayNet();
    void SetDisplayWager();
    void SetDisplayInsuranceWager();
    void SetDisplayCardsTotal();
    void SetDisplayHandsPlayed();
    // Vector Values
    void SetCards(const Card& input);
    void SetHandBankTotals(const float& input); 
    void SetHandNets(const float& input);
    void SetHandWagers(const float& input);
    void SetHandCardTotals(const int& input);
    void SetHandPlayed(const int& input);
    // Getter Functionss
    // Boolean Values
    bool GetCanBuyInsurance() const;
    bool GetCanDoubleDown() const;
    bool GetCanSplitAces() const;
    bool GetCanSplitHand() const;
    bool GetChoseBuyInsurance() const;
    bool GetChoseDoubleDown() const;
    bool GetChoseSplitAces() const;
    bool GetChoseSplitHand() const;
    bool GetHasHit() const;
    // Float Values
    float GetBankTotal() const;
    float GetNet() const;
    float GetWager() const;
    float GetInsuranceWager() const;
    // Integer Values
    int GetCardsTotal() const;
    int GetIndividualHands() const;
    int GetHandsPlayed() const;
    // String Values
    std::string GetName() const;
    std::string GetDisplayName() const;
    std::string GetDisplayBankTotal() const;
    std::string GetDisplayNet() const;
    std::string GetDisplayWager() const;
    std::string GetDisplayInsuranceWager() const;
    std::string GetDisplayCardsTotal() const;
    std::string GetDisplayHandsplayed() const;
    // Vector Values
    std::vector<Card> GetCards() const;
    std::vector<float> GetHandBankTotals() const;
    std::vector<float> GetHandNets() const;
    std::vector<float> GetHandWagers() const;
    std::vector<int> GetHandCardTotals() const;
    std::vector<int> GetHandPlayed() const;
private:
    Player currentPlayer;
};

#endif