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
#include "alAuxEffectSlot.h"

static ALeffectslot *g_AuxiliaryEffectSlotList;
static ALuint        g_AuxiliaryEffectSlotCount;


AL_API ALvoid AL_APIENTRY alGenAuxiliaryEffectSlots(ALsizei n, ALuint *effectslots)
{
    ALCcontext *Context;
    ALsizei i;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (n > 0)
    {
        // Check that enough memory has been allocted in the 'sources' array for n Sources
        if (!IsBadWritePtr((void*)effectslots, n * sizeof(ALuint)))
        {
            ALeffectslot **list = &g_AuxiliaryEffectSlotList;
            while(*list)
                list = &(*list)->next;

            i = 0;
            while(i < n)
            {
                *list = calloc(1, sizeof(ALeffectslot));
                if(!(*list))
                {
                    // We must have run out or memory
                    alDeleteAuxiliaryEffectSlots(i, effectslots);
                    alSetError(AL_OUT_OF_MEMORY);
                    break;
                }

                effectslots[i] = (ALuint)ALTHUNK_ADDENTRY(*list);
                (*list)->effectslot = effectslots[i];

                g_AuxiliaryEffectSlotCount++;
                i++;
            }
        }
    }

    ProcessContext(Context);
}

AL_API ALvoid AL_APIENTRY alDeleteAuxiliaryEffectSlots(ALsizei n, ALuint *effectslots)
{
    ALCcontext *Context;
    ALeffectslot *ALAuxiliaryEffectSlot;
    ALsizei i;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (n >= 0)
    {
        // Check that all effectslots are valid
        for (i = 0; i < n; i++)
        {
            if (!alIsAuxiliaryEffectSlot(effectslots[i]))
            {
                alSetError(AL_INVALID_NAME);
                break;
            }
        }

        if (i == n)
        {
            // All effectslots are valid
            for (i = 0; i < n; i++)
            {
                // Recheck that the effectslot is valid, because there could be duplicated names
                if (alIsAuxiliaryEffectSlot(effectslots[i]))
                {
                    ALeffectslot **list;

                    ALAuxiliaryEffectSlot = ((ALeffectslot*)ALTHUNK_LOOKUPENTRY(effectslots[i]));

                    // Remove Source from list of Sources
                    list = &g_AuxiliaryEffectSlotList;
                    while(*list && *list != ALAuxiliaryEffectSlot)
                         list = &(*list)->next;

                    if(*list)
                        *list = (*list)->next;
                    ALTHUNK_REMOVEENTRY(ALAuxiliaryEffectSlot->effectslot);

                    memset(ALAuxiliaryEffectSlot, 0, sizeof(ALeffectslot));
                    free(ALAuxiliaryEffectSlot);

                    g_AuxiliaryEffectSlotCount--;
                }
            }
        }
    }
    else
        alSetError(AL_INVALID_VALUE);

    ProcessContext(Context);
}

AL_API ALboolean AL_APIENTRY alIsAuxiliaryEffectSlot(ALuint effectslot)
{
    ALCcontext *Context;
    ALeffectslot **list;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    list = &g_AuxiliaryEffectSlotList;
    while(*list && (*list)->effectslot != effectslot)
        list = &(*list)->next;

    ProcessContext(Context);

    return (*list ? AL_TRUE : AL_FALSE);
}

AL_API ALvoid AL_APIENTRY alAuxiliaryEffectSloti(ALuint effectslot, ALenum param, ALint iValue)
{
    ALCcontext *Context;

    (void)iValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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

AL_API ALvoid AL_APIENTRY alAuxiliaryEffectSlotiv(ALuint effectslot, ALenum param, ALint *piValues)
{
    ALCcontext *Context;

    (void)piValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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

AL_API ALvoid AL_APIENTRY alAuxiliaryEffectSlotf(ALuint effectslot, ALenum param, ALfloat flValue)
{
    ALCcontext *Context;

    (void)flValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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

AL_API ALvoid AL_APIENTRY alAuxiliaryEffectSlotfv(ALuint effectslot, ALenum param, ALfloat *pflValues)
{
    ALCcontext *Context;

    (void)pflValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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

AL_API ALvoid AL_APIENTRY alGetAuxiliaryEffectSloti(ALuint effectslot, ALenum param, ALint *piValue)
{
    ALCcontext *Context;

    (void)piValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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

AL_API ALvoid AL_APIENTRY alGetAuxiliaryEffectSlotiv(ALuint effectslot, ALenum param, ALint *piValues)
{
    ALCcontext *Context;

    (void)piValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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

AL_API ALvoid AL_APIENTRY alGetAuxiliaryEffectSlotf(ALuint effectslot, ALenum param, ALfloat *pflValue)
{
    ALCcontext *Context;

    (void)pflValue;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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

AL_API ALvoid AL_APIENTRY alGetAuxiliaryEffectSlotfv(ALuint effectslot, ALenum param, ALfloat *pflValues)
{
    ALCcontext *Context;

    (void)pflValues;

    Context = alcGetCurrentContext();
    SuspendContext(Context);

    if (alIsAuxiliaryEffectSlot(effectslot))
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


ALvoid ReleaseALAuxiliaryEffectSlots(ALvoid)
{
#ifdef _DEBUG
    if(g_AuxiliaryEffectSlotCount > 0)
        AL_PRINT("exit() %d AuxiliaryEffectSlot(s) NOT deleted\n", g_AuxiliaryEffectSlotCount);
#endif

    while(g_AuxiliaryEffectSlotList)
    {
        ALeffectslot *temp = g_AuxiliaryEffectSlotList;
        g_AuxiliaryEffectSlotList = g_AuxiliaryEffectSlotList->next;

        // Release effectslot structure
        memset(temp, 0, sizeof(ALeffectslot));
        free(temp);
    }
    g_AuxiliaryEffectSlotCount = 0;
}