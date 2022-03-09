#include <iostream>
#include <vector>
using namespace std;

class Peca {
public:
    int numero[4];
    //vector<int> numero {0,0,0,0};
    int posta = 0;
    int rodada = 0;
};

static vector<int> rotacao(vector<int> peca); //concluido
static void puzzle(Peca *pecas, int nlin, int ncol);
static void direita();

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

        puzzle(pecas, nlin, ncol);

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


static void puzzle(Peca *pecas, int nlin, int ncol) {
    int solucao[nlin][ncol][4];
    int auxlin = 0, auxcol = 0, pecaPosta = 0;

    for (int i = 0; i < 4; ++i) {
        solucao[0][0][i] = pecas[0].numero[i];
    }

    //impressao
    for (int i = 0; i < nlin; ++i) {
        for (int j = 0; j < ncol; ++j) {
            for (int k = 0; k < 4; ++k) {
                cout << solucao[i][j][k];
            }
        }
    }

    //por pensar
    for(Peca peca: pecas){
        // primeira peca
        //chamar direita recursiva
        //andar nas pecas
        //chamar direita para colocar
    }










    /*
    for (int i = 0; i < 4; ++i) {
        solucao[0][0][i] = pecas[0][i];
    }

    while(pecaPosta <= pecas.size()) {
        for (int i = 0; i < pecas.size(); ++i) {
            int a = 0;
        }

        // por peca
        // insert na solucao
        // pecaPosta == 1:     #pos a peca
        // ao vetor pecas tem de retirar a q foi posta


        // se houver pecas avanca
    }

    //pecas[0] = rotacao(pecas[0]);
}*/
}

static void direita(){

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
