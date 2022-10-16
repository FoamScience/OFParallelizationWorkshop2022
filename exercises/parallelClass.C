#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

scalar Foam::parallelClass::run() const
{
    // This function must send v0 from proc 0 to proc 1
    // and v1 from proc 1 to proc 0;

    // And return v1 on proc 0, and v0 on proc 1
    scalar res = -1;
    scalar v0, v1 = -1;


    return res;
}

}
// ************************************************************************* //
