# ----- ----- ----- ----- ----- ----- ----- ----- ----- Imports ----- ----- ----- ----- ----- ----- ----- ----- ----- #
import random, time

# ----- ----- ----- ----- ----- ----- ----- ----- ----- Arrays ----- ----- ----- ----- ----- ----- ----- ----- ----- #
# Creating suits and ranks for cards
Suits = ["Clubs", "Diamonds", "Hearts", "Spades"]
Ranks = ["Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"]

# ----- ----- ----- ----- ----- ----- ----- ----- Variables / Booleans ----- ----- ----- ----- ----- ----- ----- ----- #
# Split hand booleans
Player_Split_Aces = None
Player_Split_Hand = None
Player_Bank = 0.0

# ----- ----- ----- ----- ----- ----- ----- ----- ----- Classes ----- ----- ----- ----- ----- ----- ----- ----- ----- #
# Card Class
class Card:
    # Constructor
    def __init__(self, rank, suit):
        self.suit = suit
        self.rank = rank
        if rank == "Ace":
            self.card_value = 11
        elif rank in ["10", "Jack", "Queen", "King"]:
            self.card_value = 10
        else:
            self.card_value = int(rank)

    # Value of card method
    def Value_of_Card(self):
        return self.card_value

    # Representation method
    def __repr__(self):
        return f"\033[1;32m{self.rank}\033[0m of \033[1;34m{self.suit}\033[0m"

# Deck class
class Deck:
    # Constructor
    def __init__(self):
        self.cards = [Card(rank, suit) for rank in Ranks for suit in Suits]
        self.returned_cards = []
        self.rigged_cards = []

    # Draw method
    def Draw(self):
        if len(self.rigged_cards) == 0:
            return self.cards.pop()
        elif len(self.rigged_cards) > 0:
            return self.rigged_cards.pop()
        else:
            pass

    # Deal random cards method
    def Deal_Cards(self):
        print("\n" "Here are the cards from a shuffled deck:")
        card_dealt_number = 1
        self.returned_cards = []
        rigged_deck = False
        if len(self.rigged_cards) > 0:
            rigged_deck = True
        else:
            pass
        if rigged_deck == False:
            for i in range(len(self.cards)):
                card_drawn = self.Draw()
                self.returned_cards.append(card_drawn)
                print(f"Card dealt number: {card_dealt_number} - {card_drawn}")
                card_dealt_number += 1
            self.cards = self.returned_cards
            self.cards.reverse()
            print(len(self.cards), " Cards remaining from shuffled deck" "\n")
        elif rigged_deck:
            for i in range(len(self.rigged_cards)):
                card_drawn = self.Draw()
                self.returned_cards.append(card_drawn)
                print(f"Card dealt number: {card_dealt_number} - {card_drawn}")
                card_dealt_number += 1
            self.rigged_cards = self.returned_cards
            self.rigged_cards.reverse()
            print(len(self.rigged_cards), " Cards remaining from rigged deck" "\n")
        time.sleep(1)

    # Shuffle method
    def Shuffle(self):
        random.shuffle(self.cards)

    # Representation method
    def __repr__(self):
        return f"Deck of {len(self.cards)} cards"

# Player Hand class
class Player_Hand:
    # Constructor
    def __init__(self, name=None):
        self.cards = []
        self.hand_wager = 0
        self.name = name
        self.hand_value = 0

    # Add card to hand
    def Add_Card_To_Hand(self, card):
        self.cards.append(card)
        ace_count = sum(card.rank == "Ace" for card in self.cards)
        for current_card in self.cards:
            if value_check("==", ace_count, 1):
                if check_rank_of_card(current_card, "Ace"):
                    current_card.card_value = 11
                else:
                    pass
            elif value_check(">", ace_count, 1):
                if check_rank_of_card(current_card, "Ace"):
                    current_card.card_value = 1
                else:
                    pass
            else:
                pass
            ace_count -= 1
        self.hand_value = sum(card.Value_of_Card() for card in self.cards)
        for current_card in self.cards:
            if value_check(">", self.hand_value, 21):
                if check_rank_of_card(current_card, "Ace"):
                    current_card.card_value = 1
                else:
                    pass
            else:
                pass
        self.hand_value = sum(card.Value_of_Card() for card in self.cards)
        return int(self.hand_value)

    # Bank deposit method
    def Deposit(self):
        global Player_Bank
        while Player_Bank == 0:
            while True:
                try:
                    Player_Bank = float(input("Enter a bank total to play with: "))
                    break
                except ValueError:
                    print("\n" f"Your input is not a number. Please try again." "\n")
            if value_check("<=", float(Player_Bank), 0):
                print("\n" f"Your entry of \033[1;31;40m{Player_Bank}\033[0m must be a positive number. Please"
                      f" re-enter your total for your bank." "\n")
                Player_Bank = 0
                continue
            else:
                break
        print("\n" f"\033[1;33;40m{self.name}\033[0m has chosen to start with a total"
              f" of: \033[1;31;40m{Player_Bank}\033[0m." "\n")
        time.sleep(1)
        return Player_Bank

    # Hit hand method
    def Hit_Hand(self, deck):
        card_drawn = deck.Draw()
        self.Add_Card_To_Hand(card_drawn)
        return Player_Hand

    # Player name method
    def Player_Name(self):
        player_name = input("Please enter your name: ")
        print("\n")
        self.name = player_name
        return self.name

    # Show hand method
    def Show_Hand(self, option=None):
        if option is None:
            option = "current"
            print(f"\033[1;33;40m{self.name}\033[0m's {option} hand: "
                  f"[{' , '.join(str(card) for card in self.cards)}] Hand Total: \033[1;31;40m{self.hand_value}\033[0m,"
                  f" Hand Wager: \033[1;31;40m{self.hand_wager}\033[0m, Bank Total: \033[1;31;40m{Player_Bank}\033[0m")
        elif option is not None:
            option = str(option)
            print(f"\033[1;33;40m{self.name}\033[0m's {option} hand: "
                  f"[{' , '.join(str(card) for card in self.cards)}] Hand Total: \033[1;31;40m{self.hand_value}\033[0m,"
                  f" Hand Wager: \033[1;31;40m{self.hand_wager}\033[0m, Bank Total: \033[1;31;40m{Player_Bank}\033[0m")

    # Update bank method
    def Update_Bank(self, choice, wager):
        bank = float(Player_Bank)
        wager = float(wager)
        if choice == "W":
            bank += 2.0*wager
        elif choice == "L":
            bank = bank
        elif choice == "P":
            bank += wager
        elif choice == "BJ":
            bank += wager
            bank += 1.5*wager
        elif choice == "I":
            new_wager = 0.5*float(wager)
            new_wager = float(new_wager)
            return new_wager
        else:
            pass
        return bank

