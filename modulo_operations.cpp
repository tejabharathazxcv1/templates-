const int N = 2e5 + 10;

const int invN = 1500; 

ll ainv[invN]; 

ll fact[N];

int add(int x, int y)
{

    // assuming x and y values are valid [0 , M-1]
    /*

        x %= M ;
        y %= M ;
        if (x < 0) {
            x += M;
        }
        if (y < 0) {
            y += M;
        }

    */
    x += y;
    if (x >= M)
        return x - M;
    return x;
}

int sub(int x, int y)
{

    // assuming x and y values are valid [0 , M-1]
    /*

        x %= M ;
        y %= M ;
        if (x < 0) {
            x += M;
        }
        if (y < 0) {
            y += M;
        }

    */
    x -= y;
    if (x < 0)
        return x + M;
    return x;
}

int mul(int x, int y)
{
    // assuming x and y values are valid [0 , M-1]
    /*

        x %= M ;
        y %= M ;
        if (x < 0) {
            x += M;
        }
        if (y < 0) {
            y += M;
        }

    */
    return ((ll)x * y) % M;
}

void preprocess(){

    ainv[1] = 1 ;

    for(int i = 2 ; i < invN; ++i){
        ainv[i] = M - M/i * ainv[M % i] %M;
    }

    fact[0] = 1 ;

    for(int i = 1 ; i< N;++i){
        fact[i] = mul(fact[i-1],i); 
    }

}


void euclid (ll a, ll b , ll &x , ll &y){

    if(a == 1){

        x = 1 ;
        y = 0 ; 
        return ;
    }

    ll x1 , y1 ;
    euclid(b % a , a , x1 , y1); 

    x = y1 - (b/a) * x1; 

    y = x1; 

}


ll einv (ll b){

    int a= b % M; 

    if (__gcd(a, M) != 1){
        return -1; 
    }

    ll x, y ;

    euclid(a ,M , x,  y);

    x = (x % M + M) % M ;
    return x ;
}


ll binpow(ll a, ll b){

    a %= M; 

    ll res = 1 ;

    while(b > 0){

        if (b & 1){
            res = res * a % M;
        }

        a = a * a % M; 

        b >>= 1;
    }

    return res;
}



ll binv(ll x){
    return binpow(x , M - 2);
}


ll divide (ll x, ll y){
    x %= M ;
    y %= M ;

    // choose any inverse method   here 
    return mul(x,  einv(y));
}


int C(int n , int k){

    return divide(fact[n] , mul(fact[k] , fact[n-k])); 
}
