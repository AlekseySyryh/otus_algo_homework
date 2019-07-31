#pragma once

#include <future>
#include <list>

void merge(std::vector<int> &data, std::vector<int> &copy, int begin, int mid, int end) {
    int first = begin;
    int second = mid;
    for (int ptr = begin; ptr < end; ++ptr) {
        if (first < mid && (second == end || data[first] < data[second])) {
            copy[ptr] = data[first];
            ++first;
        } else {
            copy[ptr] = data[second];
            ++second;
        }
    }
}

void splitClassic(std::vector<int> &data, std::vector<int> &copy, int begin, int end) {
    if (end - begin < 2)
        return;
    auto mid = (end + begin) / 2;
    splitClassic(copy, data, begin, mid);
    splitClassic(copy, data, mid, end);
    merge(copy, data, begin, mid, end);
}

void mergeSortClassic(std::vector<int> &data) {
    std::vector<int> copy(data);
    splitClassic(data, copy, 0, data.size());
}

void insertSort(std::vector<int> &data, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        auto x = data.at(i);
        int j = i - 1;
        while (j >= begin && data.at(j) > x) {
            data.at(j + 1) = data.at(j);
            --j;
        }
        data.at(j + 1) = x;
    }
}

void insertSort(std::vector<int> &data, std::vector<int> &copy, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        auto x = data[i];
        int j = i - 1;
        while (j >= begin && data[j] > x) {
            data[j + 1] = data[j];
            copy[j + 1] = data[j];
            --j;
        }
        data[j + 1] = x;
        copy[j + 1] = x;
    }
}

void splitInsert(std::vector<int> &data, std::vector<int> &copy, int begin, int end) {
    if (end - begin < 16) {
        insertSort(data, copy, begin, end);
        return;
    }

    auto mid = (end + begin) / 2;
    splitInsert(copy, data, begin, mid);
    splitInsert(copy, data, mid, end);
    merge(copy, data, begin, mid, end);
}

void mergeSortInsert(std::vector<int> &data) {
    std::vector<int> copy(data);
    splitInsert(data, copy, 0, data.size());
}

void splitParallel(std::vector<int> &data, std::vector<int> &copy, int begin, int end) {
    if (end - begin < 16) {
        for (int i = begin; i < end; ++i) {
            auto x = data[i];
            int j = i - 1;
            while (j >= begin && data[j] > x) {
                data[j + 1] = data[j];
                copy[j + 1] = data[j];
                --j;
            }
            data[j + 1] = x;
            copy[j + 1] = x;
        }
        return;
    }

    auto mid = (end + begin) / 2;
    auto future1 = std::async([&]() { splitInsert(copy, data, begin, mid); });
    auto future2 = std::async([&]() { splitInsert(copy, data, mid, end); });
    future1.wait();
    future2.wait();
    merge(copy, data, begin, mid, end);
}

void mergeSortParallel(std::vector<int> &data) {
    std::vector<int> copy(data);
    splitParallel(data, copy, 0, data.size());
}

struct run {
    size_t from;
    size_t to;
    int size() { return to - from + 1; }
};

int getMinRun(int n) {
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

std::list<run> getRuns(std::vector<int> &data) {
    std::list<run> runs;
    int minRun = getMinRun(data.size());
    run currentRun{0, 1};
    do {
        bool isNonDec = data[currentRun.from] <= data[currentRun.to];
        bool isNonInc = data[currentRun.from] >= data[currentRun.to];
        while ((isNonInc || isNonDec) && currentRun.to < data.size() - 1) {
            if (isNonDec && data[currentRun.to] > data[currentRun.to + 1]) {
                isNonDec = false;
            }
            if (isNonInc && data[currentRun.to] < data[currentRun.to + 1]) {
                isNonInc = false;
            }
            if (isNonInc || isNonDec) {
                ++currentRun.to;
            }
        }
        if (data[currentRun.from] > data[currentRun.to]) {
            int mid = currentRun.size() / 2;
            for (int i = 0; i < mid; ++i) {
                std::swap(data[currentRun.from + i], data[currentRun.to - i]);
            }
        }
        if (currentRun.size() < minRun) {
            currentRun.to = std::min(currentRun.from + minRun, data.size() - 1);
            int remain = data.size() - currentRun.to - 1;
            if (remain > 0 && remain < minRun) {
                currentRun.to = data.size() - 1;
            }
            insertSort(data, currentRun.from, currentRun.to + 1);
        } else {
            int remain = data.size() - currentRun.to - 1;
            if (remain > 0 && remain < minRun) {
                currentRun.to = data.size() - 1;
                insertSort(data, currentRun.from, currentRun.to + 1);
            }
        }
        runs.push_back(currentRun);
        currentRun = run{currentRun.to + 1, currentRun.to + 2};
    } while (runs.back().to < data.size() - 1);
    return runs;
}

void mergeRun(std::vector<int> &data, int begin, int mid, int end) {
    int first = 0;
    int second = mid - begin;
    std::vector<int> copy(end - begin);
    std::copy(data.begin() + begin, data.begin() + end, copy.begin());
    for (int ptr = begin; ptr < end; ++ptr) {
        if (first < mid - begin && (second == end - begin || copy[first] < copy[second])) {
            data[ptr] = copy[first];
            ++first;
        } else {
            data[ptr] = copy[second];
            ++second;
        }
    }
}

void mergeSortRun(std::vector<int> &data) {
    std::list<run> runs = getRuns(data);
    while (runs.size() != 1) {
        auto it1 = runs.begin();
        auto it2 = std::next(it1);
        while (it1 != runs.end() && it2 != runs.end()) {
            mergeRun(data, it1->from, it2->from, it2->to + 1);
            it1->to = it2->to;
            it1 = std::next(it2);
            runs.erase(it2);
            if (it1 != runs.end()) {
                it2 = std::next(it1);
            }
        }
    }
}

void mergeSortRunParallel(std::vector<int> &data) {
    std::list<run> runs = getRuns(data);
    while (runs.size() != 1) {
        auto it1 = runs.begin();
        auto it2 = std::next(it1);
        std::vector<std::future<void>> jobs;
        while (it1 != runs.end() && it2 != runs.end()) {
            int begin = it1->from;
            int mid = it2->from;
            int end = it2->to + 1;
            jobs.push_back(std::async([=, &data]() { mergeRun(data, begin, mid, end); }));
            it1->to = it2->to;
            it1 = std::next(it2);
            runs.erase(it2);
            if (it1 != runs.end()) {
                it2 = std::next(it1);
            }
        }
    }
}


