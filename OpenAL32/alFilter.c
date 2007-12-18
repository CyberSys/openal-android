/**
 * OpenAL cross platform audio library
 * Copyright (C) 1999-2007 by authors.
 * This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the
 *  Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 *  Boston, MA  02111-1307, USA.
 * Or go to http://www.gnu.org/copyleft/lgpl.html
 */

#include <stdlib.h>

#include "config.h"

#include "AL/al.h"
#include "AL/alc.h"

#include "alMain.h"
#include "alFilter.h"

static ALfilter *g_FilterList;
static ALuint    g_FilterCount;

static void InitFilterParams(ALfilter *filter, ALenum type);


AL_API ALvoid AL_APIENTRY alGenFilters(ALsizei n, ALuint *filters)
{
    ALCcontext *Context;
    ALsizei i;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (n > 0)
    {
        // Check that enough memory has been allocted in the 'sources' array for n Sources
        if (!IsBadWritePtr((void*)filters, n * sizeof(ALuint)))
        {
            ALfilter **list = &g_FilterList;
            while(*list)
                list = &(*list)->next;

            i = 0;
            while(i < n)
            {
                *list = calloc(1, sizeof(ALfilter));
                if(!(*list))
                {
                    // We must have run out or memory
                    alDeleteFilters(i, filters);
                    alSetError(AL_OUT_OF_MEMORY);
                    break;
                }

                filters[i] = (ALuint)ALTHUNK_ADDENTRY(*list);
                (*list)->filter = filters[i];

                InitFilterParams(*list, AL_FILTER_NULL);
                g_FilterCount++;
                i++;
            }
        }
    }

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alDeleteFilters(ALsizei n, ALuint *filters)
{
    ALCcontext *Context;
    ALfilter *ALFilter;
    ALsizei i;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (n >= 0)
    {
        // Check that all filters are valid
        for (i = 0; i < n; i++)
        {
            if (!alIsFilter(filters[i]))
            {
                alSetError(AL_INVALID_NAME);
                break;
            }
        }

        if (i == n)
        {
            // All filters are valid
            for (i = 0; i < n; i++)
            {
                // Recheck that the filter is valid, because there could be duplicated names
                if (filters[i] && alIsFilter(filters[i]))
                {
                    ALfilter **list;

                    ALFilter = ((ALfilter*)ALTHUNK_LOOKUPENTRY(filters[i]));

                    // Remove Source from list of Sources
                    list = &g_FilterList;
                    while(*list && *list != ALFilter)
                         list = &(*list)->next;

                    if(*list)
                        *list = (*list)->next;
                    ALTHUNK_REMOVEENTRY(ALFilter->filter);

                    memset(ALFilter, 0, sizeof(ALfilter));
                    free(ALFilter);

                    g_FilterCount--;
                }
            }
        }
    }
    else
        alSetError(AL_INVALID_VALUE);

    ProcessContext(Context);
}

AL_API ALboolean AL_APIENTRY alIsFilter(ALuint filter)
{
    ALCcontext *Context;
    ALfilter **list;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    list = &g_FilterList;
    while(*list && (*list)->filter != filter)
        list = &(*list)->next;

    ProcessContext(Context);

    return ((*list || !filter) ? AL_TRUE : AL_FALSE);
}

AL_API ALvoid AL_APIENTRY alFilteri(ALuint filter, ALenum param, ALint iValue)
{
    ALCcontext *Context;

    (void)iValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alFilteriv(ALuint filter, ALenum param, ALint *piValues)
{
    ALCcontext *Context;

    (void)piValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alFilterf(ALuint filter, ALenum param, ALfloat flValue)
{
    ALCcontext *Context;

    (void)flValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alFilterfv(ALuint filter, ALenum param, ALfloat *pflValues)
{
    ALCcontext *Context;

    (void)pflValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alGetFilteri(ALuint filter, ALenum param, ALint *piValue)
{
    ALCcontext *Context;

    (void)piValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alGetFilteriv(ALuint filter, ALenum param, ALint *piValues)
{
    ALCcontext *Context;

    (void)piValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alGetFilterf(ALuint filter, ALenum param, ALfloat *pflValue)
{
    ALCcontext *Context;

    (void)pflValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alGetFilterfv(ALuint filter, ALenum param, ALfloat *pflValues)
{
    ALCcontext *Context;

    (void)pflValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsFilter(filter))
    {
        switch(param)
        {
        default:
            alSetError(AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(AL_INVALID_NAME);

    ProcessContext(Context);
}


ALvoid ReleaseALFilters(ALvoid)
{
#ifdef _DEBUG
    if(g_FilterCount > 0)
        AL_PRINT("exit() %d Filter(s) NOT deleted\n", g_FilterCount);
#endif

    while(g_FilterList)
    {
        ALfilter *temp = g_FilterList;
        g_FilterList = g_FilterList->next;

        // Release filter structure
        memset(temp, 0, sizeof(ALfilter));
        free(temp);
    }
    g_FilterCount = 0;
}


static void InitFilterParams(ALfilter *filter, ALenum type)
{
    filter->type = type;
}