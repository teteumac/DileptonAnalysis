from __future__ import print_function, division

import pandas as pd
import matplotlib.pyplot as plt
import h5py
import csv
import numpy as np
from numpy import array 
from pylab import plot, show, legend, title, xlabel, ylabel
import pylab as pl
import numpy as np
from scipy.stats import argus
import uproot
import awkward
import mplhep as hep
import TLorentzVector

# -------------------- SIMULAÇÃO ------------------------ #

DataSet_signal_exclusivo = pd.DataFrame(np.delete((np.array(pd.read_csv('amostra_exclusivo.csv'))),0,1))
DataSet_signal_semiexclusivo = pd.DataFrame(np.delete((np.array(pd.read_csv('amostra_semiesclusivo.csv'))),0,1))
DataSet_signal = pd.concat([DataSet_signal_exclusivo,DataSet_signal_semiexclusivo], axis=0)
DataSet_backgraund = pd.DataFrame(np.delete((np.array(pd.read_csv('amostra_drellyan.csv'))),0,1))

DataSet2 = pd.concat([DataSet_signal,DataSet_backgraund], ignore_index=0),drop(7,axis=1)
dataset = DataSet2.rename(columns={0:'Pt', 1:'MassaInvariante', 2:'Acoplanaridade', 3: 'DeltaEta', 4:'vertice_prima', 5:'Almir1', 6:'Almir2'})

# ------------------------ DADOS ------------------------- #

DataFrame_DoubleMuon = pd.DataFrame(np.delete((np.array(pd.read_csv('amostra_doublemuon.csv'))),0,1))

# -------------------- NORMALIZACAO ---------------------- #

n_events_h_elastic = 200000
n_events_h_inel_el = 200000
n_events_h_dy = 48675378.
total_lumi = 37.498268
limit_lumi = 18.346268
rap_gap_surv_elastic = 0.89
rap_gap_surv_inel_el = 0.76
rap_gap_surv_inelastic = 0.13
number_of_samples = 100

scale_factor_elastic_x130 = limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic
scale_factor_inel_el_x130 = limit_lumi*rap_gap_surv_inel_el*0.025643500*1000 / n_events_h_inel_el 
scale_factor_dy = limit_lumi*5334000 / n_events_h_dy
scale_factor_dy_resample = limit_lumi*5334000 / ( n_events_h_dy*number_of_samples )

weight_signal_exclusivo = pd.DataFrame([scale_factor_elastic_x130]*len(DataSet_signal_exclusivo), columns = ['pesos'])
weight_signal_semiexclu = pd.DataFrame([scale_factor_inel_el_x130]*len(DataSet_signal_semiexclusivo), columns = ['pesos'])
weight_backgr = pd.DataFrame([scale_factor_dy]*len(DataSet_backgraund), columns = ['pesos'])
weight_dados = pd.DataFrame([1]*len(DataFrame_signal), columns = ['pesos'])

pesos = pd.concat([weight_signal_exclusivo,weight_signal_semiexclu,weight_backgr], axis=0)
#dataset = pd.concat([DataSet_signal, DataSet_backgraund], axis=0)
DataFrame = pd.concat([dataset,pesos], axis=1)

# ------------------ GRAFICAR -------------------------- #

DataFrame_DoubleMuon_pt = DataFrame_DoubleMuon[0]
DataFrame_DoubleMuon_delta_eta = DataFrame_DoubleMuon[3]
DataFrame_DoubleMuon_inv_mass = DataFrame_DoubleMuon[1]
DataFrame_DoubleMuon_acc = DataFrame_DoubleMuon[2]
DataFrame_DoubleMuon_vertiprima = DataFrame_DoubleMuon[4]


DataSet_signal_exclusivo_pt = DataSet_signal_exclusivo[0]
DataSet_signal_exclusivo_invmass = DataSet_signal_exclusivo[1]
DataSet_signal_exclusivo_acopla = DataSet_signal_exclusivo[2]
DataSet_signal_exclusivo_deltaeta = DataSet_signal_exclusivo[3]
DataSet_signal_exclusivo_vertiprima = DataSet_signal_exclusivo[4]


