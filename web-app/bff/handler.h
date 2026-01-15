#include "httplib.h"

namespace warehouse::ui {

class Handler {
public:
  explicit Handler() = default;

  virtual ~Handler() = default;

  virtual void HandleGreet(const httplib::Request &request,
                           httplib::Response &response) = 0;

  virtual void HandleLogin(const httplib::Request &request,
                           httplib::Response &response) = 0;
};

class HandlerImpl : public Handler {
public:
  explicit HandlerImpl() = default;

  void HandleGreet(const httplib::Request &request,
                   httplib::Response &response) override;

  void HandleLogin(const httplib::Request &request,
                   httplib::Response &response) override;
};

} // namespace warehouse::ui
