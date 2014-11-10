//
//  mybisplit.h
//  Leetcode
//
//  Created by Wendi Lu on 11/1/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_mybisplit_h
#define Leetcode_mybisplit_h


double power(double x, int n);

double pow(double x, int n) {//Pow(x, n)
    if(n < 0) return 1.0 / power(x, -n);
    return power(x, n);
}

double power(double x, int n){
    if(n == 0) return 1.0;
    if(n == 1) return x;
    double v = pow(x, n / 2);
    return n & 1 ? v * v * x : v * v;
}


int sqrt(int x) {//Sqrt(x)
    if(x < 2) return x;
    int first = 0;
    int last = x;
    while(first + 1 < last){
        int mid = (first + last) / 2;
        if(mid == x / mid)
            return mid;
        else if(mid > x / mid)
            last = mid;
        else first = mid;
    }
    return first;
}

#endif
