
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2012 Francois Beaune, Jupiter Jazz Limited
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_SHARED_APPLICATION_APPLICATION_H
#define APPLESEED_SHARED_APPLICATION_APPLICATION_H

// boost headers.
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

// Forward declarations.
namespace foundation    { class Logger; }

//
// On Windows, define SHAREDDLL to __declspec(dllexport) when building the DLL
// and to __declspec(dllimport) when building an application using the DLL.
// Other platforms don't use this export mechanism and the symbol SHAREDDLL is
// defined to evaluate to nothing.
//

#ifndef SHAREDDLL
#ifdef _WIN32
#ifdef APPLESEED_SHARED_EXPORTS
#define SHAREDDLL __declspec(dllexport)
#else
#define SHAREDDLL __declspec(dllimport)
#endif
#else
#define SHAREDDLL
#endif
#endif

namespace appleseed {
namespace shared {

//
// The Application class gathers functionalities for checking if the application
// is correctly installed, finding out what is the application's root path, etc.
//

class SHAREDDLL Application
{
  public:
    // Return true if the application is correctly installed, false otherwise.
    // The application should print a message and exit if not correctly installed.
    static bool is_correctly_installed();

    // Check if the application is correctly installed, and issue a fatal error
    // message (through the provided foundation::Logger object) if it isn't.
    static void check_installation(foundation::Logger& logger);

    // Return the root path of the application.  The root path of an application
    // is the path to the parent of the bin/ subdirectory.  This method returns
    // an empty string if the application is not correctly installed.
    static const char* get_root_path();

    // Return the root path of the application's tests.
    static const char* get_tests_root_path();

    // Change the current directory to the root path of the application's tests.
    // Returns the path to the current directory.
    static boost::filesystem::path change_current_directory_to_tests_root_path();
};


//
// Application class implementation.
//

// Change the current directory to the root path of the application's tests.
inline boost::filesystem::path Application::change_current_directory_to_tests_root_path()
{
    using namespace boost;

    const filesystem::path old_current_path = filesystem::current_path();

    const filesystem::path tests_root_path(Application::get_tests_root_path());
    filesystem::current_path(tests_root_path);

    return old_current_path;
}

}       // namespace shared
}       // namespace appleseed

#endif  // !APPLESEED_SHARED_APPLICATION_APPLICATION_H
