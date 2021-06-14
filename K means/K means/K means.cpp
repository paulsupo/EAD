#include <ctime>   
#include <fstream> 
#include <iostream>  
#include <sstream>   
#include <vector>
#include <cfloat>

using namespace std;

struct Point {
    double x, y;     /// coordenadas
    int cluster;     /// cluster futuro
    double minDist;  // distancia minima

    Point() :
        x(0.0),
        y(0.0),
        cluster(-1),            ///iniciamos en -1 porque no sabemos a que cluster perteneve
        minDist(DBL_MAX) {}

    Point(double x, double y) :
        x(x),
        y(y),
        cluster(-1),
        minDist(DBL_MAX) {}

    double distance(Point p) {      ///distancia
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

///leemos el archivo de datos

vector<Point> read_file() {
    vector<Point> points;
    string line;
    ifstream file("data.csv");

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double x, y;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back(Point(x, y));
    }
    return points;
}

void kMeansClustering(vector<Point>* points, int epochs, int k) {           ///vector, numero de iteraciones,  clusters
    vector<Point> centroids;
    srand(time(0));  // need to set the random seed
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand() % 1000));
    }

    for (vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {
        // quick hack to get cluster index
        int clusterId = c - begin(centroids);

        for (vector<Point>::iterator it = points->begin();
            it != points->end(); ++it) {

            Point p = *it;
            double dist = c->distance(p);
            if (dist < p.minDist) {
                p.minDist = dist;
                p.cluster = clusterId;
            }
            *it = p;
        }
    }

    vector<int> nPoints;
    vector<double> sumX, sumY;

    // llenamos los vectores con 0
    for (int j = 0; j < k; ++j) {
        nPoints.push_back(0);
        sumX.push_back(0.0);
        sumY.push_back(0.0);
    }


    // Iterate over points to append data to centroids
    for (vector<Point>::iterator it = points->begin();
        it != points->end(); ++it) {
        int clusterId = it->cluster;
        nPoints[clusterId] += 1;
        sumX[clusterId] += it->x;
        sumY[clusterId] += it->y;

        it->minDist = DBL_MAX;  // reset distance
    }

    // Calculamos nuevos centroides
    for (vector<Point>::iterator c = begin(centroids);
        c != end(centroids); ++c) {
        int clusterId = c - begin(centroids);
        c->x = sumX[clusterId] / nPoints[clusterId];
        c->y = sumY[clusterId] / nPoints[clusterId];
    }


    ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << endl;

    for (vector<Point>::iterator it = points->begin();
        it != points->end(); ++it) {
        myfile << it->x << "," << it->y << "," << it->cluster << endl;
    }
    myfile.close();



}


int main(){
    int num, vuelta;
    cout << "Cuandtos clusters desea? ";
    cin >> num;
    cout << "Cuantas iteraciones desea? ";
    cin >> vuelta;
    vector<Point> points = read_file();
    kMeansClustering(&points, vuelta, num);
    cout << "terminamos :v " << endl;
}