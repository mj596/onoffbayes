#ifndef _plots_H
#define _plots_H 1

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include "root.h"

using namespace std;

void makePosteriorPlotROOT( gsl_vector* x, gsl_vector* y, TCanvas* c1, TMultiGraph* mg );

#endif /* _plots_H */
