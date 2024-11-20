#include <iostream>
#include <algorithm>
using namespace std;
struct Student{    string name; float score;};
int n = 0, c = 0; Student sts[100000];
bool MySort(Student sts1, Student sts2)
{
    switch (c)
    {
    case 1: return sts1.score < sts2.score;
    case 2: return sts1.score == sts2.score ? sts1.name < sts2.name : sts1.name < sts2.name;
    }
    return false;
}

int main()
{
        while(scanf("%d", &n) != EOF)
    int c = 1;
    while (cin >> n&& 0 != n) for (int i = 0; i < n; ++i) cin >> sts[i].score >> sts[i].name;
    sort(sts, sts + n, MySort); cout << "Case:" << endl; for (int i = 0; i < n; ++i) cout << sts[i].score << ' ' << sts[i].name << endl; return 0;
}
