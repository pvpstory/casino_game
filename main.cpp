#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <ctime>


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


private:
    string name;
    float money;
};

class Game{
public:
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

     int make_bet(){
        int bet = 0;
        cout << "How much would you like to bet" << endl;
        cin >> bet;
        if (bet <= 0 ){
            cout << "Not a valid bet" << endl;
            return 1;
        }
        cout << "Your bet is " << bet << " dollars" << endl;
        return bet;
    }




};

class BlackJack: public Game{
public:
        void play(Player &player){ //ace implementation
            int deck[52] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
            // 11 - Jack, 12 - Queen, 13 - King, 14 - Ace

            int dealer_hand[2];
            int player_hand[5] = {0,0,0,0,0};

            int bet;
            bet = make_bet();

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

                if (answer == 'N'){
                    break;
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
            if(sum_hand == dealers_sum || (dealers_sum > 21 && sum_hand > 21)){
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
    void choose_number(int tab[]){
        int number;
        cout << "What number would you like to bet on(0-36): ";
        cin >> number;
        if (number < 0 or number > 36){
            cout << "Your number isn't in the range"<< endl;
            choose_number(tab);
        }
        //not sure if i should use else
         tab[number] = number;
    }

    void choose_property(int tab[]){
        char property[100];
        cout << "Would you like to bet on Even or Odd numbers?(Odd,Even,O,E): ";
        cin >> property;
        // not sure if it works

        if (strcmp(property,"O") == 0 || strcmp(property,"Odd") == 0){
            for(int i =0; i < 37; i++){
                if((i % 2)!= 0){
                    tab[i] = i;
                }
            }

        }
        else if(strcmp(property,"E") == 0 || strcmp(property,"Even") == 0){
            for(int i =0; i < 37; i++){
                if((i % 2) == 0){
                    tab[i] = i;
                }
            }
        }
        else{
            cout << "Your choice isn't Odd,Even or O,E " << endl;
            choose_property(tab);
        }


    }

//    void choose_color(int tab[]){
//        char color[4];
//        cout << "Choose the color(Red,Black,R,B): ";
//        //finish later
//        cin >> color;
//        if (strcmp(color,"R") == 0 or strcmp(color,"Red") == 0){
//            for(int i =0; i < 37; i++){
//                if((i % 2)!= 0){
//                    tab[i] = i;
//                }
//            }
//
//        }
//        else if(strcmp(color,"B") == 0 or strcmp(color,"Black") == 0){
//            for(int i =0; i < 37; i++){
//                if((i % 2) == 0){
//                    tab[i] = i;
//                }
//            }
//        }
//        else{
//            cout << "Your choice isn't Red,Black or R,B " << endl;
//            choose_color(tab);
//        }
//
//    }
    int* make_ruletka_bet() {
        int b = 1;
        cout << "Make your bets" <<endl;
        int* tablica = new int[37]();

        while(b != 10){
            cout <<"0: Exit"<<endl;
            cout <<"1: Bet on a single number" << endl;
            cout <<"2: Bet on a color(Red/Black)" <<endl;
            cout <<"3: bet on the propetry(Odd/Even)"<<endl;
            cin >> b;


            switch(b) {
                case 0://interface
                    delete[] tablica;
                    break;
                case 1:
                    choose_number(tablica);
                    return tablica;
                    break;
                case 2:
                    //choose_color(tablica);
                    break;
                case 3:
                    choose_property(tablica);
                    return tablica;
                    break;
            }
        }

    }

    void play(Player &player){
        int* bet_numbers = make_ruletka_bet();
        int number_of_numbers = 0;

        for (int i = 0; i < 36; ++i) {
            if (bet_numbers[i] != 0)
                number_of_numbers++;
        }
        cout << "number_of_numbers: " << number_of_numbers <<endl;
        int bet_amount = make_bet();

    int d;
    cout << ">>>The game is starting"<<endl;
    cin >> d;
    cout << ">>>The Roulete is spinning" << endl;
    cin >> d;

    int the_winning_number = rand() % 36;
    cout << "The number is: " << the_winning_number <<endl; //" " << color <<  endl;

    int amount;
    int cof;
    if(number_of_numbers == 1){
        cof = 35;

    }
    else{
        cof = 1;
    }


    if(bet_numbers[the_winning_number] == the_winning_number) {
        amount = bet_amount * cof;
        cout << "Congratulations you won your bet: " << amount << endl;
    }
    else{
        cout << "Unfortunately you lost your bet: " << bet_amount << endl;
        amount = -bet_amount;

    }
    delete[] bet_numbers;
    resultGame(amount,player);

}

};
int main() {
    cout << "Hello, Brother!, what's your name" << endl;
    string name;
    cin >> name;
    Player player(name);
    //interface
    int b;
    while(b != 6 || player.getMoney() <= 0){
        cout << "Interface: " << endl;
        cout <<"1: Play BlackJack" << endl;
        cout <<"2: Play Roulette" << endl;
        cout <<"3: Play Slot Machine" << endl;
        cout <<"4: Show my balance" << endl;
        cout <<"5: Show top players" << endl;
        cout <<"6: Exit" << endl;
        cin >> b;
        switch(b){
            case 1:
                BlackJack blackjack;
                blackjack.play(player);
                break;
            case 2:
                Ruletka ruletka;
                ruletka.play(player); //something is wrong with memory
                break;
            case 4:
                cout <<"Your balance: " << player.getMoney() <<endl;
                break;
            case 6:
                cout <<">>>Exiting" << endl;
                break;
        }
    }




    return 1;
}


