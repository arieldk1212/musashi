#ifndef LOG_H_
#define LOG_H_

#include <atomic>
#include <new>
#include <thread>
#include <vector>

namespace musashi {

#ifdef __cpp_lib_hardware_interference_size
static constexpr size_t kCacheLineSize =
    std::hardware_destructive_interference_size;
#else
static constexpr size_t kCacheLineSize = 64;
#endif

static constexpr int kLogBufferSize{512};

enum class LogLevel : uint8_t { kTrace, kDebug, kWarning, kError, kCritical };

struct LogRecord {
  LogRecord() = default;
  explicit LogRecord(LogLevel level, std::string msg);

  void PrintLog() const;

  std::string msg;
  LogLevel level{LogLevel::kTrace};
  std::chrono::sys_seconds timestamp;
};

class LogRingBuffer {
 public:
  explicit LogRingBuffer(size_t capacity = kLogBufferSize);

  bool Pop(LogRecord& log);
  bool Push(const LogRecord& log);

 private:
  size_t capacity_;
  alignas(kCacheLineSize) std::atomic<size_t> head_{0};
  alignas(kCacheLineSize) std::atomic<size_t> tail_{0};
  alignas(kCacheLineSize) std::vector<LogRecord> buffer_;
};

// TODO: Use fflush instead of std::println
// TODO: Add codition variable instead of sleep
class Logger {
 public:
  explicit Logger(size_t capacity = kLogBufferSize);
  ~Logger();

  void Trace(std::string msg) { Log(LogLevel::kTrace, std::move(msg)); }
  void Debug(std::string msg) { Log(LogLevel::kDebug, std::move(msg)); }
  void Warning(std::string msg) { Log(LogLevel::kWarning, std::move(msg)); }
  void Error(std::string msg) { Log(LogLevel::kError, std::move(msg)); }
  void Critical(std::string msg) { Log(LogLevel::kCritical, std::move(msg)); }

 private:
  bool Log(LogLevel level, std::string msg);

  void Run();

  std::thread thread_;
  LogRingBuffer buffer_;
  std::atomic<bool> running_;
};

}  // namespace musashi

#endif
