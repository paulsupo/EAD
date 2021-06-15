#include <ctime>   
#include <fstream> 
#include <iostream>  
#include <cstdlib>
#include <sstream>   
#include <vector>
#include <random>
#include <cfloat>

using namespace std;




int ran() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> random(-73, 40);
    return random(rng);
}

struct Point {
    double x, y;     /// coordenadas
    int cluster;     /// cluster futuro
    double minDist;  // distancia minima

    Point() :
        x(0.0),
        y(0.0),
        cluster(-1),
        minDist(DBL_MAX) {}

    Point(double x, double y) :
        x(x),
        y(y),
        cluster(-1),
        minDist(DBL_MAX) {}
    double distance(Point p) {      ///distancia
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }

    double distance2(Point p, Point q) {      ///distancia
        double disX = (p.x - q.x);
        double disY = (p.y - q.y);
        disX *= disX;
        disY *= disY;
        double total = sqrt(disX + disY);
        return total;
    }
};

double distance2(Point p, Point q) {      ///distancia
    double disX = (p.x - q.x);
    double disY = (p.y - q.y);
    disX *= disX;
    disY *= disY;
    double total = sqrt(disX + disY);
    return total;
}

bool sortbysec(const pair <int, double>& a, const pair <int, double>& b) {
    return (a.second < b.second);
}


void kMeansClustering(vector<Point>* points, int vueltas, int k) {           ///vector, numero de iteraciones,  clusters
    vector<Point> centroids;
    srand(time(0));  // need to set the random seed
    for (int i = 0; i < k; ++i) {
        int temp = -30 + rand() % 40;
        int temp2 = -30 + rand() % 40;
        cout << "Centroide: " << temp << " , " << temp2 << endl;
        centroids.push_back(Point(temp,temp2));
    }

    /*
    vector< pair <int, double> > cl_dis;
    for (vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {
        double distancia= DBL_MAX;
        int i = 0;
        for (vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {
            distancia = distance2((*it), (*c));
            cl_dis.push_back(make_pair(i, distancia));
            cout << "Para el cluster " << i << " la distancia es " << distancia << endl;
            i++;
        }
        sort(cl_dis.begin(), cl_dis.end(), sortbysec);

        Point p = *it;
        p.minDist = cl_dis[0].second;
        p.cluster = cl_dis[0].first;
        cout << "Para el punto "<<p.x<<","<<p.y<<" la minima distancia es " << p.minDist << " y su cluster es " << p.cluster << endl << endl;
        cl_dis.clear();
    }
    
    cout << "-------------------------------------------------------------------------------------" << endl;

    */

    for (int i = 0; i < vueltas; i++) {

        for (vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {              // quick hack to get cluster index
            int clusterId = c - begin(centroids);

            for (vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {

                Point p = *it;
                double dist = c->distance2(p, *c);
                if (dist < p.minDist) {
                    p.minDist = dist;
                    p.cluster = clusterId;
                    //cout << "Para el punto " << p.x << "," << p.y << " el clauster es " << p.cluster << endl;

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


        // Itera sobre puntos para agregar datos a los centroides
        for (vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {
            int clusterId = it->cluster;
            nPoints[clusterId] += 1;
            sumX[clusterId] += it->x;
            sumY[clusterId] += it->y;

            it->minDist = DBL_MAX;  // reseteamos la distancia
        }

        // Calculamos nuevos centroides
        for (vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {
            int clusterId = c - begin(centroids);
            c->x = sumX[clusterId] / nPoints[clusterId];
            c->y = sumY[clusterId] / nPoints[clusterId];
        }
    }
    
    ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << endl;

    for (vector<Point>::iterator it = points->begin();it != points->end(); ++it) {

        myfile << it->x << "," << it->y << "," << it->cluster << endl;
    }

    myfile.close();


}


int main() {
    int num = 2, vuelta = 1;
    cout << "Cuantos clusters desea? ";
    cin >> num;
    cout << "Cuantas iteraciones desea? ";
    cin >> vuelta;

    vector<Point> points;
    string line;
    ifstream file("temp.csv");

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


    file.close();
    kMeansClustering(&points, vuelta, num);
    /*
    vector<Point> a;
    a.push_back(Point(3.5, 9.8));
    a.push_back(Point(6.8, 7.4));
    a.push_back(Point(6.4, 9.3));
    a.push_back(Point(9.1, 3.0));
    */
    ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << endl;

    for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {

        myfile << it->x << "," << it->y << "," << it->cluster << endl;
    }
    myfile.close();
    //cout << "terminamos :v " << endl;
}
