#include <iostream>
#include <vector>

using namespace std;

int funcao(vector<vector<int>> nos, int atual);

int main() {
    int n;
    vector<vector<int>> nos;
    while (cin >> n) {
        if (n != -1) {
            vector<int> linha;
            linha.push_back(n);

            while (cin.peek() != '\n') {
                cin >> n;
                linha.push_back(n);
            }

            nos.push_back(linha);
            linha.clear();

        } else {
            funcao(nos, 0);
            nos.clear();
        }
    }

    return 0;
}


int funcao(vector<vector<int>> nos, int atual) {
    //vector<int> final_in;
    //vector<int> final_out;
    vector<int> recrutados = nos.at(atual);

    for (int rec: recrutados) {
        cout << "rec: " << rec << "\n";
    }

    int final_in = 0, final_out = 0;
    if (nos.size() <= 1) { //apenas 1 no
        return 0;
    }

    if(recrutados.size() < 2){ //sem no filho
        return 0;
    }

    //in
    cout << "custo1: " << recrutados.back() << "\n";
    cout << "tamanho rec: " << recrutados.size() << "\n";

    for (int i = 1; i < (int) recrutados.size() - 1; i++) {
        cout << "--------------i: " << i << "\n";
        int a = funcao(nos, recrutados[i]);
        cout << "a: " << a << "\n";
        final_in += a;
        cout << "final_in: " << final_in << "\n";
    }


    //out

    for (int i = 1; i < (int) recrutados.size() - 1; i++) {
        cout << "---->recrutdossss: " << recrutados[i] << "\n";

        cout << "tamanho da linha: " << nos[i].size() << "\n";
        if (nos[i].size() >= 3) { //verificar se tem no filho
            cout << "if\n";
            for (int j = 1; j < (int) nos.at(recrutados[i]).size() -1 ; j++) {
                cout << "!!!!!!!!!!!!!recrutadosss: " << nos.at(recrutados[j])[i] << "\n";
                final_out += funcao(nos, nos.at(recrutados[j])[i]);
                cout << "final_out: " << final_in << "\n";
            }
        }
    }

    cout << "custo2: " << recrutados.back() << "\n";
    return min(final_in, final_out);
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

2 10
3 91
 */