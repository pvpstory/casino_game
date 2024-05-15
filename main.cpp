#include <iostream>
#include <string>

using namespace std;

class Player {

public:
    Player(string name) : name(name) {
        int lb = 200;
        int ub = 1000;
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
    void resultGame(int amount,Player player){
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
        cout << "Your bet is " << bet << "dollars" << endl;
        return bet;
    }




};

class BlackJack: public Game{


        void play(Player player){ //ace implementation
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
                int sum_hand = player_hand[0] + player_hand[1] + player_hand[2] + player_hand[3] + player_hand[4];
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

            int amount;
            if(sum_hand == 21){
                cout << "BlackJack!!!" << endl;
                cout << "Congratulations you won" << endl;
                amount = bet * 1.5;
            }
            if (dealers_sum > 21 or sum_hand == 21 or sum_hand > dealers_sum ){
                cout << "Congratulations you won" << endl;
                amount = bet;
            }
            else
                cout << "Unfortunately you lost" <<endl;
                amount = -bet;

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
        if(card = 14)
            /////////////////implemnt
            return 0;

        if (card > 10){
            card = 10;
        }

        return card;
    }


};

class Ruletka: public Game{
    void choose_number(int tab[]){
        int number;
        cout << "What number would you like to bet on(0-36): " << endl;
        cin >> number;
        if (number )

    }

    void choose_property(int tab[]){


    }

    void choose_color(int tab[]){

    }
    void make_ruletka_bet() {
        int b = 1;
        cout << "Make your bets" <<endl;\

        while(b != 10){
            cout <<"0: Exit"<<endl;
            cout <<"1: Bet on a single number" << endl;
            cout <<"2: Bet on a color(Red/Black)" <<endl;
            cout <<"3: bet on the propetry(Odd/Even)"<<endl;
            cin >> b;
            if (b == 0){
                // interface()
            }
            int tablica[37];
            switch(b) {
                case 0://interface
                    break;
                case 1:
                    choose_number(tablica);
                    break;
                case 2:
                    choose_color(tablica);
                    break;
                case 3:
                    choose_property(tablica);
                    break;
            }
        }

    }
    void play(Player player,int bet_amount, int bet_numbers[]){
    int number_of_numbers = 0;
    for(int i = 0; i < 37;i++){
        if (bet_numbers[i] != 0){
            number_of_numbers++;
        }
    }
    int d;
    cout << ">>>The game is starting"<<endl;
    cin >> d;
    cout << ">>>The Roulete is spinning" << endl;
    cin >> d;

    int the_winning_number = rand() % 52;
    cout << "The number is: " << the_winning_number << " " << color <<  endl;

    int amount;

    for(int i = 0; i < 37; i++){
        if(bet_numbers[i] == the_winning_number){
            cout << "BlackJack!!!" << endl;
            cout << "Congratulations you won: " << amount << endl;
            if (number_of_numbers == 1){
                amount = bet_amount * 35;
                break;
            }
            else{
                amount = bet_amount;
                break;
            }

        }
        else{
            cout << "Unfortunately you lost your bet: " << bet_amount << endl;
            amount = -bet_amount;
            break;
        }
    }
    player.changeMoney(amount);


}

};
int main() {
    cout << "Hello, Brother!, what's your name" << endl;
    string name;
    cin >> name;

    Player player(name);

    return 1;
}


