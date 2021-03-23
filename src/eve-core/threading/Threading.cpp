/**
 * @name Threading.cpp
 *   lightweight thread pool specifically for EvEmu Sockets
 *   this code is very basic and very specific.
 * @Author:         Allan
 * @date:   05 March 2016
 */

/** @todo the entire concurrency idea needs work throughout evemu.  currently, it uses posix threads, boost, and shared_pointer.
 * they all need updating
 *
 *  @note  image server uses boost::asio::thread and has no problems....leave for now, and may leave as is.
 *
 * update this to use thread pools and strictly for network sockets
 */

#include "Threading.h"
#include "log/LogNew.h"
#include "log/logsys.h"


Threading::Threading()
{
}

Threading::~Threading()
{
    m_threads.clear();
}

void Threading::Initialize() {
    nfds = 1;
    bufferLen = 64 * 1024; // 64kbyte recieve buffer, up from default of 8k
    sleepTime = 10;     //sConfig.rates.NetSleepTime
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    m_threads.clear();
    sLog.Blue( "        Threading", "Threading System Initialized.");
}

void Threading::RunLoop() {
    while (true) {
        Process();
        Sleep(sleepTime);
    }
}

/** @todo  begin basic thread pool for processing sockets, using select() */
void Threading::Process() {
    /* reset timeouts because select() reset them */
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rSoc);
    FD_ZERO(&wSoc);
    FD_SET(0, &rSoc);
    FD_SET(0, &wSoc);
    int status = select(nfds, &rSoc, &wSoc, nullptr, &tv);
    if (status == 0) /* nothing ready yet */
        return;
    else if (status == -1) {  /* error */
        _log(THREAD__ERROR, "Process() - select() returned: %s", strerror(status));
        return;
    }
    if (FD_ISSET(nfds, &rSoc)) {
        buf = (char*) malloc (bufferLen);
        /* read from socket here */
        free(buf);
    }
    if (FD_ISSET(nfds, &wSoc)) {
        buf = (char*) malloc (bufferLen);
        /* write to socket here */
        free(buf);
    }

}
void Threading::AddSocket(SOCKET soc) {
    /* when adding a new socket, we must add it to the read and write sets, with it's fd# */
    FD_SET(soc, &rSoc);
    FD_SET(soc, &wSoc);
    ++nfds;
}

void Threading::CreateThread(void *(*start_routine) (void *), void *args) {
    pthread_t thread;
    int status = pthread_create( &thread, nullptr, start_routine, args);
    if (status) {
        _log(THREAD__ERROR, "CreateThread() - Error Creating new thread: %s", strerror(errno));
    } else {
        _log(THREAD__INFO, "CreateThread() - Creating new threadID 0x%X", thread);
        AddThread(thread);
        pthread_detach(thread);
    }
}

void Threading::AddThread(pthread_t thread) {
    m_threads.push_back(thread);
    _log(THREAD__INFO, "AddThread() - Added thread ID 0x%X", thread);
}

void Threading::RemoveThread(pthread_t thread) {
    for (std::vector<pthread_t>::iterator cur = m_threads.begin(); cur != m_threads.end(); ++cur) {
        if ((*cur) == thread) {
            _log(THREAD__INFO, "RemoveThread() called for thread ID 0x%X", thread);
            m_threads.erase(cur);
            return;
        }
    }
    _log(THREAD__ERROR, "RemoveThread() - Called on unregistered threadID 0x%X", thread);
}

void Threading::ListThreads() {
    for (auto cur : m_threads)
        sLog.Warning( "                 ", "ThreadID 0x%X", cur );
}

void Threading::EndThreads() {
    if (!m_threads.size()) {
        _log(THREAD__MESSAGE, "EndThreads() - There are no active threads.");
        return;
    }
    _log(THREAD__MESSAGE, "EndThreads() - Joining %u currently active threads.", m_threads.size());
    std::vector<pthread_t>::iterator cur = m_threads.begin();
    while ((cur != m_threads.end())) {
        _log(THREAD__TRACE, "EndThreads() - Removing threadID 0x%X", (*cur));
        cur = m_threads.erase(cur);
    }
    m_threads.clear();
}
