#include <iostream>
#include <vector>
using namespace std;

class Peca {
public:
    int numero[4];
    int posta = 0;
};


static Peca rotacao(Peca peca); // concluido
static void puzzle(Peca *pecas, int npecas, int nlin, int ncol);
static bool direita(int nlin, int ncol, int npecas, Peca **solucao, Peca *pecas, int line, int col);
void impressao(Peca *pecas, int nlin, int ncol, bool state);

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int ntest, npecas, nlin, ncol;
    cin >> ntest;
    //cout << ntest << "\n";

    for (int i = 0; i < ntest; i++){
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
        puzzle(pecas, npecas, nlin, ncol);
        //impressao(pecas, npecas, nlin, ncol);

    }

    return 0;
}


// concluido
static Peca rotacao(Peca peca) {
    int aux = peca.numero[3];
    for (int i = 3; i > 0; i--) {
        peca.numero[i] = peca.numero[i-1];
    }
    peca.numero[0] = aux;

    //impressao
    //cout << "Rodada[" << peca[0] << "," << peca[1] << "," << peca[2] << "," << peca[3] << "]\n";

    return peca;
}


static void puzzle(Peca *pecas, int npecas, int nlin, int ncol) {
    Peca **solucao = new Peca*[nlin];

    //inicializar a solucao a 0
    for (int i = 0; i < nlin; ++i) {
        solucao[i] = new Peca[ncol];
    }

    //primeira peca
    solucao[0][0]= pecas[0];
    pecas[0].posta = 1;

    /*
    for (int i = 0; i < 4; i++) {
        cout << "Solucao: " << solucao[0][0][i] << "\n";
    }

    for (int j = 0; j < npecas; ++j) {
        cout << "Pecas: [" << pecas[j].numero[0] << pecas[j].numero[1] << pecas[j].numero[2] << pecas[j].numero[3] << "]\n";
    }*/

    bool state = direita(nlin, ncol, npecas, solucao, pecas, 0, 1);
    //cout << state << "\n";
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

    impressao(*solucao, nlin, ncol, state);

}

static bool direita(int nlin, int ncol, int npecas, Peca **solucao, Peca *pecas, int line, int col) {
    for (int pos = 1; pos < npecas ; pos++) {
        if (pecas[pos].posta == 0) {//a pecas nao esta posta, vai por
            for (int i = 0; i < 4; ++i) {
                if (solucao[line][col - 1].numero[1] == pecas[pos].numero[0] and
                    solucao[line][col - 1].numero[2] == pecas[pos].numero[3]) {
                    solucao[line][col] = pecas[pos];
                    pecas[pos].posta = 1;

                    if (pos + 1 < npecas) {
                        if (direita(nlin, ncol, npecas, solucao, pecas, line, col + 1))
                            return true;
                    }
                } else {
                    Peca aux = rotacao(pecas[pos]);
                    pecas[pos] = aux;
                }
            }
            pecas[pos].posta = 0;
        }
    }



    //cout << solucao[nlin-1][ncol-1].numero[0] << solucao[nlin-1][ncol-1].numero[1] << solucao[nlin-1][ncol-1].numero[2] << solucao[nlin-1][ncol-1].numero[3];
    if(solucao[nlin-1][ncol-1].posta == 1){
        return true;
    }

    return false;
}


void impressao(Peca *pecas, int nlin, int ncol, bool state) {
    int aux = 0;


    if (state == 0) {
        cout << "impossible puzzle!\n";
        return;
    }
    else{
        for (int l = 0; l < nlin; ++l) {
            if (pecas[aux].numero[0] != 0) {
                if (l >= 1)
                    cout << "\n";
                cout << pecas[aux].numero[0] << " " << pecas[aux].numero[1];
                if (ncol >= 1) {
                    for (int j = 1; j < ncol; j++) {
                        cout << "  " << pecas[j].numero[0] << " " << pecas[j].numero[1];
                    }
                }
                cout << "\n";
                cout << pecas[aux].numero[3] << " " << pecas[aux].numero[2];
                if (ncol >= 1) {
                    for (int j = 1; j < ncol; j++) {
                        cout << "  " << pecas[j].numero[3] << " " << pecas[j].numero[2];
                    }
                }
                cout << "\n";
                aux++;
            }
        }
    }



    //if (pecas[nlin].numero[0] == 0 or pecas[ncol].numero[0] == 0) {
    //cout << "wwwwwwwwwwwwwwww: " << pecas[1].numero[0] << "\n";
    /*
    if (pecas[1].numero[0] == 0) {
        cout << "impossible puzzle!\n";
    }*/
}


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
