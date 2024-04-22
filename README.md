# KnnVisualiser
KnnVisualiser application demonstrates how K-Nearest Neighbours classification works with an example of Ronald Fisher's Iris dataset. Using graphical interface you can set model parameters and flower's features and predict iris type.
## Features 
Iris dataset includes 150 rows of data with 3 different types of irises (Iris-setosa, Iris-versicolor, Iris-virginica). Each row of data includes 4 features: sepal length, sepal width, petal length and petal width. You can choose which of four features you whant to use in prediction. Minimum number of used features is 2 (It must be features selected as plot axes, so application can visualise data correctly).
## Plot 
2D scatter-plot demonstrates dataset points of three colors (Iris-setosa - red, Iris-versicolor - green, Iris-virginica - blue) and point with data, entered by user. Each time you predict iris type, prediction point is painted in corresponding iris type color. 
## UI example
![Снимок экрана от 2024-04-22 15-30-34](https://github.com/EL96cpp/KnnVisualiser/assets/120955824/94427061-ce7a-4a73-8fce-c881161e8122)

## Accuracy 
Each time you predict iris type, application randomly splits data into train and test datasets (20% for train and 80% for test dataset). Test dataset is balanced: it includes 10 data rows for each type of flower.
## Model parameters
### Window width
Window width parameter greatly affects the quality of the model. If the width is too small, the model overfits the training set and loses its generalization ability. If the width is too large, on the contrary, the model becomes too simple.
### Kernel function
There are five types of kernels available in KnnVisualiser: rectangular, triangular, Epanchenkov's, Gaussian and biquadratic. The smoothness of the approximation depends on the choice of kernel, but this choice has almost no effect on its quality.
### Minkowski metric parameter
Minkowski metric parameter represents $p$ parameter in Minkowski distance formula: $$D\(x,y\) = \left(\sum^{\substack{n}}_{\substack{i = 1}}\left|x_i-y_i\right|^p\right)^{\frac{1}{p}}$$
This parameter determines which set of points is considered equidistant from a given point.
### Number of neighbours
This parameter indicates the number of closest neighbors model uses to predict iris type.
