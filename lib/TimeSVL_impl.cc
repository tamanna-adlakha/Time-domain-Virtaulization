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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <boost/math/common_factor_rt.hpp>
#include <gnuradio/io_signature.h>
#include<cstdio>
#include "TimeSVL_impl.h"

namespace gr {
  namespace timesvl {

    TimeSVL::sptr
    TimeSVL::make(size_t itemsize, unsigned int blocksize, const char *map_filename, const char *time_parameter_file)
    {
      return gnuradio::get_initial_sptr
        (new TimeSVL_impl(itemsize, blocksize, map_filename, time_parameter_file));
    }

    /*
     * The private constructor
     */
    TimeSVL_impl::TimeSVL_impl(size_t       itemsize,
                       unsigned int blocksize,
                       const char  *map_filename,
                       const char  *time_parameter_file)
      : gr::block("TimeSVL",
              gr::io_signature::make(1, io_signature::IO_INFINITE, itemsize),
              gr::io_signature::make(1, io_signature::IO_INFINITE, itemsize)),d_itemsize(itemsize),d_blocksize(blocksize),d_current_input(0),
      d_current_output(0), d_time_hypervisor(map_filename, time_parameter_file,itemsize,blocksize) 

//constructor definition
    {
     d_time_hypervisor.get_time_array();	
	 d_time_hypervisor.get_span();
	 //printf("pass1");
		std::vector<time_parameters> d_time_array = d_time_hypervisor.get_time_array();
		//printf("pass_time_array_svl \n");
		int smallest_window_size = d_time_array[0].window_size;		
      	set_tag_propagation_policy(TPP_DONT);
		
		d_time_array_in.clear();
		d_time_array_out.clear();
		//printf("clear pass\n");

	for(int j = 0; j<d_time_array.size(); j++)
		{	
			if(d_time_array[j].window_size < smallest_window_size)
			{
			smallest_window_size = d_time_array[j].window_size;
			//printf("if1 pass\n");
			}

			if(d_time_array[j].input)
			{
			d_time_array_in.push_back(d_time_array[j]);
			//printf("if2 pass\n");
			}
			else
			{
			d_time_array_out.push_back(d_time_array[j]);
			//printf("else pass\n");
			}
		//	printf("value of j %d", j);	
		} 
		//printf("for pass\n");

	 set_output_multiple(d_time_hypervisor.get_span());
	// d_time_hypervisor.print_spectrum_map();
}
    /*
     * Our virtual destructor.
     */
    TimeSVL_impl::~TimeSVL_impl() {}
	bool
	TimeSVL_impl::check_topology(int ninputs,int noutputs)
	{ 
	  d_ninputs  = ninputs;
      d_noutputs = noutputs;
      int total_input_size  = 0;
      int total_output_size = 0;
	for (int i = 0; i < d_time_array_in.size(); i++)
	{
	total_input_size+= d_time_array_in[i].window_size;
	//printf("Total input size%d\n",total_input_size);
	}	
	for (int j = 0; j< d_time_array_out.size(); j++)
{	
	total_output_size+= d_time_array_out[j].window_size;
}
d_time_hypervisor.create_vectors(ninputs, noutputs);
set_output_multiple(d_time_hypervisor.get_span());	
return true;

}
	void
    TimeSVL_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
		int span = d_time_hypervisor.get_span();
		//printf("span:%d\n", span);
	for(unsigned int i = 0; i<ninput_items_required.size(); i++) 
		{       
			ninput_items_required[i] = (int)(noutput_items *d_time_array_in[i].window_size/d_time_hypervisor.get_span()+.5) ;
//printf("Number of items required for input %d is %d \n", i, ninput_items_required[i]);
   }
}
    int
    TimeSVL_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
	const char **in = (const char **) &input_items[0];
  	char **out = (char **) &output_items[0];
//	int span_work = d_time_hypervisor.get_span();
	
		unsigned int acc = 0;
		unsigned int skip = 0;
		int ntags = 0;
		int count = 0;
		int total_count = noutput_items /d_time_hypervisor.get_span();
		std::vector<tag_t> tags;
     get_tags_in_range(tags, 0, 0, noutput_items, pmt::intern("trigger"));
	if(tags.size()>0)
	{
		if(tags[0].offset % d_time_hypervisor.get_span() != 0)
		{
			 printf("Unsynchronized tag. Dropping %lu samples\n", tags[0].offset);
		      consume(0, tags[0].offset);
		      set_history(ninput_items[0] - tags[0].offset);
		      return 0;
		}
	}		
while(count<total_count)
{
	for (unsigned int i = 0; i<d_ninputs; i++)
	{
d_time_hypervisor.store_input_vector(i,d_time_array_in[i].window_size, (gr_complex *)in[i], d_itemsize);
//d_time_hypervisor.print_complex_samples(i); 
in[i] = in[i]+ (d_itemsize * d_time_array_in[i].window_size);
	consume(i, d_time_array_in[i].window_size);
	}

	d_time_hypervisor.work();

	for (unsigned int j = 0; j<d_noutputs; j++)
	{
	d_time_hypervisor.output_vector(j, d_time_array_out[j].window_size, (gr_complex *)out[j]);
	out[j] = out[j]+d_itemsize * d_time_array_out[j].window_size;
	//printf("output %d, Window Size: %d", j, d_time_array_out[j].window_size);
	produce(j,d_time_array_out[j].window_size);
	}
	
 count++;
//printf("count: %d\n", count);
//printf("total_count: %d\n", total_count);

}
return WORK_CALLED_PRODUCE;
	} 

  } /* namespace timesvl */
} /* namespace gr */

