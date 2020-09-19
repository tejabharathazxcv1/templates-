
const int dx[] = {0,0, -1,1};
const int dy[] = {-1 ,1 , 0 , 0 };

// const int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int m , n ; 

bool valid (int i , int j ){

    if (i < 0 || j < 0 || i>= m || j >= n){
        return false;
    }

    return true; 
}

