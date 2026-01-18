#include "AEVEC2OVERLOAD.hpp"

AEVec2 operator+(const AEVec2& lhs, const AEVec2& rhs) {
    AEVec2 aev = { lhs.x + rhs.x, lhs.y + rhs.y };
    return aev;
}

AEVec2 operator-(const AEVec2& lhs, const AEVec2& rhs) {
    AEVec2 aev = { lhs.x - rhs.x, lhs.y - rhs.y };
    return aev;
}

AEVec2 operator*(const AEVec2& lhs, const AEVec2& rhs) {
    AEVec2 aev = { lhs.x * rhs.x, lhs.y * rhs.y };
    return aev;
}

AEVec2 operator/(const AEVec2& lhs, const AEVec2& rhs) {
    AEVec2 aev = { lhs.x / rhs.x, lhs.y / rhs.y };
    return aev;
}

AEVec2 abs(const AEVec2& lhs) {
    AEVec2 aev = { std::sqrt(lhs.x * lhs.x),  std::sqrt(lhs.y * lhs.y) };
    return aev;
}