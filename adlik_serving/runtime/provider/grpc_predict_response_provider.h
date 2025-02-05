#ifndef ADLIK_SERVING_RUNTIME_PROVIDER_GRPC_PREDICT_RESPONSE_PROVIDER_H
#define ADLIK_SERVING_RUNTIME_PROVIDER_GRPC_PREDICT_RESPONSE_PROVIDER_H

#include <string>
#include <vector>

#include "adlik_serving/runtime/provider/predict_response_provider.h"

namespace adlik {
namespace serving {

struct PredictResponse;

struct GRPCPredictResponseProvider : PredictResponseProvider {
public:
  static tensorflow::Status create(const std::vector<std::string>& output_names,
                                   size_t batch_size,
                                   PredictResponse& rsp,
                                   std::unique_ptr<GRPCPredictResponseProvider>* provider);

  tensorflow::Status addOutput(const std::string&,
                               tensorflow::DataType dtype,
                               const DimsList& dims,
                               void** buffer,
                               size_t buffer_byte_size);

private:
  GRPCPredictResponseProvider(const std::vector<std::string>& output_names,
                              size_t batch_size,
                              PredictResponse& response);

  std::vector<std::string> output_names;
  PredictResponse& rsp;
  size_t batch_size;
};

}  // namespace serving
}  // namespace adlik

#endif /* RUNTIME_PROVIDER_MODEL_GRPC_PREDICT_RESPONSE_PROVIDER_H_ */
