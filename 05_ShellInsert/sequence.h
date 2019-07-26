#pragma once
#include <string>
#include <vector>

class seq {
public:
    virtual std::string GetName() = 0;
    virtual std::vector<size_t> GetSeq(size_t len) = 0;
};

class shell : public seq{
public:
    std::string GetName() override {
        return "Shell, 1959";
    };
    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        len /=2;
        while (len > 0){
            answer.push_back(len);
            len /=2;
        }
    }

};

class sequences : public