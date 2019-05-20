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
        if (c != '-')
            while (true) {
            if (c == 'K') Kok = true;
            else if (c == 'Q') Qok = true;
            else if (c == 'k') kok = true;
            else if (c == 'q') qok = true;
            else {
                iss.seekg(-1, std::ios::cur);
                break;
            }
            iss >> c;
        }

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
        oss << (nextW ? "w " : "b ");
        if (Kok) oss << 'K';
        if (Qok) oss << 'Q';
        if (kok) oss << 'k';
        if (qok) oss << 'q';
        if (Kok | Qok | kok | qok) oss << ' ';
        else oss << "- ";
        oss << enPassant << " " << halfmove << " " << fullmove;
        return oss.str();
    };

    void move(std::string move) {
        if (!nextW) ++fullmove;
        nextW = !nextW;
        size_t cf = move[0] - 'a';
        size_t rf = 8 - (move[1] - '0');
        size_t ct = move[2] - 'a';
        size_t rt = 8 - (move[3] - '0');
        if (board[rf][cf] == 'p' || board[rf][cf] == 'P' || board[rt][ct] != '.') {
            halfmove = 0;
        } else {
            ++halfmove;
        }
        if (qok && (cf == 0 && rf == 0 || ct==0 && rt ==0 || board[rf][cf] == 'k')) qok = false;
        if (kok && (cf == 7 && rf == 0 || ct==7 && rt ==0 || board[rf][cf] == 'k')) kok = false;
        if (Qok && (cf == 0 && rf == 7 || ct==0 && rt ==7 || board[rf][cf] == 'K')) Qok = false;
        if (Kok && (cf == 7 && rf == 7 || ct==7 && rt ==7 || board[rf][cf] == 'K')) Kok = false;
        if (cf != ct || rf != rt) {
            if (move.length()==5)
            {
                board[rt][ct] = move[4];
            } else {
                board[rt][ct] = board[rf][cf];
            }
            board[rf][cf] = '.';
        }
    }
private:
    std::array<std::array<char, 8>, 8> board;
    bool nextW, Kok = false, Qok = false, kok = false, qok = false;
    std::string enPassant;
    size_t halfmove, fullmove;
};