#include <iostream>
#include <tuple>

using namespace std;

int euclid(int a, int b, int& x, int& y){
    int r1 = a, r2 = b;
    int x1 = 1, y1 = 0;
    int x2 = 0, y2 = 1;

    while(r2 > 0){
        int q = r1/r2;
        tie(r1, r2) = make_pair(r2, r1 - q * r2);
        tie(x1, x2) = make_pair(x2, x1 - q * x2);
        tie(y1, y2) = make_pair(y2, y1 - q * y2);
    }

    x = x1;
    y = y1;
    return a;
}

bool diofant(int a, int b, int c, int& x, int& y){
    int d = euclid(abs(a), abs(b), x, y);

    if(c % d != 0)
        return false;

    if(a < 0)
        x *= -1;
    if(b < 0)
        y *= -1;

    x *= c / d;
    y *= c / d; 
    return true;
}

int main(){
    int a, b, c, x, y, d;
    cin >> a >> b;
    cin >> c;

    // d = euclid(a, b, x, y);
    
    // cout << d << ' = ' << a << ' * ' << x << ' + ' << b << ' * ' << y << endl;

    if(diofant(a, b, c, x, y))
        cout << c << ' = ' << a << ' * ' << x << ' + ' << b << ' * ' << y << endl;
    else
        cout << "No result." << endl;

    return 0;
    
}