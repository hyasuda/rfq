#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;


const double m_mu   = 105.66    ; // muon mass [MeV]
const double m_e    = 511E+3    ; // electron mass [eV]
const double c      = 299792458 ; // light speed [m/s]
const double pi     = 3.1415    ; // PI
const double RF     = 324E+6    ; // RF frequency [Hz]
const double lambda = 925.285   ; // RF wave-length [mm] : c/RF

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
int nline = 0;

// Transfer components //
double X[n]     = {}; // x, xp, y, yp, phi, Ek
double Xmean[n] = {}; // x, xp, y, yp, phi, Ek
double Y[n]     = {}; // x, xp, y, yp, phi, Ek
// double Y[n];

// relativistic parameter //
double beta  = 0;
double Gamma = 0;

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
void beta_calc( double ke);
void Gamma_calc( double beta_val );
void unit();
void trans();
void unitorigin();
void reset();

void transfer(string outputfile = "rfqll_trans.dat"){

    mean( inputfile );
    beta_calc( Xmean[5] );
    Gamma_calc( beta );

    stringstream filename;
    stringstream output;
    ifstream ifs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", inputfile.c_str()));   // Input  file name
    ofstream ofs(Form("/Users/YASUDA/data/muonLinac/rfq/%s", outputfile.c_str())); // Output file name for muon after rfq

    int nline = 0;

    while(ifs >> X[0] >> X[1] >> X[2] >> X[3] >> X[4] >> X[5] ){
        cout << "nline : " << nline << endl;
        // if(nline > 3) break; // for debug
        for(int i = 0 ; i < 6 ; i++ ){
            cout << X[i] << "\t" ;
        }
        cout << endl;
        unit();
        trans();
        unitorigin();
        if(Y[5] < 0 ) continue;
        for(int i = 0 ; i < 6 ; i++ ){
            cout << Y[i] << "\t" ;
        }
        ofs  << scientific;
        ofs  << Y[0] << "\t" << Y[1] << "\t" << Y[2] << "\t" << Y[3] << "\t" << Y[4] << "\t" << Y[5] << endl;
        nline++;
        reset();
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
    Xmean[0] = xsum/nline;
    Xmean[1] = xpsum/nline;
    Xmean[2] = ysum/nline;
    Xmean[3] = ypsum/nline;
    Xmean[4] = phisum/nline;
    Xmean[5] = Wsum/nline;
    // cout << "#####  AVERAGE  #####" << endl;
    // cout << scientific ; cout.precision(4);
    // cout << "Enrty = " << nline << endl;
    // cout << "x[mm]   " << "\t" << "xp[mrad]" << "\t" << "y[mm]   " << "\t" << "yp[mrad]" << "\t" << "phi[deg]" << "\t" << "W[MeV]" << endl;
    // cout << Xmean[0] << "\t" << Xmean[1] << "\t" << Xmean[2] << "\t" << Xmean[3] << "\t" << Xmean[4] << "\t" << Xmean[5] << endl;
}

void beta_calc(double ke){
    double mom = sqrt(2 * m_mu * ke);
    beta = mom / sqrt(m_mu*m_mu + mom*mom);
    cout << scientific;
    cout << "beta = " << beta << " ,\t";
}

void Gamma_calc( double beta_val ){
    Gamma = 1/sqrt( 1 - beta_val * beta_val );
    cout << "Gamma = " << Gamma << endl;
}

// void diff(){
//     cout << "after diff :: " ;
//     for(int i = 0 ; i < n ; i++){
//         X[i] = X[i] - Xmean[i];
//         if(i == 5) cout << X[i] << "\t" ;
//     }
//     cout << endl;
// }

void unit(){
    Y[0] = X[0] - Xmean[0];
    Y[1] = X[1] - Xmean[1];
    Y[2] = X[2] - Xmean[2];
    Y[3] = X[3] - Xmean[3];
    Y[4] = -beta * lambda / 360 * ( X[4] - Xmean[4] );
    Y[5] = Gamma/(Gamma + 1) * (X[5] - Xmean[5])/X[5] * 1.e+3;
}

void trans(){
    for(int i = 0 ; i < n ; i++ ){
        for(int j = 0 ; j < n ; j++){
            Y[i] += R[i][j] * X[j];
        }
    }
}

void unitorigin(){
    Y[0] = Y[0] + Xmean[0]; // mm
    Y[1] = Y[1] + Xmean[1]; // mm
    Y[2] = Y[2] + Xmean[2]; // mm
    Y[3] = Y[3] + Xmean[3]; // mm
    Y[4] = -360/(beta * lambda) * Y[4]; // mm
    Y[5] = Y[5] * 1.e-3; // mrad -> rad
    Y[5] = Gamma * Xmean[5] / (Gamma - (Gamma + 1) * Y[5]); // [MeV]
    // Y[5] = Xmean[5] * (1 + (Gamma + 1)/Gamma * Y[5]); // delta W / W ~ (W-<W>)/<W> [MeV]
}

// void add(){
//     for(int i = 0 ; i < n ; i++){
//         Y[i] = Y[i] + Xmean[i];
//         if(i == 5)cout << "after add :: " << Y[i ] << endl;
//     }
// }

void reset(){
    for(int i = 0 ; i < n ; i++){
        X[i] = 0;
        Y[i] = 0;
    }
}
