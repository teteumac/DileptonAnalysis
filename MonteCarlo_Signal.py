from __future__ import absolute_import

import os
import sys
import struct
import uuid
import csv

import uproot_methods.convert
import uproot.const
import uproot.source.file
import uproot.write.compress
import uproot.write.sink.cursor
import uproot.write.sink.file
import uproot.write.streamers
import uproot.write.TDirectory
import uproot.write.TFree
import uproot.write.TKey
from uproot.rootio import nofilter
from uproot.write.objects.util import Util
from uproot.write.objects.TTree import TTree

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

import math
import TLorentzVector
from pandas import DataFrame

# TlorentzVector

def TLV(x, y, z):
	return uproot_methods.TLorentzVectorArray.from_ptetaphim(x,y,z,0.1057)

# Para dar aos argumentos das funções, precisa ser o TLorentzVector

def Acoplanaridade(x,y):
	return pd.DataFrame(1 - abs(x.delta_phi(y))/math.pi, columns = ['acoplanaridade'])
	
def MassaInvariante(x,y):
	return pd.DataFrame((x + y).mass, columns = ['inv_mass'])	

def DeltaEta(x,y):
        return pd.DataFrame((x.rapidity - y.rapidity), columns=['delta_eta'])

def Pt(x,y):
	return pd.DataFrame((x+y).pt, columns = ['Pt'])	

def deltaPhi(x,y):
    return (x - y + math.pi) % (2*math.pi) - math.pi
   


# -------------------------------------------------------------- #

## Abrindo os arquivos .root pelo uproot Para o caso INELÁSTICO ##

# -------------------------------------------------------------- #

TTree_inel = uproot.open('~/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/output_inel-el_xangle130.root')['ggll_miniaod']['ntp1']
#TTree_inel_show = TTree_inel.show() # Para mostrar todos as branches da nTupla

#protons = uproot.open('/home/matheus/nTuplas/algoritmos/pileup_protons_EG.root')['pileup_protons']
nPfCand_inel = TTree_inel.array('nPfCand')
PfCand_fromPV_inel = DataFrame(TTree_inel.array('PfCand_fromPV'))[0]
PfCand_phi = DataFrame(TTree_inel.array('PfCand_phi'))
PfCand_eta = DataFrame(TTree_inel.array('PfCand_eta'))

DF_MuPt_inel              = pd.DataFrame(TTree_inel.array('MuonCand_pt')).rename(columns={0:'pt1', 1:'pt2'}).drop(2, axis=1)
DF_MuEta_inel             = pd.DataFrame(TTree_inel.array('MuonCand_eta')).rename(columns = {0:'eta1', 1:'eta2'}).drop(2, axis=1) 
DF_Muphi_inel             = pd.DataFrame(TTree_inel.array('MuonCand_phi')).rename(columns = {0:'phi1', 1:'phi2'}).drop(2, axis=1)

DF_ptetaphi_inel = pd.concat([DF_MuPt_inel, DF_MuEta_inel, DF_Muphi_inel], axis = 1)

DF_PrimVertexCand_z_inel = pd.DataFrame(abs(pd.DataFrame(TTree_inel.array('PrimVertexCand_z'))[0])).rename(columns = {0: 'vertice_prima'})
DF_charge_inel           = pd.DataFrame(TTree_inel.array('MuonCand_charge')).drop([2],axis=1).rename(columns = {0:'carga1',1:'carga2'})
DF_MuonCand_vtxz_inel    = pd.DataFrame(TTree_inel.array('MuonCand_vtxz')).drop([2], axis=1).rename(columns={0:'muon1', 1:'muon2'})
DF_MuonCand_istight_inel = pd.DataFrame(TTree_inel.array('MuonCand_istight')).drop([2], axis = 1).rename(columns={0:'istight1', 1:'istight2'})

# modulo do muon - vertice primario
DF_Modulo1inel = pd.DataFrame(abs(DF_MuonCand_vtxz_inel['muon1'] - DF_PrimVertexCand_z_inel['vertice_prima'])).rename(columns = {0:'almir1'})
DF_Modulo2inel = pd.DataFrame(abs(DF_MuonCand_vtxz_inel['muon2'] - DF_PrimVertexCand_z_inel['vertice_prima'])).rename(columns = {0:'almir2'})


TLV_0_inel = TLV(DF_MuPt_inel['pt1'], DF_MuEta_inel['eta1'], DF_Muphi_inel['phi1'])
TLV_1_inel = TLV(DF_MuPt_inel['pt2'], DF_MuEta_inel['eta2'], DF_Muphi_inel['phi2'])

