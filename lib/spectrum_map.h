#ifndef INCLUDED_SPECTRUM_MAP_H
#define INCLUDED_SPECTRUM_MAP_H

#include <timesvl/TimeSVL.h>
#include <boost/thread/mutex.hpp>
#include <string>

namespace gr {
  namespace timesvl {

    class spectrum_map
    {
	private:
		int d_spectrum_span;
		gr_vector_int d_spectrum_map_in;
		gr_vector_int d_spectrum_map_out;
		
		// From file_source_impl.h
		FILE *d_fp;
		FILE *d_new_fp;
		bool d_updated;
		boost::mutex fp_mutex;
		std::string d_filename;

		void do_update();
		

	public:
		spectrum_map();
		spectrum_map(const char *filename);
		~spectrum_map();

		void update_filename(const char* filename);
		std::string get_filename();

		void open(const char *filename);
		void close();
		void read_file();
		int get_size() const;
		gr_vector_int get_spectrum_map_in() const;
		gr_vector_int get_spectrum_map_out() const;

    };

  } // namespace mysvl
} // namespace gr

#endif /* INCLUDED_SPECTRUM_MAP_H */

