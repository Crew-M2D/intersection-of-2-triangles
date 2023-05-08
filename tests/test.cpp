#include <gtest/gtest.h>
#include <vcruntime.h>

#include <Application.hpp>

#include "GraphicsComponent.hpp"
#include "MathComponent.hpp"


using namespace std;

struct MathComponentTest {
    MathComponent* result;
    Triangle* trian1;
    Triangle* trian2;
    Intersection* intersection;
    vector<float>* answer;

    MathComponentTest() {
        result = new MathComponent;
        trian1 = new Triangle;
        trian2 = new Triangle;
        intersection = new Intersection;
        answer = new vector<float>;
    }

    virtual ~MathComponentTest() {
        delete result;
        delete trian1;
        delete trian2;
        delete intersection;
        delete answer;
    }
};

Point2f Equation(Point2f point_1, Point2f point_2) {
    float k = (point_2.y - point_1.y) / (point_2.x - point_1.x);
    float b = point_1.y - point_1.x * k;
    return Point2f(k, b);
}

Point2f Findpoint(Point2f eq_1, Point2f eq_2) {
    float det = (-1) * eq_1.y + eq_2.x;
    float det_x = eq_1.y - eq_2.y;
    float det_y = (-1) * eq_1.x * eq_2.y + eq_2.x * eq_1.y;
    return Point2f(det_x / det, det_y / det);
}

//-----------------------------------------------------------TESTS---------------------------------------------------------------------------

// No
// Intersection----------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, NoIntersection_1) {
    MathComponent result;
    Triangle trian1{Point2f(1, 7), Point2f(2, 2), Point2f(8, 1)};
    Triangle trian2{Point2f(4, 9), Point2f(5, 4), Point2f(7, 11)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector<float> answer = {};

    EXPECT_EQ(answer.size(), 0);
}

