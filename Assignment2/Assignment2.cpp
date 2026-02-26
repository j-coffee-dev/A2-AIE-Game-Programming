//Assignment 2 for AIE Game Programming Course - 2026

#include <iostream>
#include <cassert>
#include <string>
#include <chrono>
#include <thread>
#include <random>
using namespace std;

int linear_search(int* array, int size, int target) {
    /////////////////////////////////////////////////
    /// @brief  Takes in an array, if target is an element of the array returns the index 
    ///         index where it first occurs, else return -1.
    ///
    /// @param  array  : A pointer to the array to be searched.
    /// @param  size   : The number of elements in array.
    /// @param  target : Element to search for.
    /// 
    /// @return  if target first occurs as element array[i] return index i,
    ///          else return -1 if target doesn't equal any element.
    /////////////////////////////////////////////////

    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}
void search_for_targ_linear(int* array, int size) {
    /////////////////////////////////////////////////
    /// @brief  Loops through user input and searches the array 
    ///         for the input using linear_search.
    ///         Print to let user know if that element was found.
    ///
    /// @param  array  : A pointer to the array to be searched.
    /// @param  size   : The number of elements in array.
    /// 
    /// @return  Nothing.
    /////////////////////////////////////////////////

    string target;
    int target_int;
    cout << "linear_search: Continue entering values to search the array for (type Q to quit): " << endl;

    while(true){
        cin >> target;
        try {
            target_int = stoi(target);
        }
        catch (...) {
            break;
        }
        int result = linear_search(array, size, target_int);
        if (result == -1) { cout << "Result not found." << endl; }
        else { cout << "Result found at index " << result << endl; }
    }
}

void swap_integers(int& a, int& b) {
    /////////////////////////////////////////////////
    /// @brief  Swaps the values of two integers.
    ///
    /// @param  a : First integer to be swapped.
    /// @param  b : Second integer to be swapped.
    /// 
    /// @return  No return. Original variables are modified
    ///          as they are passed by reference.
    /////////////////////////////////////////////////

    int temp;
    temp = a;
    a = b;
    b = temp;
}

