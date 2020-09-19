
class TrieNode{

public :

    int endCnt= 0 ; 

    int prefCnt = 0 ;

    TrieNode* alphas[26]; 

    TrieNode(){
        
        prefCnt = 0; 
        endCnt = 0 ;
        for(int i = 0 ; i < 26 ; ++i){
            alphas[i] = NULL; 
        }
    }

    void insert (const string &s){

        TrieNode* cur = this;

        // debug(s); 

        for(char c : s){
            // debug(c);

            if (!cur ->alphas[c-'a']){
                cur->alphas[c-'a'] =  new TrieNode(); 
            }

            cur->alphas[c-'a']->prefCnt++; 

            cur = cur->alphas[c-'a']; 
        }

        cur->endCnt++; 
    }


    bool search (const string &s){
        TrieNode* cur = this ;

        for(char  c : s){
            if (!cur->alphas[c-'a']){
                return false;
            }
            cur = cur->alphas[c-'a']; 
        }

        return cur->endCnt >0 ;
    }
    
    bool startsWith(const string &p){

        TrieNode* cur = this ;

        for(char c : p){
            if (!cur->alphas[c-'a']){
                return false; 
            }
            cur = cur->alphas[c-'a']; 
        }

        return true; 

    }

    
};


ll ans = 0 , k;


// dfs on Trie
ll dfs(TrieNode* u, int d){

    if (u == NULL){
        return  0; 
    }

    ll cnt = u->endCnt; 

    for(TrieNode* v:  u->alphas){
        cnt += dfs(v, d + 1); 
    }

    if (cnt >= k){


        ans += (cnt/k) * d;
        cnt %= k; 
    }

    return cnt ;
    

}

