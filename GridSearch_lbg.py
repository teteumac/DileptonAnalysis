from __future__ import print_function, division

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import time
import math
from pandas import set_option
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import PrecisionRecallDisplay,precision_score,plot_roc_curve,recall_score,accuracy_score,log_loss,roc_auc_score,classification_report,f1_score,confusion_matrix,roc_curve,precision_recall_curve,plot_precision_recall_curve,average_precision_score
from sklearn.model_selection import RandomizedSearchCV, GridSearchCV
from sklearn.metrics import fbeta_score
from sklearn.metrics import make_scorer
from sklearn.model_selection import KFold
from sklearn.preprocessing import StandardScaler
from lightgbm import LGBMClassifier
import lightgbm as lgb
import sys
from matplotlib.colors import ListedColormap
import seaborn as sns
import mplhep as hep

##############################################################################################################################


def plotROC(predictions,class_true,title):
    # choose score cuts:
    cuts = np.linspace(0,1,500); # Dividi o intervalo de 0 té 1 em 500 partes iguais 
    n_truePos = np.zeros(len(cuts)); # Cria uma matriz de zeros com o mesmo comprimento que o cuts, ou seja, 500
    n_falsePos = np.zeros(len(cuts));
    n_TotPos = len(np.where(class_true==1)[0]) # A partir da condição class_predict==1, retorna os valores em um array com essas condições. Com a função len(), retorna o comprimento desse array
    for i,cut in enumerate(cuts): # Enumerates organiza o array para melhor vizualizar
       y_pred = np.array([i>cut for i in predictions ])
       n_truePos[i] = len(np.where(predictions[class_true==1] > cut)[0]);
       n_falsePos[i] = len(np.where(predictions[class_true==0] > cut)[0]);
       if i%50 ==0:
         ascore = accuracy_score(class_true,y_pred)
         pscore = precision_score(class_true,y_pred)
         rscore = recall_score(class_true,y_pred)
         print("corte em {:2.1f} --> eficiência  {:2.1f} % e  pureza {:2.1f} %".format(cut,n_truePos[i]/n_TotPos *100,n_truePos[i]/(n_truePos[i]+n_falsePos[i])*100))
         print("accuracy_score = {:2.4f}     precision_score = {:2.4f}     recall_score = {:2.4f}\n".format(ascore,pscore,rscore))
    # plot efficiency vs. purity (ROC curve)
    plt.figure();
    custom_cmap3 = ListedColormap(['orange','yellow','lightgreen',"lightblue","violet"])
    plt.scatter((n_truePos/n_TotPos),n_truePos/(n_truePos + n_falsePos),c=cuts,cmap=custom_cmap3,label="ROC");
    # make the plot readable
    plt.title(title)
    plt.xlabel('Efficiency');
    plt.ylabel('Purity');
    plt.tight_layout()
    plt.colorbar()
    plt.show()
    plt.close()    

def ConfusionMatrix(class_true,class_predict,cmap,title):
    conf_mat = confusion_matrix(y_true=class_true, y_pred=class_predict)
    print('Confusion matrix:\n', conf_mat)
    conf_mat = DataFrame(conf_mat)
    conf_mat = conf_mat.rename(columns={0:'Drell-Yan', 1:'Signal'})
    conf_mat = conf_mat.T
    conf_mat = conf_mat.rename(columns={0:'Drell-Yan', 1:'Signal'})
    conf_mat = conf_mat.T
    sns.heatmap(conf_mat, annot=True, fmt="d",cmap = cmap)
    plt.title(title)
    plt.xlabel('Predicted')
    plt.ylabel('Expected')
    plt.tight_layout()
    plt.show()
    plt.close()

##############################################################################################################################

n_events_h_elastic = 200000
n_events_h_inel_el = 200000
n_events_h_dy = 48675378
total_lumi = 37.498268
limit_lumi = 18.516268
rap_gap_surv_elastic = 0.89
rap_gap_surv_inel_el = 0.76
rap_gap_surv_inelastic = 0.13
number_of_samples = 1200

scale_factor_elastic_x130 = limit_lumi*rap_gap_surv_elastic*0.017254036*1000*2 / n_events_h_elastic
scale_factor_inel_el_x130 = limit_lumi*rap_gap_surv_inel_el*0.025643500*1000*2 / n_events_h_inel_el 
scale_factor_dy = limit_lumi*5334000*2 / n_events_h_dy
scale_factor_dy_resample = limit_lumi*5334000 / ( n_events_h_dy*number_of_samples )


