#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

bool find2(vector<string> v, string to_find) {
    for (string s : v) {
        if(s == to_find)
            return true;
    }
    return false;
}

int main() {
    cout << "Add meg a szabályokat (bal_oldal->jobb_oldal formában), majd írd hogy 'done', ha beírtad mindet:\n";
    string rule, key, value, counter;
    multimap<string, string> rules;

    int i, char_counter;
    while(cin>>rule) {
        if(rule == "done")
            break;
        key = value = "";
        i = 0;
        while(rule[i] != '-' && rule[i+1] != '>') {
            key += rule[i];
            i++;
        }
        i += 2;
        while(i < rule.size()) {
            value += rule[i];
            i++;
        }
        counter += key;
        char_counter = 0;
        for(char c : counter)
            if(c == key[0])
                char_counter++;
        rules.insert(pair<string, string>(key + to_string(char_counter), value));
    }

    multimap<string, string>::iterator pos;
    cout << "\nSzabályok:\n";
    for(pos = rules.begin(); pos != rules.end(); pos++)
        cout << pos->first << "->" << pos->second << '\n';

    string word;
    cout << "Add meg a szót, amit megnézzünk, hogy levezethető-e: ";
    cin >> word;
    cout << '\n';
    string word2 = word;

    vector<string> levezetes, nem_jo, megoldas;
    levezetes.push_back("S");

    string masolat;
    bool talalt = false;
    while (word2.size() != 0) {
        while(levezetes[levezetes.size()-1][0] == word2[0] && word2.size() != 0) {
            levezetes[levezetes.size()-1].erase(levezetes[levezetes.size()-1].begin());
            word2.erase(word2.begin());
        }
        talalt = false;
        for(pos = rules.begin(); pos != rules.end(); pos++) {
            if (pos->first[0] == levezetes[levezetes.size()-1][0]) {
                masolat = levezetes[levezetes.size()-1];
                masolat = masolat.replace(0, 1, pos->second);
                if(!find2(nem_jo, masolat)) {
                    talalt = true;
                    levezetes.push_back(masolat);
                    megoldas.push_back(pos->first);
                }
            }
        }
        if(!talalt && word2.size() != 0) {
            if (levezetes.size() == 1){
                cout << "A " << word << " szó nem levezethető.\n";
                return 0;
            }
            nem_jo.push_back(levezetes[levezetes.size()-1]);
            levezetes.pop_back();
            megoldas.pop_back();
        }
    }

    cout << "\nA " << word << " szó levezethető.\n";
    cout << "Egy baloldali levezetés: ";
    for(string s : megoldas){
        cout << s << ' ';
    }
    cout << '\n';

    return 0;
}
