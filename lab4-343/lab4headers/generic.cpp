//-------------------- Metadata --------------------
/**
 * @file generic.cpp
 * Purpose:     We're not even sure what this file does.
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        June 06 2014
 * @copyright   WTFPLv2.1
 *
 * Note: Private helpers are typically found under the routine(s)
 * that uses them.
 *///-----------------------------------------------
        

#include "generic.h"

Generic::~Generic() {}

ostream& operator << (ostream& out, const Generic& gen) {
	gen.formatOutput(out);
	return out;
}