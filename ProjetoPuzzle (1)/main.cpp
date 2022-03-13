#include <iostream>
#include <vector>
using namespace std;

class Peca {
public:
    int numero[4];
    //vector<int> numero {0,0,0,0};
    int posta = 0;
    //int rodada = 0;
    int rotacao[3][4]; //3 rotacoes sem a original
};

static Peca rotacao(Peca peca); // concluido
static void puzzle(Peca *pecas, int npecas, int nlin, int ncol);
static bool direita(int nlin, int ncol, int npecas, Peca **solucao, Peca *peca, int pos, int line, int col);


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int ntest, npecas, nlin, ncol;
    cin >> ntest;
    cout << ntest << "\n";

    for (int i = 0; i < ntest; i++){
        cin >> npecas >> nlin >> ncol;
        cout << npecas << nlin << ncol << "\n";
        Peca pecas[npecas];

        for (int j = 0; j < npecas; j++) {
            cin >> pecas[j].numero[0] >> pecas[j].numero[1] >> pecas[j].numero[2] >> pecas[j].numero[3];
        }

        //impressao
        for (int j = 0; j < npecas; ++j) {
            cout << "[" << pecas[j].numero[0] << pecas[j].numero[1] << pecas[j].numero[2] << pecas[j].numero[3] << "]\n";
        }

        puzzle(pecas, npecas, nlin, ncol);


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

    int auxlin = 0, auxcol = 0, pecaPosta = 0;

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


    //primeira peca esta posta

    //pecas seguintes
    //direita(nlin, ncol, npecas, solucao, pecas, 1);

    direita(nlin, ncol, npecas, solucao, pecas, 1, 0, 1);

    //impressao solucao
    for (int i = 0; i < nlin; ++i) {
        for (int j = 0; j < ncol; ++j) {
            for (int k = 0; k < 4; ++k) {
                cout << "solucao2222: " << solucao[i][j].numero[k] << "\n";
            }
            cout << "-------------------\n";
        }
    }

}

static bool direita(int nlin, int ncol, int npecas, Peca **solucao, Peca *peca, int pos, int line, int col) {
    if (peca[pos].posta == 0) { //a peca nao esta posta, vai por
        if (solucao[line][col - 1].numero[1] == peca[pos].numero[0] and solucao[line][col - 1].numero[2] == peca[pos].numero[3]) {
            solucao[line][col] = peca[pos];
            peca[pos].posta = 1;

            if (pos + 1 < npecas) {
                direita(nlin, ncol, npecas, solucao, peca, pos + 1, line, col + 1);
            }

        } else {
            rotacao(peca[pos]);
            return false;
        }
    } else { //a peca esta posta, vai avancar
        if (pos + 1 <= npecas) {
            direita(nlin, ncol, npecas, solucao, peca, pos + 1, line, col + 1);
        }
    }

    return true;
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
