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
    "Parallel comms for custom data types - advanced",
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

    SECTION("Compatibility of Edge with IDLList") {
    
        // Create a list of edges
        Edge e(mesh, 1);
        IDLList<Edge> edges;
        edges.append(e.clone().ptr());

        // This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun(), Pstream::myProcNo());

        REQUIRE(edges.size() == 1);
    }

    SECTION("Compatibility of Edge with *Pstreams") {
    
        // Create an Edge
        Edge e(mesh,0);
        if (Pstream::master()) {
            e.destination = 2;
        }

        Pstream::scatter(e);
        
        // This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun(), Pstream::myProcNo());

        REQUIRE(e.destination == 2);
    }

    SECTION("A graph of edges") {
        List<IDLList<Edge>> g = Edge::collectEdges(mesh);

        Edge e00(mesh,1);
        Edge e10(mesh,2);
        IDLList<Edge> e0; e0.append(e00.clone().ptr()); e0.append(e10.clone().ptr());
        Edge e20(mesh,0);
        Edge e30(mesh,3);
        IDLList<Edge> e2; e2.append(e20.clone().ptr()); e2.append(e30.clone().ptr());
        List<IDLList<Edge>> expectedG;
        expectedG.append(e0);
        expectedG.append(e2);
        expectedG.append(e2);
        expectedG.append(e0);
            
        if (Pstream::parRun() && Pstream::master()) {
            REQUIRE(g == expectedG);
        }
    }

    // Do not forget to clear the mesh every time!
    meshPtr.clear();
}

#include "undefineTestMacros.H"

// ************************************************************************* //
