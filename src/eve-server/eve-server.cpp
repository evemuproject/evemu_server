/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of EVEmu: EVE Online Server Emulator
    Copyright 2006 - 2011 The EVEmu Team
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

#include "eve-server.h"

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
// apiserver services
#include "apiserver/APIServer.h"
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
// dogmaim services
#include "dogmaim/DogmaIMService.h"
#include "dogmaim/DogmaService.h"
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
// pos services
#include "pos/PlanetMgr.h"
#include "pos/PosMgrService.h"
// ship services
#include "ship/BeyonceService.h"
#include "ship/FleetProxy.h"
#include "ship/InsuranceService.h"
#include "ship/RepairService.h"
#include "ship/ShipService.h"
#include "ship/modules/ModuleEffects.h"
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

static void SetupSignals();
static void CatchSignal( int sig_num );

static const char* const CONFIG_FILE = EVEMU_ROOT "/etc/eve-server.xml";
static const uint32 MAIN_LOOP_DELAY = 10; // delay 10 ms.

static volatile bool RunLoops = true;
dgmtypeattributemgr * _sDgmTypeAttrMgr;

// Create global singletons.
EntityList &_sEntityList = EntityList::get();
ItemFactory &_sItemFactory = ItemFactory::get();
PyServiceMgr &_sManager = *(new PyServiceMgr( 888444 ));

int main( int argc, char* argv[] )
{
    // unbuffer the stdout so that custom terminal or gui type
    // programs can properly capture the output of the server.
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    
#if defined( HAVE_CRTDBG_H ) && !defined( NDEBUG )
    // Under Visual Studio setup memory leak detection
    _CrtSetDbgFlag( _CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) );
