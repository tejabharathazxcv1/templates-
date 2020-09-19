
class EulerianPath {

public : 

    int n , edgeCnt ;
    vector<int> in , out; 

    int start ;
    list<int> path ;
    vector<vector<int>> adj ;


    EulerianPath(vector<vector<int>>& _adj, int x){
        adj = _adj; 
        n = adj.size(); 

        path = list<int>(); 
        start = x ;
    }

    void setup() {

        in = vector<int>(n);
        out = vector<int>(n); 

        edgeCnt = 0 ;

        for(int u = 0 ; u < n ; ++u){
            for(int v : adj[u]){
                in[v]++; 
                out[u]++;
                ++edgeCnt; 
            }
        }


    }


    bool hasEulerianPath(){

        int startNodes = 0 , endNodes = 0 ;

        for(int i = 0 ; i <  n; ++i){

            if (out[i] -  in[i] > 1 || in[i] - out[i] > 1){
                return false; 
            }
            else if (out[i] - in[i] == 1){
                startNodes++;
            }
            else if (in[i] - out[i] == 1){
                endNodes++;
            }
        }

        return (endNodes == 0 && startNodes == 0) || (endNodes == 1 && startNodes == 1); 


    }



    void edfs(int i ){

        while(out[i] != 0){

            int next = adj[i][--out[i]]; 
            edfs(next);
        }

        path.push_front(i); 

    }

    int findStartNode(){

        return start;
        
    }

    vector<int> getEulerianPath(){

        setup(); 

        if (edgeCnt == 0){
            return {}; 
        }

        if (!hasEulerianPath()){
            return {}; 
        }

        edfs(findStartNode()); 

        if (path.size() != edgeCnt + 1){
            return {}; 
        }

        vector<int> sol (path.begin(),path.end());

        return sol ;

    }


};

