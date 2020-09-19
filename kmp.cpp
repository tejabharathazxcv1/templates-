vector<int> getlps (string &s){
    
    int n = s.size(); 

    vector<int> lps (n) ; 

    for(int i = 1 ; i < n ; ++i){

        int j =  lps[i- 1] ;

        while ((s[j] != s[i])){
            if (j == 0){
                break; 
            }
            j = lps[j - 1]; 
        }

        if (s[j] == s[i]){
            lps[i] = j + 1 ; 
        }
        
    }

    return lps; 
}

int get (string &p , string &s){
    vector<int> lps =  getlps(p) ;


    int n = s.size(); 

    int m = p.size();

    int cnt= 0 ; 
    int l = 0 ; 
    for(int i = 0 ; i < n ; ++i){


        while(s[i] != p[l]){
            if (l == 0){
                break; 
            }
            l = lps[l- 1]; 
        }

        if (s[i] == p[l]){
            ++l;
        }

        if (l ==m ){
            ++cnt; 
            l =  lps[l-1]; 
        }

        
    }

    return cnt  ;
}
