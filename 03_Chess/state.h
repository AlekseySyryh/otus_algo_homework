#pragma once

#include <array>
#include <sstream>


class state {
public:
    state(std::string fen) {
        std::istringstream iss(fen);
        size_t freeSpace = 0;
        char c;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (freeSpace > 0) {
                    board[i][j] = '.';
                    --freeSpace;
                } else {
                    iss >> c;
                    if (c >= '1' and c <= '8') {
                        board[i][j] = '.';
                        freeSpace = c - '1';
                    } else {
                        board[i][j] = c;
                    }
                }
            }
            if (i != 7) iss >> c;
        }
        iss >> c;
        nextW = (c == 'w' || c == 'W');
        iss >> c;
        while (c != ' ') {
            if (c == 'K') Kok = true;
            else if (c == 'Q') Qok = true;
            else if (c == 'k') kok = true;
            else if (c == 'q') qok = true;
            else break;
            iss >> c;
        }
        iss.seekg(-1, std::ios::cur);
        iss >> enPassant >> halfmove >> fullmove;
    }

    std::string show() {
        std::ostringstream oss;
        oss << "  +-----------------+\n";

        for (int i = 0; i < 8; ++i) {
            oss << 8 - i << " | ";
            for (int j = 0; j < 8; ++j) {
                oss << board[i][j] << " ";
            }
            oss << "|\n";
        }
        oss << "  +-----------------+\n    a b c d e f g h";
        return oss.str();
    }

    std::string build() {
        std::ostringstream oss;
        for (int i = 0; i < 8; ++i) {
            size_t nothing = 0;
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == '.') {
                    ++nothing;
                } else {
                    if (nothing != 0) {
                        oss << nothing;
                        nothing = 0;
                    }
                    oss << board[i][j];
                }
            }
            if (nothing != 0) {
                oss << nothing;
            }
            oss << (i == 7 ? ' ' : '/');
        }
        oss << (nextW ? "w " : "n ");
        if (Kok) oss << 'K';
        if (Qok) oss << 'Q';
        if (kok) oss << 'k';
        if (qok) oss << 'q';
        if (Kok | Qok | kok | qok) oss << ' ';
        oss << enPassant << " " << halfmove << " " << fullmove;
        return oss.str();
    };
private:
    std::array<std::array<char, 8>, 8> board;
    bool nextW, Kok, Qok, kok, qok;
    std::string enPassant;
    size_t halfmove, fullmove;
};