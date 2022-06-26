#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> z(string s){
    int n = s.size();
    vector<int> v(n);

    int l = 0, r = 0;
    for(int i = 1; i < n; i++){
        if(i <= r){
            v[i] = min(v[i - l], r - i + 1);
        }
        while(i+v[i] < n && s[i + v[i]] == s[v[i]]){
            v[i]++;
        }
        if(i + v[i] - 1 > r){
            l = i;
            r = i + v[i] - 1;
        }
    }
    return v;
}

int main(){
    string s, t;
    cin >> s >> t;

    string p = s + "#" + t;
    vector<int> v = z(p);

    for(int i = s.size() + 1; i < p.size(); i++)
        if(v[i] == s.size())
            cout << i - (s.size() + 1) << endl;

    return 0;
}