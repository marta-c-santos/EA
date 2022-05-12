#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <list>

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
int id_final = 0;
bool no_final = false;
map<int, Tarefas> mapa_op;
vector<int> visitados(1000);
vector<bool> pintado(1000);     //stat 3

void funcao(int stat);
bool valid();
bool ciclo(int no);
void ordenar(int no);
int minimo(int no);
vector<int> congest();
void congest_frente(int no);
void congest_tras(int no);


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
            ordenar(id_inicial);
        } else if (stat == 2) {
            // imprimir o tempo minimo possivel
            int tempo = minimo(id_inicial);
            cout << tempo << "\n";
        } else if (stat == 3) {
            vector<int> btn = congest();
            for (int i = 0; i < (int)btn.size(); i++) {
                cout << btn[i] << "\n";
            }

        } else { // tem de dar erro
            return;
        }
    } else {
        cout << "INVALID\n";
    }
}


/**
 * Verificacao se o conjunto de tarefas e valido
 *
 * @return true - valido
 * @return false - invalido
 */
bool valid() {
    // verifica se nao ha ciclos
    if (ciclo(id_inicial)) {
        //cout << "existe um ciclo\n";
        return false;
    }
    return true;
}


/**
 * Funcao verifica se existem ciclos, NO independe e NO final no grafo
 * DFS
 *
 * @param no
 * @return true - existe ciclo, NO independente e 2 NOS finais
 * @return false - nao existe ciclo
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
                id_final = no;
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


/**
 * Stat == 1 -> tempo minimo e a ordem do caminho
 * BFS
 *
 * @param no
 */
void ordenar(int no) {
    vector<bool> visitado(1000, false);
    priority_queue<int, vector<int>, greater<int>> q;

    q.push(no);
    visitado[no] = true;

    while (!q.empty()) {
        no = q.top();
        cout << no << "\n";
        q.pop();

        for (int seg: mapa_op.at(no).dep_filhos) {
            mapa_op.at(seg).n_dep--;
            if (mapa_op.at(seg).n_dep <= 0) {
                visitado[seg] = true;
                q.push(seg);
            }
        }
    }

}


/**
 * Stat == 2
 * Encontra o caminho com um custo menor,
 * partindo do primeiro NO percorrendo os NOS filhos seguintes
 *
 * @param no
 * @return
 */
int minimo(int no) {
    Tarefas n = mapa_op.at(no);
    int aux = 0, tempo = 0;

    if (visitados[no] != 0) { //verificar se o caminho ja foi percorrido
        return visitados[no];
    }

    for (int i: n.dep_filhos) {
        int a = minimo(i);
        if (a > aux) {
            aux = a; //se o custo for menor atualiza o aux e escolhendo esse caminho
        }
    }
    tempo += (n.time + aux);
    visitados[no] = tempo;      // adiciona o valor do caminho seguinte

    return tempo;
}


/**
 * Stat == 3
 *
 * BFS
 *
 * @return
 */
vector<int> congest() {
    vector<int> bottlenecks;
    bottlenecks.push_back(id_inicial);

    congest_frente(id_inicial);
    for (int i = 1; i < 8; i++) {
        cout << i << ": " << pintado[i] << "\n";
    }
    cout << "\n\n";

    congest_tras(id_final);
    for (int j = 1; j < 8; j++) {
        cout << j << ": " << pintado[j] << "\n";
    }


    for (int i = 1; i < tamanho_mapa; ++i) {
        if ( !pintado[i]) {
            bottlenecks.push_back(mapa_op.at(i).dep_filhos[0]);
        }
    }

    bottlenecks.push_back(id_final);

    return bottlenecks;
}

/**
 *
 * @param no
 */
void congest_frente(int no) {
    queue<int> q;

    q.push(no);
    pintado[no] = true;

    while (!q.empty()) {
        no = q.front();

        q.pop()
        for (int seg: mapa_op.at(no).dep_filhos) {

            pintado[seg] = true;
            q.push(seg);
        }
    }

}

/**
 *
 * @param no
 */
void congest_tras(int no) {
    if(!pintado[no]) {
        pintado[no] = true;

        if (mapa_op.at(no).n_dep != 0) {
            congest_tras(mapa_op.at(no).dep[0]);
        }
    }
}

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

