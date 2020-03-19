#include "stdafx.h"
#include <dmusicc.h>               // DirectMusic includes
#include <dmusici.h>
#include <d3d8types.h>             // for D3DVECTOR
#include <cguid.h>                 // for GUID_NULL

#include "audiosystem.h"

////// The CAudio implementation

void CAudio::Set3DBuffer(IDirectSound3DBuffer *dsBuff)
{
	ds3DBuffer = dsBuff;
}

void CAudio::Set3DPos(float x, float y, float z)
{
	ds3DBuffer->SetPosition(x, y, -z, DS3D_IMMEDIATE);
}

void CAudio::Set3DParams(float minDistance, float maxDistance)
{
	DS3DBUFFER dsBufferParams;
	
     // set minimum and maximum distances
     dsBufferParams.flMinDistance = minDistance;
     dsBufferParams.flMaxDistance = maxDistance;

     if (ds3DBuffer)
          ds3DBuffer->SetAllParameters(&dsBufferParams, DS3D_IMMEDIATE);
}

////// The CAudioSystem implementation

// constructor
CAudioSystem::CAudioSystem()
{
	dmusic3DAudioPath = NULL;
	dmusicLoader = NULL;
	dmusicPerformance = NULL;
	ds3DListener = NULL;
}

// destructor
CAudioSystem::~CAudioSystem()
{
	if (dmusic3DAudioPath)
		dmusic3DAudioPath->Release();

	if (dmusicPerformance)
		dmusicPerformance->Release();

	if (dmusicLoader)
		dmusicLoader->Release();
}

// InitDirectXAudio()
// desc: initialize the audio system
bool CAudioSystem::InitDirectXAudio(HWND hwnd)
{
	char pathStr[MAX_PATH];		// path for audio file
	WCHAR wcharStr[MAX_PATH];

	// create the loader object
	if (FAILED(CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
						   IID_IDirectMusicLoader8, (void**)&dmusicLoader)))
	{
		MessageBox(hwnd, "Unable to create the IDirectMusicLoader8 object!\nPress OK to exit",
				 "ERROR!", MB_OK);
		return false;
	}

	// create the performance object
	if (FAILED(CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
						   IID_IDirectMusicPerformance8, (void**)&dmusicPerformance)))
	{
		MessageBox(hwnd, "Unable to create the IDirectMusicPerformance8 object!\nPress OK to exit",
				 "ERROR!", MB_OK);
		return false;
	}

	// initialize the performance with the standard audio path
	dmusicPerformance->InitAudio(NULL, NULL, hwnd, DMUS_APATH_SHARED_STEREOPLUSREVERB, 64,
						    DMUS_AUDIOF_ALL, NULL);

     // create a standard 3D audiopath
     if (FAILED(dmusicPerformance->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_3D,
                                                           64, TRUE, &dmusic3DAudioPath)))
     {
          MessageBox(hwnd, "Unable to create standard 3D audiopath! Press OK to exit",
                     "ERROR!", MB_OK);
          return false;
     }

     // retrieve the listener from the audiopath
     if (FAILED(dmusic3DAudioPath->GetObjectInPath(0, DMUS_PATH_PRIMARY_BUFFER, 0, GUID_NULL, 0, 
                                                  IID_IDirectSound3DListener8,
                                                  (void**)&ds3DListener)))
     {
          MessageBox(hwnd, "Unable to retrieve the listener! Press OK to exit",
                     "ERROR!", MB_OK);
          return false;
     }

     // get the listener parameters
     dsListenerParams.dwSize = sizeof(DS3DLISTENER);
     ds3DListener->GetAllParameters(&dsListenerParams);

     // set position of listener
     dsListenerParams.vPosition.x = 0.0f;
     dsListenerParams.vPosition.y = 0.0f;
     dsListenerParams.vPosition.z = 0.0f;
     ds3DListener->SetAllParameters(&dsListenerParams, DS3D_IMMEDIATE);

	// retrieve the current directory
	GetCurrentDirectory(MAX_PATH, pathStr);

	// convert to unicode string
	MultiByteToWideChar(CP_ACP, 0, pathStr, -1, wcharStr, MAX_PATH);

	// set the search directory
	dmusicLoader->SetSearchDirectory(GUID_DirectMusicAllTypes, wcharStr, FALSE);

	return true;
}

// Shutdown()
// desc: shutdown the audio system
void CAudioSystem::Shutdown()
{
	// stop the music
	dmusicPerformance->Stop(NULL, NULL, 0, 0);

	// close down DirectMusic
	dmusicPerformance->CloseDown();
}

// PlaySegment()
// desc: play a segment
void CAudioSystem::PlaySegment(IDirectMusicSegment8 *dmSeg, bool is3DSound, DWORD numRepeats)
{
     // set the number of repeats
     dmSeg->SetRepeats(numRepeats);//DMUS_SEG_REPEAT_INFINITE);

	if (!is3DSound)
		// download the segment's instruments to the audiopath
		dmSeg->Download(dmusicPerformance);
	else
	{
		dmSeg->Download(dmusic3DAudioPath);

		// play the segment on the next beat using the 3d audio path
		dmusicPerformance->PlaySegmentEx(dmSeg, NULL, NULL, DMUS_SEGF_DEFAULT, 0,
                           NULL, NULL, dmusic3DAudioPath);
	}
}

