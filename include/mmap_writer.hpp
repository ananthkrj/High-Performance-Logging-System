#pragma once

#include <string>
#include <cstddef>

namespace mmapwriter {
    class mmapWriter {
    public:
        int mmap_create(const std::string& filename, const std::string& message);
        int mmap_read(const std::string& filename);
        int mmap_update(const std::string& filename, const std::string& message);
    };
}