# Dealer Hand Class
class Dealer_Hand:
    # Constructor
    def __init__(self):
        self.cards = []
        self.hand_value = 0

    # Add card to hand method
    def Add_Card_To_Hand(self, card):
        self.cards.append(card)
        ace_count = sum(card.rank == "Ace" for card in self.cards)
        for current_card in self.cards:
            if value_check("==", ace_count, 1):
                if check_rank_of_card(current_card, "Ace"):
                    current_card.card_value = 11
                else:
                    pass
            elif value_check(">", ace_count, 1):
                if check_rank_of_card(current_card, "Ace"):
                    current_card.card_value = 1
                else:
                    pass
            else:
                pass
            ace_count -= 1
        self.hand_value = sum(card.Value_of_Card() for card in self.cards)
        for current_card in self.cards:
            if value_check(">", self.hand_value, 21):
                if check_rank_of_card(current_card, "Ace"):
                    current_card.card_value = 1
                else:
                    pass
            else:
                pass
        self.hand_value = sum(card.Value_of_Card() for card in self.cards)
        return int(self.hand_value), self.cards

    def Hit_Hand(self, deck):
        card_drawn = deck.Draw()
        self.Add_Card_To_Hand(card_drawn)
        return Dealer_Hand

    def Show_Hand(self, display=None, option=None):
        if display is None:
            if option is None:
                option = "current"
                print(f"\033[1;33;40mDealer\033[0m's {option} hand: [Hidden, {self.cards[1]}]"
                      f" Hand Total: \033[1;31;40m{self.cards[1].card_value}\033[0m" )
            elif option is not None:
                option = str(option)
                print(f"\033[1;33;40mDealer\033[0m's {option} hand: [Hidden, {self.cards[1]}]"
                      f" Hand Total: \033[1;31;40m{self.cards[1].card_value}\033[0m" )
        elif display is not None:
            if option is None:
                option = "current"
                print(f"\033[1;33;40mDealer\033[0m's {option} hand: [{' , '.join(str(card) for card in self.cards)}]"
                      f" Hand Total: \033[1;31;40m{self.hand_value}\033[0m")
            elif option is not None:
                option = str(option)
                print(f"\033[1;33;40mDealer\033[0m's {option} hand: [{' , '.join(str(card) for card in self.cards)}]"
                      f" Hand Total: \033[1;31;40m{self.hand_value}\033[0m")

# ----- ----- ----- ----- ----- ----- ----- Game Methods ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- #
# Check for rank of card method
def check_rank_of_card(card, checking_rank):
    result = False
    if card.rank == checking_rank:
        result = True
    else:
        pass
    return result

# Check for rank in hand method
def check_rank_in_hand(hand, checking_rank):
    result = False
    for card in hand:
        if check_rank_of_card(card, checking_rank):
            result = True
            break
    return result

# Check for same rank in hand
def check_same_rank_in_hand(hand, checking_rank = None):
    result = True
    first_card_rank = hand[0].rank
    for card in hand[1:]:
        if card.rank != first_card_rank or (checking_rank is not None and card.rank != checking_rank):
            result = False
        return result

# Check for blackjack method
def check_for_blackjack(hand):
    result = False
    for card in hand:
        if card.card_value == 10:
            if check_rank_in_hand(hand, "Ace"):
                result = True
        else:
            continue
    return result

# Deal hand method
def deal_hand(deck, dealer_hand, player_hand):
    global Player_Bank
    for turn in range(4):
        if (turn % 2) == 0:
            player_hand.Hit_Hand(deck)
        elif (turn % 2) == 1:
            dealer_hand.Hit_Hand(deck)
    print("\n")
    time.sleep(1)
    player_hand.Show_Hand("initial")
    time.sleep(1)
    dealer_hand.Show_Hand(None, "initial")
    return player_hand, dealer_hand

