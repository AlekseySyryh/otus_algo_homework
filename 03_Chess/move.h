#pragma once

class move {
public:
    move(pos from, pos to) : from(from), to(to) {
        valid = (from != to);
        pawnConvert = false;
        std::ostringstream oss;
        oss << from.name << to.name;
        name = oss.str();
    }

    move(pos from, pos to, char newFigure) : move(from, to) {
        pawnConvert = true;
        this->newFigure = newFigure;
        std::ostringstream oss;
        oss << from.name << to.name << newFigure;
        name = oss.str();
    }

    move(std::string move) : from(move.substr(0, 2)), to(move.substr(2, 2)), name(move) {
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
            if (from.colc != other.from.colc) {
                return from.colc < other.from.colc;
            }
            return pawnConvert && other.pawnConvert && newFigure < other.newFigure;
        }
        if (to.rowc != other.to.rowc) {
            return to.rowc < other.to.rowc;
        }
        if (to.colc != other.to.colc) {
            return to.colc < other.to.colc;
        }
        return pawnConvert && other.pawnConvert && newFigure < other.newFigure;
    }

    pos from, to;
    bool valid, pawnConvert;
    char newFigure;
    std::string name;
};