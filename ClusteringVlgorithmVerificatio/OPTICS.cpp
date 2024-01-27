#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

struct Point {
    double x, y;
    bool processed;
    bool is_core_point;
    double reachability_distance;
    int cluster_id;

    Point(double x, double y) : x(x), y(y), processed(false), is_core_point(false),
                                reachability_distance(std::numeric_limits<double>::infinity()), cluster_id(-1) {}
};

double euclideanDistance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

std::vector<Point> getNeighbors(const std::vector<Point>& points, const Point& point, double epsilon) {
    std::vector<Point> neighbors;
    for (const Point& other : points) {
        if (euclideanDistance(point, other) <= epsilon) {
            neighbors.push_back(other);
        }
    }
    return neighbors;
}

void expandClusterOrder(std::vector<Point>& points, Point& point, double epsilon, int minPts, std::vector<Point>& orderedList, int clusterId) {
    std::vector<Point> seeds = getNeighbors(points, point, epsilon);

    point.processed = true;
    point.cluster_id = clusterId;
    orderedList.push_back(point);

    for (Point& seed : seeds) {
        if (!seed.processed) {
            seed.processed = true;
            seed.cluster_id = clusterId;

            std::vector<Point> seedNeighbors = getNeighbors(points, seed, epsilon);
            if (seedNeighbors.size() >= minPts) {
                for (Point& neighbor : seedNeighbors) {
                    seeds.push_back(neighbor);
                }
            }
        }

        if (seed.cluster_id == -1) {
            seed.cluster_id = clusterId;
            orderedList.push_back(seed);
        }
    }
}

void optics(std::vector<Point>& points, double epsilon, int minPts) {
    int clusterId = 0;

    for (Point& point : points) {
        if (!point.processed) {
            std::vector<Point> neighbors = getNeighbors(points, point, epsilon);

            point.processed = true;

            if (neighbors.size() >= minPts) {
                point.is_core_point = true;
                std::vector<Point> orderedList;
                expandClusterOrder(points, point, epsilon, minPts, orderedList, clusterId);

                // Print the cluster
                std::cout << "Cluster " << clusterId << ": ";
                for (const Point& p : orderedList) {
                    std::cout << "(" << p.x << ", " << p.y << ") ";
                }
                std::cout << std::endl;

                clusterId++;
            }
        }
    }
}

int main() {
    // Example usage
    std::vector<Point> points = {
            {1.0, 2.0},
            {1.5, 1.8},
            {5.0, 8.0},
            {8.0, 8.0},
            {1.0, 0.6},
            {9.0, 11.0},
            {8.0, 2.0},
            {10.0, 2.0},
            {9.0, 3.0}
    };

    double epsilon = 2.0;
    int minPts = 2;

    optics(points, epsilon, minPts);

    return 0;
}
