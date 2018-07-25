#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;


const double m_mu  = 105.66E+6; // muon mass [eV]
const double m_e   = 511E+3   ; // electron mass [eV]
const double c     = 299792458; // light speed [m/s]
const double pi    = 3.1415   ; // PI

const string inputfile = "rfqll.dat";

const int n = 6;
// Base file is rfqll.dat //
// double x;
// double xp;
// double y;
// double yp;
// double phi;
// double Ek;

// Average //
double xmean = 0;
double xpmean = 0;
double ymean = 0;
double ypmean = 0;
double phimean = 0;
double Wmean = 0;
int nline = 0;

// Transfer components //
double X[n]     = {}; // x, xp, y, yp, phi, Ek
double Xmean[n] = {}; // x, xp, y, yp, phi, Ek
double Y[n]     = {}; // x, xp, y, yp, phi, Ek
// double Y[n];

// Transfer matrix definition //
// const int n = 6;
const double R[n][n] = {
    {  0.229,  0.358,  0.   ,  0.   ,  0.   ,  0.   },
    { -2.629,  0.253,  0.   ,  0.   ,  0.   ,  0.   },
    {  0.   ,  0.   , -1.743,  0.262,  0.   ,  0.   },
    {  0.   ,  0.   , -2.857, -0.145,  0.   ,  0.   },
    {  0.   ,  0.   ,  0.   ,  0.   , -0.776,  0.156},
    {  0.   ,  0.   ,  0.   ,  0.   , -3.529, -0.579},
};


// function definition //
void mean(string fname);
void diff();
void unit();
void trans();
void unitorigin();
void add();

void transfer(string outputfile = "rfqll_trans.dat"){

    mean( inputfile );

    stringstream filename;
    stringstream output;
    ifstream ifs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", inputfile.c_str()));   // Input  file name
    ofstream ofs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", outputfile.c_str())); // Output file name for muon after rfq

    int nline = 0;

    while(ifs >> X[0] >> X[1] >> X[2] >> X[3] >> X[4] >> X[5] ){
        // cout << "nline : " << nline << endl;
        diff();
        unit();
        trans();
        unitorigin();
        add();
        ofs  << scientific;
        ofs  << Y[0] << "\t" << Y[1] << "\t" << Y[2] << "\t" << Y[3] << "\t" << Y[4] << "\t" << Y[5] << endl;
        nline++;
    }
}

void mean(string fname){
    int nline = 0;
    double x, xp, y, yp, phi, W;
    double xsum = 0;
    double xpsum = 0;
    double ysum = 0;
    double ypsum = 0;
    double phisum = 0;
    double Wsum = 0;
    double xmean = 0;
    double xpmean = 0;
    double ymean = 0;
    double ypmean = 0;
    double phimean = 0;
    double Wmean = 0;

    ifstream rf(Form("/Users/YASUDA/data/muonLinac/rfq/%s", fname.c_str()));

    while(rf >> x >> xp >> y >> yp >> phi >> W){
        xsum   += x;
        xpsum  += xp;
        ysum   += y;
        ypsum  += yp;
        phisum += phi;
        Wsum   += W;
        nline++;
    }
    xmean   = xsum/nline;
    xpmean  = xpsum/nline;
    ymean   = ysum/nline;
    ypmean  = ypsum/nline;
    phimean = phisum/nline;
    Wmean   = Wsum/nline;
    Xmean[0] = xmean;
    Xmean[1] = xpmean;
    Xmean[2] = ymean;
    Xmean[3] = ypmean;
    Xmean[4] = phimean;
    Xmean[5] = Wmean;
    cout << "#####  AVERAGE  #####" << endl;
    cout << "Enrty = " << nline << endl;
    cout << "x" << "\t" << "xp" << "\t" << "y" << "\t" << "yp" << "\t" << "phi" << "\t" << "W" << endl;
    cout << xmean << "\t" << xpmean << "\t" << ymean << "\t" << ypmean << "\t" << phimean << "\t" << Wmean << endl;
}

void diff(){
    for(int i = 0 ; i < n ; i++){
        X[i] = X[i] - Xmean[i];
    }
}

void unit(){
    // Ek = Ek * 1.e+3; // MeV -> keV
    X[5] = X[5] * 1.e+3; // MeV -> keV
}

void unitorigin(){
    Y[5] = Y[5] * 1.e-3; // keV -> MeV
}


void trans(){
    for(int i = 0 ; i < n ; i++ ){
        for(int j = 0 ; j < n ; j++){
            // cout << R[i][j] << "\t" ;
            Y[i] += R[i][j] * X[j];
        }
        // cout << endl;
    }
}

void add(){
    for(int i = 0 ; i < n ; i++){
        Y[i] = Y[i] + Xmean[i];
    }
}
