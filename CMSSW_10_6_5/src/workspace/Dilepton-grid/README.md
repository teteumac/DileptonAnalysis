# Dilepton Analysis

Workflow of the analysis.

## Files

The ntp1 files, generated from MakeClass on the ntpules of interest, are the files where I'm applying all the selection criteria, filling the histograms and obtaining the main variables for this analysis.

```
histos_data , ntp1-miniaod_data.C , ntp1.h
```

Analyze the data ntuples. The output root files are in the *histos_data* folder.

```
ntp1-miniaod_MC.C , ntp1.h
```

Analyze the signal MC ntuples. The output root files are in the *histos_MC* folder.

```
ntp1-miniaod_MC_pileup.C , ntp1_pileup.h
```

Analyze the background MC ntuples. The output root files are in the *histos_MC* folder.

*PS.: All root files are created using HTCondor, where I run all ntp1 files, use "hadd" method to cluster them and put on these folders. More information on the using of HTCondor on this analysis on condor folder.*

```
pol_function.C
```

From gaussian fit using proton resolution information from signal MC, draws a first degree polynomial (σ x ξ). 

```
draw_band.py
```

From the functions generated from pol_function.C and requiring 2σ to consider an event compatible, draws a "matching" band 
on 2D proton ξ graphs. The output pngs are in the *results* folder.

```
CompHistos_new.C
```

Takes all histograms generated from ntp1 files, apply scale factors on MC histograms, put them in the same Canvas using
THStack method, where filled bars are the MC ones and the dots are data. The output pngs are in the *comp_new* folder.

```
pixelEfficiencies.root , PreliminaryEfficiencies_October92019_1D2DMultiTrack.root
```

Efficiencies (radiation damage and multitrack) used on signal MC. 

```
pileup_protons/pileup_protons.C , pileup_protons/pileup_protons.h
```

Creates pileup proton events from electron-gamma ntuples, where I mix them on the background MC events.

