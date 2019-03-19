#include "time_parameter.h"
#include <gnuradio/thread/thread.h>
#include <gnuradio/io_signature.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <stdio.h>

bool window_size_2(int x)
{
  bool check = false;
  if (!(x == 0) && !(x & (x - 1))) check = true;
  
return check;
}

namespace gr
{
	namespace timesvl
	{
		time_parameter::time_parameter()
		{
			d_fp = 0;
			d_new_fp  =0;
			d_updated =false;
		}
		
		time_parameter::time_parameter(const char *filename)
		{
			d_fp      = 0;
			d_new_fp  = 0;
			d_updated = false;
			open(filename);
			do_update();
			rfile();
		}
		time_parameter::~time_parameter()
		{
			if (d_fp) fclose( (FILE *)d_fp);

			if(d_new_fp) fclose((FILE *)d_new_fp);
		}
		
		void time_parameter::update_filename(const char *filename)
		{	d_fp      = 0;
      			d_new_fp  = 0;
			d_updated = false;
			open(filename);
			do_update();
			rfile();
		}

		void time_parameter::open(const char *filename)
		{
		int fd;

		if((fd=::open(filename, O_RDONLY))<0)
		{
			perror(filename);
			throw std::runtime_error("file not opened");
		}
		
		if(d_new_fp)
		{
			fclose(d_new_fp);
			d_new_fp = 0;
		}
		
		if((d_new_fp=fdopen(fd, "rb"))==NULL)
		{
			perror(filename);
			::close(fd);
			throw std::runtime_error("file not opened");
		}
		d_updated=true;
		}
    void time_parameter::close()
    {
      // obtain exclusive access for duration of this function
      //gr::thread::scoped_lock lock(fp_mutex);

      if (d_new_fp != NULL)
      {
        fclose(d_new_fp);
        d_new_fp = NULL;
      }
      d_updated = true;
    }

		void time_parameter::do_update()
		{
		if(d_updated)
		{
			if(d_fp)
			fclose(d_fp);
			d_fp      = d_new_fp; // install new file pointer
			d_new_fp  = 0;
			d_updated = false;
    		}
		}	
		void time_parameter::rfile()
		{
			do_update();
			if(d_fp == NULL)
			throw std::runtime_error("work with file not open");
			int num = 0;
			time_array.clear();
			
			bool input;
			int index;
			int window_size;
		while (fscanf((FILE *)d_fp, "%d%d%d",&num,&index,&window_size)==3)
		{
		if((num>1) || (num<0))
		{
			perror("file error: input should be binary or bool");
			throw std::invalid_argument("error with time parameters in the file");
		}
		else input =(bool)num;

		//if(!window_size_2(window_size))
		//{
			//perror("file error");
			//throw std::invalid_argument("error with time parameter size in the file");
		//}

		time_parameters temp{ input, index, window_size};
		time_array.push_back(temp);

 		}
		if (ferror((FILE *)d_fp)) throw std::invalid_argument(
                "error reading time parameter file");
		}
std::vector<time_parameters> time_parameter::get_time_array() const
    {
      return time_array;
    }
}
}
