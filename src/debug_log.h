//
// Created by Jan Hruby on 02.08.2025.
//

#pragma once
#include <iomanip>
#include <ostream>
#include <mutex>

class debug_log {
public:
    static debug_log& instance();
    ~debug_log();

    template <typename... Args>
    void log(Args const&... args) {
        if (stream_) {
            auto lock = std::unique_lock<std::mutex>(mutex_);
            auto & stream = *stream_;

            // print timestamp as an iso format
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            stream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S") << " ";

            (( (stream) << " " << args ), ...);
            (stream) << std::endl;
        }
    }
private:
    debug_log();
    std::mutex mutex_;
    std::unique_ptr<std::ostream> stream_;

};
