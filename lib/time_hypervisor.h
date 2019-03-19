#ifndef INCLUDED_HYPERVISOR_H
#define INCLUDED_HYPERVISOR_H

#include <timesvl/TimeSVL.h>
#include "spectrum_map.h"
#include "time_parameter.h"

namespace gr
{
	namespace timesvl
	{
	class hypervisor
	{
	private:
		
		size_t d_itemsize;
		unsigned int d_blocksize;
		unsigned int d_ninputs;
		unsigned int d_noutputs;
		unsigned int d_current_input;
		unsigned int d_current_output;
		unsigned int d_size_bytes;
		unsigned int noutput_items;
		int d_span;
		//unsigned int d_ninput_items;
		spectrum_map d_map;
		time_parameter d_time_params;
		//std::vector<std::vector<int>> ninput_items;
		//std::vector<std::vector<const void *>> input_items;
		//std::vector<std::vector<void *>> output_items;			
		std::vector<std::vector<gr_complex>> d_items_in;
		std::vector<std::vector<gr_complex>> d_items_out;
	public:
		
		hypervisor();

		hypervisor(const char *map_filename, const char *time_parameter_file, int itemsize,int blocksize);
		~hypervisor();

		void create_vectors(int ninputs, int noutputs);
		void store_input_vector(int input, unsigned int ninput_items, const gr_complex* in, size_t itemsize);
		void output_vector(int output, unsigned int noutput_items, gr_complex* out);		
		void print_spectrum_map();

		std::vector<time_parameters> get_time_array();
		
		int get_span();		

		void print_complex_samples(int input);

		//bool check_spectrum_map(int ninputs, int nouputs);

		void work();
};

/*		
typedef std::vector<int> &ninput_items;
typedef std::vector<const void *> &input_items;
typedef std::vector<void *> &output_items;
*/
}
}
#endif 
