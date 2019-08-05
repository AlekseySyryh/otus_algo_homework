#pragma once

#include <future>
#include "insertSort.h"
#include <queue>

enum pivotStrategy {
    last,
    median,
    random
};

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
    task(int begin, int end) : begin(begin), end(end) {}

    int begin;
    int end;
};

void quickSortStep(std::vector<int> &data, pivotStrategy strategy, bool useInsert) {
    std::queue<task> tasks;
    tasks.emplace(0, (int) data.size());

    while (tasks.size() > 0) {
        auto task = tasks.front();
        tasks.pop();
        if (task.begin >= task.end) continue;
        if (useInsert && task.end - task.begin < 32) {
            insertSort(data, task.begin, task.end);
            continue;
        }
        int pivot = partition(data, task.begin, task.end, strategy);
        tasks.emplace(task.begin, pivot);
        tasks.emplace(pivot + 1, task.end);
    }
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
        tasks.emplace_back(subtask.begin, pivot);
        tasks.emplace_back(pivot + 1, subtask.end);
        return tasks;

}

const int minParallelBlock = 10000;

void quickSortParallelStep(std::vector<int> &data, pivotStrategy strategy,
                           bool useInsert) {
    std::queue<task> tasks, subtasks;
    std::vector<std::unique_ptr<std::future<std::vector<task>>>> futures;
    futures.reserve(threads);
    tasks.emplace(0, (int) data.size());
    while (tasks.size() > 0) {
        while (tasks.size() > 0 && subtasks.size() < threads) {
            task task = tasks.front();
            tasks.pop();
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
}

void quickSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::last, false);
}

void quickMedianSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::median, false);
}

void quickRandomSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::random, false);
}

void quickInsertSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::last, true);
}

void quickInsertMedianSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::median, true);
}

void quickInsertRandomSort(std::vector<int> &data) {
    return quickSortStep(data, pivotStrategy::random, true);
}

void quickParallelSort(std::vector<int> &data) {
    quickSortParallelStep(data, pivotStrategy::last, false);
}

void quickMedianParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::median, false);
}

void quickRandomParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::random, false);
}

void quickInsertParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::last, true);
}

void quickInsertMedianParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::median, true);
}

void quickInsertRandomParallelSort(std::vector<int> &data) {
    return quickSortParallelStep(data, pivotStrategy::random, true);
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

void quickSort3Step(std::vector<int> &data, pivotStrategy strategy, bool useInsert) {
    std::queue<task> tasks;
    tasks.emplace(0, (int) data.size());

    while (tasks.size() > 0) {
        auto task = tasks.front();
        tasks.pop();
        if (task.begin >= task.end) continue;
        if (useInsert && task.end - task.begin < 32) {
            insertSort(data, task.begin, task.end);
            continue;
        }
        auto pivots = partition3(data, task.begin, task.end, strategy);
        if (task.begin < pivots.first)
            tasks.emplace(task.begin, pivots.first);
        if (pivots.second + 1 < task.end)
            tasks.emplace(pivots.second + 1, task.end);
    }
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
        tasks.emplace_back(subtask.begin, pivots.first);
    if (pivots.second + 1 < subtask.end)
        tasks.emplace_back(pivots.second + 1, subtask.end);
    return tasks;

}

void quickSort3ParallelStep(std::vector<int> &data, pivotStrategy strategy,
                            bool useInsert) {
    std::queue<task> tasks, subtasks;
    std::vector<std::unique_ptr<std::future<std::vector<task>>>> futures;
    futures.reserve(threads);
    tasks.emplace(0, (int) data.size());
    while (tasks.size() > 0) {
        while (tasks.size() > 0 && subtasks.size() < threads) {
            task task = tasks.front();
            tasks.pop();
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
}


void quick3WaySort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::last, false);
}

void quick3WayMedianSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::median, false);
}

void quick3WayRandomSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::random, false);
}

void quick3WayInsertSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::last, true);
}

void quick3WayInsertMedianSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::median, true);
}

void quick3WayInsertRandomSort(std::vector<int> &data) {
    return quickSort3Step(data, pivotStrategy::random, true);
}

void quick3WayParallelSort(std::vector<int> &data) {
    quickSort3ParallelStep(data, pivotStrategy::last, false);
}

void quick3WayMedianParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::median, false);
}

void quick3WayRandomParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::random, false);
}

void quick3WayInsertParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::last, true);
}

void quick3WayInsertMedianParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::median, true);
}

void quick3WayInsertRandomParallelSort(std::vector<int> &data) {
    return quickSort3ParallelStep(data, pivotStrategy::random, true);
}