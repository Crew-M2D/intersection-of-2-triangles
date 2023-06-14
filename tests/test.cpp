#include <gtest/gtest.h>
#include <vcruntime.h>

#include <Application.hpp>

#include "GraphicsComponent.hpp"
#include "MathComponent.hpp"

using namespace std;

auto Equation(Point2f point_1, Point2f point_2) -> Point2f {
    float k = (point_2.y - point_1.y) / (point_2.x - point_1.x);
    float b = point_1.y - point_1.x * k;
    return Point2f(k, b);
}

auto Findpoint(Point2f eq_1, Point2f eq_2) -> Point2f {
    float det = (-1) * eq_1.y + eq_2.x;
    float det_x = eq_1.y - eq_2.y;
    float det_y = (-1) * eq_1.x * eq_2.y + eq_2.x * eq_1.y;
    return Point2f(det_x / det, det_y / det);
}

//-----------------------------------------------------------TESTS---------------------------------------------------------------------------

// No
// Shape----------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, NoIntersection1) {
    MathComponent result;
    Shape trian1{Point2f(1, 7), Point2f(2, 2), Point2f(8, 1)};
    Shape trian2{Point2f(4, 9), Point2f(5, 4), Point2f(7, 11)};
    Shape intersection = result.calculate_intersection(trian1, trian2);

    EXPECT_EQ(intersection.size(), 0);
}

TEST(MathComponentTest, NoIntersection2) {
    MathComponent result;
    Shape trian1{Point2f(1, 1), Point2f(1, 5), Point2f(5, 10)};
    Shape trian2{Point2f(2, 1), Point2f(7, 1), Point2f(6, 12)};
    Shape intersection = result.calculate_intersection(trian1, trian2);

    EXPECT_EQ(intersection.size(), 0);
}

TEST(MathComponentTest, NoIntersection3) {
    MathComponent result;
    Shape trian1{Point2f(-5, 1), Point2f(-2, -7), Point2f(3, -2)};
    Shape trian2{Point2f(-4, 3), Point2f(3, 6), Point2f(6, -2)};
    Shape intersection = result.calculate_intersection(trian1, trian2);

    EXPECT_EQ(intersection.size(), 0);
}

TEST(MathComponentTest, NoIntersection4) {
    MathComponent result;
    Shape trian1{Point2f(-8, -1), Point2f(-7, -5), Point2f(-2, -1)};
    Shape trian2{Point2f(-4, 2), Point2f(-1, 6), Point2f(1, -2)};
    Shape intersection = result.calculate_intersection(trian1, trian2);

    EXPECT_EQ(intersection.size(), 0);
}

