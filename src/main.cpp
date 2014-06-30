#include <iostream>
#include <cstdio>
#include <cstdlib> 
#include <sstream>
#include "anaBayes.h"
#include "anaLiMa.h"
#include "anaData.h"
#include "print.h"
#include "plots.h"

using namespace std;

int main(int argc, char *argv[]) {
  anaBayes *abayes = new anaBayes( false );
  anaLiMa *alima = new anaLiMa( false );    
  anaData *data = new anaData( false );

  if( data->set( atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atof(argv[4]) ) )
    { print_info("You do not want to use ExpOn > ExpOff! Quit.");
      exit(1); }

  // data->print();
  alima->set( data->get_NOn(),
	      data->get_NOff(),
	      data->get_ExpOn(),
	      data->get_ExpOff() );
  alima->analyse( );
  
  cout << "LiMa:" << endl;
  cout << "Excess : " << alima->getExcess( ) << endl;
  cout << "Significance : " << alima->getSignificance( ) << endl;
  cout << "1 sig interval : (" << alima->getInterval( 1.0 )[0] << ";" << alima->getInterval( 1.0 )[1] << ")" << endl;
  cout << "2 sig interval : (" << alima->getInterval( 2.0 )[0] << ";" << alima->getInterval( 2.0 )[1] << ")" << endl;
  cout << "3 sig interval : (" << alima->getInterval( 3.0 )[0] << ";" << alima->getInterval( 3.0 )[1] << ")" << endl;

  abayes->set( data->get_NOn(),
	      data->get_NOff(),
	      data->get_ExpOn(),
	      data->get_ExpOff() );

  abayes->setReadDir("data");
  abayes->setSaveDir("data");

  if( abayes->readAnalysis( ) )
    {
      if( !abayes->analyse( true ) )      
      {
    	  cout << "Bayes:" << endl;
    	  cout << "Mean : " << abayes->getMean( ) << endl;
	  cout << "Mode : " << abayes->getMode( ) << endl;
	  cout << "Median : " << abayes->getMedian( ) << endl;
	  cout << "Significance : " << abayes->getSignificance( ) << endl;
	  
	  abayes -> initialize_credible_interval_calculator( );
	  cout << "1 sig interval : (" << abayes->getInterval( 1.0 )[0] << ";" << abayes->getInterval( 1.0 )[1] << ")" << endl;
	  cout << "2 sig interval : (" << abayes->getInterval( 2.0 )[0] << ";" << abayes->getInterval( 2.0 )[1] << ")" << endl;
	  cout << "3 sig interval : (" << abayes->getInterval( 3.0 )[0] << ";" << abayes->getInterval( 3.0 )[1] << ")" << endl;
	  
	  TApplication theApp("App",0,0);
	  if( atoi(argv[5]) ) {
	    /* Create TApplication and check if we're not in a Batch Mode */
	    if (gROOT->IsBatch()) { print_info("[ERROR] Cannot run in batch mode. Quit."); }
	    TCanvas *posteriorCanvas = new TCanvas("Posterior","",0,0,600,600);   
	    gSystem->ProcessEvents();
	    TMultiGraph *posteriorMG = new TMultiGraph("Posterior",";s;p(s)");
	    makePosteriorPlotROOT( abayes->get_vs( ), abayes->get_vps( ), posteriorCanvas, posteriorMG ); }
	  if( atoi(argv[5]) ) {
	    print_info("[MAIN] PRESS 'ENTER' TO QUIT.");
	    cin.ignore(); }	  
	}
    }
  else
    {
      cout << "Mean : " << abayes->getMean( ) << endl;
      cout << "Mode : " << abayes->getMode( ) << endl;
      cout << "Median : " << abayes->getMedian( ) << endl;
      cout << "Significance : " << abayes->getSignificance( ) << endl;
      
      abayes -> initialize_credible_interval_calculator( );
      cout << "1 sig interval : (" << abayes->getInterval( 1.0 )[0] << ";" << abayes->getInterval( 1.0 )[1] << ")" << endl;
      cout << "2 sig interval : (" << abayes->getInterval( 2.0 )[0] << ";" << abayes->getInterval( 2.0 )[1] << ")" << endl;
      cout << "3 sig interval : (" << abayes->getInterval( 3.0 )[0] << ";" << abayes->getInterval( 3.0 )[1] << ")" << endl;
      
      TApplication theApp("App",0,0);
      if( atoi(argv[5]) ) {
	/* Create TApplication and check if we're not in a Batch Mode */
	if (gROOT->IsBatch()) { print_info("[ERROR] Cannot run in batch mode. Quit."); }
	TCanvas *posteriorCanvas = new TCanvas("Posterior","",0,0,600,600);   
	gSystem->ProcessEvents();
	TMultiGraph *posteriorMG = new TMultiGraph("Posterior",";s;p(s)");
	makePosteriorPlotROOT( abayes->get_vs( ), abayes->get_vps( ), posteriorCanvas, posteriorMG );
	posteriorCanvas->Print();
      }
      
      if( atoi(argv[5]) ) {
	print_info("[MAIN] PRESS 'ENTER' TO QUIT.");
	cin.ignore(); }
    }
  
  
  delete abayes;
  delete alima;
  delete data;
  abayes = NULL;
  alima = NULL;
  data = NULL;
  
  return 0; }
