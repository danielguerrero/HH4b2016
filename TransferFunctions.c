#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLine.h>
#include <RooPolynomial.h>
#include "CMS_lumi.h"
#include <iostream>


Double_t pol0(Double_t *x, Double_t *par){
	return  par[0];
}


Double_t pol1(Double_t *x, Double_t *par){
        return  par[0]+par[1]*x[0];
}


Double_t pol2(Double_t *x, Double_t *par){
        return  par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
}


void TransferFunctions(){
    gROOT->SetStyle("Plain");
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gStyle->SetOptStat(0000);
    gStyle->SetOptFit(11111111);
    //gStyle->SetOptStat("SneMRou");
    
    int rebin = 5;

    TFile *f_SR_AntiTag_150=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2_AntiTag_150/Histograms_LMR_AntiTag_150_BTagTotal.root");
    TH1F *h_SR_AntiTag_150=(TH1F*)f_SR_AntiTag_150->Get("h_mX_SR_kinFit");
    h_SR_AntiTag_150->Rebin(rebin);

    TFile *f_SR_AntiTag=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2_AntiTag/Histograms_LMR_AntiTag_BTagTotal.root");
    TH1F *h_SR_AntiTag=(TH1F*)f_SR_AntiTag->Get("h_mX_SR_kinFit");
    h_SR_AntiTag->Rebin(rebin);

    TFile *f_SR_150=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2_150/Histograms_LMR_150BTagTotal.root");
    TH1F *h_SR_150=(TH1F*)f_SR_150->Get("h_mX_SR_kinFit");
    h_SR_150->Rebin(rebin);

    TFile *f_SB_AntiTag_150=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2_AntiTag_150/Histograms_LMR_AntiTag_150_BTagTotal.root");
    TH1F *h_SB_AntiTag_150=(TH1F*)f_SB_AntiTag_150->Get("h_mX_SB_kinFit");
    h_SB_AntiTag_150->Rebin(rebin);

    TFile *f_SB_AntiTag=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2_AntiTag/Histograms_LMR_AntiTag_BTagTotal.root");
    TH1F *h_SB_AntiTag=(TH1F*)f_SB_AntiTag->Get("h_mX_SB_kinFit");
    h_SB_AntiTag->Rebin(rebin);

    TFile *f_SB_150=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2_150/Histograms_LMR_150BTagTotal.root");
    TH1F *h_SB_150=(TH1F*)f_SB_150->Get("h_mX_SB_kinFit");
    h_SB_150->Rebin(rebin);

    TFile *f_SB=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_BTagTotal.root");
    TH1F *h_SB=(TH1F*)f_SB->Get("h_mX_SB_kinFit");
    h_SB->Rebin(rebin);


    h_SR_AntiTag_150->Scale(1./h_SR_AntiTag_150->Integral());
    h_SR_AntiTag->Scale(1./h_SR_AntiTag->Integral());
    h_SB_AntiTag->Scale(1./h_SB_AntiTag->Integral());
    h_SR_150->Scale(1./h_SR_150->Integral());
    h_SB_AntiTag_150->Scale(1./h_SB_AntiTag_150->Integral());
    h_SB_AntiTag->Scale(1./h_SB_AntiTag->Integral());
    h_SB_150->Scale(1./h_SB_150->Integral());
    h_SB->Scale(1./h_SB->Integral());

    TH1F *h_SB_AntiTag_test_1=(TH1F*)h_SB_AntiTag_150->Clone("h_mX_SB_kinFit");
    TH1F *h_SB_AntiTag_test_2=(TH1F*)h_SB_AntiTag_150->Clone("h_mX_SB_kinFit");
    h_SB_AntiTag_test_1->SetLineColor(kRed);
    h_SB_AntiTag_test_2->SetLineColor(kRed);

    TH1F *h_SR_150_test_1=(TH1F*)h_SR_AntiTag_150->Clone("h_mX_SR_kinFit");
    TH1F *h_SR_150_test_2=(TH1F*)h_SR_AntiTag_150->Clone("h_mX_SR_kinFit");
    h_SR_150_test_1->SetLineColor(kRed);
    h_SR_150_test_2->SetLineColor(kRed);

    h_SB_AntiTag_test_1->Divide(h_SB_150);
    h_SB_AntiTag_test_1->Multiply(h_SB);
    h_SB_AntiTag_test_2->Divide(h_SR_AntiTag_150);
    h_SB_AntiTag_test_2->Multiply(h_SR_AntiTag);

    h_SR_150_test_1->Divide(h_SB_150);
    h_SR_150_test_1->Multiply(h_SB_AntiTag_150);
    h_SR_150_test_2->Multiply(h_SB_150);
    h_SR_150_test_2->Divide(h_SB_AntiTag_150);


    TH1F *h_SB_test_1=(TH1F*)h_SB_AntiTag->Clone("h_mX_SR_kinFit");
    h_SB_test_1->SetLineColor(kRed);

    h_SB_test_1->Divide(h_SB_AntiTag_150);
    h_SB_test_1->Multiply(h_SB_150);

    TH1F *h_SR_test_1=(TH1F*)h_SB->Clone("h_mX_SR_kinFit");
    h_SR_test_1->SetLineColor(kRed);

    h_SR_test_1->Divide(h_SB_AntiTag);
    h_SR_test_1->Multiply(h_SR_AntiTag);

    //TH1F *h_SR_test_1=(TH1F*)h_SR_150->Clone("h_mX_SR_kinFit");
    //h_SR_test_1->SetLineColor(kRed);

    //h_SR_test_1->Divide(h_SB_150);
    //h_SR_test_1->Multiply(h_SB);

    TCanvas *c_D1=new TCanvas("c_D1", "c_D1", 700, 700);
    h_SB_AntiTag_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SB_AntiTag_test_1->Draw("same");
    h_SB_AntiTag->Draw("same");
    TLegend *leg_D1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_D1->SetBorderSize(0);
    leg_D1->SetTextSize(0.02);
    leg_D1->SetLineColor(1);
    leg_D1->SetLineStyle(1);
    leg_D1->SetLineWidth(2);
    leg_D1->SetFillColor(0);
    leg_D1->SetFillStyle(0);
    h_SB_AntiTag_test_1->SetMarkerColor(kRed);
    h_SB_AntiTag->SetMarkerColor(kAzure+10);
    leg_D1->AddEntry(h_SB_AntiTag_test_1, "h_SB_AntiTag_test_1", "l");
    leg_D1->AddEntry(h_SB_AntiTag, "h_SB_AntiTag", "l");
    leg_D1->Draw("same");

    TCanvas *c_D2=new TCanvas("c_D2", "c_D2", 700, 700);
    h_SB_AntiTag_test_2->GetXaxis()->SetRangeUser(240, 700);
    h_SB_AntiTag_test_2->Draw("same");
    h_SB_AntiTag->Draw("same");
    TLegend *leg_D2 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_D2->SetBorderSize(0);
    leg_D2->SetTextSize(0.02);
    leg_D2->SetLineColor(1);
    leg_D2->SetLineStyle(1);
    leg_D2->SetLineWidth(2);
    leg_D2->SetFillColor(0);
    leg_D2->SetFillStyle(0);
    h_SB_AntiTag_test_2->SetMarkerColor(kRed);
    h_SB_AntiTag->SetMarkerColor(kAzure+10);
    leg_D2->AddEntry(h_SB_AntiTag_test_2, "h_SB_AntiTag_test_2", "l");
    leg_D2->AddEntry(h_SB_AntiTag, "h_SB_AntiTag", "l");
    leg_D2->Draw("same");

    TCanvas *c_E1=new TCanvas("c_E1", "c_E1", 700, 700);
    h_SR_150_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SR_150_test_1->Draw("same");
    h_SB_AntiTag->Draw("same");
    TLegend *leg_E1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_E1->SetBorderSize(0);
    leg_E1->SetTextSize(0.02);
    leg_E1->SetLineColor(1);
    leg_E1->SetLineStyle(1);
    leg_E1->SetLineWidth(2);
    leg_E1->SetFillColor(0);
    leg_E1->SetFillStyle(0);
    h_SR_150_test_1->SetMarkerColor(kRed);
    h_SR_150->SetMarkerColor(kAzure+10);
    leg_E1->AddEntry(h_SR_150_test_1, "h_SR_150_test_1", "l");
    leg_E1->AddEntry(h_SR_150, "h_SR_150", "l");
    leg_E1->Draw("same");

    TCanvas *c_E2=new TCanvas("c_E2", "c_E2", 700, 700);
    h_SR_150_test_2->GetXaxis()->SetRangeUser(240, 700);
    h_SR_150_test_2->SetTitle("Test for ABCD Method in SR-150");
    h_SR_150_test_2->Draw("same");
    h_SR_150->Draw("same");
    //h_SB_150->SetLineColor(kAzure+10);
    //h_SR_AntiTag_150->Draw("same");
    //h_SR_AntiTag_150->SetLineColor(kOrange);
    //h_SB_AntiTag_150->Draw("same");
    //h_SB_AntiTag_150->SetLineColor(kGreen);
    TLegend *leg_E2 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_E2->SetBorderSize(0);
    leg_E2->SetTextSize(0.02);
    leg_E2->SetLineColor(1);
    leg_E2->SetLineStyle(1);
    leg_E2->SetLineWidth(2);
    leg_E2->SetFillColor(0);
    leg_E2->SetFillStyle(0);
    h_SR_150_test_2->SetMarkerColor(kRed);
    h_SR_150->SetMarkerColor(kAzure+10);
    leg_E2->AddEntry(h_SR_150_test_2, "h_SR_150_test", "l");
    leg_E2->AddEntry(h_SR_150, "h_SR_150", "l");
    //leg_E2->AddEntry(h_SR_AntiTag_150, "h_SR_AntiTag_150", "l");
    //leg_E2->AddEntry(h_SB_AntiTag_150, "h_SB_AntiTag_150", "l");
    leg_E2->Draw("same");
    c_E2->SaveAs("ABCDvalidation.png");

    TCanvas *c_B1=new TCanvas("c_B1", "c_B1", 700, 700);
    h_SB_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SB->GetXaxis()->SetRangeUser(240, 700);
    h_SB->Draw("same");
    h_SB_test_1->Draw("same");
    TLegend *leg_B1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_B1->SetBorderSize(0);
    leg_B1->SetTextSize(0.02);
    leg_B1->SetLineColor(1);
    leg_B1->SetLineStyle(1);
    leg_B1->SetLineWidth(2);
    leg_B1->SetFillColor(0);
    leg_B1->SetFillStyle(0);
    h_SB_test_1->SetMarkerColor(kRed);
    h_SB->SetMarkerColor(kAzure+10);
    leg_B1->AddEntry(h_SB_test_1, "h_SB_test_1", "l");
    leg_B1->AddEntry(h_SB, "h_SR", "l");
    leg_B1->Draw("same");



    TFile *f_SR=new TFile("PreselectedWithRegressionDeepCSV/LMRSelection_chi2/Histograms_LMR_BTagTotal.root");
    TH1F *h_SR=(TH1F*)f_SR->Get("h_mX_SR_kinFit");
    h_SR->Rebin(rebin);
    h_SR->Scale(1./h_SR->Integral());

    TCanvas *c_A1=new TCanvas("c_A1", "c_A1", 700, 700);
    h_SR_test_1->GetXaxis()->SetRangeUser(240, 700);
    h_SR_test_1->SetTitle("Prediction of \"A\"");
    h_SR_test_1->Draw("same");
    h_SB->Draw("same");
    h_SB->SetLineColor(kAzure+10);
    h_SR_AntiTag->Draw("same");
    h_SR_AntiTag->SetLineColor(kOrange);
    h_SB_AntiTag->Draw("same");
    h_SB_AntiTag->SetLineColor(kGreen);
    TLegend *leg_A1 = new TLegend(0.6,0.6,0.8,0.89,NULL,"brNDC");
    leg_A1->SetBorderSize(0);
    leg_A1->SetTextSize(0.02);
    leg_A1->SetLineColor(1);
    leg_A1->SetLineStyle(1);
    leg_A1->SetLineWidth(2);
    leg_A1->SetFillColor(0);
    leg_A1->SetFillStyle(0);
    h_SR_test_1->SetMarkerColor(kRed);
    h_SR_test_1->SetMarkerColor(kAzure+10);
    leg_A1->AddEntry(h_SR_test_1, "h_SR_prediction", "l");
    leg_A1->AddEntry(h_SB, "h_SB", "l");
    leg_A1->AddEntry(h_SR_AntiTag, "h_SR_AntiTag", "l");
    leg_A1->AddEntry(h_SB_AntiTag, "h_SB_AntiTag", "l");
    leg_A1->Draw("same");
    c_A1->SaveAs("ABCDprediction.png");



new TCanvas;
    TH1F *h_SR_150_diff=(TH1F*)h_SR_150_test_2->Clone("h_mX_SB_kinFit");
    h_SR_150_diff->Add(h_SR_150,-1);
    h_SR_150_diff->SetLineColor(kBlack);
    h_SR_150_diff->Draw("same");


    TCanvas * c_ratio = new TCanvas("Ratio_fit","Ratio_fit", 700,700);
    c_ratio->Divide(1,3);

    c_ratio->cd(1);
    TH1F *h_SR_150_ratio=(TH1F*)h_SR_150_test_2->Clone("h_mX_SB_kinFit");
    h_SR_150_ratio->Divide(h_SR_150);
    h_SR_150_ratio->SetLineColor(kBlack);
    TF1 *fit_pol = new TF1("fit_pol", pol0, 0., 2000., 1);	
    fit_pol->SetParameter(0, 1.);
    h_SR_150_ratio->Fit(fit_pol,"","",0.,700.);
    h_SR_150_ratio->GetYaxis()->SetRangeUser(0,2);
    h_SR_150_ratio->Draw();


    c_ratio->cd(2);
    TH1F *h_SR_150_ratio_1=(TH1F*)h_SR_150_test_2->Clone("h_mX_SB_kinFit");
    h_SR_150_ratio_1->Divide(h_SR_150);
    h_SR_150_ratio_1->SetLineColor(kBlack);
    TF1 *fit1_pol = new TF1("fit1_pol", pol1, 0., 2000., 2);
    fit1_pol->SetParameter(0, 1.);
    fit1_pol->SetParameter(1, 0.);
    h_SR_150_ratio_1->Fit(fit1_pol,"","",0.,700.);
    h_SR_150_ratio_1->GetYaxis()->SetRangeUser(0,2);
    h_SR_150_ratio_1->Draw();


    c_ratio->cd(3);
    TH1F *h_SR_150_ratio_2=(TH1F*)h_SR_150_test_2->Clone("h_mX_SB_kinFit");
    h_SR_150_ratio_2->Divide(h_SR_150);
    h_SR_150_ratio_2->SetLineColor(kBlack);
    TF1 *fit2_pol = new TF1("fit2_pol", pol2, 0., 2000., 3);
    fit2_pol->SetParameter(0, 1.);
    fit2_pol->SetParameter(1, 0.);
    fit2_pol->SetParameter(2, 0.);
    h_SR_150_ratio_2->Fit(fit2_pol,"","",0.,700.);
    h_SR_150_ratio_2->GetYaxis()->SetRangeUser(0,2);
    h_SR_150_ratio_2->Draw();

    c_ratio->SaveAs("ABCDratio.png");


/*
new TCanvas;
    TH1F *h_SB_AntiTag_ratio=(TH1F*)h_SB_AntiTag_test_1->Clone("h_mX_SB_kinFit");
    h_SB_AntiTag_ratio->Divide(h_SB_AntiTag);
    h_SB_AntiTag_ratio->SetLineColor(kBlack);
    h_SB_AntiTag_ratio->Draw("same");


TF1 *fit_pol1 = new TF1("fit_pol", pol0, 0., 2000., 1);
        fit_pol1->SetParameter(0, 1.);

        h_SB_AntiTag_ratio->Fit(fit_pol1,"","",0.,700.);

new TCanvas;
    TH1F *h_SB_ratio=(TH1F*)h_SB_test_1->Clone("h_mX_SB_kinFit");
    h_SB_ratio->Divide(h_SB);
    h_SB_ratio->SetLineColor(kBlack);
    h_SB_ratio->Draw("same");


TF1 *fit_pol2 = new TF1("fit_pol", pol0, 0., 2000., 1);
        fit_pol2->SetParameter(0, 1.);

        h_SB_ratio->Fit(fit_pol2,"","",0.,700.);
*/

}

