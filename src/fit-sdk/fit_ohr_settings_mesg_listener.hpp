////////////////////////////////////////////////////////////////////////////////
// The following FIT Protocol software provided may be used with FIT protocol
// devices only and remains the copyrighted property of Garmin Canada Inc.
// The software is being provided on an "as-is" basis and as an accommodation,
// and therefore all warranties, representations, or guarantees of any kind
// (whether express, implied or statutory) including, without limitation,
// warranties of merchantability, non-infringement, or fitness for a particular
// purpose, are specifically disclaimed.
//
// Copyright 2020 Garmin Canada Inc.
////////////////////////////////////////////////////////////////////////////////
// ****WARNING****  This file is auto-generated!  Do NOT edit this file.
// Profile Version = 21.40Release
// Tag = production/akw/21.40.00-0-g813c158
////////////////////////////////////////////////////////////////////////////////


#if !defined(FIT_OHR_SETTINGS_MESG_LISTENER_HPP)
#define FIT_OHR_SETTINGS_MESG_LISTENER_HPP

#include "fit_ohr_settings_mesg.hpp"

namespace fit
{

class OhrSettingsMesgListener
{
public:
    virtual ~OhrSettingsMesgListener() {}
    virtual void OnMesg(OhrSettingsMesg& mesg) = 0;
};

} // namespace fit

#endif // !defined(FIT_OHR_SETTINGS_MESG_LISTENER_HPP)
