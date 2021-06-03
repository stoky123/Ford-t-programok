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
    vector<pair<string, string>> rules;
    string rule, key, value;
    int i;

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
        rules.push_back(pair<string, string>(key, value));
    }

    cout << "\nSzabályok:\n";
    for(i = 0; i < rules.size(); i++)
        cout << rules[i].first << "->" << rules[i].second << "  Sorszám: " << i+1 << '\n';

    string word;
    cout << "Add meg a szót, amit megnézzünk, hogy levezethető-e: ";
    cin >> word;
    cout << '\n';
    string word2 = word;

    vector<string> levezetes, nem_jo, szavak;
    vector<int> megoldas;
    string szo = "";
    szo += word2[0];
    levezetes.push_back(szo);
    szavak.push_back(word2);

    string masolat;
    bool talalt;
    std::size_t found;
    while(szavak.back().size() > 1 || levezetes.back() != "S"){
        talalt = false;
        for(i = 0; i < rules.size(); i++) {
            found = levezetes.back().find(rules[i].second);
            masolat = levezetes.back();
            if (found!=std::string::npos) {
                masolat.replace(found, rules[i].second.length(), rules[i].first);
                szo = szavak.back();
                szo.erase(szo.begin());
                if(!find2(nem_jo, masolat+szo)){
                    levezetes.push_back(masolat);
                    megoldas.push_back(i+1);
                    szavak.push_back(szavak.back());
                    talalt = true;
                    break;
                }
            }
        }
        if(!talalt) {
            masolat = szavak.back();
            masolat.erase(masolat.begin());
            if (masolat.size() && !find2(nem_jo, levezetes.back()+masolat)) {
                levezetes.push_back(levezetes.back()+masolat[0]);
                megoldas.push_back(-1);
                szavak.push_back(masolat);
            }
            else if(levezetes.size() > 1){
                nem_jo.push_back(levezetes.back()+masolat);
                levezetes.pop_back();
                megoldas.pop_back();
                szavak.pop_back();
            }
            else {
                cout << "A szó nem vezethető le! \n";
                return 0;
            }
        }
    }

    cout << "A szó levezethető az alábbi szabályok alkalmazásával:\n";

    for(i = megoldas.size()-1; i >= 0; i--) {
        if(megoldas[i] != -1)
            cout << megoldas[i] << ": " << rules[megoldas[i]-1].first << "->" << rules[megoldas[i]-1].second << '\n';
    }

    return 0;
}