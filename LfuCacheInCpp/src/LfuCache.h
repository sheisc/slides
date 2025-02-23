#ifndef LFU_CACHE_H
#define LFU_CACHE_H
#include <list>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <cassert>

template <class KeyTy, class ValueTy>
class LfuCache {   
    
    struct ValueInfo {
        ValueTy value;
        long freq;
        ValueInfo(ValueTy value, long freq): value(value), freq(freq) {
            //std::cout << this << ": ValueInfo(" << value << ", " << freq << ")" << std::endl;
        }
        ~ValueInfo() {
            //std::cout << this << ": \t\t~ValueInfo(" << value << ", " << freq << ")" << std::endl;
        }
    };

    // capacity of the Lfu Cache
    size_t capacity;    
    // the current minimum frequency     
    long minFreq;          

    // key -> ValueInfo *
    std::unordered_map<KeyTy, std::shared_ptr<ValueInfo>> key2ValueInfoMap;
    // key -> list<KeyTy>::iterator
    std::unordered_map<KeyTy, typename std::list<KeyTy>::iterator> key2PosInList;
    // frequency -> list<KeyTy>
    std::unordered_map<long, std::list<KeyTy>> freq2KeyList;

    // no copy constructor
    LfuCache(const LfuCache &) = delete;
    // no assignment operator
    LfuCache & operator= (const LfuCache &) = delete;

    /*
        Update the access frequency info.
     */
    void UpdateAccessFrequency(KeyTy key, std::shared_ptr<ValueInfo> &valInfo) {
        long oldFreq = valInfo->freq;
        long newFreq = oldFreq + 1;
        valInfo->freq = newFreq;
        // remove it from listWithSameFreq
        freq2KeyList[oldFreq].erase(key2PosInList[key]);
        if (freq2KeyList[oldFreq].size() == 0) {
            freq2KeyList.erase(oldFreq);
            minFreq = newFreq;
        }
        // Test whether there is a key list with the frequency newFreq 
        if (freq2KeyList.count(newFreq) != 0) {
            freq2KeyList[newFreq].push_front(key);
        } else {
            freq2KeyList[newFreq] = {key};        
        }
        key2PosInList[key] = freq2KeyList[newFreq].begin();
    }

public:
    /*
        If @key exits
            update its value
            update its access frequency via Get()
        else
            if it is full, remove least frequently used item
            add a new key with the frequency 1
     */
    void Put(KeyTy key, ValueTy value) {
        auto it = key2ValueInfoMap.find(key);
        if (it != key2ValueInfoMap.end()) {
            // update the value
            it->second->value = value;
            // access frequency is updated in Get()        
            UpdateAccessFrequency(key, it->second);
            return;
        }
        // if it is full
        if (capacity == key2ValueInfoMap.size()) {
            KeyTy deletedKey = freq2KeyList[minFreq].back();
            key2ValueInfoMap.erase(deletedKey);
            key2PosInList.erase(deletedKey);
            freq2KeyList[minFreq].pop_back();
        }
        // add a new node
        minFreq = 1;
        key2ValueInfoMap[key] = std::shared_ptr<ValueInfo>(new ValueInfo(value, 1));
        if (freq2KeyList.count(minFreq) == 0) {
            freq2KeyList[minFreq] = {key};        
        } else {
            freq2KeyList[minFreq].push_front(key);
        }
        key2PosInList[key] = freq2KeyList[minFreq].begin();   
    }
    
    /*
        If found
            update the access frequency.
            @value contains the found value.
            return true
        else
            return false
     */
    bool Get(KeyTy key, ValueTy &value) {
        auto it = key2ValueInfoMap.find(key);
        if (it == key2ValueInfoMap.end()) {
            return false;
        }  
        value = it->second->value;
        UpdateAccessFrequency(key, it->second);
        return true;
    }

    LfuCache(size_t capacity): capacity(capacity), minFreq(0) {
        assert(capacity > 0);
    }

    virtual ~LfuCache() {
        //std::cout << this << ": \t\t~LfuCache()" << std::endl;
    }

    /*
        Output the LfuCache.
     */
    void Print(std::ostream &os, const std::string &info, KeyTy key) {
        std::vector<long> freqs;
        for (auto &item: freq2KeyList) {
            freqs.push_back(item.first);
        }
        std::sort(freqs.begin(), freqs.end());
        os << "\n" << info << "(" << key << "): ";
        os << "******************* capacity = " << capacity << ", size = " 
           << key2ValueInfoMap.size() << " *******************\n";
        for (long freq: freqs) {
            os << "\t\t........ freq = " << freq << "........\n\t\t";
            for (KeyTy key: freq2KeyList[freq]) {
                std::shared_ptr<ValueInfo> &sp = key2ValueInfoMap[key];
                os << "(" << key << ", " << sp->value << ")" << " ";
            }
            os << "\n";
        }
    }
};
#endif

