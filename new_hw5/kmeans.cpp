#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>

// g++ -std=c++17 -O2 -o kmeans kmeans.cpp

using namespace std;

struct Point {
    double x, y;
    int cluster;
    
    Point(double x = 0, double y = 0) : x(x), y(y), cluster(-1) {}
};

class KMeans {
private:
    vector<Point> points;
    vector<Point> centers;
    int k;
    double tolerance;
    int maxIterations;
    int iterations;
    
public:
    KMeans(int k, double tolerance = 1e-4, int maxIterations = 100)
        : k(k), tolerance(tolerance), maxIterations(maxIterations), iterations(0) {}
    
    double distance(const Point& p1, const Point& p2) const {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return sqrt(dx * dx + dy * dy);
    }
    
    void initializeCenters() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, points.size() - 1);
        
        centers.clear();
        for (int i = 0; i < k; i++) {
            int idx = dis(gen);
            centers.push_back(points[idx]);
            centers[i].cluster = i;
        }
        cout << "Initialized " << k << " cluster centers randomly.\n";
    }
    
    void assignPoints() {
        for (auto& p : points) {
            double minDist = numeric_limits<double>::max();
            int nearestCluster = 0;
            
            for (int i = 0; i < k; i++) {
                double d = distance(p, centers[i]);
                if (d < minDist) {
                    minDist = d;
                    nearestCluster = i;
                }
            }
            p.cluster = nearestCluster;
        }
    }
    
    bool updateCenters() {
        vector<Point> newCenters(k, Point(0, 0));
        vector<int> counts(k, 0);
        
        for (const auto& p : points) {
            newCenters[p.cluster].x += p.x;
            newCenters[p.cluster].y += p.y;
            counts[p.cluster]++;
        }
        
        for (int i = 0; i < k; i++) {
            if (counts[i] > 0) {
                newCenters[i].x /= counts[i];
                newCenters[i].y /= counts[i];
            }
        }
        
        double maxShift = 0;
        for (int i = 0; i < k; i++) {
            double shift = distance(centers[i], newCenters[i]);
            maxShift = max(maxShift, shift);
        }
        
        centers = newCenters;
        
        return maxShift < tolerance;
    }
    
    void fit() {
        if (points.empty()) {
            cerr << "Error: No data points to cluster.\n";
            return;
        }
        
        initializeCenters();
        cout << "\nStarting K-Means clustering...\n";
        cout << "Tolerance: " << tolerance << "\n";
        cout << "Max iterations: " << maxIterations << "\n\n";
        
        for (iterations = 0; iterations < maxIterations; iterations++) {
            assignPoints();
            bool converged = updateCenters();
            
            double totalInertia = calculateInertia();
            cout << "Iteration " << setw(3) << iterations + 1 << " | "
                 << "Inertia: " << fixed << setprecision(4) << totalInertia << "\n";
            
            if (converged) {
                cout << "\nConverged after " << iterations + 1 << " iterations!\n";
                return;
            }
        }
        
        cout << "\nReached maximum iterations (" << maxIterations << ").\n";
    }
    
    double calculateInertia() const {
        double inertia = 0;
        for (const auto& p : points) {
            inertia += distance(p, centers[p.cluster]) * 
                      distance(p, centers[p.cluster]);
        }
        return inertia;
    }
    
    void addPoint(double x, double y) {
        points.push_back(Point(x, y));
    }
    
    void generateSyntheticData(int numPoints) {
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> dis(0, 1);
        
        vector<pair<double, double>> clusterCenters = {
            {2, 2}, {8, 8}, {8, 2}
        };
        
        int pointsPerCluster = numPoints / k;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < pointsPerCluster; j++) {
                double x = clusterCenters[i % clusterCenters.size()].first + 
                          dis(gen) * 0.5;
                double y = clusterCenters[i % clusterCenters.size()].second + 
                          dis(gen) * 0.5;
                addPoint(x, y);
            }
        }
    }
    
    void saveAsImage(const string& filename) {
        // PPM format (simple, no external library needed)
        int width = 800;
        int height = 800;
        int margin = 50;
        
        // Find data bounds
        double minX = numeric_limits<double>::max();
        double maxX = numeric_limits<double>::lowest();
        double minY = numeric_limits<double>::max();
        double maxY = numeric_limits<double>::lowest();
        
        for (const auto& p : points) {
            minX = min(minX, p.x);
            maxX = max(maxX, p.x);
            minY = min(minY, p.y);
            maxY = max(maxY, p.y);
        }
        
        double rangeX = maxX - minX + 1;
        double rangeY = maxY - minY + 1;
        
        // Create image buffer
        vector<vector<vector<int>>> image(height, vector<vector<int>>(width, vector<int>(3, 255)));
        
        // Colors for clusters
        vector<vector<int>> colors = {
            {255, 0, 0},      // Red
            {0, 255, 0},      // Green
            {0, 0, 255},      // Blue
            {255, 255, 0},    // Yellow
            {255, 0, 255},    // Magenta
            {0, 255, 255}     // Cyan
        };
        
        // Draw data points
        for (const auto& p : points) {
            int px = margin + (int)((p.x - minX) / rangeX * (width - 2 * margin));
            int py = height - margin - (int)((p.y - minY) / rangeY * (height - 2 * margin));
            
            if (px >= 0 && px < width && py >= 0 && py < height) {
                int colorIdx = p.cluster % colors.size();
                image[py][px] = colors[colorIdx];
                
                // Draw small circle around point
                for (int dx = -2; dx <= 2; dx++) {
                    for (int dy = -2; dy <= 2; dy++) {
                        if (dx*dx + dy*dy <= 4) {
                            int nx = px + dx;
                            int ny = py + dy;
                            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                                image[ny][nx] = colors[colorIdx];
                            }
                        }
                    }
                }
            }
        }
        
        // Draw cluster centers as larger stars
        for (int i = 0; i < k; i++) {
            int cx = margin + (int)((centers[i].x - minX) / rangeX * (width - 2 * margin));
            int cy = height - margin - (int)((centers[i].y - minY) / rangeY * (height - 2 * margin));
            
            if (cx >= 0 && cx < width && cy >= 0 && cy < height) {
                // Draw cross pattern for centers
                for (int r = 3; r <= 8; r++) {
                    if (cx + r < width) image[cy][cx + r] = {0, 0, 0};
                    if (cx - r >= 0) image[cy][cx - r] = {0, 0, 0};
                    if (cy + r < height) image[cy + r][cx] = {0, 0, 0};
                    if (cy - r >= 0) image[cy - r][cx] = {0, 0, 0};
                }
                // Center point in white
                image[cy][cx] = {255, 255, 255};
            }
        }
        
        // Write PPM file
        ofstream file(filename, ios::binary);
        file << "P3\n";
        file << width << " " << height << "\n";
        file << "255\n";
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                file << image[y][x][0] << " " << image[y][x][1] << " " << image[y][x][2] << "  ";
            }
            file << "\n";
        }
        file.close();
        
        cout << "\nImage saved as: " << filename << "\n";
        cout << "You can convert it to PNG using: convert " << filename << " output.png\n";
    }
    
    void displayResults() const {
        cout << "\n=== CLUSTERING RESULTS ===\n";
        cout << "Total iterations: " << iterations + 1 << "\n";
        cout << "Final inertia: " << fixed << setprecision(4) << calculateInertia() << "\n\n";
        
        for (int i = 0; i < k; i++) {
            cout << "Cluster " << i << " center: ("
                 << fixed << setprecision(2) << centers[i].x << ", "
                 << centers[i].y << ")\n";
            
            int count = 0;
            for (const auto& p : points) {
                if (p.cluster == i) count++;
            }
            cout << "  Points: " << count << "\n";
        }
    }
    
    const vector<Point>& getPoints() const {
        return points;
    }
    
    const vector<Point>& getCenters() const {
        return centers;
    }
};

int main() {
    int k = 3;
    KMeans kmeans(k, 1e-4, 100);
    
    cout << "Generating 300 synthetic data points...\n";
    kmeans.generateSyntheticData(300);
    
    kmeans.fit();
    kmeans.displayResults();
    
    // Save results as image
    kmeans.saveAsImage("kmeans_result.ppm");
    
    cout << "\nSample point assignments (first 10 points):\n";
    const auto& points = kmeans.getPoints();
    for (int i = 0; i < min(10, (int)points.size()); i++) {
        cout << "Point (" << fixed << setprecision(2) << points[i].x << ", "
             << points[i].y << ") -> Cluster " << points[i].cluster << "\n";
    }
    
    return 0;
}