#include "../include/Enemy_service.h"
#include <cmath>
#include <unistd.h>
Enemy_service::Enemy_service(Game_state* state_): state(state_) {}
/*!
 * @brief checks if the end point of the path is visited
 * @param x current point x-parameter
 * @param y current point y-parameter
 * @param end end point
 * @return true if end point is visited, false otherwise
 */
bool Enemy_service::check_if_end(const long long& x, const long long& y, const std::pair<size_t,size_t>& end) {
    return x == end.first && y == end.second;
}

/*!
 * @brief visiting current point if it's possible
 * @param x current point x-parameter
 * @param y current point y-parameter
 * @param visited vector of already visited points
 * @param points a map of points available
 * @param edge_points current edge points used bt wave-algorithm
 * @return true if possible to visit, false otherwise
 */
bool Enemy_service::visit(const long long& x, const long long& y, std::vector<bool>& visited, const matrix<bool>& points,
           std::vector<std::pair<size_t , size_t>>& edge_points) {
    if(x < 0 || x >= points.get_columns() || y < 0 || y > points.get_rows() || visited[x * points.get_columns() + y])
        return false;
    if(points[x][y]) {
        visited[x * points.get_columns() + y] = true;
        edge_points.emplace_back(std::make_pair(x,y));
    }
    return true;
}

/*!
 * @brief initializing function for wave-algorithm
 * @param map matrix of the current level map
 * @return matrix of bool values representing the current level map
 */
matrix<bool> Enemy_service::init_for_shortest_path(const matrix<Cell*>& map){
    matrix<bool> points;
    for(int i = 0; i < map.get_rows(); ++i)
    {
        std::vector<bool> row;
        for(int j = 0; j < map.get_columns(); ++j)
            row.emplace_back(map[i][j]->if_movable_to());
        points.emplace_back_row(row);
    }
    return points;
}
/*!
 * @brief builds the shortest path from start to end on the planar graph
 * @param map matrix of current level map
 * @param start start point
 * @param end end point
 * @return vector of integer values representing number of steps that needs to be taken from the start point to any point on the map
 */
std::vector<int> Enemy_service::make_shortest_path(const matrix<Cell*>& map,const std::pair<size_t, size_t>& start,
                                                         const std::pair<size_t, size_t>& end)
{
    size_t columns = map.get_columns();
    size_t rows = map.get_rows();
    std::vector<std::pair<size_t , size_t>> edge_points = {start};
    std::vector<bool> visited(columns * rows, false);
    std::vector<int> wave_lengths(columns * rows, -1);
    wave_lengths[start.first * columns + start.second] = 0;
    matrix<bool> points = init_for_shortest_path(map);
    points[start.first][start.second] = true;
    points[end.first][end.second] = true;
    visited[start.first * columns + start.second] = true;
    int wave_count = 0;
    while(edge_points.size() != 0){
        ++wave_count;
        ptrdiff_t diff = edge_points.end() - edge_points.begin();
        std::vector<std::pair<size_t , size_t>> new_edge_points;
        for(size_t i = 0; i < diff; ++i)
        {
            size_t curr_pos_x = edge_points[i].first;
            size_t curr_pos_y = edge_points[i].second;
            if(check_if_end(curr_pos_x, curr_pos_y, end))
                return wave_lengths;
            else{
                if(visit(curr_pos_x, curr_pos_y - 1, visited, points, new_edge_points))
                    wave_lengths[curr_pos_x * columns + curr_pos_y - 1] = wave_count;
                if(visit(curr_pos_x - 1, curr_pos_y, visited, points, new_edge_points))
                    wave_lengths[(curr_pos_x-1) * columns + curr_pos_y] = wave_count;
                if(visit(curr_pos_x + 1, curr_pos_y, visited, points, new_edge_points))
                    wave_lengths[(curr_pos_x + 1) * columns + curr_pos_y] = wave_count;
                if(visit(curr_pos_x, curr_pos_y + 1, visited, points, new_edge_points))
                    wave_lengths[curr_pos_x * columns + curr_pos_y + 1] = wave_count;
            }
        }
        edge_points.clear();
        edge_points = new_edge_points;
    }
    return wave_lengths;
}
/*!
 * @brief checks if current point if within the boundaries of a map
 * @param x x-parameter of current point
 * @param y y-parameter of current point
 * @param columns number of columns in the map
 * @param rows number of rows in the map
 * @return true if within boundaries, false otherwise
 */
bool Enemy_service::check_if_within_boundaries(const size_t& x, const size_t& y, const size_t& columns, const size_t& rows)
{
    return x > 0 && x < columns && y > 0 && y < rows;
}
/*!
 * @brief build the shortest path consisting of points sequence from start to end
 * @param wave_lengths vector of steps to be taken from start to any point on the map
 * @param start start point
 * @param end end point
 * @param columns number of columns in the map
 * @param rows number of rows in the map
 * @return vector of pair which represents a path from start to end
 */
std::vector<std::pair<size_t, size_t>> Enemy_service::get_shortest_path(const std::vector<int>& wave_lengths,const std::pair<size_t, size_t>& start,
                                                         const std::pair<size_t, size_t>& end, const size_t& columns, const size_t& rows)
{
    std::vector<std::pair<size_t, size_t>> sequence{};
    std::pair<size_t, size_t> curr_point = end;
    size_t curr_len = wave_lengths[curr_point.first * columns + curr_point.second];
    if(curr_len == -1)
        return sequence;
    else{
        sequence.push_back(end);
        while(curr_len != 0) {
            if (check_if_within_boundaries(curr_point.first - 1, curr_point.second, columns, rows)) {
                if (wave_lengths[(curr_point.first - 1) * columns + curr_point.second] == curr_len - 1) {
                    curr_len -= 1;
                    curr_point = {curr_point.first - 1, curr_point.second};
                    sequence.push_back(curr_point);
                    continue;
                }
            }
            if(check_if_within_boundaries(curr_point.first + 1, curr_point.second, columns, rows)) {
                if (wave_lengths[(curr_point.first + 1) * columns + curr_point.second] == curr_len - 1) {
                    curr_len -= 1;
                    curr_point = {curr_point.first + 1, curr_point.second};
                    sequence.push_back(curr_point);
                    continue;
                }
            }
            if(check_if_within_boundaries(curr_point.first, curr_point.second - 1, columns, rows)) {
                if (wave_lengths[(curr_point.first) * columns + curr_point.second - 1] == curr_len - 1) {
                    curr_len -= 1;
                    curr_point = {curr_point.first, curr_point.second - 1};
                    sequence.push_back(curr_point);
                    continue;
                }
            }
            if(check_if_within_boundaries(curr_point.first, curr_point.second + 1, columns, rows)) {
                if (wave_lengths[(curr_point.first) * columns + curr_point.second + 1] == curr_len - 1) {
                    curr_len -= 1;
                    curr_point = {curr_point.first, curr_point.second + 1};
                    sequence.push_back(curr_point);
                    continue;
                }
            }
        }
    }
    return sequence;
}

/*!
 * @brief check if the enemy is in the triggering radius
 * @param first coordinates of the first creature
 * @param second coordinates of the second creature
 * @return true if in the radius, false otherwise
 */
bool Enemy_service::check_if_within_triggering_radius(const std::pair<size_t, size_t> &first,
                                                      const std::pair<size_t, size_t> &second) {
    float dist = sqrt(pow((int)first.first - (int)second.first, 2) + pow((int)first.second - (int)second.second, 2));
    if(dist <= 2)
        return true;
    else
        return false;
}