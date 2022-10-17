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

        // Initiate sends
        PstreamBuffers pBufs(Pstream::commsTypes::nonBlocking);
        for(auto& nei: neis) {
            UOPstream toNei(nei, pBufs);
            toNei << lists_[nei];
        }

        pBufs.finishedSends();

        // Receive all things
        for(auto& nei: neis) {
            UIPstream fromNei(nei, pBufs);
            lists_[nei] = labelList(fromNei);
        }
    }
}

}
// ************************************************************************* //
