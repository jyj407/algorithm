// Formula:
// res[i] = min{res[i-1] + a[0] + a[i] , res[i-2] + a[0] + a[i] + 2*a[1] }
#include<vector>
using namespace std;

int crossRiverTime(vector<int>& times) {
    if (times.empty())
        return 0;
 
    sort(times.begin(), times.end());
    int N = times.size();
    if (N == 1)
        return times[0];
    else if (N == 2)
        return max(times[0], times[1]);

    vector<int> res(N, 0);
    res[0] = times[0], res[1] = max(times[0], times[1]);
    for (int i = 2; i < N; i++) {
        res[i] = min(res[i - 1] + times[0] + times[i],
                     res[i - 2] + times[0] + times[i] + 2 * times[1]);
    }
    
    return res[N - 1];
        
}


int main(void) {
    //vector<int> times = {10, 5, 2, 1};
    vector<int> times = {4, 5, 6, 7};
    return crossRiverTime(times);
}



