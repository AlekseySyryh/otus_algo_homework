#pragma once

#include <future>
#include "insertSort.h"
#include "heapSort.h"
#include <queue>

enum pivotStrategy {
    last,
    median,
    random
};
const int stopLevel = 10000;
const int minParallelBlock = 10000;

int partition(std::vector<int> &data, int begin, int end, pivotStrategy strategy) {
    if (strategy == pivotStrategy::median) {
        int middleIx = (begin + end) / 2;
        int first = data[begin];
        int mid = data[middleIx];
        int last = data[end - 1];
        if ((first >= mid && first <= last) || (first <= mid && first >= last)) {
            std::swap(data[begin], data[end - 1]);
        } else if ((mid >= first && mid <= last) || (mid <= first && mid >= last)) {
            std::swap(data[middleIx], data[end - 1]);
        }
    } else if (strategy == pivotStrategy::random) {
        if (end - begin != 1) {
            int ix = begin + std::rand() % (end - begin - 1);
            std::swap(data[ix], data[end - 1]);
        }
    }
    int pivot = data[end - 1];
    int i = begin - 1;
    for (int j = begin; j < end - 1; ++j) {
        if (data[j] <= pivot) {
            ++i;
            std::swap(data[i], data[j]);
        }
    }
    std::swap(data[i + 1], data[end - 1]);
    return i + 1;
}

struct task {
    task(int begin, int end, int level) : begin(begin), end(end), level(level) {}

    int begin;
    int end;
    int level;
};

bool quickSortStep(std::vector<int> &data, pivotStrategy strategy, bool useInsert, bool useIntro) {
    std::queue<task> tasks;
    tasks.emplace(0, (int) data.size(), 0);
    int introLimit = (int) std::ceil(5 * std::log(data.size()));
    while (tasks.size() > 0) {
        auto task = tasks.front();
        tasks.pop();
        if (useIntro && task.level > introLimit) {
            heapSort(data);
            return true;
        }
        if (task.level > stopLevel) return false;
        if (task.begin >= task.end) continue;
        if (useInsert && task.end - task.begin < 32) {
            insertSort(data, task.begin, task.end);
            continue;
        }
        int pivot = partition(data, task.begin, task.end, strategy);
        tasks.emplace(task.begin, pivot, task.level + 1);
        tasks.emplace(pivot + 1, task.end, task.level + 1);
    }
    return true;
}

auto threads = std::thread::hardware_concurrency();

std::vector<task> step(task subtask, std::vector<int> &data, pivotStrategy strategy,
                       bool useInsert) {

        std::vector<task> tasks;
        if (subtask.begin >= subtask.end) return tasks;
        if (useInsert && subtask.end - subtask.begin < 32) {
            insertSort(data, subtask.begin, subtask.end);
            return tasks;
        }
        int pivot = partition(data, subtask.begin, subtask.end, strategy);
    tasks.emplace_back(subtask.begin, pivot, subtask.level + 1);
    tasks.emplace_back(pivot + 1, subtask.end, subtask.level + 1);
        return tasks;

}



bool quickSortParallelStep(std::vector<int> &data, pivotStrategy strategy,
                           bool useInsert, bool useIntro) {
    std::queue<task> tasks, subtasks;
    std::vector<std::unique_ptr<std::future<std::vector<task>>>> futures;
    futures.reserve(threads);
    tasks.emplace(0, (int) data.size(), 0);

    int introLimit = (int) std::ceil(5 * std::log(data.size()));
    while (tasks.size() > 0) {
        while (tasks.size() > 0 && subtasks.size() < threads) {
            task task = tasks.front();
            tasks.pop();
            if (useIntro && task.level > introLimit) {
                heapSort(data);
                return true;
            }
            if (task.level > stopLevel) return false;
            if (task.end - task.begin >= minParallelBlock) {
                subtasks.push(task);
            } else {
                auto newTasks = step(task, data, strategy, useInsert);
                for (auto &newTask:newTasks) {
                    if (newTask.end - newTask.begin > 1)
                        tasks.push(newTask);
                }
            }
        }
        if (subtasks.size() == 1) {
            auto subtask = subtasks.front();
            subtasks.pop();
            auto newTasks = step(subtask, data, strategy, useInsert);
            for (auto &newTask:newTasks) {
                if (newTask.end - newTask.begin > 1)
                    tasks.push(newTask);
            }
        }

        while (subtasks.size() > 0) {
            auto subtask = subtasks.front();
            subtasks.pop();
            futures.push_back(std::make_unique<std::future<std::vector<task>>>(
                    std::async([&, subtask]() { return step(subtask, data, strategy, useInsert); })));
        }
        for (auto &future:futures) {
            auto newTasks = future.get()->get();
            for (auto &newTask:newTasks) {
                if (newTask.end - newTask.begin > 1)
                    tasks.push(newTask);
            }
        }
        futures.clear();
    }
    return true;
}

