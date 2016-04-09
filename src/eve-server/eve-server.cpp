/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2016 The EVEmu Team
    For the latest information visit http://evemu.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
    Author:     Zhur, mmcs
 */

// uncomment to throw exceptions
//#define _THROW_FP_EXCEPTIONS
#ifdef _THROW_FP_EXCEPTIONS
#ifdef HAVE_WINDOWS_H
// Need windows equivalent.
#else /* !HAVE_WINDOWS_H */
// Set throw errors on floating point exceptions.
#define _GNU_SOURCE 1
#include <fenv.h>

static void __attribute__((constructor))
trapfpe()
{
    /* Enable some exceptions.  At startup all exceptions are masked.  */
    feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
}
#endif /* !HAVE_WINDOWS_H */
#endif

#include "eve-server.h"
#include "eveStatic.h"

#include "EVEServerConfig.h"
#include "NetService.h"
// account services
#include "account/AccountService.h"
#include "account/AuthService.h"
#include "account/BrowserLockdownSvc.h"
#include "account/ClientStatMgrService.h"
#include "account/InfoGatheringMgr.h"
#include "account/TutorialService.h"
#include "account/UserService.h"
// admin services
#include "admin/AlertService.h"
#include "admin/AllCommands.h"
#include "admin/ClientStatLogger.h"
#include "admin/CommandDispatcher.h"
#include "admin/DevToolsProviderService.h"
#include "admin/PetitionerService.h"
#include "admin/SlashService.h"
// cache services
#include "cache/BulkMgrService.h"
#include "cache/ObjCacheService.h"
// character services
#include "character/AggressionMgrService.h"
#include "character/CertificateMgrService.h"
#include "character/CharFittingMgrService.h"
#include "character/CharMgrService.h"
#include "character/CharUnboundMgrService.h"
#include "character/PaperDollService.h"
#include "character/PhotoUploadService.h"
#include "character/SkillMgrService.h"
// chat services
#include "chat/LookupService.h"
#include "chat/LSCService.h"
#include "chat/OnlineStatusService.h"
#include "chat/VoiceMgrService.h"
// config services
#include "config/ConfigService.h"
#include "config/LanguageService.h"
#include "config/LocalizationServerService.h"
// corporation services
#include "corporation/CorpBookmarkMgrService.h"
#include "corporation/CorpMgrService.h"
#include "corporation/CorporationService.h"
#include "corporation/CorpRegistryService.h"
#include "corporation/CorpStationMgrService.h"
#include "corporation/LPService.h"
// database
#include "database/dbcore.h"
// dogmaim services
#include "dogmaim/DogmaIMService.h"
#include "dogmaim/DogmaService.h"
// fleet services
#include "fleet/FleetObject.h"
#include "fleet/FleetProxy.h"
// imageserver services
#include "imageserver/ImageServer.h"
// inventory services
#include "inventory/InvBrokerService.h"
// mail services
#include "mail/MailMgrService.h"
#include "mail/MailingListMgrService.h"
#include "mail/NotificationMgrService.h"
// manufacturing services
#include "manufacturing/FactoryService.h"
#include "manufacturing/RamProxyService.h"
// map services
#include "map/MapService.h"
// market services
#include "market/BillMgrService.h"
#include "market/ContractMgrService.h"
#include "market/ContractProxy.h"
#include "market/MarketProxyService.h"
// mining services
#include "mining/ReprocessingService.h"
// missions services
#include "missions/AgentMgrService.h"
#include "missions/DungeonExplorationMgrService.h"
#include "missions/MissionMgrService.h"
// network
#include "network/TCPServer.h"
#include "network/EVETCPConnection.h"
// pos services
#include "pos/PlanetMgr.h"
#include "pos/PosMgrService.h"
//Search Service
#include "search/SearchMgrService.h"
// ship services
#include "ship/BeyonceService.h"
#include "ship/InsuranceService.h"
#include "ship/RepairService.h"
#include "ship/ShipService.h"
// standing services
#include "standing/FactionWarMgrService.h"
#include "standing/SovereigntyMgrService.h"
#include "standing/Standing2Service.h"
#include "standing/WarRegistryService.h"
// station services
#include "station/HoloscreenMgrService.h"
#include "station/JumpCloneService.h"
#include "station/StationService.h"
#include "station/StationSvcService.h"
// system services
#include "system/BookmarkService.h"
#include "system/DungeonService.h"
#include "system/KeeperService.h"
#include "system/ScenarioService.h"
#include "system/WrecksAndLoot.h"
// service manager
#include "PyServiceMgr.h"

