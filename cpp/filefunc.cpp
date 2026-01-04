#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

void file_it(ostream & os, double fo, const double fe[], int n);
const int LIMIT = 5;
int main(){
    ofstream fout;
    const char * fn = "ep-data.txt";
    fout.open(fn);
    if (!fout.is_open()){
        exit(EXIT_FAILURE);
    }
    double obj;
    cout << "Enter length:";
    cin >> obj;
    double eps[LIMIT];
    cout<< "enter "<<LIMIT<<"eyepieces"<<endl;
    for (int i = 0; i < LIMIT; i++){
        cout << "# "<< i+1 << ": ";
        cin >> eps[i];
    }
    file_it(fout, obj, eps, LIMIT);
    file_it(cout, obj, eps, LIMIT);
    cout<<"Done\n";
    return 0;
}

void file_it(ostream & os, double fo, const double fe[], int n){
    ios_base::fmtflags init;
    init = os.setf(ios_base::fixed);
    os.precision(0);
    os<< "Focal: "<< fo << endl;
    os.setf(ios::showpoint);
    os.precision(1);
    os.width(10);
    os << "f.1";
    os.width(15);
    os << "magnification\n";
    for (int i=0;i<n;i++){
        os.width(12);
        os<< fe[i];
        os.width(15);
        os << int (fo/fe[i] + 0.5) << endl;
    }
    os.setf(init);
}