void bubble_sort(int* array, int size) {
    /////////////////////////////////////////////////
    /// @brief  Sorts an integer array from smallest
    ///         to largest.
    ///
    /// @param  array : The array to be sorted.
    /// @param  size  : Size of the sorted array.
    /// 
    /// @return  No return. Original array is modified
    ///          via swap_integers.
    /////////////////////////////////////////////////

    bool swapped = true;

    do {
        swapped = false;
        for (int i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) {
                swap_integers(array[i], array[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

int binary_search(int* array, int size, int target) {
    /////////////////////////////////////////////////
    /// @brief  Searches a sorted integer array for a target integer
    ///         using the binary method.
    ///
    /// @param  array  : The sorted array to be searched.
    /// @param  size   : Size of the array.
    /// @param  target : Target element to search for.
    /// 
    /// @return  Return index where target is, else return -1.
    /////////////////////////////////////////////////

    for (int i = 0; i < size - 1; i++) {
        assert(array[i] <= array[i + 1]);
    }

    int L = 0;
    int R = size;
    while (L <= R) {
        int idx = static_cast <int> (L + R) / 2;
        if (array[idx] == target) {
            return idx;
        }
        else if (array[idx] < target) {
            L = idx + 1;
        }
        else if (array[idx] > target) {
            R = idx - 1;
        }
    }
    return -1;
}

void search_for_targ_binary(int* array, int size) {
    /////////////////////////////////////////////////
    /// @brief  Loops through user input and searches the array 
    ///         for the input using binary_search
    ///         Print to let user know if that element was found.
    ///
    /// @param  array  : A pointer to the array to be searched.
    /// @param  size   : The number of elements in array.
    /// 
    /// @return  Nothing.
    /////////////////////////////////////////////////

    string target;
    int target_int;
    cout << "binary_search: Continue entering values to search the array for (type Q to quit): " << endl;

    while (true) {
        cin >> target;
        try {
            target_int = stoi(target);
        }
        catch (...) {
            break;
        }
        int result = binary_search(array, size, target_int);
        if (result == -1) { cout << "Result not found." << endl; }
        else { cout << "Result found at index " << result << endl; }
    }
}

enum AttackType {
    VICIOUS_SLICE,
    REGULAR,
    FIREBALL
};

struct Mob {
    string name = "placeholder";

    AttackType attack_skill = VICIOUS_SLICE;
    int damage_rating = 0;


    int max_health = -1;
    int health = -1;
    int health_over_time = 0;
    int h_timer = 0;

    bool dodge_next_attack = false;

    bool next_strike_crit = false;
    float critical_multiplier = 1.0;
    float crit_strike_chance = 0.0;

    bool dot_next_attack = false;
    float dot_chance = 0.0;



    void config(string initial_name, int max_hp, int hp, float crit_mult, float crit_chance, float dot_prob, AttackType default_attack) {
        name = initial_name;
        max_health = max_hp;
        health = hp;
        critical_multiplier = crit_mult;
        crit_strike_chance = crit_chance;
        dot_chance = dot_prob;
        attack_skill = default_attack;
    }

    void add_health(int amount) {
        health += amount;
    }

    void attack(Mob& mob, int step, bool pause_on, bool print_details) {

        //Logic for attack dodge
        if (mob.dodge_next_attack) {
            if (print_details) { cout << "-> " << "\033[33m" << mob.name << " dodged the attack from " << name << ". \033[0m" << endl; }
            mob.dodge_next_attack = false;
            if (pause_on) {
                this_thread::sleep_for(chrono::milliseconds(step));
            }
            return;
        }

        //Switch on basic attacks defined by AttackType enum
        switch (attack_skill) {

        case(FIREBALL):
            if (next_strike_crit) {
                mob.add_health(-static_cast <int> (damage_rating * critical_multiplier));
                if (print_details) { cout << "-> " << name << " attacked " << mob.name << " with Fireball! " << "(" << static_cast <int> (damage_rating*critical_multiplier) << " damage)" << " - \033[33mCRITICAL!\033[0m" << endl; }
            }
            else {
                mob.add_health(-damage_rating);
                if (print_details) { cout << "-> " << name << " attacked " << mob.name << " with Fireball. " << " (" << damage_rating << " damage)" << endl; }
            }
            if (dot_next_attack) {
                //Mage's Fireball has a chance to inflict 50 damage in each round as a status effect for the next 4 attacks.
                mob.health_over_time = -50;
                mob.h_timer = 4000;
                if (print_details) { cout << "\033[33mFireball applied a damage over time to " << mob.name << " this round!\033[0m" << endl; }
            }
            break;

        case(REGULAR):
            mob.add_health(-damage_rating);
            if (print_details) { cout << "-> " << name << " attacked " << mob.name << " with a regular attack. " << "(" << damage_rating << " damage)" << endl; }
            break;

        case(VICIOUS_SLICE):
            mob.add_health(-damage_rating);
            if (print_details) { cout << "-> " << name << " attacked " << mob.name << " with Vicious Slice! " << "(" << damage_rating << " damage)" << endl; }
            if (dot_next_attack) {

                //Vicious Slice has a chance to inflict 2% max health as damage over time for the next 6 attacks.
                mob.health_over_time = -static_cast <int> (0.02 * mob.max_health);
                mob.h_timer = 6000;
                if (print_details) { cout << " \033[33mVicious Slice applied a damage over time to " << mob.name << " this round!\033[0m" << endl; }
            }
            break;        
        }

        if (pause_on) {
            this_thread::sleep_for(chrono::milliseconds(step));
        }
    }

    void update_status(int step, bool print_details) {
        if (h_timer > 0) {
            add_health(health_over_time);
            if (health_over_time < 0) {
                if (print_details) { cout << "\033[31m" << "-> " << name << " took " << -health_over_time << " damage from a status effect from a previous attack. (Remaining time: " << (h_timer - step) / 1000 << " rounds)" << "\033[0m" << endl; }
            }
            else if (health_over_time > 0) {
                if (print_details) { cout << "\033[32m" << "-> " << name << " gained " << health_over_time << " from a status effect. (Remaining time: " << (h_timer - step) / 1000 << " rounds)" << "\033[0m" << endl; }
            }
        }
        h_timer -= step;
    }

    void determine_attack_style(int idx) {
        switch (idx) {
        case (0):
            attack_skill = VICIOUS_SLICE;
            break;
        case (1):
            attack_skill = REGULAR;
            break;
        }
    }

    void apply_special_effect() {
        if (name == "Hogger") {
            health_over_time = static_cast <int> (0.05 * max_health);
            h_timer = 2000;
        }
        if (name == "Level 10 Human Mage") {
            dodge_next_attack = true;
        }
    }
};

enum WinState {
    PLAYING,
    WIN,
    LOSE,
    DRAW
};

WinState get_win_state(Mob mob1, Mob mob2) {
    if (mob1.health <= 0 && mob2.health <= 0) {
        return DRAW;
    }
    else if (mob1.health > 0 && mob2.health <= 0) {
        return LOSE;
    }
    else if (mob1.health <= 0 && mob2.health > 0) {
        return WIN;
    }
    else { return PLAYING; }
}

WinState mob_battle(Mob& mob1, Mob& mob2, bool pause_on, const unsigned int seed, bool print_details) {

    WinState winstate = PLAYING;
    mt19937 generator(seed);
    Mob* mobs[2] = { &mob1, &mob2 };

    uniform_int_distribution<int> uniform_damage_rating(10, 25);
    uniform_int_distribution<int> uniform_dist(0, 1);
    bernoulli_distribution special_effect(0.3);
    bernoulli_distribution bernoulli_dist_crit_mob2(mob2.crit_strike_chance);
    bernoulli_distribution bernoulli_dist_dot_mob1(mob1.dot_chance);
    bernoulli_distribution bernoulli_dist_dot_mob2(mob2.dot_chance);

    int time_step = 1000;
    int round = 1;

    while (winstate == PLAYING) {
        //Randomly determine Hogger's attack style this turn (Uniform probability of either attack)
        int hogger_attack_idx = uniform_dist(generator);
        mob1.determine_attack_style(hogger_attack_idx);

        //Randomly determine damage amount for Hogger (Uniform: Equal probability of damage rating on integers in the interval [10,25])
        mob1.damage_rating = uniform_damage_rating(generator);

        //Randomly determine damage amount for Hogger (Uniform: Equal probability of damage rating on integers in the interval [60,150]) 
        mob2.damage_rating = 6 * uniform_damage_rating(generator);

        //Randomly determine one mob to get a special effect (Bernoulli: On average, in 3 out of 10 attacks one mob will get their special effect) 
        int idx_exp = uniform_dist(generator);
        bool se_sample = special_effect(generator);
        if (se_sample) {
            (*mobs[idx_exp]).apply_special_effect();
        }

        //Randomly determine if the player will crit Hogger this round (Bernoulli: Player will crit with probability mob2.crit_strike_chance) 
        mob2.next_strike_crit = bernoulli_dist_crit_mob2(generator);


        //Randomly determine if each player will apply their damage over time effects this round (Bernoulli: Effects applied with probability mobi.dot_chance) 
        mob1.dot_next_attack = bernoulli_dist_dot_mob1(generator);
        mob2.dot_next_attack = bernoulli_dist_dot_mob1(generator);

        //Randomly determine who attacks first (Uniform: Equal probability of each mob attacking first)
        int idx = uniform_dist(generator);
        int other_idx = (idx + 1) % 2;

        if (print_details) {
            cout << "-----------------------------------------------------------------------------------------------------------" << endl;
            cout << "ATTACK ROUND: " << round << " " << endl;
            cout << "CURRENT STATS: " << mob1.name << " has \033[31m" << mob1.health << "\033[0m health. " << mob2.name << " has \033[32m" << mob2.health << "\033[0m health." << endl;
            cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        }

        if (pause_on) {
            this_thread::sleep_for(chrono::milliseconds(2 * time_step));
        }

        (*mobs[idx]).attack((*mobs[other_idx]), time_step, pause_on, print_details);

        //Check if the first attacking mob killed other mob
        winstate = get_win_state(*mobs[idx], *mobs[other_idx]);
        if (winstate != PLAYING) {
            break;
        }

        (*mobs[other_idx]).attack((*mobs[idx]), time_step, pause_on, print_details);

        //Check if the second attacking mob killed other mob
        winstate = get_win_state(*mobs[idx], *mobs[other_idx]);
        if (winstate != PLAYING) {
            break;
        }

        //Randomly determine who's dots are applied first (Uniform: Equal probability of each mob applying their dot first)
        idx = uniform_dist(generator);
        other_idx = (idx + 1) % 2;

        (*mobs[idx]).update_status(time_step, print_details);
        //Check if applied dots killed the mob
        winstate = get_win_state(*mobs[idx], *mobs[other_idx]);
        if (winstate != PLAYING) {
            break;
        }

        (*mobs[other_idx]).update_status(time_step, print_details);
        //Check if applied dots killed the mob
        winstate = get_win_state(*mobs[idx], *mobs[other_idx]);
        if (winstate != PLAYING) {
            break;
        }

        if (pause_on) {
            this_thread::sleep_for(chrono::milliseconds(time_step));
        }
        round += 1;
    }

    if (print_details) { cout << "-----------------------------------------------------------------------------------------------------------" << endl; }

    return winstate;
}

void announce_win(Mob mob1, Mob mob2, WinState winstate) {
    switch (winstate) {
    case(WIN):
        cout << "****************************** " << mob2.name << " won this match!" << " ******************************" << endl;
        break;
    case(DRAW):
        cout << "It was a draw!" << endl;
        break;
    case(LOSE):
        cout << "****************************** " << mob1.name << " won this match!" << " ******************************" << endl;
        break;
    }
}

void print_battle_statistics(vector <WinState> win_array) {
    int num_of_wins = 0;
    int num_of_draws = 0;
    int num_of_battles = win_array.size();
    for (WinState winstate : win_array) {
        if (winstate == WIN) {
            num_of_wins += 1;
        }
        else if (winstate == DRAW) {
            num_of_draws += 1;
        }
    }
    cout << endl << "---------------------------------------------BATTLE STATISTICS---------------------------------------------" << endl;
    cout << "Level 10 Human Mage won " << to_string(num_of_wins) << " out of " << to_string(num_of_battles) << " battles." << endl;
    cout << "Hogger won " << to_string(num_of_battles - num_of_wins - num_of_draws) << " out of " << to_string(num_of_battles) << " battles." << endl;
    cout << "There were " << to_string(num_of_draws) << " draws out of " << to_string(num_of_battles) << " battles." << endl;
    cout << "...as expected, Hogger is brutal." << endl;
    cout << "-----------------------------------------------------------------------------------------------------------";
}



int main()
{
    //Question 6 - Linear Search
    cout << "---------------------------Question 6---------------------------" << endl;
    const int num_of_elements = 20;
    int arr[num_of_elements] = { 67,13,3,89,43,2,19,71,5,61,97,7,37,31,17,11,83,53,23,29 };
    assert(linear_search(arr, num_of_elements, 3) == 2);
    assert(linear_search(arr, num_of_elements, 7) == 11);
    assert(linear_search(arr, num_of_elements, 67) == 0);
    assert(linear_search(arr, num_of_elements, 88) == -1);
    cout << endl << "linear_search ASSERTS PASSED" << endl;

    search_for_targ_linear(arr, num_of_elements);

    //Question 7 - Bubble Sort
    cout << "---------------------------Question 7---------------------------" << endl;
    bubble_sort(arr, num_of_elements);

    for (int i = 0; i < num_of_elements-1; i++) {
            assert(arr[i] <= arr[i + 1]);
    }
    cout << "bubble_sort ASSERTS PASSED" << endl;

    //Question 8 - Binary Search
    cout << "---------------------------Question 8---------------------------" << endl;
    assert(binary_search(arr, num_of_elements, 11) == 4);
    assert(binary_search(arr, num_of_elements, 23) == 8);
    assert(binary_search(arr, num_of_elements, 97) == 19);
    assert(binary_search(arr, num_of_elements, 88) == -1);
    cout << "binary_search ASSERTS PASSED" << endl;

    search_for_targ_binary(arr, num_of_elements);

    //Question 9 - Pointers
    cout << "---------------------------Question 9---------------------------" << endl;
    int a_after = 1;
    int b_after = 53;
    swap_integers(a_after, b_after);

    int a_before = 1;
    int b_before = 53;
    assert((a_before == b_after) && (a_after == b_before));
    cout << "swap_integer ASSERTS PASSED" << endl;

    //Question 10 - Mob battle
    cout << "---------------------------Question 10---------------------------" << endl;

    //Config form: (name, maxhp, currenthp, crit multiplier, crit chance, dot chance, default attack skill)
    Mob mob1;
    mob1.config("Hogger", 666, 666, 1.0, 0, 0.1, AttackType::REGULAR);

    Mob mob2;
    mob2.config("Level 10 Human Mage", 100, 100, 1.2, 0.2, 0.1, AttackType::FIREBALL);

    const int num_of_battles = 100;
    bool pause_on = false;
    bool print_details = false;
    unsigned int seed = 0;
    vector<WinState> win_array;
    cout << "Out of the " << num_of_battles << " battles which one would you like to watch?" << endl;
    int battle_to_watch = 5;
    cin >> battle_to_watch;
    for (int i = 0; i < num_of_battles; i++) {
        //Reset mob health for each battle
        mob1.health = 666;
        mob2.health = 100;

        //Give a new random seed so that each battle is different
        seed = i;

        if (i == battle_to_watch) {
            cout << "----------Press any key to begin printing details of battle number " << to_string(battle_to_watch) << " between the two mobs.----------" << endl;
            //Wait for user input >nul ensures the system string is not printed.
            system("pause >nul");
            print_details = true;
            pause_on = true;
        }
        else {
            print_details = false;
            pause_on = false;
        }
        WinState winstate = mob_battle(mob1, mob2, pause_on, seed, print_details);
        if (i == battle_to_watch) {
            announce_win(mob1, mob2, winstate);
        }
        win_array.push_back(winstate);
    }
    print_battle_statistics(win_array);
}
