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
    "Parallel comms for custom data types",
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

    SECTION("Compatibility of Edge with List") {
    
        // Create a list of edges
        List<Edge> edges(Pstream::nProcs());

        // This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun(), Pstream::myProcNo());

        REQUIRE(edges.size() == Pstream::nProcs());
    }

    SECTION("Compatibility of Edge with *Pstreams") {
    
        // Create an Edge
        Edge e(0,0);
        if (Pstream::master()) {
            e.destination = 2;
            e.weight = .15;
        }

        Pstream::scatter(e);
        
        // This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun(), Pstream::myProcNo());

        REQUIRE(e.destination == 2);
        REQUIRE(e.weight == .15);
    }

    SECTION("A graph of edges") {
    
        List<List<Edge>> g = Edge::collectEdges(mesh);

        Edge e00(1,0);
        Edge e10(2,0);
        List<Edge> e0; e0.append(e00); e0.append(e10);
        //e0.append(e10); e0.append(e11);
        Edge e20(0,0);
        Edge e30(3,0);
        List<Edge> e2; e2.append(e20); e2.append(e30);
        List<List<Edge>> expectedG;
        expectedG.append(e0);
        expectedG.append(e2);
        expectedG.append(e2);
        expectedG.append(e0);
            
        if (Pstream::parRun()) {
            REQUIRE(g == expectedG);
        }
    }

    // Do not forget to clear the mesh every time!
    meshPtr.clear();
}

#include "undefineTestMacros.H"

// ************************************************************************* //
