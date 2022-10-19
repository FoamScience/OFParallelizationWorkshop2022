/*---------------------------------------------------------------------------*\
Description
    Test parallelClass methods for Activity 01

Author
    Mohammed Elwardi Fadeli (elwardi.fadeli@tu-darmstadt.de)
\*---------------------------------------------------------------------------*/

#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "fvCFD.H"
#include "testMacros.H"
#include "parallelClass.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace Foam;

namespace serialParallel
{
    #include "createTestTime.H"
    autoPtr<fvMesh> meshPtr;
}
using namespace serialParallel;
prepareTimePaths();

TEST_CASE
(
    "Blocking P2P comms between two processes",
    "[Serial][Parallel][Case_cavity]"
)
{
    // Turn this on if you want to see FATAL ERROR msgs
    //FatalError.dontThrowExceptions();

    // Mess with Time paths so we can work care-free with both serial/parallel runs
    if (Pstream::parRun()) {
        word procPath = "processor"+Foam::name(Pstream::myProcNo());
        modifyTimePaths(runTime, true, procPath);
    }

    // Read mesh from case dir
    resetMeshPointer
    (
        runTime,
        meshPtr,
        fvMesh,
        fvMesh::defaultRegion
    );
    auto& mesh = meshPtr();

    SECTION("Collect a list on master") {
		// This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun());

        // Expected output
        std::vector<label> correctSizes{1,2,2,3,3,3};
        if (!Pstream::parRun()) correctSizes.clear();

        // Create a sample object and run the method
        parallelClass p(mesh);
        labelList res = p.run();

        // Compare to expected on master only
        if (Pstream::master()) {
            REQUIRE
            (
                std::vector<label>(res.begin(), res.end()) == correctSizes
            );
        }
    }

    // Do not forget to clear the mesh every time!
    meshPtr.clear();
}

#include "undefineTestMacros.H"

// ************************************************************************* //
