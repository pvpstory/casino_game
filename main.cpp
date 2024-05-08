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


};

int main() {
    cout << "Hello, Brother!, what's your name" << endl;
    string name;
    cin >> name;

    Player player(name);



    return 1;
}


