
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

// Interface header.
#include "statusbar.h"

// appleseed.foundation headers.
#include "foundation/utility/string.h"

using namespace foundation;
using namespace std;

namespace appleseed {
namespace studio {

//
// StatusBar class implementation.
//

StatusBar::StatusBar()
  : m_rendering_timer(0)
  , m_timer_id(-1)
{
}

void StatusBar::set_text(const string& text)
{
    setText(QString::fromStdString(text));
}

void StatusBar::start_rendering_time_display(RenderingTimer* rendering_timer)
{
    assert(m_rendering_timer == 0);
    assert(m_timer_id == -1);

    assert(rendering_timer);

    m_rendering_timer = rendering_timer;
    m_timer_id = startTimer(1000 / 4);
}

void StatusBar::stop_rendering_time_display()
{
    assert(m_rendering_timer != 0);
    assert(m_timer_id != -1);

    killTimer(m_timer_id);

    m_rendering_timer = 0;
    m_timer_id = -1;
}

void StatusBar::timerEvent(QTimerEvent* event)
{
    assert(m_rendering_timer);

    m_rendering_timer->measure();

    const double rendering_time = m_rendering_timer->get_seconds();
    const string rendering_time_string = pretty_time(rendering_time, 0);

    set_text("Rendering time: " + rendering_time_string);
}

}   // namespace studio
}   // namespace appleseed
