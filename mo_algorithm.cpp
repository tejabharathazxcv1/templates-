unordered_map<ll,ll> m ; 

vector<ll> A ;

void remove(int i){

    if (--m[A[i]] == 0){
        m.erase(A[i]); 
    }
}

void add(int i){
    ++m[A[i]]; 
}


int getval(){

   return m.size();  
}

const int BL = sqrt (30000) + 1 ;

// bool cmp(pair<int, int> p, pair<int, int> q)
// {
//     if (p.first / BL != q.first / BL)
//         return p < q;
//     return (p.first / BL & 1) ? (p.second < q.second) : (p.second > q.second);
// }

struct Query {

    int l , r, idx; 

    Query(int _l , int _r, int _idx){
        l = _l; 
        r = _r;
        idx = _idx;
    }

    bool operator< (Query other)const{

        return make_pair(l / BL , r) <  make_pair(other.l / BL , other.r); 
    }

};

vector<ll> MO (vector<Query> queries){


    vector<ll> ans(queries.size()); 


    sort(queries.begin(),queries.end()); 

    int cur_l = 0 ;
    int cur_r = -1 ;

    for(Query q :  queries){


        while(cur_l >  q.l){
            --cur_l; 
            add(cur_l); 
        }

        while(cur_r < q.r){
            ++cur_r; 
            add(cur_r); 
        }

        while(cur_l < q.l){
            remove(cur_l); 
            cur_l++; 
        }

        while(cur_r > q.r){
            remove(cur_r); 
            cur_r--;
        }

        ans[q.idx] = getval(); 
    }

    return ans;
}

