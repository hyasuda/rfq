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
// const double beta    = 0.08     ; // velocity of muon after RFQ


int main(){
// void rfq_ttf_conv(){

    cout << "%%%%% START %%%%%" << endl;

    // const double gamma = 1/(sqrt(1-beta*beta)); // Lorentz factor

    stringstream filename;
    stringstream output;
    filename.str("/Users/YASUDA/data/muonLinac/rfq/rfqll.dat");   // Input  file name
    output.str("/Users/YASUDA/data/muonLinac/rfq/rfqll_ttf.dat"); // Output file name

    ifstream ifs(filename.str().c_str(), std::ios::in);
    ofstream ofs(output.str().c_str(), std::ios::in);


    //////// Char-type variables /////
    double xc;
    double xpc;
    double yc;
    double ypc;
    double phasec;
    double Ekc;

    int N = 100000;
    //////// Origin file after RFQ output ///////
    vector<double> x;     // x  [cm]
    vector<double> xp;    // x' [rad]
    vector<double> y;     // y  [cm]
    vector<double> yp;    // y' [rad]
    vector<double> phase;  // phase [rad]
    vector<double> Ek;     // Kinetic energy [MeV]


    //////// TurtleFile after RFQ output ///////
    vector<double> xt;     // x  [cm]
    vector<double> xpt;    // x' [mrad]
    vector<double> yt;     // y  [cm]
    vector<double> ypt;    // y' [mrad]
    vector<double> Pt;     // Momentum [GeV]
    double dummy1 = 0;     // dummy
    double dummy2 = 0;     // dummy
    double Z = 0;          // Atomic number
    double A = 0;          // Mass number


    // string str;
    // int lineno = 0;
    // int iword = 0;
    // const int N = 20;
    // string atoken[ N ];

    // while(getline(ifs,str)){
    //     string token;
    //     istringstream stream(str);

    //     iword = 0;
    //     while(getline(stream,token,' ')){
    //         atoken[ iword ] = token;
    //         // cout << iword << " , " << atoken[iword] << endl;
    //         if(atoken[iword] == "  ") continue;
    //         cout << iword << " , " << atoken[iword] << endl;
    //         // if(atoken[iword] != 0) iword++;
    //     }

    //     switch (lineno) {
    //         /* SAVE BY ASCII*/
    //         // case 0 :
    //         //   break;
    //         // case 1 :
    //         //   break;
    //     default :
    //         xc      = (double) atof( atoken[ 0 ].c_str() ) ;
    //         xpc     = (double) atof( atoken[ 1 ].c_str() ) ;
    //         yc      = (double) atof( atoken[ 2 ].c_str() ) ;
    //         ypc     = (double) atof( atoken[ 3 ].c_str() ) ;
    //         phasec  = (double) atof( atoken[ 4 ].c_str() ) ;
    //         Ekc     = (double) atof( atoken[ 5 ].c_str() ) ;
    //         // cout << lineno << " " << xc << " " << xpc << " " << yc << " " << ypc << " " << phasec << " " << Ekc << endl;

    //             x.push_back( xc     );
    //            xp.push_back( xpc    );
    //             y.push_back( yc     );
    //            yp.push_back( ypc    );
    //         phase.push_back( phasec );
    //            Ek.push_back( Ekc    );

    //         break;
    //     }

    //     lineno++;
    // }

    int lineno = 0;

    double x0[N];
    double xp0[N];
    double y0[N];
    double yp0[N];
    double phase0[N];
    double Ek0[N];


    while(ifs >> x0[lineno] >> xp0[lineno] >> y0[lineno] >> yp0[lineno] >> phase0[lineno] >> Ek0[lineno]){
            x.push_back( x0[lineno]     );  // cm   <- cm
           xp.push_back( xp0[lineno]    );  // mrad <- rad
            y.push_back( y0[lineno]     );  // cm   <- cm
           yp.push_back( yp0[lineno]    );  // mrad <- rad
        phase.push_back( phase0[lineno] );
           Ek.push_back( Ek0[lineno]    );
        lineno++;
    }
    int flineno = lineno;

    cout << "#####START INPUT FILE######" << endl;

    for(int i = 0 ; i < flineno ; i++){
         xt.push_back( x[i]       );         // cm   <- cm
        xpt.push_back( xp[i]*1000 );  // mrad <- rad
         yt.push_back( y[i]       );         // cm   <- cm
        ypt.push_back( yp[i]*1000 );  // mrad <- rad
         Pt.push_back( sqrt(2*m_mu*1.E-9*Ek[i]*1.E-3) ); // [GeV]
         // cout << scientific << setprecision(6);
         cout << scientific ;
         cout << xt[i] << " " << xpt[i] << " " << yt[i] << " " << ypt[i] << " " << Pt[i] << " " << dummy1 << " " << dummy2 << " " << Z << " " << A << endl;
         ofs << scientific ;
         ofs  << xt[i] << "\t" << xpt[i] << "\t" << yt[i] << "\t " << ypt[i] << "\t" << Pt[i] << "\t" << dummy1 << "\t" << dummy2 << "\t" << Z << "\t" << A << endl;
    }



    cout << "%%%%% FINISHED %%%%%" << endl;
    return 0;
}
