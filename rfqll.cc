void rfqll(string fname){
    double x, xp, y, yp, phi, W;
    ifstream rf(Form("/Users/YASUDA/data/muonLinac/rfq/%s", fname.c_str()));

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
    cout << "Enrty = " << nline << endl;
    cout << "x" << "\t" << "xp" << "\t" << "y" << "\t" << "yp" << "\t" << "phi" << "\t" << "W" << endl;
    cout << xsum/nline << "\t" << xpsum/nline << "\t" << ysum/nline << "\t" << ypsum/nline << "\t" << phisum/nline << "\t" << Wsum/nline << endl;
}
