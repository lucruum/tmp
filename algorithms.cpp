#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define CYAN(...) "\x1b[1;36m" << __VA_ARGS__ << "\x1b[0m"
#define GREEN(...) "\x1b[1;92m" << __VA_ARGS__ << "\x1b[0m"
#define RED(...) "\x1b[1;91m" << __VA_ARGS__ << "\x1b[0m"
#define WHITE(...) "\x1b[1;37m" << __VA_ARGS__ << "\x1b[0m"
#define YELLOW(...) "\x1b[1;33m" << __VA_ARGS__ << "\x1b[0m"

template <typename T, size_t N>
void show(std::ostream& stream, const std::array<T, N>& a);

template <typename T>
void show(std::ostream& stream, const std::list<T>& l);

template <typename K, typename V>
void show(std::ostream& stream, const std::map<K, V>& m);

template <typename F, typename S>
void show(std::ostream& stream, const std::pair<F, S>& p);

template <typename T>
void show(std::ostream& stream, const std::set<T>& s);

template <typename... Ts>
void show(std::ostream& stream, const std::tuple<Ts...>& t);

template <typename K, typename V>
void show(std::ostream& stream, const std::unordered_map<K, V>& m);

template <typename T>
void show(std::ostream& stream, const std::unordered_set<T>& s);

template <typename T>
void show(std::ostream& stream, const std::vector<T>& v);

void show(std::ostream& stream, const bool b) {
    stream << WHITE(b);
}

void show(std::ostream& stream, const char c) {
    stream << RED("'" << c << "'");
}

void show(std::ostream& stream, const char* s) {
    stream << RED('"' << s << '"');
}

void show(std::ostream& stream, const double d) {
    stream << WHITE(d);
}

void show(std::ostream& stream, const float f) {
    stream << WHITE(f);
}

void show(std::ostream& stream, const int i) {
    stream << WHITE(i);
}

void show(std::ostream& stream, const long long ll) {
    stream << WHITE(ll);
}

void show(std::ostream& stream, const size_t s) {
    stream << WHITE(s);
}

void show(std::ostream& stream, const std::string& s) {
    stream << RED('"' << s << '"');
}

void show(std::ostream& stream, const void* p) {
    stream << WHITE(p);
}

void show(std::ostream& stream, const unsigned u) {
    stream << WHITE(u);
}

// См. https://leetcode.com/problems/add-two-numbers/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    bool operator==(const ListNode& node) const {
        if (val != node.val) {
            return false;
        }

        if (bool(next) != bool(node.next)) {
            return false;
        }

        if (!next) {
            return true;
        }

        return *next == *node.next;
    }
};

ListNode* make_list(const std::vector<int>& vals) {
    if (vals.empty()) {
        return nullptr;
    }

    ListNode* head = new ListNode(vals[0]);
    ListNode* last = head;
    for (int i = 1; i < vals.size(); i++) {
        last->next = new ListNode(vals[i]);
        last = last->next;
    }
    return head;
}

void show(std::ostream& stream, const ListNode& node) {
    show(stream, node.val);

    if (node.next) {
        stream << YELLOW(" :: ");
        show(stream, *node.next);
    }
}

template <typename T, size_t N>
void show(std::ostream& stream, const std::array<T, N>& a) {
    stream << YELLOW("[");

    for (size_t i = 0; i < a.size(); i++) {
        if (i) {
            stream << ", ";
        }
        show(stream, a[i]);
    }

    stream << YELLOW("]");
}

template <typename T>
void show(std::ostream& stream, const std::list<T>& l) {
   stream << YELLOW("[");

    size_t i = 0;
    for (const auto& it: l) {
        if (i++) {
            stream << ", ";
        }
        show(stream, it);
    }

    stream << YELLOW("]");
}

template <typename K, typename V>
void show(std::ostream& stream, const std::map<K, V>& m) {
    stream << YELLOW("{");

    size_t i = 0;
    for (const auto& it: m) {
        if (i++) {
            stream << ", ";
        }
        show(stream, it.first);
        stream << ": ";
        show(stream, it.second);
    }

    stream << YELLOW("}");
}

template <typename F, typename S>
void show(std::ostream& stream, const std::pair<F, S>& p) {
    stream << YELLOW("(");
    show(stream, p.first);
    stream << ", ";
    show(stream, p.second);
    stream << YELLOW(")");
}

template <typename T>
void show(std::ostream& stream, const std::set<T>& s) {
    stream << YELLOW("{");

    size_t i = 0;
    for (const auto& it: s) {
        if (i++) {
            stream << ", ";
        }
        show(stream, it);
    }

    stream << YELLOW("}");
}

template <typename... Ts, size_t... Is>
void show_tuple_impl(std::ostream& stream, const std::tuple<Ts...>& t, std::index_sequence<Is...>) {
    ((stream << (Is == 0? "" : ", "), show(stream, std::get<Is>(t))), ...);
}

