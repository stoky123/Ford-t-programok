#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

int main() {
    string input;
    getline(cin, input);

    for(int i = 0; i < input.size(); i++) {
        if(input[i] == ' ')
            i++;
        else if(isdigit(input[i])) {
            while(isdigit(input[i]))
                i++;
            i--;
            cout << "<szám>\n";
        }
        else if(isalpha(input[i])) {
            while(isalpha(input[i]) || isdigit(input[i]))
                i++;
            i--;
            cout << "<változó>\n";
        }
        else if(input[i] == '{') {
            while(input[i] != '}' && input[i] != '$') {
                i++;
            }
            if(input[i] == '$')
                cout << "hibakezelő, nincs bezárva a komment a bemenet vége előtt!\n";
            else
                cout << "<{}kommentár>\n";
        }
        else if(input[i] == '(' && input[i+1] == '*') {
            while(input[i] != '$') {
                if(input[i] == '*' && input[i+1] == ')') {
                    break;
                }
                i++;
            }
            if(input[i] == '$') {
                cout << "hibakezelő, nincs lezárva a komment a bemenet vége előtt!\n";
            }
            i++;
            cout << "<(**)kommentár>\n";
        }
        else if(input[i] == ':' && input[i+1] == '=') {
            i++;
            cout << "<értékadás>\n";
        }
        else if(input[i] == '<') {
            if(input[++i] == '=')
                cout << "< <=token >\n";
            else if(input[i] == '>')
                cout << "< <>token >\n";
            else if(input[i] == '$')
                cout << "hibakezelő, nincs lezárva a token!\n";
        }
        else if(input[i] == '>') {
            if(input[++i] == '=')
                cout << "< >=token >\n";
            else if(input[i] == '$')
                cout << "hibakezelő, nincs lezárva a token!\n";
        }
        else if (input[i] == '$') {
            cout << "<eof>\n";
            break;
        }
        else {
            cout << "Valami váratlan történt =(\n";
        }
    }

    return 0;
}
