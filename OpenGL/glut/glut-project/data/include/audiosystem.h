#ifndef __AUDIOSYSTEM_H
#define __AUDIOSYSTEM_H

/*
	AUDIOSYSTEM.H

	The CAudio and CAudioSystem classes

	Author: Kevin Hawkins
	Date: 3/28/2001
	Description: The CAudio class represents a single sound object, such
			   as a song, ambient sound, an object's sound, etc.
			   The CAudioSystem class is the controller for creating and
			   playing CAudio objects.

*/

//#include <windows.h>               // standard Windows app include
#include <dmusicc.h>               // DirectMusic includes
#include <dmusici.h>
#include <d3d8types.h>             // for D3DVECTOR
#include <cguid.h>                 // for GUID_NULL

/*
	The CAudio class
*/
class CAudio
{
private:
	IDirectMusicSegment8 *dmusicSegment;      // the segment

	// The 3D buffer might not be used (e.g. background music).
	// It should only be used for 3D positional sounds.
	IDirectSound3DBuffer *ds3DBuffer;

	bool is3DSound;	// true if this is a 3D sound

protected:

public:
	CAudio() { dmusicSegment = NULL; ds3DBuffer = NULL; is3DSound = false; }
	~CAudio() 
	{
		if (dmusicSegment != NULL)
		{
			dmusicSegment->Release(); 
			dmusicSegment = NULL;
		}

		if (ds3DBuffer != NULL)
		{
			ds3DBuffer->Release(); 
			ds3DBuffer = NULL;
		}
	}

	void SetSegment(IDirectMusicSegment8 *seg) { dmusicSegment = seg; }
	IDirectMusicSegment8 *GetSegment() { return dmusicSegment; }

	void Set3DBuffer(IDirectSound3DBuffer *dsBuff);
	IDirectSound3DBuffer *Get3DBuffer() { return ds3DBuffer; }

	bool Is3DSound() { return is3DSound; }
	void Set3DSound(bool b) { is3DSound = b; }

	void Set3DParams(float minDistance, float maxDistance);
	void Set3DPos(float x, float y, float z);
};

/*
	The CAudioSystem class
*/
class CAudioSystem
{
private:
	IDirectMusicLoader8 *dmusicLoader;                   // the loader
	IDirectMusicPerformance8 *dmusicPerformance;    // the performance
	IDirectMusicAudioPath8 *dmusic3DAudioPath;       // the audiopath
	IDirectSound3DListener8 *ds3DListener;              // 3d listener

	DS3DLISTENER dsListenerParams;                      // 3d listener properties

public:
	CAudioSystem();
	~CAudioSystem();

	bool InitDirectXAudio(HWND hwnd);
	IDirectSound3DBuffer8 *Create3DBuffer();
	CAudio *Create(char *filename, bool is3DSound);
	IDirectMusicSegment8 *CreateSegment(char *filename, bool is3DSound);
	
	void Play(CAudio *audio, DWORD numRepeats);
	void Stop(CAudio *audio);

	void PlaySegment(IDirectMusicSegment8 *dmSeg, bool is3DSound, DWORD numRepeats);
	void StopSegment(IDirectMusicSegment8 *dmSeg);
	void Shutdown();

	void SetListenerPos(float cameraX, float cameraY, float cameraZ);
	void SetListenerRolloff(float rolloff);
	void SetListenerOrientation(float forwardX, float forwardY, float forwardZ,
						   float topX, float topY, float topZ)
	{
		ds3DListener->SetOrientation(forwardX, forwardY, -forwardZ, topX, topY, topZ, DS3D_IMMEDIATE);
	}

	IDirectMusicPerformance8 *GetPerformance() { return dmusicPerformance; }
};


#endif