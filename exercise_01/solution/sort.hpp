#pragma once

#include "pair.hpp"
#include "vector.hpp"
#include <cstring>


void CountingSort(TVector<TPair>& elems) {
    uint32_t max = 0;
    for (size_t i = 0; i < elems.Size(); ++i) {
        max = std::max(max, elems[i].key);
    }
    
    TVector<uint32_t> counters(max + 1, 0);
    for (size_t i = 0; i < elems.Size(); ++i) {
        ++counters[elems[i].key];
    }
    
    for (size_t i = 1; i < counters.Size(); ++i) {
        counters[i] += counters[i - 1];
    }
   
    TVector<TPair> result(elems.Size());
    for (int i = elems.Size() - 1; i >= 0; --i) {
        result[counters[elems[i].key] - 1].key = elems[i].key;
        memcpy(result[counters[elems[i].key] - 1].value, elems[i].value, sizeof(elems[i].value));
        --counters[elems[i].key];
    }

    elems = result;
}