##############################################################################################################################

from pandas import DataFrame,concat,read_csv
DataSet_signal_exclusivo = DataFrame(np.delete((np.array(read_csv('amostra_exclusivo.csv'))),0,1))
#DataSet_signal_exclusivo['ExtraTracks'] = pd.DataFrame(np.delete((np.array(pd.read_csv('ExtraTracks_Elas.csv'))),0,1))
DataSet_signal_semiexclusivo = DataFrame(np.delete((np.array(read_csv('amostra_semiesclusivo.csv'))),0,1))
#DataSet_signal_semiexclusivo['ExtraTracks'] = pd.DataFrame(np.delete((np.array(pd.read_csv('ExtraTracks_Inel.csv'))),0,1))
DataSet_signal_exclusivo['target'] = 1 
DataSet_signal_semiexclusivo['target'] = 2
DataSet_signal = concat([DataSet_signal_exclusivo,DataSet_signal_semiexclusivo], axis=0)

#--------------------------- Drell-yan --------------------------- #

DataSet_backgraund = DataFrame(np.delete((np.array(read_csv('amostra_drellyan.csv'))),0,1))
#filename = ['ExtraTracks_DY0.csv','ExtraTracks_DY1.csv', 'ExtraTracks_DY2.csv', 'ExtraTracks_DY3.csv', 'ExtraTracks_DY4.csv', 'ExtraTracks_DY5.csv', 'ExtraTracks_DY6.csv', 'ExtraTracks_DY7.csv', 'ExtraTracks_DY8.csv']
#DataSet_backgraund['ExtraTracks'] = pd.DataFrame(np.delete((np.array(pd.concat( [ pd.read_csv ( f ) for f in filename ] ))),0,1)) 
DataSet_backgraund['target'] = 0 # atribuindo o valor de 0 para classificar o BACKGROUND das amostras
DataSet2 = concat([DataSet_signal,DataSet_backgraund], ignore_index = True)

## --------------------------------------------------------------------------------------------- ##

dataset = DataSet2.rename(columns={0:'Pt', 1:'MassaInvariante', 2:'Acoplanaridade', 3: 'DeltaEta', 4:'VerticePrimario', 5:'almir1', 6:'almir2', 7:'weight'}).drop(['almir2'], axis = 1)
print(dataset)

DataSet_Train, dataset_test = train_test_split(dataset, test_size = 0.5, random_state = 41)
#DataSet_Train_DY = dataset_train[ dataset_train.target == 0 ].sample( frac = 0.9 )
#DataSet_Train_Exclu = dataset_train[ dataset_train.target == 1 ].sample( frac = scale_factor_elastic_x130 )
#DataSet_Train_SemiExc = dataset_train[ dataset_train.target == 2 ].sample( frac = scale_factor_inel_el_x130 )

#DataSet_Train = concat( [ DataSet_Train_Exclu, DataSet_Train_SemiExc, DataSet_Train_DY ], axis = 0 )

DataSet_Train.to_csv('amostras_treino.csv')
dataset_test.to_csv('amostras_teste.csv')

y_train_ = DataSet_Train['target'].replace(2,1) # Muda os valores de 2 para 1
y_test_ = dataset_test['target'].replace(2,1)

train_data = lgb.Dataset(DataSet_Train.drop( ['target' , 'weight'] , axis = 1 ), label = y_train_ )
test_data = lgb.Dataset(dataset_test.drop( ['target' , 'weight'] , axis = 1 ) , label = y_test_ )

n_iter = 18
cv = 6
scoring = [ 'roc_auc','f1','precision','recall' ]
scoring = None

param_grid = {
    'learning_rate': list(np.arange(0.0001,1,0.001)), 
    'n_estimators': list(range(100, 1000, 50)),
    'num_leaves': list(range(1, 100, 2)),
    'max_depth': list(range(0, 150, 3)),
    'min_child_samples': list(range(0, 100, 2)),
    'subsample': list(np.arange(0.01,1,0.01)), 
    'colsample_bytree':list(np.arange(0.1,1,0.1))
              }  

##############################################################################################################################

mdl = LGBMClassifier( boosting_type = 'gbdt' , objective = 'binary' )

#search object