# Dealer logic method
def dealer_logic(deck, dealer_hand, player_hand):
    global Player_Bank
    Dealer_Total = dealer_hand.hand_value
    Player_Total = player_hand.hand_value
    if value_check("<=", Player_Total, 21):
        while value_check("<", Dealer_Total, 17):
            dealer_hand.Hit_Hand(deck)
            Dealer_Total = dealer_hand.hand_value
            time.sleep(1)
            print(f"\033[1;33;40mDealer\033[0m hits, current hand: {dealer_hand.cards} Hand Total:"
                  f" \033[1;31;40m{Dealer_Total}\033[0m")
    elif value_check(">", Player_Total, 21):
        time.sleep(1)
        print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has busted with a final value of"
              f" \033[1;31;40m{Player_Total}\033[0m. \033[1;31;40m{player_hand.name} loses\033[0m.")
        time.sleep(1)
        player_hand.Show_Hand("final")
        time.sleep(1)
        dealer_hand.Show_Hand(1, "final")
        Player_Bank = player_hand.Update_Bank("L", player_hand.hand_wager)
    else:
        pass
    print("\n")
    if value_check("<=", Player_Total, 21):
        if value_check("==", Dealer_Total, Player_Total):
            time.sleep(1)
            print(f"Both players have the same final value of \033[1;31;40m{Player_Total}\033[0m."
                  f" It is \033[1;31;40ma push\033[0m. Here are the final hands:")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            dealer_hand.Show_Hand(1, "final")
            Player_Bank = player_hand.Update_Bank("P", player_hand.hand_wager)
        elif value_check(">", Dealer_Total, Player_Total) and value_check("<=", Dealer_Total, 21):
            time.sleep(1)
            print(f"Dealer has a greater final value of \033[1;31;40m{Dealer_Total}\033[0m."
                  f" \033[1;31;40m{player_hand.name} loses\033[0m. Here are the final hands:")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            dealer_hand.Show_Hand(1, "final")
            Player_Bank = player_hand.Update_Bank("L", player_hand.hand_wager)
        elif value_check("<", Dealer_Total, Player_Total):
            time.sleep(1)
            print(f"\033[1;33;40m{player_hand.name}\033[0m has a greater final value of \033[1;31;40m{Player_Total}\033[0m."
                  f" \033[1;31;40m{player_hand.name} wins\033[0m. Here are the final hands:")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            dealer_hand.Show_Hand(1, "final")
            Player_Bank = player_hand.Update_Bank("W", player_hand.hand_wager)
        elif value_check(">", Dealer_Total, 21):
            time.sleep(1)
            print(f"Dealer has busted with a final value of \033[1;31;40m{Dealer_Total}\033[0m."
                  f" \033[1;31;40m{player_hand.name} wins\033[0m. Here are the final hands:")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            dealer_hand.Show_Hand(1, "final")
            Player_Bank = player_hand.Update_Bank("W", player_hand.hand_wager)
        else:
            pass
    return Player_Bank

# Dealer play method
def dealer_play(deck , dealer_hand, player_hand):
    global Player_Bank
    Dealer_Total = dealer_hand.hand_value
    player_totals = []
    all_over_21 = True
    if isinstance(player_hand, Player_Hand):
        player_totals.append(player_hand.hand_value)
    elif isinstance(player_hand, list):
        for current_hand in player_hand:
            player_totals.append(current_hand.hand_value)
    else:
        raise ValueError(f"This is an incorrect data type: ", type(player_hand))
    for current_total in player_totals:
        if value_check("<=", current_total, 21):
            all_over_21 = False
            break
    if value_check("<", Dealer_Total, 17):
        needs_to_play = False
        for current_total in player_totals:
            if value_check("<=", current_total, 21):
                needs_to_play = True
                break
        if needs_to_play:
            print("\n" "The dealer will now play their hand.")
        elif needs_to_play == False:
            print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has busted and therefore"
                  " the dealer does not need to play their hand.")
        else:
            pass
    elif value_check(">=", Dealer_Total, 17) and value_check("<=", Dealer_Total, 21):
        needs_to_play = False
        for current_total in player_totals:
            if value_check("<=", current_total, 21):
                needs_to_play = True
                break
        if needs_to_play:
            print("\n" "The dealer does not need to play their hand with a final value of"
                  f" \033[1;31;40m{Dealer_Total}\033[0m.")
        elif needs_to_play == False:
            print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has busted and the"
                  " dealer does not need to play their hand.")
        dealer_hand.Show_Hand(1, "final")
    elif value_check(">", Dealer_Total, 21):
        print("\n" f"The dealer has busted with a final value of \033[1;31;40m{Dealer_Total}\033[0m.")
        dealer_hand.Show_Hand(1, "final")
    else:
        pass
    if all_over_21:
        if isinstance(player_hand, list):
            print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has busted on all"
                  " hands therefore the dealer has won both hands. Here are the final hands:")
            for current_hand in player_hand:
                dealer_logic(deck, dealer_hand, current_hand)
        elif isinstance(player_hand, Player_Hand):
            dealer_logic(deck, dealer_hand, player_hand)
        else:
            pass
    elif all_over_21 == False:
        if Player_Split_Aces == True or Player_Split_Hand == True:
            for current_hand in player_hand:
                dealer_logic(deck, dealer_hand, current_hand)
        elif Player_Split_Aces != True and Player_Split_Hand != True:
            dealer_logic(deck, dealer_hand, player_hand)
    else:
        pass
    return Player_Bank

