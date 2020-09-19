
struct  snode {

    ll val ; 

    ll delta ; 

    snode (ll x){
        val = x ;
        delta = 0  ;
    }

    ll getVal (){
        return val + delta; 
    }


}; 


class stree {

public : 

    vector<ll> L , R , A  ;
    vector<snode> ST ;  

    int n ; 
    stree (vector<ll>& a ){
        A = a; 
        n = a.size(); 
        L.resize(4*n); 
        R.resize(4*n); 
        ST = vector<snode> (4*n , snode(1e18)); 
        init(1 , 0 , n - 1);
    }


    void init (int i , int l , int r){
        
        L[i] = l ;
        R[i] = r; 

        if (l == r){
            ST[i] = snode(A[l]); 
            return; 
        }

        ll mid = (l + r)/ 2; 
        init(2*i , l , mid); 
        init(2*i + 1 , mid + 1 , r);

        merge(i); 


    }

    void propogate (int i ){

        ST[2*i].delta += ST[i].delta; 
        ST[2*i + 1].delta += ST[i].delta; 
    }
    void merge (int i ){

        ST[i].val = min (ST[2*i].getVal() , ST[2*i + 1].getVal()); 
        ST[i].delta = 0 ;
    }
    void update (int i , int l , int r, ll x){
        if (R[i] < l || r < L[i]){
            return; 
        }

        if (l <= L[i] && R[i] <= r){
            ST[i].delta +=  x; 
            return ;
        }

        propogate(i); 
        update(2*i , l , r, x);
        update(2*i + 1 , l , r, x);  
        merge(i); 
    }

    void update(int l , int r , ll x){
        update(1 , l , r , x);
    }

    ll getmin (int i , int l , int r){

        if (R[i] < l || r < L[i] ){
            return 1e18 ;
        }

        if (l <= L[i] && R[i] <= r){
            return ST[i].getVal(); 
        }

        propogate(i); 

        ll left  = getmin(2* i , l , r); 
        ll right = getmin(2 * i + 1 , l, r); 

        merge(i); 

        return min(left , right); 

    }

    ll getmin(int l , int r){
        return getmin(1 , l , r); 
    }

    ll findminind (int i , ll x ){

        if (L[i] == R[i]){
            return L[i]; 
        }

        if (getmin(2*i , L[2*i] , R[2*i] ) == x){
            return findminind (2 * i , x); 
        }

        return  findminind(2*i + 1,x); 

    }

    ll findminind(ll x){
        return findminind(1 , x); 
    }


};