search = RandomizedSearchCV( estimator = mdl, param_distributions = param_grid, n_iter = n_iter, refit='precision_score' , scoring = scoring ,cv = cv, verbose = 1 )

start_time = time.time()

search_result = search.fit(DataSet_Train.drop(['target', 'weight'], axis = 1), y_train_)

# Results
print("Best: %f using %s" % ( search_result.best_score_, search_result.best_params_ ) )
print('\n')

predict_proba_LGBM = search_result.predict_proba( dataset_test.drop( ['target' , 'weight'] , axis = 1 ) )[:,1] 

fpr_lgb, tpr_lgb, thresholds_lgb = roc_curve( y_test_, predict_proba_LGBM ) # fpr -> false positive rate | tpr -> true positive rate
prec_lgb, rec_lgb, threshs_lgb = precision_recall_curve( y_test_, predict_proba_LGBM ) # prec -> precision | rec -> recall 
f1 = 2 * ( prec_lgb * rec_lgb ) / ( prec_lgb + rec_lgb )
threshs_lgb  = np.concatenate( [ threshs_lgb , [1] ] , axis = 0 )

bidx = np.argmax(prec_lgb*rec_lgb)
best_cut = threshs_lgb[bidx]
print('\n',' Best Cut ------>> ', best_cut,'\n')
y_pred_cut = predict_proba_LGBM >= best_cut

ConfusionMatrix(y_test_,y_pred_cut,'RdBu','Confusion Matrix')

plot_precision_recall_curve( search, dataset_test.drop(['target','weight'],axis=1),y_test_, color = 'red')
plt.style.use(hep.style.CMS)
hep.cms.cmslabel()
plt.show()

plot_roc_curve( search, dataset_test.drop(['target','weight'],axis=1),y_test_, color = 'red')
plt.title("ROC Curve")
plt.plot([0, 1], [0, 1], color='black', lw=2, linestyle='--')
plt.style.use(hep.style.CMS)
hep.cms.cmslabel()
plt.show()

plt.plot( threshs_lgb , prec_lgb*rec_lgb ,  color = 'purple' )
plt.plot( [ best_cut,best_cut ] , [0,(prec_lgb * rec_lgb).max()*2] ,"-.r",label='Best Cut : {:2.5f}'.format(best_cut) )
plt.plot( [-0.1,1.1] , [ (prec_lgb*rec_lgb).max(),(prec_lgb*rec_lgb).max()], "--g",label='precision*recall : {:2.5f}'.format((prec_lgb*rec_lgb).max()) )
plt.ylabel( 'PRECISION * RECALL' )
plt.xlabel(    'THRESHOLDS'    )
plt.ylim( -0.002 , 0.9 )
plt.xlim( -0.01 , 1.05)
plt.legend(loc="best")
plt.style.use(hep.style.CMS)
hep.cms.cmslabel()
plt.show()

hbgt_lgb =  plt.hist(predict_proba_LGBM[y_test_==0],bins=np.linspace(0,1,50), histtype='step',label='Background', color = 'blue')
hsigt_lgb = plt.hist(predict_proba_LGBM[y_test_==1],bins=np.linspace(0,1,50), histtype='step',label='Signal', color = 'green')
uppery_lgb=np.max(hsigt_lgb[0])
plt.plot([best_cut,best_cut],[0,uppery_lgb],"-.r",label='Best cut : {:2.2f}'.format(best_cut))
plt.xlabel("Probability")
plt.ylabel("Events")
plt.title("Monte-Carlo Test")
plt.legend(loc="upper left")
plt.text(0.6,60000, "Purity: {:2.2f}%".format(100*precision_score(y_test_,y_pred_cut)),fontsize = 18)
plt.text(0.6,55000, "Efficiency: {:2.2f}%".format(100*recall_score(y_test_,y_pred_cut)),fontsize = 18)
plt.text(0.6,50000, "Accuracy: {:2.2f}%".format(100*accuracy_score(y_test_,y_pred_cut)), fontsize = 18)
plt.text(0.6,45000, "ROC AUC: {:2.2f}%".format(100*roc_auc_score(y_test_,y_pred_cut)), fontsize = 18)
plt.text(0.6,40000, "F1_Score: {:2.2f}%".format(100*f1_score(y_test_,y_pred_cut)), fontsize = 18)
plt.text(best_cut+0.06,20000, 'SIGNAL REGION', color = 'red')
plt.style.use(hep.style.ROOT)
plt.ticklabel_format(axis="y", style="sci", scilimits=(0,3), useMathText = True)
plt.tight_layout()
plt.show()
plt.close()


