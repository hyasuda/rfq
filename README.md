# RFQ output data

This folder has the data of RFQ output.
There are some data, which is different condition.
Base data is rfqll.dsta or rfqll.dat. These are the output data from RFQ simulation.

### rfqll.dat ( from Otani-san )
        x[cm]	x'[rad]         y[cm]   y'[rad]         phase[deg]	KineticEnergy[MeV] !! Wrong Uinit !!
        x[mm]	x'[mrad]        y[mm]   y'[mrad]         phase[deg]	KineticEnergy[MeV]

### rfqll_output.dat
    - Convert the original file (rfqll.dat) to TurtleFile format.
        x[cm]   x'[mrad]        y[cm]   y'[mrad]        P[GeV]

### rfqll_trans.dat
    - Times transfer matrix, using "~/macro/muonLinac/rfq/transfer.cc" .
    - Transfer matrix is made by TRACE3D "~/data/muonLinac/TRACE3D/RFQoutput_4QM_gap_matching.t3d"
        x[mm]	x'[mrad]        y[mm]   y'[mrad]         phase[deg]	KineticEnergy[MeV]

### rfqll_trans_output.dat
    - Convert the transfered file (rfqll_trans.dat) to TurtleFile format.
        x[cm]   x'[mrad]        y[cm]   y'[mrad]        P[GeV]
