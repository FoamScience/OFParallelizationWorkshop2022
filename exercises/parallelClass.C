#include "parallelClass.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::parallelClass::swapLists()
{
    // This function must send lists_[neiProcID] to neighbouring processor
    // and put it in lists_[myProcID] there

    // This function will not be tested for serial runs

    if (Pstream::parRun()) {
        labelList neis = this->neis();

    }
}

}
// ************************************************************************* //