DataSet_DoubleMuon = DataFrame(np.delete((np.array(read_csv('amostra_doublemuon.csv'))),0,1)).rename(columns={0:'Pt', 1:'MassaInvariante', 2:'Acoplanaridade', 3: 'DeltaEta', 4:'VerticePrimario', 5:'dz1'}).drop([6,7],axis=1)

MonteCarlo_DrellYan = DataFrame( np.array ( dataset_test[ dataset_test.target == 0 ] ) )
MonteCarlo_Exclusive = DataFrame( np.array (dataset_test[ dataset_test.target == 1 ] ) )
MonteCarlo_SemiExclusive = DataFrame( np.array (dataset_test[ dataset_test.target == 2 ] ) )

predict_proba_LGBM_background = search_result.predict_proba( MonteCarlo_DrellYan.drop( [ 6 , 7 ] , axis = 1 ) )[:,1]
predict_proba_LGBM_exclusivo = search_result.predict_proba( MonteCarlo_Exclusive.drop( [ 6 , 7 ] , axis = 1 ) )[:,1]
predict_proba_LGBM_semiexclusivo = search_result.predict_proba( MonteCarlo_SemiExclusive.drop( [ 6 , 7 ] , axis = 1 ) )[:,1]
predict_proba_LGBM_Data = search_result.predict_proba( DataSet_DoubleMuon )[:,1]

class_true = dataset_test['target'].replace(2,1)

prec, rec, threshs = precision_recall_curve( y_test_, predict_proba_LGBM , sample_weight = dataset_test.weight*2 ) # prec -> precision | rec -> recall 
fpr, tpr, thresholds = roc_curve( y_test_, predict_proba_LGBM , sample_weight = dataset_test.weight*2 )
f1 = 2 * ( prec * rec ) / ( prec + rec )
threshs  = np.concatenate( [ threshs , [1] ] , axis = 0 )

argmax = np.argmax( prec * rec )
best_cut = threshs[argmax]
print('\n',' Best Cut ------>> ', best_cut,'\n')
y_pred_cut = predict_proba_LGBM >= best_cut
y_pred_cut = np.array(y_pred_cut)

plot_precision_recall_curve( search, dataset_test.drop(['target','weight'],axis=1),y_test_, color = 'red',sample_weight = dataset_test.weight*2)
plt.style.use(hep.style.CMS)
plt.plot([0, 1], [0,0], color='black', lw=2, linestyle='--')
plt.legend(loc="best")
hep.cms.cmslabel()
plt.show()

plot_roc_curve( search, dataset_test.drop(['target','weight'],axis=1),y_test_, color = 'red',sample_weight = dataset_test.weight*2)
plt.title("ROC Curve")
plt.plot([0, 1], [0, 1], color='black', lw=2, linestyle='--')
plt.style.use(hep.style.CMS)
hep.cms.cmslabel()
plt.show()

plt.plot( rec , prec*rec ,  color = 'gold' )
plt.ylabel( 'Precision*Recall' )
plt.xlabel(      'Recall'      )
plt.tight_layout()
plt.show()

plt.plot( threshs , prec*rec ,  color = 'blue' )
plt.plot( [ best_cut,best_cut ] , [-0.4,(prec * rec).max()*2] ,"-.r",label='Best Cut : {:2.5f}'.format(best_cut) )
plt.plot( [-0.1,1.1] , [ (prec*rec).max(),(prec*rec).max()], "-g",label='precision*recall : {:2.5f}'.format((prec*rec).max()) )
plt.ylabel( 'PRECISION * RECALL' )
plt.xlabel(    'THRESHOLDS'    )
plt.ylim( -0.002 , 0.09 )
plt.xlim( -0.01 , 1.05)
plt.legend(loc="center left")
plt.style.use(hep.style.CMS)
hep.cms.cmslabel()
plt.show()

