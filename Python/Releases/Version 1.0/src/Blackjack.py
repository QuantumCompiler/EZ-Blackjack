from StructureV1_0 import *
deck = Deck()
deck.Shuffle()
dealer_hand = Dealer_Hand()
player_hand = Player_Hand()
player_hand.Player_Name()
Player_Bank = player_hand.Deposit()
while len(deck.cards) >= 13 and Player_Bank > 0:
    Player_Bank = play_hand(deck, dealer_hand, player_hand)[-1]
    if len(deck.cards) >= 13 and Player_Bank > 0:
        print("\n" f"Shuffling a new hand. \033[1;33;40m{player_hand.name}\033[0m bank:"
              f" \033[1;31;40m{Player_Bank}\033[0m with \033[1;31;40m{len(deck.cards)}\033[0m cards remaining." "\n")
        time.sleep(1)
        continue
    elif len(deck.cards) < 13 and Player_Bank > 0:
        print("\n" f"Shuffling a new deck. \033[1;33;40m{player_hand.name}\033[0m bank:"
              f" \033[1;31;40m{Player_Bank}\033[0m \033[1;31;40m{len(deck.cards)}\033[0m"
              f" cards were left in the last deck." "\n")
        deck.Deal_Cards()
        deck = Deck()
        deck.Shuffle()
        time.sleep(1)
        continue
    elif Player_Bank <= 0:
        print("\n" "You are out of money. You can no longer play." "\n")
        time.sleep(1)
        break
    else:
        continue