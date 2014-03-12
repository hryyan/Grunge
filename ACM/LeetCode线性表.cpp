// Remove Duplicates from Sorted Array
class Solution
{
public:
    int removeDuplicates(int A[], int n)
    {
        if (n == 0) return 0;

        int index = 0;
        for (int i = 0; i < n; )
        {
            if (A[index] != A[i])
                A[++index] = A[i];
        }
        return index + 1;
    }
};

// Remove Duplicates from Sorted Array, 使用STL
class Solution
{
public:
    int removeDuplicates(int A[], int n)
    {
        return removeDuplicates(A, A+n, A) - A;
    }

    template<typename Init, typename OutIt>
    OutIt removeDuplicates(Init first, Init last, OutIt output)
    {
        while (first != last)
        {
            *output++ = *first;
            first = find_if(first, last, bind1st(not_equal_to<int>(), *first));
        }
        return output;
    }
};

// Remove Duplicates from Sorted Array
class Solution
{
public:
    int removeDuplicates(int A[], int n)
    {
        if (n == 0) return 0;

        int occur = 1;
        int index = 0;
        for (int i = 1; i < n; i++)
        {
            if (A[index] == A[i])
            {
                if (occur < 2)
                {
                    A[++index] = A[i];
                    occur++;
                }
            }
            else
            {
                A[++index] = A[i];
                occur = 1;
            }
        }
        return index + 1;
    }
};

// Search in Rotated Sorted Array
class Solution
{
public:
    int search(int A[], int n, int target)
    {
        int first = 0, last = n;
        while (first != last)
        {
            const int mid = (first + last) / 2;
            if (A[mid] == target)
                return mid;
            if (A[first] <= A[mid])
            {
                if (A[first] <= target && target < A[mid])
                    last = mid;
                else
                    first = mid + 1;
            }
            else
            {
                if (A[mid] < target && target <= A[last-1])
                    first = mid + 1;
                else 
                    last = mid;
            }
        }
        return -1;
    }
};

// Search in Rotated Sorted Array II
class Solution
{
public:
    bool search(int A[], int n, int target)
    {
        int first = 0, last = n;
        while (first != last)
        {
            const int mid = (first + last) / 2;
            if (A[mid] == target)
                return true;
            if (A[first] < A[mid])
            {
                if (A[first] < A[mid])
                {
                    if (A[first] <= target && target < A[mid])
                        last = mid;
                    else 
                        first = mid + 1;
                }
                else if (A[first] > A[mid])
                {
                    if (A[mid] <= target && target <= A[last-1])
                        first = mid + 1;
                    else
                        last = mid;
                }
                else
                    // skip duplicate one, A[start] == A[mid]
                    first++;
            }
        }
        return false;
    }
};

// Median of Two Sorted Arrays
class Solution
{
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n)
    {
        int total = m + n;
        if (total & 0x1)    //偶数
            return find_kth(A, m, B, n, total / 2 + 1)
        else                //奇数
            return (find_kth(A, m, B, n, total / 2)
                + find_kth(A, m, B, n, total / 2 + 1)) / 2;
    }
private:
    static double find_kth(int A[], int m, int B[], int n, int k)
    {
        //always assume that m is equal or smaller than n
        if (m > n) return find_kth(B, n, A, m, k);
        if (m == 0) return B[k - 1];
        if (k == 1) return min(A[0], B[0]);

        //divide k into two parts
        int pa = min(k / 2, m), pb = k - pa;
        if (A[pa - 1] < B[pb - 1])
            return find_kth(A + pa, m - pa, B, n, k - pa);
        else if (A[pa - 1] > B[pb - 1])
            return find_kth(A, m, B + pb, n - pb, k - pb);
        else
            return A[pa - 1];
    }
};

// Longest Consecutive Sequence
class Solution
{
public:
    int longestConsecutive(vector<int> const& num)
    {
        unordered_map<int, bool> used;
        for (auto i : num) used[i] = false;

        int longest = 1;

        used[i] = true;

        for (auto i : num)
        {
            if (used[i]) continue;

            int length = 1;

            used[i] = true;

            for (int j = i + 1; used.find(j) != used.end(); ++j)
            {
                used[j] = true;
                ++length;
            }

            for (int j = i - 1; used.find(j) != used.end(); --j)
            {
                used[j] = true;
                ++length;
            }

            longest = max(longest, length);
        }
        return longest;
    }
};

