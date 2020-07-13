from __future__ import absolute_import

import os
import sys
import struct
import uuid
import h5py

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


TTree_0 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_0.root')['ggll_miniaod']['ntp1']
TTree_1 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_1.root')['ggll_miniaod']['ntp1']
TTree_2 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_2.root')['ggll_miniaod']['ntp1']
TTree_3 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_3.root')['ggll_miniaod']['ntp1']
TTree_4 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_4.root')['ggll_miniaod']['ntp1']
TTree_5 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_5.root')['ggll_miniaod']['ntp1']
TTree_6 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_6.root')['ggll_miniaod']['ntp1']
TTree_7 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_7.root')['ggll_miniaod']['ntp1']
TTree_8 = uproot.open('~/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_8.root')['ggll_miniaod']['ntp1']

#############################################################################
## ------------------------------------------------------------------------##
#############################################################################

DF_MuPt_0 = pd.DataFrame(TTree_0.array('MuonCand_pt'))
DF_MuEta_0 = pd.DataFrame(TTree_0.array('MuonCand_eta'))
DF_Muphi_0 = pd.DataFrame(TTree_0.array('MuonCand_phi'))
DF_PrimVertexCand_z_0 = pd.DataFrame(TTree_0.array('PrimVertexCand_z'))
DF_charge_0           = pd.DataFrame(TTree_0.array('MuonCand_charge'))
DF_MuonCand_vtxz_0    = pd.DataFrame(TTree_0.array('MuonCand_vtxz'))
DF_MuonCand_istight_0 = pd.DataFrame(TTree_0.array('MuonCand_istight'))
DF_nPfCand_0 = pd.DataFrame(TTree_0.array('nPfCand'))

#############################################################################

DF_MuPt_1 = pd.DataFrame(TTree_1.array('MuonCand_pt'))
DF_MuEta_1 = pd.DataFrame(TTree_1.array('MuonCand_eta'))
DF_Muphi_1 = pd.DataFrame(TTree_1.array('MuonCand_phi'))
DF_PrimVertexCand_z_1 = pd.DataFrame(TTree_1.array('PrimVertexCand_z'))
DF_charge_1           = pd.DataFrame(TTree_1.array('MuonCand_charge'))
DF_MuonCand_vtxz_1    = pd.DataFrame(TTree_1.array('MuonCand_vtxz'))
DF_MuonCand_istight_1 = pd.DataFrame(TTree_1.array('MuonCand_istight'))
DF_nPfCand_1 = pd.DataFrame(TTree_1.array('nPfCand'))

#############################################################################

DF_MuPt_2 = pd.DataFrame(TTree_2.array('MuonCand_pt'))
DF_MuEta_2 = pd.DataFrame(TTree_2.array('MuonCand_eta'))
DF_Muphi_2 = pd.DataFrame(TTree_2.array('MuonCand_phi'))
DF_PrimVertexCand_z_2 = pd.DataFrame(TTree_2.array('PrimVertexCand_z'))
DF_charge_2           = pd.DataFrame(TTree_2.array('MuonCand_charge'))
DF_MuonCand_vtxz_2    = pd.DataFrame(TTree_2.array('MuonCand_vtxz'))
DF_MuonCand_istight_2 = pd.DataFrame(TTree_2.array('MuonCand_istight'))
DF_nPfCand_2 = pd.DataFrame(TTree_2.array('nPfCand'))

#############################################################################

DF_MuPt_3 = pd.DataFrame(TTree_3.array('MuonCand_pt'))
DF_MuEta_3 = pd.DataFrame(TTree_3.array('MuonCand_eta'))
DF_Muphi_3 = pd.DataFrame(TTree_3.array('MuonCand_phi'))
DF_PrimVertexCand_z_3 = pd.DataFrame(TTree_3.array('PrimVertexCand_z'))
DF_charge_3           = pd.DataFrame(TTree_3.array('MuonCand_charge'))
DF_MuonCand_vtxz_3    = pd.DataFrame(TTree_3.array('MuonCand_vtxz'))
DF_MuonCand_istight_3 = pd.DataFrame(TTree_3.array('MuonCand_istight'))
DF_nPfCand_3 = pd.DataFrame(TTree_3.array('nPfCand'))

#############################################################################

DF_MuPt_4 = pd.DataFrame(TTree_4.array('MuonCand_pt'))
DF_MuEta_4 = pd.DataFrame(TTree_4.array('MuonCand_eta'))
DF_Muphi_4 = pd.DataFrame(TTree_4.array('MuonCand_phi'))
DF_PrimVertexCand_z_4 = pd.DataFrame(TTree_4.array('PrimVertexCand_z'))
DF_charge_4           = pd.DataFrame(TTree_4.array('MuonCand_charge'))
DF_MuonCand_vtxz_4    = pd.DataFrame(TTree_4.array('MuonCand_vtxz'))
DF_MuonCand_istight_4 = pd.DataFrame(TTree_4.array('MuonCand_istight'))
DF_nPfCand_4 = pd.DataFrame(TTree_4.array('nPfCand'))

#############################################################################

