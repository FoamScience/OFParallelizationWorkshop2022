#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::parallelClass::checkPosition(const vector& position) const
{
    // This function must return true if the position is inside the global mesh
    // and false otherwise

    return returnReduce
    (
        mesh_.findCell(position) != -1,
        orOp<bool>()
    );
}

Foam::label Foam::parallelClass::whoHasReferenceCell(const vector& position) const
{
    // This function must return the process ID where the cell associated with
    // position is at; and -1 if position is outside the global mesh

    boolList ids(Pstream::nProcs(), false);
    ids[Pstream::myProcNo()] = mesh_.findCell(position) != -1;
    Pstream::gatherList(ids);
    Pstream::scatterList(ids);

    return findIndex(ids, true);
}

}
// ************************************************************************* //
