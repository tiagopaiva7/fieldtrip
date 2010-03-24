/*
 * Copyright (C) 2010, Stefan Klanke
 * Donders Institute for Donders Institute for Brain, Cognition and Behaviour,
 * Centre for Cognitive Neuroimaging, Radboud University Nijmegen,
 * Kapittelweg 29, 6525 EN Nijmegen, The Netherlands
 */
#ifndef __FolderWatcher_h
#define __FolderWatcher_h

#include <windows.h>
#include <vector>
#include <string>


class FolderWatcher {
	public:
	
	FolderWatcher(const char *directory);
	~FolderWatcher();
	
	/* Synchronous (blocking) operation, returns number of changes or 0 on error */
	int waitForChanges();
	
	/* Asynchronous operation, returns "false" on error */
	bool startListenForChanges(HANDLE eventHandle = INVALID_HANDLE_VALUE);
	bool stopListenForChanges();
	
	/* Asynchronous operation, returns number of changes -- if non-zero, restart listening */
	int checkHasChanged(unsigned int ms);
	
	/* retrieve vector of filenames */
	const std::vector<std::string>& getFilenames() const { 
		return vecFilenames; 
	}
	
	bool isValid() const { 
		return (dirHandle != INVALID_HANDLE_VALUE); 
	}
	
	int processChanges();
	
	HANDLE getWin32Event() { return eventHandle; }
	
	protected:
	
	bool isListening;
	
	std::vector<std::string> vecFilenames;
	char fileInfoBuffer[16384];
	HANDLE dirHandle, eventHandle, usedHandle;
	OVERLAPPED overlap;
};

#endif
