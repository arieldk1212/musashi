#include "log.h"

namespace musashi {

std::shared_ptr<spdlog::logger> Logger::engine_logger_;
std::shared_ptr<spdlog::logger> Logger::client_logger_;

void Logger::Initialize() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  engine_logger_ = spdlog::stdout_color_mt("ENGINE");
  client_logger_ = spdlog::stderr_color_mt("CLIENT");
  engine_logger_->set_level(spdlog::level::trace);
  client_logger_->set_level(spdlog::level::trace);
}

}  // namespace musashi