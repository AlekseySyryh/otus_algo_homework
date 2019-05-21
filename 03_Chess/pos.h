#pragma once

class pos {
public:
    pos(size_t row, size_t col) {
        this->row = row;
        this->col = col;
        std::ostringstream oss;
        oss << (char) (col + 'a') << (8 - row);
        name = oss.str();
        colc = name[0];
        rowc = name[1];
    }

    pos(std::string name) {
        this->name = name;
        col = name[0] - 'a';
        row = 8 - (name[1] - '0');
        colc = name[0];
        rowc = name[1];
    }

    bool operator!=(const pos &other) const {
        return !(*this == other);
    }

    bool operator==(const pos &other) const {
        return col == other.col && row == other.row;
    }

    size_t row, col;
    std::string name;
    char colc, rowc;
};