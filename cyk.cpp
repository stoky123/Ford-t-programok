#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    cout << "Add meg a szabályokat (X->AB vagy X->a formában), majd írd hogy 'done', ha kész:\n";
    string rule, key, value;
    int i, j, k, l, m;
    multimap<string, string> rules;
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
        rules.insert(pair<string, string>(key, value));
    }
    multimap<string, string>::iterator pos;
    cout << "\nSzabályok:\n";
    for(pos = rules.begin(); pos != rules.end(); pos++)
        cout << pos->first << "->" << pos->second << '\n';
      
    string word;
    cout << "Add meg a szót, amit megnézzünk, hogy levezethető-e: ";
    cin >> word;
    cout << '\n';
    
    vector<vector<string>> tree;
    vector<string> sor;
    tree.push_back(sor);
    string elfogado_szabalyok;
    string szo, szo2, szo3;
    for(i = 0; i < word.size(); i++) {
        tree[0].push_back(elfogado_szabalyok);
        for(pos = rules.begin(); pos != rules.end(); pos++) {
            szo +=  word[i];
            if(pos->second == szo)
                tree[0][i] += pos->first;
            szo = "";
        }
    }

    for(i = 1; i < word.size(); i++) {
        tree.push_back(sor);
        for(j = 0; j < tree[i-1].size()-1; j++) {
            tree[i].push_back(elfogado_szabalyok);
            for(k = 1; k < tree.size(); k++) {
                if (tree[k-1][j].size() == 0 || tree[tree.size()-1-k][j+k].size() == 0) {
                    continue;
                }
                else {
                    szo = tree[k-1][j];
                    szo2 = tree[tree.size()-1-k][j+k];
                }
                for(pos = rules.begin(); pos != rules.end(); pos++) {
                    for(l = 0; l < szo.size(); l++) {
                        for(m = 0; m < szo2.size(); m++) {
                            szo3 = "";
                            szo3 += szo[l];
                            szo3 += szo2[m];
                            if(pos->second == szo3)
                                tree[i][j] += pos->first;
                        }
                    }
                }
                szo = "";
                szo2 = "";
            }
            
        }
    }

    for(i = tree.size()-1; i >= 0; i--) {
        if(tree[i][0] == "")
            cout << '-';
        else
            cout << tree[i][0];
        for(j = 1; j < tree[i].size(); j++){
            if(tree[i][j] == "")
                cout << " | " << '-';
            else
                cout << " | " << tree[i][j];
        }
        cout << '\n';
    }

    if(tree[tree.size()-1][0].find('S') != string::npos)
        cout << "\n\nMivel a legfelső szinten megtalálható az 'S', ezért a szó levezethető.\n";
    else
        cout << "\n\nMivel a legfelső szinten nem található az 'S', ezért a szó nem vezethető le ezzel a nyelvtannal.\n";

    return 0;
}