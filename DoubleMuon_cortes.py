from __future__ import print_function, division

import pandas as pd
import matplotlib.pyplot as plt
import h5py
import csv
import numpy as np
from numpy import array 
import TLorentzVector
import uproot_methods.convert
import math

def TLV(x, y, z):
	return uproot_methods.TLorentzVectorArray.from_ptetaphim(x,y,z,0.1057)

# Para dar aos argumentos das funções, precisa ser o TLorentzVector

def Acoplanaridade(x,y):
	return pd.DataFrame(1 - abs(x.delta_phi(y))/math.pi, columns = ['acoplanaridade'])
	

def MassaInvariante(x,y):
	return pd.DataFrame((x + y).mass, columns = ['inv_mass'])	

def	DeltaEta(x,y):
	return pd.DataFrame((x.rapidity - y.rapidity), columns=['delta_eta'])

def Pt(x,y):
	return pd.DataFrame((x+y).pt, columns = ['Pt'])		



DF_ptetphi1 = pd.DataFrame(np.delete((np.array(pd.read_csv('DF_ptetaphi_E1.csv'))),0,1), columns = ['pt1','pt2','eta1','eta2','phi1','phi2'])
DF_ptetphi2 = pd.DataFrame(np.delete((np.array(pd.read_csv('DF_ptetaphi_E2.csv'))),0,1), columns = ['pt1','pt2','eta1','eta2','phi1','phi2'])
DF_ptetphi3 = pd.DataFrame(np.delete((np.array(pd.read_csv('DF_ptetaphi_E3.csv'))),0,1), columns = ['pt1','pt2','eta1','eta2','phi1','phi2'])
DF_ptetphi  = pd.concat([DF_ptetphi1,DF_ptetphi2,DF_ptetphi3],axis=0)

# Vertice Primário

DataFrame_VertiPrima1 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_VertPrimaE1.csv'))),0,1), columns = ['VerticePrimario'])
DataFrame_VertiPrima2 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_VertPrimaE2.csv'))),0,1), columns = ['VerticePrimario'])
DataFrame_VertiPrima3 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_VertPrimaE3.csv'))),0,1), columns = ['VerticePrimario'])
DataFrame_VertiPrima  = pd.concat([DataFrame_VertiPrima1,DataFrame_VertiPrima2,DataFrame_VertiPrima3],axis=0)

# modulo

DataFrame_modulo1 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_moduloE1.csv'))),0,1), columns = ['almir1', 'almir2'])
DataFrame_modulo2 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_moduloE2.csv'))),0,1), columns = ['almir1', 'almir2'])
DataFrame_modulo3 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_moduloE3.csv'))),0,1), columns = ['almir1', 'almir2'])
DataFrame_modulo  = pd.concat([DataFrame_modulo1,DataFrame_modulo2,DataFrame_modulo3],axis=0)
# carga

DataFrame_carga1 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_chargeE1.csv'))),0,1), columns = ['carga1', 'carga2'])
DataFrame_carga2 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_chargeE2.csv'))),0,1), columns = ['carga1', 'carga2'])
DataFrame_carga3 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_chargeE3.csv'))),0,1), columns = ['carga1', 'carga2'])
DataFrame_carga  = pd.concat([DataFrame_carga1,DataFrame_carga2,DataFrame_carga3],axis=0)

# istigh

DataFrame_instight1 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_istightE1.csv'))),0,1), columns = ['instight1', 'instight2'])
DataFrame_instight2 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_istightE2.csv'))),0,1), columns = ['instight1', 'instight2'])
DataFrame_instight3 = pd.DataFrame(np.delete((np.array(pd.read_csv('Dados_istightE3.csv'))),0,1), columns = ['instight1', 'instight2'])
DataFrame_instight  = pd.concat([DataFrame_instight1,DataFrame_instight2,DataFrame_instight3],axis=0)

# Extra Tracks

DataFrame_extratracks1 = pd.DataFrame(np.delete((np.array(pd.read_csv('DF_ExtraTracksE1.csv'))),0,1), columns = ['ExtraTracks'])
DataFrame_extratracks2 = pd.DataFrame(np.delete((np.array(pd.read_csv('DF_ExtraTracksE2.csv'))),0,1), columns = ['ExtraTracks'])
DataFrame_extratracks3 = pd.DataFrame(np.delete((np.array(pd.read_csv('DF_ExtraTracksE3.csv'))),0,1), columns = ['ExtraTracks'])
DataFrame_extratracks  = pd.concat([DataFrame_extratracks1,DataFrame_extratracks2,DataFrame_extratracks3],axis=0)
#####################################################################################

dataset = pd.concat([DF_ptetphi, DataFrame_carga, DataFrame_VertiPrima, DataFrame_modulo, DataFrame_instight,DataFrame_extratracks], axis=1)

dataset = dataset.dropna() 

corte_pt1 = dataset.loc[dataset['pt1'] > 50]
corte_pt2 = corte_pt1.loc[corte_pt1['pt2'] > 50]


corte_oppos_charged_muon = corte_pt2.loc[corte_pt2['carga1']*corte_pt2['carga2'] < 0] 

corte_tight_muon_identification = corte_oppos_charged_muon.loc[corte_oppos_charged_muon['instight1']*corte_oppos_charged_muon['instight2']==1] 


TLV_0 = TLV(corte_tight_muon_identification['pt1'], corte_tight_muon_identification['eta1'], corte_tight_muon_identification['phi1'])
TLV_1 = TLV(corte_tight_muon_identification['pt2'], corte_tight_muon_identification['eta2'], corte_tight_muon_identification['phi2'])

DataFrame_Massa_inva = MassaInvariante(TLV_0,TLV_1)
DataFrame_DeltaEta = DeltaEta(TLV_0,TLV_1)
DF_PT = Pt(TLV_0,TLV_1)
DataFrame_Acopla = Acoplanaridade(TLV_0,TLV_1)
DataFrame_VerticePrima = abs(pd.DataFrame(np.array(corte_tight_muon_identification['VerticePrimario'])).rename(columns = {0:'vertice_prima'}))
DataFrame_almir = pd.DataFrame(np.array(corte_tight_muon_identification.loc[:,'almir1':'almir2'])).rename(columns = {0:'almir1',1:'almir2'})
DataFrame_extratracks = pd.DataFrame(np.array(corte_tight_muon_identification['ExtraTracks'])).rename(columns = {0:'ExtraTracks'})

amostra_doublemuon = pd.concat([DF_PT, DataFrame_Massa_inva, DataFrame_Acopla, DataFrame_DeltaEta, DataFrame_VerticePrima, DataFrame_almir,DataFrame_extratracks], axis = 1)


corte_MassaInvariante = amostra_doublemuon.loc[amostra_doublemuon['inv_mass'] > 110]

corte_VerticePriama = corte_MassaInvariante.loc[corte_MassaInvariante['vertice_prima'] < 15]

corte_almir = corte_VerticePriama.loc[corte_VerticePriama['almir1'] < 0.012].loc[corte_VerticePriama['almir2'] < 0.012]

corte_acoplanaridade = corte_almir.loc[corte_almir['acoplanaridade'] < 0.009]


amostra_doublemuon.to_csv('amostra_doublemuon.csv')
