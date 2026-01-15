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

} // namespace
} // namespace warehouse::ui