TEST(MathComponentTest, NoIntersection_2) {
    MathComponent result;
    Triangle trian1{Point2f(1, 1), Point2f(1, 5), Point2f(5, 10)};
    Triangle trian2{Point2f(2, 1), Point2f(7, 1), Point2f(6, 12)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector<float> answer = {};

    EXPECT_EQ(answer.size(), 0);
}

TEST(MathComponentTest, NoIntersection_3) {
    MathComponent result;
    Triangle trian1{Point2f(-5, 1), Point2f(-2, -7), Point2f(3, -2)};
    Triangle trian2{Point2f(-4, 3), Point2f(3, 6), Point2f(6, -2)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector<float> answer = {};

    EXPECT_EQ(answer.size(), 0);
}

TEST(MathComponentTest, NoIntersection_4) {
    MathComponent result;
    Triangle trian1{Point2f(-8, -1), Point2f(-7, -5), Point2f(-2, -1)};
    Triangle trian2{Point2f(-4, 2), Point2f(-1, 6), Point2f(1, -2)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector<float> answer = {};

    EXPECT_EQ(answer.size(), 0);
}

// One
// Point----------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, OnePoint_1) {
    MathComponent result;
    Triangle trian1{Point2f(4, 3), Point2f(3, 10), Point2f(12, 7)};
    Triangle trian2{Point2f(4, 3), Point2f(11, 1), Point2f(11, 3)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(4, 3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, OnePoint_2) {
    MathComponent result;
    Triangle trian1{Point2f(2, 4), Point2f(10, 4), Point2f(11, 8)};
    Triangle trian2{Point2f(3, 2), Point2f(6, 4), Point2f(9, 1)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(6, 4)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, OnePoint_3) {
    MathComponent result;
    Triangle trian1{Point2f(-4, 4), Point2f(7, 6), Point2f(0, 0)};
    Triangle trian2{Point2f(0, 0), Point2f(5, 1), Point2f(2, -4)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(0, 0)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, OnePoint_4) {
    MathComponent result;
    Triangle trian1{Point2f(-2, -2), Point2f(7, 3), Point2f(-1, -5)};
    Triangle trian2{Point2f(2.5, -1.5), Point2f(7, -2), Point2f(8, -3)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(2.5, -1.5)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_FLOAT_EQ(intersection[i].x, answer[i].x);
            EXPECT_FLOAT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Two
// Points---------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, TwoPoints_1) {
    MathComponent result;
    Triangle trian1{Point2f(-6, 2), Point2f(-4, 2), Point2f(6, -3)};
    Triangle trian2{Point2f(-4, 2), Point2f(6, -3), Point2f(2, 5)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, 2), Point2f(6, -3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, TwoPoints_2) {
    MathComponent result;
    Triangle trian1{Point2f(-5, 3), Point2f(-1, 1), Point2f(7, 3)};
    Triangle trian2{Point2f(3, 2), Point2f(3, -4), Point2f(11, 4)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(3, 2), Point2f(7, 3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, TwoPoints_3) {
    MathComponent result;
    Triangle trian1{Point2f(-3, 2), Point2f(-3, -1), Point2f(4, 6)};
    Triangle trian2{Point2f(0, 2), Point2f(2, 4), Point2f(2, -3)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(0, 2), Point2f(2, 4)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Three
// Points------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, ThreePoints_1) {
    MathComponent result;
    Triangle trian1{Point2f(2, 3), Point2f(8, 11), Point2f(11, 2)};
    Triangle trian2{Point2f(2, 3), Point2f(8, 11), Point2f(11, 2)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(2, 3), Point2f(8, 11), Point2f(11, 2)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_2) {
    MathComponent result;
    Triangle trian1{Point2f(4, 6), Point2f(7, 12), Point2f(10, 3)};
    Triangle trian2{Point2f(3, 4), Point2f(9, 1), Point2f(12, 7)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(6, 5), Point2f(9, 6), Point2f(10, 3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_3) {
    MathComponent result;
    Triangle trian1{Point2f(-4, -2), Point2f(2, -5), Point2f(5, 1)};
    Triangle trian2{Point2f(-1, -1), Point2f(2, 0), Point2f(3, -3)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-1, -1), Point2f(2, 0), Point2f(3, -3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_4) {
    MathComponent result;
    Triangle trian1{Point2f(-5, 2), Point2f(-4, -3), Point2f(5, 3)};
    Triangle trian2{Point2f(-5, 2), Point2f(3, -4), Point2f(9, 0)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-5, 2), Point2f(-1, -1), Point2f(2, 1)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_5) {
    MathComponent result;
    Triangle trian1{Point2f(-3, 6), Point2f(6, 0), Point2f(6, 4)};
    Triangle trian2{Point2f(-3, 6), Point2f(-3, -2), Point2f(6, 4)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-3, 6), Point2f(3, 2), Point2f(6, 4)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_6) {
    MathComponent result;
    Triangle trian1{Point2f(-5, -2), Point2f(-2, 6), Point2f(8, -2)};
    Triangle trian2{Point2f(-4, -2), Point2f(3, 2), Point2f(8, -2)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, -2), Point2f(3, 2), Point2f(8, -2)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_7) {
    MathComponent result;
    Triangle trian1{Point2f(-5, -3), Point2f(-3, 5), Point2f(3, 1)};
    Triangle trian2{Point2f(-4, 1), Point2f(-1, 1), Point2f(0, 3)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, 1), Point2f(-1, 1), Point2f(0, 3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_8) {
    MathComponent result;
    Triangle trian1{Point2f(2, 2), Point2f(6, 2), Point2f(6, 11)};
    Triangle trian2{Point2f(5, 5), Point2f(7, 1), Point2f(8, 8)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(5, 5), Point2f(6, 3), Point2f(6, 6)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, ThreePoints_9) {
    MathComponent result;
    Triangle trian1{Point2f(2, 1), Point2f(5, 8), Point2f(11, 2)};
    Triangle trian2{Point2f(5, 4), Point2f(5, 10), Point2f(11, 4)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(5, 4), Point2f(5, 8), Point2f(9, 4)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
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
    Triangle trian1{Point2f(-8, -3), Point2f(-3, 7), Point2f(1, -5)};
    Triangle trian2{Point2f(-5, 3), Point2f(-3.5, -4), Point2f(9, -4)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-5, 3), Point2f(-3.5, -4), Point2f(-1, 1),
                     Point2f(float(2.0 / 3.0), -4)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_FLOAT_EQ(intersection[i].x, answer[i].x);
            EXPECT_FLOAT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FourPoints_2) {
    MathComponent result;
    Triangle trian1{Point2f(4, 7), Point2f(6, 5), Point2f(10, 9)};
    Triangle trian2{Point2f(2, 2), Point2f(6, 6), Point2f(11, 1)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(5.5, 5.5), Point2f(6, 5), Point2f(6, 6),
                     Point2f(6.5, 5.5)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_FLOAT_EQ(intersection[i].x, answer[i].x);
            EXPECT_FLOAT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

// Five
// Points-------------------------------------------------------------------------------------------------------------------------------

TEST(MathComponentTest, FivePoints_1) {
    MathComponent result;
    Triangle trian1{Point2f(-6, -6), Point2f(0, 6), Point2f(6, -6)};
    Triangle trian2{Point2f(-5, 6), Point2f(0, -9), Point2f(5, 6)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-3, 0), Point2f(-1, -6), Point2f(0, 6),
                     Point2f(1, -6), Point2f(3, 0)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FivePoints_2) {
    MathComponent result;
    Triangle trian1{Point2f(-8, -4), Point2f(-7, 4), Point2f(8, 4)};
    Triangle trian2{Point2f(-6, -2), Point2f(2, 6), Point2f(6, -2)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-6, -2), Point2f(-4, -2), Point2f(0, 4),
                     Point2f(3, 4), Point2f(4, 2)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            EXPECT_EQ(intersection[i].x, answer[i].x);
            EXPECT_EQ(intersection[i].y, answer[i].y);
        }

    } else {
        EXPECT_EQ(intersection.size(), answer.size());
    }
}

TEST(MathComponentTest, FivePoints_3) {
    MathComponent result;
    Triangle trian1{Point2f(-7, -3), Point2f(0, 4), Point2f(7, -3)};
    Triangle trian2{Point2f(-4, -3), Point2f(0, 7), Point2f(4, -3)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, -3), Point2f(-2, 2), Point2f(0, 4),
                     Point2f(2, 2), Point2f(4, -3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
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
    Triangle trian1{Point2f(-6, 1), Point2f(0, 7), Point2f(6, 1)};
    Triangle trian2{Point2f(-6, 5), Point2f(0, -1), Point2f(6, 5)};
    Intersection intersection = result.calculate_intersection(trian1, trian2);
    vector answer = {Point2f(-4, 3), Point2f(-2, 1), Point2f(-2, 5),
                     Point2f(2, 1),  Point2f(2, 5),  Point2f(4, 3)};

    if (intersection.size() == answer.size()) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
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
