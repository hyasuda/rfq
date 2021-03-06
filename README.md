# RFQ output data and macro

This folder has the data of RFQ output.
There are some data, which is different condition.
Base data is rfqll.dsta or rfqll.dat. These are the output data from RFQ simulation.


## RFQ output macro "~/macro/muonLinac/rfq/"

### rfq_ttf_conv.cc (string inputfile , string outputfile)
    - Convert the original file (rfqll.dat) to TurtleFile format.

### transfer.cc (string outputfile = "rfqll_trans.dat")
    - Times transfer matrix R[i][j]
    - before trans :: x[mm]	x'[mrad]        y[mm]   y'[mrad]         z[mm]          Delta_P/P[mrad]

### rfqll.cc (string fname)
    - Derive the average of all components from RFQ output raw data "rfqll.dat"

### macro.cc
    - for test

###

## RFQ output data file "~/data/muonLinac/rfq/"

### rfqll.dat ( from Otani-san )
        x[cm]	x'[rad]         y[cm]   y'[rad]         phase[deg]	KineticEnergy[MeV] !! Wrong Uinit !!
        x[mm]	x'[mrad]        y[mm]   y'[mrad]         phase[deg]	KineticEnergy[MeV]

### rfqll_output.dat
    - Convert the original file (rfqll.dat) to TurtleFile format.
        x[cm]   x'[mrad]        y[cm]   y'[mrad]        P[GeV]

### rfqll_trans.dat
    - Times transfer matrix, using "~/macro/muonLinac/rfq/transfer.cc" .
    - exclude kinetic energy < 0 data  :  Entry is 16,116 -> 16,114  (2 data is died)
    - Transfer matrix is made by TRACE3D "~/data/muonLinac/TRACE3D/RFQoutput_4QM_gap_matching.t3d"
        x[mm]	x'[mrad]        y[mm]   y'[mrad]         phase[deg]	KineticEnergy[MeV]

### rfqll_trans_01.dat
    - change the unit as below
    - origin       :: x[mm]	x'[mrad]        y[mm]   y'[mrad]         phase[deg]	KineticEnergy[MeV]
    - before trans :: x[mm]	x'[mrad]        y[mm]   y'[mrad]         z[mm]          Delta_P/P[mrad]

### rfqll_trans_02.dat
    - Using for musr_545.root simulation.
    - This is transffered by alpha = 0 beam line designed by TRACE3D
    - before trans :: x[mm]	x'[mrad]        y[mm]   y'[mrad]         z[mm]          Delta_P/P[mrad]

### rfqll_trans_test.dat
    - For test of "~/macro/muonLinac/rfq/transfer.cc"

### rfqll_trans_output.dat
    - Convert the transfered file (rfqll_trans.dat) to TurtleFile format.
        x[cm]   x'[mrad]        y[cm]   y'[mrad]        P[GeV]

### rfqll_tr.data
    - Finalized data of transferred by alpha = 0 beam line (TRACE3D)

### rfqll_tr_ttf.data
    - Finalized Turtle data of transferred by alpha = 0 beam line (TRACE3D)
