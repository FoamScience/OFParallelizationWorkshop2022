#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::parallelClass::checkPosition(const vector& position) const
{
    // This function must return true if the position is inside the global mesh
    // and false otherwise

    return false;
}

Foam::label Foam::parallelClass::whoHasReferenceCell(const vector& position) const
{
    // This function must return the process ID where the cell associated with
    // position is at; and -1 if position is outside the global mesh

    return -1;
}

}
// ************************************************************************* //
