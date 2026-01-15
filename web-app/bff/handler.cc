#include "web-app/bff/handler.h"

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "google/protobuf/util/json_util.h"
#include "httplib.h"
#include "shared/proto/ui.pb.h"

namespace warehouse::ui {

using ::google::protobuf::util::JsonStringToMessage;
using ::google::protobuf::util::MessageToJsonString;

void HandlerImpl::HandleGreet(const httplib::Request &request,
                              httplib::Response &response) {
  Person person;
  if (absl::Status status = JsonStringToMessage(request.body, &person);
      !status.ok()) {
    LOG(ERROR) << "Failed to parse JSON: " << status;
    response.status = 404;
    return;
  }
  Greet greet;
  greet.set_message(absl::StrCat("Hello ", person.name()));

  std::string json_output;
  if (absl::Status status = MessageToJsonString(greet, &json_output);
      !status.ok()) {
    LOG(ERROR) << "Failed to serialize JSON: " << status;
    response.status = 500;
    return;
  }
  response.status = 200;
  response.set_content(json_output, "application/json");
}

void HandlerImpl::HandleLogin(const httplib::Request &request,
                              httplib::Response &response) {
  LoginRequest login_request;
  if (absl::Status status = JsonStringToMessage(request.body, &login_request);
      !status.ok()) {
    LOG(ERROR) << "Failed to parse JSON: " << status;
    response.status = 400;
    return;
  }

  LoginResponse login_response;
  if (login_request.code() == "123456") {
    login_response.set_success(true);
    login_response.set_message("Login Successful");
    response.status = 200;
  } else {
    login_response.set_success(false);
    login_response.set_message("Invalid code");
    response.status = 401;
  }

  std::string json_output;
  if (absl::Status status = MessageToJsonString(login_response, &json_output);
      !status.ok()) {
    LOG(ERROR) << "Failed to serialize JSON: " << status;
    response.status = 500;
    return;
  }
  response.set_content(json_output, "application/json");
}

} // namespace warehouse::ui
