#include <cmath>
#include <iostream>
using namespace std;

void check(int x, int l, int r) {
    int smallest = l * (l + 1) * (l + 2);
    int abc[3] = {0,0,0};
    bool bingo = false;
    if (x < smallest) {
        cout << -1 << endl;
        return;
    }

    for (int i = l; i < (r - l) + 1; i++) {
        if (x % i == 0) {
            int a = x / i;
            for (int j = l; j < (r - l) + 1; j++) {
                if (i == j) continue;
                if (a % j == 0) {
                    int b = a / j;
                    if (b <= r && b >= l) {            
                        abc[0] = i;
                        abc[1] = j;
                        abc[2] = b;
                        bingo = true;
                    }
                }
            }
        }
    }

    if (bingo) {
        cout << abc[0] << " " << abc[1] << " " << abc[2] << endl;
    } else {
        cout << -1 << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int x, l, r;
        cin >> x >> l >> r;
        check(x, l, r);
    }

    return 0;
}
