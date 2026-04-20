#include "log.h"

#include <chrono>
#include <print>

namespace musashi {

LogRecord::LogRecord(LogLevel level, std::string msg)
    : msg(std::move(msg)),
      level(level) {
  timestamp = std::chrono::time_point_cast<std::chrono::seconds>(
      std::chrono::system_clock::now());
}

void LogRecord::PrintLog() const {
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
  // TODO: Change to:
  // TODO: [LEVEL][file:line][function_name][msg_tag] msg
  std::println("[{:%F %T}] [{}] {}", timestamp, level_str, msg);
}

LogRingBuffer::LogRingBuffer(size_t capacity)
    : capacity_(capacity) {
  buffer_.resize(capacity);
}

bool LogRingBuffer::Pop(LogRecord& log) {
  auto curr_head = head_.load(std::memory_order_relaxed);

  if (tail_.load(std::memory_order_acquire) == curr_head) {
    return false;
  }
  log = std::move(buffer_[curr_head]);
  head_.store((curr_head + 1) % capacity_, std::memory_order_release);
  return true;
}

bool LogRingBuffer::Push(const LogRecord& log) {
  auto curr_tail = tail_.load(std::memory_order_relaxed);
  auto next_tail = (curr_tail + 1) % capacity_;

  if (next_tail == head_.load(std::memory_order_acquire)) {
    return false;
  }
  buffer_[curr_tail] = log;
  tail_.store(next_tail, std::memory_order_release);
  return true;
}

Logger::Logger(size_t capacity)
    : buffer_(capacity),
      running_(true) {
  thread_ = std::thread(&Logger::Run, this);
}
Logger::~Logger() {
  running_.store(false, std::memory_order_release);
  if (thread_.joinable()) {
    thread_.join();
  }

  LogRecord log;
  while (buffer_.Pop(log)) {
    log.PrintLog();
  }
}

bool Logger::Log(LogLevel level, std::string msg) {
  if (!running_.load(std::memory_order_acquire)) {
    return false;
  }
  LogRecord log(level, std::move(msg));
  return buffer_.Push(log);
}

void Logger::Run() {
  LogRecord log;
  while (running_.load(std::memory_order_acquire)) {
    if (buffer_.Pop(log)) {
      log.PrintLog();
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
}

}  // namespace musashi
