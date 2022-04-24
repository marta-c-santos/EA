#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void funcao(vector<vector<int>> operacoes, int stat);

bool valid(vector<vector<int>> operacoes);

vector<int> ordenar(vector<vector<int>> operacoes);

int minimo(vector<vector<int>> operacoes);

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
            int tempo_total = 0;

            // imprimir o tempo todo
            for (int i = 0; i < operacoes.size(); i++) {
                tempo_total += operacoes[i][0];
            }
            cout << tempo_total << "\n";

            // printar ordem da qual vai correr
            vector<int> ordenado = ordenar(operacoes);
            for (int i: ordenado) {
                cout << i << "\n";
            }


        } else if (stat == 2) {
            // imprimir o tempo minimo possivel
            int tempo = minimo(operacoes);
            cout << tempo << "\n";
        } else if (stat == 3) {

        } else { // tem de dar erro

        }
    } else {
        cout << "INVALID";
    }
}

int minimo(vector<vector<int>> operacoes) {
    int aux, tempo = 0;
    for (int i = 0; i < operacoes.size(); ++i) {
        if (operacoes[i].size() == 2) { //sem dependencias
            tempo += operacoes[i][0];
        }
        if (operacoes[i].size() == 3) { //1 dependencia
            cout << "1: " << operacoes.at(operacoes[i][2])[0] << "\n";
            tempo += operacoes.at(operacoes[i][2])[0];
        } else if (operacoes[i].size() > 3) { //tem varias dependencias
            for (int j = 2; j < operacoes[i].size(); j++) {
                if (aux < operacoes.at(operacoes[i][i])[0]) {
                    aux = operacoes.at(operacoes[i][i])[0];
                }
            }
            cout << "aux: " << aux << "\n";
            tempo += aux;
        }

        cout << "tempo: " << tempo << "\n";

    }


    return tempo;
}

vector<int> ordenar(vector<vector<int>> operacoes) {
    vector<int> ordenado;
    int no, no2;

    //cout << "tam: " << operacoes.size() << "\n";
    for (int i = 0; i < operacoes.size(); i++) {
        //cout << "i: " << i << "\n";
        no = i + 1;
        if (ordenado.empty()) {
            if (operacoes[i].size() == 2) {
                ordenado.push_back(no);
            }
        }

        //cout << "procurando: " << no << "\n";
        for (int j = 0; j < operacoes.size(); j++) {
            for (int k = 2; k < operacoes[j].size(); k++) {
                no2 = j + 1;
                //cout << "\t comparando com: " << operacoes[j][k] << "\n";
                auto r = std::find(ordenado.begin(), ordenado.end(), no2);
                if (no == operacoes[j][k] and r == ordenado.end()) {
                    //cout << "\t\t\tmeti dentro: " << no << "\n";
                    ordenado.push_back(no2);
                }
            }
        }

    }

    return ordenado;
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
