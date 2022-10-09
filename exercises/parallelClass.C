#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::labelList Foam::parallelClass::run() const
{
    // This function must return:
    // A list containing all elements from lst_ from all processes (appended 
    // in the order of procID)

    // Eg. if lst_ is {0, 0} on proc 0 and it's {1, 1} on proc 1
    // The result should say: {0, 0, 1, 1}

    // Use blocking P2P communication API
    labelList res;
    
    return res;
}

}
// ************************************************************************* //
