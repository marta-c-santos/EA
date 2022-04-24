#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void funcao(vector<vector<int>> operacoes, int stat);

bool valid(vector<vector<int>> operacoes);

int main() {
    int n_op, time, n_dep, dep, stat;
    vector<vector<int>> operacoes;
    vector<int> line;

    cin >> n_op;
    for (int i = 0; i < n_op; i++) {
        cin >> time >> n_dep;
        line.push_back(time);
        line.push_back(n_dep);
        for (int j = 0; j < n_dep; j++) {
            cin >> dep;
            line.push_back(dep);
        }
        operacoes.push_back(line);
        line.clear();
    }
    cin >> stat;

    /* impressao
    for(vector<int> a: operacoes) {
        for(int b: a) {
            cout << b << " ";
        }
        cout << "\n";
    }
    cout << stat;
     */

    funcao(operacoes, stat);

}

void funcao(vector<vector<int>> operacoes, int stat) {
    /*
     * .
     * .
     * .
     */

    // verificacao das estatisticas
    if (valid(operacoes)) {
        if (stat == 0) {
            cout << "VALID";
        } else if (stat == 1) {

        } else if (stat == 2) {

        } else if (stat == 3) {

        } else { // tem de dar erro

        }
    } else {
        cout << "INVALID";
    }
}

bool valid(vector<vector<int>> operacoes) {
    bool no_dep = false;
    vector<int> not_terminal;

    for (int i = 0; i < operacoes.size(); i++) {
        if (operacoes[i].size() == 2) { // nao tem dependencias
            if (!no_dep) {
                no_dep = true;
            } else {
                return false;
            }
        }

        int no = i + 1;
        for (int j = 0; j < operacoes.size(); j++) {
            for (int k = 2; k < operacoes[j].size(); k++) {
                auto r = find(not_terminal.begin(), not_terminal.end(), no); //verifica se no ja nao e terminal
                if (no == operacoes[j][k] and r == not_terminal.end()) {
                    not_terminal.push_back(no);
                }
            }
        }
    }

    // compara retira os nos que nao sao terminais
    // descubrindo o nº de nos terminais
    if (operacoes.size() - not_terminal.size() > 1) {
        //cout << "nos terminais: " << operacoes.size() - not_terminal.size() << "\n";
        return false;
    }

    return true;
}
