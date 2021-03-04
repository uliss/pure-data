/*****************************************************************************
 * Copyright 2021 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "config.h"
#include "tcl2cxx_lexer.h"

#ifdef HAVE_LIBGEN_H
#include <libgen.h>
#endif

static std::string mybasename(const std::string& name)
{
#ifdef HAVE_LIBGEN_H
    char buf[name.length() + 1];
    strcpy(buf, name.c_str());
    return basename(buf);
#endif
}

static std::string guard_name(const std::string& name)
{
    std::string lc_name(mybasename(name));
    for (auto& ch : lc_name) {
        if (ch == '.')
            ch = '_';
        else if (!std::isalnum(ch))
            continue;
        else
            ch = std::tolower(ch);
    }

    return std::string("__") + lc_name + "_h";
}

static std::string fn_name(const std::string& name)
{
    std::string lc_name(mybasename(name));
    for (auto& ch : lc_name) {
        if (ch == '.')
            ch = '_';
        else if (!std::isalnum(ch))
            continue;
        else
            ch = std::tolower(ch);
    }

    return lc_name + "_output";
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " FILENAME" << std::endl;
        return EXIT_FAILURE;
    }

    std::string fname(argv[1]);
    std::ifstream ifs(fname.c_str(), std::ios_base::binary);
    if (!ifs) {
        std::cerr << "can't open file \"" << fname << "\"" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "# this is autogenerated file, do not edit manually!\n";
    std::cout << "#include \"m_pd.h\"\n";
    std::cout << "#ifndef " << guard_name(fname) << "\n";
    std::cout << "#define " << guard_name(fname) << "\n";
    std::cout << "namespace {\n";
    std::cout << "void " << fn_name(fname) << "() {\n";

    tcl2cxx_lexer l;
    l.lex(ifs);
    std::cout << "}\n}\n";
    std::cout << "#endif // " << guard_name(fname) << "\n";
    return EXIT_SUCCESS;
}