#endif /* defined( HAVE_CRTDBG_H ) && !defined( NDEBUG ) */

    printf("Copyright (C) 2006-2011 EVEmu Team. http://evemu.org/\n");
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

    // Load server configuration
    if( !sConfig.ParseFile( CONFIG_FILE ) )
    {
        printf("ERROR: Loading server configuration '%s' failed.", CONFIG_FILE );
        //sLog.Error( "server init", "Loading server configuration '%s' failed.", CONFIG_FILE );
        std::cout << std::endl << "press any key to exit...";  std::cin.get();
        return 1;
    }

    sLog.InitializeLogging(sConfig.files.logDir);
    sLog.Log("server init", "Loading server configuration...");

    sLog.Log("", "" );
    sLog.Log("SERVER VERSION", "EVEmu " EVEMU_VERSION );
    sLog.Log("", "" );
    sLog.Log("SOURCE", "get at " EVEMU_REPOSITORY );
    sLog.Log("", "" );
    sLog.Log("SERVER INIT", "\n"
        "\tSupported Client: %s\n"
        "\tVersion %.2f\n"
        "\tBuild %d\n"
        "\tMachoNet %u",
        EVEProjectVersion,
        EVEVersionNumber,
        EVEBuildVersion,
        MachoNetVersion
    );

    //it is important to do this before doing much of anything, in case they use it.
    Timer::SetCurrentTime();

    // Load server log settings ( will be removed )
    if( load_log_settings( sConfig.files.logSettings.c_str() ) )
        sLog.Success( "server init", "Log settings loaded from %s", sConfig.files.logSettings.c_str() );
    else
        sLog.Warning( "server init", "Unable to read %s (this file is optional)", sConfig.files.logSettings.c_str() );

    // open up the log file if specified ( will be removed )
    if( !sConfig.files.logDir.empty() )
    {
        std::string logFile = sConfig.files.logDir + "eve-server.log";
        if( log_open_logfile( logFile.c_str() ) )
            sLog.Success( "server init", "Found log directory %s", sConfig.files.logDir.c_str() );
        else
            sLog.Warning( "server init", "Unable to find log directory '%s', only logging to the screen now.", sConfig.files.logDir.c_str() );
    }

    //connect to the database...
    DBerror err;
    if( !sDatabase.Open( err,
        sConfig.database.host.c_str(),
        sConfig.database.username.c_str(),
        sConfig.database.password.c_str(),
        sConfig.database.db.c_str(),
        sConfig.database.port ) )
    {
        sLog.Error( "server init", "Unable to connect to the database: %s", err.c_str() );
        std::cout << std::endl << "press any key to exit...";  std::cin.get();
        return 1;
    }
    _sDgmTypeAttrMgr = new dgmtypeattributemgr(); // needs to be after db init as its using it

    //Start up the TCP server
    EVETCPServer tcps;

    char errbuf[ TCPCONN_ERRBUF_SIZE ];
    if( tcps.Open( sConfig.net.port, errbuf ) )
    {
        sLog.Success( "server init", "TCP listener started on port %u.", sConfig.net.port );
    }
    else
    {
        sLog.Error( "server init", "Failed to start TCP listener on port %u: %s.", sConfig.net.port, errbuf );
        std::cout << std::endl << "press any key to exit...";  std::cin.get();
        return 1;
    }

    //setup the command dispatcher
    CommandDispatcher command_dispatcher;
    RegisterAllCommands( command_dispatcher );

    /*
     * Service creation and registration.
     *
     */
    sLog.Log("server init", "Creating sManager.");

    // Please keep the services list clean so it's easyier to find something

    sManager.RegisterService(new AccountService());
    sManager.RegisterService(new AgentMgrService());
    sManager.RegisterService(new AggressionMgrService());
    sManager.RegisterService(new AlertService());
    sManager.RegisterService(new AuthService());
    sManager.RegisterService(new BillMgrService());
    sManager.RegisterService(new BeyonceService());
    sManager.RegisterService(new BookmarkService());
    sManager.RegisterService(new BrowserLockdownService());
    sManager.RegisterService(new BulkMgrService());
    sManager.RegisterService(new CertificateMgrService());
    sManager.RegisterService(new CharFittingMgrService());
    sManager.RegisterService(new CharUnboundMgrService());
    sManager.RegisterService(new CharMgrService());
    sManager.RegisterService(new ClientStatLogger());
    sManager.RegisterService(new ClientStatsMgr());
    sManager.RegisterService(new ConfigService());
    sManager.RegisterService(new CorpBookmarkMgrService());
    sManager.RegisterService(new CorpMgrService());
    sManager.RegisterService(new CorporationService());
    sManager.RegisterService(new CorpRegistryService());
    sManager.RegisterService(new CorpStationMgrService());
    sManager.RegisterService(new ContractMgrService());
    sManager.RegisterService(new ContractProxyService());
    sManager.RegisterService(new DevToolsProviderService());
    sManager.RegisterService(new DogmaIMService());
    sManager.RegisterService(new DogmaService());
    sManager.RegisterService(new DungeonExplorationMgrService());
    sManager.RegisterService(new DungeonService());
    sManager.RegisterService(new FactionWarMgrService());
    sManager.RegisterService(new FactoryService());
    sManager.RegisterService(new FleetProxyService());
    sManager.RegisterService(new HoloscreenMgrService());
    sManager.RegisterService(new InfoGatheringMgr());
    sManager.RegisterService(new InsuranceService());
    sManager.RegisterService(new InvBrokerService());
    sManager.RegisterService(new JumpCloneService());
    sManager.RegisterService(new KeeperService());
    sManager.RegisterService(new LanguageService());
    sManager.RegisterService(new LocalizationServerService());
    sManager.RegisterService(new LookupService());
    sManager.RegisterService(new LPService());
    sManager.RegisterService(sManager.lsc_service = new LSCService(&command_dispatcher));
    sManager.RegisterService(new MailMgrService());
    sManager.RegisterService(new MailingListMgrService());
    sManager.RegisterService(new MapService());
    sManager.RegisterService(new MarketProxyService());
    sManager.RegisterService(new MissionMgrService());
    sManager.RegisterService(new NetService());
    sManager.RegisterService(new NotificationMgrService());
    sManager.RegisterService(sManager.cache_service = new ObjCacheService(sConfig.files.cacheDir.c_str()));
    sManager.RegisterService(new OnlineStatusService());
    sManager.RegisterService(new PaperDollService());
    sManager.RegisterService(new PetitionerService());
    sManager.RegisterService(new PhotoUploadService());
    sManager.RegisterService(new PlanetMgrService());
    sManager.RegisterService(new PosMgrService());
    sManager.RegisterService(new RamProxyService());
    sManager.RegisterService(new RepairService());
    sManager.RegisterService(new ReprocessingService());
    sManager.RegisterService(new ShipService());
    sManager.RegisterService(new SkillMgrService());
    sManager.RegisterService(new SlashService(&command_dispatcher));
    sManager.RegisterService(new SovereigntyMgrService());
    sManager.RegisterService(new Standing2Service());
    sManager.RegisterService(new StationService());
    sManager.RegisterService(new StationSvcService());
    sManager.RegisterService(new TutorialService());
    sManager.RegisterService(new UserService());
    sManager.RegisterService(new VoiceMgrService());
    sManager.RegisterService(new WarRegistryService());

    sLog.Log("server init", "Priming cached objects.");
    sManager.cache_service->PrimeCache();
    sLog.Log("server init", "finished priming");

    // start up the image server
    sImageServer.Run();
	sLog.Log("server init", "started image server");

    // start up the api server
    sAPIServer.CreateServices();
    sAPIServer.Run();
	sLog.Log("server init", "started API server");

    // start up the image server
    sLog.Log("server init", "Loading Dynamic Database Table Objects...");

	// Create In-Memory Database Objects for Critical Systems, such as ModuleManager:
	sLog.Log("server init", "---> sDGM_Effects_Table: Loading...");
	sDGM_Effects_Table.Initialize();
	sLog.Log("server init", "---> sDGM_Skill_Bonus_Modifiers_Table: Loading...");
	sDGM_Skill_Bonus_Modifiers_Table.Initialize();
	//sLog.Log("server init", "---> sDGM_Ship_Bonus_Modifiers_Table: Loading...");
	//sDGM_Ship_Bonus_Modifiers_Table.Initialize();
	sLog.Log("server init", "---> sDGM_Types_to_Wrecks_Table: Loading...");
	sDGM_Types_to_Wrecks_Table.Initialize();

        sLog.Log("server init", "Init done.");

	/////////////////////////////////////////////////////////////////////////////////////
	//     !!!  DO NOT PUT ANY INITIALIZATION CODE OR CALLS BELOW THIS LINE   !!!
	/////////////////////////////////////////////////////////////////////////////////////
	sManager.serviceDB().SetServerOnlineStatus(true);
	sLog.Success("server init", "SERVER IS NOW [ONLINE]");
	sLog.Log("INFO", "(press Ctrl+C to start controlled server shutdown)");

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
        while( ( tcpc = tcps.PopConnection() ) )
        {
            Client* c = new Client( &tcpc );

            sEntityList.Add( &c );
        }

        sEntityList.Process();
        sManager.Process();

        /* UPDATE */
        last_time = GetTickCount();
        etime = last_time - start;

        // do the stuff for thread sleeping
        if( MAIN_LOOP_DELAY > etime )
            Sleep( MAIN_LOOP_DELAY - etime );
    }

    sLog.Log("server shutdown", "Main loop stopped" );

    // Shutting down EVE Client TCP listener
    tcps.Close();
    sLog.Log("server shutdown", "TCP listener stopped." );

    // Shutting down API Server:
    sAPIServer.Stop();
    sLog.Log("server shutdown", "Image Server TCP listener stopped." );

    // Shutting down Image Server:
    sImageServer.Stop();
    sLog.Log("server shutdown", "API Server TCP listener stopped." );

    sManager.serviceDB().SetServerOnlineStatus(false);
	sLog.Log("server shutdown", "SERVER IS NOW [OFFLINE]");

    sLog.Log("server shutdown", "Cleanup db cache" );
    delete _sDgmTypeAttrMgr;

    log_close_logfile();

    //std::cout << std::endl << "press the ENTER key to exit...";  std::cin.get();

	// Shut down the Item system ensuring ALL items get saved to the database:
	sLog.Log("server shutdown", "Shutting down Item Factory." );
    sItemFactory.ShutDown();

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
    sLog.Log( "Signal system", "Caught signal: %d", sig_num );

    RunLoops = false;
}