static void SetupSignals();
static void CatchSignal( int sig_num );

static const char* const CONFIG_FILE = EVEMU_ROOT "/etc/eve-server.xml";
static const uint32 MAIN_LOOP_DELAY = 10; // delay 10 ms.

static volatile bool RunLoops = true;
dgmtypeattributemgr * _sDgmTypeAttrMgr;

int main( int argc, char* argv[] )
{
#if defined( HAVE_CRTDBG_H ) && !defined( NDEBUG )
    // Under Visual Studio setup memory leak detection
    _CrtSetDbgFlag( _CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) );
#endif /* defined( HAVE_CRTDBG_H ) && !defined( NDEBUG ) */

    printf("Copyright (C) 2006-2016 EVEmu Team. http://evemu.org/\n");
    printf("This program is free software; you can redistribute it and/or modify it under\n");
    printf("the terms of the GNU Lesser General Public License as published by the Free \n");
    printf("Software Foundation; either version 2 of the License, or (at your option) any\n");
    printf("later version.\n");
    printf("\n");
    printf("This program is distributed in the hope that it will be useful, but WITHOUT\n");
    printf("ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS\n");
    printf("FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more\n");
    printf("details.\n");
    printf("\n");

    // Initialize the configuration.
    EVEServerConfig config;
    // Load server configuration
    if (!config.ParseFile(CONFIG_FILE))
    {
        printf("ERROR: Loading server configuration '%s' failed.", CONFIG_FILE );
        //Log::Error( "server init", "Loading server configuration '%s' failed.", CONFIG_FILE );
        std::cout << std::endl << "press any key to exit...";  std::cin.get();
        return 1;
    }

    SysLog::InitializeLogging(EVEServerConfig::files.logDir);
    SysLog::Log("", "");
    SysLog::Warning("EvEMu", "Server Information:");
    SysLog::Log("Server Revision", EVEMU_VERSION);
    SysLog::Log("Build Date Time", "%s %s", __DATE__, __TIME__);
    SysLog::Log("This Source", "%s", EVEMU_REPOSITORY);
    SysLog::Log("Client", "Codename: %s | Version: %g | Build: %u (macho: %u)", EVEProjectCodename, EVEVersionNumber, EVEBuildVersion, MachoNetVersion );
    SysLog::Log("Database", "%s@%s:%u", EVEServerConfig::database.db.c_str(), EVEServerConfig::database.host.c_str(), EVEServerConfig::database.port);
    SysLog::Log("","");

    //it is important to do this before doing much of anything, in case they use it.
    Timer::SetCurrentTime();

    // Load server log settings ( will be removed )
    if( load_log_settings( EVEServerConfig::files.logSettings.c_str() ) )
        SysLog::Success( "Server Init", "Log settings loaded from %s", EVEServerConfig::files.logSettings.c_str() );
    else
        SysLog::Warning( "Server Init", "Unable to read %s (this file is optional)", EVEServerConfig::files.logSettings.c_str() );

    // open up the log file if specified ( will be removed )
    if( !EVEServerConfig::files.logDir.empty() )
    {
        std::string logFile = EVEServerConfig::files.logDir + "eve-server.log";
        if( log_open_logfile( logFile.c_str() ) )
            SysLog::Success( "Server Init", "Found log directory %s", EVEServerConfig::files.logDir.c_str() );
        else
            SysLog::Warning( "Server Init", "Unable to find log directory '%s', only logging to the screen now.", EVEServerConfig::files.logDir.c_str() );
    }

    //connect to the database...
    DBerror err;
    if (!DBcore::Open(err,
        EVEServerConfig::database.host.c_str(),
        EVEServerConfig::database.username.c_str(),
        EVEServerConfig::database.password.c_str(),
        EVEServerConfig::database.db.c_str(),
        EVEServerConfig::database.port ) )
    {
        SysLog::Error( "Server Init", "Unable to connect to the database: %s", err.c_str() );
        std::cout << std::endl << "Exiting";
        return 1;
    }
    else if (DBcore::Connected)
    {
        SysLog::Success("Server Init", "Connected to database successfully");
    }

    _sDgmTypeAttrMgr = new dgmtypeattributemgr(); // needs to be after db init as its using it

    //Start up the TCP server
    std::map<std::shared_ptr<TCPServer < EVETCPConnection>>, EVEServerConfig::EVEConfigNet> tcps;

    char errbuf[ TCPCONN_ERRBUF_SIZE ];
    if(EVEServerConfig::networks.empty())
    {
        SysLog::Error("Server Init", "Failed to start TCP listener: no networks defined.");
        std::cout << std::endl << "Exiting";
        return 1;
    }
    for(auto net : EVEServerConfig::networks)
    {
        std::shared_ptr<TCPServer < EVETCPConnection>> tcp = std::shared_ptr<TCPServer < EVETCPConnection >> (new TCPServer<EVETCPConnection>());
        if(tcp->open(net.port, net.serverBind, errbuf))
        {
            SysLog::Success("Server Init", "TCP listener started on port %u bound to %s.", net.port, net.serverBind.c_str());
            tcps[tcp] = net;
        }
        else
        {
            SysLog::Error("Server Init", "Failed to start TCP listener on port %u: %s.", net.port, errbuf);
        }
    }
    if(tcps.empty())
    {
        SysLog::Error("Server Init", "Failed to start TCP listener: no networks created.");
        std::cout << std::endl << "Exiting";
        return 1;
    }

    //make the item factory
    SysLog::Log("Server Init", "Loading static data.");
    if (!EVEStatic::loadStaticData())
    {
        SysLog::Error("Server Init", "Failed to load static data.");
        return 1;
    }

    //now, the service manager...
    PyServiceMgr::Init(888444);
    SysLog::Log("Server Init", "starting service manager");

    //setup the command dispatcher
    CommandDispatcher command_dispatcher;
    RegisterAllCommands( command_dispatcher );

    /*
     * Service creation and registration.
     *
     */
    SysLog::Log("Server Init", "Creating services.");

    // Please keep the services list clean so it's easier to find something

    PyServiceMgr::RegisterService(new AccountService());
    PyServiceMgr::RegisterService(new AgentMgrService());
    PyServiceMgr::RegisterService(new AggressionMgrService());
    PyServiceMgr::RegisterService(new AlertService());
    PyServiceMgr::RegisterService(new AuthService());
    PyServiceMgr::RegisterService(new BillMgrService());
    PyServiceMgr::RegisterService(new BeyonceService());
    PyServiceMgr::RegisterService(new BookmarkService());
    PyServiceMgr::RegisterService(new BrowserLockdownService());
    PyServiceMgr::RegisterService(new BulkMgrService());
    PyServiceMgr::RegisterService(new CertificateMgrService());
    PyServiceMgr::RegisterService(new CharFittingMgrService());
    PyServiceMgr::RegisterService(new CharUnboundMgrService());
    PyServiceMgr::RegisterService(new CharMgrService());
    PyServiceMgr::RegisterService(new ClientStatLogger());
    PyServiceMgr::RegisterService(new ClientStatsMgr());
    PyServiceMgr::RegisterService(new ConfigService());
    PyServiceMgr::RegisterService(new CorpBookmarkMgrService());
    PyServiceMgr::RegisterService(new CorpMgrService());
    PyServiceMgr::RegisterService(new CorporationService());
    PyServiceMgr::RegisterService(new CorpRegistryService());
    PyServiceMgr::RegisterService(new CorpStationMgrService());
    PyServiceMgr::RegisterService(new ContractMgrService());
    PyServiceMgr::RegisterService(new ContractProxyService());
    PyServiceMgr::RegisterService(new DevToolsProviderService());
    PyServiceMgr::RegisterService(new DogmaIMService());
    PyServiceMgr::RegisterService(new DogmaService());
    PyServiceMgr::RegisterService(new DungeonExplorationMgrService());
    PyServiceMgr::RegisterService(new DungeonService());
    PyServiceMgr::RegisterService(new FactionWarMgrService());
    PyServiceMgr::RegisterService(new FactoryService());
    PyServiceMgr::RegisterService(new FleetManager());
    PyServiceMgr::RegisterService(new FleetObject());
    PyServiceMgr::RegisterService(new FleetProxyService());
    PyServiceMgr::RegisterService(new HoloscreenMgrService());
    PyServiceMgr::RegisterService(new InfoGatheringMgr());
    PyServiceMgr::RegisterService(new InsuranceService());
    PyServiceMgr::RegisterService(new InvBrokerService());
    PyServiceMgr::RegisterService(new JumpCloneService());
    PyServiceMgr::RegisterService(new KeeperService());
    PyServiceMgr::RegisterService(new LanguageService());
    PyServiceMgr::RegisterService(new LocalizationServerService());
    PyServiceMgr::RegisterService(new LookupService());
    PyServiceMgr::RegisterService(new LPService());
    PyServiceMgr::RegisterService(PyServiceMgr::lsc_service = new LSCService(&command_dispatcher));
    PyServiceMgr::RegisterService(new MailMgrService());
    PyServiceMgr::RegisterService(new MailingListMgrService());
    PyServiceMgr::RegisterService(new MapService());
    PyServiceMgr::RegisterService(new MarketProxyService());
    PyServiceMgr::RegisterService(new MissionMgrService());
    PyServiceMgr::RegisterService(new NetService());
    PyServiceMgr::RegisterService(new NotificationMgrService());
    PyServiceMgr::RegisterService(PyServiceMgr::cache_service = new ObjCacheService(EVEServerConfig::files.cacheDir.c_str()));
    PyServiceMgr::RegisterService(new OnlineStatusService());
    PyServiceMgr::RegisterService(new PaperDollService());
    PyServiceMgr::RegisterService(new PetitionerService());
    PyServiceMgr::RegisterService(new PhotoUploadService());
    PyServiceMgr::RegisterService(new PlanetMgrService());
    PyServiceMgr::RegisterService(new PosMgrService());
    PyServiceMgr::RegisterService(new RamProxyService());
    PyServiceMgr::RegisterService(new RepairService());
    PyServiceMgr::RegisterService(new ReprocessingService());
    PyServiceMgr::RegisterService(new SearchMgrService());
    PyServiceMgr::RegisterService(new ShipService());
    PyServiceMgr::RegisterService(new SkillMgrService());
    PyServiceMgr::RegisterService(new SlashService(&command_dispatcher));
    PyServiceMgr::RegisterService(new SovereigntyMgrService());
    PyServiceMgr::RegisterService(new Standing2Service());
    PyServiceMgr::RegisterService(new StationService());
    PyServiceMgr::RegisterService(new StationSvcService());
    PyServiceMgr::RegisterService(new TutorialService());
    PyServiceMgr::RegisterService(new UserService());
    PyServiceMgr::RegisterService(new VoiceMgrService());
    PyServiceMgr::RegisterService(new WarRegistryService());

    SysLog::Log("Server Init", "Priming cached objects.");
    PyServiceMgr::cache_service->PrimeCache();
    SysLog::Log("Server Init", "finished priming");

    // start up the image server
    ImageServer::Run();
  SysLog::Log("Server Init", "started image server");

    // start up the api server
    //    APIServer::CreateServices();
    //    APIServer::Run();
    //  SysLog::Log("Server Init", "started API server");

    // start up the image server
  SysLog::Log("Server Init", "Loading Dynamic Database Table Objects...");

  // Create In-Memory Database Objects for Critical Systems, such as ModuleManager:
  SysLog::Log("Server Init", "---> sDGM_Effects_Table: Loading...");
  DGM_Effects_Table::Initialize();
  SysLog::Log("Server Init", "---> sDGM_Types_to_Wrecks_Table: Loading...");
  DGM_Types_to_Wrecks_Table::Initialize();

