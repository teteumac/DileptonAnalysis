from __future__ import absolute_import

import os
import sys
import struct
import uuid

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
from pandas import DataFrame

dataB = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataB.root')['ggll_miniaod/ntp1']
dataC_0_limitRum = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataC_0_limitRun.root')['ggll_miniaod/ntp1']
dataC_1_limitRum = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataC_1_limitRun.root')['ggll_miniaod/ntp1']
dataC_2_limitRum = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataC_2_limitRun.root')['ggll_miniaod/ntp1']
dataC_3_limitRum = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataC_3_limitRun.root')['ggll_miniaod/ntp1']

dataE_0 = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataE_0.root')['ggll_miniaod/ntp1']
dataE_1 = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataE_1.root')['ggll_miniaod/ntp1']
dataE_2 = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataE_2.root')['ggll_miniaod/ntp1']
dataE_3 = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataE_3.root')['ggll_miniaod/ntp1']
dataE_4 = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataE_4.root')['ggll_miniaod/ntp1']

dataE_5 = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataE_5.root')['ggll_miniaod/ntp1']
dataE_6 = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataE_6.root')['ggll_miniaod/ntp1']
dataF_0_limitRum = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataF_0_limitRun.root')['ggll_miniaod/ntp1']
dataF_1_limitRum = uproot.open('/mnt/hadoop/cms/store/user/malvesga/data_limitRun/output_dataF_1_limitRun.root')['ggll_miniaod/ntp1']

############################### output_dataB ###############################

