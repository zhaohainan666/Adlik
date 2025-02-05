#ifndef ADLIK_SERVING_PROVIDER_PREDICT_RESPONSE_PROVIDER_H
#define ADLIK_SERVING_PROVIDER_PREDICT_RESPONSE_PROVIDER_H

#include <string>

#include "adlik_serving/framework/domain/dims_list.h"
#include "tensorflow/core/framework/types.pb.h"
#include "tensorflow/core/lib/core/status.h"

namespace adlik {
namespace serving {

struct PredictResponseProvider {
public:
  explicit PredictResponseProvider() {
  }

  // Get a pointer to the buffer into which output 'name' should be
  // written. The size of the buffer must be exactly
  // 'buffer_byte_size'.
  virtual tensorflow::Status addOutput(const std::string&,
                                       tensorflow::DataType dtype,
                                       const adlik::serving::DimsList& dims,
                                       void** buffer,
                                       size_t buffer_byte_size) = 0;
};

}  // namespace serving
}  // namespace adlik

#endif
