#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <set>

class seqence {
public:
    virtual std::string GetName() = 0;

    virtual std::vector<size_t> GetSeq(size_t len) = 0;
};

class shell : public seqence {
public:
    std::string GetName() override {
        return "Shell, 1959";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        len /= 2;
        while (len > 0) {
            answer.push_back(len);
            len /= 2;
        }
        return answer;
    }
};

class frank : public seqence {
public:
    std::string GetName() override {
        return "Frank & Lazarus, 1960";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        size_t ans = 999;
        size_t k = 1;
        while (ans != 1) {
            ++k;
            ans = 2 * std::floor(1.0 * len / std::pow(2, k)) + 1;
            answer.push_back(ans);
        }
        return answer;
    }
};

class hibbard : public seqence {
private:
    std::vector<size_t> offsets = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535,
                                   131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431,
                                   67108863, 134217727, 268435455, 536870911, 1073741823, 2147483647, 4294967295,
                                   8589934591};
public:
    std::string GetName() override {
        return "Hibbard, 1963";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class papernov : public seqence {
private:
    std::vector<size_t> offsets = {1, 3, 5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8193, 16385,
                                   32769, 65537, 131073, 262145, 524289, 1048577, 2097153, 4194305, 8388609, 16777217,
                                   33554433, 67108865, 134217729, 268435457, 536870913, 1073741825, 2147483649};
public:
    std::string GetName() override {
        return "Papernov & Stasevich, 1965";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class pratt : public seqence {
private:
    std::set<size_t> offsets;
public:
    pratt() {
        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 20; ++j) {
                offsets.insert(std::pow(2, i) * std::pow(3, j));
            }
        }
    }

    std::string GetName() override {
        return "Pratt, 1971";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class pratt2 : public seqence {
private:
    std::vector<size_t> offsets = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720, 797161, 2391484,
                                   7174453, 21523360, 64570081, 193710244, 581130733, 1743392200, 5230176601,
                                   15690529804, 47071589413, 141214768240, 423644304721, 1270932914164};
public:
    std::string GetName() override {
        return "Pratt, 1971, Knuth, 1973";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class incerpi : public seqence {
private:
    std::vector<size_t> offsets = {1, 3, 7, 21, 48, 112, 336, 861, 1968, 4592, 13776, 33936, 86961, 198768, 463792,
                                   1391376, 3402672, 8382192, 21479367, 49095696, 114556624, 343669872, 852913488,
                                   2085837936, 5138283696, 13166851971, 30095661648, 70223210512};
public:
    std::string GetName() override {
        return "Incerpi & Sedgewick, 1985, Knuth";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class sedgewick : public seqence {
private:
    std::vector<size_t> offsets = {1, 8, 23, 77, 281, 1073, 4193, 16577, 65921, 262913, 1050113, 4197377, 16783361,
                                   67121153, 268460033, 1073790977, 4295065601, 17180065793, 68719869953, 274878693377,
                                   1099513200641, 4398049656833, 17592192335873, 70368756760577};
public:
    std::string GetName() override {
        return "Sedgewick, 1982";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class sedgewick2 : public seqence {
private:
    std::vector<size_t> offsets = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305,
                                   260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929, 37730305, 67084289,
                                   150958081, 268386305, 603906049, 1073643521, 2415771649, 4294770689};
public:
    std::string GetName() override {
        return "Sedgewick, 1986";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class gonnet : public seqence {
public:
    std::string GetName() override {
        return "Gonnet & Baeza-Yates, 1991";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        len = 5 * len / 11;
        while (len > 0) {
            answer.push_back(len);
            len = 5 * len / 11;
        }
        return answer;
    }
};

class tokuda : public seqence {
private:
    std::vector<size_t> offsets = {1, 4, 9, 20, 46, 103, 233, 525, 1182, 2660, 5985, 13467, 30301, 68178, 153401,
                                   345152, 776591, 1747331, 3931496, 8845866, 19903198, 44782196, 100759940, 226709866,
                                   510097200, 1147718700, 2582367076, 5810325920, 13073233321, 29414774973};
public:
    std::string GetName() override {
        return "Tokuda, 1992";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};

class ciura : public seqence {
private:
    std::vector<size_t> offsets = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
public:
    std::string GetName() override {
        return "Ciura, 2001, Dovgopol, 2011";
    };

    std::vector<size_t> GetSeq(size_t len) override {
        std::vector<size_t> answer;
        std::for_each(offsets.rbegin(), offsets.rend(), [&len, &answer](auto val) {
            if (val < len) {
                answer.push_back(val);
            }
        });
        return answer;
    }
};


class sequences : public std::vector<std::unique_ptr<seqence>> {
public:
    sequences() {
        push_back(std::make_unique<shell>());
        push_back(std::make_unique<frank>());
        push_back(std::make_unique<hibbard>());
        push_back(std::make_unique<papernov>());
        push_back(std::make_unique<pratt>());
        push_back(std::make_unique<pratt2>());
        push_back(std::make_unique<incerpi>());
        push_back(std::make_unique<sedgewick>());
        push_back(std::make_unique<sedgewick2>());
        push_back(std::make_unique<gonnet>());
        push_back(std::make_unique<tokuda>());
        push_back(std::make_unique<ciura>());
    }
};