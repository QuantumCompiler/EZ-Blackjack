# [Blackjack](https://github.com/RelativiBit/Blackjack) | By [RelativiBit](https://github.com/RelativiBit)

## Introduction - What is Blackjack?
Blackjack is a popular card game played in casinos, and it's also sometimes called "21." The game is usually played with multiple decks of cards, and the goal is to have a hand of cards that is worth a higher total than the dealer's hand, without going over 21.

Each card in the game is assigned a point value. Number cards (2-10) are worth their face value, face cards (Jacks, Queens, and Kings) are worth 10 points, and Aces are worth either 1 or 11 points, depending on what value will help the player the most.

At the start of the game, each player is dealt two cards face up, and the dealer is dealt one card face up and one card face down. Players can then choose to "hit," or be dealt another card, or "stand," or keep their current hand. The player can continue to hit until they either choose to stand, or their hand's value goes over 21, which is called "busting."

Once all players have finished taking their turns, the dealer will then reveal their face-down card and hit until their hand's value is at least 17. If the dealer busts, all remaining players win. If the dealer does not bust, then each player's hand is compared to the dealer's hand, and the player with the higher value hand without going over 21 wins.

There are also a few other rules and strategies to consider in blackjack, such as "splitting" pairs of cards, "doubling down" on certain hands, and taking "insurance" against the dealer having a blackjack.

## What is This Program?
This program is designed to be a fully functional implementation of all the rules that are present in blackjack. From buying insurance, to splitting hands, doubling down, along with other subtle intracacies, this program is designed to be a full fledged application that can simulate playing blackjack at a casino. Early [releases](https://github.com/RelativiBit/Blackjack/releases) of this game are console based applications that are built so that they can run in Unix and Windows based operating systems.

## [Releases](https://github.com/RelativiBit/Blackjack/releases)
- [Version 1.0](https://github.com/RelativiBit/Blackjack/releases/tag/v1.0) - Version 1.0 of this application was built using Python. Users can play against a computer and can play with a fixed number of decks in the shoe. This specific release is only available for Unix systems.
- [Version 1.1]() - Version 1.1 of this application was also built using Python. Small changes were made in this release, primarily bug and formatting fixes. This specific release is only available for Unix systems.
- [Version 2.0.0]() - Version 2.0.0 of this application was built using C++. Users still can only play against the computer, but are able to choose the number of decks that they would like to play with in their shoe. Along with being able to choose how many cards are in a shoe, users are greeted with a new an improved formatting of the application that can be run in their console of their machine. Error handling for inputs of quantities, such as a bank deposit, placing of bets, and deck counts are implemented in this releases build that can be downloaded in a Unix or Windows executable file.
- [Version 2.1.0]() - Version 2.1.0 of this application was built using C++. Users have an option at the beginning of the game to view the specific rules that are layed out for players. Along with this new information that is presented at the beginning of the game, users can now choose to continue playing at their own will after a hand has completed. If users run out of currency in their bank, they can choose if they would like to re-deposit money into their bank to continue playing.
- [Version 2.2.0]() - Version 2.2.0 of this application was built using C++. Users will be given hints to how they should play their hand at every moment. Using Blackjack logic, players now can make the best decisions when playing to maximize their odds at winning each hand. The Blackjack strategy that has been implemented into this version can be seen below. 
    <div style="text-align: center;">
        <img src="C++/Releases/Version 2.2.0/Assets/Blackjack Chart.PNG" style="max-width: 40%;">
    </div> 