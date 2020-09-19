// ############################  UNDIRECTED  GRAPHS TEMPLATE  ################################################
// change  int to ll, if the weight of the edges are large



struct UNDIR_GRAPH {


    int n ; 
    vector<vector<ar<int,2>>> adj; 
    bool is_weighted =  false; 
    int no_of_edges ;
    int diam_len = 0 ;
    vector<int> parent_d; 
    vector<int> parent; 
    vector<int> diam_path; 
    vector<int> depths  , tin, out_time , subs ;  

    int time = 0;  


    UNDIR_GRAPH (int _n, int _no_of_edges, bool _is_weighted){
        n = _n; 
        adj.resize(n); 
        parent.resize(n, -1); parent_d.resize(n,-1); 
        depths.resize(n); 
        tin.resize(n); 
        out_time.resize(n); 
        subs.resize(n); 
        no_of_edges = _no_of_edges; 
        is_weighted = _is_weighted;
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
            adj[v].push_back({u, w});
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

            cur = max(cur, dfs_d1(j[0], i, d + 1, par));
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

        parent_d = par; 
        while (v != u)
        {
            diam_path.push_back(v);
            v = par[v];
        }

        diam_path.push_back(u);
        
    }

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
        out_time[i] = time; 
        subs[i] = sum; 
    }


};
