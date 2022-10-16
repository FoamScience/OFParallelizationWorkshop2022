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
    "Blocking P2P comms - find prime numbers",
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

    SECTION("Check if a number is prime") {
        // Expected output
        std::vector<label> primesUpTo800{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
            43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
            127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197,
            199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
            283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
            383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
            467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571,
            577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
            661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761,
            769, 773, 787, 797};
    
        // Choose a number randomly from 2-800
        label n = GENERATE(take(20, random(3, 800)));
    
        // If "--rng-seed time" is not pased in as  arg, 
        // make sure all processors agree on n value, so it's no longer random,
        // but good enough
        //reduce(n, maxOp<label>());
    
        // Create a sample object and run the method
        parallelClass p(mesh);
        bool nIsPrime = p.isPrime(n);
        bool isInPrimesList = std::find(primesUpTo800.begin(), primesUpTo800.end(), n) != primesUpTo800.end();
    
        // This has nothing to do with OpenFOAM
        CAPTURE(Pstream::parRun(), n, nIsPrime, isInPrimesList);
    
        REQUIRE(nIsPrime == isInPrimesList);

    }

    SECTION("Large prime numbers") {
        // Choose a number randomly from 2-800
        label n = 900016417;
    
        // Create a sample object and run the method
        parallelClass p(mesh);
        CAPTURE(Pstream::parRun(), n);
        REQUIRE(p.isPrime(n) == true);
    }

    // Do not forget to clear the mesh every time!
    meshPtr.clear();
}

#include "undefineTestMacros.H"

// ************************************************************************* //
