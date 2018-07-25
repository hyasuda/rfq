string strtmp;
TH2F* fH;
const int    xnbin = 100;
const double xmin  = -0.3;
const double xmax  = 0.3;
const int    ynbin = 100;
const double ymin  = -100;
const double ymax  = 100;

void macro(string fname){
    double x, xp, y, yp, phi, w, P;
    double xxsum = 0;
    double xpxpsum = 0;
    double xxpsum = 0;
    double nline = 0;
    ifstream rf(fname.c_str());
    getline(rf, strtmp);
    fH = new TH2F("fH","", xnbin, xmin, xmax, ynbin ,ymin, ymax);
    // while(rf >> x >> xp >> y >> yp >> phi >> w){
    while(rf >> x >> xp >> y >> yp >> P){
        fH -> Fill(x,xp);
        xxsum   += x*x;
        xpxpsum += xp*xp;
        xxpsum  += x*xp;
        nline +=1;
    }

    cout << "emittance = " << sqrt(xxsum * xpxpsum - xxpsum * xxpsum)/nline << endl;

    fH->Draw("colz");
}
