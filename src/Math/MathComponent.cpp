#include "MathComponent.hpp"
#include<vector>
#include<stdio.h>
#include <algorithm>
#include <iostream>

double cross_product(Point2f point_1, Point2f point_2, Point2f point_3) {
	double point_1_x = point_2.x - point_1.x;
	double point_1_y = point_2.y - point_1.y;
	double point_2_x = point_3.x - point_1.x;
	double point_2_y = point_3.y - point_1.y;
	return point_1_x * point_2_y - point_1_y * point_2_x;
}
// Функция для проверки принадлежности точки треугольнику
bool point_inside_triangle(Point2f triangle_point_1, Point2f triangle_point_2, Point2f triangle_point_3, Point2f point_to_check) {
	double cross_area_1 = cross_product(triangle_point_1, triangle_point_2, point_to_check);
	double cross_area_2 = cross_product(triangle_point_2, triangle_point_3, point_to_check);
	double cross_area_3 = cross_product(triangle_point_3, triangle_point_1, point_to_check);
	if ((cross_area_1 > 0 && cross_area_2 > 0 && cross_area_3 > 0) || (cross_area_1 < 0 && cross_area_2 < 0 && cross_area_3 < 0)) {
		return true;
	}
	return false;
}
auto MathComponent::calculate_intersection(Triangle triangle_1,
                                           Triangle triangle_2)
->Intersection
{
	std::vector<Point2f> Intersection_points;
	for (int i = 0;i < 2;++i)
	{
    	for (int j = 0;j < 2;++j)
		{		
			bool indicator = true;
			float first_point_x_1 = triangle_1[i].x;
			float first_point_y_1 = triangle_1[i].y;
			float second_point_x_1 = triangle_1[(i+1)%3].x;
			float second_point_y_2 = triangle_1[(i+1)%3].y;
			float first_point_x_2 = triangle_2[j].x;
			float first_point_y_2 = triangle_2[j].y;
			float second_point_x_2 = triangle_2[(j + 1) % 3].x;
			float second_point_y_2 = triangle_2[(j + 1) % 3].y;
			if ((first_point_x_1 - second_point_x_1) * (first_point_y_2 - second_point_y_2) - (first_point_y_1 - second_point_y_2) * (first_point_x_2 - second_point_x_2) != 0)
			{
				float new_x = ((first_point_x_1 * second_point_y_2 - first_point_y_1 * second_point_x_1) * (first_point_x_2 - second_point_x_2) - (first_point_x_1 - second_point_x_1) * (first_point_x_2 * second_point_y_2 - first_point_y_2 * second_point_x_2)) / ((first_point_x_1 - second_point_x_1) * (first_point_y_2 - second_point_y_2) - (first_point_y_1 - second_point_y_2) * (first_point_x_2 - second_point_x_2));
				float new_y = ((first_point_x_1 * second_point_y_2 - first_point_y_1 * second_point_x_1) * (first_point_y_2 - second_point_y_2) - (first_point_y_1 - second_point_y_2) * (first_point_x_2 * second_point_y_2 - first_point_y_2 * second_point_x_2)) / ((first_point_x_1 - second_point_x_1) * (first_point_y_2 - second_point_y_2) - (first_point_y_1 - second_point_y_2) * (first_point_x_2 - second_point_x_2));
				if (!(std::min(first_point_x_1, second_point_x_1) <= new_x <= std::max(first_point_x_1, second_point_x_1)))
				{
					indicator = false;
				}else if (!(std::min(first_point_y_1, second_point_y_2) <= new_y <= std::max(first_point_y_1, second_point_y_2)))
				{
					indicator = false;
				}else if (!(std::min(first_point_x_2, first_point_x_2) <= new_x <= std::max(first_point_x_2, second_point_x_2)))
				{
					indicator = false;
				}else if (!(std::min(first_point_y_2, second_point_y_2) <= new_y <= std::max(first_point_y_2, second_point_y_2)))
				{
					indicator = false;
				}
				if (indicator)
				{
					Point2f new_point;
					new_point.x = new_x;
					new_point.y = new_y;
					Intersection_points.push_back(new_point);
				}
			}
		}
	}
	for (int i = 0; i < 3;++i)
	{
		if (point_inside_triangle(triangle_2[0], triangle_2[1], triangle_2[2], triangle_1[i]))
		{
			Intersection_points.push_back(triangle_1[i]);
		}
	}
	for (int i = 0; i < 3;++i)
	{
		if (point_inside_triangle(triangle_1[0], triangle_1[1], triangle_1[2], triangle_2[i]))
		{
			Intersection_points.push_back(triangle_2[i]);
		}
	}
    return {Intersection_points};
}

auto MathComponent::calculate_ratio(Triangle triangle_1, Triangle triangle_2)
    -> float {
    float max_x = std::max({std::abs(triangle_1[0].x), std::abs(triangle_1[1].x),std::abs(triangle_1[2].x), std::abs(triangle_2[2].x),std::abs(triangle_1[0].x), std::abs(triangle_1[1].x)});
	float max_y = std::max({std::abs(triangle_1[0].y), std::abs(triangle_1[1].y),std::abs(triangle_1[2].y), std::abs(triangle_2[2].y),std::abs(triangle_1[0].y), std::abs(triangle_1[1].y)});
	float ratio = 400/std::max(max_y, max_x);
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
