#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    vector<pair<string, string>> rules;
    string rule, key, value;
    int i;
    string start = "S#";
    string result = "";

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
    
    cout << "\nAdja meg a vizsgálandó szót: ";
    string word;
    cin >> word;
    word += "#";
    
    while (start[0] != '#'){
        if(start[0] == word[0]){
            start.erase(start.begin());
            word.erase(word.begin());
            continue;
        }
        for(i = 0; i < rules.size(); i++) {
            if(rules[i].first[0] == start[0])
                if(rules[i].second[0] == word[0]) {
                    start.replace(start.begin(), start.begin()+1, rules[i].second);
                    result += to_string(i+1);
                }
        }
    }

    cout << "Ezen szabályok alkalmazásával lehet levezetni a szót: " << result << '\n';
}