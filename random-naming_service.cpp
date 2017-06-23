#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <OB/OBNaming.h>

#include <fstream>
#include <iostream>

#include "RandomImplementation.h"

using namespace std;

int
main(int argc, char* argv[])
{
        try {
                // Initialize server ORB
                CORBA::ORB_var vOrb = CORBA::ORB_init(argc, argv);

                // Locate Name Service
                CORBA::Object_var vObject =
                  vOrb->resolve_initial_references("NameService");
                assert(!CORBA::is_nil(vObject));
                CosNaming::NamingContext_var vNamingContext =
                  CosNaming::NamingContext::_narrow(vObject);

                // Get Root POA reference from ORB
                //	(with object lifetime managed by CORBA)
                CORBA::Object_var vPoaObj =
                  vOrb->resolve_initial_references("RootPOA");
                assert(!CORBA::is_nil(vPoaObj));

                // Narrow (cast) reference to expected object class type
                PortableServer::POA_var vRootPoa =
                  PortableServer::POA::_narrow(vPoaObj);

                // Create POA policies
                CORBA::PolicyList policies;
                policies.length(1);

                // Single threaded to ensure that random numbers are requested
                // in sequence
                policies[0] = vRootPoa->create_thread_policy(
                  PortableServer::SINGLE_THREAD_MODEL);

                // Get Root POA Manager object reference
                PortableServer::POAManager_var vManager =
                  vRootPoa->the_POAManager();

                // Create a new POA with specified policies
                PortableServer::POA_var myPOA =
                  vRootPoa->create_POA("myPOA", vManager, policies);

                // Free policies
                CORBA::ULong len = policies.length();
                for (CORBA::ULong i = 0; i < len; i++)
                        policies[i]->destroy();

                // Create implementation class instance object
                //    (available locally on server)
                RandomImplementation* randImpl = new RandomImplementation(vOrb);
                // Activate object
                PortableServer::ObjectId_var myObjID =
                  myPOA->activate_object(randImpl);

                // Get a CORBA reference with the POA through the servant
                CORBA::Object_var o = myPOA->servant_to_reference(randImpl);

                // Prepare object with "server name" data key
                CosNaming::Name implName;
                implName.length(1);
                implName[0].id = CORBA::string_dup(argv[1]);
                implName[0].kind = CORBA::string_dup("");

                // Register object IOR reference in Name Service
                vNamingContext->bind(implName, o);

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
