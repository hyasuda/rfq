void rfqll(string fname){
    double x, xp, y, yp, phi, W;
    ifstream rf(fname.c_str());

    double xsum = 0;
    double xpsum = 0;
    double ysum = 0;
    double ypsum = 0;
    double phisum = 0;
    double Wsum = 0;
    int nline = 0;

    while(rf >> x >> xp >> y >> yp >> phi >> W){
        xsum   += x;
        xpsum  += xp;
        ysum   += y;
        ypsum  += yp;
        phisum += phi;
        Wsum   += W;
        nline++;
    }

    cout << "#####  AVERAGE  #####" << endl;

    cout << "x" << "\t" << "xp" << "\t" << "y" << "\t" << "yp" << "\t" << "phi" << "\t" << "W" << endl;
    cout << x/nline << "\t" << xp/nline << "\t" << y/nline << "\t" << yp/nline << "\t" << phi/nline << "\t" << W << endl;
}