plt.plot( threshs , f1 ,  color = 'green' )
plt.plot( [ best_cut,best_cut ] , [-0.4,(f1).max()*2] ,"-.r",label='Best Cut : {:2.5f}'.format(best_cut) )
plt.plot( [-0.1,1.1] , [ (f1).max(),(f1).max()], "-b",label='F1_SCORE : {:2.5f}'.format((f1).max()) )
plt.ylabel(  'F1_SCORE'  )
plt.xlabel( 'THRESHOLDS' )
plt.ylim( -0.002 , 0.3 )
plt.xlim( -0.01 , 1.05)
plt.legend(loc="center left")
plt.style.use(hep.style.CMS)
hep.cms.cmslabel()
plt.show()

confu_matrix = confusion_matrix( y_test_ , y_pred_cut , sample_weight = dataset_test.weight*2 )
confu_matrix_DY = ((DataFrame(confu_matrix[0,:]).T).rename(columns = {0: 'Drell-Yan', 1: 'Signal'}).T).rename(columns = {0: 'Drell-Yan'}).T
confu_matrix_sig = ((DataFrame(confu_matrix[1,:]).T).rename(columns = {0: 'Drell-Yan', 1: 'Signal'}).T).rename(columns = {0:'Signal'}).T
cunfusion_matrix = concat([confu_matrix_DY,confu_matrix_sig],axis=0)
sns.heatmap(cunfusion_matrix.astype('int'), annot=True, fmt="d", cmap = 'summer')
plt.title('Confusion Matrix - cut: {:2.5f}'.format(best_cut) )
plt.xlabel('Predicted')
plt.ylabel('Expected')
plt.tight_layout()
plt.show()
plt.close() 

hist_Exclu = plt.hist(predict_proba_LGBM_exclusivo, bins=np.linspace(0,1,50), histtype='step', color = 'green', label='Exclusive', weights = MonteCarlo_Exclusive[ 6 ]*2)
hist_SemiExclu = plt.hist(predict_proba_LGBM_semiexclusivo, bins=np.linspace(0,1,50), histtype='step',color = 'gold',label='Semi-Exclusive',  weights = MonteCarlo_SemiExclusive[ 6 ]*2 )
hist_DY = plt.hist(predict_proba_LGBM_background, bins=np.linspace(0,1,50), histtype='step',label='Drell-Yan', color = 'blue' )
plt.plot([best_cut,best_cut],[0,10e10],"-.r",label='Best Cut : {:2.5f}'.format(best_cut))
plt.yscale('log')
plt.ylim(10e-5,10e8)
plt.xlabel("Probability")
plt.ylabel("Events")
plt.legend(loc="upper left")
plt.text(best_cut+0.02,10e3, 'SIGNAL REGION', color = 'red', rotation = 90)
plt.text(0.5,60e6, "Purity: {:2.2f}%".format(100*precision_score(y_test_,y_pred_cut, sample_weight = dataset_test.weight*2)),fontsize = 18)
plt.text(0.5,20e6, "Efficiency: {:2.2f}%".format(100*recall_score(y_test_,y_pred_cut, sample_weight = dataset_test.weight*2)),fontsize = 18)
plt.text(0.5,70e5, "F1_Score: {:2.2f}%".format(100*f1_score(y_test_,y_pred_cut, sample_weight = dataset_test.weight*2)),fontsize = 18)
plt.text(0.5,20e5, "ROC AUC: {:2.2f}%".format(100*roc_auc_score(y_test_,y_pred_cut, sample_weight = dataset_test.weight*2)),fontsize = 18)
plt.text(0.5,70e4, "Acuracy: {:2.2f}%".format(100*accuracy_score(y_test_,y_pred_cut, sample_weight = dataset_test.weight*2)),fontsize = 18)
hep.cms.cmslabel()
plt.style.use(hep.style.CMS)
plt.show()

class_pred_DY = predict_proba_LGBM_background >= best_cut
class_pred_Exclusive = predict_proba_LGBM_exclusivo >= best_cut
class_pred_SemiExclusive = predict_proba_LGBM_semiexclusivo >= best_cut
class_pred_Data = predict_proba_LGBM_Data >= best_cut

MonteCarlo_Exclusive['target'] = DataFrame((map(int, class_pred_Exclusive)))
MonteCarlo_SemiExclusive['target'] = DataFrame((map(int, class_pred_SemiExclusive)))
MonteCarlo_DrellYan['target'] = DataFrame((map(int, class_pred_DY)))
DataSet_DoubleMuon['target'] = DataFrame((map(int, class_pred_Data)))