'''
# Tentativa de calcular o número de traços extras

contador_PV3 = 0

for i in range(0,len(nPfCand_inel)):

	mylist = pow(pow(deltaPhi(PfCand_phi[i],TLV_0_inel.phi),2) + pow(PfCand_eta[i]-TLV_0_inel.eta,2), 0.5) 
	mylist2 = pow(pow(deltaPhi(PfCand_phi[i],TLV_1_inel.phi),2) + pow(PfCand_eta[i]-TLV_1_inel.eta,2), 0.5)
	
	for value_list1[i], value_list2[i] in zip(mylist, mylist2):

		#print (f"value_list1 {value_list1} \t value_list2 {value_list1}")

		if (value_list1[i] > 0.3 and value_list2[i] > 0.3):
			contador_PV3+=1
import itertools
it = (i for i in range(0,len(nPfCand_inel)))
mylist = pow(pow(deltaPhi(PfCand_phi,TLV_0_inel.phi),2) + pow(PfCand_eta-TLV_0_inel.eta,2), 0.5)
mylist2 = pow(pow(deltaPhi(PfCand_phi,TLV_1_inel.phi),2) + pow(PfCand_eta-TLV_1_inel.eta,2), 0.5)
a = itertools.dropwhile(mylist > 0.3 and mylist2 > 0.3, enumerate(it))
list(a)							
							
'''				
# -------------------------------------------------------------- #

## Abrindo os arquivos .root pelo uproot Para o caso ELÁSTICO   ##

# -------------------------------------------------------------- #


TTree_elas = uproot.open('~/GGToMuMu_Pt-50_Elastic_13TeV-lpair/output_elastic_xangle130.root')['ggll_miniaod']['ntp1']
#TTree_elas = TTree_elas.show() # Para mostrar todos as branches da nTupla

nPfCand_elas = pd.DataFrame(TTree_elas.array('nPfCand'))[0]

DF_MuPt_elas_             = pd.DataFrame(TTree_elas.array('MuonCand_pt')).rename(columns={0:'pt1', 1:'pt2'}).drop(2, axis=1)
DF_MuEta_elas             = pd.DataFrame(TTree_elas.array('MuonCand_eta')).rename(columns = {0:'eta1', 1:'eta2'}).drop(2, axis=1)
DF_Muphi_elas             = pd.DataFrame(TTree_elas.array('MuonCand_phi')).rename(columns = {0:'phi1', 1:'phi2'}).drop(2, axis=1)
DF_ptetaphi_elas = pd.concat([DF_MuPt_elas_, DF_MuEta_elas, DF_Muphi_elas], axis = 1)

DF_PrimVertexCand_z_elas = pd.DataFrame(abs(pd.DataFrame(TTree_elas.array('PrimVertexCand_z'))[0])).rename(columns = {0:'vertice_prima'})
DF_charge_elas           = pd.DataFrame(TTree_elas.array('MuonCand_charge')).drop([2],axis=1).rename(columns = {0:'carga1',1:'carga2'})
DF_MuonCand_vtxz_elas    = pd.DataFrame(TTree_elas.array('MuonCand_vtxz')).rename(columns={0:'muon1', 1:'muon2'}).drop(2, axis=1)
DF_MuonCand_istight_elas = pd.DataFrame(TTree_elas.array('MuonCand_istight')).rename(columns={0:'istight1', 1:'istight2'}).drop(2, axis=1)

# modulo do muon - vertice primario
DF_Modulo1elas = pd.DataFrame(abs(DF_MuonCand_vtxz_elas['muon1'] - DF_PrimVertexCand_z_elas['vertice_prima'])).rename(columns = {0:'almir1'})
DF_Modulo2elas = pd.DataFrame(abs(DF_MuonCand_vtxz_elas['muon2'] - DF_PrimVertexCand_z_elas['vertice_prima'])).rename(columns = {0:'almir2'})


# ----------------------- CORTES NO SIGNAL EXCLUSIVO ----------------------- #


signal_exclusivo = pd.concat([DF_ptetaphi_elas,DF_charge_elas, DF_PrimVertexCand_z_elas, DF_Modulo1elas, DF_Modulo2elas, DF_MuonCand_istight_elas, nPfCand_elas], axis=1)

signal_exclusivo = signal_exclusivo.dropna() # eliminar eventos com NaN

corte_pt_exclusivo = signal_exclusivo.loc[signal_exclusivo['pt1'] > 50].loc[signal_exclusivo['pt2'] > 50] # corte no Pt acima de 50 GeV

corte_oppos_charged_muon_exclusivo = corte_pt_exclusivo.loc[corte_pt_exclusivo['carga1']*signal_exclusivo['carga2'] < 0] # Selecionando Muons de cargas opostas

corte_tight_muon_identification_exclusivo = corte_oppos_charged_muon_exclusivo.loc[corte_oppos_charged_muon_exclusivo['istight1']*corte_oppos_charged_muon_exclusivo['istight2']==1] # identificação dos Muons

