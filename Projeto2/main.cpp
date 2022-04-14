#include <iostream>
#include <vector>
#include <map>
using namespace std;

class No {
public:
    int id = 0;
    int usado[2]{0, 0};       // quantidade + custo
    int n_usado[2]{0, 0};

    vector<int> recrutados;
    int custo = 0;
};

int res[2];
vector<No *> *arvore;
map<int, No*> mapa;

No* funcao(int id_atual);

int main() {
    int n;

    arvore = new vector<No *>;
    while (cin >> n) {
        if (n != -1) {
            //criar o no
            No *no = new No();
            no->id = n;
            while (cin.peek() != '\n') {
                cin >> n;
                no->recrutados.push_back(n);
            }
            no->custo = (int) no->recrutados.back();
            mapa.insert(make_pair(no->id, no));

        } else {
            funcao(0);

            if (mapa.at(0)->usado[0] > mapa.at(0)->n_usado[0]) {
                res[0] = mapa.at(0)->n_usado[0];
                res[1] = mapa.at(0)->n_usado[1];
            } else if (mapa.at(0)->usado[0] < mapa.at(0)->n_usado[0]) {
                res[0] = mapa.at(0)->usado[0];
                res[1] = mapa.at(0)->usado[1];
            } else {
                if (mapa.at(0)->usado[1] > mapa.at(0)->n_usado[1]) {
                    res[0] = mapa.at(0)->usado[0];
                    res[1] = mapa.at(0)->usado[1];
                } else {
                    res[0] = mapa.at(0)->n_usado[0];
                    res[1] = mapa.at(0)->n_usado[1];
                }
            }
            cout << res[0] << " " << res[1] << "\n";

            arvore->clear();
            mapa.clear();
        }
    }
    return 0;
}


No* funcao(int id_atual) {
    No *n = mapa.at(id_atual);

    n->usado[0] = 1;
    n->usado[1] = n->custo;
    n->n_usado[0] = 0;
    n->n_usado[1] = 0;

    for (int rec = 0; rec < (int) n->recrutados.size() - 1; rec++) {

        No* filho = funcao(n->recrutados[rec]);

        //somados usados dos filhos
        n->n_usado[0] += filho->usado[0];
        n->n_usado[1] += filho->usado[1];

        if (filho->usado[0] > filho->n_usado[0]) {
            n->usado[0] += filho->n_usado[0];
            n->usado[1] += filho->n_usado[1];
        } else if (filho->usado[0] < filho->n_usado[0]) {
            n->usado[0] += filho->usado[0];
            n->usado[1] += filho->usado[1];
        } else {
            if (filho->usado[1] > filho->n_usado[1]) {
                n->usado[0] += filho->usado[0];
                n->usado[1] += filho->usado[1];
            } else {
                n->usado[0] += filho->n_usado[0];
                n->usado[1] += filho->n_usado[1];
            }
        }
    }
    return n;
}
