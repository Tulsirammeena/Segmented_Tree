#include<bits/stdc++.h>
using namespace std;

class SGTree{
    public:
    vector<int> seg;
    SGTree(int n){
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, vector<int> a){
    if(low == high){
        seg[ind] = a[low];
        return;
    }

    int mid = (low + high)/2;
    build(2 * ind + 1, low, mid,a);
    build(2 * ind + 2, mid + 1, high,a);
    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r){
        // NO Overlap
        // l r low high or low high l r
        if(r < low || high < l){
            return INT_MAX;
        }
        // complete overlap

        else if(low >= l && high <= r)
            return seg[ind];

        // Partial overlap
        int mid = (low + high) / 2;
        int  left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return min(left, right);

    }

    void update(int ind, int low, int high, int i, int val){
        if(low == high){
            seg[ind] = val;
            return;
        }

        int mid = (low + high) / 2;
        if( i <= mid){
            update(2 * ind + 1, low, mid,i, val );
        }
        else {
            update(2 * ind + 2, mid + 1, high, i, val);
        }
        seg[ind] = min(seg[2 * ind + 1] , seg[2 * ind + 2]);
    }
};


// void solve1(){
//     int n;
//     cin >> n;
//     vector<int> a(n),seg(4 * n);
//     for(int i = 0; i < n; i++){
//         cin >> a[i];
//     } 
//     build(0,0,n-1,a,seg);
//     int q;
//     cin >> q;
//     while(q--){
//         int type; 
//         cin >> type;
//         if(type == 1){
//             int l, r;
//             cin >> l >> r;
//             cout<< query(0,0,n-1, l, r, seg) << endl;
//         }
//         else{
//             int i, val;
//             cin >> i >> val;
//             update(0, 0, n-1, i, val, seg);
//             a[i] = val;
//             cout<< a[i] <<endl; 
//         }

//     }
// }
        
void solve2(){
    int n1;
    cin >> n1;
    vector<int> a1(n1);
    for(int i = 0; i < n1; i++)
        cin >> a1[i];
    SGTree seg1(n1);
    seg1.build(0 ,0 , n1 - 1, a1);
    
    int n2;
    cin >> n2;
    vector<int> a2(n2);
    for(int i = 0; i < n2; i++)
        cin >> a2[i];
    SGTree seg2(n2);
    seg2.build(0, 0, n2 - 1, a2); 
     
    int q;
    cin >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            int min1 = seg1.query(0, 0, n1 - 1, l1, r1);
            int min2 = seg2.query(0, 0, n2 - 1, l2, r2);
            cout << min(min1, min2) << endl; 

        }
        else{
            int arrNo,  i,  val;
            cin >> arrNo >> i >> val;
            if(arrNo == 1){
                  seg1.update(0, 0, n1 - 1, i, val);
                  a1[i] = val;  
            }
            else{
                    seg1.update(0, 0, n2 - 1, i, val);
                    a2[i] = val;
            }

        }
    }

}
int main(){
    solve2();

    return 0;
}