// One
// Point----------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, OnePoint1) {
    MathComponent result;
    Shape trian1{Point2f(4, 3), Point2f(3, 10), Point2f(12, 7)};
    Shape trian2{Point2f(4, 3), Point2f(11, 1), Point2f(11, 3)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(4, 3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, OnePoint2) {
    MathComponent result;
    Shape trian1{Point2f(2, 4), Point2f(10, 4), Point2f(11, 8)};
    Shape trian2{Point2f(3, 2), Point2f(6, 4), Point2f(9, 1)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(6, 4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, OnePoint3) {
    MathComponent result;
    Shape trian1{Point2f(-4, 4), Point2f(7, 6), Point2f(0, 0)};
    Shape trian2{Point2f(0, 0), Point2f(5, 1), Point2f(2, -4)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(0, 0)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, OnePoint4) {
    MathComponent result;
    Shape trian1{Point2f(-2, -2), Point2f(7, 3), Point2f(-1, -5)};
    Shape trian2{Point2f(2.5, -1.5), Point2f(7, -2), Point2f(8, -3)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(2.5, -1.5)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_FLOAT_EQ(intersection[i].x, answer[i].x);
            EXPECT_FLOAT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Two
// Points---------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, TwoPoints1) {
    MathComponent result;
    Shape trian1{Point2f(-6, 2), Point2f(-4, 2), Point2f(6, -3)};
    Shape trian2{Point2f(-4, 2), Point2f(6, -3), Point2f(2, 5)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, 2), Point2f(6, -3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, TwoPoints2) {
    MathComponent result;
    Shape trian1{Point2f(-5, 3), Point2f(-1, 1), Point2f(7, 3)};
    Shape trian2{Point2f(3, 2), Point2f(3, -4), Point2f(11, 4)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(3, 2), Point2f(7, 3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, TwoPoints3) {
    MathComponent result;
    Shape trian1{Point2f(-3, 2), Point2f(-3, -1), Point2f(4, 6)};
    Shape trian2{Point2f(0, 2), Point2f(2, 4), Point2f(2, -3)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(0, 2), Point2f(2, 4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Three
// Points------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, ThreePoints1) {
    MathComponent result;
    Shape trian1{Point2f(2, 3), Point2f(8, 11), Point2f(11, 2)};
    Shape trian2{Point2f(2, 3), Point2f(8, 11), Point2f(11, 2)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(2, 3), Point2f(8, 11), Point2f(11, 2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints2) {
    MathComponent result;
    Shape trian1{Point2f(4, 6), Point2f(7, 12), Point2f(10, 3)};
    Shape trian2{Point2f(3, 4), Point2f(9, 1), Point2f(12, 7)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(6, 5), Point2f(9, 6), Point2f(10, 3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints3) {
    MathComponent result;
    Shape trian1{Point2f(-4, -2), Point2f(2, -5), Point2f(5, 1)};
    Shape trian2{Point2f(-1, -1), Point2f(2, 0), Point2f(3, -3)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-1, -1), Point2f(2, 0), Point2f(3, -3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints4) {
    MathComponent result;
    Shape trian1{Point2f(-5, 2), Point2f(-4, -3), Point2f(5, 3)};
    Shape trian2{Point2f(-5, 2), Point2f(3, -4), Point2f(9, 0)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-5, 2), Point2f(-1, -1), Point2f(2, 1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints5) {
    MathComponent result;
    Shape trian1{Point2f(-3, 6), Point2f(6, 0), Point2f(6, 4)};
    Shape trian2{Point2f(-3, 6), Point2f(-3, -2), Point2f(6, 4)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-3, 6), Point2f(3, 2), Point2f(6, 4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints6) {
    MathComponent result;
    Shape trian1{Point2f(-5, -2), Point2f(-2, 6), Point2f(8, -2)};
    Shape trian2{Point2f(-4, -2), Point2f(3, 2), Point2f(8, -2)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, -2), Point2f(3, 2), Point2f(8, -2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints7) {
    MathComponent result;
    Shape trian1{Point2f(-5, -3), Point2f(-3, 5), Point2f(3, 1)};
    Shape trian2{Point2f(-4, 1), Point2f(-1, 1), Point2f(0, 3)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, 1), Point2f(-1, 1), Point2f(0, 3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints8) {
    MathComponent result;
    Shape trian1{Point2f(2, 2), Point2f(6, 2), Point2f(6, 11)};
    Shape trian2{Point2f(5, 5), Point2f(7, 1), Point2f(8, 8)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(5, 5), Point2f(6, 3), Point2f(6, 6)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints9) {
    MathComponent result;
    Shape trian1{Point2f(2, 1), Point2f(5, 8), Point2f(11, 2)};
    Shape trian2{Point2f(5, 4), Point2f(5, 10), Point2f(11, 4)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(5, 4), Point2f(5, 8), Point2f(9, 4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_10) {
    MathComponent result;
    Shape trian1{Point2f(-6, -2), Point2f(-2, -3), Point2f(2, 3)};
    Shape trian2{Point2f(-5, 4), Point2f(-3, -2), Point2f(1, 5)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Findpoint(Equation(Point2f(-5, 4), Point2f(-3, 2)),
                               Equation(Point2f(-6, -2), Point2f(2, 3))),
                     Point2f(-3, -2),
                     Findpoint(Equation(Point2f(-3, -2), Point2f(1, 5)),
                               Equation(Point2f(-6, -2), Point2f(2, 3)))};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_11) {
    MathComponent result;
    Shape trian1{Point2f(-6, -1), Point2f(2, 6), Point2f(1, -6)};
    Shape trian2{Point2f(-6, 7), Point2f(-3, 2), Point2f(1.5, 0)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Findpoint(Equation(Point2f(-3, 2), Point2f(1.5, 0)),
                               Equation(Point2f(-6, -1), Point2f(2, 6))),
                     Findpoint(Equation(Point2f(-6, 7), Point2f(1.5, 0)),
                               Equation(Point2f(-6, -1), Point2f(2, 6))),
                     Point2f(1.5, 0)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_12) {
    MathComponent result;
    Shape trian1{Point2f(-7, -2), Point2f(2, 5), Point2f(5, -2)};
    Shape trian2{Point2f(-4, 2), Point2f(2, 5), Point2f(5, -2)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Findpoint(Equation(Point2f(-7, -2), Point2f(2, 5)),
                               Equation(Point2f(-4, 2), Point2f(5, -2))),
                     Point2f(2, 5), Point2f(5, -2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_13) {
    MathComponent result;
    Shape trian1{Point2f(-9, 2), Point2f(-6, 7), Point2f(2, -2)};
    Shape trian2{Point2f(-6, 2), Point2f(-5, 4), Point2f(-4, 3)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-6, 2), Point2f(-5, 4), Point2f(-4, 3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_14) {
    MathComponent result;
    Shape trian1{Point2f(1, -6), Point2f(2, 3), Point2f(8, 8)};
    Shape trian2{Point2f(2, 3), Point2f(3, 1), Point2f(3, 5)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(2, 3), Point2f(3, 1),
                     Findpoint(Equation(Point2f(2, 3), Point2f(8, 8)),
                               Equation(Point2f(3, 1), Point2f(3, 5)))};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_15) {
    MathComponent result;
    Shape trian1{Point2f(-5, -4), Point2f(-2, -5), Point2f(2, 2)};
    Shape trian2{Point2f(1, 2), Point2f(2, 2), Point2f(2, 1)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Findpoint(Equation(Point2f(-5, -4), Point2f(2, 2)),
                               Equation(Point2f(1, 2), Point2f(2, 1))),
                     Findpoint(Equation(Point2f(-2, -5), Point2f(2, 2)),
                               Equation(Point2f(1, 2), Point2f(2, 1))),
                     Point2f(2, 2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Four
// Points-------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, FourPoints_1) {
    MathComponent result;
    Shape trian1{Point2f(-8, -3), Point2f(-3, 7), Point2f(1, -5)};
    Shape trian2{Point2f(-5, 3), Point2f(-3.5, -4), Point2f(9, -4)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-5, 3), Point2f(-3.5, -4), Point2f(-1, 1),
                     Point2f(float(2.0 / 3.0), -4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_FLOAT_EQ(intersection[i].x, answer[i].x);
            EXPECT_FLOAT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FourPoints_2) {
    MathComponent result;
    Shape trian1{Point2f(4, 7), Point2f(6, 5), Point2f(10, 9)};
    Shape trian2{Point2f(2, 2), Point2f(6, 6), Point2f(11, 1)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(5.5, 5.5), Point2f(6, 5), Point2f(6, 6),
                     Point2f(6.5, 5.5)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_FLOAT_EQ(intersection[i].x, answer[i].x);
            EXPECT_FLOAT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FourPoints_3) {
    MathComponent result;
    Shape trian1{Point2f(-9, 1), Point2f(-3, 9), Point2f(-1, -7)};
    Shape trian2{Point2f(-7, 1), Point2f(-4, 6), Point2f(4, -4)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-7, 1), Point2f(-4, 6),
                     Findpoint(Equation(Point2f(-4, 6), Point2f(4, -4)),
                               Equation(Point2f(-3, 9), Point2f(-1, -7))),
                     Findpoint(Equation(Point2f(-7, 1), Point2f(4, -4)),
                               Equation(Point2f(-3, 9), Point2f(-1, -7)))};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FourPoints_4) {
    MathComponent result;
    Shape trian1{Point2f(-6, 1), Point2f(3, 2), Point2f(2, -4)};
    Shape trian2{Point2f(-2, 7), Point2f(4, 3), Point2f(2, -1)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Findpoint(Equation(Point2f(-6, 1), Point2f(3, 2)),
                               Equation(Point2f(-2, 7), Point2f(2, -1))),
                     Point2f(2, -1),
                     Findpoint(Equation(Point2f(4, 3), Point2f(2, -1)),
                               Equation(Point2f(3, 2), Point2f(2, -4))),
                     Point2f(3, 2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FourPoints_5) {
    MathComponent result;
    Shape trian1{Point2f(-5, 3), Point2f(-4, 7), Point2f(9, -4)};
    Shape trian2{Point2f(-5, -4), Point2f(-3, -6), Point2f(7, 8)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Findpoint(Equation(Point2f(-5, 3), Point2f(9, -4)),
                               Equation(Point2f(-5, -4), Point2f(7, 8))),
                     Findpoint(Equation(Point2f(-5, 3), Point2f(9, -4)),
                               Equation(Point2f(-3, -6), Point2f(7, 8))),
                     Findpoint(Equation(Point2f(-4, 7), Point2f(9, -4)),
                               Equation(Point2f(-5, -4), Point2f(7, 8))),
                     Findpoint(Equation(Point2f(-4, 7), Point2f(9, -4)),
                               Equation(Point2f(-3, -6), Point2f(7, 8)))};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Five
// Points-------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, FivePoints_1) {
    MathComponent result;
    Shape trian1{Point2f(-6, -6), Point2f(0, 6), Point2f(6, -6)};
    Shape trian2{Point2f(-5, 6), Point2f(0, -9), Point2f(5, 6)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-3, 0), Point2f(-1, -6), Point2f(0, 6),
                     Point2f(1, -6), Point2f(3, 0)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FivePoints_2) {
    MathComponent result;
    Shape trian1{Point2f(-8, -4), Point2f(-7, 4), Point2f(8, 4)};
    Shape trian2{Point2f(-6, -2), Point2f(2, 6), Point2f(6, -2)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-6, -2), Point2f(-4, -2), Point2f(0, 4),
                     Point2f(3, 4), Point2f(4, 2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FivePoints_3) {
    MathComponent result;
    Shape trian1{Point2f(-7, -3), Point2f(0, 4), Point2f(7, -3)};
    Shape trian2{Point2f(-4, -3), Point2f(0, 7), Point2f(4, -3)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, -3), Point2f(-2, 2), Point2f(0, 4),
                     Point2f(2, 2), Point2f(4, -3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FivePoints_4) {
    MathComponent result;
    Shape trian1{Point2f(-6, -2), Point2f(-4, 4), Point2f(8, 5)};
    Shape trian2{Point2f(-3, 2), Point2f(1, 8), Point2f(6, 1)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-3, 2),
                     Findpoint(Equation(Point2f(-4, 4), Point2f(8, 5)),
                               Equation(Point2f(-3, 2), Point2f(1, 8))),
                     Findpoint(Equation(Point2f(-6, -2), Point2f(8, 5)),
                               Equation(Point2f(-3, 2), Point2f(6, 1))),
                     Findpoint(Equation(Point2f(-4, 4), Point2f(8, 5)),
                               Equation(Point2f(1, 8), Point2f(6, 1))),
                     Findpoint(Equation(Point2f(-6, 2), Point2f(8, 5)),
                               Equation(Point2f(1, 8), Point2f(6, 1)))};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Six
// Points--------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, SixPoints_1) {
    MathComponent result;
    Shape trian1{Point2f(-6, 1), Point2f(0, 7), Point2f(6, 1)};
    Shape trian2{Point2f(-6, 5), Point2f(0, -1), Point2f(6, 5)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, 3), Point2f(-2, 1), Point2f(-2, 5),
                     Point2f(2, 1),  Point2f(2, 5),  Point2f(4, 3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, SixPoints_2) {
    MathComponent result;
    Shape trian1{Point2f(3, 2), Point2f(4, 5), Point2f(6, 3)};
    Shape trian2{Point2f(3, 4), Point2f(5, 5), Point2f(5, 2)};
    Shape intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Findpoint(Equation(Point2f(3, 4), Point2f(5, 2)),
                               Equation(Point2f(3, 2), Point2f(4, 5))),
                     Findpoint(Equation(Point2f(3, 4), Point2f(5, 5)),
                               Equation(Point2f(3, 2), Point2f(4, 5))),
                     Findpoint(Equation(Point2f(3, 4), Point2f(5, 5)),
                               Equation(Point2f(4, 5), Point2f(6, 3))),
                     Findpoint(Equation(Point2f(3, 2), Point2f(6, 3)),
                               Equation(Point2f(3, 4), Point2f(5, 2))),
                     Findpoint(Equation(Point2f(3, 2), Point2f(6, 3)),
                               Equation(Point2f(5, 2), Point2f(5, 5))),
                     Point2f(5, 4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

//==========================================================OTHER=TESTS======================================================================

TEST(MathComponentTest, Shapes1) {
    MathComponent result;
    Shape shape1{Point2f(-12, 3), Point2f(-3, 3), Point2f(-1, -7), Point2f(2, 1), Point2f(2, -4)};
    Shape shape2{Point2f(-8, 3), Point2f(-5, 7), Point2f(-1, -7), Point2f(6, 4), Point2f(10, -3)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-8, 3), Point2f(-3, 3), Point2f(-1, -7),
                     Point2f(2, 1),  Point2f(2, -4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes2) {
    MathComponent result;
    Shape shape1{Point2f(-8, 1), Point2f(-5, -7), Point2f(4, 6), Point2f(10, -6)};
    Shape shape2{Point2f(-4, -3), Point2f(-3, 0), Point2f(-3, -6), Point2f(2, 4), Point2f(5, 3), Point2f(7, -2)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-4, -3), Point2f(-3, 0), Point2f(-3, -6),
                     Point2f(2, 4), Point2f(5, 3), Point2f(7, -2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes3) {
    MathComponent result;
    Shape shape1{Point2f(-7, 5), Point2f(-4, -1), Point2f(1, 8), Point2f(1, -3), Point2f(7, -3), Point2f(9, 6), Point2f(10, -1)};
    Shape shape2{Point2f(-11, 2), Point2f(-4, -7), Point2f(6, -2), Point2f(9, 6)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-6, 3), Point2f(-4, -1), Point2f(1, -3),
                     Point2f(4, -3),  Point2f(6, -2), Point2f(9, 6)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes4) {
    MathComponent result;
    Shape shape1{Point2f(-13, -4), Point2f(-3, -4), Point2f(-2, -3), Point2f(7, 3)};
    Shape shape2{Point2f(-11, 2), Point2f(-7, 5), Point2f(-5, -3), Point2f(1, 3), Point2f(6,-3), Point2f(7,-1)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-8, 0), Point2f(-5, 3), Point2f(-3, 4), Point2f(-2,-3),  Point2f(1, 3),  Point2f(4, 1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes5) {
    MathComponent result;
    Shape shape1{Point2f(-10, 3), Point2f(-6, 7), Point2f(0, -5), Point2f(5, 7), Point2f(12, 1)};
    Shape shape2{Point2f(-5, 0), Point2f(-4, 4), Point2f(0, 5), Point2f(5, 5), Point2f(10, -5)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-5, 0), Point2f(-4, 4), Point2f(0, 5), Point2f(4, -3),  Point2f(5, 5),  Point2f(8, -1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes6) {
    MathComponent result;
    Shape shape1{Point2f(-9, -5), Point2f(-9, 1), Point2f(-2, 8), Point2f(5, -5), Point2f(5, 1)};
    Shape shape2{Point2f(-9, 1), Point2f(-7, -3), Point2f(-4, 6), Point2f(-1, 7), Point2f(5, -5), Point2f(5, 1)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-9, -1), Point2f(-7, -3), Point2f(-4, -5), Point2f(-4, 6),  Point2f(5, -5),  Point2f(5, 1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes7) {
    MathComponent result;
    Shape shape1{Point2f(-10, 1), Point2f(-10, 4), Point2f(-8, -3), Point2f(-4, 6), Point2f(0, -5), Point2f(2, -4), Point2f(2, 6), Point2f(6, -2), Point2f(6, 2)};
    Shape shape2{Point2f(-10, 1), Point2f(-8, -3), Point2f(2, -4), Point2f(4, 8), Point2f(6, 2)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-10, 1), Point2f(-8, -3), Point2f(2, -4), Point2f(4, 8),  Point2f(6, 2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes8) {
    MathComponent result;
    Shape shape1{Point2f(-6, -1), Point2f(-6, 3), Point2f(0, -4), Point2f(0, 6), Point2f(6, -1), Point2f(6, 3)};
    Shape shape2{Point2f(-6, 0), Point2f(-3, 6), Point2f(-2, -4), Point2f(4, -4), Point2f(4, -1)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-6, 0), Point2f(-4, -2), Point2f(-4, 4), Point2f(-2, 5),  Point2f(0, -4), Point2f(4, -2), Point2f(4, -1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes9) {
    MathComponent result;
    Shape shape1{Point2f(-3, -4), Point2f(-1, -7), Point2f(0, 5), Point2f(3, -5), Point2f(5, 7), Point2f(8, 5)};
    Shape shape2{Point2f(-3, -4), Point2f(-1, -7), Point2f(2, 5), Point2f(3, -5)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-3, -4), Point2f(-1, -7), Point2f(2, 5), Point2f(3, -5)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes10) {
    MathComponent result;
    Shape shape1{Point2f(-5, 5), Point2f(-5, -2), Point2f(-1, -6), Point2f(2, 3), Point2f(4, -5), Point2f(8, -1)};
    Shape shape2{Point2f(-8, -2), Point2f(0, 6), Point2f(8, -6)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-5, -2), Point2f(-5, 1), Point2f(-4, -3),
                     Point2f(-2, 4),  Point2f(2, 3), Point2f(4, -5), Point2f(6, -3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes11) {
    MathComponent result;
    Shape shape1{Point2f(-7, -1), Point2f(-3, 5), Point2f(3, 5), Point2f(4, 3), Point2f(5, -4), Point2f(5, 1)};
    Shape shape2{Point2f(-5, 2), Point2f(0, 5), Point2f(1, -3), Point2f(4, 3), Point2f(5, -2)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-5, 2), Point2f(0, 5), Point2f(1, -3),
                     Point2f(4, 3), Point2f(5, -2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes12) {
    MathComponent result;
    Shape shape1{Point2f(-5, -4), Point2f(-4, -8), Point2f(-2, 5), Point2f(0, 8), Point2f(2, 5), Point2f(4, -8), Point2f(5, -4)};
    Shape shape2{Point2f(-5, -4), Point2f(-5, 2), Point2f(3, 2), Point2f(4, -8), Point2f(4, -1)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-5, -4), Point2f(-3, 2), Point2f(3, 2),
                     Point2f(4, -8), Point2f(4, -1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes13) {
    MathComponent result;
    Shape shape1{Point2f(-3, -1), Point2f(0, -3), Point2f(0, 5), Point2f(6, 2)};
    Shape shape2{Point2f(-2, 1), Point2f(-1, -1), Point2f(0, 2), Point2f(2, 0)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-2, 1), Point2f(-1, -1), Point2f(0, 2), Point2f(2, 0)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes14) {
    MathComponent result;
    Shape shape1{Point2f(-2, 8), Point2f(1, -1), Point2f(1, 9), Point2f(4, 2), Point2f(4, 6)};
    Shape shape2{Point2f(-1, 5), Point2f(0, 2), Point2f(3, 2), Point2f(3, 9)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-1, 5), Point2f(0, 2), Point2f(2, 8),
                     Point2f(3, 2), Point2f(3, 7)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes15) {
    MathComponent result;
    Shape shape1{Point2f(-5, -5), Point2f(-4, -2), Point2f(-3, -7), Point2f(-2, 2), Point2f(-1, -6), Point2f(3, 6), Point2f(5, 2)};
    Shape shape2{Point2f(-7, 8), Point2f(0, 6), Point2f(3, 6), Point2f(5, 0), Point2f(5, 2), Point2f(5, 4)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-5, -5), Point2f(-4, -6), Point2f(-4, -2),
                     Point2f(-2, 2), Point2f(2, -2), Point2f(3, 6), Point(5, 2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes16) {
    MathComponent result;
    Shape shape1{Point2f(-5, 5), Point2f(-3, 8), Point2f(-2, 2), Point2f(3, 8), Point2f(6, 6)};
    Shape shape2{Point2f(-4, 1), Point2f(-1, 7), Point2f(1, 0), Point2f(3, 8)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-3, 3), Point2f(-2, 2), Point2f(-1, 7), Point2f(2, 4), Point2f(3, 8)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes17) {
    MathComponent result;
    Shape shape1{Point2f(-8, -3), Point2f(-7, 2), Point2f(-3, 5), Point2f(1, -3), Point2f(1, 1)};
    Shape shape2{Point2f(-7, 2), Point2f(-6, -2), Point2f(-2, -4), Point2f(-1, 3), Point2f(4, -2)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-7, 2), Point2f(-6, -2), Point2f(-4, -3), Point2f(-1, 3), Point2f(1, -3), Point2f(1, 1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes18) {
    MathComponent result;
    Shape shape1{Point2f(-6, -3), Point2f(-3, -4), Point2f(-2, 3), Point2f(6, -1)};
    Shape shape2{Point2f(-5, 4), Point2f(-3, -4), Point2f(-1, 6), Point2f(3, 6), Point2f(4, 3)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-4, 0), Point2f(-3, -4), Point2f(-2, 3), Point2f(2, 1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes19) {
    MathComponent result;
    Shape shape1{Point2f(-4, -3), Point2f(-4, 4), Point2f(2, 5), Point2f(5, -1)};
    Shape shape2{Point2f(-4, 4), Point2f(-3, -1), Point2f(1, -1), Point2f(2, 1)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-4, 4), Point2f(-3, -1), Point2f(1, -1), Point2f(2, 1)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes20) {
    MathComponent result;
    Shape shape1{Point2f(-4, -5), Point2f(-4, 4), Point2f(1, 4), Point2f(2, -5), Point2f(4, 2), Point2f(6, -3)};
    Shape shape2{Point2f(-5, 2), Point2f(-4, -2), Point2f(-3, 4), Point2f(2, -4), Point2f(4, 2), Point2f(10, -2)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-4, -2), Point2f(-4, 4), Point2f(-3, 4), Point2f(2, -4), Point2f(4, 2), Point2f(6, -3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes21) {
    MathComponent result;
    Shape shape1{Point2f(-3, -2), Point2f(-2, -3), Point2f(-2, 2), Point2f(2, 4), Point2f(4, 3)};
    Shape shape2{Point2f(-2, 2), Point2f(0, -6), Point2f(0, 3), Point2f(3, 0)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-2, 2), Point2f(-1, -2), Point2f(0, 3), Point2f(2, 1)};
    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes22) {
    MathComponent result;
    Shape shape1{Point2f(-7, -3), Point2f(-7, 2), Point2f(-5, -6), Point2f(-4, 5), Point2f(-2, 3)};
    Shape shape2{Point2f(-7, 0), Point2f(-6, -3), Point2f(-2, -3), Point2f(-2, 5)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-7, 0), Point2f(-6, -3), Point2f(-4, -3), Point2f(-3, 4), Point2f(-2, 3)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes23) {
    MathComponent result;
    Shape shape1{Point2f(-4, -2), Point2f(-3, -4), Point2f(-3, -2), Point2f(5, -6)};
    Shape shape2{Point2f(1, 0), Point2f(3, 2), Point2f(5, -6), Point2f(8, -1)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(5, -6)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes25) {
    MathComponent result;
    Shape shape1{Point2f(-4, 4), Point2f(-3, 4), Point2f(-1, -8), Point2f(-1, 2), Point2f(2, -7)};
    Shape shape2{Point2f(-3, 0), Point2f(1, 4), Point2f(3, -6), Point2f(5, -2), Point2f(5, 2)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-3, 0), Point2f(-1, 2), Point2f(1, -4)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes26) {
    MathComponent result;
    Shape shape1{Point2f(-5, -3), Point2f(-5, -6), Point2f(-1, -7), Point2f(2, -7)};
    Shape shape2{Point2f(-4, -4), Point2f(0, -6), Point2f(1, -1)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-4, -4), Point2f(0, -6)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes27) {
    MathComponent result;
    Shape shape1{Point2f(-9, -4), Point2f(-4, 4), Point2f(-1, 5), Point2f(3, 4), Point2f(3, -2)};
    Shape shape2{Point2f(-9, -4), Point2f(-4, 4), Point2f(-1, 5), Point2f(3, 4), Point2f(3, -2)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-9, -4), Point2f(-4, 4), Point2f(-1, 5), Point2f(3, 4), Point2f(3, -2)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, Shapes28) {
    MathComponent result;
    Shape shape1{Point2f(-6, -3), Point2f(-4, 2), Point2f(-2, -7), Point2f(-1, 6), Point2f(5, 4), Point2f(6, -6)};
    Shape shape2{Point2f(-4, -5), Point2f(-2, -7), Point2f(2, 5), Point2f(5, 4), Point2f(6, -6)};
    Shape intersection = result.calculate_intersection(shape1, shape2);
    vector answer = {Point2f(-4, -5), Point2f(-2, -7), Point2f(2, 5), Point2f(5, 4), Point2f(6, -6)};

    if (intersection.size() == answer.size()) {
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}
//--------------------------------------------------------TESTS-EXECUTING--------------------------------------------------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}