#ifdef HAVE_UNISTD_H
  if(getuid() == 0) {
    SysLog::Warning("Server Init", "Running as root. Attempting to drop root privileges.");
    // uid:gid 99:99 is nobody:nobody on my system. seems standard across all my linux systems. (arch, centos, debian)
    if(setgid(99) != 0) {
      SysLog::Error("Server Init", "setgid: Unable to drop group privileges: %s", strerror(errno));
      RunLoops = false;
    }
    if(setuid(99) != 0) {
      SysLog::Error("Server Init", "setuid: Unable to drop user privileges: %S", strerror(errno));
      RunLoops = false;
    }
    SysLog::Success("Server Init", "Dropped root privileges successfully: %u", getuid());
  }
#endif /* HAVE_UNISTD_H */

    SysLog::Success("Server Init", "Initialisation finished");

  /////////////////////////////////////////////////////////////////////////////////////
  //     !!!  DO NOT PUT ANY INITIALIZATION CODE OR CALLS BELOW THIS LINE   !!!
  /////////////////////////////////////////////////////////////////////////////////////
    ServiceDB::SetServerOnlineStatus(true);
  SysLog::Success("STATUS", "SERVER IS NOW [ONLINE]");
  SysLog::Log("INFO", "(press Ctrl+C to start controlled server shutdown)");

    /*
     * THE MAIN LOOP
     *
     * Everything except IO should happen in this loop, in this thread context.
     *
     */

    /* program events system */
    SetupSignals();

    uint32 start;
    uint32 etime;
    uint32 last_time = GetTickCount();

    EVETCPConnection* tcpc;
    while( RunLoops == true )
    {
        Timer::SetCurrentTime();
        start = GetTickCount();

        //check for timeouts in other threads
        //timeout_manager.CheckTimeouts();
        for(auto tcp : tcps)
        {
            while((tcpc = tcp.first->popConnection()))
            {
                Client* c = new Client(&tcpc, tcp.second);
                EntityList::Add(&c);
            }
        }

        EntityList::Process();
        PyServiceMgr::Process();

        /* UPDATE */
        last_time = GetTickCount();
        etime = last_time - start;

        // do the stuff for thread sleeping
        if( MAIN_LOOP_DELAY > etime )
            Sleep( MAIN_LOOP_DELAY - etime );
    }

    SysLog::Log("Server Shutdown", "Main loop stopped" );

    // Shutting down EVE Client TCP listener
    for(auto tcp : tcps)
    {
        tcp.first->close();
    }
    SysLog::Log("Server Shutdown", "TCP listener stopped." );

    // Shutting down API Server:
    //    APIServer::Stop();
    SysLog::Log("Server Shutdown", "API Server TCP listener stopped.");

    // Shutting down Image Server:
    ImageServer::Stop();
    SysLog::Log("Server Shutdown", "Image Server TCP listener stopped.");

    ServiceDB::SetServerOnlineStatus(false);
    PyServiceMgr::Shutdown();
    SysLog::Log("Server Shutdown", "SERVER IS NOW [OFFLINE]");

    SysLog::Log("Server Shutdown", "Cleanup db cache" );
    delete _sDgmTypeAttrMgr;

    log_close_logfile();

    //std::cout << std::endl << "press the ENTER key to exit...";  std::cin.get();

	// Shut down the Item system ensuring ALL items get saved to the database:
	SysLog::Log("Server Shutdown", "Shutting down Item Factory." );

	return 0;
}

static void SetupSignals()
{
    ::signal( SIGINT, CatchSignal );
    ::signal( SIGTERM, CatchSignal );
    ::signal( SIGABRT, CatchSignal );

#ifdef SIGABRT_COMPAT
    ::signal( SIGABRT_COMPAT, CatchSignal );
#endif /* SIGABRT_COMPAT */

#ifdef SIGBREAK
    ::signal( SIGBREAK, CatchSignal );
#endif /* SIGBREAK */

#ifdef SIGHUP
    ::signal( SIGHUP, CatchSignal );
#endif /* SIGHUP */
}

static void CatchSignal( int sig_num )
{
    SysLog::Log( "Signal system", "Caught signal: %d", sig_num );

    RunLoops = false;
}
