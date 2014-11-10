//
//  mydetail.h
//  Leetcode
//
//  Created by Wendi Lu on 11/3/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mydetail_h
#define Leetcode_mydetail_h

#include <sstream>
#include <iomanip>

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};



int reverse(int x) {//Reverse Integer
    int r = 0;
    for(; x; x /= 10)
        r = r * 10 + x % 10;
    return r;
}


bool isPalindrome(int x) {//Palindrome Number
    if(x < 0) return false;
    int d = 1;
    while(x / d >= 10) d *= 10;
    while(x > 0){
        int q = x / d;
        int r = x % 10;
        if(q != r) return false;
        x = x % d / 10;
        d /= 100;;
    }
    return true;
}


vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {//Insert Interval
    vector<Interval> result;
    for(int i = 0; i < intervals.size(); i++){
        if(newInterval.start > intervals[i].end){
            result.push_back(intervals[i]);
        }else if(newInterval.end < intervals[i].start){
            result.push_back(newInterval);
            newInterval = intervals[i];
        }else{
            newInterval.start = min(newInterval.start, intervals[i].start);
            newInterval.end = max(newInterval.end, intervals[i].end);
        }
    }
    result.push_back(newInterval);
    return result;
}


vector<Interval> merge(vector<Interval> &intervals) {//Merge Intervals
    vector<Interval> result;
    for(int i = 0; i < intervals.size(); i++){
        result = insert(result, intervals[i]);
    }
    return result;
}


string minWindow(string S, string T) {//Minimum Window Substring
    if(S.empty() || S.size() < T.size()) return "";
    int appeared[256];
    int expected[256];
    fill(appeared, appeared + 256, 0);
    fill(expected, expected + 256, 0);
    for(int i = 0; i < T.size(); i++) expected[T[i]]++;
    int minWidth = INT_MAX, min_start = 0;
    int start = 0, appear = 0;
    for(int end = 0; end < S.size(); end++){
        appeared[S[end]]++;
        if(expected[S[end]] > 0 && appeared[S[end]] <= expected[S[end]]){
            appear++;
        }
        if(appear == T.size()){
            while(appeared[S[start]] > expected[S[start]]){
                appeared[S[start]]--;
                start++;
            }
            if(minWidth > end -start + 1){
                minWidth = end - start + 1;
                min_start = start;
            }
        }
    }
    if(minWidth == INT_MAX) return "";
    else return S.substr(min_start, minWidth);
}


class BigInt{
public:
    BigInt(string s){
        vector<int64_t> result;
        result.reserve(s.size() / 9 + 1);
        for(int i = (int)s.size(); i > 0; i -= 9){
            int temp = 0;
            const int low = max(i - 9, 0);
            for(int j = low; j < i; j++)
                temp = temp * 10 + s[j] - '0';
            result.push_back(temp);
        }
        elems = result;
    }
    
    string toString(){
        stringstream result;
        bool started = false;
        for(auto i = elems.rbegin(); i != elems.rend(); ++i){
            if(started){
                result << setw(9) << setfill('0') << *i;
            }else{
                result << *i;
                started = true;
            }
        }
        if(!started) return "0";
        else return result.str();
    }
    
    static BigInt multiply(const BigInt &x, const BigInt &y){
        vector<int64_t> z(x.elems.size() + y.elems.size(), 0);
        for(int i = 0; i < y.elems.size(); i++){
            for(int j = 0; j < x.elems.size(); j++){
                z[i + j] += y.elems[i] * x.elems[j];
                if(z[i + j] >= 1000000000){
                    z[i + j + 1] += z[i + j] / 1000000000;
                    z[i + j] %= 1000000000;
                }
            }
        }
        while(z.back() == 0) z.pop_back();
        return BigInt(z);
    }
    
private:
    typedef long long int64_t;
    vector<int64_t> elems;
    BigInt(vector<int64_t> num) : elems(num) {}
};

string multipy(string num1, string num2){//Multiply Strings
    BigInt x(num1);
    BigInt y(num2);
    return BigInt :: multiply(x, y).toString();
}


vector<int> findSubstring(string S, vector<string> &L) {//Substring with Concatenation of All Words
    size_t wordLength = L[0].size();
    size_t catLength = wordLength * L.size();
    vector<int> result;
    if(S.size() < catLength) return result;
    unordered_map<string, int> wordCount;
    for(const auto &word : L) wordCount[word]++;
    for(auto i = S.begin(); i <= prev(S.end(), catLength); i++){
        unordered_map<string, int> unused(wordCount);
        for(auto j = i; j < next(i, catLength); j += wordLength){
            auto pos = unused.find(string(j, next(j, wordLength)));
            if(pos == unused.end()) break;
            pos->second--;
            if(pos->second == 0) unused.erase(pos);
        }
        if(unused.size() == 0) result.push_back((int)distance(begin(S), i));
    }
    return result;
}


vector<vector<int> > generate(int numRows) {//Pascal's Triangle
    vector<vector<int> > result;
    if(numRows == 0) return result;
    result.push_back(vector<int>(1, 1));
    for(int i = 2; i <= numRows; i++){
        vector<int> current(i ,1);
        for(int j = 1; j < i - 1; j++)
            current[j] = result[i - 2][j - 1] + result[i - 2][j];
        result.push_back(current);
    }
    return result;
}


