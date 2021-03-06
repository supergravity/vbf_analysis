#include "vbf_analysis/Utils/interface/PlotObject.h"
#include "vbf_analysis/Utils/interface/ParameterSet.h"

using namespace std;

namespace ARTKIT{


TCanvas* signalCanvas(){

    TCanvas* canv = new TCanvas("canv","canv",CANVX,CANVY);

return canv;

}

TPad* TopPad(){
    
    TPad* pad = new TPad("Pad","Pad",0.,0.245,1.,0.98);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.05);
    pad->SetBottomMargin(0.019);
    pad->SetLeftMargin(0.135);//0.12
    pad->SetRightMargin(0.06);//0.12

return pad;

}


TPad* BottomPad(){
    
    TPad* pad = new TPad("Pad1","Pad1",0.,0.0,1.,0.26);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.0);
    pad->SetBottomMargin(0.35);
    pad->SetLeftMargin(0.135);
    pad->SetRightMargin(0.06);

return pad;

}

TPad* NormalPad(){

    TPad* pad = new TPad("pad2","",0.,0.,1,0.98);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.05);
    pad->SetBottomMargin(0.12);
    pad->SetLeftMargin(0.135);//0.12
    pad->SetRightMargin(0.06);//0.12

return pad;
}

TLegend* newLegend(){

    TLegend* legend = new TLegend(LEGXMIN, LEGYMIN, LEGXMAX, LEGYMAX);
    legend -> SetFillStyle(0);
    legend -> SetBorderSize(0);
    legend -> SetTextFont(62);

return legend;
}

TH1D* ratioPlot(TH1D* hNumerator, TH1D* hDenominator, string xTitle, string yTitle){

    TH1D* hratioPlot = (TH1D*)hNumerator -> Clone();
    hratioPlot -> GetXaxis()->SetTitleSize(0.11);
    hratioPlot -> GetXaxis()->SetLabelSize(0.11);
    hratioPlot -> GetYaxis()->SetTitleSize(0.11);
    hratioPlot -> GetYaxis()->SetLabelSize(0.11); 
    hratioPlot -> GetYaxis()->SetTitleOffset(0.4);
    hratioPlot -> GetYaxis()->SetNdivisions(905);
    hratioPlot -> GetYaxis()->CenterTitle(true);
    hratioPlot -> SetLineColor(kBlack);
    hratioPlot -> SetXTitle(Form("%s",xTitle.c_str()));
    hratioPlot -> SetYTitle(Form("%s",yTitle.c_str()));
    hratioPlot -> Divide(hNumerator,hDenominator,1.,1.);
    hratioPlot -> SetMinimum(0.);
    hratioPlot -> SetMaximum(2.);

return hratioPlot;
}

TLine* horizontalLine(TH1D* plot, double y, Color_t color, Style_t style, Width_t width){

    TLine* line = new TLine(plot->GetBinLowEdge(1), y, plot->GetBinLowEdge(plot->GetNbinsX()+1), y);
    line -> SetLineColor(color);
    line -> SetLineStyle(style);
    line -> SetLineWidth(width);

return line;
}

};
