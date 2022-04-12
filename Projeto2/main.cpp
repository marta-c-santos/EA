#include <iostream>
#include <vector>

using namespace std;

void funcao(vector<vector<int>> nos);
void check_rec(vector<vector<int>> nos, vector<int> final[], int atual, int anterior);

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
            funcao(nos);
            nos.clear();
        }
    }

    return 0;
}

void funcao(vector<vector<int>> nos){
    vector<int> final[nos.size() + 1];

    for (int i = 0; i < nos.size(); ++i) {
        final[i].push_back(0);

        final[i].push_back(1);
    }

    check_rec(nos, final, 0, -1);

    cout << min(final[1][0], final[1][1]) << endl;
}

void check_rec(vector<vector<int>> nos, vector<int> final[], int atual, int anterior) {
    cout << "atual: " << atual  << " anterior: " << anterior << "\n";
    vector<int> custo;

    vector<int> rec = nos.at(atual);

    for (int pos = 1; pos < (int) rec.size() - 1; pos++) {
        if (rec[pos] != anterior) {
            check_rec(nos, final, rec[pos], atual);
        }
    }

    for (int pos = 1; pos < (int) rec.size() - 1; pos++) {
        if (rec[pos] != anterior) {
            custo.push_back(nos.at(atual).back());
            // in
            final[atual][0] += final[atual][1];
            // out
            final[atual][1] += min(final[atual][1], final[atual][0]);
        }
    }

    int c;
    for (int i = 0; i < custo.size(); ++i) {
        cout << "custo: " << custo[i] << "\n";
        c += custo[i];
    }

    cout << "custo final: " << c << "\n";
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