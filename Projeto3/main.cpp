#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n_op, time, n_dep, dep, stat;
    vector<vector<int>> operacoes;
    vector<int> line;

    cin >> n_op;
    for (int i = 0; i < n_op; i++) {
        cin >> time >> n_dep;
        line.push_back(time);
        line.push_back(n_dep);
        for (int j = 0; j < n_dep; j++) {
            cin >> dep;
            line.push_back(dep);
        }
        operacoes.push_back(line);
        line.clear();
    }
    cin >> stat;

    /* impressao
    for(vector<int> a: operacoes) {
        for(int b: a) {
            cout << b << " ";
        }
        cout << "\n";
    }
    cout << stat;
     */

    
}