events_select_DY = MonteCarlo_DrellYan.loc[MonteCarlo_DrellYan['target'] == 1]
events_select_exclusive = MonteCarlo_Exclusive.loc[MonteCarlo_Exclusive['target'] == 1]
events_select_semiexclu = MonteCarlo_SemiExclusive.loc[MonteCarlo_SemiExclusive['target'] == 1]
events_select_Data = DataSet_DoubleMuon.loc[DataSet_DoubleMuon['target'] == 1]

print('# eventos DY', (events_select_DY[6]*2).sum())
# eventos DY 403.1626630216077
print('# eventos Semi-Exclusive', (events_select_semiexclu[6]*2).sum())
# eventos Semi-Exclusive 36.51837196384899
print('# eventos Exclusivo', (events_select_exclusive[6]*2).sum())
# eventos Exclusivo 125.0399233047652
print('# eventos Data', len(events_select_Data))
# eventos Data 624

class_pred_DY = predict_proba_LGBM_background >= best_cut
class_pred_Exclusive = predict_proba_LGBM_exclusivo >= best_cut
class_pred_SemiExclusive = predict_proba_LGBM_semiexclusivo >= best_cut
class_pred_Data = predict_proba_LGBM_Data >= best_cut

MonteCarlo_Exclusive['target'] = DataFrame((map(int, class_pred_Exclusive)))
MonteCarlo_SemiExclusive['target'] = DataFrame((map(int, class_pred_SemiExclusive)))
MonteCarlo_DrellYan['target'] = DataFrame((map(int, class_pred_DY)))
DataSet_DoubleMuon['target'] = DataFrame((map(int, class_pred_Data)))

events_select_DY = MonteCarlo_DrellYan.loc[MonteCarlo_DrellYan['target'] == 1]
events_select_exclusive = MonteCarlo_Exclusive.loc[MonteCarlo_Exclusive['target'] == 1]
events_select_semiexclu = MonteCarlo_SemiExclusive.loc[MonteCarlo_SemiExclusive['target'] == 1]
events_select_Data = DataSet_DoubleMuon.loc[DataSet_DoubleMuon['target'] == 1]

print('# eventos DY', (events_select_DY[6]*2).sum())
# eventos DY 1255.5415577531858
print('# eventos Semi-Exclusive', (events_select_semiexclu[6]*2).sum())
# eventos Semi-Exclusive 69.60476656746316
print('# eventos Exclusivo', (events_select_exclusive[6]*2).sum())
# eventos Exclusivo 169.43988437545897
print('# eventos Data', len(events_select_Data))
# eventos Data 4727

import coffea.hist as hist
import mplhep as hep

histo = hist.Hist("Events",
        hist.Cat("sample", ""),
        hist.Bin("pt", "$P_{T_{\mu^{+}\mu^{-}}}(GeV/c)$", 20, 0, 10),
        hist.Bin("delta_eta", "$\Delta \eta_{\mu^{+}\mu^{-}}$", 20, -3, 3),
        hist.Bin("massa_inv", "$M_{\mu^{+}\mu^{-}}(GeV/c^{2})$", 20, 0, 600),
        hist.Bin("acopla", "Acoplanarity", 20, 0, 0.004),   
        )
histo.fill(
    sample = "Drell-Yan",
    pt = np.array(events_select_DY[0]),
    delta_eta = np.array(events_select_DY[3]),    
    massa_inv = np.array(events_select_DY[1]),
    acopla = np.array(events_select_DY[2]),
    weight = np.array(events_select_DY[6]*2)
    )
histo.fill(
    sample = "Semiexclusivo",
    pt = np.array(events_select_semiexclu[0]),
    delta_eta = np.array(events_select_semiexclu[3]),
    massa_inv = np.array(events_select_semiexclu[1]),
    acopla = np.array(events_select_semiexclu[2]),    
    weight = np.array(events_select_semiexclu[6]*2)
    )
histo.fill(
    sample = "Exclusivo",
    pt = np.array(events_select_exclusive[0]),
    delta_eta = np.array(events_select_exclusive[3]),
    massa_inv = np.array(events_select_exclusive[1]),
    acopla = np.array(events_select_exclusive[2]),    
    weight = np.array(events_select_exclusive[6]*2)
    )
