#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Tarefas {
public:
    vector<int> dep;
    bool terminal;
    int time;
    int n_dep;
};

void funcao(vector<Tarefas> operacoes, int stat);
bool valid(vector<Tarefas> operacoes);
vector <int> ordenar(vector<Tarefas> operacoes);
int minimo(vector<Tarefas> operacoes);
void congestionamento(vector<Tarefas> operacoes);

int main() {
    int n_op, time, n_dep, dep, stat;
    vector<Tarefas> operacoes;
    vector<int> line;

    cin >> n_op;
    Tarefas t;
    for (int i = 0; i < n_op; i++) {
        cin >> time >> n_dep;
        t.time = time;
        t.n_dep = n_dep;
        for (int j = 0; j < n_dep; j++) {
            cin >> dep;
            line.push_back(dep);
        }
        t.dep = line;
        operacoes.push_back(t);
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
    if(!operacoes.empty()) {
        funcao(operacoes, stat);
    }

}


void funcao(vector<Tarefas> operacoes, int stat) {
    // verificacao das estatisticas
    if (valid(operacoes)) {
        if (stat == 0) {
            cout << "VALID";
        } else if (stat == 1) {
            int tempo_total = 0;

            // imprimir o tempo todo
            for (int i = 0; i < (int)operacoes.size(); i++) {
                tempo_total += operacoes[i].time;
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
            congestionamento(operacoes);
        } else { // tem de dar erro

        }
    } else {
        cout << "INVALID";
    }
}
void congestionamento(vector<Tarefas> operacoes) {
    vector<int> total;
    vector<int> not_terminal;

    for (int i = 0; i < (int)operacoes.size(); ++i) {
        not_terminal.push_back(i+1);
    }

    for (int i = 0; i < (int)operacoes.size(); ++i) {
        if ((int)operacoes[i].size() == 2) {
            total.push_back(i+1);
        }
        else if ((int)operacoes[i].size() > 3) {
            total.push_back(i+1);
        }

        int no = i + 1;
        for (int j = 0; j < (int)operacoes.size(); j++) {
            for (int k = 2; k < (int)operacoes[j].size(); k++) {
                auto r = find(not_terminal.begin(), not_terminal.end(), no); //verifica se o no ja nao e terminal
                if (no == operacoes[j][k] and r != not_terminal.end()) {
                    auto r = std::find(not_terminal.begin(), not_terminal.end(), no);
                    not_terminal.erase(r);
                }
            }
        }
    }

    total.push_back(not_terminal[0]);

    for (int id: total) {
        cout << id << "\n";
    }
}

int minimo(vector<Tarefas> operacoes) {
    int tempo = 0;
    pair<int,int> aux;
    vector<int> somados;

    for (int i = 0; i < (int)operacoes.size(); i++) {
        aux = make_pair(0,0);
        if ((int)operacoes[i].size() > 2) { //tem dependencia
            for (int j = 2; j < (int)operacoes[i].size(); j++) {
                if (aux.second < operacoes.at(operacoes[i][j]-1)[0]) {
                    aux.second = operacoes.at(operacoes[i][j]-1)[0];
                    aux.first = operacoes[i][j];
                }
            }

            //cout << "\naux: " << aux.second << "\n";
            auto r = std::find(somados.begin(), somados.end(), aux.first);
            if (r == somados.end()) {
                tempo += aux.second;
                somados.push_back(aux.first);
            }
        }

        //cout << "tempo: " << tempo << "\n";

    }
    tempo += operacoes.back()[0];

    return tempo;
}

vector<int> ordenar(vector<Tarefas> operacoes) {
    vector<int> ordenado;
    int no, no2;

    //cout << "tam: " << operacoes.size() << "\n";
    for (int i = 0; i < (int)operacoes.size(); i++) {
        //cout << "i: " << i << "\n";
        no = i + 1;
        if (ordenado.empty()) {
            if ((int)operacoes[i].size() == 2) {
                ordenado.push_back(no);
            }
        }

        //cout << "procurando: " << no << "\n";
        for (int j = 0; j < (int)operacoes.size(); j++) {
            for (int k = 2; k < (int)operacoes[j].size(); k++) {
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

bool valid(vector<Tarefas> operacoes) {
    bool no_dep = false;
    vector<int> not_terminal;

    for (int i = 0; i < (int)operacoes.size(); i++) {
        if (operacoes[i].n_dep == 0) { // nao tem dependencias
            if (!no_dep) {
                no_dep = true;
            } else {
                return false;
            }
        }

        int no = i + 1;
        for (int j = 0; j < (int)operacoes.size(); j++) {
            for (int k = 2; k < (int)operacoes[j].size(); k++) {
                auto r = find(not_terminal.begin(), not_terminal.end(), no); //verifica se no ja nao e terminal
                if (no == operacoes[j][k] and r == not_terminal.end()) {
                    not_terminal.push_back(no);
                }
            }
        }
    }

    // compara retira os nos que nao sao terminais
    // descubrindo o nº de nos terminais
    if ((int)operacoes.size() - (int)not_terminal.size() > 1) {
        //cout << "nos terminais: " << operacoes.size() - not_terminal.size() << "\n";
        return false;
    }

    return true;
}
