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
                    // Call simulate_options
                    simulate_options();
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

/*  game_rules - Tells a player the rules to blackjack
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * See inline comments for more details
*   Output:
*       This function does not return a value
*/
void game_rules() {
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
                    game_rules();
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
    for (int i = 0; i < 1; i++) {
        if (i == 0) {
            std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " Single player versus the dealer.", PRINT_LINE_SLEEP); std::cout << std::endl;
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
            modeResponse.clear();
        }
    }
}

/*  simulate_choices - Presents a user with the different options for simulating a game of blackjack
*   Input:
*       input - Integer value that indicates the choice selected from simulate_options
*   Algorithm:
*       * Process the logic for what type of options are available from simulate_options
*       * See inline comments for full details
*   Output:
*       This function does not return a value
*/
void simulate_choices(int input) {
    // Strings
    std::string Blackjack = color_text(32, "Blackjack");
    std::string SinglePlayerVDealer = color_text(31, "Single Player Versus Dealer");
    // Single player versus the dealer with perfect strategy and constant wager
    if (input == 1) {
        clear_terminal();
        std::cout << std::endl; rolling_text("For this specific simulation, a simulated player will play " + Blackjack + " with perfect strategy and a constant wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
        std::cout << std::endl; rolling_text("The dealer in this simulation will still adhere to all rules that they must follow.", PRINT_LINE_SLEEP); std::cout << std::endl;
        std::cout << std::endl; rolling_text("For a " + SinglePlayerVDealer + " with " + Blackjack + " strategy simulation, you have a couple of options. Here are the options:", PRINT_LINE_SLEEP); std::cout << std::endl;
        std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " Simulate a game to see how many hands a player can last until they are out of currency:", PRINT_LINE_SLEEP);
        std::cout << std::endl; rolling_text(color_text(31, "[2]:") + " Simulate a game until a player reaches a minimum bank total:", PRINT_LINE_SLEEP);
        std::cout << std::endl; rolling_text(color_text(31, "[3]:") + " Simulate a game until a player reaches a maximum bank total:", PRINT_LINE_SLEEP);
        std::cout << std::endl; rolling_text(color_text(31, "[4]:") + " Simulate a game until a player reaches a total hands played:", PRINT_LINE_SLEEP);
        std::cout << std::endl; rolling_text(color_text(31, "[5]:") + " Simulate a game that incorporates options " + color_text(31, "[2]-[4]") + ":", PRINT_LINE_SLEEP); std::cout << std::endl;
        // Get response from user
        std::string modeResponse;
        std::vector<std::string> modeChoices = {"1","2","3","4","5"};
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
                    // Simulate until player runs out of currency
                    if (modeResponse == "1") {
                        std::cout << std::endl; rolling_text("You have chosen to simulate a game until a player runs out of their currency.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                        spv_out_of_bank();
                    }
                    // Simulate until player reaches a minimum bank total
                    else if (modeResponse == "2") {
                        std::cout << std::endl; rolling_text("You have chosen to simulate a game until a player reaches a minimum bank total.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                        spv_min_bank();
                    }
                    // Simulate until player reaches a minimum bank total
                    else if (modeResponse == "3") {
                        std::cout << std::endl; rolling_text("You have chosen to simulate a game until a player reaches a maximum bank total.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                        spv_max_bank();
                    }
                    // Simulate until a player reaches a total hands played
                    else if (modeResponse == "4") {
                        std::cout << std::endl; rolling_text("You have chosen to simulate a game until a player reaches a total number of hands played.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                        spv_hands_played();
                    }
                    else if (modeResponse == "5") {
                        std::cout << std::endl; rolling_text("You have chosen to simulate a game that incorporates options " + color_text(31, "[2]-[4]") + " of " + SinglePlayerVDealer + ".", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
                        spv_all_options();
                    }
                    break;
                }
            }
            // User has entered an invalid choice
            if(!modes) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please re-enter your response.", PRINT_LINE_SLEEP); std::cout << std::endl;
                modeResponse.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

/*  simulate_options - Presents a user with the options of how to simulate a game in blackjack
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Give a generic overview of the simulated games
*       * Present the player with the first options for what type of simulated game they would like to run
*       * See inline comments for the rest
*   Output:
*       This function does not return a value
*/
void simulate_options() {
    // Strings
    std::string Blackjack = color_text(32, "Blackjack");
    // Show user the options for simulations
    std::cout << std::endl; rolling_text("This program offers a variety of different simulations that can be ran to simulate a game of " + Blackjack + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; rolling_text("We will now present you with the first level of options for simulating a game of " + Blackjack + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
    for (int i = 0; i < 1; i++) {
        if (i == 0) {
            std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " Single player versus the dealer with perfect " + Blackjack + " strategy and a constant wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
        }
    }
    // Game mode selection
    std::string modeResponse;
    std::vector<std::string> modeChoices = {"1"};
    bool modes = false;
    int mode = 0;
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
                    mode = 1;
                    std::cout << std::endl; rolling_text("You have chosen to simulate " + color_text(31, "Single Player Versus The Dealer") + " with " + Blackjack + " strategy and constant wager." , PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(LONG_TIME_SLEEP);
                }
                break;
            }
        }
        // User has entered an invalid choice
        if(!modes) {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please re-enter your response.", PRINT_LINE_SLEEP); std::cout << std::endl;
            modeResponse.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    // Simulate choices call
    simulate_choices(mode);
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
    std::string csvFile = csv_generator(humanPlayer, "Game Results");
    // Plot Bank Totals vs. Hand Numbers
    std::cout << std::endl; rolling_text("Your results will now be plotted, if you wish to save the results, export the image to your desired format.", PRINT_LINE_SLEEP); std::cout << std::endl;
    plot(csvFile, 4);
    clear_terminal();
    // Prompt player if they would like to keep CSV file
    save_results(csvFile);
}

/*  spv_all_options - Simulates a game until a player reaches a set number of parameters
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * See inline comments
*   Output:
*       This function does not return a value
*/
void spv_all_options() {
    clear_terminal();
    progress_bar(LONG_TIME_SLEEP, "Preparing Simulation", "Ready to Simulate");
    clear_terminal();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Create players
    std::shared_ptr<Player> simUser(new Player);
    std::shared_ptr<Player> simDealer(new Player);
    simDealer->SetName("Dealer");
    simUser->SetName("Simulated Player");
    // Create shoe of cards
    std::shared_ptr<Shoe> simShoe(new Shoe);
    simShoe->CreateShoePrompt();
    // Deposit bank
    simUser->BankDepositPrompt();
    // Wager deposit
    std::cout << std::endl; rolling_text("This simulation involves placing a constant wager for every hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
    float hand_wager = 0;
    bool valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the wager you'd like to place every hand: ", PRINT_LINE_SLEEP);
        std::cin >> hand_wager;
        // Check if response is valid
        if (hand_wager > 0) {
            // Wager greater than bank
            if (hand_wager > simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a wager that is less than or equal to your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                hand_wager = 0;
                continue;
            }
            // Valid wager placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen to place a constant wager of " + color_text(31, round_to_string(hand_wager)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Wager less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for a wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            hand_wager = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    // Maximum hands prompt
    int max_hands = 0;
    valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the maximum hands played that you'd like to stop playing at: ", PRINT_LINE_SLEEP);
        std::cin >> max_hands;
        // Maximum hands valid
        if (max_hands > 0) {
            std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen a maximum hands played total of " + color_text(31, std::to_string(max_hands)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
            valid = true;
        }
        // Hands played less than zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for your minimum bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
            max_hands = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    // Maximum bank prompt
    float max_bank = 0;
    valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the maximum bank total that you'd like to stop playing at: ", PRINT_LINE_SLEEP);
        std::cin >> max_bank;
        // Check if response is valid
        if (max_bank > 0) {
            // Maximum bank less than initial bank
            if (max_bank < simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a maximum bank that is greater than your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                max_bank = 0;
                continue;
            }
            // Valid maximum bank placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen a maximum bank total of " + color_text(31, round_to_string(max_bank)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Maximum bank less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for your minimum bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
            max_bank = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    // Minimum bank prompt
    float min_bank = 0;
    valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the minimum bank total that you'd like to stop playing at: ", PRINT_LINE_SLEEP);
        std::cin >> min_bank;
        // Check if response is valid
        if (min_bank >= 0) {
            // Minimum bank total greater than current bank total
            if (min_bank > simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a minimum bank that is less than your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                min_bank = 0;
                continue;
            }
            // Valid maximum bank total
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen a minimum bank total of " + color_text(31, round_to_string(min_bank)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Minimum bank less than zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a nonnegative value for your minimum bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
            min_bank = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    int minCardCount = 13;
    float origWager = hand_wager;
    std::cout << std::endl; rolling_text("This simulation will run until one of the following conditions are met:", PRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " The player's bank total is less than or equal to that of the specified minimum.", PRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "[2]:") + " The player's bank total is greater than or equal to that of the specified maximum.", PRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "[3]:") + " The player has played the max number of specified hands.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
    clear_terminal();
    while (true) {
        // Bank not zero but less than original wager
        if (simUser->GetBankTotal() < hand_wager && simUser->GetBankTotal() > min_bank) {
            // Go all in
            hand_wager = simUser->GetBankTotal();
        }
        // Bank greater than original wager
        if (simUser->GetBankTotal() >= origWager && simUser->GetBankTotal() < max_bank) {
            // Set wager to original wager
            hand_wager = origWager;
        }
        // Process logic of hand(s)
        game_logic_sim(simUser, simDealer, simShoe, hand_wager);
        // Player reaches one of the predetermined parameters
        if (simUser->GetHandsPlayed() == max_hands || simUser->GetBankTotal() <= min_bank || simUser->GetBankTotal() >= max_bank) {
            clear_terminal();
            std::cout << "\rSimulation Finished. Final hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Final bank total: " << simUser->GetDisplayBankTotal() 
            << " Final Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Final Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Final Hands Pushed: "
            << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Final Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(LONG_TIME_SLEEP);
            break;
        }
        // Display stats of game
        std::cout << "\rSimulation running. Current hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Current bank total: " << simUser->GetDisplayBankTotal() 
        << " Current Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Current Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Current Hands Pushed: "
        << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Current Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(1);
        // Re-Shuffle shoe if needed
        if (simShoe->GetCardsInShoe()->GetSize() < minCardCount) {
            simShoe->EmptyShoe();
            simShoe->CreateShoeSim();
            continue;
        }
    }
    // Generate csv of statistics for a game
    std::string csvFile = csv_generator(simUser, "Simulated Game - All Options");
    // Plot Bank Totals vs. Hand Numbers
    std::cout << std::endl; rolling_text("Your results will now be plotted, if you wish to save the results, export the image to your desired format.", PRINT_LINE_SLEEP); std::cout << std::endl;
    plot(csvFile, 4);
    clear_terminal();
    // Prompt player if they would like to keep CSV file
    save_results(csvFile);
}

/*  spv_hands_played - Simulates a game until a player reaches a maximum hands played total
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * See inline comments
*   Output:
*       This function does not return a value
*/
void spv_hands_played() {
    clear_terminal();
    progress_bar(LONG_TIME_SLEEP, "Preparing Simulation", "Ready to Simulate");
    clear_terminal();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Create players
    std::shared_ptr<Player> simUser(new Player);
    std::shared_ptr<Player> simDealer(new Player);
    simDealer->SetName("Dealer");
    simUser->SetName("Simulated Player");
    // Create shoe of cards
    std::shared_ptr<Shoe> simShoe(new Shoe);
    simShoe->CreateShoePrompt();
    // Deposit bank
    simUser->BankDepositPrompt();
    // Wager deposit
    std::cout << std::endl; rolling_text("This simulation involves placing a constant wager for every hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
    float hand_wager = 0;
    bool valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the wager you'd like to place every hand: ", PRINT_LINE_SLEEP);
        std::cin >> hand_wager;
        // Check if response is valid
        if (hand_wager > 0) {
            // Wager greater than bank
            if (hand_wager > simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a wager that is less than or equal to your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                hand_wager = 0;
                continue;
            }
            // Valid wager placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen to place a constant wager of " + color_text(31, round_to_string(hand_wager)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Wager less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for a wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            hand_wager = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    int max_hands = 0;
    valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the maximum hands played that you'd like to stop playing at: ", PRINT_LINE_SLEEP);
        std::cin >> max_hands;
        // Check if response is valid
        if (max_hands > 0) {
            std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen a maximum hands played total of " + color_text(31, std::to_string(max_hands)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
            valid = true;
        }
        // Hands played less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for your maximum hands played.", PRINT_LINE_SLEEP); std::cout << std::endl;
            max_hands = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    int minCardCount = 13;
    float origWager = hand_wager;
    std::cout << std::endl; rolling_text("This simulation will run until one of the following conditions is met:", PRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " The player runs out of currency in their bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "[2]:") + " The player has reached the maximum number of hands played.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
    clear_terminal();
    while (true) {
        // Bank not zero but less than original wager
        if (simUser->GetBankTotal() < hand_wager) {
            // Go all in
            hand_wager = simUser->GetBankTotal();
        }
        // Bank greater than original wager
        if (simUser->GetBankTotal() >= origWager) {
            // Set wager to original wager
            hand_wager = origWager;
        }
        // Process logic of hand(s)
        game_logic_sim(simUser, simDealer, simShoe, hand_wager);
        // Player reaches maximum bank total or is out of currency
        if (simUser->GetHandsPlayed() == max_hands || simUser->GetBankTotal() == 0) {
            clear_terminal();
            std::cout << "\rSimulation Finished. Final hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Final bank total: " << simUser->GetDisplayBankTotal() 
            << " Final Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Final Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Final Hands Pushed: "
            << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Final Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(LONG_TIME_SLEEP);
            break;
        }
        // Display stats of game
        std::cout << "\rSimulation running. Current hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Current bank total: " << simUser->GetDisplayBankTotal() 
        << " Current Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Current Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Current Hands Pushed: "
        << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Current Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(1);
        // Re-Shuffle shoe if needed
        if (simShoe->GetCardsInShoe()->GetSize() < minCardCount) {
            simShoe->EmptyShoe();
            simShoe->CreateShoeSim();
            continue;
        }
    }
    // Generate csv of statistics for a game
    std::string csvFile = csv_generator(simUser, "Simulated Game - Maximum Hands Played Simulation");
    // Plot Bank Totals vs. Hand Numbers
    std::cout << std::endl; rolling_text("Your results will now be plotted, if you wish to save the results, export the image to your desired format.", PRINT_LINE_SLEEP); std::cout << std::endl;
    plot(csvFile, 4);
    clear_terminal();
    // Prompt player if they would like to keep CSV file
    save_results(csvFile);
}

/*  spv_max_bank - Simulates a game until a player reaches a minimum bank total
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * See inline comments
*   Output:
*       This function does not return a value
*/
void spv_max_bank() {
    clear_terminal();
    progress_bar(LONG_TIME_SLEEP, "Preparing Simulation", "Ready to Simulate");
    clear_terminal();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Create players
    std::shared_ptr<Player> simUser(new Player);
    std::shared_ptr<Player> simDealer(new Player);
    simDealer->SetName("Dealer");
    simUser->SetName("Simulated Player");
    // Create shoe of cards
    std::shared_ptr<Shoe> simShoe(new Shoe);
    simShoe->CreateShoePrompt();
    // Deposit bank
    simUser->BankDepositPrompt();
    // Wager deposit
    std::cout << std::endl; rolling_text("This simulation involves placing a constant wager for every hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
    float hand_wager = 0;
    bool valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the wager you'd like to place every hand: ", PRINT_LINE_SLEEP);
        std::cin >> hand_wager;
        // Check if response is valid
        if (hand_wager > 0) {
            // Wager greater than bank
            if (hand_wager > simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a wager that is less than or equal to your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                hand_wager = 0;
                continue;
            }
            // Valid wager placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen to place a constant wager of " + color_text(31, round_to_string(hand_wager)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Wager less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for a wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            hand_wager = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    float max_bank = 0;
    valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the maximum bank total that you'd like to stop playing at: ", PRINT_LINE_SLEEP);
        std::cin >> max_bank;
        // Check if response is valid
        if (max_bank > 0) {
            // Maximum bank is less than bank
            if (max_bank < simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a maximum bank that is greater than your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                max_bank = 0;
                continue;
            }
            // Valid maximum bank placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen a maximum bank total of " + color_text(31, round_to_string(max_bank)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Wager less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for your maximum bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
            max_bank = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    int minCardCount = 13;
    float origWager = hand_wager;
    std::cout << std::endl; rolling_text("This simulation will run until one of the following conditions is met:", PRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " The player runs out of currency in their bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
    rolling_text(color_text(31, "[2]:") + " The player has reached the maximum bank total.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
    clear_terminal();
    while (true) {
        // Bank not zero but less than original wager
        if (simUser->GetBankTotal() < hand_wager && simUser->GetBankTotal() < max_bank) {
            // Go all in
            hand_wager = simUser->GetBankTotal();
        }
        // Bank greater than original wager
        if (simUser->GetBankTotal() >= origWager && simUser->GetBankTotal() < max_bank) {
            // Set wager to original wager
            hand_wager = origWager;
        }
        // Process logic of hand(s)
        game_logic_sim(simUser, simDealer, simShoe, hand_wager);
        // Player reaches maximum bank total or is out of currency
        if (simUser->GetBankTotal() >= max_bank || simUser->GetBankTotal() == 0) {
            clear_terminal();
            std::cout << "\rSimulation Finished. Final hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Final bank total: " << simUser->GetDisplayBankTotal() 
            << " Final Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Final Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Final Hands Pushed: "
            << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Final Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(LONG_TIME_SLEEP);
            break;
        }
        // Display stats of game
        std::cout << "\rSimulation running. Current hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Current bank total: " << simUser->GetDisplayBankTotal() 
        << " Current Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Current Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Current Hands Pushed: "
        << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Current Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(1);
        // Re-Shuffle shoe if needed
        if (simShoe->GetCardsInShoe()->GetSize() < minCardCount) {
            simShoe->EmptyShoe();
            simShoe->CreateShoeSim();
            continue;
        }
    }
    // Generate csv of statistics for a game
    std::string csvFile = csv_generator(simUser, "Simulated Game - Maximum Bank Simulation");
    // Plot Bank Totals vs. Hand Numbers
    std::cout << std::endl; rolling_text("Your results will now be plotted, if you wish to save the results, export the image to your desired format.", PRINT_LINE_SLEEP); std::cout << std::endl;
    plot(csvFile, 4);
    clear_terminal();
    // Prompt player if they would like to keep CSV file
    save_results(csvFile);
}

/*  spv_min_bank - Simulates a game until a player reaches a minimum bank total
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * See inline comments
*   Output:
*       This function does not return a value
*/
void spv_min_bank() {
    clear_terminal();
    progress_bar(LONG_TIME_SLEEP, "Preparing Simulation", "Ready to Simulate");
    clear_terminal();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Create players
    std::shared_ptr<Player> simUser(new Player);
    std::shared_ptr<Player> simDealer(new Player);
    simDealer->SetName("Dealer");
    simUser->SetName("Simulated Player");
    // Create shoe of cards
    std::shared_ptr<Shoe> simShoe(new Shoe);
    simShoe->CreateShoePrompt();
    // Deposit bank
    simUser->BankDepositPrompt();
    // Wager deposit
    std::cout << std::endl; rolling_text("This simulation involves placing a constant wager for every hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
    float hand_wager = 0;
    bool valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the wager you'd like to place every hand: ", PRINT_LINE_SLEEP);
        std::cin >> hand_wager;
        // Check if response is valid
        if (hand_wager > 0) {
            // Wager greater than bank
            if (hand_wager > simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a wager that is less than or equal to your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                hand_wager = 0;
                continue;
            }
            // Valid wager placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen to place a constant wager of " + color_text(31, round_to_string(hand_wager)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Wager less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for a wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            hand_wager = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    float min_bank = 0;
    valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the minimum bank total that you'd like to stop playing at: ", PRINT_LINE_SLEEP);
        std::cin >> min_bank;
        // Check if response is valid
        if (min_bank >= 0) {
            // Minimum bank greater than bank
            if (min_bank > simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a minimum bank that is less than your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                min_bank = 0;
                continue;
            }
            // Valid minimum bank placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen a minimum bank total of " + color_text(31, round_to_string(min_bank)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Wager less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for your minimum bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
            min_bank = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    int minCardCount = 13;
    float origWager = hand_wager;
    std::cout << std::endl; rolling_text("This simulation will run until one of the following conditions is met:", PRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " The player has reached the minimum bank total or less.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
    clear_terminal();
    while (true) {
        // Bank not zero but less than original wager
        if (simUser->GetBankTotal() < hand_wager && simUser->GetBankTotal() > min_bank) {
            // Go all in
            hand_wager = simUser->GetBankTotal();
        }
        // Bank greater than original wager
        if (simUser->GetBankTotal() >= origWager && simUser->GetBankTotal() > min_bank) {
            // Set wager to original wager
            hand_wager = origWager;
        }
        // Process logic of hand(s)
        game_logic_sim(simUser, simDealer, simShoe, hand_wager);
        // Player reaches minimum bank total
        if (simUser->GetBankTotal() <= min_bank) {
            clear_terminal();
            std::cout << "\rSimulation Finished. Final hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Final bank total: " << simUser->GetDisplayBankTotal() 
            << " Final Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Final Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Final Hands Pushed: "
            << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Final Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(LONG_TIME_SLEEP);
            break;
        }
        // Display stats of game
        std::cout << "\rSimulation running. Current hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Current bank total: " << simUser->GetDisplayBankTotal() 
        << " Current Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Current Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Current Hands Pushed: "
        << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Current Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(1);
        // Re-Shuffle shoe if needed
        if (simShoe->GetCardsInShoe()->GetSize() < minCardCount) {
            simShoe->EmptyShoe();
            simShoe->CreateShoeSim();
            continue;
        }
    }
    // Generate csv of statistics for a game
    std::string csvFile = csv_generator(simUser, "Simulated Game - Minimum Bank Simulation");
    // Plot Bank Totals vs. Hand Numbers
    std::cout << std::endl; rolling_text("Your results will now be plotted, if you wish to save the results, export the image to your desired format.", PRINT_LINE_SLEEP); std::cout << std::endl;
    plot(csvFile, 4);
    clear_terminal();
    // Prompt player if they would like to keep CSV file
    save_results(csvFile);
}

/*  spv_out_of_bank - Simulates a game until a player runs out of currency in their bank
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * See inline comments
*   Output:
*       This function does not return a value
*/
void spv_out_of_bank() {
    clear_terminal();
    progress_bar(LONG_TIME_SLEEP, "Preparing Simulation", "Ready to Simulate");
    clear_terminal();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Create players
    std::shared_ptr<Player> simUser(new Player);
    std::shared_ptr<Player> simDealer(new Player);
    simDealer->SetName("Dealer");
    simUser->SetName("Simulated Player");
    // Create shoe of cards
    std::shared_ptr<Shoe> simShoe(new Shoe);
    simShoe->CreateShoePrompt();
    // Deposit bank
    simUser->BankDepositPrompt();
    // Wager deposit
    std::cout << std::endl; rolling_text("This simulation involves placing a constant wager for every hand.", PRINT_LINE_SLEEP); std::cout << std::endl;
    float hand_wager = 0;
    bool valid = false;
    // Check for validity
    while (!valid) {
        // Prompt user for choices
        std::cout << std::endl; rolling_text("Enter the wager you'd like to place every hand: ", PRINT_LINE_SLEEP);
        std::cin >> hand_wager;
        // Check if response is valid
        if (hand_wager > 0) {
            // Wager greater than bank
            if (hand_wager > simUser->GetBankTotal()) {
                std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter a wager that is less than or equal to your initial bank.", PRINT_LINE_SLEEP); std::cout << std::endl;
                hand_wager = 0;
                continue;
            }
            // Valid wager placed
            else {
                std::cout << std::endl; rolling_text(simUser->GetDisplayName() + " has chosen to place a constant wager of " + color_text(31, round_to_string(hand_wager)) + ".", PRINT_LINE_SLEEP); std::cout << std::endl;
                valid = true;
            }
        }
        // Wager less than or equal to zero
        else {
            std::cout << std::endl; rolling_text(color_text(31, "Invalid Response") + ". Please enter positive value for a wager.", PRINT_LINE_SLEEP); std::cout << std::endl;
            hand_wager = 0;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
    int minCardCount = 13;
    float origWager = hand_wager;
    std::cout << std::endl; rolling_text("This simulation will run until one of the following conditions is met:", PRINT_LINE_SLEEP); std::cout << std::endl;
    std::cout << std::endl; rolling_text(color_text(31, "[1]:") + " The player is out of currency.", PRINT_LINE_SLEEP); std::cout << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
    clear_terminal();
    while (true) {
        // Bank not zero but less than original wager
        if (simUser->GetBankTotal() < hand_wager && simUser->GetBankTotal() > 0) {
            // Go all in
            hand_wager = simUser->GetBankTotal();
        }
        // Bank greater than original wager
        if (simUser->GetBankTotal() >= origWager) {
            // Set wager to original wager
            hand_wager = origWager;
        }
        // Process logic of hand(s)
        game_logic_sim(simUser, simDealer, simShoe, hand_wager);
        // Player is out of currency
        if (simUser->GetBankTotal() == 0) {
            clear_terminal();
            std::cout << "\rSimulation Finished. Final hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Final bank total: " << simUser->GetDisplayBankTotal() 
            << " Final Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Final Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Final Hands Pushed: "
            << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Final Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(LONG_TIME_SLEEP);
            break;
        }
        // Display stats of game
        std::cout << "\rSimulation running. Current hands played: " << color_text(34, std::to_string(simUser->GetHandsPlayed())) << " Current bank total: " << simUser->GetDisplayBankTotal() 
        << " Current Hands Won: " << color_text(31, std::to_string(simUser->GetHandsWon())) << " Current Hands Lost: " << color_text(31, std::to_string(simUser->GetHandsLost())) << " Current Hands Pushed: "
        << color_text(31, std::to_string(simUser->GetHandsPushed())) << " Current Blackjacks: " << color_text(31, std::to_string(simUser->GetBlackjackHands())) << std::flush; time_sleep(1);
        // Re-Shuffle shoe if needed
        if (simShoe->GetCardsInShoe()->GetSize() < minCardCount) {
            simShoe->EmptyShoe();
            simShoe->CreateShoeSim();
            continue;
        }
    }
    // Generate csv of statistics for a game
    std::string csvFile = csv_generator(simUser, "Simulated Game - Max Hands Played");
    // Plot Bank Totals vs. Hand Numbers
    std::cout << std::endl; rolling_text("Your results will now be plotted, if you wish to save the results, export the image to your desired format.", PRINT_LINE_SLEEP); std::cout << std::endl;
    plot(csvFile, 4);
    clear_terminal();
    // Prompt player if they would like to keep CSV file
    save_results(csvFile);
}