histo.fill(
    sample = "Data-2017",
    pt = np.array(events_select_Data['Pt']),
    delta_eta = np.array(events_select_Data['DeltaEta']),    
    massa_inv = np.array(events_select_Data['MassaInvariante']),
    acopla = np.array(events_select_Data['Acoplanaridade']),   
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
fig, (ax, rax) = plt.subplots(
    nrows=2,
    ncols=1,
    figsize=(7,7),
    gridspec_kw={"height_ratios": (3, 1)},
    sharex=True

)
fig.subplots_adjust(hspace=.07)

pt1hist = histo.sum("delta_eta", "massa_inv", 'acopla')

hist.plot1d(
    pt1hist['Data-2017'],
    overlay="sample",
    clear=True,
    ax=ax,
    error_opts=data_err_opts
    )
hist.plot1d(
    pt1hist[notdata],
    overlay='sample',
    stack=True,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],
    clear=False,
    ax=ax,
    line_opts=False,
    fill_opts=fill_opts,
    error_opts=error_opts
    )

#plt.yscale('log')
plt.style.use([hep.style.ROOT, hep.style.firamath])
hep.cms.cmslabel()
ax.autoscale(axis='x', tight=True)
ax.set_ylim(0, 500)
ax.set_xlabel(None)
leg = ax.legend()

hist.plotratio(
    num=pt1hist['Data-2017'].sum("sample"),
    denom=pt1hist[notdata].sum("sample"),
    ax=rax,
    error_opts=data_err_opts,
    denom_fill_opts={},
    guide_opts={},
    unc='num'
)
rax.set_ylabel('Ratio')
rax.set_ylim(0,2)
plt.show()

# ---------------------------------- delta eta ---------------------------------- #

delta_etahist = histo.sum('pt', "massa_inv", 'acopla')

fig, (ax, rax) = plt.subplots(
    nrows=2,
    ncols=1,
    figsize=(7,7),
    gridspec_kw={"height_ratios": (3, 1)},
    sharex=True

)
fig.subplots_adjust(hspace=.07)

hist.plot1d(
    delta_etahist[notdata],
    overlay='sample',
    stack=True,
    ax = ax,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],
    line_opts=None,
    fill_opts=fill_opts,
    error_opts=error_opts 
)
hist.plot1d(
    delta_etahist['Data-2017'],
    ax = ax,
    overlay="sample",
    clear=False,
    error_opts=data_err_opts,
    density = False
)
plt.ylim(0,800)
plt.xlim(-4,4)
hep.cms.cmslabel()
ax.autoscale(axis='x', tight=True)
ax.set_ylim(0, 500)
ax.set_xlabel(None)
leg = ax.legend()

hist.plotratio(
    num=delta_etahist['Data-2017'].sum("sample"),
    denom=delta_etahist[notdata].sum("sample"),
    ax=rax,
    error_opts=data_err_opts,
    denom_fill_opts={},
    guide_opts={},
    unc='num'
)
rax.set_ylabel('Ratio')
rax.set_ylim(0,2)
plt.show()


# ---------------------------------- massa invariante ---------------------------------- #

masshist = histo.sum("pt", "delta_eta", 'acopla')

fig, (ax, rax) = plt.subplots(
    nrows=2,
    ncols=1,
    figsize=(7,7),
    gridspec_kw={"height_ratios": (3, 1)},
    sharex=True

)
fig.subplots_adjust(hspace=.07)

hist.plot1d(
    masshist[notdata],
    overlay='sample',
    stack=True,
    ax=ax,
    order = ['Exclusivo', 'Semiexclusivo', 'Drell-Yan'],    
    line_opts=None,
    fill_opts=fill_opts,
    error_opts=error_opts 
)
hist.plot1d(
    masshist['Data-2017'],
    overlay="sample",
    ax=ax,
    clear=False,
    error_opts=data_err_opts,
    density = False
)
plt.ylim(0, 1750)
#plt.yscale('log')
hep.cms.cmslabel()
plt.legend(loc="upper right")
ax.autoscale(axis='x', tight=True)
ax.set_ylim(0, 500)
ax.set_xlabel(None)
leg = ax.legend()

hist.plotratio(
    num=masshist['Data-2017'].sum("sample"),
    denom=masshist[notdata].sum("sample"),
    ax=rax,
    error_opts=data_err_opts,
    denom_fill_opts={},
    guide_opts={},
    unc='num'
)
rax.set_ylabel('Ratio')
rax.set_ylim(0,2)
plt.show()

