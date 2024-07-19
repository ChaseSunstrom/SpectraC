//
// Created by chase on 7/8/24.
//

#ifndef SPECTRAC_RUN_HPP
#define SPECTRAC_RUN_HPP

#include "../pch.hpp"
#include "args.hpp"

namespace Spectra
{
    class Run
    {
    public:
        static void RunFiles(const std::vector<Args>& parsed_args);
        static void RunPrompt();
    };
}


#endif //SPECTRAC_RUN_HPP
