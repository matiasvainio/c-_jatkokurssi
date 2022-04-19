#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Spell_obj {
   public:
    void operator()(int& i) {
        if (i - 100 >= 0)
            i = i - 100;
        else
            i = 0;
    }
};

void spell(int& i) {
    if (i - 100 >= 0)
        i = i - 100;
    else
        i = 0;
}

void print(vector<int> hitpoints) {
    cout << "Hitpoints ";
    for_each(hitpoints.begin(), hitpoints.end(), [](int x) { cout << x << ", "; });
    cout << endl;
}

int main() {
    vector<int> hitpoints = {100, 300, 120, 450, 35};
    Spell_obj f;
    auto spell_lamdba = [](int& i) {
        if (i - 100 >= 0)
            i = i - 100;
        else
            i = 0;
    };

    // a. erillinen funktio.
    for_each(hitpoints.begin(), hitpoints.end(), spell);
    print(hitpoints);

    hitpoints = {100, 300, 120, 450, 35};
    // b. funktio-objekti.
    for_each(hitpoints.begin(), hitpoints.end(), f);
    print(hitpoints);

    hitpoints = {100, 300, 120, 450, 35};
    // c. lambda-funktio.
    for_each(hitpoints.begin(), hitpoints.end(), [](int& i) {
        if (i - 100 >= 0)
            i = i - 100;
        else
            i = 0;
    });
    print(hitpoints);

    hitpoints = {100, 300, 120, 450, 35};
    // d. nimetty lambda-funktio.
    for_each(hitpoints.begin(), hitpoints.end(), spell_lamdba);
    print(hitpoints);

    return 0;
}
