#ifndef ADLIK_SERVING_SERVER_HTTP_HTTP_SERVER_H_
#define ADLIK_SERVING_SERVER_HTTP_HTTP_SERVER_H_

#include <memory>

#include "adlik_serving/server/http/http_options.h"
#include "adlik_serving/server/http/internal/server_interface.h"
#include "cub/base/status.h"
#include "cub/dci/role.h"

namespace adlik {
namespace serving {

struct ServerInterface;
struct GetModelMetaImpl;
struct PredictImpl;

struct HttpServer : HttpOptions {
  cub::Status start();
  void wait();

private:
  void buildServer();
  std::unique_ptr<ServerInterface> server;

private:
  USE_ROLE(GetModelMetaImpl);
  USE_ROLE(PredictImpl);
};

}  // namespace serving
}  // namespace adlik

#endif /* SERVER_HTTP_HTTP_SERVER_H_ */
