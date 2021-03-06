//=============================================================================================================
/**
* @file     dacqserver.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>;
* @version  1.0
* @date     July, 2012
*
* @section  LICENSE
*
* Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief     implementation of the DacqServer Class.
*
*/


#ifndef DACQSERVER_H
#define DACQSERVER_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "types_definitions.h"
#include <fiff/fiff_info.h>
#include <fiff/fiff_tag.h>


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QThread>

#include <QTcpSocket>

#include <QByteArray>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE NeuromagPlugin
//=============================================================================================================

namespace NeuromagPlugin
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace FIFFLIB;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class Neuromag;
class CollectorSocket;
class ShmemSocket;
//class FiffInfo;


//=============================================================================================================
/**
* DECLARE CLASS DacqServer
*
* @brief The DacqServer class provides a Neuromag MEG connector.
*/
class DacqServer : public QThread
{
    Q_OBJECT

    friend class Neuromag;

public:

    //=========================================================================================================
    /**
    * Constructs a acquisition Server.
    */
    explicit DacqServer(Neuromag* p_pNeuromag, QObject * parent = 0);
    
    
    //=========================================================================================================
    /**
    * Constructs a acquisition Server.
    */
    ~DacqServer();

    
public slots: //--> in Qt 5 not anymore declared as slot

    void readCollectorMsg();


signals:

    void measInfoAvailable();


protected:
    //=========================================================================================================
    /**
    * The starting point for the thread. After calling start(), the newly created thread calls this function.
    * Returning from this method will end the execution of the thread.
    * Pure virtual method inherited by QThread.
    */
    virtual void run();

private:

    //=========================================================================================================
    /**
    * Quit function
    *
    * @return
    */
//    void clean_up();



    //newly written stuff ported to qt
//    QString         m_sCollectorHost;
    CollectorSocket*    m_pCollectorSock;


    ShmemSocket*        m_pShmemSock;
    









//dacqserver

    bool m_bIsRunning;

    bool m_bMeasInfoRequest;
    bool m_bMeasRequest;
    bool m_bMeasStopRequest;
    bool m_bSetBuffersizeRequest;


    bool getMeasInfo(FiffInfo::SDPtr& p_pFiffInfo);

    Neuromag* m_pNeuromag;


};

} // NAMESPACE


#endif // DACQSERVER_H