DF_MuPt_elas_ = corte_tight_muon_identification_exclusivo.loc[:,'pt1':'pt2']
DF_MuEta_elas = corte_tight_muon_identification_exclusivo.loc[:, 'eta1':'eta2']
DF_Muphi_elas = corte_tight_muon_identification_exclusivo.loc[:, 'phi1':'phi2']

TLV_0_elas = TLV(DF_MuPt_elas_['pt1'], DF_MuEta_elas['eta1'], DF_Muphi_elas['phi1'])
TLV_1_elas = TLV(DF_MuPt_elas_['pt2'], DF_MuEta_elas['eta2'], DF_Muphi_elas['phi2'])

Acc_elas = Acoplanaridade(TLV_0_elas,TLV_1_elas)
Delta_Eta_elas = DeltaEta(TLV_0_elas,TLV_1_elas)
DF_M_inv_elas = MassaInvariante(TLV_0_elas,TLV_1_elas)
DF_MuPt_elas = Pt(TLV_0_elas,TLV_1_elas)
DF_VerticePrima_elas = pd.DataFrame(np.array(corte_tight_muon_identification_exclusivo['vertice_prima'])).rename(columns = {0:'vertice_prima'})
DF_Almir_elas = pd.DataFrame(np.array(corte_tight_muon_identification_exclusivo.loc[:,'almir1':'almir2'])).rename(columns = {0:'almir1',1:'almir2'})
DF_nPfCand_elas = pd.DataFrame(np.array(corte_tight_muon_identification_exclusivo[0]), columns = ['extra_tracks'])

amostra_exclusivo = pd.concat([DF_MuPt_elas, DF_M_inv_elas, Acc_elas, Delta_Eta_elas, DF_VerticePrima_elas, DF_Almir_elas, DF_nPfCand_elas], axis = 1)

amostra_exclusivo.to_csv('amostra_exclusivo.csv')


####################### CORTES NO SEMI-EXCLUSIVO #######################


signal_simiexclusivo = pd.concat([DF_ptetaphi_inel, DF_charge_inel, DF_PrimVertexCand_z_inel, DF_Modulo1inel, DF_Modulo2inel, DF_MuonCand_istight_inel, nPfCand_inel], axis=1)

signal_simiexclusivo = signal_simiexclusivo.dropna() # eliminar eventos com NaN

corte_pt_semiexclusivo = signal_simiexclusivo.loc[signal_simiexclusivo['pt1'] > 50].loc[signal_simiexclusivo['pt2'] > 50] # corte no Pt acima de 50 GeV

corte_oppos_charged_muon_semiexclusivo = corte_pt_semiexclusivo.loc[corte_pt_semiexclusivo['carga1']*corte_pt_semiexclusivo['carga2'] < 0] #  Selecionando Muons de cargas opostas

corte_tight_muon_identification_semiexclusivo = corte_oppos_charged_muon_semiexclusivo.loc[corte_oppos_charged_muon_semiexclusivo['istight1']*corte_oppos_charged_muon_semiexclusivo['istight2']==1] # identificação dos Muons

DF_MuPt_inel_ = corte_tight_muon_identification_semiexclusivo.loc[:, 'pt1':'pt2']
DF_MuEta_inel = corte_tight_muon_identification_semiexclusivo.loc[:, 'eta1':'eta2']
DF_Muphi_inel = corte_tight_muon_identification_semiexclusivo.loc[:, 'phi1':'phi2']

TLV_0_inel = TLV(DF_MuPt_inel_['pt1'], DF_MuEta_inel['eta1'], DF_Muphi_inel['phi1'])
TLV_1_inel = TLV(DF_MuPt_inel_['pt2'], DF_MuEta_inel['eta2'], DF_Muphi_inel['phi2'])

Acc_inel = Acoplanaridade(TLV_0_inel,TLV_1_inel)
Delta_Eta_inel = DeltaEta(TLV_0_inel,TLV_1_inel)
DF_M_inv_inel = MassaInvariante(TLV_0_inel,TLV_1_inel)
DF_MuPt_inel = Pt(TLV_0_inel,TLV_1_inel)
DF_VerticePrima_inel = pd.DataFrame(np.array(corte_tight_muon_identification_semiexclusivo['vertice_prima'])).rename(columns = {0:'vertice_prima'})
DF_Almir_inel = pd.DataFrame(np.array(corte_tight_muon_identification_semiexclusivo.loc[:,'almir1':'almir2'])).rename(columns = {0:'almir1',1:'almir2'})
DF_nPfCand_inel = pd.DataFrame(np.array(corte_tight_muon_identification_semiexclusivo[0]), columns = ['extra_tracks'])

amostra_semiesclusivo = pd.concat([DF_MuPt_inel, DF_M_inv_inel, Acc_inel, Delta_Eta_inel, DF_VerticePrima_inel, DF_Almir_inel,DF_nPfCand_inel], axis = 1)

amostra_semiesclusivo.to_csv('amostra_semiesclusivo.csv')
