#pragma once

class move {
public:
    move(std::string move) : from(move.substr(0, 2)), to(move.substr(2, 2)) {
        valid = (from != to);
        if (move.length() == 5) {
            pawnConvert = true;
            newFigure = move[4];
        } else {
            pawnConvert = false;
        }
    }

    bool operator==(const move &other) const {
        return from == other.from &&
               to == other.to &&
               valid == other.valid &&
               pawnConvert == other.pawnConvert &&
               (!pawnConvert || newFigure == other.newFigure);

    }

    bool operator<(const move &other) const {
        if (from != other.from) {
            if (from.rowc != other.from.rowc) {
                return from.rowc < other.from.rowc;
            }
            return from.colc < other.from.colc;
        }
        if (to.rowc != other.to.rowc) {
            return to.rowc < other.to.rowc;
        }
        return to.colc < other.to.colc;
    }

    pos from, to;
    bool valid, pawnConvert;
    char newFigure;
};