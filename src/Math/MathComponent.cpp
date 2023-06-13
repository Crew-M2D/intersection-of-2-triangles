#include "MathComponent.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <vector>

#include "Application.hpp"


auto get_vector_coords(const Point& point_1, const Point& point_2) -> Point {
    float vec_x = point_2.x - point_1.x;
    float vec_y = point_2.y - point_1.y;
    Point vec(vec_x, vec_y);
    return vec;
}

// Функция проверяет принадлежит ли точка треугольнику
auto point_inside_shape(const Shape& triangle, const Point& point_to_check)
    -> bool {
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

auto value_between_others(float value, float other1, float other2) -> bool {
    return ((std::min(other1, other2) <= value) &&
            (value <= std::max(other1, other2)));
}

// проверка, что полигоны одинаковые
auto polygons_are_same(const Shape& polygon_1, const Shape& polygon_2)
    -> bool {
    if (polygon_1.size()!=polygon_2.size()) {
        return false;
    }
    for (std::uint64_t i = 0; i < polygon_1.size(); i++) {
        if ((polygon_1[i].x != polygon_2[i].x) ||
            (polygon_1[i].y != polygon_2[i].y)) {
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
auto two_segments_on_one_line(const Point& fst_p_segment_1,
                              const Point& scd_p_segment_1,
                              const Point& fst_p_segment_2,
                              const Point& scd_p_segment_2) -> bool {
    return ((fst_p_segment_1.x - fst_p_segment_2.x) *
            (scd_p_segment_1.y - scd_p_segment_2.y)) ==
           ((fst_p_segment_1.y - fst_p_segment_2.y) *
            (scd_p_segment_1.x - scd_p_segment_2.x));
}

auto point_already_recorded(const Shape& intersection,
                            const Point& point_to_check) -> bool {
    for (std::uint64_t i = 0; i < intersection.size(); i++) {
        if ((point_to_check.x == intersection[i].x) &&
            (point_to_check.y == intersection[i].y)) {
            return true;
        }
    }
    return false;
}

// возвращает точку пересечения двух прямых
// в этом случае прямые AB и CD
auto find_intersection_point_of_lines(const Point& p_A, const Point& p_B,
                                      const Point& p_C, const Point& p_D)
    -> Point {
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

auto MathComponent::calculate_intersection(Shape polygon_1, Shape polygon_2)
    -> Shape {
    Shape intersection_points;

    // сортируем фигуры
    polygon_1.sort();
    polygon_2.sort();

    // если треугольники одинаковые, то вернем в качестве пересечения просто
    // один из треугольников
    if (polygons_are_same(polygon_1, polygon_2)) {
        return polygon_1;
    }

    // находим точки пересечения по прямым
    for (std::uint64_t i = 0; i < 3; ++i) {
        for (std::uint64_t j = 0; j < 3; ++j) {
            bool indicator = true;
            Point current_p_tr_1 = polygon_1[i];
            Point neighbor_p_tr_1 = polygon_1[(i + 1) % 3];
            Point current_p_tr_2 = polygon_2[j];
            Point neighbor_p_tr_2 = polygon_2[(j + 1) % 3];
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
                        intersection_points.add(new_intersection_point);
                    }
                }
            }
        }
    }
    // одна из точек первого треугольника внутри второго
    for (std::uint64_t i = 0; i < 3; i++) {
        if (point_inside_shape(polygon_2, polygon_1[i])) {
            if (!point_already_recorded(intersection_points, polygon_1[i])) {
                intersection_points.add(polygon_1[i]);
            }
        }
    }
    // одна из точек второго треугольника внутри первого
    for (std::uint64_t i = 0; i < 3; i++) {
        if (point_inside_shape(polygon_1, polygon_2[i])) {
            if (!point_already_recorded(intersection_points, polygon_2[i])) {
                intersection_points.add(polygon_2[i]);
            }
        }
    }

    // соритруем
    intersection_points.sort();
    return intersection_points;
}

auto MathComponent::calculate_ratio(const Shape& polygon_1, const Shape& polygon_2)
    -> float {
    // вычисление максимальных и минимальных x и y
    float max_x = std::max(polygon_1.get_max_x(), polygon_2.get_max_x());
    float min_x = std::max(polygon_1.get_min_x(), polygon_2.get_min_x());
    float max_y = std::max(polygon_1.get_max_y(), polygon_2.get_max_y());
    float min_y = std::max(polygon_1.get_min_y(), polygon_2.get_min_y());
    float ratio = 2.0F / (std::max(max_y, max_x) - std::min(min_y, min_x));
    return ratio;
}

void MathComponent::on_update() {
    // Считываешь треугольники из глобального хранилища
    auto triangle_1 = global_storage.get_polygon_1();
    auto triangle_2 = global_storage.get_polygon_2();
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
