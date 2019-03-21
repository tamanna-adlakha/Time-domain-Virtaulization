/* -*- c++ -*- */

#define TIMESVL_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "timesvl_swig_doc.i"

%{
#include "timesvl/TimeSVL.h"
%}


%include "timesvl/TimeSVL.h"
GR_SWIG_BLOCK_MAGIC2(timesvl, TimeSVL);


