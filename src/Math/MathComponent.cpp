#include "MathComponent.hpp"

#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

#include "Application.hpp"

Point get_vector_coords(const Point& point_1, const Point& point_2) {
    float vec_x = point_2.x - point_1.x;
    float vec_y = point_2.y - point_1.y;
    Point vec(vec_x, vec_y);
    return vec;
}

// Функция проверяет принадлежит ли точка треугольнику
bool point_inside_triangle(const Triangle& triangle,
                           const Point& point_to_check) {
    // Векторный способ

    // Вычислеям координаты векторов всех сторон треугольника
    // vec1 - соединеят точки 0 и 1
    Point vec1 = get_vector_coords(triangle[0], triangle[1]);
    // vec2 - соединяет точки 1 и 2
    Point vec2 = get_vector_coords(triangle[1], triangle[2]);
    // vec3 - соединяет точки 0 и 2
    Point vec3 = get_vector_coords(triangle[2], triangle[0]);

    // Вычисляем координаты векторов от точек треугольника до проверяемой точки
    Point vec_check1 = get_vector_coords(triangle[0], point_to_check);
    Point vec_check2 = get_vector_coords(triangle[1], point_to_check);
    Point vec_check3 = get_vector_coords(triangle[2], point_to_check);

    // Вычисляем знаки смешанных произведений векторов
    float mixed_product1 = (vec1.x * vec_check1.y) - (vec1.y * vec_check1.x);
    float mixed_product2 = (vec2.x * vec_check2.y) - (vec2.y * vec_check2.x);
    float mixed_product3 = (vec3.x * vec_check3.y) - (vec3.y * vec_check3.x);

    // Если знаки смешанных произведений одинаковы, то точка принадлежит
    // треугольнику
    return (mixed_product1 > 0 && mixed_product2 > 0 && mixed_product3 > 0) ||
           (mixed_product1 < 0 && mixed_product2 < 0 && mixed_product3 < 0);
}

bool value_between_others(float value, float other1, float other2) {
    return ((std::min(other1, other2) <= value) &&
            (value <= std::max(other1, other2)));
}

// проверка, что треугольники одинаковые
bool triangle_are_same(const Triangle& triangle_1, const Triangle& triangle_2) {
    for (unsigned long long i = 0; i < 3; i++) {
        if ((triangle_1[i].x != triangle_2[i].x) ||
            (triangle_1[i].y != triangle_2[i].y)) {
            return false;
        }
    }
    return true;
}
// проверка, что два отрезка лежат на одной прямой
// если две прямые лежат на одной прямой, то их направляющие векторы
// коллинеарны, то есть параллельны или противоположно направлены
// в нвшем случае первой отрезок [fst_p_segment_1, scd_p_segment_2]
// и второй аналогично
bool two_segments_on_one_line(const Point& fst_p_segment_1,
                              const Point& scd_p_segment_1,
                              const Point& fst_p_segment_2,
                              const Point& scd_p_segment_2) {
    return ((fst_p_segment_1.x - fst_p_segment_2.x) *
            (scd_p_segment_1.y - scd_p_segment_2.y)) ==
           ((fst_p_segment_1.y - fst_p_segment_2.y) *
            (scd_p_segment_1.x - scd_p_segment_2.x));
}

bool point_already_recorded(const Intersection& intersection,
                            const Point& point_to_check) {
    for (unsigned long long i = 0; i < intersection.size(); i++) {
        if ((point_to_check.x == intersection[i].x) &&
            (point_to_check.y == intersection[i].y)) {
            return true;
        }
    }
    return false;
}

// возвращает точку пересечения двух прямых
// в этом случае прямые AB и CD
Point find_intersection_point_of_lines(const Point& p_A, const Point& p_B,
                                       const Point& p_C, const Point& p_D) {
    float new_x =
        ((p_A.x * p_B.y - p_A.y * p_B.x) * (p_C.x - p_D.x) -
         (p_A.x - p_B.x) * (p_C.x * p_D.y - p_C.y * p_D.x)) /
        ((p_A.x - p_B.x) * (p_C.y - p_D.y) - (p_A.y - p_B.y) * (p_C.x - p_D.x));
    float new_y =
        ((p_A.x * p_B.y - p_A.y * p_B.x) * (p_C.y - p_D.y) -
         (p_A.y - p_B.y) * (p_C.x * p_D.y - p_C.y * p_D.x)) /
        ((p_A.x - p_B.x) * (p_C.y - p_D.y) - (p_A.y - p_B.y) * (p_C.x - p_D.x));
    Point new_point(new_x, new_y);
    return new_point;
}

