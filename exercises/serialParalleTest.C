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
    "Collective comms - reference cells",
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

    SECTION("Check if reference point is in global mesh") {
    
        // Create a sample object and run the method
        parallelClass p(mesh);

        // This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun(), Pstream::myProcNo());
    
        // Position at proc 2
        vector pos(.0975, .0025, 0);
        label isInside = p.checkPosition(pos);

        REQUIRE(isInside == true);

        // Position outside the mesh
        vector out(1, 1, 0);
        label isOutside = !p.checkPosition(out);

        REQUIRE(isOutside == true);
    }

    SECTION("Get procID of owning process if position is inside the mesh") {
    
        // Create a sample object and run the method
        parallelClass p(mesh);

        // This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun(), Pstream::myProcNo());
    
        // Position at proc 2
        vector pos(.0975, .0025, 0);
        label id = p.whoHasReferenceCell(pos);

        if (Pstream::parRun()) {
            REQUIRE(id == 1);
        } else {
            REQUIRE(id == 0);
        }
    }

    // Do not forget to clear the mesh every time!
    meshPtr.clear();
}

#include "undefineTestMacros.H"

// ************************************************************************* //
