#include "phrqtype.h"
#include <Phreeqc.h>

double Phreeqc::get_rate_m() const { return this->rate_m; }
double Phreeqc::get_rate_time() const { return this->rate_time; }
double Phreeqc::get_saturation_index(const char *name) {
  static LDBLE dummy;
  LDBLE ret_val;

  this->saturation_index(name, &dummy, &ret_val);

  return ret_val;
}
double Phreeqc::get_activity(const char *name) { return this->activity(name); }
