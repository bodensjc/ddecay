#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <mutex>
#include <stdexcept>
#include <vector>


const int gamma = 1;

  virtual T get_quantiles(double q) override
  {

    auto iter = checkpoint_raw_.begin();
    int idx   = iter->first;
    int count = iter->second;

    while (count < (q * (this->checkpoint_[1] - 1)) && iter != checkpoint_raw_.end())
    {
      iter++;
      idx = iter->first;
      count += iter->second;
    }
    return static_cast<T>(round(2 * pow(gamma, idx) / (gamma + 1)));
  }