DF_MuPt_5 = pd.DataFrame(TTree_5.array('MuonCand_pt'))
DF_MuEta_5 = pd.DataFrame(TTree_5.array('MuonCand_eta'))
DF_Muphi_5 = pd.DataFrame(TTree_5.array('MuonCand_phi'))
DF_PrimVertexCand_z_5 = pd.DataFrame(TTree_5.array('PrimVertexCand_z'))
DF_charge_5           = pd.DataFrame(TTree_5.array('MuonCand_charge'))
DF_MuonCand_vtxz_5    = pd.DataFrame(TTree_5.array('MuonCand_vtxz'))
DF_MuonCand_istight_5 = pd.DataFrame(TTree_5.array('MuonCand_istight'))
DF_nPfCand_5 = pd.DataFrame(TTree_5.array('nPfCand'))

#############################################################################

DF_MuPt_6 = pd.DataFrame(TTree_6.array('MuonCand_pt'))
DF_MuEta_6 = pd.DataFrame(TTree_6.array('MuonCand_eta'))
DF_Muphi_6 = pd.DataFrame(TTree_6.array('MuonCand_phi'))
DF_PrimVertexCand_z_6 = pd.DataFrame(TTree_6.array('PrimVertexCand_z'))
DF_charge_6           = pd.DataFrame(TTree_6.array('MuonCand_charge'))
DF_MuonCand_vtxz_6    = pd.DataFrame(TTree_6.array('MuonCand_vtxz'))
DF_MuonCand_istight_6 = pd.DataFrame(TTree_6.array('MuonCand_istight'))
DF_nPfCand_6 = pd.DataFrame(TTree_6.array('nPfCand'))

#############################################################################

DF_MuPt_7 = pd.DataFrame(TTree_7.array('MuonCand_pt'))
DF_MuEta_7 = pd.DataFrame(TTree_7.array('MuonCand_eta'))
DF_Muphi_7 = pd.DataFrame(TTree_7.array('MuonCand_phi'))
DF_PrimVertexCand_z_7 = pd.DataFrame(TTree_7.array('PrimVertexCand_z'))
DF_charge_7           = pd.DataFrame(TTree_7.array('MuonCand_charge'))
DF_MuonCand_vtxz_7    = pd.DataFrame(TTree_7.array('MuonCand_vtxz'))
DF_MuonCand_istight_7 = pd.DataFrame(TTree_7.array('MuonCand_istight'))
DF_nPfCand_7 = pd.DataFrame(TTree_7.array('nPfCand'))

#############################################################################

DF_MuPt_8 = pd.DataFrame(TTree_8.array('MuonCand_pt'))
DF_MuEta_8 = pd.DataFrame(TTree_8.array('MuonCand_eta'))
DF_Muphi_8 = pd.DataFrame(TTree_8.array('MuonCand_phi'))
DF_PrimVertexCand_z_8 = pd.DataFrame(TTree_8.array('PrimVertexCand_z'))
DF_charge_8           = pd.DataFrame(TTree_8.array('MuonCand_charge'))
DF_MuonCand_vtxz_8    = pd.DataFrame(TTree_8.array('MuonCand_vtxz'))
DF_MuonCand_istight_8 = pd.DataFrame(TTree_8.array('MuonCand_istight'))
DF_nPfCand_8 = pd.DataFrame(TTree_8.array('nPfCand'))

#####################################################################################################

DF_pt = pd.concat([DF_MuPt_0, DF_MuPt_1, DF_MuPt_2, DF_MuPt_3, DF_MuPt_4, DF_MuPt_5, DF_MuPt_6, DF_MuPt_7, DF_MuPt_8], axis = 0, ignore_index = True).rename(columns={0:'pt1', 1:'pt2'}).drop([2,3,4],axis=1)
DF_eta = pd.concat([DF_MuEta_0, DF_MuEta_1, DF_MuEta_2, DF_MuEta_3, DF_MuEta_4, DF_MuEta_5, DF_MuEta_6, DF_MuEta_7, DF_MuEta_8], axis = 0, ignore_index = True).rename(columns={0:'eta1', 1:'eta2'}).drop([2,3,4],axis=1)
DF_phi = pd.concat([DF_Muphi_0, DF_Muphi_1, DF_Muphi_2, DF_Muphi_3, DF_Muphi_4, DF_Muphi_5, DF_Muphi_6, DF_Muphi_7, DF_Muphi_8], axis = 0, ignore_index = True).rename(columns={0:'phi1', 1:'phi2'}).drop([2,3,4],axis=1)
DF_muetaphi = pd.concat([DF_pt, DF_eta, DF_phi], axis = 1)


# CARGA DO MUON
DF_charge = pd.concat([DF_charge_0,DF_charge_1,DF_charge_2,DF_charge_3,DF_charge_4, DF_charge_5, 
DF_charge_6, DF_charge_7, DF_charge_8], axis=0, ignore_index = True).drop([2,3,4], axis = 1).rename(columns={0:'carga1', 1:'carga2'})

