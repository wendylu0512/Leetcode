//
//  mystring.h
//  Leetcode
//
//  Created by Wendi Lu on 10/25/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mystring_h
#define Leetcode_mystring_h

#include <cctype>



bool isPalindrome(string s) {//Valid Palindrome
    auto left = s.begin(), right = prev(s.end());
    while(left < right){
        if(!isalnum(*left)) left++;
        else if(!isalnum(*right)) right--;
        else if(*left == *right || *left + 'A' - 'a' == *right || *left -'A' + 'a' == *right) {left++; right--;}
        else return false;
    }
    return true;
}


char *strStr(char *haystack, char *needle) {//Implement strStr()
    if(!*needle) return haystack;
    char *p1 = needle, *p2 = haystack;
    while(*p2 != '\0'){
        char* start = p2;
        while(*p1 != '\0' && *p2 != '\0'){
            if(*p1 != *p2) {
                break;
            }else{p1++; p2++;}
        }
        if(*p1 != '\0' && *p2 != '\0'){
            p2 = start + 1;
            p1 = needle;
        }else if(*p1 != '\0' && *p2 == '\0'){
            return nullptr;
        }else
            return start;
    }
    return nullptr;
}


int atoi(const char *str) {//String to Integer (atoi)
    int num = 0;
    int sign = 1;
    const int n = (int)strlen(str);
    int i = 0;
    while(i < n && str[i] == ' ') i++;
    if(str[i] == '+') i++;
    else if(str[i] == '-') {sign = -1; i++;}
    for(; i < n; i++){
        if(str[i] < '0' || str[i] > '9')
            break;
        if(num > INT_MAX / 10 || (num == INT_MAX / 10 && str[i] - '0' > INT_MAX % 10))
            return sign == -1? INT_MIN : INT_MAX;
        num = num * 10 + str[i] -'0';
    }
    return sign * num;
}


string addBinary(string a, string b) {//Add Binary
    const int n = (int)max(a.size(), b.size());
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int carry = 0;
    string result;
    for(int i = 0; i < n; i++){
        int ai = i >= a.size()? 0 : a[i] - '0';
        int bi = i >= b.size()? 0 : b[i] - '0';
        if(ai + bi + carry >= 2){
            result.push_back('0' + ai + bi + carry - 2);
            carry = 1;
        }else{
            result.push_back('0' + ai + bi + carry);
            carry = 0;
        }
    }
    if(carry) result.push_back('1');
    reverse(result.begin(), result.end());
    return result;
}


string expandAroundCenter(string s, int c1, int c2);

string longestPalindrome(string s) {//Longest Palindromic Substring
    int n = (int)s.size();
    if (n < 2) return s;
    string longest = s.substr(0, 1);
    for (int i = 0; i < n - 1; i++) {
        string p1 = expandAroundCenter(s, i, i);
        if (p1.length() > longest.length())
            longest = p1;
        
        string p2 = expandAroundCenter(s, i, i + 1);
        if (p2.length() > longest.length())
            longest = p2;
    }
    return longest;
}

string expandAroundCenter(string s, int c1, int c2) {
    int l = c1, r = c2;
    int n = (int)s.size();
    while (l >= 0 and r < n and s[l] == s[r]) {
        l--;
        r++;
    }
    return s.substr(l + 1, r - l - 1);
}


bool isMatch(const char *s, const char *p) {//Regular Expression Matching
    if(!*p) return !*s;
    if(*(p + 1) != '*'){
        if(*p == *s || (*p == '.' && *s))
            return isMatch(s + 1, p + 1);
        else return false;
    }
    else{
        while(*p == *s || (*p == '.' && *s)){
            if(isMatch(s, p + 2))
                return true;
            s++;
        }
        return isMatch(s, p + 2);
    }
}


bool isMatch2(const char *s, const char *p) {//Wildcard Matching
    bool star = false;
    const char *str = s, *ptr = p;
    for(; *str != '\0'; str++, ptr++){
        switch(*ptr){
            case '?':
                break;
            case '*':
                star = true;
                s = str;
                p = ptr;
                while(*p == '*') p++;
                if(*p == '\0') return true;
                str = s - 1;
                ptr = p - 1;
                break;
            default:
                if(*str != *ptr){
                    if(!star) return false;
                    s++;
                    str = s - 1;
                    ptr = p - 1;
                }
        }
    }
    while(*ptr == '*') ptr++;
    return *ptr == '\0';
}


string longestCommonPrefix(vector<string> &strs) {//Longest Common Prefix
    if(strs.empty()) return "";
    for(int i = 0; i < strs[0].size(); ++i){
        for(int j = 1; j < strs.size(); ++j){
            if(strs[j][i] != strs[0][i])
                return strs[0].substr(0, i);
        }
    }
    return strs[0];
}