DF_MuPt_dataB = DataFrame(dataB.array('MuonCand_pt'))
DF_MuEta_dataB = DataFrame(dataB.array('MuonCand_eta'))
DF_MuPhi_dataB = DataFrame(dataB.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataB = DataFrame(dataB.array('PrimVertexCand_z'))[0]
DF_charge_dataB = DataFrame(dataB.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataB = DataFrame(dataB.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataB = DataFrame(dataB.array('MuonCand_istight'))
DF_nPfCand_dataB = DataFrame(dataB.array('nPfCand'))[0]


############################### output_dataC_0_limitRum ###############################

DF_MuPt_C_0_limitRum = DataFrame(dataC_0_limitRum.array('MuonCand_pt'))
DF_MuEta_C_0_limitRum = DataFrame(dataC_0_limitRum.array('MuonCand_eta'))
DF_MuPhi_C_0_limitRum = DataFrame(dataC_0_limitRum.array('MuonCand_phi'))
DF_PrimVertexCand_z_C_0_limitRum = (pd.DataFrame(dataC_0_limitRum.array('PrimVertexCand_z')))[0]
DF_charge_inel_C_0_limitRum      = pd.DataFrame(dataC_0_limitRum.array('MuonCand_charge'))
DF_MuonCand_vtxz_C_0_limitRum    = pd.DataFrame(dataC_0_limitRum.array('MuonCand_vtxz'))
DF_MuonCand_istight_C_0_limitRum = pd.DataFrame(dataC_0_limitRum.array('MuonCand_istight'))
DF_nPfCand_dataC_0_limitRum = DataFrame(dataC_0_limitRum.array('nPfCand'))[0]


############################### output_dataC_1_limitRum ###############################

DF_PrimVertexCand_z_C_1_limitRum = (pd.DataFrame(dataC_1_limitRum.array('PrimVertexCand_z')))[0]
DF_charge_inel_C_1_limitRum      = pd.DataFrame(dataC_1_limitRum.array('MuonCand_charge'))
DF_MuonCand_vtxz_C_1_limitRum    = pd.DataFrame(dataC_1_limitRum.array('MuonCand_vtxz'))
DF_MuonCand_istight_C_1_limitRum = pd.DataFrame(dataC_1_limitRum.array('MuonCand_istight'))
DF_MuPt_C_1_limitRum = DataFrame(dataC_1_limitRum.array('MuonCand_pt'))
DF_MuEta_C_1_limitRum = DataFrame(dataC_1_limitRum.array('MuonCand_eta'))
DF_MuPhi_C_1_limitRum = DataFrame(dataC_1_limitRum.array('MuonCand_phi'))
DF_nPfCand_dataC_1_limitRum = DataFrame(dataC_1_limitRum.array('nPfCand'))[0]


############################### output_dataC_2_limitRum ###############################

DF_PrimVertexCand_z_C_2_limitRum = (pd.DataFrame(dataC_2_limitRum.array('PrimVertexCand_z')))[0]
DF_charge_inel_C_2_limitRum      = pd.DataFrame(dataC_2_limitRum.array('MuonCand_charge'))
DF_MuonCand_vtxz_C_2_limitRum    = pd.DataFrame(dataC_2_limitRum.array('MuonCand_vtxz'))
DF_MuonCand_istight_C_2_limitRum = pd.DataFrame(dataC_2_limitRum.array('MuonCand_istight'))
DF_MuPt_C_2_limitRum = DataFrame(dataC_2_limitRum.array('MuonCand_pt'))
DF_MuEta_C_2_limitRum = DataFrame(dataC_2_limitRum.array('MuonCand_eta'))
DF_MuPhi_C_2_limitRum = DataFrame(dataC_2_limitRum.array('MuonCand_phi'))
DF_nPfCand_dataC_2_limitRum = DataFrame(dataC_2_limitRum.array('nPfCand'))[0]

############################### output_dataC_3_limitRum ###############################

DF_PrimVertexCand_z_C_3_limitRum = (pd.DataFrame(dataC_3_limitRum.array('PrimVertexCand_z')))[0]
DF_charge_inel_C_3_limitRum      = pd.DataFrame(dataC_3_limitRum.array('MuonCand_charge'))
DF_MuonCand_vtxz_C_3_limitRum    = pd.DataFrame(dataC_3_limitRum.array('MuonCand_vtxz'))
DF_MuonCand_istight_C_3_limitRum = pd.DataFrame(dataC_3_limitRum.array('MuonCand_istight'))
DF_MuPt_C_3_limitRum = DataFrame(dataC_3_limitRum.array('MuonCand_pt'))
DF_MuEta_C_3_limitRum = DataFrame(dataC_3_limitRum.array('MuonCand_eta'))
DF_MuPhi_C_3_limitRum = DataFrame(dataC_3_limitRum.array('MuonCand_phi'))
DF_nPfCand_dataC_3_limitRum = DataFrame(dataC_3_limitRum.array('nPfCand'))[0]


############################### output_dataE0 ###############################

DF_MuPt_dataE0 = DataFrame(dataE_0.array('MuonCand_pt'))
DF_MuEta_dataE0 = DataFrame(dataE_0.array('MuonCand_eta'))
DF_MuPhi_dataE0 = DataFrame(dataE_0.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataE0 = DataFrame(dataE_0.array('PrimVertexCand_z'))[0]
DF_charge_dataE0 = DataFrame(dataE_0.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataE0 = DataFrame(dataE_0.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataE0 = DataFrame(dataE_0.array('MuonCand_istight'))
DF_nPfCand_dataE_0 = DataFrame(dataE_0.array('nPfCand'))[0]


############################### output_dataE1 ###############################

DF_MuPt_dataE1 = DataFrame(dataE_1.array('MuonCand_pt'))
DF_MuEta_dataE1 = DataFrame(dataE_1.array('MuonCand_eta'))
DF_MuPhi_dataE1 = DataFrame(dataE_1.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataE1 = DataFrame(dataE_1.array('PrimVertexCand_z'))[0]
DF_charge_dataE1 = DataFrame(dataE_1.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataE1 = DataFrame(dataE_1.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataE1 = DataFrame(dataE_1.array('MuonCand_istight'))
DF_nPfCand_dataE_1 = DataFrame(dataE_1.array('nPfCand'))[0]


############################### output_dataE2 ###############################

DF_MuPt_dataE2 = DataFrame(dataE_2.array('MuonCand_pt'))
DF_MuEta_dataE2 = DataFrame(dataE_2.array('MuonCand_eta'))
DF_MuPhi_dataE2 = DataFrame(dataE_2.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataE2 = DataFrame(dataE_2.array('PrimVertexCand_z'))[0]
DF_charge_dataE2 = DataFrame(dataE_2.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataE2 = DataFrame(dataE_2.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataE2 = DataFrame(dataE_2.array('MuonCand_istight'))
DF_nPfCand_dataE_2 = DataFrame(dataE_2.array('nPfCand'))[0]

############################### output_dataE3 ###############################

DF_MuPt_dataE3 = DataFrame(dataE_3.array('MuonCand_pt'))
DF_MuEta_dataE3 = DataFrame(dataE_3.array('MuonCand_eta'))
DF_MuPhi_dataE3 = DataFrame(dataE_3.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataE3 = DataFrame(dataE_3.array('PrimVertexCand_z'))[0]
DF_charge_dataE3 = DataFrame(dataE_3.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataE3 = DataFrame(dataE_3.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataE3 = DataFrame(dataE_3.array('MuonCand_istight'))
DF_nPfCand_dataE_3 = DataFrame(dataE_3.array('nPfCand'))[0]


############################### output_dataE4 ###############################

DF_MuPt_dataE4 = DataFrame(dataE_4.array('MuonCand_pt'))
DF_MuEta_dataE4 = DataFrame(dataE_4.array('MuonCand_eta'))
DF_MuPhi_dataE4 = DataFrame(dataE_4.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataE4 = DataFrame(dataE_4.array('PrimVertexCand_z'))[0]
DF_charge_dataE4 = DataFrame(dataE_4.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataE4 = DataFrame(dataE_4.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataE4 = DataFrame(dataE_4.array('MuonCand_istight'))
DF_nPfCand_dataE_4 = DataFrame(dataE_4.array('nPfCand'))[0]


############################### output_dataE5 ###############################

DF_MuPt_dataE5 = DataFrame(dataE_5.array('MuonCand_pt'))
DF_MuEta_dataE5 = DataFrame(dataE_5.array('MuonCand_eta'))
DF_MuPhi_dataE5 = DataFrame(dataE_5.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataE5 = DataFrame(dataE_5.array('PrimVertexCand_z'))[0]
DF_charge_dataE5 = DataFrame(dataE_5.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataE5 = DataFrame(dataE_5.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataE5 = DataFrame(dataE_5.array('MuonCand_istight'))
DF_nPfCand_dataE_5 = DataFrame(dataE_5.array('nPfCand'))[0]

############################### output_dataE6 ###############################

DF_MuPt_dataE6 = DataFrame(dataE_6.array('MuonCand_pt'))
DF_MuEta_dataE6 = DataFrame(dataE_6.array('MuonCand_eta'))
DF_MuPhi_dataE6 = DataFrame(dataE_6.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataE6 = DataFrame(dataE_6.array('PrimVertexCand_z'))[0]
DF_charge_dataE6 = DataFrame(dataE_6.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataE6 = DataFrame(dataE_6.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataE6 = DataFrame(dataE_6.array('MuonCand_istight'))
DF_nPfCand_dataE_6 = DataFrame(dataE_6.array('nPfCand'))[0]

############################### output_dataF_0_limitRum ###############################

DF_MuPt_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('MuonCand_pt'))
DF_MuEta_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('MuonCand_eta'))
DF_MuPhi_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('PrimVertexCand_z'))[0]
DF_charge_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('MuonCand_istight'))
DF_nPfCand_dataF_0_limitRum = DataFrame(dataF_0_limitRum.array('nPfCand'))[0]

############################### output_dataF_1_limitRum ###############################

DF_MuPt_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('MuonCand_pt'))
DF_MuEta_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('MuonCand_eta'))
DF_MuPhi_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('MuonCand_phi'))
DF_PrimVertexCand_z_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('PrimVertexCand_z'))[0]
DF_charge_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('MuonCand_charge'))
DF_MuonCand_vtxz_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('MuonCand_vtxz'))
DF_MuonCand_istight_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('MuonCand_istight'))
DF_nPfCand_dataF_1_limitRum = DataFrame(dataF_1_limitRum.array('nPfCand'))[0]

################################################################################################################################################

print('INICÍO DA CONCATENAÇÃO \n')

print('PT ETA PHI \n')

DF_MuPt  = pd.concat([DF_MuPt_dataB, DF_MuPt_C_0_limitRum,DF_MuPt_C_1_limitRum,DF_MuPt_C_2_limitRum,DF_MuPt_C_3_limitRum,
DF_MuPt_dataE0,DF_MuPt_dataE1,DF_MuPt_dataE2,DF_MuPt_dataE3,DF_MuPt_dataE4,
DF_MuPt_dataE5,DF_MuPt_dataE6,DF_MuPt_dataF_0_limitRum,DF_MuPt_dataF_1_limitRum,
], axis = 0).drop([2,3,4],axis=1)

DF_MuEta = pd.concat([DF_MuEta_dataB,DF_MuEta_C_0_limitRum,DF_MuEta_C_1_limitRum,DF_MuEta_C_2_limitRum,DF_MuEta_C_3_limitRum,
DF_MuEta_dataE0,DF_MuEta_dataE1,DF_MuEta_dataE2,DF_MuEta_dataE3,DF_MuEta_dataE4,
DF_MuEta_dataE5,DF_MuEta_dataE6,DF_MuEta_dataF_0_limitRum,DF_MuEta_dataF_1_limitRum
], axis = 0).drop([2,3,4],axis=1)

DF_MuPhi = pd.concat([DF_MuPhi_dataB,DF_MuPhi_C_0_limitRum,DF_MuPhi_C_1_limitRum,DF_MuPhi_C_2_limitRum,DF_MuPhi_C_3_limitRum,
DF_MuPhi_dataE0,DF_MuPhi_dataE1,DF_MuPhi_dataE2,DF_MuPhi_dataE3,DF_MuPhi_dataE4,
DF_MuPhi_dataE5,DF_MuPhi_dataE6,DF_MuPhi_dataF_0_limitRum,DF_MuPhi_dataF_1_limitRum
], axis = 0).drop([2,3,4],axis=1)

DF_ptetaphi = pd.concat([DF_MuPt, DF_MuEta, DF_MuPhi], axis = 1)
DF_ptetaphi.to_csv('DF_ptetaphi_E1.csv')

########################################################################################################

print('VERTICE PRIMARIO \n')

# Vértice Primário 

DataFrame_VerticePrimario_limitRum = pd.concat([DF_PrimVertexCand_z_dataB, DF_PrimVertexCand_z_C_0_limitRum,DF_PrimVertexCand_z_C_1_limitRum, DF_PrimVertexCand_z_C_2_limitRum, DF_PrimVertexCand_z_C_3_limitRum,
DF_PrimVertexCand_z_dataE0,DF_PrimVertexCand_z_dataE1,DF_PrimVertexCand_z_dataE2,DF_PrimVertexCand_z_dataE3,DF_PrimVertexCand_z_dataE4,
DF_PrimVertexCand_z_dataE5,DF_PrimVertexCand_z_dataE6,DF_PrimVertexCand_z_dataF_0_limitRum,DF_PrimVertexCand_z_dataF_1_limitRum
], axis=0)
DataFrame_VerticePrimario_limitRum.to_csv('Dados_VertPrimaE3.csv')
 
########################################################################################################

print('CARGA DO MUON \n')

# Carga do par do Muon

DataFrame_charge = pd.concat([DF_charge_dataB,DF_charge_inel_C_3_limitRum, DF_charge_inel_C_0_limitRum,DF_charge_inel_C_1_limitRum, DF_charge_inel_C_2_limitRum,
DF_charge_dataE0,DF_charge_dataE1,DF_charge_dataE2,DF_charge_dataE3,DF_charge_dataE4,
DF_charge_dataE5,DF_charge_dataE6,DF_charge_dataF_0_limitRum,DF_charge_dataF_1_limitRum
], axis=0).drop([2,3,4], axis=1)
DataFrame_charge.to_csv('Dados_chargeE3.csv')

########################################################################################################

print('MÓDULO \n')

# Módulo

DataFrame_istight = pd.concat([DF_charge_dataB, DF_MuonCand_istight_C_2_limitRum, DF_MuonCand_istight_C_1_limitRum, DF_MuonCand_istight_C_0_limitRum, DF_MuonCand_istight_C_3_limitRum,
DF_MuonCand_istight_dataE0,DF_MuonCand_istight_dataE1,DF_MuonCand_istight_dataE2,DF_MuonCand_istight_dataE3,DF_MuonCand_istight_dataE4,
DF_MuonCand_istight_dataE5,DF_MuonCand_istight_dataE6,DF_MuonCand_istight_dataF_0_limitRum,DF_MuonCand_istight_dataF_1_limitRum
],axis=0).drop([2,3,4], axis=1)
DataFrame_istight.to_csv('Dados_istightE3.csv')

print('TIGHT MUON \n')

# TIGHT MUON IDENTIFICATION
DataFrame_vtxz = pd.concat([DF_MuonCand_vtxz_dataB,DF_MuonCand_vtxz_C_3_limitRum, DF_MuonCand_vtxz_C_0_limitRum, DF_MuonCand_vtxz_C_1_limitRum, DF_MuonCand_vtxz_C_2_limitRum,
DF_MuonCand_vtxz_dataE0,DF_MuonCand_vtxz_dataE1,DF_MuonCand_vtxz_dataE2,DF_MuonCand_vtxz_dataE3,DF_MuonCand_vtxz_dataE4,
DF_MuonCand_vtxz_dataE5,DF_MuonCand_vtxz_dataE6,DF_MuonCand_vtxz_dataF_0_limitRum,DF_MuonCand_vtxz_dataF_1_limitRum
], axis=0).drop([2,3,4], axis=1)

########################################################################################################

# modulo do muon - vertice primario

DF_Modulo1 = pd.DataFrame(abs(np.array(DataFrame_vtxz[0]) - np.array(DataFrame_VerticePrimario_limitRum)))
DF_Modulo2 = pd.DataFrame(abs(np.array(DataFrame_vtxz[1]) - np.array(DataFrame_VerticePrimario_limitRum)))

DataFrame_concat = pd.concat([DF_Modulo1,DF_Modulo2], axis=1)
pd.DataFrame(DataFrame_concat).to_csv('Dados_moduloE3.csv')


########################################################################################################