bool quickSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::last, false, false);
}

bool quickMedianSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::median, false, false);
}

bool quickRandomSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::random, false, false);
}

bool quickInsertSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::last, true, false);
}

bool quickInsertMedianSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::median, true, false);
}

bool quickInsertRandomSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::random, true, false);
}

bool quickParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::last, false, false);
}

bool quickMedianParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::median, false, false);
}

bool quickRandomParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::random, false, false);
}

bool quickInsertParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::last, true, false);
}

bool quickInsertMedianParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::median, true, false);
}

bool quickInsertRandomParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::random, true, false);
}

std::pair<int, int> partition3(std::vector<int> &data, int begin, int end, pivotStrategy strategy) {
    if (strategy == pivotStrategy::median) {
        int middleIx = (begin + end) / 2;
        int first = data[begin];
        int mid = data[middleIx];
        int last = data[end - 1];
        if ((first >= mid && first <= last) || (first <= mid && first >= last)) {
            std::swap(data[begin], data[end - 1]);
        } else if ((mid >= first && mid <= last) || (mid <= first && mid >= last)) {
            std::swap(data[middleIx], data[end - 1]);
        }
    } else if (strategy == pivotStrategy::random) {
        if (end - begin != 1) {
            int ix = begin + std::rand() % (end - begin - 1);
            std::swap(data[ix], data[end - 1]);
        }
    }
    int ixToCheck = begin, eqBegin = begin - 1, eqEnd = begin - 1;
    while (ixToCheck < end - 1) {
        if (data[ixToCheck] < data[end - 1]) {
            ++eqBegin;
            ++eqEnd;
            std::swap(data[eqBegin], data[eqEnd]);
            if (ixToCheck != eqEnd)
                std::swap(data[ixToCheck], data[eqBegin]);
            ++ixToCheck;
        } else if (data[ixToCheck] == data[end - 1]) {
            ++eqEnd;
            std::swap(data[ixToCheck], data[eqEnd]);
            ++ixToCheck;
        } else { ++ixToCheck; }
    }
    ++eqBegin;
    ++eqEnd;
    std::swap(data[eqEnd], data[end - 1]);
    return {eqBegin, eqEnd};
}

bool quickSort3Step(std::vector<int> &data, pivotStrategy strategy, bool useInsert, bool useIntro) {
    std::queue<task> tasks;
    tasks.emplace(0, (int) data.size(), 0);
    int introLimit = (int) std::ceil(5 * std::log(data.size()));
    while (tasks.size() > 0) {
        auto task = tasks.front();
        tasks.pop();
        if (useIntro && task.level > introLimit) {
            heapSort(data);
            return true;
        }
        if (task.level > stopLevel) return false;
        if (task.begin >= task.end) continue;
        if (useInsert && task.end - task.begin < 32) {
            insertSort(data, task.begin, task.end);
            continue;
        }
        auto pivots = partition3(data, task.begin, task.end, strategy);
        if (task.begin < pivots.first)
            tasks.emplace(task.begin, pivots.first, task.level + 1);
        if (pivots.second + 1 < task.end)
            tasks.emplace(pivots.second + 1, task.end, task.level + 1);
    }
    return true;
}

