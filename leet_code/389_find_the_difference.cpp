#include <string>
#include <unordered_set>

class Solution {
public:
    char findTheDifference(std::string s, std::string t) {
        std::unordered_multiset<char> set_t(t.begin(), t.end());
        char result;

        for (char c: s){
            set_t.erase(set_t.find(c));
        }

        return *set_t.begin();
    }
};