DataSet_signal_semiexclusivo_pt = DataSet_signal_semiexclusivo[0]
DataSet_signal_semiexclusivo_invmas = DataSet_signal_semiexclusivo[1]
DataSet_signal_semiexclusivo_acopla = DataSet_signal_semiexclusivo[2]
DataSet_signal_semiexclusivo_deltaeta = DataSet_signal_semiexclusivo[3]
DataSet_signal_semiexclusivo_vertiprima = DataSet_signal_semiexclusivo[4]


DataSet_backg_pt = DataSet_backgraund[0]
DataSet_backg_invmass = DataSet_backgraund[1]
DataSet_backg_acopla = DataSet_backgraund[2]
DataSet_backg_deltaeta = DataSet_backgraund[3]
DataSet_backg_verticeprima = DataSet_backgraund[4]


# --------------------------------- Gráficos da simulação  --------------------------------- #

import seaborn as sns
import coffea.hist as hist
import mplhep as hep


##################################################################################

# O primeiro número é a binagem e os outros dois são os limites na abscissa
histo = hist.Hist("Events",
        hist.Cat("sample", ""), # Os samples aparece na legenda dos gráficos
        hist.Bin("pt", "$P_{T}$", 20, 0, 20),
        hist.Bin("delta_eta", "$\Delta \eta$", 20, -3, 3),
        hist.Bin("massa_inv", "Invariante Mass", 20, 0, 600), 
        hist.Bin("acopla", "Acoplanarity", 20, 0, .12),   
        hist.Bin("vertiprima", "Primary Vertice", 20, 0, 15),                                               
        )
histo.fill(
    sample="Drell-Yan",
    pt=np.array(DataSet_backg_pt),
    delta_eta = np.array(DataSet_backg_deltaeta),    
    massa_inv = np.array(DataSet_backg_invmass),
    acopla = np.array(DataSet_backg_acopla),
    vertiprima = np.array(DataSet_backg_verticeprima),  
    weight = np.array(weight_backgr['pesos'])
    )
histo.fill(
    sample="Semiexclusivo",
    pt=np.array(DataSet_signal_semiexclusivo_pt),
    delta_eta = np.array(DataSet_signal_semiexclusivo_deltaeta),
    massa_inv = np.array(DataSet_signal_semiexclusivo_invmas),
    vertiprima = np.array(DataSet_signal_semiexclusivo_vertiprima),
    acopla = np.array(DataSet_signal_semiexclusivo_acopla),    
    weight = np.array(weight_signal_semiexclu['pesos'])
    )
histo.fill(
    sample="Exclusivo",
    pt=np.array(DataSet_signal_exclusivo_pt),
    delta_eta = np.array(DataSet_signal_exclusivo_deltaeta),
    massa_inv = np.array(DataSet_signal_exclusivo_invmass),
    acopla = np.array(DataSet_signal_exclusivo_acopla),    
    vertiprima = np.array(DataSet_signal_exclusivo_vertiprima),    
    weight = np.array(weight_signal_exclusivo['pesos'])
    )
histo.fill(
    sample="Data-2017",
    pt=np.array(DataFrame_DoubleMuon_pt),
    delta_eta = np.array(DataFrame_DoubleMuon_delta_eta),    
    massa_inv = np.array(DataFrame_DoubleMuon_inv_mass),
    acopla = np.array(DataFrame_DoubleMuon_acc),   
    vertiprima = np.array(DataFrame_DoubleMuon_vertiprima)
        )

plt.rcParams.update({
    'font.size': 14,
    'axes.titlesize': 18,
    'axes.labelsize': 18,
    'xtick.labelsize': 12,
    'ytick.labelsize': 12
})

fill_opts = {
    'edgecolor': (0,0,0,0.3),
    'alpha': 0.8
}
error_opts = {
    'label': 'Stat. Unc.',
    'hatch': '///',
    'facecolor': 'none',
    'edgecolor': (0,0,0,1),
    'linewidth': 0
}
data_err_opts = {
    'linestyle': 'none',
    'marker': '.',
    'markersize': 10.,
    'color': 'k',
    'elinewidth': 1,
}

import re
notdata = re.compile('(?!Data-2017)')


