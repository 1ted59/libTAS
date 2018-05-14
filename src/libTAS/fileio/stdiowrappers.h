/*
    Copyright 2015-2018 Clément Gallet <clement.gallet@ens-lyon.org>

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

#ifndef LIBTAS_STDIO_H_INCLUDED
#define LIBTAS_STDIO_H_INCLUDED

#ifdef LIBTAS_ENABLE_FILEIO_HOOKING

#include "../global.h"
#include <cstdio> // FILE

namespace libtas {

/* Check if oldf is a savefile and rename it. Returns true is renamed */
bool rename_stdio (const char *oldf, const char *newf);

/* Check if filename is a savefile and flag it as removed. Returns true is removed */
bool remove_stdio (const char *filename);

/* Open a file and create a new stream for it. */
OVERRIDE FILE *fopen (const char *filename, const char *modes);
OVERRIDE FILE *fopen64 (const char *filename, const char *modes);

/* Close STREAM. */
OVERRIDE int fclose (FILE *stream);

}

#endif
#endif
