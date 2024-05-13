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
            cout << "Unfortunately you lost" << -amount << " dollars" << endl;
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


        void play(){
            int deck[52] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
            // 11 - Jack, 12 - Queen, 13 - King, 14 - Ace

            int dealer_hand[2];
            int player_hand[5];

            int bet;
            bet = make_bet();

            cout << ">>>Starting the round" << endl;




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
    }


};
int main() {
    cout << "Hello, Brother!, what's your name" << endl;
    string name;
    cin >> name;

    Player player(name);



    return 1;
}


