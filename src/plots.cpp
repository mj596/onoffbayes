#include "plots.h"

void makePosteriorPlotROOT( gsl_vector* x, gsl_vector* y, TCanvas* c1, TMultiGraph* mg ) {
  c1->cd();
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  gPad->Modified();
  gPad->Update();
  double xx[y->size], yy[y->size];
  for (int i=0;i<y->size;i++) {
      xx[i] = gsl_vector_get(x,i);
      yy[i] = gsl_vector_get(y,i); }

  TGraph *gr = new TGraph(y->size,xx,yy);
  gr->SetLineColor(2);
  gr->SetLineWidth(-202);
  gr->SetFillStyle(3001);
  gr->GetXaxis()->SetLimits(1.9,8.3);
  mg->SetMinimum(0);
  //  mg->SetMinimum(0.5);
  mg->Add( gr );
  c1->Clear();
  mg->Draw("alp");
  c1->Modified();
  c1->Update();
  gSystem->ProcessEvents();
}
