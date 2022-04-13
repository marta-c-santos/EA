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

void funcao(vector<No> nos, int id_atual, int n_filhos);

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

            funcao(arvore, 0, 0);
            cout << "acabei!\n";
            //cout << "Resultado: " << res << "\n";
        }
    }

    return 0;
}


void funcao(vector<No> nos, int id_atual, int n_filhos) {
    cout << "----------------->atual: " << id_atual << "\n";

    /*
    for (No n: nos) {
        for (int i = 0; i < (int) n.recrutados.size(); ++i) {
            cout << "rec: " << n.recrutados[i] << "\n";
        }
    }*/

    for (No n: nos) {
        if (n.id == id_atual) {
            cout << "estou no 1ºif tantan\n";
            if ((int) n.recrutados.size() >= 2) {
                cout << ">>>>entrei no if\n";
                int n1 = (int) n.recrutados.size();
                for (int rec = 0; rec < (int) n.recrutados.size() - 1; rec++) {

                    funcao(nos, n.recrutados[rec], n1);
                    n1--;

                    //somados usados dos filhos
                    n.n_usado.first = filhos_usados.first;
                    n.n_usado.second = filhos_usados.second;

                    //proprio caso usado + melhor caso de todos os filhos
                    n.usado.first = 1 + best_filhos.first;
                    n.usado.second = n.custo + best_filhos.second;
                }

                if( n_filhos == 0) {
                    //dar reset
                    filhos_usados.first = 0;
                    filhos_usados.second = 0;
                    best_filhos.first = 0;
                    best_filhos.second = 0;
                }


            } else { // nao tem filhos
                cout << ">>>>entrei no else\n";
                n.n_usado.first = 0;
                n.n_usado.second = 0;
                n.usado.first = 1;
                n.usado.second = n.custo;
                if(n_filhos > 0) {
                    filhos_usados.first += n.usado.first;
                    filhos_usados.second += n.usado.second;

                    if (n.n_usado.first > n.usado.first) {
                        best_filhos.first = n.n_usado.first;
                        best_filhos.second = n.n_usado.second;

                    } else if (n.n_usado.first == n.usado.first) {

                        if (n.n_usado.second > n.usado.second) {
                            best_filhos.first = n.n_usado.first;
                            best_filhos.second = n.n_usado.second;
                        } else {
                            best_filhos.first = n.usado.first;
                            best_filhos.second = n.usado.second;
                        }

                    } else {
                        best_filhos.first = n.usado.first;
                        best_filhos.second = n.usado.second;
                    }
                }
            }

        }

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
-1

3 39

 */