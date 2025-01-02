#include<bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin>>T;

    switch (T) {
        case 1:
            printf("I love Luogu!\n");
            break;
        case 2:
            printf("6 4\n");
            break;
        case 3:
            printf("3\n12\n2\n");
            break;
        case 4:
            printf("%.3lf\n", 500.0 / 3);
            break;
        case 5:
            printf("%d\n", (260 + 220) / (12 + 20));
            break;
        case 6:
            cout<<sqrt(36 + 81);
            break;
        case 7:
            printf("%d\n%d\n%d\n", 100 + 10, 100 + 10 - 20, 0);
            break;
        case 8: {
            double Pi = 3.141593;
            int r = 5;
            cout<<2 * Pi * r<<endl<<Pi * r * r<<endl<<Pi * r * r * r * 4 / 3.0<<endl;
            break;
        }
        case 9: {
            int k = 1;
            for (int i = 1; i <= 3; i++) {
                k = (k + 1) * 2;
            }
            printf("%d\n", k);
            break;
        }
        case 10: {
            printf("9");
            break;
        }
        case 11:
            cout<<(100.0 / (8 - 5));
            break;
        case 12:
            printf("%d\n%c\n", 'M' - 'A' + 1, 'A' + 17);
            break;
        case 13: {
            double Pi = 3.141593;
            double v1 = 4.0 / 3 * Pi * pow(4, 3);
            double v2 = 4.0 / 3 * Pi * pow(10, 3);
            double total_volume = v1 + v2;
            double side_length = pow(total_volume, 1.0 / 3);
            printf("%d\n", (int)side_length);
            break;
        }
        case 14: {
            cout<<50<<endl;
        }
    }

    return 0;
}