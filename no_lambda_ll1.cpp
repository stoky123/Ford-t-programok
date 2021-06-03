#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    vector<pair<string, string>> rules;
    vector<pair<pair<char, char>, int>> talalkozasok;
    string rule, key, value, szabaly_betuk;
    int i;
    string start = "S#";
    string result = "";
    std::size_t found;

    cout << "Add meg a szabályokat:\n";
    while(cin>>rule) {
        if(rule == "done")
            break;
        key = value = "";
        i = 0;
        while(rule[i] != '-') {
            key += rule[i];
            i++;
        }
        i += 2;
        while(i < rule.size()) {
            value += rule[i];
            i++;
        }
        found = szabaly_betuk.find(key);
        if(found == std::string::npos)
            szabaly_betuk += key;
        rules.push_back(pair<string, string>(key, value));
    }

    for(i = 0; i < rules.size(); i++) {
        if(islower(rules[i].second[0])) {
            talalkozasok.push_back(pair<pair<char, char>, int>(pair<char, char>(rules[i].first[0], rules[i].second[0]), i));
            for(int j = 0; j < rules.size(); j++) {
                if(rules[j].second[0] == rules[i].first[0]) {
                    talalkozasok.push_back(pair<pair<char, char>, int>(pair<char, char>(rules[j].first[0], rules[i].second[0]), j));
                }
            }
        }
    }
    bool van = false, talalt = true;
    while(talalt){
        talalt = false;
        for(i = 0; i < talalkozasok.size(); i++){
            for(int j = 0; j < rules.size(); j++) {
                van = false;
                if(rules[j].second[0] == talalkozasok[i].first.first) {
                    for(int k = 0; k < talalkozasok.size(); k++) {
                        if(talalkozasok[k].first.first == rules[j].first[0] && talalkozasok[k].first.second == talalkozasok[i].first.second)
                            van = true;
                    }
                    if(!van){
                        talalkozasok.push_back(pair<pair<char, char>, int>(pair<char, char>(rules[j].first[0], talalkozasok[i].first.second), j));
                        talalt = true;
                    }
                }
            }
        }
    }

    for(i = 0; i < talalkozasok.size(); i++){
        cout << talalkozasok[i].first.first << '+' << talalkozasok[i].first.second << '=' << talalkozasok[i].second << '\n';
    }

    cout << "\nSzabályok:\n";
    for(i = 0; i < rules.size(); i++)
        cout << rules[i].first << "->" << rules[i].second << "  Sorszám: " << i+1 << '\n';
    
    cout << "\nAdja meg a vizsgálandó szót: ";
    string word;
    cin >> word;
    word += "#";
    
    while (start[0] != '#' || word[0] != '#'){
        talalt = false;
        if(start[0] == word[0]){
            start.erase(start.begin());
            word.erase(word.begin());
            result += "pop ";
            continue;
        }
        for(i = 0; i < talalkozasok.size(); i++) {
            if(talalkozasok[i].first.second == word[0] && talalkozasok[i].first.first == start[0]) {
                start.replace(start.begin(), start.begin()+1, rules[talalkozasok[i].second].second);
                cout << word << '\n';
                result += '(' + rules[talalkozasok[i].second].second + ", " + to_string(talalkozasok[i].second+1) + ") ";
                talalt = true;
            }
        }
        if(!talalt) {
            cout << "A szó nem levezethető.";
            return 0;
        }
    }

    cout << "A szó az alábbi szabályok alkalmazásával vezethető le: " << result << '\n';
}