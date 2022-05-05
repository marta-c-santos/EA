#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Tarefas {
public:
    int time;                   // tempo para processar
    int n_dep;                  // numero de dependencias
    vector<int> dep;            // dependencias
    bool terminal;
    vector<int> dep_filhos;     // nos q sao dependentes do no atual
    bool pintado;
};

map<int, Tarefas> mapa_op;

void funcao(int stat);

bool valid();

void ciclo(int no, bool pintado);

vector<int> ordenar();

int minimo();

void congestionamento();

int main() {
    int n_op, time, n_dep, dep, stat;
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
        mapa_op.insert(make_pair(i + 1, t));
        line.clear();
    }
    cin >> stat;

    if (!mapa_op.empty()) {
        funcao(stat);
    }
}


void funcao(int stat) {
    // verificacao das estatisticas
    if (valid()) {
        if (stat == 0) {
            cout << "VALID";
        } /*else if (stat == 1) {
            int tempo_total = 0;

            // imprimir o tempo total
            for (int i = 0; i < int(mapa_op.size()); ++i) {
                tempo_total += mapa_op[i].time;
            }
            cout << tempo_total << "\n";

            // printar ordem da qual vai correr
            vector<int> ordenado = ordenar();
            for (int i: ordenado) {
                cout << i << "\n";
            }


        } else if (stat == 2) {
            // imprimir o tempo minimo possivel
            int tempo = minimo();
            cout << tempo << "\n";
        } else if (stat == 3) {
            congestionamento();
        } else { // tem de dar erro

        }*/
    } else {
        cout << "INVALID";
    }
}

bool valid() {
    bool no_dep = false;
    vector<int> not_terminal(mapa_op.size());

    for (int i = 1; i < (int) mapa_op.size(); i++) {
        if (mapa_op[i].n_dep == 0) { // nao tem dependencias
            if (!no_dep) {
                no_dep = true;
            } else {
                return false;
            }
        }

        int no = i;
        for (int j = 1; j < (int) mapa_op.size(); j++) {
            for (int k = 0; k < mapa_op[j].n_dep; k++) {
                // verifica se no nao e terminal
                if (no == mapa_op[j].dep[k] and not_terminal.at((i-1)) != no) {
                    not_terminal[i-1] = no;
                }
            }

        }
    }
    
    // verifica se nao ha ciclos
    //ciclo(no, pintado);


    // contar os nos n terminais
    int count = 0;
    for (int i: not_terminal) {
        if (i != 0) {
            count ++;
        }
    }

    // descubrindo o nº de nos terminais
    if ((int) mapa_op.size() - count > 1) {
        return false;
    }

    return true;
}

/*
void ciclo(int no, bool pintado) {

    if(!operacoes[no].pintado) {
        operacoes[no].pintado = true;

        for (int i = 0; i < (int)operacoes[no].dep.size(); i++) {
            int no = operacoes[no].dep[i];
            mapa.at(no);

            if(operacoes[no].dep[i])
        }
    }
}


// stat == 1
vector<int> ordenar() {
    vector<int> ordenado;
    int no, no2;
    int total = 0; // soma do tempo total

    for (int i = 0; i < (int)operacoes.size(); i++) {
        no = i + 1;
        if (ordenado.empty()) {
            if ((int)operacoes[i].n_dep == 0) { // nao existem dependencias
                ordenado.push_back(no);
                total += (int)operacoes[i].time;
            }
        } else {
            // verificar se existem dependencias do no atual





        }



        for (int j = 0; j < (int)operacoes.size(); j++) {
            for (int k = 2; k < (int)operacoes[j].dep.size(); k++) {
                no2 = j + 1;
                //cout << "\t comparando com: " << operacoes[j][k] << "\n";
                auto r = std::find(ordenado.begin(), ordenado.end(), no2);
                if (no == operacoes[j].dep[k] and r == ordenado.end()) {
                    //cout << "\t\t\tmeti dentro: " << no << "\n";
                    ordenado.push_back(no2);
                }
            }
        }

    }

    return ordenado;
}

// stat == 2
int minimo() {
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

// stat == 3
void congestionamento() {
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
            for (int k = 0; k < (int)operacoes[j].dep.size(); k++) {
                auto r = find(not_terminal.begin(), not_terminal.end(), no); //verifica se o no ja nao e terminal
                if (no == operacoes[j].dep[k] and r != not_terminal.end()) {
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
}*/




