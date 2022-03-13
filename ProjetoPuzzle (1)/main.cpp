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

static int *rotacao(int peca[]); // concluido
static void rodarTodas(Peca *pecas, int npecas); //concluido
static void puzzle(Peca *pecas, int npecas, int nlin, int ncol);
static int ***direita(int nlin, int ncol, int npecas, int ***solucao, Peca *peca, int pos);


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

        // na impressao do tabuleiro, se o array for 0 ele n imprime, pq n existe nenhuma peca nessa posicao
    }

    return 0;
}


// concluido
static int *rotacao(int peca[]) {
    int aux = peca[3];
    for (int i = 3; i > 0; i--) {
        peca[i] = peca[i-1];
    }
    peca[0] = aux;

    //impressao
    //cout << "Rodada[" << peca[0] << "," << peca[1] << "," << peca[2] << "," << peca[3] << "]\n";

    return peca;
}


// concluido
static void rodarTodas(Peca *pecas, int npecas) {

    for (int i = 0; i < npecas; i++) {  //for para cada peca

        for (int j = 0; j < 3; ++j) {    //for para cada rotacao - so 3 porque nao precisa rodar no fim para a original
            //cout << "rotacao " << j << "\n";
            int aux[4];
            for (int n = 0; n < 4; ++n) {
                aux[n] = pecas[i].numero[n];
            }

            int *rot = rotacao(aux);
            for (int k = 0; k < 4; k++) {   //for para guardar os 4 numeros da peca no fim de rodada
                pecas[i].rotacao[j][k] = rot[k];
            }
        }
    }
}


static void puzzle(Peca *pecas, int npecas, int nlin, int ncol) {
    int ***solucao = new int**[nlin];

    int auxlin = 0, auxcol = 0, pecaPosta = 0;

    //inicializar a solucao a 0
    for (int i = 0; i < nlin; ++i) {
        solucao[i] = new int*[ncol];
        for (int j = 0; j < ncol; ++j){
            solucao[i][j] = new int[4];
            for (int k = 0; k < 4; ++k) {
                solucao[i][j][k] = 0;
            }
        }
    }

    rodarTodas(pecas, npecas);

    //primeira peca
    for (int i = 0; i < 4; ++i) {
        solucao[0][0][i] = pecas[0].numero[i];
    }
    pecas[0].posta = 1;

    /*
    for (int i = 0; i < 4; i++) {
        cout << "Solucao: " << solucao[0][0][i] << "\n";
    }

    for (int j = 0; j < npecas; ++j) {
        cout << "Pecas: [" << pecas[j].numero[0] << pecas[j].numero[1] << pecas[j].numero[2] << pecas[j].numero[3] << "]\n";
    }*/

    //impressao
    for (int i = 0; i < nlin; ++i) {
        for (int j = 0; j < ncol; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (solucao[i][j][k] != 0) {
                    cout << "solucao: " << solucao[i][j][k] << "\n";
                }
            }
        }
    }


    //for (int j = 0; j < npecas; j++) {
    //primeira peca esta posta

    //pecas seguintes
    //direita(nlin, ncol, npecas, solucao, pecas, 1);

    //}

    solucao = direita(nlin, ncol, npecas, solucao, pecas, 1);



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

static int ***direita(int nlin, int ncol, int npecas, int ***solucao, Peca *peca, int pos) {
    int flag = 0;

    //cout << peca[pos].posta;

    if (peca[pos].posta == 0) { //vai tentar por a peca
        for (int i = 0; i < nlin; i++) {
            for (int j = 0; j < ncol; j++) {
                cout << "chegou aqui\n";

                cout << "tem 0: " << solucao[i][j][0] << "\n";

                if( solucao[i][j][0] == 0 ){
                    cout << "chegou aqui22222\n" << solucao[0][0][2] << "\n";
                    cout << "i,j" << i << j << "\n";
                    //cout << solucao[i][j-1][2];//<< "," << peca[pos].numero[0]<< "," << solucao[i][j-1][3]<< "," << peca[pos].numero[3] << "\n";
                    /*if(solucao[i-1][j-1][2] == peca[pos].numero[0] and solucao[i-1][j-1][3] == peca[pos].numero[3]){
                        cout << "Entrou\n";
                        //solucao[i][j] = peca[pos].numero;
                        peca[pos].posta = 1;
                    }

                    //if (pecas[i][1] == solucao[auxcol][auxlin][0] and pecas[i][2] == solucao[auxcol][auxlin][3]):
                     */
                }
            }
        }
    }
    for (int i = 0; i < nlin; ++i) {
        for (int j = 0; j < ncol; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (solucao[i][j][k] != 0) {
                    cout << "solucao22: " << solucao[i][j][k] << "\n";
                }
            }
        }
    }

    //direita(nlin, ncol, npecas, solucao, peca, aux);


    return solucao;
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
