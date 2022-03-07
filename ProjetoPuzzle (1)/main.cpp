#include <iostream>
#include <vector>
using namespace std;

static int* rotacao(int peca[]);
static void puzzle(int pecas[][4], int nlin, int ncol);

int main() {

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int ntest, npecas, nlin, ncol;
    std::cin >> ntest;
    std::cin >> npecas >> nlin >> ncol;

    for (int i = 0; i < ntest; i++) {
        int totalpecas[npecas][4];
        int peca[4];

        for (int j = 0; j < npecas; j++) {
            std::cin >> peca[0] >> peca[1] >> peca[2] >> peca[3] ;
            for (int k = 0; k < 4; ++k) {
                totalpecas[j][k] = peca[k];
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

static int* rotacao(int peca[]) {
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

static void puzzle(int pecas[][4], int nlin, int ncol){

    rotacao(pecas[0]);
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
