    #include <iostream>
    #include <string>
    #include <string.h>
    #include <cstdlib>
    #include <ctime>
    #include <vector>
    #include <unordered_map>
    #include <limits>
    #include <fstream>
    #include <algorithm>



    using namespace std;



    class Player {

    public:
        Player(string name) : name(name) {
            int lb = 200;
            int ub = 1000;
            srand(time(0));
            money = (rand() % (ub - lb + 1)) + lb;
        }

        void changeMoney(int amount){
            money = money + amount;
        }
        float getMoney(){
            return money;
        }
        string getName(){
            return name;
        }


    private:
        string name;
        float money;
    };

    class Game{
    public:
        virtual void play(Player& player) = 0;
        void resultGame(int amount,Player &player){
            if (amount > 0)
                cout << "Congratulations you won: " << amount << " dollars" << endl;

            else if(amount < 0)
                cout << "Unfortunately you lost: " << amount << " dollars" << endl;
            else
                cout <<"You didn't win or lose" << endl;

            player.changeMoney(amount);
            cout << "Your balance now is: " << player.getMoney() << endl;
        }

         int make_bet(Player &player){
            int bet = 0;
            cout << "How much would you like to bet" << endl;
            cin >> bet;
            if (bet <= 0 ){
                cout << "Not a valid bet" << endl;
                return 1;
            }
            if(bet > player.getMoney()){
                cout << "Not enough Money"<<endl;
                return make_bet(player );
            }
            cout << "Your bet is " << bet << " dollars" << endl;
            return bet;
        }




    };
    class SlotMachine: public Game{
    public:
        string getRandomSymbol(const std::vector<std::pair<std::string, int>>& symbols) {
            int totalWeight = 0;
            for (const auto& symbol : symbols) {
                totalWeight += symbol.second;
            }

            int randomValue = rand() % totalWeight;
            int cumulativeWeight = 0;

            for (const auto& symbol : symbols) {
                cumulativeWeight += symbol.second;
                if (randomValue < cumulativeWeight) {
                    return symbol.first;
                }
            }

            return symbols.back().first; // Fallback, should not reach here
        }
        int makespin(){
            vector<std::pair<std::string, int>> symbols = {
                    {"🍋", 30}, // Common
                    {"🍌", 30}, // Common
                    {"🍒", 20}, // Uncommon
                    {"♥️", 20}, // Uncommon
                    {"♣️", 10}, // Rare
                    {"♦️", 10}, // Rare
                    {"💎", 5},  // Very rare
                    {"👑", 2}   // Very rare
            };
            unordered_map<std::string, int> payouts = {
                    {"🍋", 1},
                    {"🍌", 1},
                    {"🍒", 2},
                    {"♥️", 2},
                    {"♣️", 3},
                    {"♦️", 3},
                    {"💎", 5},
                    {"👑", 10}
            };
            // Populate the slot line with random symbols
            vector<std::string> slotLine(3);
            for (int i = 0; i < 3; i++) {
                slotLine[i] = getRandomSymbol(symbols);
            }
            for (const auto& symbol : slotLine) {
                std::cout << symbol << " ";
            }
            std::cout << std::endl;
            cout << endl;
            int payout = 0;
            if (slotLine[0] == slotLine[1] && slotLine[1] == slotLine[2]) {
                // Three of a kind
                payout = payouts[slotLine[0]] * payouts[slotLine[0]] * payouts[slotLine[0]];
                std::cout << "You win! Three " << slotLine[0] << "s in a line. Payout: " << payout << "x" << std::endl;
            } else if (slotLine[0] == slotLine[1]) {
                // First two symbols match
                payout = payouts[slotLine[0]];
                std::cout << "You win! The first two symbols are the same: " << slotLine[0] << ". Payout: " << payout+1<< "x" << std::endl;
            } else {
                std::cout << "You lose. No matching symbols." << std::endl;
            }

            return payout;
        }
        void play(Player &player) override{



            int bet = make_bet(player);
            int b = -1;
            while(b != 0 and player.getMoney() > 0){
                cout << "Starting the game" << endl;
                cout << "0: Exit " << endl;
                cout <<"1: make a spin" << endl;
                cout <<"2: Change the bet"<<endl;
                cin >> b;
                if (cin.fail()) {
                    cout << "Invalid input. Please enter a valid option." << endl;
                    // Clear the error flag on cin
                    cin.clear();
                    // Ignore the rest of the line up to the maximum number of characters in a stream
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                    }
                if(b != 2 and b != 0 and b != 1){
                    cout <<"Not a valid option"<<endl;
                    return;
                }

                switch(b){
                    case(2): bet = make_bet(player);
                        break;
                    case(0):
                        b = 0;
                        break;
                    case(1):
                        if (player.getMoney() < bet){
                            cout <<"Your balance is not enough, lower the bet or exit the game"<<endl;
                            break;
                        }
                        int amount = makespin() * bet;
                            if (amount == 0){
                                amount = -bet;
                            }

                        resultGame(amount,player);
                        break;


                }



            }
        }
    };
    class BlackJack: public Game{
    public:
            void play(Player &player) override{ //ace implementation
                int deck[52] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
                // 11 - Jack, 12 - Queen, 13 - King, 14 - Ace

                int dealer_hand[2];
                int player_hand[5] = {0,0,0,0,0};

                int bet;
                bet = make_bet(player);

                cout << ">>>Starting the round" << endl;
                cout << ">>>Dealer gives you a card and himself a card" << endl;

                player_hand[0] = random_card(deck);
                cout << "Your hand: " << player_hand[0] << endl;

                dealer_hand[0] = random_card(deck);
                cout << "Dealer's hand: " << dealer_hand[0] << endl;

                cout << ">>>Dealer gives you a card and himself a card" << endl;

                player_hand[1] = random_card(deck);
                cout << "Your hand: " << player_hand[0] << " + " <<player_hand[1] << endl;

                dealer_hand[1] = random_card(deck);
                cout << "Dealer's hand: " << dealer_hand[0] << " + " <<"Hidden" << endl;

                int sum_hand = player_hand[0] + player_hand[1] + player_hand[2] + player_hand[3] + player_hand[4];

                int current_index = 1;
                while(sum_hand < 21){
                    current_index++;
                    char answer;
                    cout << "Would you like another card?: Y/N" << endl;
                    cin >> answer;
                    if(answer != 'Y' or answer !='N'){
                        cout <<"Not a valid option"<<endl;
                        cin >> answer;
                    }

                    if (answer == 'N'){
                        break;
                    }
                    if (answer != 'Y'){
                        cout << "Not a valid option" << endl;
                        return;
                    }

                    player_hand[current_index] = random_card(deck);
                    sum_hand = player_hand[0] + player_hand[1] + player_hand[2] + player_hand[3] + player_hand[4];
                    cout << "Your hand: " << player_hand[0];
                    for(int i = 1; i <= current_index;i++){
                        cout << " + ";
                        cout << player_hand[i];

                    }
                    cout << endl;
                }
                cout << ">>>Results" << endl;
                cout << "Dealer's hand: " << dealer_hand[0] << " + " <<dealer_hand[1] << endl;
                int dealers_sum = dealer_hand[0] + dealer_hand[1];
                sum_hand = player_hand[0] + player_hand[1] + player_hand[2] + player_hand[3] + player_hand[4];

                int amount;
                if (sum_hand > 21){
                    cout << "Your hand is over 21, you lost" << endl;
                    amount = -bet;
                }
                else if(sum_hand == dealers_sum || (dealers_sum > 21 && sum_hand > 21)){
                    cout << "Tie, your hands are equal"<< endl;
                    amount = 0 ;
                }
                else if(sum_hand == 21){
                    cout << "BlackJack!!!" << endl;
                    cout << "Congratulations you won" << endl; //deleete later
                    amount = bet * 1.5;
                }
                else if (dealers_sum > 21 || (sum_hand > dealers_sum && sum_hand < 21) ){
                    cout << "Congratulations you won" << endl; // delete later
                    amount = bet;
                }
                else{
                    cout << "Unfortunately you lost" <<endl; // delete later
                    amount = -bet;
                }


                resultGame(amount,player);
            };
        int random_card(int deck[]){
            int deck_index;
            int card;
            do{
                deck_index = rand() % 52;
            }while(deck[deck_index] == 0);

            card = deck[deck_index];
            deck[deck_index] = 0;
            return card;
    //        if(card = 14)
    //            /////////////////implemnt
    //            return 0;

            if (card > 10){
                card = 10;
            }

            return card;
        }


    };

    class Ruletka: public Game{
    public:
        int choose_number(){
            int number;
            string winning_number;

            cout << "What number would you like to bet on(0-36): ";
            cin >> number;
            if (number < 0 or number > 36){
                cout << "Your number isn't in the range"<< endl;
                choose_number();
            }
            else{

                return number;

            }

        }

        string choose_property(){
            char property[100];
            string winning_property;
            cout << "Would you like to bet on Even or Odd numbers?(Odd,Even,O,E): ";
            cin >> property;
            // not sure if it works

            if (strcmp(property,"O") == 0 || strcmp(property,"Odd") == 0){
                winning_property = "Odd";

            }
            else if(strcmp(property,"E") == 0 || strcmp(property,"Even") == 0){
                winning_property = "Even";

            }
            else{
                cout << "Your choice isn't Odd,Even or O,E " << endl;
                choose_property();
            }
            return winning_property;


        }

        string choose_color(){
            char color[4];
            string winning_color;
            cout << "Choose the color(Red,Black,R,B): ";

            cin >> color;
            if (strcmp(color,"R") == 0 or strcmp(color,"Red") == 0){
                winning_color = "Red";

            }
            else if(strcmp(color,"B") == 0 or strcmp(color,"Black") == 0){
                winning_color = "Black";

            }
            else{
                cout << "Your choice isn't Red,Black or R,B " << endl;
                choose_color();
            }
            return winning_color;

        }


        void play(Player &player) override{
            int winning_number = -1;
            string winning_property = "";
            string winning_color = "";


            int b = 1;
            cout << "Make your bets" <<endl;


                cout <<"0: Exit"<<endl;
                cout <<"1: Bet on a single number" << endl;
                cout <<"2: Bet on a color(Red/Black)" <<endl;
                cout <<"3: bet on the propetry(Odd/Even)"<<endl;
                cin >> b;
                if (cin.fail()) {
                    cout << "Invalid input. Please enter a valid option." << endl;
                    // Clear the error flag on cin
                    cin.clear();
                    // Ignore the rest of the line up to the maximum number of characters in a stream
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                     // Skip the rest of the loop and prompt again
                     return;
                }
                if(b != 2 and b != 0 and b != 1 and b!=3){
                    cout <<"Not a valid option"<<endl;
                    return;
                }


                switch(b) {
                    case 0:
                        return;
                        break;
                    case 1:
                        winning_number = choose_number();
                        break;
                    case 2:
                        winning_color = choose_color();
                        break;
                    case 3:
                        winning_property = choose_property();
                        cout << winning_property<<endl;
                        break;
                }




            int bet_amount = make_bet(player);
            int d;

            cout << ">>>The Roulete is spinning" << endl;



        int the_winning_number = rand() % 37;

        string color;
        string property;
        if ((the_winning_number >= 1 and the_winning_number <= 10) or (the_winning_number >= 19 and the_winning_number <= 28)){
            if(the_winning_number%2 == 0){
                color = "Black";
                property = "Even";
            }
            else{
                color = "Red";
                property = "Odd";
            }
        }
        else if(the_winning_number != 0){
            if(the_winning_number%2 == 0){
                color = "Red";
                property = "Even";

            }
            else{
                color = "Black";
                property = "Odd";
            }

        }
        cout << "The number is: " << the_winning_number << " " << color << endl;

        int amount;
        int cof;
        if(winning_number != -1){
            cof = 35;

        }
        else{
            cof = 1;
        }

            amount = -bet_amount;
            if (b == 1 && winning_number == the_winning_number) {
                amount = bet_amount * 35;
            } else if (b == 2 && winning_color == color) {
                amount = bet_amount * 1;
            } else if (b == 3 && winning_property == property) {
                amount = bet_amount * 1;
            }
        resultGame(amount,player);

    }

    };
    class Casino {
    private:
        pair<string, float> topPlayers[100];
        int currentSize;
        const string topPlayersFile = "top_players.txt";

    public:
        Casino() : currentSize(0) {
            loadTopPlayers();
        }

        ~Casino() {
            saveTopPlayers();
        }

        void updateTopPlayers(Player &player) {
            if (currentSize < 100) {
                topPlayers[currentSize++] = {player.getName(), player.getMoney()};
            } else {
                topPlayers[99] = {player.getName(), player.getMoney()};
            }
            sort(topPlayers, topPlayers + currentSize, [](const auto& a, const auto& b) {
                return a.second > b.second;
            });
            if (currentSize > 100) {
                currentSize = 100;
            }
        }

        void loadTopPlayers() {
            ifstream file(topPlayersFile);
            string name;
            float money;
            currentSize = 0;
            while (file >> name >> money && currentSize < 100) {
                topPlayers[currentSize++] = {name, money};
            }
        }

        void saveTopPlayers() {
            ofstream file(topPlayersFile);
            for (int i = 0; i < currentSize; ++i) {
                file << topPlayers[i].first << " " << topPlayers[i].second << endl;
            }
        }

        void showTopPlayers() {
            for (int i = 0; i < currentSize; ++i) {
                cout << topPlayers[i].first << ": " << topPlayers[i].second << endl;
            }
        }
    };
    int main() {
        cout << "Hello, Brother!, what's your name" << endl;
        string name;
        cin >> name;
        Player player(name);
        Casino casino;

        //interface
        int b;
        while(b != 6 and(player.getMoney() > 0)){
            cout << "Interface: " << endl;
            cout <<"1: Play BlackJack" << endl;
            cout <<"2: Play Roulette" << endl;
            cout <<"3: Play Slot Machine" << endl;
            cout <<"4: Show my balance" << endl;
            cout <<"5: Show top players" << endl;
            cout <<"6: Exit" << endl;
            cin >> b;
            if (cin.fail()) {
                cout << "Invalid input. Please enter a valid option." << endl;
                // Clear the error flag on cin
                cin.clear();
                // Ignore the rest of the line up to the maximum number of characters in a stream
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue; // Skip the rest of the loop and prompt again
            }
            switch (b) {
                case 1: {
                    // Play Blackjack
                    Game* blackjack = new BlackJack();
                    blackjack->play(player);
                    delete blackjack;
                    break;
                }
                case 2: {
                    // Play Ruletka
                    Game* ruletka = new Ruletka();
                    ruletka->play(player);
                    delete ruletka;
                    break;
                }
                case 3: {
                    // Play Slot Machine
                    Game* slot = new SlotMachine();
                    slot->play(player);
                    delete slot;
                    break;
                }
                case 4: {
                    cout <<"Your balance: " << player.getMoney() <<endl;
                    break;
                }
                case 5: {
                    casino.showTopPlayers();
                    break;
                }
                case 6: {
                    cout << ">>>Exiting" << endl;
                    casino.updateTopPlayers(player);
                    break;
                }
                default: {
                    cout <<"Not a valid option" << endl;
                    break;
                }
            }}


        return 1;
    }