# ---------------------------------- PT ---------------------------------- #


pt1hist = histo.sum("delta_eta", "massa_inv", 'acopla', 'vertiprima')

hist.plot1d(
    pt1hist['Data-2017'],
    overlay="sample",
    clear=True,
    error_opts=data_err_opts,
    density = False
)
hist.plot1d(
    pt1hist[notdata],
    overlay='sample',
    stack=True,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],
    line_opts=True,
    fill_opts=fill_opts,
    error_opts=error_opts,
    density = False)

plt.yscale('log')
plt.ylim(10e-2,30e5)
plt.style.use([hep.style.ROOT, hep.style.firamath])
hep.cms.cmslabel()
plt.legend(loc="upper right")
plt.tight_layout()
plt.savefig('/home/matheus/nTuplas/algoritmos/graficos/graficos_MC/hist_pt_DoubleMuon.pdf')
plt.close()


# ---------------------------------- delta eta ---------------------------------- #

delta_etahist = histo.sum('pt', "massa_inv", 'acopla', 'vertiprima')

hist.plot1d(
    delta_etahist[notdata],
    overlay='sample',
    stack=True,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],
    line_opts=None,
    fill_opts=fill_opts,
    error_opts=error_opts 
)
hist.plot1d(
    delta_etahist['Data-2017'],
    overlay="sample",
    clear=False,
    error_opts=data_err_opts,
    density = False
)
plt.yscale('log')
plt.ylim(10e-2,30e6)
hep.cms.cmslabel()
plt.legend(loc="upper right")
plt.tight_layout()
plt.savefig('/home/matheus/nTuplas/algoritmos/graficos/graficos_MC/hist_delta_eta_DoubleMuon.pdf')
plt.close()

# ---------------------------------- massa invariante ---------------------------------- #

masshist = histo.sum("pt", "delta_eta", 'acopla', 'vertiprima')

hist.plot1d(
    masshist[notdata],
    overlay='sample',
    stack=True,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],    
    line_opts=None,
    fill_opts=fill_opts,
    error_opts=error_opts 
)
hist.plot1d(
    masshist['Data-2017'],
    overlay="sample",
    clear=False,
    error_opts=data_err_opts,
    density = False
)
plt.ylim(10e-1,10e6)
plt.yscale('log')
hep.cms.cmslabel()
plt.legend(loc="upper right")
plt.tight_layout()
plt.savefig('/home/matheus/nTuplas/algoritmos/graficos/graficos_MC/hist_inv_mass_DoubleMuon.pdf')
plt.close()

# ---------------------------------- Acoplanaridade ---------------------------------- #

acchist = histo.sum('pt', 'massa_inv', 'delta_eta', 'vertiprima')

hist.plot1d(
    acchist[notdata],
    overlay='sample',
    stack=True,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],    
    line_opts=None,
    fill_opts=fill_opts,
    error_opts=error_opts 
)
hist.plot1d(
    acchist['Data-2017'],
    overlay="sample",
    clear=False,
    error_opts=data_err_opts,
    density = False
)
plt.ylim(10e-3,10e6)
plt.yscale('log')
hep.cms.cmslabel()
plt.legend(loc="upper right")
plt.tight_layout()
plt.savefig('/home/matheus/nTuplas/algoritmos/graficos/graficos_MC/hist_acopla_DoubleMuon.pdf')
plt.close()


# ---------------------------------- vertice primario ---------------------------------- #


vertprimahist = histo.sum('pt', 'massa_inv', 'delta_eta', 'acopla')

hist.plot1d(
    vertprimahist[notdata],
    overlay='sample',
    stack=True,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],    
    line_opts=None,
    fill_opts=fill_opts,
    error_opts=error_opts     
)
hist.plot1d(
    vertprimahist['Data-2017'],
    overlay="sample",
    clear=False,
    error_opts=data_err_opts,
    density = False
)
plt.yscale('log')
plt.ylim(0, 10e6) 
hep.cms.cmslabel()
plt.legend(loc="upper right")
plt.tight_layout()
plt.savefig('/home/matheus/nTuplas/algoritmos/graficos/graficos_MC/hist_vertiprima_DoubleMuon.pdf')
plt.close()
