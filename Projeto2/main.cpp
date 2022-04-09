#include <iostream>
#include <vector>
using namespace std;
int len;
vector<int> rec;

void funcao(vector<vector<int>> nos);
void check_rec(int id, vector<vector<int>> nos);

int main() {
    int n;
    vector<vector<int>> nos;
    while (cin >> n){
        //cout << n << "\n";
        if (n != -1) {
            vector<int> linha;
            linha.push_back(n);

            while(cin.peek() != '\n') {
                cin >> n;
                //cout << "n: " << n << " / ";
                linha.push_back(n);
            }
            //cout << "\n";
            nos.push_back(linha);

            /*for (int s: linha){
                cout << "linha: " << s << " | ";
            }*/

            linha.clear();
            //cout << "\n";
        } else {
            len = (int)nos.size();
            //cout << "len: " << len << "\n";
            funcao(nos);
            nos.clear();
        }
    }

    return 0;
}

void funcao(vector<vector<int>> nos) {
    for (int pos = 0; pos < len; pos++) {
        if (nos[pos].size() == 2) {
            //cout << "folhas: " << nos[pos][0] << "\n";
            check_rec(nos[pos][0], nos);
        }
    }

    int custo = 0, count = 0;
    //cout << "size rec: " << rec.size() << "\n";
    for (int i = 0; i < rec.size(); i++) {
        for (int pos = 0; pos < len ; pos++) {
            if( nos[pos][0] == rec[i]) {
                //cout << "custo: " << nos[pos].back() << "\n";
                custo += nos[pos].back();
            }
        }
    }
    count = rec.size();
    cout << count << " " << custo << endl;


    /*
     * verificar o tamanho da linha (nos[pos])
     * se for > 2 é porque tem pelo menos 1 recrutado
     * verificar se conseguimos verificar a existência de todos os recrutados
     */

    /* impressao
    for (int i = 0; i < nos.size(); ++i) {
        for (int j: nos[i]){
            cout << "linha: " << j << " | ";
        }
        cout << "\n";
    }
    cout << "\n\n";*/
}


void check_rec(int id, vector<vector<int>> nos) {
    int aux = 0;
    for (int pos = 0; pos < len; pos++) {
        int nolen = nos[pos].size();
        for (int i = 1; i < nolen - 1; i++) {
            if (nos[pos][i] == id) {
                //cout << "recrutador: " << nos[pos][0] << "\n";
                if(!rec.empty()) {
                    for (int j = 0; j < rec.size(); j++) {
                        if (nos[pos][0] != rec[j])
                            aux++;
                        //cout << "comp: " << aux << "\n";
                        if (aux == rec.size())
                            rec.push_back(nos[pos][0]);
                    }
                } else {
                    rec.push_back(nos[pos][0]);
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
 */