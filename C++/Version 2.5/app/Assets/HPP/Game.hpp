// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/Game.h"

/*  play_game - Processes all the logic that is required for a game of blackjack to be played
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
void play_game() {
    clear_terminal();
    progress_bar(LONG_TIME_SLEEP, "Loading Game", "Ready To Play :)");
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
    // Deposit currency into players bank
    humanPlayer->BankDepositPrompt();
    // float origBank = humanPlayer->GetBankTotal();
    deal_hand(humanPlayer, dealer, gameShoe);
//     // Card count minimum
//     int min_card_count = 13;
//     // Play game while the cards in the shoe is greater than 13 and the users bank total is greater than 0
//     while (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count && humanHand->GetBankTotal() > 0) {
//         // Process the game_logic function
//         auto gameLogic = game_logic(humanHand, dealerHand, gameShoe);
//         humanHand->CopyVariables(std::get<0>(gameLogic));
//         dealerHand->CopyVariables(std::get<1>(gameLogic));
//         gameShoe = std::get<2>(gameLogic);
//         bool continue_playing = false;
//         // Continue playing if the player has a bank total of greater than zero
//         if (humanHand->GetBankTotal() > 0) {
//             std::string cont_play;
//             // Prompt the player if they want to continue playing, force them to enter either y or n
//             while (true) {
//                 std::cout << std::endl << "Would you like to continue playing? (y/n): "; time_sleep(SHORT_TIME_SLEEP);
//                 std::cin >> cont_play; time_sleep(SHORT_TIME_SLEEP);
//                 // Player has chosen to continue playing
//                 if (cont_play == "y") {
//                     // Ample enough cards left in shoe to continue playing
//                     if (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count) {
//                         std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Dealing new hands.");
//                         clear_terminal();
//                         break;
//                     }
//                     // Shoe must be reshuffled
//                     else {
//                         std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Shuffling a new shoe.");
//                         gameShoe->EmptyShoe();
//                         gameShoe->SetNumOfDecks(gameShoe->GetNumOfDecks());
//                         gameShoe->CreateShoePrompt();
//                         clear_terminal();
//                         break;
//                     }
//                 }
//                 // Player has chosen to stop playing
//                 else if (cont_play == "n") {
//                     std::cout << std::endl << humanHand->GetDisplayName() << " has chosen to quit playing. Final bank total: " << humanHand->GetDisplayBankTotal() << std::endl; time_sleep(SHORT_TIME_SLEEP);
//                     std::cout << std::endl << "Thank you for playing " << humanHand->GetDisplayName() << "!" << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                     clear_terminal();
//                     break;
//                 }
//                 // Player has entered an incorrect response to the prompt
//                 else {
//                     clear_terminal();
//                     cont_play.clear();
//                     continue;
//                 }
//             }
//             // Set "continue_playing" to true if the player has chosen to continue playing
//             if (cont_play == "y") {
//                 continue_playing = true;
//             }
//             // Set "continue_playing" to false if the player has chosen to stop playing
//             else {
//                 cont_play = false;
//             }
//         }
//         // Player has run out of currency in their bank
//         else {
//             std::string redeposit;
//             std::cout << std::endl << humanHand->GetDisplayName() << " has run out of currency in their bank." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//             // Prompt the player if they want to re-deposit currency into their bank, require them to enter y or n
//             while (true) {
//                 std::cout << std::endl << "Would you like to deposit more currency into your bank? (y/n): "; time_sleep(SHORT_TIME_SLEEP);
//                 std::cin >> redeposit; time_sleep(SHORT_TIME_SLEEP);
//                 // Player has chosen to re-deposit currency into their bank
//                 if (redeposit == "y") {
//                     humanHand->BankDepositPrompt(); time_sleep(MEDIUM_TIME_SLEEP);
//                     // Proceed with same shoe if greater than minimum card count
//                     if (gameShoe->GetCardsInShoe()->GetSize() >= min_card_count) {
//                         std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Dealing new hands.");
//                     }
//                     // Create new shoe if the current card count in the shoe is less than "min_card_count"
//                     else {
//                         std::cout << std::endl; progress_bar(LONG_TIME_SLEEP, std::to_string(gameShoe->GetCardsInShoe()->GetSize()) + " cards left in shoe.", "Shuffling a new shoe.");
//                         gameShoe->EmptyShoe();
//                         gameShoe->SetNumOfDecks(gameShoe->GetNumOfDecks());
//                         gameShoe->CreateShoePrompt();
//                     }
//                     clear_terminal();
//                     break;
//                 }
//                 // Player has chosen not to re-deposit currency into their bank
//                 else if (redeposit == "n") {
//                     std::cout << std::endl << humanHand->GetDisplayName() << " has chosen to not redeposit more currency into their bank. Game over." << std::endl; time_sleep(SHORT_TIME_SLEEP);
//                     std::cout << std::endl << "Thank you for playing " << humanHand->GetDisplayName() << "!" << std::endl; time_sleep(MEDIUM_TIME_SLEEP);
//                     clear_terminal();
//                     break;
//                 }
//                 // Player has entered an incorrect response to the prompt
//                 else {
//                     clear_terminal();
//                     redeposit.clear();
//                     continue;;
//                 }
//             }
//             // Set "continue_playing" to true if the player has chosen to re-deposit currency
//             if (redeposit == "y") {
//                 continue_playing = true;
//             }
//             // Set "continue_playing" to false if the player has chosen not to re-deposit currency
//             else {
//                 continue_playing = false;
//             }
//         }
//         // End the while loop if "continue_playing" has been set to false
//         if (!continue_playing) {
//             break;
//         }
//         // Continue the while loop if "continue_playing" has been set to true
//         else {
//             continue;
//         }
//     }
//     std::string csvFile = csv_generator(humanHand);
//     plot(csvFile, 4);
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