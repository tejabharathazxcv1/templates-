class STDC {

public : 

    int n ; 
    vector<ll>a ;
    vector<ll> b ; 
    int len ; 
    STDC (vector<ll>& A){
        a = A ;
        n = A.size(); 
        len = (int)sqrt(n + 0.0 ) +1 ;
        b = vector<ll> (len); 
    }

    void init (){

        for(int i = 0 ; i < n ; ++i){
            b[i/len] += a[i]; 
        }
    }

    ll getval (int l , int r){
        ll sum = 0; 
        int L = l / len; 
        int R = r / len; 

        if (L == R){
            for(int i = l ; i <= r ;++i){
                sum += a[i]; 
            }
            return sum ;
        }

        for(int i = l , en = (L + 1)*len - 1 ; i <=en ; ++i){
            sum += a[i]; 
        }

        for(int i = L + 1 ; i <= R - 1 ; ++i){
            sum += b[i]; 
        }

        for(int i = R * len; i <= r ; ++i){
            sum += a[i]; 
        }


        return sum; 
    }


};