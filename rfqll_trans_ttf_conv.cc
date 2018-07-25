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
const string inputfile = "rfqll_trans.dat";
void rfqll_trans_ttf_conv(string outputfile = "rfqll_trans_output.dat"){

    ifstream ifs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", inputfile.c_str()));   // Input  file name
    ofstream ofs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", outputfile.c_str())); // Output file name for muon after rfq

    while(ifs >> x >> xp >> y >> yp >> phase >> Ek){
        P = 2*m_mu*1.E-9*Ek*1.E-3;
        // P = sqrt(P);
        conv();
        cout << scientific;
        ofs  << scientific;
        cout << x << "\t" << xp << "\t" << y << "\t" << yp << "\t" << P << endl;
        ofs  << x << "\t" << xp << "\t" << y << "\t" << yp << "\t" << P << endl;
    }
}

const double non = 0;
const double scl = 0.1;
void conv(){
        x = x * scl; // mm -> cm
        y = y * scl; // mm -> cm
        // P = 8.4465 * 1.e-3;
}
