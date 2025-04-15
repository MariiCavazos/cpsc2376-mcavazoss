#include "MixedFraction.h"

MixedFraction::MixedFraction(int whole, int n, int d) : Fraction(n, d), whole(whole) {}

MixedFraction::MixedFraction(const Fraction& fraction) : Fraction(fraction) {
    whole = fraction.getNumerator() / fraction.getDenominator();
    int newNum = fraction.getNumerator() % fraction.getDenominator();
    if (newNum < 0) newNum = -newNum;
    setNumerator(newNum);
}

std::ostream& operator<<(std::ostream& out, const MixedFraction& mf) {
    if (mf.whole != 0) {
        out << mf.whole;
        if (mf.getNumerator() != 0) out << " " << mf.getNumerator() << "/" << mf.getDenominator();
    }
    else {
        out << mf.getNumerator() << "/" << mf.getDenominator();
    }
    return out;
}
