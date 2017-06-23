#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <OB/OBNaming.h>

#include <fstream>
#include <iostream>

#include "GeneticImplementation.h"

using namespace std;

int
main(int argc, char* argv[])
{
        if (argc < 3) {
                std::cout << "Usage: " << argv[0] << " -ORBnaming  randProvider"
                          << std::endl;
                return -1;
        }

        try {
                // Initialize server ORB
                CORBA::ORB_var vOrb = CORBA::ORB_init(argc, argv);

                // Locate Name Service
                CORBA::Object_var vObject =
                  vOrb->resolve_initial_references("NameService");
                assert(!CORBA::is_nil(vObject));
                CosNaming::NamingContext_var vNamingContext =
                  CosNaming::NamingContext::_narrow(vObject);

                // Now try to connect to the random number provider
                CosNaming::Name implName;
                implName.length(1);
                implName[0].id = CORBA::string_dup(argv[2]);
                implName[0].kind = CORBA::string_dup("");

                // Get remote object reference from Name Service
                CORBA::Object_var vCorbaObj = vNamingContext->resolve(implName);

                Genetic::RandomProvider* randProv =
                  Genetic::RandomProvider::_narrow(vCorbaObj);

                // Get Root POA reference from ORB
                //	(with object lifetime managed by CORBA)
                CORBA::Object_var vPoaObj =
                  vOrb->resolve_initial_references("RootPOA");
                assert(!CORBA::is_nil(vPoaObj));

                // Narrow (cast) reference to expected object class type
                PortableServer::POA_var vRootPoa =
                  PortableServer::POA::_narrow(vPoaObj);

                // Get Root POA Manager object reference
                PortableServer::POAManager_var vManager =
                  vRootPoa->the_POAManager();

                // Create implementation class instance object
                //    (available locally on server)
                GeneticImplementation* pGenImpl =
                  new GeneticImplementation(vOrb, randProv);

                // Implicitly activate local instance as "CORBA Object" ...
                PortableServer::ServantBase_var vServant = pGenImpl;
                // ... and obtain its IOR reference (for remote use)
                Genetic::GeneticTimeTable_var vGenImplObj = pGenImpl->_this();

                // Prepare object with "server name" data key
                implName.length(1);
                implName[0].id = CORBA::string_dup(argv[1]);
                implName[0].kind = CORBA::string_dup("");

                // Register object IOR reference in Name Service
                vNamingContext->bind(implName, vGenImplObj);

                // Activate Root POA Manager - start processing request queue
                vManager->activate();

                // Start ORB event loop (indefinitely)
                vOrb->run();
        } catch (CORBA::SystemException& e) {
                cout << "Problem: parameters 1,2,3 are " << argv[1] << " "
                     << argv[2] << " " << argv[3] << "\n";
                cout << "Exception: " << e.reason() << std::endl;
                return 1;
        }
        return 0;
}
