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


#ifndef INCLUDED_TIMESVL_TIMESVL_H
#define INCLUDED_TIMESVL_TIMESVL_H

#include <timesvl/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace timesvl {

    /*!
     * \brief <+description of block+>
     * \ingroup timesvl
     *
     */
    class TIMESVL_API TimeSVL : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<TimeSVL> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of timesvl::TimeSVL.
       *
       * To avoid accidental use of raw pointers, timesvl::TimeSVL's
       * constructor is in a private implementation
       * class. timesvl::TimeSVL::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t itemsize, unsigned int blocksize, const char *map_filename,
              const char *time_parameter_file);
    };

  } // namespace timesvl
} // namespace gr

#endif /* INCLUDED_TIMESVL_TIMESVL_H */