# POSIÇÃO DO VÉRTICE PRIMÁRIO
DF_PrimVertexCand_z = pd.DataFrame(abs(pd.concat([DF_PrimVertexCand_z_0[0],DF_PrimVertexCand_z_1[0],DF_PrimVertexCand_z_2[0],DF_PrimVertexCand_z_3[0],DF_PrimVertexCand_z_4[0],
DF_PrimVertexCand_z_5[0],DF_PrimVertexCand_z_6[0],DF_PrimVertexCand_z_7[0],DF_PrimVertexCand_z_8[0]], axis=0, ignore_index = True))).rename(columns = {0:'vertice_prima'})

# TIGHT MUON IDENTIFICATION
DF_MuonCand_vtxz = pd.concat([DF_MuonCand_vtxz_0,DF_MuonCand_vtxz_1,DF_MuonCand_vtxz_2,DF_MuonCand_vtxz_3,DF_MuonCand_vtxz_4,
DF_MuonCand_vtxz_5,DF_MuonCand_vtxz_6,DF_MuonCand_vtxz_7,DF_MuonCand_vtxz_8],axis=0, ignore_index = True).drop([2,3,4], axis=1).rename(columns={0:'muon1',1:'muon2'})

DF_MuonCand_istight = pd.concat([DF_MuonCand_istight_0,DF_MuonCand_istight_1,DF_MuonCand_istight_2,DF_MuonCand_istight_3,DF_MuonCand_istight_4,
DF_MuonCand_istight_5,DF_MuonCand_istight_6,DF_MuonCand_istight_7,DF_MuonCand_istight_8], axis=0, ignore_index = True).drop([2,3,4], axis=1).rename(columns={0:'istight1', 1:'istight2'})

# EXTRA TRACKS
DF_ExtraTracks = pd.concat([DF_nPfCand_0,DF_nPfCand_1,DF_nPfCand_2,DF_nPfCand_3,DF_nPfCand_4,DF_nPfCand_5,DF_nPfCand_6,DF_nPfCand_7,DF_nPfCand_8],axis = 0, ignore_index = True).rename(columns = {0:'extra_tracks'})

# ALMIR
DF_almir1 = pd.DataFrame(abs(DF_MuonCand_vtxz['muon1'] - DF_PrimVertexCand_z['vertice_prima'])).rename(columns={0:'modulo_1'})
DF_almir2 = pd.DataFrame(abs(DF_MuonCand_vtxz['muon2'] - DF_PrimVertexCand_z['vertice_prima'])).rename(columns={0:'modulo_2'})

# CONCATENANDO E REALIZANDO OS CORTES

total = np.concatenate([np.array(DF_muetaphi), np.array(DF_charge), np.array(DF_PrimVertexCand_z), np.array(DF_almir1), np.array(DF_almir2), np.array(DF_MuonCand_istight), np.array(DF_ExtraTracks)], axis=1)
total = pd.DataFrame(total, columns=['pt1', 'pt2','eta1','eta2','phi1','phi2','carga1', 'carga2', 'vertice_prima', 'almir1', 'almir2', 'istight1', 'istight2', 'extra_tracks'])
total = total.dropna() 

corte_pt = total.loc[total['pt1'] > 50].loc[total['pt2'] > 50]

corte_oppos_charged_muon = corte_pt.loc[corte_pt['carga1']*corte_pt['carga2'] < 0] 

corte_tight_muon_identification = corte_oppos_charged_muon.loc[corte_oppos_charged_muon['istight1']*corte_oppos_charged_muon['istight2']==1] 

DF_MuPt = corte_tight_muon_identification.loc[:,'pt1':'pt2']
DF_MuEta = corte_tight_muon_identification.loc[:, 'eta1':'eta2']
DF_Muphi = corte_tight_muon_identification.loc[:, 'phi1':'phi2']

TLV_0 = TLV(DF_MuPt['pt1'], DF_MuEta['eta1'], DF_Muphi['phi1'])
TLV_1 = TLV(DF_MuPt['pt2'], DF_MuEta['eta2'], DF_Muphi['phi2'])
DataFrame_Massa_inva = MassaInvariante(TLV_0,TLV_1)
DataFrame_DeltaEta = DeltaEta(TLV_0,TLV_1)
DF_PT = Pt(TLV_0,TLV_1)
DataFrame_Acopla = Acoplanaridade(TLV_0,TLV_1)
DataFrame_VerticePrima = pd.DataFrame(np.array(corte_tight_muon_identification['vertice_prima'])).rename(columns = {0:'vertice_prima'})
DataFrame_Almir = pd.DataFrame(np.array(corte_tight_muon_identification.loc[:,'almir1':'almir2'])).rename(columns = {0:'almir1',1:'almir2'})
DataFrame_ExtraTracks = pd.DataFrame(np.array(corte_tight_muon_identification['extra_tracks'])).rename(columns = {0:'extra_tracks'})

amostras = pd.concat([DF_PT, DataFrame_Massa_inva, DataFrame_Acopla, DataFrame_DeltaEta, DataFrame_VerticePrima, DataFrame_Almir,DataFrame_ExtraTracks], axis = 1)

amostras.to_csv('amostra_drellyan.csv')

