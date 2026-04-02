#ifndef LOG_H_
#define LOG_H_

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace musashi {

// TODO: change to ring buffer, and overall architecture of the static

class Logger {
 public:
  static void Initialize();

  static std::shared_ptr<spdlog::logger>& GetEngineLogger() {
    return engine_logger_;
  }
  static std::shared_ptr<spdlog::logger>& GetClientLogger() {
    return client_logger_;
  }

  static void EngineTrace(const std::string& msg) {
    GetEngineLogger()->trace(msg);
  }
  static void EngineDebug(const std::string& msg) {
    GetEngineLogger()->debug(msg);
  }
  static void EngineInfo(const std::string& msg) { engine_logger_->info(msg); }
  static void EngineWarning(const std::string& msg) {
    GetEngineLogger()->warn(msg);
  }
  static void EngineError(const std::string& msg) {
    GetEngineLogger()->error(msg);
  }
  static void EngineCritical(const std::string& msg) {
    GetEngineLogger()->critical(msg);
  }

  static void ClientTrace(const std::string& msg) {
    GetClientLogger()->trace(msg);
  }
  static void ClientDebug(const std::string& msg) {
    GetClientLogger()->debug(msg);
  }
  static void ClientInfo(const std::string& msg) { client_logger_->info(msg); }
  static void ClientWarning(const std::string& msg) {
    GetClientLogger()->warn(msg);
  }
  static void ClientError(const std::string& msg) {
    GetClientLogger()->error(msg);
  }
  static void ClientCritical(const std::string& msg) {
    GetClientLogger()->critical(msg);
  }

 private:
  static std::shared_ptr<spdlog::logger> engine_logger_;
  static std::shared_ptr<spdlog::logger> client_logger_;
};

}  // namespace musashi

#endif