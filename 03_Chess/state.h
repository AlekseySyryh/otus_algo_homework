#pragma once

#include <array>
#include <sstream>
#include "pos.h"

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
        pos from(move.substr(0, 2));
        pos to(move.substr(2, 2));
        if (at(from) == 'p' || at(from) == 'P' || at(to) != '.') {
            halfmove = 0;
        } else {
            ++halfmove;
        }
        if (qok && (from.name == "a8" || to.name == "a8" || at(from) == 'k')) qok = false;
        if (kok && (from.name == "h8" || to.name == "h8" || at(from) == 'k')) kok = false;
        if (Qok && (from.name == "a1" || to.name == "a1" || at(from) == 'K')) Qok = false;
        if (Kok && (from.name == "h1" || to.name == "h1" || at(from) == 'K')) Kok = false;
        if ((at(from) == 'p' || at(from) == 'P') &&
            (from.rowc == '2' && to.rowc == '4' || from.rowc == '7' && to.rowc == '5')) {
            pos ep((from.row + to.row) / 2, from.col);
            enPassant = ep.name;
        } else {
            enPassant = "-";
        }
        if (from != to) {
            if (move.length()==5)
            {
                at(to) = move[4];
            } else {
                at(to) = at(from);
            }
            at(from) = '.';
        }
    }
private:
    char &at(const pos &pos) {
        return board[pos.row][pos.col];
    }

    std::array<std::array<char, 8>, 8> board;
    bool nextW, Kok = false, Qok = false, kok = false, qok = false;
    std::string enPassant;
    size_t halfmove, fullmove;
};