// Play()
// desc: play a CAudio object
void CAudioSystem::Play(CAudio *audio, DWORD numRepeats)
{
	// set number of repeats
	audio->GetSegment()->SetRepeats(numRepeats);
	
	if (audio->Is3DSound())
	{
		audio->GetSegment()->Download(dmusic3DAudioPath);

		// play the segment on the next beat using the 3d audio path
		dmusicPerformance->PlaySegmentEx(audio->GetSegment(), NULL, NULL, DMUS_SEGF_SECONDARY, 0,
                           NULL, NULL, dmusic3DAudioPath);
	}
	else
	{
		audio->GetSegment()->Download(dmusicPerformance);
		// play the segment on the next beat using the 3d audio path
		dmusicPerformance->PlaySegmentEx(audio->GetSegment(), NULL, NULL, DMUS_SEGF_DEFAULT, 0,
                           NULL, NULL, NULL);
	}
}

// Stop()
// desc: stop a CAudio object from playing
void CAudioSystem::Stop(CAudio *audio)
{
	dmusicPerformance->StopEx(audio->GetSegment(), 0, 0);
}

// StopSegment()
// desc: stop a segment from playing
void CAudioSystem::StopSegment(IDirectMusicSegment8 *dmSeg)
{
	// stop the dmSeg from playing
	dmusicPerformance->StopEx(dmSeg, 0, 0);
}

// SetListenerPos()
// desc: set the listener position
void CAudioSystem::SetListenerPos(float cameraX, float cameraY, float cameraZ)
{
     // set the listener position
	//ds3DListener->SetPosition(cameraX, cameraY, -cameraZ, DS3D_IMMEDIATE);	
	// get the listener parameters
     dsListenerParams.dwSize = sizeof(DS3DLISTENER);
     ds3DListener->GetAllParameters(&dsListenerParams);

     // set position of listener
     dsListenerParams.vPosition.x = cameraX;
     dsListenerParams.vPosition.y = cameraY;
     dsListenerParams.vPosition.z = -cameraZ;
     ds3DListener->SetAllParameters(&dsListenerParams, DS3D_IMMEDIATE);
}

// SetListenerRolloff()
// desc: set the listener rolloff
void CAudioSystem::SetListenerRolloff(float rolloff)
{
	if (ds3DListener)
		ds3DListener->SetRolloffFactor(rolloff, DS3D_IMMEDIATE);
}

// Create3DBuffer()
// desc: create a DX Audio 3D buffer
IDirectSound3DBuffer *CAudioSystem::Create3DBuffer()
{
	IDirectSound3DBuffer *buff;
	DS3DBUFFER dsBufferParams;          // 3d buffer properties

     // get the 3D buffer in the audiopath
     if (FAILED(dmusic3DAudioPath->GetObjectInPath(DMUS_PCHANNEL_ALL, DMUS_PATH_BUFFER, 0, GUID_NULL, 0,
                                                   IID_IDirectSound3DBuffer,
                                                   (void**)&buff)))
     {
          MessageBox(NULL, "Unable to retrieve 3D buffer from audiopath! Press OK to exit",
                     "ERROR!", MB_OK);
          return NULL;
     }

     // get the 3D buffer parameters
     dsBufferParams.dwSize = sizeof(DS3DBUFFER);
     buff->GetAllParameters(&dsBufferParams);

     // set the new 3D buffer parameters
     dsBufferParams.dwMode = DS3DMODE_HEADRELATIVE;    // relative to the listener
     buff->SetAllParameters(&dsBufferParams, DS3D_IMMEDIATE);

	return buff;
}

// CreateSegment()
// desc: create a DX Audio segment
IDirectMusicSegment8 *CAudioSystem::CreateSegment(char *filename, bool is3DSound)
{
	IDirectMusicSegment8 *seg;

     WCHAR wcharStr[MAX_PATH];

     // convert filename to unicode string
     MultiByteToWideChar(CP_ACP, 0, filename, -1, wcharStr, MAX_PATH);

     // load the segment from file
     if (FAILED(dmusicLoader->LoadObjectFromFile(CLSID_DirectMusicSegment,
                                                 IID_IDirectMusicSegment8,
                                                 wcharStr,
                                                 (void**)&seg)))
     {
          MessageBox(NULL, "Audio file not found! Press OK to exit",
                     "ERROR!", MB_OK);

          return NULL;
     }

	return seg;
}

// Create()
// desc: create a CAudio object
CAudio *CAudioSystem::Create(char *filename, bool is3DSound)
{
	CAudio *audio;
	IDirectMusicSegment8 *dmSeg;
	IDirectSound3DBuffer8 *ds3D;

	audio = new CAudio;

	dmSeg = CreateSegment(filename, is3DSound);
	audio->SetSegment(dmSeg);
	
	if (is3DSound)
	{
		ds3D = Create3DBuffer();
		audio->Set3DBuffer(ds3D);
		audio->Set3DSound(true);
	}
	else
	{
		audio->Set3DBuffer(NULL);
		audio->Set3DSound(false);
	}

	return audio;
}