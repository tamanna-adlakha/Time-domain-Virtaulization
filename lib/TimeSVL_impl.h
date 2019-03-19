/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_TIMESVL_TIMESVL_IMPL_H
#define INCLUDED_TIMESVL_TIMESVL_IMPL_H

#include <timesvl/TimeSVL.h>
#include "time_hypervisor.h"

namespace gr {
  namespace timesvl {

    class TimeSVL_impl : public TimeSVL
    {
     private:
   		size_t d_itemsize;
		unsigned int d_blocksize;
		unsigned int d_ninputs;
		unsigned int d_noutputs;
		unsigned int d_current_input;
		unsigned int d_current_output;
		unsigned int d_size_bytes;
		hypervisor d_time_hypervisor;
		//spectrum_map d_map;
		//time_parameter d_time_params;
		//std::vector<time_parameters> d_time_array;		
		std::vector<time_parameters> d_time_array_in;
		std::vector<time_parameters> d_time_array_out;
     public:

		TimeSVL_impl(size_t itemsize, unsigned int blocksize, const char *map_filename, const char *time_parameter_file);
		
		 ~TimeSVL_impl();
			
		//std::vector<time_parameters> get_time_array();
		 
		bool check_topology(int ninputs, int noutputs);

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

     
int general_work(int noutput_items,
       gr_vector_int &ninput_items,
     gr_vector_const_void_star &input_items,
     gr_vector_void_star &output_items);
   
		};

  } // namespace timesvl
} // namespace gr

#endif /* INCLUDED_TIMESVL_TIMESVL_IMPL_H */

