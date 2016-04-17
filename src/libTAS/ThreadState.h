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

/* We want to store the state of each thread somewhere,
 * to be able to differentiate if some code is being called by the game
 * or by our own program.
 *
 * Indeed, if we use some library that eventually call a function that we hooked,
 * we don't want to process that call in the same way as if the game called that
 * function itself.
 *
 * This is also necessary to avoid some recursive loops.
 * For example, the logging function calls fwrite at some point,
 * so printing a log message inside the hooked fwrite function leads to a loop.
 *
 * This state is different for each thread, so we have to declare an instance
 * using c++11 thread_local.
 */

#ifndef LIBTAS_THREADSTATE_H_INCLUDED
#define LIBTAS_THREADSTATE_H_INCLUDED

class ThreadState
{
    public:
        /* Add or remove the NATIVE, OWNCODE and NOLOG flags.
         * This function and all other set* functions have a call count,
         * meaning we must call set*(false) by the same number as set*(true)
         * to disable the flag */
        void setNative(bool state);

        /* Check the NATIVE flag */
        bool isNative(void);

        /* Add or remove the OWNCODE and NOLOG flags. */
        void setOwnCode(bool state);
        /* Check the OWNCODE flag */
        bool isOwnCode(void);

        /* Add or remove the NOLOG flag. */
        void setNoLog(bool state);
        /* Check the NOLOG flag */
        bool isNoLog(void);

    private:

        /* State flags that compose the state of the thread.
         * flags are tested in descending order: NATIVE -> OWNCODE -> NOLOG
         */
        enum {
            /* When NATIVE flag is on, we ask each hooked function to act
             * as closely as possible as the real function. This disable 
             * any log message, side effects, etc.
             */
            NATIVE = 0x01,

            /* When OWNCODE flag is on, we indicate each hooked function that
             * the caller was our own code and not the game code. This usually
             * make the code closer to the original function, although it is not
             * as strong as NATIVE.
             */
            OWNCODE = 0x02,

            /* When NOLOG flag is on, we ask each hooked function to not generate
             * any log message.
             */
            NOLOG  = 0x04
        };

        int stateMask = 0;
};

extern thread_local ThreadState threadState;

#endif