// 3Sum
// 先排序，然后二分查找
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &num)
    {
        vector<vector<int>> result;
        if (num.size() < 3) return result;
        sort(num.begin(), num.end());
        const int target = 0;
        
        auto last = num.end();
        for (auto a = num.begin(); a < prev(last, 2); a = upper_bound(a, prev(last, 2), *a))
        {
            for (auto b = next(a); b < prev(last); b = upper_bound(b, prev(last), *b))
            {
                const int c = target - *a - *b;
                if (binary_search(next(b), last, c))
                    result.push_back(vector<int> {*a, *b, c});
            }
        }
        return result;
    }
};

// 3Sum Closest
// 先排序，然后左右夹逼
class Solution
{
public:
    int threeSumClosest(vector<int> &num, int target)
    {
        int result;
        int min_gap = int_MAX;

        sort(num.begin(), num.end());

        for (auto a = num.begin(); a != prev(num.end(), 2); a = upper_bound(a, prev(num.end(), 2), *a))
        {
            auto b = next(a);
            auto c = prev(num.end());

            while (b < c)
            {
                const int sum = *a + *b + *c;
                const int gap = abs(sum - target);

                if (gap < min_gap)
                {
                    min_gap = gap;
                    result = sum;
                }

                if (sum < target)
                    b = upper_bound(b, c, *b);
                else
                    c = prev(lower_bound(b, c, *c))
            }
        }
        return result;
    }
};

// 4Sum
// 先排序，然后二分查找，复杂度O(n^3*logn)
class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &num)
    {
        vector<vector<int>> result;
        if (num.size() < 4) return result;
        sort(num.begin(), num.end());
        const int target = 0;

        for (auto a = num.begin(); a < prev(num.end(), 3); a = upper_bound(a, prev(num.end(), 3), *a))
        {
            for (auto b = next(a); b < prev(num.end(), 2); b = upper_bound(b, prev(num.end(), 2), *b))
            {
                for (auto c = next(b); c < prev(num.end(), 1); c = upper_bound(c, prev(num.end(), 1), *c))
                {
                    const int d = target - *a - *b - *c;
                    if (binary_search(next(c), num.end(), d))
                        result.push_back(vector<int> {*a, *b, *c, d});
                }
            }
        }
        return result;
    }
};

// 4Sum
// 先缓冲两个数的和，复杂度O(n^3)
class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &num, int target)
    {
        if (num.size() < 4) return vector<vector<int>>();
        sort(num.begin(), num.end());

        map<int, vector<pair<int, int>>> cache;
        for (size_t a = 0; a < num.size(); ++a)
            for (size_t b = a + 1; b < num.size(); ++b)
                cache[num[a] + num[b]].push_back(pair<int, int>(a, b));

        set<vector<int>> result;
        for (size_t c = 2; c < num.size(); ++c)
            for (size_t d = c + 1; d < num.size(); ++d)
            {
                const int key = target - num[c] - num[d];
                if (cache.find(key) != cache.end())
                {
                    for (size_t k = 0; k < cache[key].size(); ++k)
                    {
                        if (c <= cache[key][k].second) continue;
                        result.insert(vector<int> {num[cache[key][k].first], num[cache[key][k].second], num[c], num[d] });
                    }
                }
            }
        return vector<vector<int>> (result.begin(), result.end());
    }
};

// 2.1.10 Remove Element
class Solution
{
public:
    int removeElement(int A[], int n, int elem)
    {
        int index = 0;
        for (int i = 0; i < n; ++i)
        {
            if (A[i] != elem)
                A[index++] = A[i];
        }
        return index;
    }
};

// 8.3.1 Permutations

vector<vector<int>> permute(vector<int> &num)
{
    vector<vector<int>> result;
    sort(num.begin(), num.end());

    do{
        result.push_back(num);
    }while(next_permutation(num.begin(), num.end()));
    return result;
}

// 2.1.11 next_permutation

void nextPermutation(vector<int> &num)
{
    next_permutation(num.begin(), num.end());
}

template<typename BidiIt>
bool next_permutation(BidiIt first, BidiIt last)
{
    // Get a reversed range to simplify reversed traversal
    const auto rfirst = reverse_iterator<BidiIt>(last);
    const auto rlast  = reverse_iterator<BidiIt>(first);

    // Begin from the second last element to the first element
    auto pivot = next(rfirst);

    // Find `pivot`, which is the first element that is not less than its
    // successor. `Prev` is used since `pivot` is a `reversed_iterator`.
    while (pivor != rlast and !(*pivot < *prev(pivot)))
        ++pivot;

    // No such element found, 
}