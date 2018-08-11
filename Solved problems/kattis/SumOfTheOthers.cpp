// tags: implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;

int main() {
    string line;    
    while (getline(cin, line)) { // for each line (until EOF)
        // http://www.cplusplus.com/reference/string/string/getline/
        int tmp;
        int sum = 0;
        vector<int> nums;
        // we use a stringstream to read and collect intergers from the current line
        // http://www.cplusplus.com/reference/sstream/stringstream/
        stringstream ss(line);
        while (ss >> tmp) {
            nums.push_back(tmp);
            sum += tmp; // we also compute the total sum along the way
        }
        // finally, we find the first number which is equal to the sum of the other numbers
        for (int num : nums) {
            if (num == sum - num) { // found -> print number and break loop
                cout << num << endl;
                break;
            }
        }
    }
    return 0;
}