template <typename... Ts>
void show(std::ostream& stream, const std::tuple<Ts...>& t) {
    stream << YELLOW("(");
    show_tuple_impl(stream, t, std::index_sequence_for<Ts...>());
    stream << YELLOW(")");
}

template <typename K, typename V>
void show(std::ostream& stream, const std::unordered_map<K, V>& m) {
    stream << YELLOW("{");

    size_t i = 0;
    for (const auto& it: m) {
        if (i++) {
            stream << ", ";
        }
        show(stream, it.first);
        stream << ": ";
        show(stream, it.second);
    }

    stream << YELLOW("}");
}

template <typename T>
void show(std::ostream& stream, const std::unordered_set<T>& s) {
    stream << YELLOW("{");

    size_t i = 0;
    for (const auto& it: s) {
        if (i++) {
            stream << ", ";
        }
        show(stream, it);
    }

    stream << YELLOW("}");
}

template <typename T>
void show(std::ostream& stream, const std::vector<T>& v) {
    stream << YELLOW("[");

    for (size_t i = 0; i < v.size(); i++) {
        if (i) {
            stream << ", ";
        }
        show(stream, v[i]);
    }

    stream << YELLOW("]");
}

#define DBG(...) dbg_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)

template <typename T, typename... Ts>
void dbg_impl2(std::ostream& stream, const T& x, const Ts&... xs) {
    show(stream, x);

    if constexpr (sizeof...(xs)) {
        stream << ", ";
        dbg_impl2(stream, xs...);
    }
}

template <typename... Ts>
void dbg_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const Ts&... xs) {
    stream << WHITE(filename << ":" << line << ": ");
    stream << CYAN(expr << " = ");
    dbg_impl2(stream, xs...);
    stream << "\n";
}

#define TEST TEST_IMPL(__COUNTER__, __COUNTER__)
#define TEST_IMPL(x, y) TEST_IMPL2(x, y)
#define TEST_IMPL2(x, y) TEST_IMPL3(TEST_##x##_BODY, TEST_##y##_CASE)
#define TEST_IMPL3(test_body, test_case)        \
    static void test_body();                    \
    static const TestCase test_case(test_body); \
    static void test_body()

struct TestCase {
    TestCase(void (*body)()) {
        body();
    }
};

#define ASSERT(...) assert_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#define ASSERT_EQ(...) assert_eq_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#define ASSERT_NE(...) assert_ne_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#define ASSERT_LT(...) assert_lt_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#define ASSERT_GT(...) assert_gt_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#define ASSERT_LE(...) assert_le_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#define ASSERT_GT(...) assert_gt_impl(std::cout, __FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)

void assert_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const bool test) {
    if (!test) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT(" << expr << ")") << "\n";

        exit(1);
    }
}

