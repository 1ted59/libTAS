/*
    Copyright 2015-2016 Clément Gallet <clement.gallet@ens-lyon.org>

    This file is part of libTAS.

    libTAS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libTAS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libTAS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "frame.h"
#include "../shared/tasflags.h"
#include "../shared/AllInputs.h"
#include "../shared/messages.h"
#include "inputs.h"
#include "socket.h"
#include "libTAS.h"
#include "logging.h"
#include "DeterministicTimer.h"
#include "windows.h" // gameWindow
#ifndef LIBTAS_DISABLE_AVDUMPING
#include "avdumping.h"
#endif

void frameBoundary(void)
{
    debuglog(LCF_TIMEFUNC | LCF_FRAME, "Enter frame boundary");

    detTimer.enterFrameBoundary();

    /* Audio mixing is done above, so encode must be called after */
#ifndef LIBTAS_DISABLE_AVDUMPING
    /* Dumping audio and video */
    if (tasflags.av_dumping) {
        /* Write the current frame */
        int enc = encodeOneFrame(frame_counter, gameWindow);
        if (enc != 0) {
            /* Encode failed, disable AV dumping */
            closeAVDumping();
            tasflags.av_dumping = 0;
        }
    }
#endif

    sendMessage(MSGB_START_FRAMEBOUNDARY);
    sendData(&frame_counter, sizeof(unsigned long));

    struct TasFlags oldflags = tasflags;
    proceed_commands();

    /* We don't update AllInputs old_ai here. We update during the generation of events */
    ++frame_counter;

    detTimer.exitFrameBoundary();
    debuglog(LCF_TIMEFUNC | LCF_FRAME, "Leave frame boundary");
}

void proceed_commands(void)
{
    int message;
    while (1)
    {
        receiveData(&message, sizeof(int));

        switch (message)
        {
            case MSGN_TASFLAGS:
                receiveData(&tasflags, sizeof(struct TasFlags));
                break;

            case MSGN_END_FRAMEBOUNDARY:
                return;

            case MSGN_ALL_INPUTS:
                receiveData(&ai, sizeof(struct AllInputs));
                break;

        }
    }
}
