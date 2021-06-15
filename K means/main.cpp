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
    double dist_minima;  // distancia minima

    Point() :
        x(0.0),
        y(0.0),
        cluster(-1),
        dist_minima(DBL_MAX) {}

    Point(double x, double y) :
        x(x),
        y(y),
        cluster(-1),
        dist_minima(DBL_MAX) {}
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


void k_means(vector<Point>* puntos, int vueltas, int k) {           ///vector, numero de iteraciones,  clusters
    vector<Point> centroides;
    srand(time(0));  // need to set the random seed
    for (int i = 0; i < k; ++i) {
        int temp = -30 + rand() % 40;
        int temp2 = -30 + rand() % 40;
        cout << "Centroide: " << temp << " , " << temp2 << endl;
        centroides.push_back(Point(temp,temp2));
    }

    /*
    vector< pair <int, double> > cl_dis;
    for (vector<Point>::iterator it = puntos->begin(); it != puntos->end(); ++it) {
        double distancia= DBL_MAX;
        int i = 0;
        for (vector<Point>::iterator c = begin(centroides); c != end(centroides); ++c) {
            distancia = distance2((*it), (*c));
            cl_dis.push_back(make_pair(i, distancia));
            cout << "Para el cluster " << i << " la distancia es " << distancia << endl;
            i++;
        }
        sort(cl_dis.begin(), cl_dis.end(), sortbysec);

        Point p = *it;
        p.dist_minima = cl_dis[0].second;
        p.cluster = cl_dis[0].first;
        cout << "Para el punto "<<p.x<<","<<p.y<<" la minima distancia es " << p.dist_minima << " y su cluster es " << p.cluster << endl << endl;
        cl_dis.clear();
    }
    
    cout << "-------------------------------------------------------------------------------------" << endl;

    */

    for (int i = 0; i < vueltas; i++) {

        for (vector<Point>::iterator c = begin(centroides); c != end(centroides); ++c) {              // quick hack to get cluster index
            int clust_id = c - begin(centroides);

            for (vector<Point>::iterator it = puntos->begin(); it != puntos->end(); ++it) {

                Point p = *it;
                double dist = c->distance2(p, *c);
                if (dist < p.dist_minima) {
                    p.dist_minima = dist;
                    p.cluster = clust_id;
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
        for (vector<Point>::iterator it = puntos->begin(); it != puntos->end(); ++it) {
            int clust_id = it->cluster;
            nPoints[clust_id] += 1;
            sumX[clust_id] += it->x;
            sumY[clust_id] += it->y;

            it->dist_minima = DBL_MAX;  // reseteamos la distancia
        }

        // Calculamos nuevos centroides
        for (vector<Point>::iterator c = begin(centroides); c != end(centroides); ++c) {
            int clust_id = c - begin(centroides);
            c->x = sumX[clust_id] / nPoints[clust_id];
            c->y = sumY[clust_id] / nPoints[clust_id];
        }
    }
    
    ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << endl;

    for (vector<Point>::iterator it = puntos->begin();it != puntos->end(); ++it) {

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

    vector<Point> puntos;
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

        puntos.push_back(Point(x, y));
    }


    file.close();
    k_means(&puntos, vuelta, num);
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

    for (vector<Point>::iterator it = puntos.begin(); it != puntos.end(); ++it) {

        myfile << it->x << "," << it->y << "," << it->cluster << endl;
    }
    myfile.close();
    //cout << "terminamos :v " << endl;
}