template <typename T>
void assert_eq_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const T& expected) {
    if (!(actual == expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_EQ(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T, typename U>
void assert_eq_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const U& expected) {
    if (!(actual == expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_EQ(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T>
void assert_ne_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const T& expected) {
    if (!(actual != expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_NE(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T, typename U>
void assert_ne_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const U& expected) {
    if (!(actual != expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_NE(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T>
void assert_lt_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const T& expected) {
    if (!(actual < expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_LT(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T, typename U>
void assert_lt_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const U& expected) {
    if (!(actual < expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_LT(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T>
void assert_gt_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const T& expected) {
    if (!(actual > expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_GT(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T, typename U>
void assert_gt_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const U& expected) {
    if (!(actual > expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_GT(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T>
void assert_le_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const T& expected) {
    if (!(actual <= expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_LE(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T, typename U>
void assert_le_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const U& expected) {
    if (!(actual <= expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_LE(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T>
void assert_ge_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const T& expected) {
    if (!(actual >= expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_GE(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

template <typename T, typename U>
void assert_ge_impl(std::ostream& stream, const char* filename, const size_t line, const char* expr, const T& actual, const U& expected) {
    if (!(actual >= expected)) {
        stream << WHITE(filename << ":" << line << ": ");
        stream << RED("assertion failed: ");
        stream << WHITE("ASSERT_GE(" << expr << ")") << "\n";

        stream << WHITE(filename << ":" << line << ": ");
        stream << CYAN("note: ") << "mismatched values ";
        show(stream, actual);
        stream << " and ";
        show(stream, expected);

        exit(1);
    }
}

/// 1. Two Sum (Easy)
/// https://leetcode.com/problems/two-sum/
/// Array, Hash Table
std::vector<int> twoSum(const std::vector<int>& nums, const int target) {
    std::unordered_map<int, int> seen;

    for (int i = 0; i < nums.size(); i++) {
        if (auto found = seen.find(target - nums[i]); found != seen.end()) {
            return {found->second, i};
        }
        seen[nums[i]] = i;
    }

    return {};
}

TEST {
    ASSERT_EQ(twoSum({2, 7, 11, 15}, 9), {0, 1});
    ASSERT_EQ(twoSum({3, 2, 4}, 6), {1, 2});
    ASSERT_EQ(twoSum({3, 3, 6}, 6), {0, 1});
}

/// 2. Add Two Numbers (Medium)
/// https://leetcode.com/problems/add-two-numbers/
/// Linked List, Math, Recursion
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    std::vector<int> l1_digits;
    ListNode* ptr = l1;
    while (ptr) {
        l1_digits.push_back(ptr->val);
        ptr = ptr->next;
    }

    std::vector<int> l2_digits;
    ptr = l2;
    while (ptr) {
        l2_digits.push_back(ptr->val);
        ptr = ptr->next;
    }

    l1_digits.resize(std::max(l1_digits.size(), l2_digits.size()), 0);
    l2_digits.resize(std::max(l1_digits.size(), l2_digits.size()), 0);

    ListNode* head = new ListNode((l1_digits[0] + l2_digits[0]) % 10);
    ListNode* last = head;
    bool overflow = (l1_digits[0] + l2_digits[0]) > 9;
    for (int i = 1; i < l1_digits.size(); i++) {
        last->next = new ListNode(l1_digits[i] + l2_digits[i] + overflow);
        overflow = false;

        if (last->next->val > 9) {
            last->next->val -= 10;
            overflow = true;
        }

        last = last->next;
    }
    if (overflow) {
        last->next = new ListNode(1);
    }

    return head;
}

TEST {
    ASSERT_EQ(*addTwoNumbers(make_list({2, 4, 3}), make_list({5, 6, 4})), *make_list({7, 0, 8}));
    ASSERT_EQ(*addTwoNumbers(make_list({0}), make_list({0})), *make_list({0}));
    ASSERT_EQ(*addTwoNumbers(make_list({9, 9, 9, 9, 9, 9, 9}), make_list({9, 9, 9, 9})), *make_list({8, 9, 9, 9, 0, 0, 0, 1}));
    ASSERT_EQ(*addTwoNumbers(make_list({2, 4, 9}), make_list({5, 6, 4, 9})), *make_list({7, 0, 4, 0, 1}));
}

/// 3. Longest Substring Without Repeating Characters (Medium)
/// https://leetcode.com/problems/longest-substring-without-repeating-characters/
/// Hash Table, String, Sliding Window
int lengthOfLongestSubstring(const std::string s) {
    std::unordered_set<char> seen;
    int length = 0;

    int first = 0, last = 0;
    while (last < s.size()) {
        if (auto found = seen.find(s[last]); found == seen.end()) {
            seen.insert(s[last]);
            last++;
        } else {
            length = std::max(length, last - first);

            while (first <= last) {
                seen.erase(seen.find(s[first]));
                first++;

                if (s[first - 1] == s[last]) {
                    break;
                }
            }
        }
    }
    length = std::max(length, last - first);

    return length;
}

TEST {
    ASSERT_EQ(lengthOfLongestSubstring("abcabcbb"), 3);
    ASSERT_EQ(lengthOfLongestSubstring("bbbbb"), 1);
    ASSERT_EQ(lengthOfLongestSubstring("pwwkew"), 3);
    ASSERT_EQ(lengthOfLongestSubstring(" "), 1);
    ASSERT_EQ(lengthOfLongestSubstring("abba"), 2);
    ASSERT_EQ(lengthOfLongestSubstring("tmmzuxt"), 5);
}

/// 4. Median of Two Sorted Arrays (Hard)
/// https://leetcode.com/problems/median-of-two-sorted-arrays/
/// Array, Binary Search, Divide and Conquer
double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    std::vector<int> merged;
    int ptr1 = 0, ptr2 = 0;
    while (ptr1 < nums1.size() || ptr2 < nums2.size()) {
        if (ptr2 >= nums2.size()) {
            merged.push_back(nums1[ptr1++]);
        } else if (ptr1 >= nums1.size()) {
            merged.push_back(nums2[ptr2++]);
        } else {
            if (nums1[ptr1] < nums2[ptr2]) {
                merged.push_back(nums1[ptr1++]);
            } else {
                merged.push_back(nums2[ptr2++]);
            }
        }
    }

    if (merged.size() % 2 == 0) {
        return (merged[merged.size() / 2 - 1] + merged[merged.size() / 2]) / 2.0;
    }
    return merged[merged.size() / 2];
}

TEST {
    ASSERT_EQ(findMedianSortedArrays({1, 3}, {2}), 2.0);
    ASSERT_EQ(findMedianSortedArrays({1, 2}, {3, 4}), 2.5);
}

/// 5. Longest Palindromic Substring (Medium)
/// https://leetcode.com/problems/longest-palindromic-substring/
/// String, Dynamic Programming
std::string longestPalindrome(const std::string& s) {
    std::string result;

    for (int i = 0; i < int(s.size()) - 1; i++) {
        if (s[i] == s[i + 1]) {
            for (int left = i, right = i + 1; left >= 0 && right < s.size() && s[left] == s[right]; left--, right++) {
                if (right - left + 1 > result.size()) {
                    result = s.substr(left, right - left + 1);
                }
            }
        }
        if (i < int(s.size()) - 2 && s[i] == s[i + 2]) {
            for (int left = i, right = i + 2; left >= 0 && right < s.size() && s[left] == s[right]; left--, right++) {
                if (right - left + 1 > result.size()) {
                    result = s.substr(left, right - left + 1);
                }
            }
        }
    }

    if (result.empty()) {
        return std::string(1, s[0]);
    }
    return result;
}

TEST {
    ASSERT_EQ(longestPalindrome("babad"), "bab");
    ASSERT_EQ(longestPalindrome("cbbd"), "bb");
    ASSERT_EQ(longestPalindrome("a"), "a");
}

/// 7. Reverse Integer (Medium)
/// https://leetcode.com/problems/reverse-integer/
/// Math
int reverse(double x) {
    if (x == 0) {
        return 0;
    }

    const bool positive = x > 0;
    x = std::abs(x);

    double result = 0;
    int length = std::floor(std::log10(x)) + 1;
    while (x) {
        result += std::fmod(x, 10.0) * std::pow(10.0, length-- - 1);
        x = std::trunc(x / 10.0);
    }

    if (result > std::numeric_limits<int>::max()) {
        return 0;
    }
    return positive ? result : -result;
}

TEST {
    ASSERT_EQ(reverse(123), 321);
    ASSERT_EQ(reverse(-123), -321);
    ASSERT_EQ(reverse(120), 21);
    ASSERT_EQ(reverse(1), 1);
    ASSERT_EQ(reverse(10), 1);
}

/// 8. String to Integer (atoi) (Medium)
/// https://leetcode.com/problems/string-to-integer-atoi/
/// String
int myAtoi(const std::string& s) {
    int first = 0;
    while (std::isspace(s[first])) {
        first++;
    }

    bool negative = false;
    if (s[first] == '-') {
        negative = true;
        first++;
    } else if (s[first] == '+') {
        first++;
    }
    
    int last = std::find_if_not(s.begin() + first, s.end(), [](const char x) {
        return std::isdigit(x);
    }) - s.begin();

    unsigned result = 0;
    for (int i = first; i < last; i++) {
        if (((result * 10 + s[i] - '0') - (s[i] - '0')) / 10 != result) {
            return negative? INT_MIN : INT_MAX;
        }
        result = result * 10 + s[i] - '0';
    }
    if (result > INT_MAX) {
        return negative? INT_MIN : INT_MAX;
    }
    return negative? -result : result;
}

TEST {
    ASSERT_EQ(myAtoi("42"), 42);
    ASSERT_EQ(myAtoi("   -42"), -42);
    ASSERT_EQ(myAtoi("4193 with words"), 4193);
    ASSERT_EQ(myAtoi("-91283472332"), -2147483648);
    ASSERT_EQ(myAtoi("+1"), 1);
    ASSERT_EQ(myAtoi("20000000000000000000"), 2147483647);
    ASSERT_EQ(myAtoi("21474836460"), 2147483647);
    ASSERT_EQ(myAtoi("-6147483648"), -2147483648);
}

/// 9. Palindrome Number (Easy)
/// https://leetcode.com/problems/palindrome-number/
/// Math
bool isPalindrome(const int x) {
    if (x < 0) {
        return false;
    }

    std::string s = std::to_string(x);
    for (int i = 0; i < s.size() / 2; i++) {
        if (s[i] != s[s.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

TEST {
    ASSERT(isPalindrome(121));
    ASSERT(!isPalindrome(-121));
    ASSERT(!isPalindrome(10));
}

/// 10. Regular Expression Matching (Hard)
/// https://leetcode.com/problems/regular-expression-matching/
/// String, Dynamic Programming, Recursion
bool isMatch(const std::string& s, const std::string& p) {
    return {};
}

TEST {
    ASSERT(!isMatch("aa", "a"));
    ASSERT(isMatch("aa", "a*"));
    ASSERT(isMatch("aa", "a*"));
    ASSERT(isMatch("ab", ".*"));
    ASSERT(isMatch("aab", "a*b"));
    ASSERT(isMatch("aab", "c*a*b"));
    ASSERT(!isMatch("ab", ".*c"));
    ASSERT(isMatch("aaa", "a*a"));
}

int main() {
    std::cout << GREEN("done");
    return 0;
}