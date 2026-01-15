#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "httplib.h"
#include "web-app/bff/handler.h"

ABSL_FLAG(int, port, 8080, "Port of the server will listen on");

namespace {

constexpr absl::string_view kStaticFilesPath = "./web-app/ui/dist";

absl::Status RealMain() {

  warehouse::ui::HandlerImpl handler;

  httplib::Server svr;

  // 1. Serve Static Files from the Angular build directory
  // In Bazel, this path will be relative to the runfiles
  auto ret = svr.set_mount_point("/", std::string(kStaticFilesPath));
  if (!ret) {
    return absl::InternalError("Static mount point directory not found.");
  }

#define REGISTER_HANDLER(path, func)                                           \
  svr.Post(path, [&](const httplib::Request &req, httplib::Response &res) {    \
    handler.func(req, res);                                                    \
  })

  // 2. API Endpoint (Standard POST)
  REGISTER_HANDLER("/api/greet", HandleGreet);

  LOG(INFO) << "Server running on http://localhost:"
            << absl::GetFlag(FLAGS_port);
  svr.listen("0.0.0.0", absl::GetFlag(FLAGS_port));
  return absl::OkStatus();
}
} // namespace

int main() {
  LOG(INFO) << "Hello World";
  CHECK_OK(RealMain());
  return 0;
}
