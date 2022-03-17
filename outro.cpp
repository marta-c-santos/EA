#include <iostream>
#include <vector>

using namespace std;

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

        //impressao
        //cout << "Rodada[" << peca[0] << "," << peca[1] << "," << peca[2] << "," << peca[3] << "]\n";

        return *this;
    }
};


static void puzzle(Peca *pecas, int npecas, int nlin, int ncol);
static bool direita(int nlin, int ncol, int npecas, Peca **solucao, Peca *pecas, int line, int col);
static bool baixo(int nlin, int ncol, int npecas, Peca **solucao, Peca *pecas, int line, int col);
static bool pre_process(Peca *pecas, int npecas);
void impressao(Peca **solucao, int nlin, int ncol, bool state); // concluido


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int ntest, npecas, nlin, ncol;
    cin >> ntest;
    //cout << ntest << "\n";

    for (int i = 0; i < ntest; i++) {
        cin >> npecas >> nlin >> ncol;
        //cout << npecas << nlin << ncol << "\n";
        Peca pecas[npecas];

        for (int j = 0; j < npecas; j++) {
            cin >> pecas[j].numero[0] >> pecas[j].numero[1] >> pecas[j].numero[2] >> pecas[j].numero[3];
        }
        /*
        //impressao
        for (int j = 0; j < npecas; ++j) {
            cout << "[" << pecas[j].numero[0] << pecas[j].numero[1] << pecas[j].numero[2] << pecas[j].numero[3] << "]\n";
        }
        */
        bool state = pre_process(pecas, npecas);
        if(state)
            puzzle(pecas, npecas, nlin, ncol);
        else
            cout << "impossible puzzle!\n";
        //impressao(pecas, npecas, nlin, ncol);

    }

    return 0;
}

static bool pre_process(Peca *pecas, int npecas){
    int arr[1000];
    int count = 0;
    for (int i = 0; i < 1000; i++){
        arr[i] = 0;
    }

    for (int i = 0; i < npecas; i++) {
        for (int j : pecas[i].numero) {
            arr[j] += 1;
        }
    }

    for (int i = 0; i < 1000; i++) {
        if(arr[i] % 2 != 0){
            count += 1;
        }
    }

    if (count > 4)
        return false;

    return true;
}


static void puzzle(Peca *pecas, int npecas, int nlin, int ncol) {
    Peca **solucao = new Peca *[nlin];

    //inicializar a solucao a 0
    for (int i = 0; i < nlin; ++i) {
        solucao[i] = new Peca[ncol];
    }

    //primeira peca
    solucao[0][0] = pecas[0];
    pecas[0].posta = 1;

    /*
    for (int i = 0; i < 4; i++) {
        cout << "Solucao: " << solucao[0][0][i] << "\n";
    }

    for (int j = 0; j < npecas; ++j) {
        cout << "Pecas: [" << pecas[j].numero[0] << pecas[j].numero[1] << pecas[j].numero[2] << pecas[j].numero[3] << "]\n";
    }*/

    bool state;

    if(ncol == 1){
        state = baixo(nlin, ncol, npecas, solucao, pecas, 1, 0);
    }else {
        state = direita(nlin, ncol, npecas, solucao, pecas, 0, 1);
    }

    /*
    //impressao solucao
    for (int i = 0; i < nlin; ++i) {
        for (int j = 0; j < ncol; ++j) {
            for (int k = 0; k < 4; ++k) {
                cout << "solucao2222: " << solucao[i][j].numero[k] << "\n";
            }
            cout << "-------------------\n";
        }
    }*/

    impressao(solucao, nlin, ncol, state);

}

static bool direita(int nlin, int ncol, int npecas, Peca **solucao, Peca *pecas, int line, int col) {
    if (col == ncol and line == nlin-1) {
        return true;
    }

    for (int pos = 1; pos < npecas; pos++) {
        if (pecas[pos].posta == 0) { //a pecas nao esta posta, vai por
            for (int i = 0; i < 4; i++) {
                if (line == 0) {
                    if (solucao[line][col - 1].numero[1] == pecas[pos].numero[0] and
                        solucao[line][col - 1].numero[2] == pecas[pos].numero[3]) {

                        solucao[line][col] = pecas[pos];
                        pecas[pos].posta = 1;

                        //if (pos + 1 <= npecas) { //ve se ainda ha pecas
                        if (col < ncol - 1) {
                            if (direita(nlin, ncol, npecas, solucao, pecas, line, col + 1))
                                return true;
                        } else {
                            if (baixo(nlin, ncol, npecas, solucao, pecas, line + 1, 0))
                                return true;
                        }
                        //}
                    }
                    pecas[pos].rotacao();
                    //pecas[pos] = aux;

                } else {
                    if (solucao[line - 1][col].numero[3] == pecas[pos].numero[0] and
                        solucao[line - 1][col].numero[2] == pecas[pos].numero[1] and
                        solucao[line][col - 1].numero[1] == pecas[pos].numero[0] and
                        solucao[line][col - 1].numero[2] == pecas[pos].numero[3]) {

                        solucao[line][col] = pecas[pos];
                        pecas[pos].posta = 1;

                        //if (pos + 1 <= npecas) { //ve se ainda ha pecas
                            if (col < ncol - 1) {
                                if (direita(nlin, ncol, npecas, solucao, pecas, line, col + 1))
                                    return true;

                            } else {
                                if (baixo(nlin, ncol, npecas, solucao, pecas, line + 1, 0))
                                    return true;
                            }
                        //}
                    }
                    pecas[pos].rotacao();
                }
            }
            pecas[pos].posta = 0;
        }
    }
    //cout << solucao[nlin-1][ncol-1].numero[0] << solucao[nlin-1][ncol-1].numero[1] << solucao[nlin-1][ncol-1].numero[2] << solucao[nlin-1][ncol-1].numero[3];


    return false;
}

static bool baixo(int nlin, int ncol, int npecas, Peca **solucao, Peca *pecas, int line, int col) {
    //cout << "Entrou\n";
    if (line == nlin) {
        return true;
    }

    for (int pos = 0; pos < npecas; pos++) {
        //cout << "pecas[pos]: " << pecas[pos].numero[0] << pecas[pos].numero[1] << pecas[pos].numero[2] << pecas[pos].numero[3] << "\n";
        if (pecas[pos].posta == 0) {
            for (int i = 0; i < 4; ++i) {

                //for (int i = 0; i < 4; ++i) {
                //for (int pos = 0; pos < npecas; pos++) {
                if (solucao[line - 1][col].numero[3] == pecas[pos].numero[0] and
                    solucao[line - 1][col].numero[2] == pecas[pos].numero[1]) {

                    solucao[line][col] = pecas[pos];
                    pecas[pos].posta = 1;

                    //if (pos + 1 <= npecas) {
                    if(ncol == 1) {
                        if (baixo(nlin, ncol, npecas, solucao, pecas, line + 1, 0))
                            return true;
                    }
                    else {
                        if (direita(nlin, ncol, npecas, solucao, pecas, line, col + 1))
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


//concluido
void impressao(Peca **solucao, int nlin, int ncol, bool state) {
    int aux;

    if (!state) {
        cout << "impossible puzzle!\n";
        return;
    } else {
        for (int i = 0; i < nlin; i++) {
            aux = 0;
            //if (solucao[i][aux].numero[0] != 0) {
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
    //}
//}


/*
 * Input
3
3 1 3
2 5 1 3
1 5 4 5
3 2 5 4
2 2 1
1 2 3 4
4 1 3 4
4 2 2
1 2 3 4
1 3 2 5
4 2 3 1
5 4 3 2
 */

