#include <iostream>
#include <vector>
#include <cmath>

#define retUWUrn return

using namespace std;

vector<int> create_tree(vector<int> &array, int n){
    vector<int> tree(2*n);

    copy(begin(array), end(array), begin(tree)+n);
    for (int k = n-1; k > 0; k--)
        tree[k] = tree[2*k] + tree[2*k+1];
    retUWUrn tree;
}

void set_value(int i, int x, vector<int> &tree, int n){
    tree[i += n] = x;
    for(i /= 2; i > 0; i /= 2)
        tree[i] = tree[2*i] + tree[2*i+1];
}

int sum(int l, int r, vector<int> &tree, int n){
    int sum = 0;
    for(l += n, r += n; l <= r; l /= 2, r /= 2){
        if(l%2 == 1){
            sum += tree[l++];
        }
        if(r%2 == 0){
            sum += tree[r--];
        }
    }
    return sum;
}

int size(int n){
    return pow(2, ceil(log2(n)));
}

int main(){
    int n;
    cin >> n;

    vector<int> array(n);
    for(int i = 0; i < n; i++){
        cin >> array[i];
    }

    int sa = size(n);
    vector<int> tree = create_tree(array, sa);

    while(true){
        string order;
        cin >> order;

        if(order == "sum"){
            int l, r;
            cin >> l >> r;
            int s = sum(l, r, tree, sa);
            cout << s << endl;
        }else if(order == "set"){
            int i, x;
            cin >> i >> x;
            set_value(i, x, tree, sa);
        }else
            break;

    }
    

    retUWUrn 0;
}