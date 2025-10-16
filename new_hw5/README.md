# HW5 Assignment: Supervised and Unsupervised Machine Learning with C++
Implement one supervised ML algorithm (linear regression) and one unsupervised ML algorithm (K-means Clustering).
Provide the exact instructions to run your code. 
You can choose ANY 2D dataset (synthetic, real-world, etc.) to test your algorithms. 

# K-Means Clustering Algorithm 

## Overview

Implement the **K-Means clustering algorithm**, a fundamental unsupervised learning algorithm, to partition 2D data points into K clusters. The algorithm iteratively assigns points to nearest centers and updates centers based on cluster membership.

## Algorithm Summary

**K-Means works in 4 steps:**

1. **Initialize**: Randomly select K points as cluster centers
2. **Assign**: Assign each point to the nearest center (using Euclidean distance)
3. **Update**: Recalculate each center as the mean of its assigned points
4. **Converge**: Repeat steps 2-3 until centers stabilize or max iterations reached

## Required Functions

You must implement the following functions in the `KMeans` class:

### 1. `distance(const Point& p1, const Point& p2) -> double`
Calculate the Euclidean distance between two points.

### 2. `initializeCenters() -> void`
Randomly select K points from the dataset as initial cluster centers. 

### 3. `assignPoints() -> void`
For each data point, find the nearest cluster center and assign the point to that cluster. 

### 4. `updateCenters() -> bool`
Calculate new cluster centers as the mean of all assigned points. Return `true` if converged, `false` otherwise.

### 5. `fit() -> void`
Main algorithm loop:
- Initialize centers
- For each iteration (up to maxIterations):
  - Call `assignPoints()`
  - Call `updateCenters()`
  - Print iteration number and current inertia
  - Check for convergence
- Print final status (converged or max iterations reached)

### 6. `calculateInertia() -> double`
Calculate total inertia: sum of squared distances from each point to its assigned center.
```
Inertia = Σ (distance from point to its center)²
```

### 7. `saveAsImage(const string& filename) -> void`
Generate a PPM image visualization:
- Plot each data point as a colored dot (color = cluster ID)
- Mark cluster centers with crosses
- Save as PPM format file

## Data Structures

```cpp
struct Point {
    double x, y;        // 2D coordinates
    int cluster;        // Assigned cluster ID (-1 if unassigned)
};

class KMeans {
    vector<Point> points;        // All data points
    vector<Point> centers;       // K cluster centers
    int k;                       // Number of clusters
    double tolerance;            // Convergence threshold
    int maxIterations;           // Maximum iterations
    int iterations;              // Actual iterations completed
};
```

### Using the KMeans Class: Example with Synthetic Data 

```cpp
int main() {
    KMeans kmeans(3, 1e-4, 100);  // k=3 clusters, tolerance=1e-4, max 100 iterations
    kmeans.generateSyntheticData(300);  // Generate 300 random points
    kmeans.fit();                       // Run clustering
    kmeans.saveAsImage("output.ppm");   // Save visualization    
    return 0;
}
```

# Linear Regression 

## Overview

Implement **Linear Regression**, a fundamental supervised learning algorithm that fits a line to data points. The goal is to find the best-fit line that minimizes prediction errors using the Least Squares method.

## Algorithm Summary

**Linear Regression finds the best-fit line y = mx + b by:**

1. **Compute slope**: m 
2. **Compute intercept**: b 
3. **Generate predictions**: For each x: y_predicted = mx + b
4. **Calculate metrics**: Compute R², MSE, MAE to evaluate model quality

## Required Functions

You must implement the following functions in the `LinearRegression` class:

### 1. `fit() -> void`
Fit the regression line using Least Squares method
- Compute slope and intercept 
- Call `calculateMetrics()` to evaluate the model
- Print the fitted equation: "Model: y = [slope]x + [intercept]"

### 2. `calculateMetrics() -> void`
Calculate predicted values and R² score:
- For each data point: `predicted_y = slope * x + intercept`
- Calculate R² (coefficient of determination)
- Store all predicted values in each DataPoint

### 3. `calculateMSE() -> double`
Calculate Mean Squared Error:
```
MSE = Σ(y_actual - y_predicted)² / n
```
### 4. `calculateMAE() -> double`
Calculate Mean Absolute Error:
```
MAE = Σ|y_actual - y_predicted| / n
```
### 5. `predict(double x) -> double`
Return predicted y value for given x: `y = slope * x + intercept`

### 6. `saveAsImage(const string& filename) -> void`
Generate a PPM image visualization:
- Plot data points 
- Draw regression line 
- Save as PPM format file

## Data Structures

```cpp
struct DataPoint {
    double x, y;           // Actual coordinates
    double predicted;      // Predicted y value from model
};

class LinearRegression {
    vector<DataPoint> data;    // Training data
    double slope;              // m in y = mx + b
    double intercept;          // b in y = mx + b
    double rSquared;           // R² score
};
```

### Using the LinearRegression Class: Example with Synthetic Data 

```cpp
int main() {
    LinearRegression lr;
    // Generate synthetic data with true slope=2.5, intercept=1.0, noise=0.5
    lr.generateSyntheticData(100, 2.5, 1.0, 0.5);
    
    lr.fit();                              // Fit the model
    lr.saveAsImage("regression.ppm");      // Visualize
    
    return 0;
}
```



