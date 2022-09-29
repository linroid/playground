class Solution {
    std::map<char, char> backets = {
        std::make_pair('(', ')'),
        std::make_pair('{', '}'),
        std::make_pair('[', ']')
    };
public:
    bool isValid(string s) {
        stack<char> stack;
        for (int i = 0; i < s.size(); ++i) {
            if (backets.find(s[i]) != backets.end()) {
                stack.push(s[i]);
            } else {
                if (stack.empty()) {
                    return false;
                }
                if (backets[stack.top()] != s[i]) {
                    return false;
                }
                stack.pop();
            }
        }
        return stack.empty();
    }
};
