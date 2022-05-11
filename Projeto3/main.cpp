#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Tarefas {
public:
    int time = 0;               // tempo para processar
    int n_dep = 0;              // numero de dependencias
    vector<int> dep;            // dependencias
    //bool terminal = false;
    vector<int> dep_filhos;     // nos q sao dependentes do no atual
    bool pintado = false;
    bool rec = false;           // recursao ativa para os ciclos
};


int tamanho_mapa = 0;
int id_inicial = 0;
bool no_final = false;
map<int, Tarefas> mapa_op;
vector<int> visitados(1000);
void funcao(int stat);
bool valid();
bool ciclo(int no);
vector<int> ordenar();
int minimo(int no);
//void congestionamento();


int main() {
    int n_op, time, n_dep, dep, stat;
    bool no_inicial = false;
    vector<int> line;

    cin >> n_op; // numero de tarefas
    Tarefas t;

    for (int a = 0; a < n_op + 1; a++) {
        mapa_op.insert(make_pair(a, t));
    }

    for (int i = 1; i < n_op + 1; i++) {
        cin >> time >> n_dep;
        mapa_op[i].time = time;
        mapa_op[i].n_dep = n_dep;
        for (int j = 0; j < n_dep; j++) {
            cin >> dep;
            mapa_op.at(dep).dep_filhos.push_back(i);    //adicionar os dependentes deste
            line.push_back(dep);
        }
        mapa_op[i].dep = line;


        if (mapa_op[i].n_dep == 0) { // nao tem dependencias
            id_inicial = i;
            if (!no_inicial) { // verificar se ja existe NO id_inicial
                no_inicial = true;
            } else {
                cout << "INVALID\n";
                return 0;
            }
        }

        line.clear();
    }
    cin >> stat;

    if (!mapa_op.empty()) {
        tamanho_mapa = (int) mapa_op.size();
        funcao(stat);
    }
}


void funcao(int stat) {
    // verificacao das estatisticas
    if (valid()) {
        if (stat == 0) {
            cout << "VALID\n";

        } else if (stat == 1) {
            int tempo_total = 0;
            // imprimir o tempo total
            for (int i = 0; i < tamanho_mapa; i++) {
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
            int tempo = minimo(id_inicial);
            cout << tempo << "\n";
        } /*else if (stat == 3) {
            congestionamento();
        } else { // tem de dar erro
        }*/
    } else {
        cout << "INVALID\n";
    }
}

/*
 * Verificacao se o conjunto de tarefas e valido
 *
 * return true - valido
 * return false - invalido
 */
bool valid() {
    // verifica se nao ha ciclos
    if (ciclo(id_inicial)) {
        //cout << "existe um ciclo\n";
        return false;
    }
    return true;
}

/*
 * Funcao verifica se existem ciclos no grafo
 *
 * return true - existe ciclo
 * return false - nao existe ciclo
 */

bool ciclo(int no) {
    if (!mapa_op[no].pintado) { //o no nao esta pintado
        mapa_op[no].pintado = true;
        mapa_op[no].rec = true;

        //cout << "n_filhos: " << mapa_op[no].dep_filhos.size() << "\n";
        if ((int) mapa_op[no].dep_filhos.size() != 0) {
            for (int dep: mapa_op[no].dep_filhos) {
                // se o no nao estiver pintado ou existir um ciclo -> ciclo
                //cout << "estamos no No " << no << " pintado " << dep << ": " << mapa_op.at(dep).pintado << "\n";
                if (!mapa_op.at(dep).pintado && ciclo(dep)) {
                    return true;
                } else if (mapa_op.at(dep).rec) { // recursao em curso
                    return true;
                }
            }
        }

        if (mapa_op[no].dep_filhos.size() == 0) {
            if (!no_final) {
                no_final = true;
            } else {
                return false;
            }
        }

        if (mapa_op[no].n_dep == 0 and mapa_op[no].dep_filhos.size() == 0) {
            return false;
        }

        mapa_op[no].rec = false;
        return false;
    }
    return true;
}


// stat == 1            concluida
vector<int> ordenar() {
    vector<int> ordenado;
    int total = 0; // soma do tempo total

    for (int no = 1; no < tamanho_mapa; no++) {
        // adicionar todos os nos por ordem -> ordenado
        if (ordenado.empty()) {
            if ((int) mapa_op[no].n_dep == 0) { // nao existem dependencias
                ordenado.push_back(no);
                total += (int) mapa_op[no].time;
            }
        } else {
            // verificar se existem dependencias do no atual
            if ((int) mapa_op[no].n_dep != 0) { // tem pelo menos 1 dependencia
                ordenado.push_back(no);
                total += (int) mapa_op[no].time;
            }
        }
    }
    return ordenado;
}


// stat == 2
int minimo(int no) {
    Tarefas n = mapa_op.at(no);
    int aux = 0, tempo = 0;

    if( visitados[no] != 0){ //verificar se o caminho ja foi percorrido
        return visitados[no];
    }

    for (int i: n.dep_filhos) {
        int a = minimo(i);
        if (a > aux) {
            aux = a; //se o custo for menor atualiza o aux e escolhendo esse caminho
        }
    }
    tempo += (n.time + aux);
    visitados[no] = tempo;

    return tempo;
}

/*
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

/*
 Exemplo 1 - ha 1 no desconectado
4
3 0
2 1 1
4 1 2
3 0
0

>> INVALID

 Exemplo 2 - 2 nos iniciais
5
3 0
2 1 1
2 0
5 2 2 3
1 1 4
1

>> INVALID

 Exemplo 3 - 2 nos terminais
6
3 0
2 1 1
2 1 1
5 2 2 3
1 1 4
2 1 4
2

>> INVALID

 Exemplo 4 - ciclos
5
3 0
2 2 1 4
2 2 1 2
5 1 3
1 1 4
3

>> INVALID

 Exemplo 5
5
3 0
2 1 1
2 1 1
5 2 2 3
1 1 4
0

>> VALID

 Exemplo 6
5
3 0
2 1 1
2 1 1
5 2 2 3
1 1 4
1

>> 13
    1
    2
    3
    4
    5

 Exemplo 7
5
3 0
2 1 1
2 1 1
5 2 2 3
1 1 4
2

>> 11

 Exemplo 8
5
2 1 2
3 0
2 1 2
1 1 5
5 2 1 3
3

>> 2
   5
   4

 */

