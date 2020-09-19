// ############################  DIRECTED  GRAPHS TEMPLATE  ################################################
// change  int to ll, if the weight of the edges are large


struct DIR_GRAPH {


    int n ; 
    vector<vector<ar<int,2>>> adj; 
    bool is_weighted =  false; 
    int no_of_edges ;
    int diam_len = 0 ;
    vector<int> parent; 
    vector<int> diam_path; 
    vector<int> depths  , tin, tout , subs ;
    vector<vector<ar<int,2>>> tadj, cadj ;
    vector<int>  ind, top_array , comps;


    int time = 0;  


    DIR_GRAPH (int _n, int _no_of_edges, bool _is_weighted){
        n = _n; 
        adj.resize(n); 
        parent.resize(n, -1); 
        depths.resize(n); 
        tin.resize(n); 
        tout.resize(n); 
        subs.resize(n); 
        no_of_edges = _no_of_edges;
        is_weighted = _is_weighted;
    }

   bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

    void read_graph (){

        int m = no_of_edges; 

        int u, v;

        int w;

        for (int i = 0; i < m; ++i)
        {

            cin >> u >> v;

            --u;
            --v;

            if (is_weighted)
            {
                cin >> w;
            }
            else
            {
                w = 1;
            }

            adj[u].push_back({v, w});
        }


    }


    ar<int, 2> dfs_d1(int i, int p, int d, vector<int>& par)
    {

        ar<int, 2> cur = {d, i};

        par[i] = p;

        for (auto j : adj[i])
        {
            if (j[0] == p)
            {
                continue;
            }

            cur = max(cur, dfs_d1(j[0], i, d + 1,par));
        }

        return cur;
    }

    // diameter length (no of nodes) , diameter path
    void  set_diameter_path()
    {


        vector<int> par = vector<int>(n, -1);

        ar<int, 2> st = dfs_d1(0, -1, 1,par); 


        par = vector<int>(n, -1);

        ar<int, 2> en = dfs_d1(st[1], -1, 1, par);

        diam_len = en[0];

        int u = st[1];
        int v = en[1];

        while (v != u)
        {
            diam_path.push_back(v);
            v = par[v];
        }

        diam_path.push_back(u);
        
    }
    // sets depth, parent,subtree size, in time, out time
    void set_others (int i , int p , int d){
        depths[i] =  d; 

        parent[i] = p ;

        int sum = 1 ;

        tin[i] = time; 
        for(auto j : adj[i]){
            if (j[0] == p){
                continue; 
            }
            ++time; 
            set_others(j[0], i , d + 1); 
            sum +=  subs[i]; 
        }
        tout[i] = time; 
        subs[i] = sum; 
    }

    void set_indegree()
    {

        ind.resize(n);

        for (int i = 0; i < n; ++i)
        {
            for (auto j : adj[i])
            {
                ind[j[0]]++;
            }
        }
    }

    void set_topsort()
    {


        ind.clear();
        set_indegree();


        
        queue<int> q;

        for (int i = 0; i < n; ++i)
        {
            if (ind[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {

            int u = q.front();
            q.pop();

            top_array.push_back(u);

            for (auto v : adj[u])
            {
                if (--ind[v[0]] == 0)
                {
                    q.push(v[0]);
                }
            }
        }

    }

    void set_transpose_graph()
    {
        tadj.resize(n);
        for (int i = 0; i < n; ++i)
        {
            for (auto &j : adj[i])
            {
                tadj[j[0]].push_back({i, j[1]});
            }
        }
    }

    // dfs for kosaraju
    void dfs_sc1(int i, vector<bool> &vis, vector<int> &ord_sc)
    {

        vis[i] = true;

        for (auto &j : adj[i])
        {
            if (vis[j[0]])
            {
                continue;
            }
            dfs_sc1(j[0], vis, ord_sc);
        }

        ord_sc.push_back(i);
    }

    // uses transpose graph 
    void dfs_sc2(int i, int c, vector<bool> &vis)
    {

        vis[i] = true;

        comps[i] = c;

        for (auto j : tadj[i])
        {
            if (vis[j[0]])
            {
                continue;
            }
            dfs_sc2(j[0], c,  vis);
        }
    }

    // uses kosaraju algorithm
    // sets cadj, comps
    void set_compressed_graph()
    {


        vector<bool> vis1(n);

        vector<int> ord_sc;

        comps.resize(n, -1);

        for (int i = 0; i < n; ++i)
        {
            if (vis1[i] == false)
            {
                dfs_sc1(i,  vis1, ord_sc);
            }
        }

        reverse(all(ord_sc));

        set_transpose_graph();

        vector<bool> vis2(n);

        int c = 0;

        for (int i : ord_sc)
        {
            if (vis2[i] == false)
            {
                dfs_sc2(i, c++, vis2);
            }
        }

        cadj.resize(n);

        for (int i = 0; i < n; ++i)
        {
            assert(comps[i] != -1);
            for (auto j : adj[i])
            {
                if (comps[i] == comps[j[0]])
                {
                    continue;
                }
                cadj[comps[i]].push_back({comps[j[0]], j[1]});
            }
        }
    }
};
