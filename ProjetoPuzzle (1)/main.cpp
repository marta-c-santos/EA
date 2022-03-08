#include <iostream>
#include <vector>
using namespace std;

class Peca {
    public:
        int numero[4];
        int posta = 0;
        int rodada = 0;
};

static vector<int> rotacao(vector<int> peca); //concluido
static void puzzle(vector<vector<int>> pecas, int nlin, int ncol);


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int ntest, npecas, nlin, ncol;
    cin >> ntest;
    cout << ntest << "\n";
    cin >> npecas >> nlin >> ncol;
    cout << npecas << nlin << ncol << "\n";

    for (int i = 0; i < ntest; i++){
        cout << "antes vector" << "\n";
        vector<vector<int>> totalpecas;
        cout << "depois vector\n";
        int peca[4];

        for (int j = 0; j < npecas; j++) {
            cout << "chegouuu" << "\n";
            cin >> peca[0] >> peca[1] >> peca[2] >> peca[3];
            cout << "leu" << "\n";

            for (int k = 0; k < 4; ++k) {
                cout << "--------entrouu forr" << "\n";
                //totalpecas[j][k] = peca[k];
                //cout << ".......adicionouu";
            }
        }

        /*
        for (int j = 0; j < npecas; ++j) {
            cout << "[" << totalpecas[j][0] << "," << totalpecas[j][1] << "," << totalpecas[j][2] << "," << totalpecas[j][3] << "]\n";
        }
*/
        puzzle(totalpecas, nlin, ncol);

        // na impressao do tabuleiro, se o array for 0 ele n imprime, pq n existe nenhuma peca nessa posicao
    }

    return 0;
}

//concluido
static vector<int> rotacao(vector<int> peca) {
    int aux = peca[3];
    for (int i = 3; i > 0; i--) {
        peca[i] = peca[i-1];
    }
    peca[0] = aux;
    /*
    for (int j = 0; j < 4; ++j) {
        cout << "Rodada[" << peca[0] << "," << peca[1] << "," << peca[2] << "," << peca[3] << "]\n";
    }
    */
    return peca;
}


static void puzzle(vector<vector<int>> pecas, int nlin, int ncol) {
    int solucao[nlin][ncol][4];
    int auxlin = 0, auxcol = 0, pecaPosta = 0;
    for (int i = 0; i < 4; ++i) {
        solucao[0][0][i] = pecas[0][i];
    }
    for (int j = 0; j < 4; ++j) {
        cout << "peca[" << solucao[0] << "," << solucao[1] << "," << solucao[2] << "," << solucao[3] << "]\n";
    }

    while(pecaPosta <= pecas.size()) {
        for (int i = 0; i < pecas.size(); ++i) {

        }

        // por peca
        // insert na solucao
        // pecaPosta == 1:     #pos a peca
        // ao vetor pecas tem de retirar a q foi posta


        // se houver pecas avanca
    }

    //pecas[0] = rotacao(pecas[0]);
}
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
