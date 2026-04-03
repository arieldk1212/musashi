#ifndef LOG_H_
#define LOG_H_

#include <chrono>
#include <print>
#include <vector>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace musashi {

// TODO: change to ring buffer, and overall architecture of the static

#ifdef __cpp_lib_hardware_interference_size
static constexpr size_t kCacheLineSize =
    std::hardware_destructive_interference_size;
#else
static constexpr size_t kCacheLineSize = 64;
#endif

class Logger {
 public:
  enum class LogLevel : uint8_t { kTrace, kDebug, kWarning, kError, kCritical };

  explicit Logger(size_t capacity = 256)
      : capacity_(capacity) {
    buffer_.resize(capacity_);
  }
  ~Logger() = default;

  struct LogRecord {
    explicit LogRecord(LogLevel level)
        : level(level) {
      timestamp = std::chrono::time_point_cast<std::chrono::seconds>(
          std::chrono::system_clock::now());
    }
    std::string msg;
    LogLevel level{LogLevel::kTrace};
    std::chrono::system_clock::time_point timestamp;

    void PrintLog() const {
      std::string level_str{"TRACE"};
      switch (level) {
        case LogLevel::kTrace:
          level_str = "TRACE";
          break;
        case LogLevel::kDebug:
          level_str = "DEBUG";
          break;
        case LogLevel::kWarning:
          level_str = "WARNING";
          break;
        case LogLevel::kError:
          level_str = "ERROR";
          break;
        case LogLevel::kCritical:
          level_str = "CRITICAL";
          break;
      }
      std::println("[{:%F %T}] [{}] {}", timestamp, level_str, msg);
    }
  };

  void Log() {}  // TODO: implement this

 private:
  size_t capacity_;
  alignas(kCacheLineSize) std::vector<LogRecord> buffer_;
  alignas(kCacheLineSize) std::atomic<size_t> head_{0};
  alignas(kCacheLineSize) std::atomic<size_t> tail_{0};
};

// class Logger {
//  public:
//   static void Initialize();

//   static std::shared_ptr<spdlog::logger>& GetEngineLogger() {
//     return engine_logger_;
//   }
//   static std::shared_ptr<spdlog::logger>& GetClientLogger() {
//     return client_logger_;
//   }

//   static void EngineTrace(const std::string& msg) {
//     GetEngineLogger()->trace(msg);
//   }
//   static void EngineDebug(const std::string& msg) {
//     GetEngineLogger()->debug(msg);
//   }
//   static void EngineInfo(const std::string& msg) { engine_logger_->info(msg);
//   } static void EngineWarning(const std::string& msg) {
//     GetEngineLogger()->warn(msg);
//   }
//   static void EngineError(const std::string& msg) {
//     GetEngineLogger()->error(msg);
//   }
//   static void EngineCritical(const std::string& msg) {
//     GetEngineLogger()->critical(msg);
//   }

//   static void ClientTrace(const std::string& msg) {
//     GetClientLogger()->trace(msg);
//   }
//   static void ClientDebug(const std::string& msg) {
//     GetClientLogger()->debug(msg);
//   }
//   static void ClientInfo(const std::string& msg) { client_logger_->info(msg);
//   } static void ClientWarning(const std::string& msg) {
//     GetClientLogger()->warn(msg);
//   }
//   static void ClientError(const std::string& msg) {
//     GetClientLogger()->error(msg);
//   }
//   static void ClientCritical(const std::string& msg) {
//     GetClientLogger()->critical(msg);
//   }

//  private:
//   static std::shared_ptr<spdlog::logger> engine_logger_;
//   static std::shared_ptr<spdlog::logger> client_logger_;
// };

}  // namespace musashi

#endif
