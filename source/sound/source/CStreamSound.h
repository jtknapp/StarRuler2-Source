#pragma once

#include "ISound.h"
#include "SoundTypes.h"
#include "threads.h"
#include <set>

namespace audio {

	class ISoundSource;
	class CSoundSource;
	extern void checkError();

	class CStreamSound : public ISound {
	public:
		CStreamSound(const ISoundSource* sound, bool is3D, bool priority);
		~CStreamSound();

		virtual void streamData();
		void freeQueuedBuffers();

		virtual bool isStopped() const;

		virtual bool isPlaying() const;

		virtual void pause();

		virtual void resume();

		virtual void seek(int timeMS);

		virtual void setLooped(bool loop);

		virtual bool isLooped() const;

		virtual void stop();

		virtual void setPosition(float x, float y, float z);
		virtual void setVelocity(float x, float y, float z);

		virtual void setRolloff(float factor);
		virtual void setLowPass(float strength);

		virtual void setVolume(float volume);
		virtual void setPitch(float pitch);

		virtual int getPlayPosition();

		virtual void setPlayPosition(int timeMs);

		virtual int getPlayLength();

		virtual void setMinDistance(float minDist);
		virtual void setMaxDistance(float maxDist);

		virtual const ISoundSource* getSoundSource();

	protected:
		mutable threads::Mutex lock;
		void acquire() const { lock.lock(); }
		void release() const { checkError(); lock.release(); }

		const CSoundSource* soundSource;
		sourceID soundID, filterID;

		bool streaming;
		long streamPos;

		bool loop;
		unsigned timestamp;
		unsigned byterate;
		bufferID resetStampID;

		std::set<bufferID> buffers;
	};
};