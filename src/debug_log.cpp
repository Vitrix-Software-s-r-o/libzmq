//
// Created by Jan Hruby on 02.08.2025.
//

#pragma once

#include "debug_log.hpp"
#include <fstream>
#include <memory>

debug_log::debug_log ()
{
    auto log_file = std::getenv ("ZMQ_DEBUG_LOG_FILE");
    if (log_file && *log_file) {
        stream_ = std::unique_ptr<std::ofstream>(new std::ofstream(log_file, std::ios::app));
        if (!stream_) {
            stream_.reset();
        }
    }
}

debug_log &debug_log::instance ()
{
    static debug_log log;
    return log;
}
debug_log::~debug_log ()
{
}

