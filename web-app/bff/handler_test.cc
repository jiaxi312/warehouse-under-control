#include "web-app/bff/handler.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace warehouse::ui {
namespace {

using ::testing::Eq;
using ::testing::HasSubstr;

TEST(HandlerTest, GreetInvalidJson) {
  HandlerImpl handler;
  httplib::Request request;
  request.body = "{";
  httplib::Response response;

  handler.HandleGreet(request, response);

  EXPECT_THAT(response.status, Eq(404));
}

TEST(HandlerTest, GreetEmptyName) {
  HandlerImpl handler;
  httplib::Request request;
  request.body = R"({"name": ""})";
  httplib::Response response;

  handler.HandleGreet(request, response);

  ASSERT_THAT(response.status, Eq(200));
  EXPECT_THAT(response.body, HasSubstr("Hello "));
}

TEST(HandlerTest, Greet) {
  HandlerImpl handler;
  httplib::Request request;
  request.body = R"({"name": "World"})";
  httplib::Response response;

  handler.HandleGreet(request, response);

  ASSERT_THAT(response.status, Eq(200));
  EXPECT_THAT(response.body, HasSubstr("Hello World"));
}

TEST(HandleLogin, LoginInvalidJson) {
  HandlerImpl handler;
  httplib::Request request;
  request.body = "invalid json";
  httplib::Response response;

  handler.HandleLogin(request, response);

  EXPECT_THAT(response.status, Eq(400));
}

TEST(HandleLogin, LoginInvalidCode) {
  HandlerImpl handler;
  httplib::Request request;
  request.body = R"({"code": "invalid code"})";
  httplib::Response response;

  handler.HandleLogin(request, response);

  EXPECT_THAT(response.status, Eq(401));
}

TEST(HandleLogin, LoginSuccess) {
  HandlerImpl handler;
  httplib::Request request;
  request.body = R"({"code": "123456"})";
  httplib::Response response;

  handler.HandleLogin(request, response);

  EXPECT_THAT(response.status, Eq(200));
}

} // namespace
} // namespace warehouse::ui
