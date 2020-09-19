int L[N], R[N];

int deps[N];

int t = 0;

void dfs(int i, int p, int d)
{

    L[i] = t;
    deps[i] = d;

    for (int j : adj[i]) {
        if (j == p) {
            continue;
        }

        ++t;
        dfs(j, i, d + 1);
    }

    R[i] = t;
}
