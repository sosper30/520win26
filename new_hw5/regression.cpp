#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <numeric>

using namespace std;

struct DataPoint {
    double x, y;
    double predicted;
    
    DataPoint(double x = 0, double y = 0) : x(x), y(y), predicted(0) {}
};

class LinearRegression {
private:
    vector<DataPoint> data;
    double slope;        // m in y = mx + b
    double intercept;    // b in y = mx + b
    double rSquared;
    
public:
    LinearRegression() : slope(0), intercept(0), rSquared(0) {}
    
    // Add a data point
    void addPoint(double x, double y) {
        data.push_back(DataPoint(x, y));
    }
    
    // Calculate mean of a vector
    double calculateMean(const vector<double>& values) const {
        if (values.empty()) return 0;
        double sum = accumulate(values.begin(), values.end(), 0.0);
        return sum / values.size();
    }
    
    // Fit the linear regression model using Least Squares method
    void fit() {
        if (data.size() < 2) {
            cerr << "Error: Need at least 2 data points to fit a line.\n";
            return;
        }
        
        // Extract x and y values
        vector<double> xValues, yValues;
        for (const auto& point : data) {
            xValues.push_back(point.x);
            yValues.push_back(point.y);
        }
        
        // Calculate means
        double meanX = calculateMean(xValues);
        double meanY = calculateMean(yValues);
        
        // Calculate slope: m = Σ((x - meanX)(y - meanY)) / Σ((x - meanX)²)
        double numerator = 0;
        double denominator = 0;
        
        for (size_t i = 0; i < data.size(); i++) {
            double xDiff = xValues[i] - meanX;
            double yDiff = yValues[i] - meanY;
            numerator += xDiff * yDiff;
            denominator += xDiff * xDiff;
        }
        
        if (denominator == 0) {
            cerr << "Error: Cannot fit line (all x values are identical).\n";
            return;
        }
        
        slope = numerator / denominator;
        
        // Calculate intercept: b = meanY - m * meanX
        intercept = meanY - slope * meanX;
        
        // Calculate predictions and R²
        calculateMetrics();
        
        cout << "Linear regression model fitted successfully.\n";
        cout << "Model: y = " << fixed << setprecision(4) << slope << "x + " 
             << intercept << "\n\n";
    }
    
    // Calculate predicted values and R² score
    void calculateMetrics() {
        vector<double> yValues;
        vector<double> residuals;
        
        for (auto& point : data) {
            point.predicted = slope * point.x + intercept;
            yValues.push_back(point.y);
            residuals.push_back(point.y - point.predicted);
        }
        
        // Calculate R² = 1 - (SS_res / SS_tot)
        double meanY = calculateMean(yValues);
        
        double ssRes = 0;  // Sum of squared residuals
        double ssTot = 0;  // Total sum of squares
        
        for (size_t i = 0; i < data.size(); i++) {
            ssRes += residuals[i] * residuals[i];
            double yDiff = yValues[i] - meanY;
            ssTot += yDiff * yDiff;
        }
        
        if (ssTot == 0) {
            rSquared = 0;
        } else {
            rSquared = 1 - (ssRes / ssTot);
        }
    }
    
    // Predict y value for given x
    double predict(double x) const {
        return slope * x + intercept;
    }
    
    // Calculate Mean Squared Error
    double calculateMSE() const {
        if (data.empty()) return 0;
        
        double sumSquaredErrors = 0;
        for (const auto& point : data) {
            double error = point.y - point.predicted;
            sumSquaredErrors += error * error;
        }
        
        return sumSquaredErrors / data.size();
    }
    
    // Calculate Mean Absolute Error
    double calculateMAE() const {
        if (data.empty()) return 0;
        
        double sumAbsErrors = 0;
        for (const auto& point : data) {
            double error = abs(point.y - point.predicted);
            sumAbsErrors += error;
        }
        
        return sumAbsErrors / data.size();
    }
    
    // Generate synthetic data with noise
    void generateSyntheticData(int numPoints, double trueSlope = 2.5, 
                               double trueIntercept = 1.0, double noise = 0.5) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> xDis(0, 10);
        normal_distribution<> noiseDis(0, noise);
        
        for (int i = 0; i < numPoints; i++) {
            double x = xDis(gen);
            double y = trueSlope * x + trueIntercept + noiseDis(gen);
            addPoint(x, y);
        }
        