std::vector<task> step3(task subtask, std::vector<int> &data, pivotStrategy strategy,
                        bool useInsert) {

    std::vector<task> tasks;
    if (subtask.begin >= subtask.end) return tasks;
    if (useInsert && subtask.end - subtask.begin < 32) {
        insertSort(data, subtask.begin, subtask.end);
        return tasks;
    }
    auto pivots = partition3(data, subtask.begin, subtask.end, strategy);
    if (subtask.begin < pivots.first)
        tasks.emplace_back(subtask.begin, pivots.first, subtask.level + 1);
    if (pivots.second + 1 < subtask.end)
        tasks.emplace_back(pivots.second + 1, subtask.end, subtask.level + 1);
    return tasks;

}

bool quickSort3ParallelStep(std::vector<int> &data, pivotStrategy strategy,
                            bool useInsert, bool useIntro) {
    std::queue<task> tasks, subtasks;
    std::vector<std::unique_ptr<std::future<std::vector<task>>>> futures;
    futures.reserve(threads);
    tasks.emplace(0, (int) data.size(), 0);
    int introLimit = (int) std::ceil(5 * std::log(data.size()));
    while (tasks.size() > 0) {
        while (tasks.size() > 0 && subtasks.size() < threads) {
            task task = tasks.front();
            tasks.pop();
            if (useIntro && task.level > introLimit) {
                heapSort(data);
                return true;
            }
            if (task.level > stopLevel) return false;
            if (task.end - task.begin >= minParallelBlock) {
                subtasks.push(task);
            } else {
                auto newTasks = step3(task, data, strategy, useInsert);
                for (auto &newTask:newTasks) {
                    if (newTask.end - newTask.begin > 1)
                        tasks.push(newTask);
                }
            }
        }
        if (subtasks.size() == 1) {
            auto subtask = subtasks.front();
            subtasks.pop();
            auto newTasks = step3(subtask, data, strategy, useInsert);
            for (auto &newTask:newTasks) {
                if (newTask.end - newTask.begin > 1)
                    tasks.push(newTask);
            }
        }

        while (subtasks.size() > 0) {
            auto subtask = subtasks.front();
            subtasks.pop();
            futures.push_back(std::make_unique<std::future<std::vector<task>>>(
                    std::async([&, subtask]() { return step3(subtask, data, strategy, useInsert); })));
        }
        for (auto &future:futures) {
            auto newTasks = future.get()->get();
            for (auto &newTask:newTasks) {
                if (newTask.end - newTask.begin > 1)
                    tasks.push(newTask);
            }
        }
        futures.clear();
    }
    return true;
}


bool quick3WaySort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::last, false, false);
}

bool quick3WayMedianSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::median, false, false);
}

bool quick3WayRandomSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::random, false, false);
}

bool quick3WayInsertSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::last, true, false);
}

bool quick3WayInsertMedianSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::median, true, false);
}

bool quick3WayInsertRandomSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::random, true, false);
}

bool quick3WayParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::last, false, false);
}

bool quick3WayMedianParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::median, false, false);
}

bool quick3WayRandomParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::random, false, false);
}

bool quick3WayInsertParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::last, true, false);
}

bool quick3WayInsertMedianParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::median, true, false);
}

bool quick3WayInsertRandomParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::random, true, false);
}

bool introSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::last, false, true);
}

bool introMedianSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::median, false, true);
}

bool introRandomSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::random, false, true);
}

bool introInsertSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::last, true, true);
}

bool introInsertMedianSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::median, true, true);
}

bool introInsertRandomSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::random, true, true);
}

bool introParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::last, false, true);
}

bool introMedianParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::median, false, true);
}

bool introRandomParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::random, false, true);
}

bool introInsertParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::last, true, true);
}

bool introInsertMedianParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::median, true, true);
}

bool introInsertRandomParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::random, true, true);
}

bool intro3WaySort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::last, false, true);
}

bool intro3WayMedianSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::median, false, true);
}

bool intro3WayRandomSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::random, false, true);
}

bool intro3WayInsertSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::last, true, true);
}

bool intro3WayInsertMedianSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::median, true, true);
}

bool intro3WayInsertRandomSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::random, true, true);
}

bool intro3WayParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::last, false, true);
}

bool intro3WayMedianParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::median, false, true);
}

bool intro3WayRandomParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::random, false, true);
}

bool intro3WayInsertParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::last, true, true);
}

bool intro3WayInsertMedianParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::median, true, true);
}

bool intro3WayInsertRandomParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::random, true, true);
}
