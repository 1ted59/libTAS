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

#include "isteamuser.h"
#include "../logging.h"

namespace libtas {

HSteamUser ISteamUser::GetHSteamUser()
{
    DEBUGLOGCALL(LCF_STEAM);
	return 1;
}

bool ISteamUser::BLoggedOn()
{
    DEBUGLOGCALL(LCF_STEAM);
	return false;
}

CSteamID ISteamUser::GetSteamID()
{
    DEBUGLOGCALL(LCF_STEAM);
    return 1;
}

}
