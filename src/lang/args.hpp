//
// Created by chase on 7/8/24.
//

#ifndef SPECTRAC_ARGS_HPP
#define SPECTRAC_ARGS_HPP

#include "../pch.hpp"

namespace Spectra
{
    class Args
    {
    public:

        Args(const std::fs::path& path, const std::vector<std::string>& args)
            : m_path(path), m_args(args) {}

        [[nodiscard]] const std::fs::path& GetPath() const { return m_path; }
        [[nodiscard]] const std::vector<std::string>& GetArgs() const { return m_args; }

    private:
        std::fs::path m_path;
        std::vector<std::string> m_args;
    };
}

#endif //SPECTRAC_ARGS_HPP
