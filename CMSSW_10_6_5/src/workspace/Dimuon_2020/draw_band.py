
import numpy as np

import ROOT

def draw_band( functionprotonName, functionmumuName, graph_matchName, graph_non_matchName, titleName, fileName ):

    xi_min = 0.
    xi_max = 0.25

    file_func = ROOT.TFile("/mnt/hadoop/cms/store/user/malvesga/etc/pol_function.root","READ")
    res_vs_xi_proton = file_func.Get( functionprotonName )
    res_vs_xi_mumu = file_func.Get( functionmumuName )
    file_graph = ROOT.TFile("histos_data/output_data_sigma_limitRun.root","READ")
    graph_match = file_graph.Get( graph_matchName )
    graph_non_match = file_graph.Get( graph_non_matchName )

    arr_xi = np.linspace(xi_min,xi_max,100)

    f_up = lambda xi: xi + 2*np.sqrt( ( res_vs_xi_mumu.Eval(xi) )**2 + ( res_vs_xi_proton.Eval(xi) )**2 )
    f_dw = lambda xi: xi - 2*np.sqrt( ( res_vs_xi_mumu.Eval(xi) )**2 + ( res_vs_xi_proton.Eval(xi) )**2 )

    arr_xi_up = np.array( list(map(f_up,arr_xi)) )
    arr_xi_dw = np.array( list(map(f_dw,arr_xi)) )

    n_points = arr_xi.size 
    gr_all = ROOT.TGraph(2*n_points)
    for i in range(n_points):
        gr_all.SetPoint(i,arr_xi[i],arr_xi_up[i])
        gr_all.SetPoint(n_points+i,arr_xi[n_points-i-1],arr_xi_dw[n_points-i-1]) 

    gr_all.SetFillColor(16)
    gr_all.SetFillStyle(3013)

    canvas1 = ROOT.TCanvas()
    gr_box1 = ROOT.TBox(0, 0, 0.02, 0.16)
    gr_box2 = ROOT.TBox(0.02, 0, 0.03, 0.16)
    gr_line1 = ROOT.TLine(0.02, 0, 0.02, 0.16)
    gr_line2 = ROOT.TLine(0.03, 0, 0.03, 0.16)
    gr_box1.SetLineColorAlpha(49, 0.5)
    gr_box1.SetLineStyle(9)
    gr_box1.SetFillColorAlpha(49, 0.5)
    gr_box1.SetFillStyle(1001)
    gr_box2.SetLineColorAlpha(30, 0.5)
    gr_box2.SetLineStyle(9)
    gr_box2.SetFillColorAlpha(30, 0.5)
    gr_box2.SetFillStyle(1001)
    gr_line1.SetLineColorAlpha(49, 0.5)
    gr_line1.SetLineWidth(2)
    gr_line2.SetLineColorAlpha(30, 0.5)
    gr_line2.SetLineWidth(2)
    graph_match.SetMarkerStyle(22)
    graph_match.SetMarkerColor(4)
    graph_non_match.SetMarkerStyle(23)
    graph_non_match.SetMarkerColor(2)
    mg = ROOT.TMultiGraph()
    #mg.SetTitle( titleName )
    mg.GetXaxis().SetTitle("#xi(RP)")
    mg.GetXaxis().SetLimits(0, .16)
    mg.GetYaxis().SetTitle("#xi(#mu^{+}#mu^{-})")
    mg.SetMinimum(0)
    mg.SetMaximum(.16)
    mg.Add(gr_all, "ALF")
    mg.Add(graph_match, "AP")
    mg.Add(graph_non_match, "AP")
    mg.Draw("AP")
    leg = ROOT.TLegend(.9,.9,.68,.68)
    leg.AddEntry(gr_box1, "No acceptance for any RP" , "f")
    leg.AddEntry(gr_box2, "No acceptance for right RP" , "f")
    leg.AddEntry(graph_match, "Matching Events" , "p")
    leg.AddEntry(graph_non_match, "Non-Matching Events" , "p")
    leg.AddEntry(gr_all, "2 Sigma Area" , "f")
    leg.Draw()
    gr_box1.Draw("SAME")
    gr_box2.Draw("SAME")
    gr_line1.Draw("SAME")
    gr_line2.Draw("SAME")

    canvas1.SaveAs( fileName, "pdf")
    canvas1.cd()
    canvas1.Close()

    return 0

if __name__ == "__main__":

   draw_band("f_rp3", "f_pair_left", "g_xi_left_reco_rp3_match", "g_xi_left_reco_rp3_non_match", "#xi Left Correlation - RP 3", "results/xi_corr_rp3_band.pdf") 
   draw_band("f_rp23", "f_pair_left", "g_xi_left_reco_rp23_match", "g_xi_left_reco_rp23_non_match", "#xi Left Correlation - RP 23", "results/xi_corr_rp23_band.pdf") 
   draw_band("f_rp23_nprot", "f_pair_left", "g_xi_left_reco_rp23_nprot_match", "g_xi_left_reco_rp23_nprot_non_match", "#xi Left Correlation - RP 23_nprot", "results/xi_corr_rp23_nprot_band.pdf") 
   draw_band("f_left_single", "f_pair_left", "g_xi_left_reco_single_match", "g_xi_left_reco_single_non_match", "#xi Left Correlation - Single RP", "results/xi_corr_left_single_band.pdf") 
   draw_band("f_rp103", "f_pair_right", "g_xi_right_reco_rp103_match", "g_xi_right_reco_rp103_non_match", "#xi Right Correlation - RP 103", "results/xi_corr_rp103_band.pdf") 
   draw_band("f_rp123", "f_pair_right", "g_xi_right_reco_rp123_match", "g_xi_right_reco_rp123_non_match", "#xi Right Correlation - RP 123", "results/xi_corr_rp123_band.pdf") 
   draw_band("f_rp123_nprot", "f_pair_right", "g_xi_right_reco_rp123_nprot_match", "g_xi_right_reco_rp123_nprot_non_match", "#xi Right Correlation - RP 123_nprot", "results/xi_corr_rp123_nprot_band.pdf") 
   draw_band("f_right_single", "f_pair_right", "g_xi_right_reco_single_match", "g_xi_right_reco_single_non_match", "#xi Right Correlation - Single RP", "results/xi_corr_right_single_band.pdf") 
   draw_band("f_left_multi", "f_pair_left", "g_xi_left_reco_multi_match", "g_xi_left_reco_multi_non_match", "#xi Left Correlation - Multi RP", "results/xi_corr_left_multi_band.pdf") 
   draw_band("f_right_multi", "f_pair_right", "g_xi_right_reco_multi_match", "g_xi_right_reco_multi_non_match", "#xi Right Correlation - Multi RP", "results/xi_corr_right_multi_band.pdf") 