        cout << "Generated " << numPoints << " synthetic data points.\n";
        cout << "True model: y = " << trueSlope << "x + " << trueIntercept << "\n";
        cout << "Noise level: " << noise << "\n\n";
    }
    
    // Save results as image
    void saveAsImage(const string& filename) {
        if (data.empty()) {
            cerr << "Error: No data points to visualize.\n";
            return;
        }
        
        int width = 800;
        int height = 600;
        int margin = 50;
        
        // Find data bounds
        double minX = data[0].x, maxX = data[0].x;
        double minY = data[0].y, maxY = data[0].y;
        
        for (const auto& point : data) {
            minX = min(minX, point.x);
            maxX = max(maxX, point.x);
            minY = min(minY, point.y);
            maxY = max(maxY, point.y);
        }
        
        // Add padding
        double rangeX = maxX - minX + 1;
        double rangeY = maxY - minY + 1;
        
        // Create image buffer
        vector<vector<vector<int>>> image(height, vector<vector<int>>(width, vector<int>(3, 255)));
        
        // Draw grid lines
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if ((x - margin) % 50 == 0 || (y - margin) % 50 == 0) {
                    if (x >= margin && x < width - margin && y >= margin && y < height - margin) {
                        image[y][x] = {220, 220, 220};
                    }
                }
            }
        }
        
        // Draw regression line (pixel by pixel for smoothness)
        for (int px = margin; px < width - margin; px++) {
            // Convert pixel x back to data x
            double dataX = minX + (double)(px - margin) / (width - 2 * margin) * rangeX;
            double dataY = predict(dataX);
            
            int py = height - margin - (int)((dataY - minY) / rangeY * (height - 2 * margin));
            
            if (py >= margin && py < height - margin) {
                for (int thickness = -2; thickness <= 2; thickness++) {
                    if (py + thickness >= 0 && py + thickness < height) {
                        image[py + thickness][px] = {0, 0, 255};  // Blue line
                    }
                }
            }
        }
        
        // Draw data points
        for (const auto& point : data) {
            int px = margin + (int)((point.x - minX) / rangeX * (width - 2 * margin));
            int py = height - margin - (int)((point.y - minY) / rangeY * (height - 2 * margin));
            
            if (px >= margin && px < width - margin && py >= margin && py < height - margin) {
                // Draw point as red circle
                for (int dx = -3; dx <= 3; dx++) {
                    for (int dy = -3; dy <= 3; dy++) {
                        if (dx * dx + dy * dy <= 9) {
                            int nx = px + dx;
                            int ny = py + dy;
                            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                                image[ny][nx] = {255, 0, 0};  // Red
                            }
                        }
                    }
                }
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
        
        cout << "Image saved as: " << filename << "\n";
        cout << "You can convert it to PNG using: convert " << filename << " output.png\n";
    }
    
    // Display results
    void displayResults() const {
        cout << "\n=== LINEAR REGRESSION RESULTS ===\n";
        cout << "Number of data points: " << data.size() << "\n";
        cout << "Slope (m): " << fixed << setprecision(6) << slope << "\n";
        cout << "Intercept (b): " << fixed << setprecision(6) << intercept << "\n";
        cout << "Equation: y = " << slope << "x + " << intercept << "\n\n";
        
        cout << "Model Performance:\n";
        cout << "R² Score: " << fixed << setprecision(6) << rSquared << "\n";
        cout << "Mean Squared Error (MSE): " << fixed << setprecision(6) << calculateMSE() << "\n";
        cout << "Mean Absolute Error (MAE): " << fixed << setprecision(6) << calculateMAE() << "\n";
    }
    
    // Make predictions on new data
    void makePredictions(const vector<double>& xValues) const {
        cout << "\n=== PREDICTIONS ===\n";
        cout << setw(12) << "X Value" << " | " << setw(12) << "Predicted Y\n";
        cout << string(28, '-') << "\n";
        
        for (double x : xValues) {
            cout << fixed << setprecision(4) << setw(12) << x << " | " 
                 << setw(12) << predict(x) << "\n";
        }
    }
    
    // Getters
    double getSlope() const { return slope; }
    double getIntercept() const { return intercept; }
    double getRSquared() const { return rSquared; }
    const vector<DataPoint>& getData() const { return data; }
};

int main() {
    LinearRegression lr;
    
    // Generate synthetic data
    cout << "Generating synthetic data...\n";
    lr.generateSyntheticData(50, 2.5, 1.0, 0.8);
    
    // Fit the model
    lr.fit();
    
    // Display results
    lr.displayResults();
    
    // Make predictions
    vector<double> testX = {1.0, 3.5, 7.2, 9.5};
    lr.makePredictions(testX);
    
    // Save visualization
    lr.saveAsImage("regression_result.ppm");
    
    // Print sample data
    cout << "\nSample predictions (first 5 points):\n";
    const auto& data = lr.getData();
    cout << setw(12) << "X" << " | " << setw(12) << "Actual Y" 
         << " | " << setw(12) << "Predicted Y" << " | " << setw(10) << "Error\n";
    cout << string(52, '-') << "\n";
    
    for (int i = 0; i < min(5, (int)data.size()); i++) {
        double error = data[i].y - data[i].predicted;
        cout << fixed << setprecision(4) << setw(12) << data[i].x << " | "
             << setw(12) << data[i].y << " | " << setw(12) << data[i].predicted 
             << " | " << setw(10) << error << "\n";
    }
    
    return 0;
}