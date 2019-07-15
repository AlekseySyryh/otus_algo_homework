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
        nextWhite = (c == 'w' || c == 'W');
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
        oss << (nextWhite ? "w " : "b ");
        if (Kok) oss << 'K';
        if (Qok) oss << 'Q';
        if (kok) oss << 'k';
        if (qok) oss << 'q';
        if (Kok | Qok | kok | qok) oss << ' ';
        else oss << "- ";
        if (enPassant != "-") {
            if (underAttack(pos{enPassant})) {
                oss << enPassant;
            } else {
                oss << "-";
            }
        } else {
            oss << enPassant;
        }
        oss << " " << halfmove << " " << fullmove;
        return oss.str();
    };

    void makeMove(std::string newMove) {
        move mv(newMove);
        makeMove(mv);
    }

    void makeMove(const move &newMove) {
        if (!nextWhite) ++fullmove;
        nextWhite = !nextWhite;

        if (at(newMove.from) == 'p' || at(newMove.from) == 'P' || at(newMove.to) != '.') {
            halfmove = 0;
        } else {
            ++halfmove;
        }
        if (qok && (newMove.from.name == "a8" || newMove.to.name == "a8" || at(newMove.from) == 'k')) qok = false;
        if (kok && (newMove.from.name == "h8" || newMove.to.name == "h8" || at(newMove.from) == 'k')) kok = false;
        if (Qok && (newMove.from.name == "a1" || newMove.to.name == "a1" || at(newMove.from) == 'K')) Qok = false;
        if (Kok && (newMove.from.name == "h1" || newMove.to.name == "h1" || at(newMove.from) == 'K')) Kok = false;

        if (normalize(newMove.from) == 'p' &&
            (newMove.from.rowc == '2' && newMove.to.rowc == '4' ||
             newMove.from.rowc == '7' && newMove.to.rowc == '5')) {
            pos ep((newMove.from.row + newMove.to.row) / 2, newMove.from.col);
            enPassant = ep.name;
        } else {
            if (normalize(newMove.from) == 'p' && newMove.to.name == enPassant) {
                if (nextWhite) {
                    at(pos(newMove.to.row-1,newMove.to.col)) = '.';
                } else {
                    at(pos(newMove.to.row+1,newMove.to.col)) = '.';
                }
            }
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
        std::vector<std::vector<move>> ret;
        if (moves.size() != 0) {
            ret.resize(1);
            std::sort(moves.begin(), moves.end());
            pos grPos = moves.front().from;
            for (const auto &newMove : moves) {
                if (grPos != newMove.from) {
                    grPos = newMove.from;
                    ret.emplace_back();
                }
                ret.back().emplace_back(newMove);
            }
        }
        return ret;
    }

    std::vector<move> getPossibleKnightMoves() {
        std::vector<move> ret;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                pos p(i, j);
                if (
                        isWhite(p) == nextWhite &&
                        normalize(p) == 'n') {
                    pos np = pos(i - 2, j - 1);
                    addMoveIfOk(ret, p, np);
                    np = pos(i - 2, j + 1);
                    addMoveIfOk(ret, p, np);
                    np = pos(i - 1, j - 2);
                    addMoveIfOk(ret, p, np);
                    np = pos(i - 1, j + 2);
                    addMoveIfOk(ret, p, np);
                    np = pos(i + 2, j - 1);
                    addMoveIfOk(ret, p, np);
                    np = pos(i + 2, j + 1);
                    addMoveIfOk(ret, p, np);
                    np = pos(i + 1, j - 2);
                    addMoveIfOk(ret, p, np);
                    np = pos(i + 1, j + 2);
                    addMoveIfOk(ret, p, np);
                }
            }
        }
        return ret;
    }

    std::vector<move> getPossibleRockMoves() {
        std::vector<move> ret;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                pos p(i, j);
                if (isWhite(p) == nextWhite &&
                    normalize(p) == 'r') {
                    pos pn = p;
                    do {
                        pn = pos(pn.row - 1, pn.col);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row + 1, pn.col);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row, pn.col - 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row, pn.col + 1);
                    } while (addMoveIfOk(ret, p, pn));
                }
            }
        }
        return ret;
    }

    std::vector<move> getPossibleBishopMoves() {
        std::vector<move> ret;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                pos p(i, j);
                if (isWhite(p) == nextWhite &&
                    normalize(p) == 'b') {
                    pos pn = p;
                    do {
                        pn = pos(pn.row - 1, pn.col - 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row - 1, pn.col + 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row + 1, pn.col - 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row + 1, pn.col + 1);
                    } while (addMoveIfOk(ret, p, pn));
                }
            }
        }
        return ret;
    }

    std::vector<move> getPossibleQueenMoves() {
        std::vector<move> ret;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                pos p(i, j);
                if (isWhite(p) == nextWhite &&
                    normalize(p) == 'q') {
                    pos pn = p;
                    do {
                        pn = pos(pn.row - 1, pn.col);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row + 1, pn.col);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row, pn.col - 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row, pn.col + 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row - 1, pn.col - 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row - 1, pn.col + 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row + 1, pn.col - 1);
                    } while (addMoveIfOk(ret, p, pn));
                    pn = p;
                    do {
                        pn = pos(pn.row + 1, pn.col + 1);
                    } while (addMoveIfOk(ret, p, pn));
                }
            }
        }
        return ret;
    }

    std::vector<move> getPossibleKingMoves() {
        std::vector<move> ret;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                pos p(i, j);
                if (isWhite(p) == nextWhite &&
                    normalize(p) == 'k') {
                    addMoveIfOk(ret, p, pos{p.row - 1, p.col - 1});
                    addMoveIfOk(ret, p, pos{p.row, p.col - 1});
                    addMoveIfOk(ret, p, pos{p.row + 1, p.col - 1});
                    addMoveIfOk(ret, p, pos{p.row - 1, p.col});
                    addMoveIfOk(ret, p, pos{p.row + 1, p.col});
                    addMoveIfOk(ret, p, pos{p.row - 1, p.col + 1});
                    addMoveIfOk(ret, p, pos{p.row, p.col + 1});
                    addMoveIfOk(ret, p, pos{p.row + 1, p.col + 1});
                }
            }
        }
        return ret;
    }

    std::vector<move> getPossiblePawnMoves() {
        std::vector<move> ret;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                pos p(i, j);
                if (isWhite(p) == nextWhite &&
                    normalize(p) == 'p') {
                    if (nextWhite) {
                        if (at(pos{p.row - 1, p.col}) == '.') {
                            if (p.rowc != '7') {
                                ret.emplace_back(p, pos{p.row - 1, p.col});
                            } else {
                                ret.emplace_back(p, pos{p.row - 1, p.col}, 'Q');
                                ret.emplace_back(p, pos{p.row - 1, p.col}, 'R');
                                ret.emplace_back(p, pos{p.row - 1, p.col}, 'B');
                                ret.emplace_back(p, pos{p.row - 1, p.col}, 'N');
                            }

                            if (p.rowc == '2' && at(pos{p.row - 2, p.col}) == '.') {
                                ret.emplace_back(p, pos{p.row - 2, p.col});
                            }
                        }

                        pos p1 = {p.row - 1, p.col - 1};
                        if (p1.valid && (
                                (at(p1) != '.' && !isWhite(p1)) ||
                                enPassant == p1.name)) {
                            ret.emplace_back(p, p1);
                        }
                        p1 = {p.row - 1, p.col + 1};
                        if (p1.valid && (
                                (at(p1) != '.' && !isWhite(p1)) ||
                                enPassant == p1.name)) {
                            ret.emplace_back(p, p1);
                        }
                    } else {
                        if (at(pos{p.row + 1, p.col}) == '.') {
                            if (p.rowc != '2') {
                                ret.emplace_back(p, pos{p.row + 1, p.col});
                            } else {
                                ret.emplace_back(p, pos{p.row + 1, p.col}, 'q');
                                ret.emplace_back(p, pos{p.row + 1, p.col}, 'r');
                                ret.emplace_back(p, pos{p.row + 1, p.col}, 'b');
                                ret.emplace_back(p, pos{p.row + 1, p.col}, 'n');
                            }
                            if (p.rowc == '7' && at(pos{p.row + 2, p.col}) == '.') {
                                ret.emplace_back(p, pos{p.row + 2, p.col});
                            }
                        }
                        pos p1 = {p.row + 1, p.col - 1};
                        if (p1.valid && (
                                (at(p1) != '.' && isWhite(p1)) ||
                                enPassant == p1.name)) {
                            ret.emplace_back(p, p1);
                        }
                        p1 = {p.row + 1, p.col + 1};
                        if (p1.valid && (
                                (at(p1) != '.' && isWhite(p1)) ||
                                enPassant == p1.name)) {
                            ret.emplace_back(p, p1);
                        }
                    }
                }
            }
        }
        return ret;
    }

    std::vector<move> getAllMoves() {
        std::vector<move> ret;
        auto addon = getPossibleBishopMoves();
        std::copy(addon.begin(), addon.end(), std::back_inserter(ret));
        addon = getPossibleKingMoves();
        std::copy(addon.begin(), addon.end(), std::back_inserter(ret));
        addon = getPossibleKnightMoves();
        std::copy(addon.begin(), addon.end(), std::back_inserter(ret));
        addon = getPossiblePawnMoves();
        std::copy(addon.begin(), addon.end(), std::back_inserter(ret));
        addon = getPossibleQueenMoves();
        std::copy(addon.begin(), addon.end(), std::back_inserter(ret));
        addon = getPossibleRockMoves();
        std::copy(addon.begin(), addon.end(), std::back_inserter(ret));
        return ret;
    }

private:
    bool underAttack(pos pos) {
        std::vector<move> allMoves = getAllMoves();
        return std::any_of(allMoves.begin(), allMoves.end(), [&pos](const auto &move) {
            return move.to == pos;
        });
    }

    bool addMoveIfOk(std::vector<move> &ret, const pos &oldpos, const pos &newpos) const {
        if (newpos.valid) {
            if (at(newpos) != '.' && isWhite(newpos) == isWhite(oldpos)) {
                return false;
            }
            ret.emplace_back(oldpos, newpos);
            bool okToContinue = (at(newpos) == '.');
            return okToContinue;
        }
        return false;
    }

    char at(const pos &pos) const {
        return board[pos.row][pos.col];
    }
    char &at(const pos &pos) {
        return board[pos.row][pos.col];
    }

    bool isWhite(const pos &pos) const {
        return at(pos) >= 'A' && at(pos) <= 'Z';
    }

    char normalize(const pos &pos) const {
        return isWhite(pos) ? at(pos) - 'A' + 'a' : at(pos);
    }

    std::array<std::array<char, 8>, 8> board;
    bool nextWhite, Kok = false, Qok = false, kok = false, qok = false;
    std::string enPassant;
    size_t halfmove, fullmove;
};