int n, L;
vector<vector<int>> adj;

int timer = 0;

vector<int> tin, tout;

vector<vector<int>> up;

vector<vector<int>> down;

vector<int> sz;

vector<int> dep;

void dfs(int u, int p, int d)
{

    int s = 1;
    dep[u] = d;

    tin[u] = ++timer;

    up[u][0] = p;

    for (int i = 1; i <= L; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
            s += sz[v];
        }
    }

    sz[u] = s;

    tout[u] = ++timer;
}


bool isAncestor(int u, int v)
{

    return (tin[u] <= tin[v]) && (tout[u] >= tout[v]);
}

int lca(int u, int v)
{

    if (isAncestor(u, v)) {
        return u;
    }

    if (isAncestor(v, u)) {
        return v;
    }

    for (int i = L; i >= 0; --i) {
        if (!isAncestor(up[u][i], v)) {
            u = up[u][i];
        }
    }

    return up[u][0];
}



int dist(int u, int v)
{

    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}


// ################  get element at a distance of d from u , on path u to 0 (root) ################
// getpos function is not needed to use, both jump and getpos do the same job


int jump(int u, int d)
{

    for (int i = L; i >= 0; --i) {

        if ((1 << i) <= d) {
            u = up[u][i];
            d -= (1 << i);
        }
    }

    return u;
}

int getpos(int u, int d)
{

    if (d == 0) {
        return u;
    }

    for (int i = L; i >= 0; --i) {

        if ((1 << i) < d) {
            u = up[u][i];
            d -= (1 << i);
        }
    }

    return up[u][0];
}


// ##################      finds element at a distance of k from a on path a to b          ################################

int kthfrom (int a , int b , int  k){

    int x  = lca(a , b); 

    int d =  dist(a, x); 

    if (d >=  k){

        return jump(a , k);  
    }


    k -= d;

    d =  dist(x,  b); 

    

    return  jump(b , d - k ); 

}

void preprocess(int r)
{

    tin = vector<int>(n);
    tout = vector<int>(n);

    sz = vector<int>(n);
    dep = vector<int>(n);

    timer = 0;

    L = ceil(log2(n));


    up = vector<vector<int>>(n, vector<int>(L + 1));

    dfs(r, r, 0);
}


