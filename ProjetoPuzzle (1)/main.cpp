#include <iostream>
#include <vector>
#include <map>
using namespace std;

// fazer a hash table aqui
map<array<int,2>, vector<int>> CompMap;
int nlin, ncol;
class Peca {
public:
    int numero[4];
    int posta = 0;

    // concluido
    Peca rotacao() {
        int aux = numero[3];
        for (int i = 3; i > 0; i--) {
            numero[i] = numero[i - 1];
        }
        numero[0] = aux;

        return *this;
    }
};


static void puzzle(Peca *pecas, int npecas);
static bool direita( int npecas, Peca **solucao, Peca *pecas, int line, int col);
static bool baixo( int npecas, Peca **solucao, Peca *pecas, int line, int col);
static bool pre_process(Peca *pecas, int npecas); // concluido
static vector<int> compatibilidades(Peca *pecas, int n1, int n2);
void impressao(Peca **solucao, bool state); // concluido




int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int ntest, npecas;
    cin >> ntest;

    for (int i = 0; i < ntest; i++) {
        cin >> npecas >> nlin >> ncol;
        Peca pecas[npecas];

        for (int j = 0; j < npecas; j++) {
            cin >> pecas[j].numero[0] >> pecas[j].numero[1] >> pecas[j].numero[2] >> pecas[j].numero[3];
        }

        bool state = pre_process(pecas, npecas);
        if (state)
            puzzle(pecas, npecas);
        else
            cout << "impossible puzzle!\n";

        CompMap.clear();
    }

    return 0;
}

static bool pre_process(Peca *pecas, int npecas) {
    int arr[1000];
    int count = 0;

    for (int i = 0; i < 1000; i++) {
        arr[i] = 0;
    }

    for (int i = 0; i < npecas; i++) {
        for (int j: pecas[i].numero) {
            arr[j] += 1;
        }
    }

    for (int i = 0; i < 1000; i++) {
        if (arr[i] % 2 != 0) {
            count += 1;
        }
    }

    if (count > 4)
        return false;

    return true;
}


static void puzzle(Peca *pecas, int npecas) {
    Peca **solucao = new Peca *[nlin];

    //inicializar a solucao a 0
    for (int i = 0; i < nlin; ++i) {
        solucao[i] = new Peca[ncol];
    }

    //primeira peca
    solucao[0][0] = pecas[0];
    pecas[0].posta = 1;


    bool state;
    if (ncol == 1) {
        state = baixo(npecas, solucao, pecas, 1, 0);
    } else {
        state = direita( npecas, solucao, pecas, 0, 1);
    }

    impressao(solucao, state);
}

static bool direita( int npecas, Peca **solucao, Peca *pecas, int line, int col) {
    vector<int> peca = compatibilidades(pecas, solucao[line][col - 1].numero[2], solucao[line][col - 1].numero[1]);

    if (col == ncol and line == nlin - 1) { //caso base
        return true;
    }
    int pos;

    for (int k = 0; k < (int)peca.size(); k++) {
        pos = peca[k];
        if (pecas[pos].posta == 0) { //a peca nao esta posta, vai tentar por
            for (int i = 0; i < 4; i++) {
                if (line == 0) {
                    if (solucao[line][col - 1].numero[1] == pecas[pos].numero[0] and
                        solucao[line][col - 1].numero[2] == pecas[pos].numero[3]) {

                        solucao[line][col] = pecas[pos];
                        pecas[pos].posta = 1;

                        if (col < ncol - 1) {
                            if (direita( npecas, solucao, pecas, line, col + 1))
                                return true;
                        } else {
                            if (baixo( npecas, solucao, pecas, line + 1, 0))
                                return true;
                        }
                    }
                    pecas[pos].rotacao();

                } else {
                    if (solucao[line - 1][col].numero[3] == pecas[pos].numero[0] and
                        solucao[line - 1][col].numero[2] == pecas[pos].numero[1] and
                        solucao[line][col - 1].numero[1] == pecas[pos].numero[0] and
                        solucao[line][col - 1].numero[2] == pecas[pos].numero[3]) {

                        solucao[line][col] = pecas[pos];
                        pecas[pos].posta = 1;

                        if (col < ncol - 1) {
                            if (direita( npecas, solucao, pecas, line, col + 1))
                                return true;

                        } else {
                            if (baixo( npecas, solucao, pecas, line + 1, 0))
                                return true;
                        }
                    }
                    pecas[pos].rotacao();
                }
            }
            pecas[pos].posta = 0;
        }
    }

    return false;
}


static bool baixo( int npecas, Peca **solucao, Peca *pecas, int line, int col) {
    vector<int> peca = compatibilidades(pecas, solucao[line - 1][col].numero[3], solucao[line - 1][col].numero[2]);


    if (line == nlin) { //caso base
        return true;
    }
    int pos;
    for (int k = 0; k < (int)peca.size(); k++) {
        pos = peca[k];
        if (pecas[pos].posta == 0) {
            for (int i = 0; i < 4; ++i) {

                if (solucao[line - 1][col].numero[3] == pecas[pos].numero[0] and
                    solucao[line - 1][col].numero[2] == pecas[pos].numero[1]) {

                    solucao[line][col] = pecas[pos];
                    pecas[pos].posta = 1;

                    if (ncol == 1) {
                        if (baixo(npecas, solucao, pecas, line + 1, 0))
                            return true;
                    } else {
                        if (direita( npecas, solucao, pecas, line, col + 1))
                            return true;
                    }
                }
                pecas[pos].rotacao();
            }
            pecas[pos].posta = 0;
        }
    }
    return false;
}

static vector<int> compatibilidades(Peca *pecas, int n1, int n2) {
    vector<int> peca;
    array<int,2> arr {n1,n2};
    auto it = CompMap.find(arr);

    if(it == CompMap.end()){
        for (int i = 0; i < (nlin*ncol); i++) {
            for (int j = 0; j < 4; j++) {
                if(pecas[i].numero[j] == n1 and pecas[i].numero[(j+1)%4] == n2){
                    peca.push_back(i);
                    break;
                }
            }
        }
        CompMap.insert({arr,peca});
        return peca;
    }else{
        return it->second;
    }
}


//concluido
void impressao(Peca **solucao, bool state) {
    int aux;

    if (!state) {
        cout << "impossible puzzle!\n";
        return;
    } else {
        for (int i = 0; i < nlin; i++) {
            aux = 0;

            if (i >= 1)
                cout << "\n";
            cout << solucao[i][aux].numero[0] << " " << solucao[i][aux].numero[1];

            if (ncol >= 1) {
                for (int j = 1; j < ncol; j++) {
                    cout << "  " << solucao[i][j].numero[0] << " " << solucao[i][j].numero[1];
                }
            }
            cout << "\n";
            cout << solucao[i][aux].numero[3] << " " << solucao[i][aux].numero[2];
            if (ncol >= 1) {
                for (int j = 1; j < ncol; j++) {
                    cout << "  " << solucao[i][j].numero[3] << " " << solucao[i][j].numero[2];
                }
            }
            cout << "\n";
            aux++;
        }
    }
}
