#include <string>
#include <iostream>

class Solution {
public:
    std::string mergeAlternately(std::string word1, std::string word2) {
        auto it1 = word1.begin(), it2 = word2.begin();
        auto end1 = word1.end(), end2 = word2.end();

        std::string result;
        while (it1 != word1.end() || it2 != word2.end()){
            if (it1 != end1) result += *it1++;
            if (it2 != end2) result += *it2++;
        }

        return result;
    }
};

int main(){
    Solution sol;
    std::cout << sol.mergeAlternately("abcd", "pq");
}