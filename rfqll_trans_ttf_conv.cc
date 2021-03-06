#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

const double m_mu  = 105.66   ; // muon mass [MeV]
const double m_e   = 511E+3   ; // electron mass [eV]
const double c     = 299792458; // light speed [m/s]
const double pi    = 3.1415   ; // PI

double x;
double xp;
double y;
double yp;
double phase;
double Ek;
double P;

// function definition //
void conv();

// AFTER TRANSFER MATRIX //
// const string inputfile = "rfqll_trans.dat";
// void rfqll_trans_ttf_conv(string inputfile, string outputfile = "rfqll_trans_output.dat"){
void rfqll_trans_ttf_conv(string inputfile, string outputfile){

    ifstream ifs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", inputfile.c_str()));   // Input  file name
    ofstream ofs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", outputfile.c_str())); // Output file name for muon after rfq
    int nline = 0;
    while(ifs >> x >> xp >> y >> yp >> phase >> Ek){
        P = 2*m_mu*Ek;
        if(P < 0) cout << nline << "\t" << P << "\t" << Ek << endl;
        P = sqrt(P);
        conv();
        cout << scientific;
        ofs  << scientific;
        // cout << x << "\t" << xp << "\t" << y << "\t" << yp << "\t" << P << endl;
        ofs  << x << "\t" << xp << "\t" << y << "\t" << yp << "\t" << P << endl;
        nline++;
    }
}

const double non = 0;
const double scl = 0.1;
void conv(){
        x = x *   scl; // mm -> cm
        y = y *   scl; // mm -> cm
        P = P * 0.001; // MeV -> GeV
        // P = 8.4465 * 1.e-3;
}