# Hit, Stay, Double Down method
def hit_stay_double_down(deck, dealer_hand, player_hand):
    global Player_Bank
    Player_Total = player_hand.hand_value
    has_hit = False
    response = ""
    while response not in ["h", "s", "d"] and value_check("<", Player_Total, 21):
        if not has_hit:
            print("\n")
            time.sleep(1)
            if Player_Split_Aces == True or Player_Split_Hand == True:
                player_hand.Show_Hand("current")
                time.sleep(1)
                dealer_hand.Show_Hand(None, "initial")
                time.sleep(1)
            elif Player_Split_Aces != True and Player_Split_Hand != True:
                pass
            else:
                pass
            response = input("\n" f"Would you like to hit, stay, or double down on your current hand?"
                             f" \033[1;32;40m(h/s/d)\033[0m: ")
            print("\n")
        elif has_hit:
            time.sleep(1)
            player_hand.Show_Hand("current")
            time.sleep(1)
            dealer_hand.Show_Hand()
            time.sleep(1)
            response = input("\n" f"Would you like to hit or stay? \033[1;32;40m(h/s)\033[0m: ")
            print("\n")
        if response.lower() == "h":
            has_hit = True
            player_hand.Hit_Hand(deck)
            Player_Total = player_hand.hand_value
            if value_check(">", Player_Total, 21):
                time.sleep(1)
                print(f"\033[1;33;40m{player_hand.name}\033[0m has busted with a final value of"
                      f" \033[1;31;40m{Player_Total}\033[0m. Here is the player's final hand:")
                time.sleep(1)
                player_hand.Show_Hand("final")
                time.sleep(1)
                break
            elif value_check("<", Player_Total, 21):
                pass
            elif value_check("==", Player_Total, 21):
                time.sleep(1)
                print(f"\033[1;33;40m{player_hand.name}\033[0m has \033[1;31;40m{Player_Total}\033[0m."
                      f" No more cards will be accepted.")
                time.sleep(1)
                player_hand.Show_Hand("final")
                time.sleep(1)
                if Player_Split_Aces == True or Player_Split_Hand == True:
                    dealer_hand.Show_Hand()
                elif Player_Split_Aces != True and Player_Split_Hand != True:
                    dealer_hand.Show_Hand(1)
                else:
                    pass
            response = ""
        elif response.lower() == "s":
            Player_Total = player_hand.hand_value
            time.sleep(1)
            print(f"\033[1;33;40m{player_hand.name}\033[0m has chosen to stay with a final value of"
                  f" \033[1;31;40m{Player_Total}\033[0m.")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            break
        elif response.lower() == "d" and has_hit == False:
            if float(Player_Bank) >= float(player_hand.hand_wager):
                Player_Bank -= player_hand.hand_wager
                player_hand.hand_wager *= 2
                player_hand.Hit_Hand(deck)
                Player_Total = player_hand.hand_value
                if value_check(">", Player_Total, 21):
                    time.sleep(1)
                    print(f"\033[1;33;40m{player_hand.name}\033[0m has doubled down and busted with a final value of"
                          f" \033[1;31;40m{Player_Total}\033[0m.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    break
                elif value_check("<=", Player_Total, 21):
                    time.sleep(1)
                    print(f"\033[1;33;40m{player_hand.name}\033[0m has doubled down and has a final value of"
                          f" \033[1;31;40m{Player_Total}\033[0m.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    break
                else:
                    pass
                    break
            elif float(Player_Bank) < float(player_hand.hand_wager):
                print(f"Your current bank total of \033[1;31;40m{Player_Bank}\033[0m does not match your"
                      f" current wager of \033[1;31;40m{player_hand.hand_wager}\033[0m. You cannot double down.")
                response = ""
                continue
            else:
                pass
        else:
            print("\033[1;31;40mInvalid choice\033[0m." "\n")
            continue
    return player_hand, Player_Bank

# Play hand method
def play_hand(deck, dealer_hand, player_hand):
    # Import global variables to be modified
    global Player_Split_Aces
    global Player_Split_Hand
    global Player_Bank
    # Take bet for current hand
    player_hand.hand_wager = 0
    while player_hand.hand_wager == 0:
        while True:
            try:
                player_hand.hand_wager = float(input("Please enter a bet for your hand: "))
                break
            except ValueError:
                print("\n" f"Your input is not a number. Please try again." "\n")
        if player_hand.hand_wager > Player_Bank:
            print("\n" f"You have entered a wager of \033[1;31;40m{player_hand.hand_wager}\033[0m that is more"
                  f" than your bank of \033[1;31;40m{Player_Bank}\033[0m. Please re-enter your wager." "\n" )
            player_hand.hand_wager = 0
            continue
        elif player_hand.hand_wager <= 0:
            print("\n" f"Your wager of \033[1;31;40m{player_hand.hand_wager}\033[0m is less than or equal"
                  f" to zero. Please re-enter a positive value for a wager." "\n" )
            player_hand.hand_wager = 0
            continue
        elif not isinstance(player_hand.hand_wager, float or int):
            print("\n" f"Your wager of \033[1;31;40m{player_hand.hand_wager}\033[0m must be a number."
                  f" Pleae re-enter your wager." "\n" )
            player_hand.hand_wager = 0
            continue
        else:
            continue
    print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has wagered: \033[1;31;40m{player_hand.hand_wager}\033[0m"
          f" for the current hand.")
    Player_Bank -= player_hand.hand_wager
    # Deal hand and start processing logic
    deal_hand(deck, dealer_hand, player_hand)
    if dealer_hand.cards[1].rank == "Ace":
        time.sleep(1)
        insurance_choice = ""
        while insurance_choice not in ["y", "n"]:
            if value_check(">=", float(Player_Bank), 0.5*float(player_hand.hand_wager)):
                time.sleep(1)
                insurance_choice = input("\n" f"The dealer is showing an \033[1;32;40m{dealer_hand.cards[1].rank}\033[0m,"
                                         f" would you like to buy insurance? \033[1;32;40m(y/n)\033[0m: ")
            else:
                pass
            if insurance_choice.lower() == "y" and value_check(">=", float(Player_Bank), 0.5*float(player_hand.hand_wager)):
                insurance_wager = player_hand.Update_Bank("I", player_hand.hand_wager)
                time.sleep(1)
                print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has chosen to buy insurance in the amount of"
                      f" \033[1;31;40m{insurance_wager}\033[0m. We will now check for if the dealer has blackjack.")
                if check_for_blackjack(dealer_hand.cards) and check_for_blackjack(player_hand.cards):
                    time.sleep(1)
                    print("\n" "Both players have blackjack, it is a \033[1;31;40mpush\033[0m."
                          f" \033[1;31;40m{player_hand.name} wins insurance\033[0m.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    dealer_hand.Show_Hand(1, "final")
                    Player_Bank += insurance_wager
                    Player_Bank = player_hand.Update_Bank("P", player_hand.hand_wager)
                    break
                elif check_for_blackjack(dealer_hand.cards) and check_for_blackjack(player_hand.cards) == False:
                    time.sleep(1)
                    print("\n" f"The dealer has blackjack, \033[1;31;40m{player_hand.hand_wager} wins insurance\033[0m"
                          " but loses the hand.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    dealer_hand.Show_Hand(1, "final")
                    Player_Bank += insurance_wager
                    Player_Bank = player_hand.Update_Bank("L", player_hand.hand_wager)
                    break
                elif check_for_blackjack(dealer_hand.cards) == False and check_for_blackjack(player_hand.cards):
                    time.sleep(1)
                    print("\n" "\033[1;33;40m{player_hand.name}\033[0m has blackjack, the dealer does not."
                          f" \033[1;31;40m{player_hand.name} loses insurance\033[0m but wins the hand.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    dealer_hand.Show_Hand(1, "final")
                    Player_Bank -= insurance_wager
                    Player_Bank = player_hand.Update_Bank("BJ", player_hand.hand_wager)
                    break
                elif check_for_blackjack(dealer_hand.cards) == False and check_for_blackjack(player_hand.cards) == False:
                    time.sleep(1)
                    print("\n" f"Neither player has blackjack, \033[1;31;40m{player_hand.name} loses insurance\033[0m."
                          " The hand will continue.")
                    Player_Bank -= insurance_wager
                    player_hand_logic(deck, dealer_hand, player_hand)
            elif insurance_choice.lower() == "n" or value_check("<", float(Player_Bank), 0.5*float(player_hand.hand_wager)):
                time.sleep(1)
                if insurance_choice.lower() == "n":
                    print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has chosen to not buy insurance."
                          " We will now check for if the dealer has blackjack.")
                elif value_check("<", float(Player_Bank), 0.5*float(player_hand.hand_wager)):
                    print("\n" f"\033[1;33;40m{player_hand.name}\033[0m does not have enough money for insurance."
                         " We will now check for if the dealer has blackjack.")
                else:
                    pass
                if check_for_blackjack(dealer_hand.cards) and check_for_blackjack(player_hand.cards):
                    time.sleep(1)
                    print("\n" "Both players have blackjack, it is a \033[1;31;40mpush\033[0m.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    dealer_hand.Show_Hand(1, "final")
                    Player_Bank = player_hand.Update_Bank("P", player_hand.hand_wager)
                    break
                elif check_for_blackjack(dealer_hand.cards) and check_for_blackjack(player_hand.cards) == False:
                    time.sleep(1)
                    print("\n" f"The dealer has blackjack, \033[1;31;40m{player_hand.name} loses\033[0m.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    dealer_hand.Show_Hand(1, "final")
                    Player_Bank = player_hand.Update_Bank("L", player_hand.hand_wager)
                    break
                elif check_for_blackjack(dealer_hand.cards) == False and check_for_blackjack(player_hand.cards):
                    time.sleep(1)
                    print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has blackjack, the dealer does not,"
                          f" \033[1;31;40m{player_hand.hand_wager} wins\033[0m.")
                    time.sleep(1)
                    player_hand.Show_Hand("final")
                    time.sleep(1)
                    dealer_hand.Show_Hand(1, "final")
                    Player_Bank = player_hand.Update_Bank("BJ", player_hand.hand_wager)
                    break
                elif check_for_blackjack(dealer_hand.cards) == False and check_for_blackjack(player_hand.cards) == False:
                    time.sleep(1)
                    print("\n" "Neither player has blackjack. The hand will continue.")
                    player_hand_logic(deck, dealer_hand, player_hand)
            else:
                print("\n" "\033[1;31;40mInvalid choice\033[0m" "\n")
                continue
    elif dealer_hand.cards[1].rank != "Ace":
        if check_for_blackjack(dealer_hand.cards) and check_for_blackjack(player_hand.cards):
            time.sleep(1)
            print("\n" "Both players have blackjack, it is a \033[1;31;40mpush\033[0m.")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            dealer_hand.Show_Hand(1, "final")
            Player_Bank = player_hand.Update_Bank("P", player_hand.hand_wager)
        elif check_for_blackjack(dealer_hand.cards) and check_for_blackjack(player_hand.cards) == False:
            time.sleep(1)
            print("\n" f"The dealer has blackjack, \033[1;31;40m{player_hand.name} loses\033[0m.")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            dealer_hand.Show_Hand(1, "final")
            Player_Bank = player_hand.Update_Bank("L", player_hand.hand_wager)
        elif check_for_blackjack(dealer_hand.cards) == False and check_for_blackjack(player_hand.cards):
            time.sleep(1)
            print("\n" f"\033[1;33;40m{player_hand.name}\033[0m has blackjack, the dealer does not,"
                  f" \033[1;31;40m{player_hand.hand_wager} wins\033[0m.")
            time.sleep(1)
            player_hand.Show_Hand("final")
            time.sleep(1)
            dealer_hand.Show_Hand(1, "final")
            Player_Bank = player_hand.Update_Bank("BJ", player_hand.hand_wager)
        elif check_for_blackjack(dealer_hand.cards) == False and check_for_blackjack(player_hand.cards) == False:
            player_hand_logic(deck, dealer_hand, player_hand)
    else:
        pass
    # Reset global variables
    if isinstance(player_hand, list):
        for current_hand in player_hand:
            current_hand.cards.clear()
            current_hand.hand_value = 0
            current_hand.hand_wager = 0
    elif isinstance(player_hand, Player_Hand):
        player_hand.cards.clear()
        player_hand.hand_value = 0
        player_hand.hand_wager = 0
    else:
        pass
    dealer_hand.cards.clear()
    dealer_hand.hand_value = 0
    Player_Split_Aces = None
    Player_Split_Hand = None
    time.sleep(2)
    return [player_hand, dealer_hand, Player_Split_Aces, Player_Split_Hand, Player_Bank]

# Player logic method
def player_hand_logic(deck, dealer_hand, player_hand):
    global Player_Bank
    hands_of_player = player_same_rank_check(deck, player_hand)[0]
    if Player_Split_Aces == True:
        print("\n" "Here are the final hands of the player:")
        hand_counter = 1
        for current_hand in hands_of_player:
            if hand_counter == 1:
                hand_option = "final first"
            elif hand_counter == 2:
                hand_option = "final second"
            time.sleep(1)
            current_hand.Show_Hand(hand_option)
            hand_counter += 1
        dealer_play(deck, dealer_hand, hands_of_player)
    elif Player_Split_Hand == True:
        print("\n" "Here are the current hands of the player:")
        hand_counter = 1
        for current_hand in hands_of_player:
            if hand_counter == 1:
                hand_option = "current first"
            elif hand_counter == 2:
                hand_option = "current second"
            elif hand_counter == 3:
                hand_option = "current third"
            elif hand_counter == 4:
                hand_option = "current fourth"
            elif hand_counter == 5:
                hand_option = "current fifth"
            time.sleep(1)
            current_hand.Show_Hand(hand_option)
            hand_counter += 1
        hand_counter = 1
        for current_hand in hands_of_player:
            if hand_counter > 1:
                current_hand.Hit_Hand(deck)
            else:
                pass
            hit_stay_double_down(deck, dealer_hand, current_hand)
            hand_counter += 1
        print("\n" "The final hands of the player are:")
        hand_counter = 1
        for current_hand in hands_of_player:
            if hand_counter == 1:
                hand_option = "final first"
            elif hand_counter == 2:
                hand_option = "final second"
            elif hand_counter == 3:
                hand_option = "final third"
            elif hand_counter == 4:
                hand_option = "final fourth"
            elif hand_counter == 5:
                hand_option = "final fifth"
            time.sleep(1)
            current_hand.Show_Hand(hand_option)
            hand_counter += 1
        dealer_play(deck, dealer_hand, hands_of_player)
    elif Player_Split_Aces != True and Player_Split_Hand != True:
        hit_stay_double_down(deck, dealer_hand, hands_of_player)
        dealer_play(deck, dealer_hand, hands_of_player)
    else:
        pass
    return Player_Bank

# Player same rank check method
def player_same_rank_check(deck, player_hand):
    global Player_Split_Aces
    global Player_Split_Hand
    global Player_Bank
    if check_same_rank_in_hand(player_hand.cards, "Ace"):
        time.sleep(1)
        if value_check(">=", float(Player_Bank), float(player_hand.hand_wager)):
            aces_response = ""
            while aces_response not in ["y", "n"]:
                aces_response = input("\n" f"You have two \033[1;32;40m{player_hand.cards[0].rank}\033[0m's in your hand."
                                      f" Would you like to split your hand? You may only split your hand once."
                                      f" \033[1;32;40m(y/n)\033[0m: ")
                if aces_response.lower() == "y":
                    time.sleep(1)
                    player_hand_1 = Player_Hand(player_hand.name)
                    player_hand_2 = Player_Hand(player_hand.name)
                    player_hand_1.hand_wager = player_hand.hand_wager
                    player_hand_2.hand_wager = player_hand.hand_wager
                    player_hand_1.Add_Card_To_Hand(split_hand(player_hand)[1][0])
                    player_hand_2.Add_Card_To_Hand(split_hand(player_hand)[0][0])
                    player_hand_1.Hit_Hand(deck)
                    player_hand_2.Hit_Hand(deck)
                    Player_Split_Aces = True
                    split_hands = [player_hand_1, player_hand_2]
                    if check_same_rank_in_hand(player_hand_1.cards, "Ace"):
                        player_hand_1.cards[0].card_value = 11
                        player_hand_1.cards[1].card_value = 1
                    else:
                        pass
                    if check_same_rank_in_hand(player_hand_2.cards, "Ace"):
                        player_hand_2.cards[0].card_value = 11
                        player_hand_2.cards[1].card_value = 1
                    else:
                        pass
                    new_hand = split_hands
                    break
                elif aces_response.lower() == "n":
                    time.sleep(1)
                    Player_Split_Aces = False
                    new_hand = player_hand
                    break
                else:
                    print("\n" "\033[1;31;40mInvalid choice\033[0m." "\n")
                    continue
        elif value_check("<", float(Player_Bank), float(player_hand.hand_wager)):
            print("\n"f"Your remaining bank total \033[1;31;40m{Player_Bank}\033[0m is not at least that of your"
                  f" bet of \033[1;31;40m{player_hand.hand_wager}\033[0m. You cannot split your hand:")
            new_hand = player_hand
        else:
            new_hand = player_hand
    elif check_same_rank_in_hand(player_hand.cards) and check_same_rank_in_hand(player_hand.cards, "Ace") == False:
        time.sleep(1)
        if value_check(">=", float(Player_Bank), float(player_hand.hand_wager)):
            same_rank_response = ""
            while same_rank_response not in ["y", "n"]:
                same_rank_response = input(
                    "\n" f"You have the same rank of \033[1;32;40m{player_hand.cards[0].rank}\033[0m"
                    f" in your hand. Would you like to split your hand? "
                    f" \033[1;32;40m(y/n)\033[0m: ")
                if same_rank_response.lower() == "y":
                    time.sleep(1)
                    player_hand_1 = Player_Hand(player_hand.name)
                    player_hand_2 = Player_Hand(player_hand.name)
                    player_hand_1.hand_wager = player_hand.hand_wager
                    player_hand_2.hand_wager = player_hand.hand_wager
                    player_hand_1.Add_Card_To_Hand(split_hand(player_hand)[1][0])
                    player_hand_2.Add_Card_To_Hand(split_hand(player_hand)[0][0])
                    player_hand_1.Hit_Hand(deck)
                    Player_Split_Hand = True
                    split_hands = []
                    checking_hand = player_hand_1
                    Player_Bank -= player_hand_2.hand_wager
                    if check_same_rank_in_hand(checking_hand.cards):
                        time.sleep(1)
                        if value_check(">=", float(Player_Bank), float(player_hand.hand_wager)):
                            print("\n" f"You have pulled the same rank of "
                                  f"\033[1;32;40m{checking_hand.cards[1].rank}\033[0m again."
                                  f" Here are your current hands:")
                            time.sleep(1)
                            checking_hand.Show_Hand("first")
                            time.sleep(1)
                            player_hand_2.Show_Hand("second")
                            split_counter = 1
                            while value_check("<=", split_counter, 3) and check_same_rank_in_hand(checking_hand.cards):
                                split_again_choice = ""
                                while split_again_choice not in ["y", "n"]:
                                    split_again_choice = input("\n" f"Would you like to split your"
                                                               f" \033[1;32;40m{checking_hand.cards[1].rank}\033[0m's"
                                                               f" again? \033[1;32;40m(y/n)\033[0m: ")
                                    if split_again_choice.lower() == "y":
                                        split_counter += 1
                                        print("\n" f"You have chosen to split your hand again."
                                              f" Total times split: \033[1;31;40m{split_counter}\033[0m")
                                        new_player_hand_1 = Player_Hand(player_hand.name)
                                        new_player_hand_2 = Player_Hand(player_hand.name)
                                        new_player_hand_1.hand_wager = player_hand.hand_wager
                                        new_player_hand_2.hand_wager = player_hand.hand_wager
                                        new_player_hand_1.Add_Card_To_Hand(split_hand(checking_hand)[1][0])
                                        new_player_hand_2.Add_Card_To_Hand(split_hand(checking_hand)[0][0])
                                        split_hands.insert(0, new_player_hand_2)
                                        new_player_hand_1.Hit_Hand(deck)
                                        checking_hand = new_player_hand_1
                                        Player_Bank -= new_player_hand_2.hand_wager
                                        break
                                    elif split_again_choice.lower() == "n":
                                        break
                                    else:
                                        print("\n" "\033[1;31;40mInvalid choice\033[0m.")
                                        continue
                                if check_same_rank_in_hand(checking_hand.cards) and split_again_choice.lower() == "y":
                                    if value_check("<", split_counter, 4) and \
                                    value_check(">=", float(Player_Bank), float(player_hand.hand_wager)):
                                        print("\n" "Your current hands are:")
                                        split_hands.insert(0, checking_hand)
                                        split_hands.append(player_hand_2)
                                        hand_counter = 1
                                        for current_hand in split_hands:
                                            if hand_counter == 1:
                                                hand_option = "current first"
                                            elif hand_counter == 2:
                                                hand_option = "current second"
                                            elif hand_counter == 3:
                                                hand_option = "currenth third"
                                            elif hand_counter == 4:
                                                hand_option = "current fourth"
                                            elif hand_counter == 5:
                                                hand_option = "current fifth"
                                            time.sleep(1)
                                            current_hand.Show_Hand(hand_option)
                                            hand_counter += 1
                                        split_hands.remove(checking_hand)
                                        split_hands.remove(player_hand_2)
                                        continue
                                    elif value_check("==", split_counter, 4) or \
                                    value_check("<", float(Player_Bank), float(player_hand.hand_wager)):
                                        if value_check("==", split_counter, 4):
                                            print("\n" f"You can no longer split your hands. Times split: "
                                                  f" \033[1;31;40m{split_counter}\033[0m" "\n")
                                        elif value_check("<", float(Player_Bank), float(player_hand.hand_wager)):
                                            print("\n" f"Your current bank balance"
                                                  f" of \033[1;31;40m{Player_Bank}\033[0m is not greater than your"
                                                  f" bet of \033[1;31;40m{player_hand.hand_wager}\033[0m. You can no"
                                                  f" longer split your hands." "\n")
                                        split_hands.insert(0, checking_hand)
                                        break
                                    else:
                                        pass
                                    continue
                                elif check_same_rank_in_hand(checking_hand.cards) == False \
                                or split_again_choice.lower() == "n":
                                    if check_same_rank_in_hand(checking_hand.cards) == False:
                                        print("\n" f"You did not pull the same rank of"
                                              f" \033[1;32;40m{checking_hand.cards[0].rank}\033[0m again."
                                              f" Total times split: \033[1;31;40m{split_counter}\033[0m" "\n")
                                    elif split_again_choice.lower() == "n":
                                        print("\n" f"You have chosen to not split your hand again."
                                              f" Total times split: \033[1;31;40m{split_counter}\033[0m" "\n")
                                    else:
                                        pass
                                    split_hands.insert(0, checking_hand)
                                    break
                                else:
                                    raise ValueError("\033[1;31;40mA catastrophic error has occurred.\033[0m")
                        else:
                            print(f"You pulled the same rank of \033[1;32;40m{checking_hand.cards[1].rank}\033[0m"
                                  " again but you do not have sufficient funds to split." "\n")
                            time.sleep(1)
                            checking_hand.Show_Hand("first")
                            time.sleep(1)
                            player_hand_2.Show_Hand("second")
                            print("\n")
                            split_hands.insert(0, player_hand_1)
                        split_hands.append(player_hand_2)
                    elif check_same_rank_in_hand(checking_hand.cards) == False:
                        split_hands.insert(0, player_hand_1)
                        split_hands.append(player_hand_2)
                    else:
                        pass
                    new_hand = split_hands
                    break
                elif same_rank_response.lower() == "n":
                    time.sleep(1)
                    Player_Split_Hand = False
                    new_hand = player_hand
                    break
                else:
                    print("\n" "\033[1;31;40mInvalid choice\033[0m." "\n")
                    continue
        elif value_check("<", float(Player_Bank), float(player_hand.hand_wager)):
            print("\n"f"Your remaining bank total \033[1;31;40m{Player_Bank}\033[0m is not at least that of your"
                  f" bet of \033[1;31;40m{player_hand.hand_wager}\033[0m. You cannot split your hand:")
            new_hand = player_hand
        else:
            new_hand = player_hand
    else:
        new_hand = player_hand
    return [new_hand, Player_Split_Aces, Player_Split_Hand, Player_Bank]

# Split hand method
def split_hand(Hand):
    hands = []
    current_hand = []
    for card in Hand.cards:
        current_hand.append(card)
        if card.rank == Hand.cards[0].rank:
            hands.append(current_hand)
            current_hand = []
        else:
            pass
    if current_hand:
        hands.append(current_hand)
    return hands

# Value check method
def value_check(operator, fed_value, checking_value):
    if operator == "==":
        if fed_value == checking_value:
            result = True
        else:
            result = False
    elif operator == "<=":
        if fed_value <= checking_value:
            result = True
        else:
            result = False
    elif operator == ">=":
        if fed_value >= checking_value:
            result = True
        else:
            result = False
    elif operator == ">":
        if fed_value > checking_value:
            result = True
        else:
            result = False
    elif operator == "<":
        if fed_value < checking_value:
            result = True
        else:
            result = False
    else:
        raise ValueError("\033[1;31;40mInvalid operator.\033[0m")
        pass
    return result