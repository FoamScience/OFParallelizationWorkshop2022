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

    if (Pstream::parRun) {
        const auto& patches = mesh_.boundaryMesh();
        labelList neis = this->neis();

        // Initiate sends
        for(auto& nei: neis) {
            OPstream toNei(Pstream::nonBlocking, nei);
            toNei << lists_[nei];
        }

        Pstream::waitRequests();

        // Receive all things
        for(auto& nei: neis) {
            IPstream fromNei(Pstream::nonBlocking, nei);
            lists_[nei] = labelList(fromNei);
        }
    }
}

}
// ************************************************************************* //
