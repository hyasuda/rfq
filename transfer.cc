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
double X[n] = {}; // x, xp, y, yp, phi, Ek
double Y[n] = {}; // x, xp, y, yp, phi, Ek
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
void unit();
void unitorigin();
void trans();

void transfer(string outputfile = "rfqll_trans.dat"){

    stringstream filename;
    stringstream output;
    ifstream ifs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", inputfile.c_str()));   // Input  file name
    ofstream ofs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", outputfile.c_str())); // Output file name for muon after rfq

    int nline = 0;

    while(ifs >> X[0] >> X[1] >> X[2] >> X[3] >> X[4] >> X[5] ){
        // if(nline > 0) break;
        cout << "LINE : " << nline + 1 << endl;
        // cout << scientific;
        // cout << X[0] << "\t" << X[1] << "\t" << X[2] << "\t" << X[3] << "\t" << X[4] << "\t" << X[5] << endl;
        unit();
        // cout << X[0] << "\t" << X[1] << "\t" << X[2] << "\t" << X[3] << "\t" << X[4] << "\t" << X[5] << " keV " << endl;
        trans();
        // cout << Y[0] << "\t" << Y[1] << "\t" << Y[2] << "\t" << Y[3] << "\t" << Y[4] << "\t" << Y[5] << endl;
        unitorigin();
        // cout << Y[0] << "\t" << Y[1] << "\t" << Y[2] << "\t" << Y[3] << "\t" << Y[4] << "\t" << Y[5] << " MeV " << endl;
        ofs  << scientific;
        ofs  << Y[0] << "\t" << Y[1] << "\t" << Y[2] << "\t" << Y[3] << "\t" << Y[4] << "\t" << Y[5] << endl;
        nline++;
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
