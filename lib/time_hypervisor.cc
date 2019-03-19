#include "spectrum_map.h"
#include "time_parameter.h"
#include "time_hypervisor.h"
#include <gnuradio/io_signature.h>
#include <cstdio>
#include <gnuradio/io_signature.h>
#include <boost/math/common_factor_rt.hpp>

namespace gr {
  namespace timesvl {
	
	hypervisor::hypervisor(const char *map_filename, const char *time_param_file, int itemsize,int blocksize): d_map(map_filename), d_itemsize(itemsize), d_time_params(time_param_file), d_blocksize(blocksize)
	{
		std::vector<time_parameters> time_array = d_time_params.get_time_array();
		
		//printf("pass");
	 	int input_window_size = 0;
	 	int output_window_size = 0;
	
	for(unsigned int i = 0; i<time_array.size(); i++)
	{ 	//printf("pass2");
		if(time_array[i].input) 
		{
		input_window_size +=time_array[i].window_size;
		//printf("input window size is : %d \n", input_window_size);
		}		
		else
		{
		output_window_size += time_array[i].window_size; 
		//printf("output window size is : %d \n", input_window_size);		
		//printf("pass3");
		}	
	} 
		if(input_window_size != output_window_size)
		printf("window_size problem");
		else 
		printf("window size same");
d_span = input_window_size;
}

	hypervisor::hypervisor() : d_map() {}
	hypervisor::~hypervisor() {}

void hypervisor::create_vectors(int ninputs, int noutputs)
{	d_time_params.get_time_array();
	
	std::vector<time_parameters> time_array = d_time_params.get_time_array();
    //printf("creating vectors \n");

		int time_inputs= 0;
		int time_outputs = 0;
		d_items_in.clear();
		d_items_out.clear();

	for(unsigned int i = 0; i<time_array.size(); i++)
	{
		if(time_array[i].input)
			{
				d_items_in.resize(d_items_in.size()+1);			d_items_in[time_inputs].resize(time_array[i].window_size);
				time_inputs++;
		//	printf("time_inputs:%d\n", time_inputs);
			//	printf("test1\n");
			}
	   else {
			d_items_out.resize(d_items_out.size() + 1);
  		d_items_out[time_outputs].resize(time_array[i].window_size);
			time_outputs++;
			//printf("time_outputs:%d\n", time_outputs);
			//printf("test2\n");
			}
	}
	if(!(time_inputs==ninputs && time_outputs==noutputs))
	{
	printf("error in items\n");
	}
}			
void hypervisor::print_spectrum_map() 
{
//		printf("Spectrum maps \n");
		for(unsigned int i=0; i<d_map.get_size(); i++) 
		{
			printf("in: %d ", d_map.get_spectrum_map_in()[i]);
			printf(" out: %d \n", d_map.get_spectrum_map_out()[i]);
		}
}
     
std::vector<time_parameters> hypervisor::get_time_array()
{//		printf("time_array_passed \n");
	return 	d_time_params.get_time_array(); 
}

int hypervisor::get_span()
{ 
return d_span;
}

void hypervisor::store_input_vector(int input, unsigned int ninput_items, const gr_complex* in, size_t itemsize)
{
	if(d_items_in[input].size() <= d_items_in[input].size() + ninput_items)
	{
		d_items_in[input].resize(d_items_in[input].size() + ninput_items);
		d_items_in[input].insert(d_items_in[input].end(), &in[0], &in[ninput_items*itemsize]);

		std::copy(&in[0], &in[ninput_items*itemsize], d_items_in[input].begin());
//printf("stored\n");
	}
}
void hypervisor::output_vector(int output, unsigned int noutput_items, gr_complex* out) 
{
	std::copy(d_items_out[output].end()-noutput_items, 	d_items_out[output].end(), out);
}

void hypervisor::work()
{ 
	//	printf("hypervisor work\n");

		gr_vector_int input_map = d_map.get_spectrum_map_in();
		gr_vector_int output_map= d_map.get_spectrum_map_out();
 
		gr_vector_int track_input_locations;
		gr_vector_int track_output_locations;

		for(unsigned int input = 0; input<d_items_in.size(); input++)
{
		track_input_locations.push_back(0); 
}		
		for(unsigned int output = 0; output<d_items_out.size(); output++)
{
		track_output_locations.push_back(0);
}
		for(unsigned int i=0; i<input_map.size(); i++) 
		{
			d_items_out[output_map[i]-1][track_output_locations[output_map[i]-1]]=d_items_in[input_map[i]-1][track_input_locations[input_map[i]-1]];
			track_output_locations[output_map[i]-1]++;
			track_input_locations[input_map[i]-1]++;
		}

		for(unsigned int input=0; input<d_items_in.size(); input++) 		{
		    d_items_in[input].clear();
		}
		

}
void hypervisor::print_complex_samples(int input) 
	{

		// Print out is working.
		for(unsigned int i=0; i<d_items_in[input].size(); i++) 
		{
			printf("Complex number: %f, %f \n", d_items_in[input][i].real(), d_items_in[input][i].imag());
		}
		
	}

}

}
