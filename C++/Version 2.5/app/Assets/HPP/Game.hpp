// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Game.h"

/*  blackjack - Greets a user with choices of game modes to play in the program
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Prompt the user with an intro
*       * Present the options to the user
*       * Handle cases for certain response (see inline comments)
*   Output:
*       This function does not return an output, it directs traffic for what type of game mode is to be chosen for blackjack
*/
void blackjack() {
    // Clear terminal
    clear_terminal(); 
    time_sleep(MEDIUM_TIME_SLEEP);
    // String objects
    std::string Blackjack = color_text(32, "Blackjack");
    std::string RelativiBit = color_text(32, "RelativiBit");
    std::string PlayBlackjack = color_text(31, "play");
    std::string SimulateBlackjack = color_text(31, "simulate");
    // Intro greeting
    rolling_text("Welcome to " + Blackjack + " by " + RelativiBit + "."  ,PRINT_LINE_SLEEP); std::cout << std::endl;
    // Display choices
    std::cout << std::endl; rolling_text("Would you like to " + PlayBlackjack + " or " + SimulateBlackjack + " " + Blackjack + "?", PRINT_LINE_SLEEP); std::cout << std::endl;
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            std::cout << std::endl; rolling_text("Enter " + color_text(31, "[P]lay") + " to " + PlayBlackjack + " " + Blackjack + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
        else {
            rolling_text("Enter " + color_text(31, "[S]imulate") + " to " + SimulateBlackjack + " " + Blackjack + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
    }
    // Get response from user
    std::string response;
    std::vector<std::string> choices = {"P", "p", "S", "s"};
    bool valid = false;
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter your response: ", PRINT_LINE_SLEEP);
        std::cin >> response;
        // Check if response is in available choices
        for (int i = 0; i < choices.size(); i++) {
            if (response != choices[i]) {
                continue;
            }
            else if (response == choices[i]) {
                valid = true;
                // User has decided to Play blackjack
                if (response == "P" || response == "p") {
                    std::cout << std::endl; rolling_text("You have chosen to " + PlayBlackjack + " " + Blackjack + ". We will now explain the options of this " + Blackjack + " game.", PRINT_LINE_SLEEP); std::cout << std::endl;
                    // Call game_options
                    game_options();
                }
                // User has chosen to simulate blackjack
                else if (response == "S" || response == "s") {
                    std::cout << std::endl; rolling_text("You have chosen to " + SimulateBlackjack + " " + Blackjack + ". We will now explain the options of for simulating.", PRINT_LINE_SLEEP); std::cout << std::endl;
                }
                break;
            }
        }
        // User has entered an invalid choice
        if(!valid) {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please re-enter your response.", PRINT_LINE_SLEEP); std::cout << std::endl;
            response.clear();
        }
    }
}

/*  blackjack_rules - Tells a player the rules to blackjack
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * See inline comments for more details
*   Output:
*       This function does not return a value
*/
void blackjack_rules() {
    clear_terminal();
    // Strings
    std::string Blackjack = color_text(32, "Blackjack");
    std::string Objective = color_text(31, "Objective:");
    std::string CardValues = color_text(31, "Card Values:");
    std::string GamePlay = color_text(31, "Gameplay:");
    std::string AdditionalOptions = color_text(31, "Additional Options:");
    // Prompt player that rules are coming
    std::cout << std::endl; rolling_text("Here are the rules to " + Blackjack + ".", SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; 
    // Objective of game
    rolling_text(Objective, SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; rolling_text("The main goal of blackjack is to beat the dealer by having a hand value as close to 21 as possible without exceeding it. If your hand goes over 21, you 'bust' and lose the game.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl;
    // Card values of game
    rolling_text(CardValues, SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl;
    rolling_text(color_text(31, "1:") + " Number cards (2-10) are worth their face value.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "2:") + " Face cards (Jack, Queen, King) are each worth 10 points.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "3:") + " Aces can be worth either 1 point or 11 points, depending on which value benefits your hand more.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl;
    // Gameplay
    rolling_text(GamePlay, SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl;
    rolling_text(color_text(31, "1:") + " You and the dealer are both dealt two cards. One of the dealer's cards is face-up, while the other is face-down (known as the 'hole' card).", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "2:") + " You can choose to 'hit' (take another card) or 'stand' (keep your current hand). You can continue to hit until you're satisfied with your hand or until you bust.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "3:") + " After all players stand, reach 21, or bust, the dealer reveals their hole card.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "4:") + " The dealer must hit until their hand totals 17 or more. However, the dealer must hit on a 'soft 17' (a hand with an Ace counted as 11).", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "5:") + " The player with a hand value closest to 21 without busting wins. If you and the dealer tie with the same value, it's a 'push,' and you get your bet back.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "6:") + " If you're dealt an Ace and a 10-value card (10, Jack, Queen, King) as your initial two cards, you have a 'blackjack,' which usually pays out at a higher rate (3:2) compared to a regular win.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl;
    // Additional Options
    rolling_text(AdditionalOptions, SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl;
    rolling_text(color_text(31, "1:") + " Split - If your initial two cards are of the same rank (e.g., two 7s), you can choose to split them into two separate hands and continue playing each hand independently.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "2:") + " Double Down - After receiving your first two cards, you can choose to double your initial bet and receive only one more card. This is a risky but potentially rewarding move.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "3:") + " Insurance - Insurance is an optional side bet made when the dealer's face-up card is an Ace, offering a 2:1 payout if the dealer has a blackjack but generally considered less favorable for players in the long run.", SPRINT_LINE_SLEEP); std::cout << std::endl;
    std::string cont;
    while (cont.empty()) {
        std::cout << std::endl; rolling_text("Press a key to continue to the game options: ", PRINT_LINE_SLEEP);
        std::cin >> cont;
        clear_terminal();
    }
}

/*  game_options - Gives a player a set of options for what type of blackjack game that they would like to play
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Prompt the player for if they would like to see the rules
*/
void game_options() {
    // Strings
    std::string Blackjack = color_text(32, "Blackjack");
    // Prompt player to see the rules
    std::cout << std::endl; rolling_text("Would you like to see the rules for " + Blackjack + "?", PRINT_LINE_SLEEP); std::cout << std::endl;
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            std::cout << std::endl; rolling_text("Enter " + color_text(32, "[Y]es") + " for yes.", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
        else {
            rolling_text("Enter " + color_text(31, "[N]o") + " for no.", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
    }
    // Get response from player
    std::string rulesResponse;
    std::vector<std::string> rulesChoices = {"Y", "y", "N", "n"};
    bool rules = false;
    while (!rules) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter your response: ", PRINT_LINE_SLEEP);
        std::cin >> rulesResponse;
        // Check if response is in available choices
        for (int i = 0; i < rulesChoices.size(); i++) {
            if (rulesResponse != rulesChoices[i]) {
                continue;
            }
            else if (rulesResponse == rulesChoices[i]) {
                rules = true;
                // Player wants to see the rules
                if (rulesResponse == "Y" || rulesResponse == "y") {
                    blackjack_rules();
                }
                else {
                    clear_terminal();
                }
                break;
            }
        }
        // User has entered an invalid choice
        if(!rules) {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please re-enter your response.", PRINT_LINE_SLEEP); std::cout << std::endl;
            rulesResponse.clear();
        }
    }
    rolling_text("We will now present you with the current game modes that you can play.", PRINT_LINE_SLEEP); std::cout << std::endl;
    // Present game mode options
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " Single player versus the dealer.", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
        else {
            std::cout << std::endl;
        }
    }
    // Game mode selection
    std::string modeResponse;
    std::vector<std::string> modeChoices = {"1"};
    bool modes = false;
    while (!modes) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter your response: ", PRINT_LINE_SLEEP);
        std::cin >> modeResponse;
        // Check if response is in available choices
        for (int i = 0; i < modeChoices.size(); i++) {
            if (modeResponse != modeChoices[i]) {
                continue;
            }
            else if (modeResponse == modeChoices[i]) {
                modes = true;
                // Player wants to play single player versus the dealer
                if (modeResponse == "1") {
                    std::cout << std::endl; rolling_text("You have chosen to play " + color_text(31, "Single player versus the dealer") + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                    std::cout << std::endl;
                    progress_bar(LONG_TIME_SLEEP, "Preparing single player versus dealer game.", "Ready to play.");
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    single_player_versus_dealer();
                }
                break;
            }
        }
        // User has entered an invalid choice
        if(!modes) {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please re-enter your response.", PRINT_LINE_SLEEP); std::cout << std::endl;
            rulesResponse.clear();
        }
    }
}

/*  single_player_versus_dealer - Processes all the logic that is required for a game of blackjack to be played
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Create hand objects for the players
*       * Set the names of the players in the game
*       * Deposit currency into the players bank
*       * Create a shoe object for the game
*       * Set the minimum cards that need to be left in the shoe to continue playing
*       * Proceed to play a new hand while the cards left in the shoe is greater than "min_card_count" and the player has a positive bank total left
*       * Process the "game_logic" function
*       * Prompt the player if they would like to continue playing if their bank total is greater than zero
*           * If they choose to continue playing, check to see if the number of cards is greater than "min_card_count"
*               * If it is, continue on to the next hand
*               * If it isn't, shuffle a new shoe
*           * If they choose to stop playing, break the while loop and end the game
*       * If the players bank total is zero, prompt the player if they would like re-deposit currency into their bank
*           * If they choose to re-deposit, check to see if the number of cards is greater than "min_card_count"
*               * If it is, continue on to the next hand
*               * If it isn't, shuffle a new shoe
*           * If they choose to not re-deposit, break the while loop and end the game
*       * After the player has chosen to stop playing, create a csv of the stats for the player
*   Output:
*       This function does not return a value
*/
void single_player_versus_dealer() {
    clear_terminal();
    // Create Player objects
    std::shared_ptr<Player> humanPlayer(new Player());
    std::shared_ptr<Player> dealer(new Player());
    // Set the names of the player
    humanPlayer->NamePrompt();
    dealer->SetName("Dealer");
    // Create Shoe object
    std::shared_ptr<Shoe> gameShoe(new Shoe);
    gameShoe->CreateShoePrompt();
    // Rigged Shoe Check
    std::shared_ptr<Card> riggedCard;
    std::shared_ptr<node<Card>> riggedNode;
    // Deposit currency into players bank
    humanPlayer->BankDepositPrompt();
    // float origBank = humanPlayer->GetBankTotal();
    // Card count minimum
    int min_card_count = 13;
    // Play game while the cards in the shoe is greater than 13 and the users bank total is greater than 0
    while (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count && humanPlayer->GetBankTotal() > 0) {
        // Process the game_logic function
        game_logic(humanPlayer, dealer, gameShoe);
        bool continue_playing = false;
        // Continue playing if the player has a bank total of greater than zero
        if (humanPlayer->GetBankTotal() > 0) {
            std::string cont_play;
            // Prompt the player if they want to continue playing, force them to enter either y or n
            while (true) {
                std::cout << std::endl; rolling_text("Would you like to continue playing? " + color_text(32, "Yes (y)") + " or " + color_text(32, "no (n)") + ": ", PRINT_LINE_SLEEP);
                std::cin >> cont_play;
                // Player has chosen to continue playing
                if (cont_play == "y") {
                    // Ample enough cards left in shoe to continue playing
                    if (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count) {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Dealing new hands.");
                        clear_terminal();
                        break;
                    }
                    // Shoe must be reshuffled
                    else {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Shuffling a new shoe.");
                        gameShoe->EmptyShoe();
                        gameShoe->SetNumOfDecks(gameShoe->GetNumOfDecks());
                        gameShoe->CreateShoePrompt();
                        clear_terminal();
                        break;
                    }
                }
                // Player has chosen to stop playing
                else if (cont_play == "n") {
                    std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has chosen to quit playing. Final bank total: " + humanPlayer->GetDisplayBankTotal() + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                    std::cout << std::endl; rolling_text("Thank you for playing " + humanPlayer->GetDisplayName() + "!", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                    clear_terminal();
                    break;
                }
                // Player has entered an incorrect response to the prompt
                else {
                    std::cout << std::endl; rolling_text("Please enter a valid response.",PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                    clear_terminal();
                    cont_play.clear();
                    continue;
                }
            }
            // Set "continue_playing" to true if the player has chosen to continue playing
            if (cont_play == "y") {
                continue_playing = true;
            }
            // Set "continue_playing" to false if the player has chosen to stop playing
            else {
                cont_play = false;
            }
        }
        // Player has run out of currency in their bank
        else {
            std::string redeposit;
            std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has run out of currency in their bank.",PRINT_LINE_SLEEP); std::cout << std::endl;
            // Prompt the player if they want to re-deposit currency into their bank, require them to enter y or n
            while (true) {
                std::cout << std::endl; rolling_text("Would you like to deposit more currency into your bank? " + color_text(32, "Yes (y)") + " or " + color_text(32, "no (n)") + ": ",PRINT_LINE_SLEEP);
                std::cin >> redeposit;
                // Player has chosen to re-deposit currency into their bank
                if (redeposit == "y") {
                    humanPlayer->BankDepositPrompt();
                    // Proceed with same shoe if greater than minimum card count
                    if (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count) {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Dealing new hands.");
                    }
                    // Create new shoe if the current card count in the shoe is less than "min_card_count"
                    else {
                        std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Shuffling a new shoe.");
                        gameShoe->EmptyShoe();
                        gameShoe->SetNumOfDecks(gameShoe->GetNumOfDecks());
                        gameShoe->CreateShoePrompt();
                    }
                    clear_terminal();
                    break;
                }
                // Player has chosen not to re-deposit currency into their bank
                else if (redeposit == "n") {
                    std::cout << std::endl; rolling_text(humanPlayer->GetDisplayName() + " has chosen to not redeposit more currency into their bank. Game over. " + humanPlayer->GetDisplayBankTotal() + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                    std::cout << std::endl; rolling_text("Thank you for playing " + humanPlayer->GetDisplayName() + "!", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                    clear_terminal();
                    break;
                }
                // Player has entered an incorrect response to the prompt
                else {
                    std::cout << std::endl; rolling_text("Please enter a valid response.",PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                    clear_terminal();
                    redeposit.clear();
                    continue;;
                }
            }
            // Set "continue_playing" to true if the player has chosen to re-deposit currency
            if (redeposit == "y") {
                continue_playing = true;
            }
            // Set "continue_playing" to false if the player has chosen not to re-deposit currency
            else {
                continue_playing = false;
            }
        }
        // End the while loop if "continue_playing" has been set to false
        if (!continue_playing) {
            break;
        }
        // Continue the while loop if "continue_playing" has been set to true
        else {
            continue;
        }
    }
    std::string csvFile = csv_generator(humanPlayer);
    plot(csvFile, 4);
}

// /*  simulate_game - Simulates a game of blackjack for given parameters
// *   Input:
// *       There are no input parameters for this function
// *   Algorithm:
// *       * See inline comments
// *   Output:
// *       This function does not return a value, it simulates a game of blackjack
// */
// void simulate_game() {
//     // Prompt player
//     clear_terminal();
//     progress_bar(LONG_TIME_SLEEP, "Preparing Simulation", "Ready To Simulate :)");
//     clear_terminal();
//     std::cout << "You have chosen to simulate a game of blackjack, first we must pick a name for your user." << std::endl;
//     // Create players and parameters for game
//     std::shared_ptr<Player> userPlayer(new Player);
//     std::shared_ptr<Player> dealer(new Player);
//     dealer->SetName("Dealer");
//     userPlayer->NamePrompt();
//     // Create shoe object
//     std::shared_ptr<Shoe> gameShoe(new Shoe);
//     gameShoe->CreateShoePrompt();
//     std::cout << std::endl << "Welcome " << userPlayer->GetDisplayName() << ". We will now have you place an original deposit into your bank." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//     // Bank deposit
//     userPlayer->BankDepositPrompt();
//     float initBank = userPlayer->GetBankTotal();
//     // Wager deposit
//     std::cout << std::endl << "Now we must pick the minimum wager for the table. "; time_sleep(SHORT_TIME_SLEEP);
//     float minWager = 0;
//     while (true) {
//         // Prompt user for min wager
//         std::cout << "Please enter the minimum table amount: "; time_sleep(SHORT_TIME_SLEEP);
//         std::cin >> minWager; time_sleep(SHORT_TIME_SLEEP);
//         const std::type_info& result = typeid(minWager);
//         std::string checkResult = result.name();
//         // Check if value is not a float or integer
//         if (checkResult != "f" && checkResult != "i") {
//             std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//             clear_terminal();
//             checkResult.clear();
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//         // Check if value is a float or integer
//         else if (checkResult == "f" || checkResult == "i") {
//             if (minWager <= 0) {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, round_to_string(minWager)) << ". Please re-enter a positive value." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             if (minWager > initBank) {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, round_to_string(minWager)) << ". Please re-enter a value less than your bank." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             else {
//                 break;
//             }
//         }
//     }
//     std::cout << std::endl << userPlayer->GetDisplayName() << " has decided to have the minimum table wager to be: " << color_text(31, round_to_string(minWager)) << std::endl; time_sleep(SHORT_TIME_SLEEP);
//     // Minimum card count for shoe
//     int minCardCount = 13;
//     // Prompt player to set wager for hand
//     std::cout << std::endl << "For this simulation, you will be betting a constant hand value each time. "; time_sleep(SHORT_TIME_SLEEP);
//     float handWager = 0;
//     while (true) {
//         // Prompt user for wager each hand
//         std::cout << "Please enter the value you'd like to bet for each hand: "; time_sleep(SHORT_TIME_SLEEP);
//         std::cin >> handWager; time_sleep(SHORT_TIME_SLEEP);
//         const std::type_info& result = typeid(handWager);
//         std::string checkResult = result.name();
//         // Check if value is not a float or integer
//         if (checkResult != "f" && checkResult != "i") {
//             std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//             clear_terminal();
//             checkResult.clear();
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//         // Check if value is a float or integer
//         else if (checkResult == "f" || checkResult == "i") {
//             if (handWager <= 0) {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, round_to_string(handWager)) << ". Please re-enter a positive value." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             if (handWager > initBank) {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, round_to_string(handWager)) << ". Please re-enter a value less than your bank." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             if (handWager < minWager) {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(31, round_to_string(handWager)) << ". Please re-enter a value greater than the table minimum." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             else {
//                 break;
//             }
//         }
//     }
//     std::cout << std::endl << userPlayer->GetDisplayName() << " has decided to place a consistent wager of: " << color_text(31, round_to_string(handWager)) << std::endl; time_sleep(SHORT_TIME_SLEEP);
//     // Create string response for first prompt
//     std::string brokeResponse;
//     std::cout << std::endl << "Now, we need to decide how to run this simulation. The first question is would you like to run the simulation until your player is out of currency?" << std::endl; time_sleep(SHORT_TIME_SLEEP);
//     std::cout << std::endl << "Enter (y) for yes and and anything else for no. "; time_sleep(SHORT_TIME_SLEEP);
//     std::cin >> brokeResponse;
//     // Play till broke
//     if (brokeResponse == "y" || brokeResponse == "Y") {
//         std::cout << std::endl << "You have chosen to simulate a game until your player runs out of currency." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         std::cout << std::endl << "We will now simulate a game of blackjack." << std::endl; time_sleep(LONG_TIME_SLEEP);
//         std::cout << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         progress_bar(LONG_TIME_SLEEP, "Compiling Parameters", "Beginning Simulation");
//         std::cout << std::endl;
//         float origWager = handWager;
//         // Play until player runs out of currency
//         while ((gameShoe->GetCardsInShoe()->GetSize() >= minCardCount && userPlayer->GetBankTotal() > 0)) {
//             // Break for bank lower than min wager
//             if (userPlayer->GetBankTotal() < minWager) {
//                 std::cout << "\rSimulation Finished. Final hands played: " << color_text(34, std::to_string(userPlayer->GetHandsPlayed())) << " Final bank total: " << userPlayer->GetDisplayBankTotal() 
//                 << " Final Hands Won: " << color_text(31, std::to_string(userPlayer->GetHandsWon())) << " Final Hands Lost: " << color_text(31, std::to_string(userPlayer->GetHandsLost())) << " Final Hands Pushed: "
//                 << color_text(31, std::to_string(userPlayer->GetHandsPushed())) << " Final Blackjacks: " << color_text(31, std::to_string(userPlayer->GetBlackjackHands())) << std::flush; time_sleep(5);
//                 break;
//             }
//             // Set hand wager for min wager when bank is between min wager and hand wager
//             if (userPlayer->GetBankTotal() >= minWager && userPlayer->GetBankTotal() < handWager) {
//                 handWager = minWager;
//             }
//             // Revert the wager back to the original wager if the bank exceeds it
//             if (userPlayer->GetBankTotal() >= origWager) {
//                 handWager = origWager;
//             }
//             // Process the game logic for a simulated hand
//             game_logic_sim(userPlayer, dealer, gameShoe, handWager);
//             if (gameShoe->GetCardsInShoe()->GetSize() < minCardCount) {
//                 gameShoe->EmptyShoe();
//                 gameShoe->CreateShoeSim();
//                 continue;
//             }
//             else {
//                 std::cout << "\rSimulation running. Current hands played: " << color_text(34, std::to_string(userPlayer->GetHandsPlayed())) << " Current bank total: " << userPlayer->GetDisplayBankTotal() 
//                 << " Current Hands Won: " << color_text(31, std::to_string(userPlayer->GetHandsWon())) << " Current Hands Lost: " << color_text(31, std::to_string(userPlayer->GetHandsLost())) << " Current Hands Pushed: "
//                 << color_text(31, std::to_string(userPlayer->GetHandsPushed())) << " Current Blackjacks: " << color_text(31, std::to_string(userPlayer->GetBlackjackHands())) << std::flush; time_sleep(1);
//             }
//         }
//         // Generate csv of statistics for a game
//         std::string csvFile = csv_generator(userPlayer);
//         // Plot hand number and post hand bank total
//         plot(csvFile, 4);
//     }
//     // Play for other parameters
//     else {
//         std::cout << std::endl << "You have chosen to play until other parameters have been met." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         // Keep track of max number of hands played
//         std::cout << std::endl << "There are a number of ways this simulation can be ran. We can run a simulation until a certain number of hands have been played or if player reaches a desired bank amount." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         int maxHands = 0;
//         while (true) {
//             // Prompt user for max number of hands
//             std::cout << std::endl << "First, what is the max number of hands that you would like to play for? "; time_sleep(SHORT_TIME_SLEEP);
//             std::cin >> maxHands; time_sleep(SHORT_TIME_SLEEP);
//             const std::type_info& result = typeid(maxHands);
//             std::string checkResult = result.name();
//             // Check if value is not a float or integer
//             if (checkResult != "f" && checkResult != "i") {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             // Check if value is a float or integer
//             else if (checkResult == "f" || checkResult == "i") {
//                 if (handWager <= 0) {
//                     std::cout << std::endl << color_text(31, "Invalid Response") << " of " << color_text(32, std::to_string(maxHands)) << ". Please re-enter a positive value." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                     clear_terminal();
//                     checkResult.clear();
//                     std::cin.clear();
//                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                     continue;
//                 }
//                 else {
//                     break;
//                 }
//             }
//         }
//         std::cout << std::endl << userPlayer->GetDisplayName() << " has decided to play for a max number of " << color_text(32, std::to_string(maxHands)) << " hands." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         // Keep an eye out for a specific bank total
//         std::cout << std::endl << "Now, we can keep track of the bank total that you would like to quit playing at. If you do not want to quit playing a specific bank total, enter zero or a negative number." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         float bankTracker = 0;
//         while (true) {
//             // Prompt user for bank value to stop at
//             std::cout << std::endl << "What is the bank total that you would like to quit playing at? "; time_sleep(SHORT_TIME_SLEEP);
//             std::cin >> bankTracker; time_sleep(SHORT_TIME_SLEEP);
//             const std::type_info& result = typeid(maxHands);
//             std::string checkResult = result.name();
//             // Check if value is not a float or integer
//             if (checkResult != "f" && checkResult != "i") {
//                 std::cout << std::endl << color_text(31, "Invalid Response") << ". Please re-enter your submission." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                 clear_terminal();
//                 checkResult.clear();
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                 continue;
//             }
//             // Check if value is a float or integer
//             else if (checkResult == "f" || checkResult == "i") {
//                 round_input(bankTracker);
//                 break;
//             }
//         }
//         if (bankTracker <= 0) {
//             std::cout << std::endl << "This simulation will run until the max number of hands played has been met or if the player runs out of currency before that max number of " << color_text(32, std::to_string(maxHands)) << " hands played." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         }
//         else {
//             std::cout << std::endl << "This simulation will run until the player runs out of currency before the max number of hands has been played of " << color_text(32, std::to_string(maxHands)) << " or if the player obtains a final bank total of " << color_text(33, round_to_string(bankTracker))
//             << " before the max number of hands played of " << color_text(32, std::to_string(maxHands)) << " has been played" << std::endl; time_sleep(SHORT_TIME_SLEEP); 
//         }
//         std::cout << std::endl << "We will now simulate a game of blackjack." << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//         std::cout << std::endl; time_sleep(SHORT_TIME_SLEEP);
//         progress_bar(LONG_TIME_SLEEP, "Compiling Parameters", "Beginning Simulation");
//         std::cout << std::endl;
//         float origWager = handWager;
//         // Play until parameters are met
//         while ((gameShoe->GetCardsInShoe()->GetSize() >= minCardCount && userPlayer->GetBankTotal() > 0)) {
//             // Break for bank lower than min wager
//             if (userPlayer->GetBankTotal() < minWager) {
//                 std::cout << "\rSimulation Finished. Final hands played: " << color_text(34, std::to_string(userPlayer->GetHandsPlayed())) << " Final bank total: " << userPlayer->GetDisplayBankTotal() 
//                 << " Final Hands Won: " << color_text(31, std::to_string(userPlayer->GetHandsWon())) << " Final Hands Lost: " << color_text(31, std::to_string(userPlayer->GetHandsLost())) << " Final Hands Pushed: "
//                 << color_text(31, std::to_string(userPlayer->GetHandsPushed())) << " Final Blackjacks: " << color_text(31, std::to_string(userPlayer->GetBlackjackHands())) << std::flush; time_sleep(5);
//                 break;
//             }
//             // Set hand wager for min wager when bank is between min wager and hand wager
//             if (userPlayer->GetBankTotal() >= minWager && userPlayer->GetBankTotal() < handWager) {
//                 handWager = minWager;
//             }
//             // Revert the wager back to the original wager if the bank exceeds it
//             if (userPlayer->GetBankTotal() >= origWager) {
//                 handWager = origWager;
//             }
//             // Process the game logic for a simulated hand
//             game_logic_sim(userPlayer, dealer, gameShoe, handWager);
//             // Break if max number of hands has been played
//             if (userPlayer->GetHandsPlayed() == maxHands) {
//                 break;
//             }
//             // Break for bank total
//             if (userPlayer->GetBankTotal() >= bankTracker) {
//                 break;
//             }
//             // Re-Shuffle show
//             if (gameShoe->GetCardsInShoe()->GetSize() < minCardCount) {
//                 gameShoe->EmptyShoe();
//                 gameShoe->CreateShoeSim();
//                 continue;
//             }
//             else {
//                 std::cout << "\rSimulation running. Current hands played: " << color_text(34, std::to_string(userPlayer->GetHandsPlayed())) << " Current bank total: " << userPlayer->GetDisplayBankTotal() 
//                 << " Current Hands Won: " << color_text(31, std::to_string(userPlayer->GetHandsWon())) << " Current Hands Lost: " << color_text(31, std::to_string(userPlayer->GetHandsLost())) << " Current Hands Pushed: "
//                 << color_text(31, std::to_string(userPlayer->GetHandsPushed())) << " Current Blackjacks: " << color_text(31, std::to_string(userPlayer->GetBlackjackHands())) << std::flush; time_sleep(1);
//             }
//         }
//         // Generate csv of statistics for a game
//         std::string csvFile = csv_generator(userPlayer);
//         // Plot hand number and post hand bank total
//         plot(csvFile, 4);
//     }
// }