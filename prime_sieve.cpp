
const int PN = 102; 

vector<bool> is_prime (PN+ 1 , true); 

void preprocess (){

    int n= PN; 
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i] && (long long)i * i <= n) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}