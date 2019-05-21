#pragma once

#include <array>
#include <sstream>
#include <vector>
#include <algorithm>
#include "pos.h"
#include "move.h"

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

    void makeMove(std::string newMove) {
        move mv(newMove);
        makeMove(mv);
    }

    void makeMove(const move &newMove) {
        if (!nextW) ++fullmove;
        nextW = !nextW;

        if (at(newMove.from) == 'p' || at(newMove.from) == 'P' || at(newMove.to) != '.') {
            halfmove = 0;
        } else {
            ++halfmove;
        }
        if (qok && (newMove.from.name == "a8" || newMove.to.name == "a8" || at(newMove.from) == 'k')) qok = false;
        if (kok && (newMove.from.name == "h8" || newMove.to.name == "h8" || at(newMove.from) == 'k')) kok = false;
        if (Qok && (newMove.from.name == "a1" || newMove.to.name == "a1" || at(newMove.from) == 'K')) Qok = false;
        if (Kok && (newMove.from.name == "h1" || newMove.to.name == "h1" || at(newMove.from) == 'K')) Kok = false;
        if ((at(newMove.from) == 'p' || at(newMove.from) == 'P') &&
            (newMove.from.rowc == '2' && newMove.to.rowc == '4' ||
             newMove.from.rowc == '7' && newMove.to.rowc == '5')) {
            pos ep((newMove.from.row + newMove.to.row) / 2, newMove.from.col);
            enPassant = ep.name;
        } else {
            enPassant = "-";
        }
        if (newMove.valid) {
            if (newMove.pawnConvert)
            {
                at(newMove.to) = newMove.newFigure;
            } else {
                at(newMove.to) = at(newMove.from);
            }
            at(newMove.from) = '.';
        }
    }

    std::vector<std::vector<move>> sortAndGroup(std::vector<move> moves) {
        std::vector<std::vector<move>> ret(1);
        std::sort(moves.begin(), moves.end());
        pos grPos = moves.front().from;
        for (const auto &newMove : moves) {
            if (grPos != newMove.from) {
                grPos = newMove.from;
                ret.emplace_back();
            }
            ret.back().emplace_back(newMove);
        }
        return ret;
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