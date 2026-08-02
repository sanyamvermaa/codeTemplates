#include <vector>

using namespace std;

class TreeAncestor {
private:
    int LOG;
    vector<vector<int>> up; // up[node][k] -> (2^k)-th ancestor of node

public:
    TreeAncestor(int n, vector<int>& parent) {
        // Compute max binary jumps needed (LOG = log2(n))
        LOG = 0;
        int temp = n;
        while (temp) {
            LOG++;
            temp >>= 1;
        }

        up.resize(n, vector<int>(LOG + 1, -1));

        // Base case: 2^0 = 1st ancestor (direct parent)
        for (int i = 0; i < n; i++) {
            up[i][0] = parent[i];
        }

        // DP state transition: 2^k ancestor = (2^(k-1))-th ancestor of (2^(k-1))-th ancestor
        for (int k = 1; k <= LOG; k++) {
            for (int node = 0; node < n; node++) {
                if (up[node][k - 1] != -1) {
                    up[node][k] = up[up[node][k - 1]][k - 1];
                }
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        // Decompose k into powers of 2 and jump
        for (int i = 0; i <= LOG; i++) {
            if ((k >> i) & 1) {
                node = up[node][i];
                if (node == -1) break; // Out of bounds above root
            }
        }
        return node;
    }
};
