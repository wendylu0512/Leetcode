//
//  LRU Cache.h
//  Leetcode
//
//  Created by Wendi Lu on 10/23/14.
//  Copyright (c) 2014 Wendi Lu. All rights reserved.
//

#ifndef Leetcode_LRU_Cache_h
#define Leetcode_LRU_Cache_h

#include <list>


class LRUCache{
private:
    struct CacheNode{
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v){};
    };
    list<CacheNode> CacheList;
    unordered_map<int, list<CacheNode> ::iterator> CacheMap;
    int capacity;
public:
    
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(CacheMap.find(key) == CacheMap.end()) return -1;
        CacheList.splice(CacheList.begin(), CacheList, CacheMap[key]);
        CacheMap[key] = CacheList.begin();
        return CacheMap[key]->value;
    }
    
    void set(int key, int value) {
        if(CacheMap.find(key) != CacheMap.end()){
            CacheList.splice(CacheList.begin(), CacheList, CacheMap[key]);
            CacheMap[key] = CacheList.begin();
            CacheMap[key]->value = value;
        }else{
            if(CacheList.size() == capacity){
                CacheMap.erase(CacheList.back().key);
                CacheList.pop_back();
            }
            CacheList.push_front(CacheNode(key, value));
            CacheMap[key] = CacheList.begin();
        }
    }
};


#endif
