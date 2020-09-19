class DSU{
public:

    vector<int> parent ;

    vector<int> sizes;

    int noOfComponenents;

    DSU(int N) {
        parent.resize(N) ;

        sizes.resize(N);
        
        noOfComponenents = N;

        for(int i = 0 ; i < N; ++i){
            parent[i] = i;
            sizes[i] = 1;
        }

    }

    int find(int x){
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    /* 

    int find(int p){

        int root = p ;

        while(root != parent[root]) root = parent[root];

        while(p != root){
            int next = parent[root];
            parent[root] = root ;
            p = next;
        }

        return root;
    }

    // mofidy into c++
    public void unify(int p, int q) {

    int root1 = find(p);
    int root2 = find(q);

    // These elements are already in the same group!
    if (root1 == root2) return;

    // Merge smaller component/set into the larger one.
    if (sz[root1] < sz[root2]) {
      sz[root2] += sz[root1];
      id[root1] = root2;
    } else {
      sz[root1] += sz[root2];
      id[root2] = root1;
    }

    // Since the roots found are different we know that the
    // number of components/sets has decreased by one
    numComponents--;
  }
 */

    void unify(int x, int y){

        if (parent[find(x)] == parent[find(y)]){
            return;
        }
        --noOfComponenents;
        sizes[find(y)] += sizes[find(x)];
        parent[find(x)] = find(y);
    }


    bool isConnected(int p , int q){
        return find(p) == find(q);
    }

    int componentSize(int p){
        return sizes[p];
    }

};