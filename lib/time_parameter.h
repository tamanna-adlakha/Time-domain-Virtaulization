#ifndef INCLUDED_TIME_PARAMETER_H
#define INCLUDED_TIME_PARAMETER_H

#include<timesvl/TimeSVL.h>
#include<fstream>
#include <boost/thread/mutex.hpp>
#include <cstring>


struct time_parameters
{
bool input;
int index;
int window_size;
};

namespace gr
{
	namespace timesvl
	{
	class time_parameter
	{
	private:
		FILE *d_fp;
		FILE *d_new_fp;
		bool d_updated;
		boost:: mutex fp_mutex;
		std::vector<time_parameters> time_array;
		void do_update();
	public:
		time_parameter();
		time_parameter(const char *filename);
		~time_parameter();
	
		void update_filename(const char* filename);
		void open(const char* filename);
		void close();
		void rfile();
		std::vector<time_parameters> get_time_array() const;
	};
	}
}
#endif
