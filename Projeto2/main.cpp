#include <iostream>
#include <vector>

using namespace std;

class No {
public:
    int id = 0;
    pair<int, int> usado;       // quantidade + custo
    pair<int, int> n_usado;

    vector<int> recrutados;
    int custo = 0;
};

pair<int, int> filhos_usados;
pair<int, int> best_filhos;
pair<int, int> res;

void funcao(vector<No> nos, int id_atual, int filhos_pai);

int main() {
    int n;
    vector<No> arvore;
    while (cin >> n) {
        if (n != -1) {
            vector<int> linha;
            //criar o no
            No no;
            no.id = n;
            while (cin.peek() != '\n') {
                cin >> n;
                linha.push_back(n);
            }

            no.custo = (int) linha.back();
            no.recrutados = linha;
            linha.clear();
            arvore.push_back(no);

        } else {

            funcao(arvore, 0, (int) arvore.at(0).recrutados.size() - 1);
            cout << "acabei!\n";
            cout << "Resultado: " << res.first << " " << res.second << "\n";
        }
    }

    return 0;
}


void funcao(vector<No> nos, int id_atual, int filhos_pai) {
    cout << "----------------->atual: " << id_atual << "\n";

    /*
    for (No n: nos) {
        for (int i = 0; i < (int) n.recrutados.size(); ++i) {
            cout << "rec: " << n.recrutados[i] << "\n";
        }
    }*/

    for (No n: nos) {
        if (n.id == id_atual) {
            //cout << "estou no 1ºif tantan\n";
            if ((int) n.recrutados.size() >= 2) { // tem pelo menos 1 filho
                //cout << ">>>>entrei no if\n";
                filhos_pai = (int) n.recrutados.size() - 1;
                cout << "numero de filhos: " << filhos_pai << "\n";

                filhos_usados = make_pair(0,0);
                for (int rec = 0; rec < (int) n.recrutados.size() - 1; rec++) {
                    cout << "id " << n.id << " filhos: " << filhos_pai << "\n";
                    filhos_pai--;
                    funcao(nos, n.recrutados[rec], filhos_pai);
                }


                //somados usados dos filhos
                n.n_usado = make_pair(filhos_usados.first, filhos_usados.second);

                //proprio caso usado + melhor caso de todos os filhos
                n.usado = make_pair((1 + best_filhos.first), (n.custo + best_filhos.second));

                // melhor caso entre usados e n_usados
                if (n.usado.first < n.n_usado.first) {
                    cout << "entra1?????????? " << n.usado.first << " " << n.usado.second << "\n";
                    best_filhos = make_pair(n.usado.first, n.usado.second);
                } else if (n.usado.first == n.n_usado.first){
                    if (n.usado.second > n.n_usado.second) {
                        best_filhos = make_pair(n.usado.first, n.usado.second);
                    } else {
                        best_filhos = make_pair(n.n_usado.first, n.n_usado.second);
                    }
                } else {
                    cout << "entra2?????????? " << n.n_usado.first << " " << n.n_usado.second << "\n";
                    best_filhos = make_pair(n.n_usado.first, n.n_usado.second);
                }
                // filhos usados
                filhos_usados = make_pair(n.usado.first, n.usado.second);
                cout << " ************************ " << best_filhos.first << " " << best_filhos.second << "\n";


                cout << "----------------------------------------------------------id: " << n.id << " nfilhos: " << filhos_pai << "\n";
                /*if(filhos_pai <= 0) { // quando nao tem + filhos
                    cout << ">>>>>>>>>>entrei no if n_filhos = 0 no id: " << n.id << "\n";
                    //dar reset
                    filhos_usados = make_pair(0, 0);
                    best_filhos = make_pair(0, 0);
                }*/


            } else { // nao tem filhos
                cout << ">>>>entrei no else\n";
                n.n_usado = make_pair(0, 0);
                n.usado = make_pair(1, n.custo);

                cout << "elseeeee, sem filhos, mas filhos_pai = " << filhos_pai << "\n";
                if (filhos_pai >= 0) { //
                    cout << ".............usado first: " << n.usado.first << " ... " << n.usado.second << "\n";

                    filhos_usados.first += n.usado.first;
                    filhos_usados.second += n.usado.second;

                    cout << "................filhos usados: " << filhos_usados.first << " ... " << filhos_usados.second << "\n";

                    if (n.n_usado.first < n.usado.first) {
                        best_filhos = make_pair(n.n_usado.first, n.n_usado.second);

                    } else if (n.n_usado.first == n.usado.first) {

                        if (n.n_usado.second < n.usado.second) {
                            best_filhos = make_pair(n.n_usado.first, n.n_usado.second);

                        } else {
                            best_filhos = make_pair(n.usado.first, n.usado.second);
                        }

                    } else {
                        best_filhos = make_pair(n.usado.first, n.usado.second);
                    }

                }
            }

            cout << n.id << " n_usados: " << n.n_usado.first << " " << n.n_usado.second << "\n";
            cout << n.id << " usados: " << n.usado.first << " " << n.usado.second << "\n";
            cout << "filhos_usados: " << filhos_usados.first << " " << filhos_usados.second << "\nbest_filhos: " << best_filhos.first << " " << best_filhos.second << "\n";


            //cout << n.id << " usado: " << n.usado.first << " " << n.usado.second << "\n";
            //cout << n.id << " n_usado: " << n.n_usado.first << " " << n.n_usado.second << "\n";
            cout << "min: " << min(n.usado.first, n.n_usado.first) << "\n";



        }
        // verificar se e o ultimo no
        // ver qual dos nos e maio (usado ou n_usado)

    }
}


/*
0 1 1
1 2 4 5 2
2 3 8
3 4
4 16
5 32
-1
0 1 2 3 30
1 4 5 54
2 6 12
3 7 8 25
4 41
5 29
6 37
7 12
8 23
-1

2 10
3 91

Teste Goncalo:
0 1 2 3 5
1 4 5 14
2 6 3
3 10
4 8
5 3
6 20
-1

3 39

 */