auto MathComponent::calculate_intersection(Triangle triangle_1,
                                           Triangle triangle_2)
    -> Intersection {
    Intersection intersection_points;

    // сортируем треугольники по x
    std::sort(triangle_1.begin(), triangle_1.end(),
              [](Point a, Point b) { return a.x < b.x; });
    std::sort(triangle_2.begin(), triangle_2.end(),
              [](Point a, Point b) { return a.x < b.x; });

    // если треугольники одинаковые, то вернем в качестве пересечения просто
    // один из треугольников
    if (triangle_are_same(triangle_1, triangle_2)) {
        return {triangle_1[0], triangle_1[1], triangle_1[2]};
    }

    // находим точки пересечения по прямым
    for (unsigned long long i = 0; i < 3; ++i) {
        for (unsigned long long j = 0; j < 3; ++j) {
            bool indicator = true;
            Point current_p_tr_1 = triangle_1[i];
            Point neighbor_p_tr_1 = triangle_1[(i + 1) % 3];
            Point current_p_tr_2 = triangle_2[j];
            Point neighbor_p_tr_2 = triangle_2[(j + 1) % 3];
            if (!two_segments_on_one_line(current_p_tr_1, current_p_tr_2,
                                          neighbor_p_tr_1, neighbor_p_tr_2)) {
                Point new_intersection_point = find_intersection_point_of_lines(
                    current_p_tr_1, neighbor_p_tr_1, current_p_tr_2,
                    neighbor_p_tr_2);
                if (!value_between_others(new_intersection_point.x,
                                          current_p_tr_1.x,
                                          neighbor_p_tr_1.x)) {
                    indicator = false;
                } else if (!value_between_others(new_intersection_point.y,
                                                 current_p_tr_1.y,
                                                 neighbor_p_tr_1.y)) {
                    indicator = false;
                } else if (!value_between_others(new_intersection_point.x,
                                                 current_p_tr_2.x,
                                                 neighbor_p_tr_2.x)) {
                    indicator = false;
                } else if (!value_between_others(new_intersection_point.y,
                                                 current_p_tr_2.y,
                                                 neighbor_p_tr_2.y)) {
                    indicator = false;
                }
                if (indicator) {
                    if (!point_already_recorded(intersection_points,
                                                new_intersection_point)) {
                        intersection_points.push_back(new_intersection_point);
                    }
                }
            }
        }
    }
    // одна из точек первого треугольника внутри второго
    for (unsigned long long i = 0; i < 3; i++) {
        if (point_inside_triangle(triangle_2, triangle_1[i])) {
            if (!point_already_recorded(intersection_points, triangle_1[i])) {
                intersection_points.push_back(triangle_1[i]);
            }
        }
    }
    // одна из точек второго треугольника внутри первого
    for (unsigned long long i = 0; i < 3; i++) {
        if (point_inside_triangle(triangle_1, triangle_2[i])) {
            if (!point_already_recorded(intersection_points, triangle_2[i])) {
                intersection_points.push_back(triangle_2[i]);
            }
        }
    }

    // соритруем точки пересечения по x
    std::sort(intersection_points.begin(), intersection_points.end(),
              [](Point a, Point b) { return a.x < b.x; });

    // добавила сортировку, чтобы при совпадающих значениях x сначала шло то, у
    // которого меньше y
    std::sort(intersection_points.begin(), intersection_points.end(),
              [](Point a, Point b) {
                  if (a.x == b.x) {
                      return a.y < b.y;
                  }
                  return a.x < b.x;
              });
    return intersection_points;
}

auto MathComponent::calculate_ratio(Triangle triangle_1, Triangle triangle_2)
    -> float {
    float max_x =
        std::max({std::abs(triangle_1[0].x), std::abs(triangle_1[1].x),
                  std::abs(triangle_1[2].x), std::abs(triangle_2[2].x),
                  std::abs(triangle_1[0].x), std::abs(triangle_1[1].x)});
    float max_y =
        std::max({std::abs(triangle_1[0].y), std::abs(triangle_1[1].y),
                  std::abs(triangle_1[2].y), std::abs(triangle_2[2].y),
                  std::abs(triangle_1[0].y), std::abs(triangle_1[1].y)});
    float ratio = 400 / std::max(max_y, max_x);
    return ratio;
}

void MathComponent::on_update() {
    // Считываешь треугольники из глобального хранилища
    auto triangle_1 = global_storage.get_triangle_1();
    auto triangle_2 = global_storage.get_triangle_2();
    // Находишь точки пересечения
    auto processed_intersection =
        calculate_intersection(triangle_1, triangle_2);
    // Записываешь в глобальное хранилище
    global_storage.set_intersection(processed_intersection);
    // Находишь множитель
    float processed_ratio = calculate_ratio(triangle_1, triangle_2);
    // Записываем в глабальное хранилище
    global_storage.set_ratio(processed_ratio);
}