vector<int> getRow(int rowIndex) {//Pascal's Triangle II
    vector<int> result;
    for(int i = 0; i <= rowIndex; i++){
        for(int j = i - 1; j > 0; j--)
            result[j] = result[j] + result[j - 1];
        result.push_back(1);
    }
    return result;
}


vector<int> spiralOrder(vector<vector<int> > &matrix) {//Spiral Matrix
    vector<int> result;
    if(matrix.empty()) return result;
    int endY = (int)matrix.size() - 1, beginY = 0;
    int endX = (int)matrix[0].size() - 1, beginX = 0;
    while(1){
        for(int j = beginX; j <= endX; j++)
            result.push_back(matrix[beginY][j]);
        if(++beginY > endY) break;
        for(int i = beginY; i <= endY; i++)
            result.push_back(matrix[i][endX]);
        if(--endX < beginX) break;
        for(int j = endX; j >= beginX; j--)
            result.push_back(matrix[endY][j]);
        if(--endY < beginY) break;
        for(int i = endY; i >= beginY; i--)
            result.push_back(matrix[i][beginX]);
        if(++beginX > endX) break;
    }
    return result;
}


vector<vector<int> > generateMatrix(int n) {//Spiral Matrix II
    vector<vector<int> > result(n, vector<int>(n, 0));
    if(n == 0) return result;
    int endY = n - 1, beginY = 0;
    int endX = n - 1, beginX = 0;
    int num = 1;
    while(1){
        for(int j = beginX; j <= endX; j++)
            result[beginY][j] = num++;
        if(++beginY > endY) break;
        for(int i = beginY; i <= endY; i++)
            result[i][endX] = num++;
        if(--endX < beginX) break;
        for(int j = endX; j >= beginX; j--)
            result[endY][j] = num++;
        if(--endY < beginY) break;
        for(int i = endY; i >= beginY; i--)
            result[i][beginX] = num++;
        if(++beginX > endX) break;
    }
    return result;
}


string convert(string s, int nRows) {//ZigZag Conversion
    if(nRows < 2 || s.size() < 2) return s;
    string result;
    for(int i = 0; i < nRows; i++){
        for(int j = 0, index = i; index < s.size(); j++, index = (2 * nRows - 2) * j + i){
            result.append(1, s[index]);
            if(i == 0 || i == nRows - 1) continue;
            if(index + (nRows - i - 1) * 2 < s.size())
                result.append(1, s[index + (nRows - i - 1) * 2]);
        }
    }
    return result;
}

int divide(int dividend, int divisor) {//Divide Two Integers
    long long a = dividend >= 0 ? dividend : -(long long)dividend;
    long long b = divisor >= 0 ? divisor : -(long long)divisor;
    long long result = 0;
    while(a >= b){
        long long c = b;
        for(int i = 0; a >= c; i++, c <<= 1){
            a -= c;
            result += 1 << i;
        }
    }
    return ((dividend ^ divisor) >> 31) ? (int)(-result) : (int)result;
}


string connect(vector<string> &words, int begin, int end, int len, int L, bool isLast);

void addSpace(string &s, int i, int n, int L, bool isLast);

vector<string> fullJustify(vector<string> &words, int L) {//Text Justification
    vector<string> result;
    const int n = (int)words.size();
    int begin = 0, len = 0;
    for(int i = 0; i < n; i++){
        if(len + words[i].size() + (i - begin) > L){
            result.push_back(connect(words, begin, i - 1, len, L, false));
            begin = i;
            len = 0;
        }
        len += words[i].size();
    }
    result.push_back(connect(words, begin, n - 1, len, L, true));
    return result;
}

string connect(vector<string> &words, int begin, int end, int len, int L, bool isLast){
    string s;
    int n = end - begin + 1;
    for(int i = 0; i < n; i++){
        s += words[begin + i];
        addSpace(s, i, n - 1, L -len, isLast);
    }
    if(s.size() < L) s.append(L - s.size(), ' ');
    return s;
}

void addSpace(string &s, int i, int n, int L, bool isLast){
    if(n < 1 || i > n - 1) return;
    int spaces = isLast ? 1 : (L / n + (i < L % n ? 1 : 0));
    s.append(spaces, ' ');
}


int maxPoints(vector<Point> &points) {//Max Points on a Line
    if(points.size() < 3) return (int)points.size();
    int result = 0;
    unordered_map<double, int> slopeCount;
    for(int i = 0; i < points.size() - 1; i++){
        slopeCount.clear();
        int samePointNum = 0;
        int pointMax = 1;
        for(int j = i + 1; j < points.size(); j++){
            double slope;
            if(points[i].x == points[j].x){
                slope = INFINITY;
                if(points[i].y == points[j].y){
                    samePointNum++;
                    continue;
                }
            }else{
                slope = 1.0 * (points[j].y - points[i].y) / (points[j].x - points[i].x);
            }
            int count = 0;
            if(slopeCount.find(slope) != slopeCount.end()){
                count = ++slopeCount[slope];
            }else{
                count = 2;
                slopeCount[slope] = 2;
            }
            pointMax = max(pointMax, count);
        }
        result = max(result, pointMax + samePointNum);
    }
    return result;
}

#endif