bool isNumber(const char *s) {// Valid Number
    enum InputType{
        INVALID,        //0
        SPACE,          //1
        SIGN,           //2
        DIGIT,          //3
        DOT,            //4
        EXPONENT,       //5
        NUM_INPUTS      //6
    };
    const int transitionTable[][NUM_INPUTS] = {
        -1, 0, 3, 1, 2, -1,     //next states for state 0: nothing
        -1, 8, -1, 1, 4, 5,     //next states for state 1: only digit or with sign
        -1, -1, -1, 4, -1, -1,  //next states for state 2: only one dot or with sign
        -1, -1, -1, 1, 2, -1,   //next states for state 3: only one sign
        -1, 8, -1, 4, -1, 5,    //next states for state 4: only digit with dot or with sign
        -1, -1, 6, 7, -1, -1,   //next states for state 5: appear an exponent
        -1, -1, -1, 7, -1, -1,  //next states for state 6: sign after exponent
        -1, 8, -1, 7, -1, -1,   //next states for state 7: digit after exponent or with sign
        -1, 8, -1, -1, -1, -1   //next states for state 8: valid number with last space
    };
    int state = 0;
    for(; *s !='\0'; s++){
        InputType inputType = INVALID;
        if(isspace(*s))
            inputType = SPACE;
        else if(*s == '+' || *s == '-')
            inputType = SIGN;
        else if(isdigit(*s))
            inputType = DIGIT;
        else if(*s == '.')
            inputType = DOT;
        else if(*s == 'e' || *s == 'E')
            inputType = EXPONENT;
        state = transitionTable[state][inputType];
        if(state == -1) return false;
    }
    return state == 1 || state == 4 || state == 7 || state == 8;
}


string intToRoman(int num) {// Integer to Roman
    int integer[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string result;
    for(int i = 0; num > 0; i++){
        int count = num / integer[i];
        num %= integer[i];
        for(; count > 0; count--) result += roman[i];
    }
    return result;
}


int romanToInt(string s) {//Roman to Integer
    int result = 0;
    for(int i = 0; i < s.size(); ++i){
        switch(s[i]){
            case 'M':
                result += 1000;
                break;
            case 'D':
                result += 500;
                break;
            case 'C':
                if(s[i + 1] == 'M' || s[i + 1] == 'D')
                    result -= 100;
                else result += 100;
                break;
            case 'L':
                result += 50;
                break;
            case 'X':
                if(s[i + 1] == 'L' || s[i + 1] == 'C')
                    result -= 10;
                else result += 10;
                break;
            case 'V':
                result += 5;
                break;
            case 'I':
                if(s[i + 1] == 'V' || s[i + 1] == 'X')
                    result --;
                else result++;
                break;
            default:
                break;
        }
    }
    return result;
}


string nextCount(string s);

string countAndSay(int n) {//Count and Say
    string result = "1";
    for(int i = 1; i < n; i++)
        result = nextCount(result);
    return result;
}

string nextCount(string s) {
    string result;
    int i = 1;
    char say = s[0];
    int count = 1;
    for(; i < s.size(); ++i){
        if(s[i] == say) count++;
        else{
            result += count + '0';
            result += say;
            say = s[i];
            count = 1;
        }
    }
    result += count + '0';
    result += say;
    return result;
}


vector<string> anagrams(vector<string> &strs) {//Anagrams
    unordered_map<string, vector<string> > group;
    for(int i = 0; i < strs.size(); ++i){
        string key = strs[i];
        sort(key.begin(), key.end());
        group[key].push_back(strs[i]);
    }
    vector<string> result;
    for(auto it = group.begin(); it != group.end(); ++it){
        if(it->second.size() > 1)
            result.insert(result.end(), it->second.begin(), it->second.end());
    }
    return result;
}


string simplifyPath(string path) {//Simplify Path
    vector<string> dirs;
    for(auto i = path.begin(); i != path.end();){
        ++i;
        auto j = find(i, path.end(), '/');
        auto dir = string(i, j);
        if(!dir.empty() && dir != "."){
            if(dir == ".."){
                if(!dirs.empty())
                    dirs.pop_back();
            }else{
                dirs.push_back(dir);
            }
        }
        i = j;
    }
    string result("/");
    for(auto i = dirs.begin(); i != dirs.end(); ++i){
        result += *i;
        result += "/";
    }
    if(result.size() > 1)
        result.pop_back();
    return result;
}


int lengthOfLastWord(const char *s) {//Length of Last Word
    int n = (int)strlen(s);
    bool start = false;
    int count = 0;
    for(int i = n - 1; i >= 0; i--){
        if(*(s + i) == ' '){
            if(!start) continue;
            else break;
        }
        else{
            start = true;
            count++;
        }
    }
    return count;
}


void reverseWords(string &s) {//Reverse Words in a String
    string result = "";
    if(s.size() == 0) return;
    for(int i = 0; i < s.size();){
        if(isspace(s[i++])) continue;
        int start = i - 1;
        while(i < s.size() && !isspace(s[i])) i++;
        if(result.size() > 0) result = ' ' + result;
        result = s.substr(start, i - start) + result;
    }
    s = result;
}


#endif
